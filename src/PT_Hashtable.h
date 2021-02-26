/**********************************************/
/*  Hashtable used as a  Page Table in   the  */
/*  Simulation. Each Hashtable Node includes  */
/*  Page Number, Frame Number and Dirty  Bit  */
/*  Number of Buckets doesn't change 		  */
/**********************************************/



#include "common.h"

struct page_table_entry;
struct page_table_node;

typedef struct page_table_entry page_table_entry;
typedef struct page_table_node page_table_node;

int pt_init(page_table_node***);		//returns -1 if page table is already initialized

int pt_clear(page_table_node**);		//returns -1 if page table is not initialized

int pt_destroy(page_table_node***);  	//returns -1 if page is not initialized

page_table_entry * pt_insert(page_table_node**, unsigned int);//returns newly inserted/created page_table_enrty

page_table_entry * pt_get(page_table_node**, unsigned int);	  //returns page_table_entry by given page number

int pt_display(page_table_node**);		//used for testing purposes

//Methods below return -1 if page_table_entry is NULL

int insert_page_to_memory(page_table_entry*, int);

int remove_page_from_memory(page_table_entry*);

int page_in_memory(page_table_entry*);		//returns 1 if page is in memory, else returns 0

int page_get_page_number(page_table_entry*);

int page_get_frame_number(page_table_entry*);

int page_set_dirty_bit(page_table_entry*, int);

int page_get_dirty_bit(page_table_entry*);		