/*********************************************/
/*  Struct used to represent a Memory Frame  */
/*********************************************/


#include "common.h"

struct frame{
	int page_number;
	int page_number_pid;
	int second_chance_bit;
};

typedef struct frame frame;

int frame_init(frame*);		//initializes a frame struct instance

//Functions below return -1 if frame pointer is NULL
	
int frame_get_page(frame*, int*, int*);	// returns number of page and it's process by pointers

int frame_set_page(frame*, int, int);	// used to "insert" a page in the frame

int frame_empty(frame*); // returns 1 if frame is empty, else 0

int frame_get_second_chance_bit(frame*); 

int frame_set_second_chance_bit(frame*, int);