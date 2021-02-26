/*********************************************/
/*  read_next_trace Function Implementation  */
/*********************************************/

#include "read_trace.h"

//reads next trace from file, returns 0 for success, -1 for End of File, -2 for improper form
int read_next_trace(FILE *file, unsigned int *page_number, char *RW){
	
	if(file==NULL)return -1;

	char c;
	char logical_address_string[LOGICAL_ADDRESS_SIZE+1]="";
	
	if((c=fgetc(file))==EOF || c==' ')return -2;  //end of file
	
	//read logical address by appending characters from file until a space character is found
	do{
		strncat(logical_address_string,&c,1);
	}while((c=fgetc(file))!= ' ');
	
	//read R or W character
	c=fgetc(file);
	*RW=c;
	
	if(*RW!='R' && *RW!='W')return -3; //read or write character should be R or W
	
	c=fgetc(file); //read end line character to set the file pointer to the next line
	
	unsigned int logical_address_number=(int)strtol(logical_address_string, NULL, 16);
	
	*page_number=logical_address_number>>OFFSET_BITS;
	
	return 0;

}