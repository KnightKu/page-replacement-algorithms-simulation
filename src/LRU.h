/*********************************************/
/*  Queue used for the LRU Page Replacement  */
/*  ALgorithm. It's implemented as a Linked  */
/*  List,  where pop happens at  the  first  */
/* 	element and push  at the last one. Each  */
/*  node includes a page number. Duplicates  */
/*  with lower priority get removed when  a  */
/*  new element with  same value  is pushed  */
/*********************************************/


#include "common.h"

struct lru_queue_node;
struct lru_queue_head;

typedef struct lru_queue_node lru_queue_node;
typedef struct lru_queue_head lru_queue_head;

int lru_queue_init(lru_queue_head**);		//returns -1 if queue is already initialized

int lru_queue_destroy(lru_queue_head**);	//returns -1 if queue is unitialized

int lru_queue_size(lru_queue_head*);		//returns size of the queue or -1 if it's unitialized

int lru_queue_push(lru_queue_head*, unsigned int, int, int);	//returns -1 if queue is unitialized

int lru_queue_pop(lru_queue_head*, int*);			//returns the value of the popped element or -1 if queue is empty or unitialized

int lru_queue_delete(lru_queue_head*, unsigned int, int);  //removes a particular element from the queue, returns -1 if queue is unitialized

void lru_queue_display(lru_queue_head*);    //displays queue for testing purposes

int LRU(lru_queue_head*, int*, int*);