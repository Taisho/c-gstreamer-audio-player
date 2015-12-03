
typedef struct
{
    int size;
    int counter;
    int rear; // This variable points to the offset immediately *after* the last data
    int front;
    char** data; 
} Queue_t;

int queue_count (Queue_t * queue);
int queue_is_empty (Queue_t * queue);
int queue_is_full (Queue_t * queue);
int queue_push(Queue_t * queue, char * data);
int queue_pop(Queue_t * queue, char **data);
Queue_t * queue_new (int size);
void queue_destroy (Queue_t * queue);
