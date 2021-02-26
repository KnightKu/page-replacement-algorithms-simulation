#include "PT_Hashtable.h"
#include "LRU.h"
#include "Second_Chance.h"
#include "read_trace.h"
#include "statistics.h"

int main(int argc, char *argv[]){

	if(argc!=4 && argc!=5){
		printf("\n\nInsufficient or Excessive Number of Arguments!\n\n");
		return -1;
	}

	char* algorithm=strdup(argv[1]);

	if(strcmp(algorithm,"LRU")!=0 && strcmp(algorithm,"SC")!=0){
		printf("\n\nAlgorithm Argument must be SC (Second Chance) or LRU (Last Recently Used)!\n\n");
		return -1;	
	}

	unsigned int number_of_frames=atoi(argv[2]);

	if(number_of_frames<=0){
		printf("\n\nInvalid Number of Memory Frames!\n\n");
		return -1;		
	}

	int q=atoi(argv[3]);

	if(q<=0){
		printf("\n\nInvalid Value for q!\n\n");
		return -1;		
	}

	int max_references;

	if(argc==5){
		max_references=atoi(argv[4]);
		
		if(max_references<=0){
			printf("\n\nInvalid Value for Max References!\n\n");
			return -1;		
		}
	}
	
	else{
		max_references=2000000;
	}

	int free_frames_counter=number_of_frames;  //stores number of free memory frames
	frame *frames;

	frames=(frame*)malloc(number_of_frames*sizeof(struct frame));  

	int frame_pointer=0;		//stores the last checked frame in the second chance algorithm

	for(int i=0;i<number_of_frames;i++){
		frame_init(&frames[i]);
	}

	statistics * stats=NULL;
	statistics_init(&stats,number_of_frames);

	FILE * file_ptr[2];

	if((file_ptr[0]=fopen("bzip.trace","r"))==NULL){
		printf("bzip file not found!");
		return -1;
	}
	
	if((file_ptr[1]=fopen("gcc.trace","r"))==NULL){
		printf("gcc file not found!");
		return -1;
	}

	page_table_node** pt[2];	//stores hashed page table for each process
	pt[0]=NULL;
	pt[1]=NULL;
	
	pt_init(&pt[0]);
	pt_init(&pt[1]);
	
	lru_queue_head* queue=NULL;
	lru_queue_init(&queue);

	char RW='\0';
	unsigned int page=0;

	int pid=0;   // index of the first process to read

	int continuous_file_reads=0;	//used for the round robin read between the processes' traces

	struct page_table_entry* curr_entry=NULL;

	for(int trace=0;trace<max_references;trace++){

		if(read_next_trace(file_ptr[pid], &page, &RW)!=0)break;
		
		increase_traces_reads(stats);

		continuous_file_reads++;

		if((curr_entry=pt_get(pt[pid],page))==NULL){
			curr_entry=pt_insert(pt[pid],page);
		}

		if(RW=='W'){
			page_set_dirty_bit(curr_entry,1);
		}

		if(!page_in_memory(curr_entry)){

			increase_disc_reads(stats);

			increase_page_faults(stats);

			if(strcmp(algorithm,"LRU")==0)lru_queue_push(queue,page,pid,0);

			//if there is available empty frame, place the page there
			if(free_frames_counter>0){
			    for(int i=0;i<number_of_frames;i++){
					if(frame_empty(&frames[i])==1){
						insert_page_to_memory(pt_get(pt[pid],page),i);
						free_frames_counter--;
						frame_set_page(&frames[i],page,pid);
						break;
					}
				}
			}

			//else use replacement algorithm
			else{

				int removed_page_number;
				int removed_page_pid;
				
				if(strcmp(algorithm,"LRU")==0)LRU(queue,&removed_page_number,&removed_page_pid);
				else if(strcmp(algorithm,"SC")==0)Second_Chance(frames,&removed_page_number,&removed_page_pid,number_of_frames,&frame_pointer);

				page_table_entry* popped_entry=pt_get(pt[removed_page_pid],removed_page_number);
				
				int free_frame=page_get_frame_number(popped_entry);
				insert_page_to_memory(curr_entry,free_frame);
				frame_set_page(&frames[free_frame],page,pid);
				
				//if page was written while on memory, write it back to disc

				if(page_get_dirty_bit(popped_entry)){
					increase_disc_writes(stats);
					page_set_dirty_bit(popped_entry,0);
				}
				remove_page_from_memory(popped_entry);
			}
		}

		else{
			if(strcmp(algorithm,"LRU")==0)lru_queue_push(queue,page,pid,1);
			else if(strcmp(algorithm,"SC")==0)frame_set_second_chance_bit(&frames[page_get_frame_number(curr_entry)],1);
		}

		//time to read from the other process
		if(continuous_file_reads==q){
			continuous_file_reads=0;
			if(pid==1)pid=0;
			else pid++;
		}

	}

	//destory (free) what's allocated
	pt_destroy(&pt[0]);
	pt_destroy(&pt[1]);
	
	lru_queue_destroy(&queue);

	fclose(file_ptr[0]);
	fclose(file_ptr[1]);

	free(frames);

	//print statistics
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~           Algorithm           ~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

	if(strcmp(algorithm,"LRU")==0){
		printf("               LRU                \n");
	}

	else{
		printf("          Second Chance       \n");
	}

	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

	statistics_display(stats);
	statistics_destroy(&stats);
	free(algorithm);

	return 0;

}