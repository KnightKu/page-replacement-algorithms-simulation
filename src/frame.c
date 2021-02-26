/**********************************************/
/*  Implementation of Struct Frame's Methods  */
/**********************************************/


#include "frame.h"


int frame_init(frame* fr){
	
	if(fr==NULL)return -1;

	fr->page_number=-1;
	fr->page_number_pid=-1;
	fr->second_chance_bit=0;

	return 0;
}

int frame_get_page(frame* fr, int* page_number, int* pid){
	
	if(fr==NULL)return -1;

	*page_number=fr->page_number;
	*pid=fr->page_number_pid;

	return 0;
}

int frame_set_page(frame* fr, int page_number, int pid){

	if(fr==NULL)return -1;

	fr->page_number=page_number;
	fr->page_number_pid=pid;
	fr->second_chance_bit=0;

	return 0;
}

int frame_get_second_chance_bit(frame* fr){
	if(fr==NULL)return -1;

	return fr->second_chance_bit;	
}

int frame_set_second_chance_bit(frame* fr, int i){

	if(fr==NULL)return -1;

	fr->second_chance_bit=i;

	return 0;

}

int frame_empty(frame* fr){

	if(fr==NULL)return -1;

	if(fr->page_number==-1)return 1;

	return 0;
}