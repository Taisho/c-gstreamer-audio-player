#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <unistd.h>
#include "queue.h"

#define BUF_SIZE 1024*1024
#define SOCKET_READ_LENGTH 320
#define PATH_LENGTH 4069
#define TRACK_LIST_SIZE 10

typedef struct
{
    char filename[PATH_LENGTH];
} TrackEntry;

//char *socket_path = "./socket";
char *socket_path = "\0hidden";
Queue_t* playlist_queue;
Queue_t* working_queue;
TrackEntry * trackList;
 
void execute (char * command)
{
    switch (command[0])
    {
    case 'Q':
        if (! queue_is_full (playlist_queue))
        {
            /* Store filename, so we can retrieve it later */
            int trackIndex = queue_count(playlist_queue);
            strcpy((char*) &trackList[trackIndex].filename, &command[1]);

            /* Enqueue */
            printf("Enqueue: %s\n", &command[1]);
            queue_push (playlist_queue, (char*) &trackList[trackIndex]);
        }
        else
        {
            puts("Queue is full!");
        }
        break;

    case 'P':
        printf("Print playlist:\n");
        /* Retrieve data from queue */
        char *registry;
        //printf("Popping out of the queue: \n");
        for (int i=0; ; i++)
        {
            if (queue_is_empty(playlist_queue)){
                //printf("Queue is empty at %ith pop\n", i);
                break;
            }

            queue_pop(playlist_queue, &registry);
            //puts(registry);
            printf("\tEntry: %s\n", ((TrackEntry*) registry)->filename);
            queue_push(working_queue, registry);
        }
        void * queue = playlist_queue;
        playlist_queue = working_queue;
        working_queue = queue;

        break;     
    }
}

int main(int argc, char *argv[]) {
  struct sockaddr_un addr;
  char * buf;
  int buf_size=BUF_SIZE;
  int socketReadLength = SOCKET_READ_LENGTH;
  int fd,cl,rc = 0, buf_offset = 0;
  playlist_queue = queue_new(3); 
  working_queue = queue_new(3); 


  if (argc > 1) socket_path=argv[1];

  if ( (fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
    perror("socket error");
    exit(-1);
  }

  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);

  unlink(socket_path);

  if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
    perror("bind error");
    exit(-1);
  }

  if (listen(fd, 5) == -1) {
    perror("listen error");
    exit(-1);
  }


  while (1) {
    if ( (cl = accept(fd, NULL, NULL)) == -1) {
      perror("accept error");
      continue;
    }

    buf = (char*) malloc(buf_size);
    trackList = malloc(sizeof(TrackEntry) * TRACK_LIST_SIZE);

    if (buf == NULL || trackList == NULL)
    {
        perror("memory allocation error");
        continue;
    }

    while ( (rc=read(cl,buf+buf_offset,socketReadLength)) > 0) {
        buf_offset += rc;

        if (rc < socketReadLength)
        {/* Final chunk of data arrived */

            /* remove trailing line feed (\n) */
            if ( *(buf+buf_offset-1) == '\n')
            {
                buf_offset--; 
            }

            *(buf+buf_offset) = 0; //inserting null-byte
            //printf("buffer %i: %s\n", buf, buf);
            execute (buf);
            buf_offset = 0; //reset buffer
            /* Recieve next data adjecent to the previous one. This effectively means we have a "data history" */
            //buf += buf_offset;
        }

    }

    if (rc == -1) {
      perror("read");
      exit(-1);
    }
    else if (rc == 0) {
      //printf("EOF\n");
      close(cl);
    }
    
    free(buf);
  }


  return 0;
}