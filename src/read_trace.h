/***********************************************/
/*  Reads Logical Address Traces and R/W from  */
/*	files of the given format like bzip.trace  */
/*	and  gcc.trace. Reads one (next)  address  */
/*  each  time. Page number is isolated  from  */
/*  logical address. Offset is not needed for  */
/*  the purposes of this simulation.           */
/***********************************************/


#include "common.h"

struct sc_queue_head;
struct sc_queue_node;

typedef struct sc_queue_head sc_queue_head;
typedef struct sc_queue_node sc_queue_node;
	
//reads next trace from given file, returns 0 for success, -1 for End of File, -2 for End of File, -3 for Improper Form
int read_next_trace(FILE *, unsigned int *, char *);	