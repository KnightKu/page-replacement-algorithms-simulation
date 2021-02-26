/***************************************************/
/*  Implementation of the Second Change Algorithm  */
/***************************************************/


#include "Second_Chance.h"

int Second_Chance(frame frame_array[], int* page_number, int* page_pid, int frames_number, int *frame_pointer){
	
	for(int i=0;i<frames_number;i++){
		//if page in this frame doesn't have a second chance or if it's the last frame to be examined, victimize it
		if(frame_get_second_chance_bit(&frame_array[(i+*frame_pointer)%frames_number])==0 || i==frames_number-1){
			frame_get_page(&frame_array[(i+*frame_pointer)%frames_number], page_number, page_pid);
			*frame_pointer=(i+*frame_pointer)%frames_number+1;
			return 0;
		}
		//the page in this frame doesn't have a second chance anymore
		else{
			frame_set_second_chance_bit(&frame_array[(i+*frame_pointer)%frames_number],0);	
		}
	}
}