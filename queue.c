#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int queue_count (Queue_t * queue)
{
    return queue->counter;
}

int queue_is_full (Queue_t * queue)
{
    int returnVal = 0;
    if (queue->counter == queue->size)
    {
        returnVal = 1;
    }
    return returnVal;
}

int queue_is_empty (Queue_t * queue)
{
    int returnVal = 0;
    if (queue->counter == 0)
    {
        returnVal = 1;
    }
    return returnVal;
}

int queue_push (Queue_t *queue, char* data){

   if (queue_is_full(queue))
       return -1;

   queue->counter++;
   queue->data[queue->rear] = data; 
   queue->rear++;

   if (queue->rear > queue->size) 
       queue->rear=0;

   return 0;
}

int queue_pop (Queue_t *queue, char **data)
{   
    if (queue_is_empty(queue))
        return -1;
    
    queue->counter--;
 
    *data=queue->data[queue->front];

    queue->front++;

    if (queue->front > queue->size)
        queue->front=0;

    return 0;
}

void queue_init (Queue_t * queue, void* memblock, int size)
{
    queue->rear = 0;
    queue->counter = 0;
    queue->front = 0;
    queue->size = size;
    queue->data = memblock; 
}

Queue_t * queue_new(int size)
{
    Queue_t* memblock = malloc(size * sizeof(char *) + sizeof(Queue_t));
    void* queue_pool = memblock + sizeof(Queue_t);
    
    if (memblock != 0){
        queue_init( memblock, queue_pool, size);
        return memblock;
    }

    return (Queue_t*) 0; 
}

void queue_destroy (Queue_t * queue)
{
    free (queue);
}
