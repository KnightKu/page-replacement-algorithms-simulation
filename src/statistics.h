/*********************************************************/
/* Struct and Methods used for the Simulation Statistics */ 
/*********************************************************/

#include "common.h"

struct statistics;

typedef struct statistics statistics;


int statistics_init(statistics**, int);  //returns -1 if statistics is already initialized

int statistics_destroy(statistics**);    //returns -1 if statistics is not initialized

int statistics_reset(statistics*, int); 		//returns -1 if statistics it not initialzed

//Methods below return -1 if statistics are not initialized

int increase_disc_reads(statistics*);

int increase_disc_writes(statistics*);

int increase_page_faults(statistics*);

int increase_traces_reads(statistics*);

int get_disc_reads(statistics*);

int get_disc_writes(statistics*);

int get_page_faults(statistics*);

int get_traces_reads(statistics*);

int statistics_display(statistics*);