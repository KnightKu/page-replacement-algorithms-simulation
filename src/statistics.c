/*********************************************************/
/*        Implementation of Statistics' Methods          */ 
/*********************************************************/

#include "statistics.h"

struct statistics{
	int disc_reads;
	int disc_writes;
	int page_faults;
	int traces_reads;
	int frames_number;	
};

int statistics_init(statistics** stats, int frames_number){
	
	if(*stats!=NULL)return -1;	//stats is already initialized
	
	*stats=(statistics*)malloc(sizeof(statistics));

	(*stats)->disc_reads=0;
	(*stats)->disc_writes=0;
	(*stats)->page_faults=0;
	(*stats)->traces_reads=0;
	(*stats)->frames_number=frames_number;
	
	return 0;

}

int statistics_destroy(statistics** stats){

	if(*stats==NULL)return -1;	//stats is not initialized

	free(*stats);
	*stats=NULL;

	return 0;

}

int statistics_reset(statistics* stats, int frames_number){

	if(stats==NULL)return -1;

	stats->disc_reads=0;
	stats->disc_writes=0;
	stats->page_faults=0;
	stats->traces_reads=0;
	stats->frames_number=frames_number;

	return 0;

}

int increase_disc_reads(statistics* stats){

	if(stats==NULL)return -1;

	stats->disc_reads++;

	return 0;

}

int increase_disc_writes(statistics* stats){

	if(stats==NULL)return -1;

	stats->disc_writes++;

	return 0;

}

int increase_page_faults(statistics* stats){

	if(stats==NULL)return -1;

	stats->page_faults++;

	return 0;
}

int increase_traces_reads(statistics* stats){

	if(stats==NULL)return -1;

	stats->traces_reads++;

	return 0;	

}

int get_disc_reads(statistics* stats){

	if(stats==NULL)return -1;

	return stats->disc_reads;

}

int get_disc_writes(statistics* stats){

	if(stats==NULL)return -1;

	return stats->disc_writes;

}

int get_page_faults(statistics* stats){

	if(stats==NULL)return -1;

	return stats->page_faults;

}

int get_traces_reads(statistics* stats){

	if(stats==NULL)return -1;

	return stats->traces_reads;

}

int get_frames_number(statistics* stats){

	if(stats==NULL)return -1;

	return stats->frames_number;

}

int statistics_display(statistics* stats){

	if(stats==NULL)return -1;

	printf("\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~           STATISTICS           ~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

	printf("Disc Reads   : %d\n",stats->disc_reads);
	printf("Disc Writes  : %d\n",stats->disc_writes);
	printf("Page Faults  : %d\n",stats->page_faults);
	printf("Traces Read  : %d\n",stats->traces_reads);
	printf("Frames Number: %d\n",stats->frames_number);

	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

	return 0;

}