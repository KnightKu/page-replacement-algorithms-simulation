/***************************************************/
/*  Implementation of Hash Talbe and Page Methods  */
/***************************************************/


#include "PT_Hashtable.h"

struct page_table_entry{
	int page_number;
	int frame_number;
	int dirty_bit;
};

struct page_table_node{
	page_table_entry page_entry;
	page_table_node *next;
};

int hash_function(unsigned int page_number){
	return page_number%NUM_OF_BUCKETS;
}

int pt_init(page_table_node*** ht_array){
	
	if(*ht_array!=NULL)return -1;
	
	*ht_array=(page_table_node**)malloc(NUM_OF_BUCKETS*sizeof(page_table_node));
	
	for(int i=0;i<NUM_OF_BUCKETS;i++){
		(*ht_array)[i]=NULL;	
	}
	
	return 0;
	
}

int pt_clear(page_table_node** ht_array){
	
	if(ht_array==NULL)return -1;

	page_table_node* temp_node;
	page_table_node* next_node;
	
	for(int bucket=0; bucket<NUM_OF_BUCKETS; bucket++){
		page_table_node* temp_node=ht_array[bucket];
		while(temp_node!=NULL){
			next_node=temp_node->next;
			free(temp_node);
			temp_node=next_node;
		}
		ht_array[bucket]=NULL;	
	}

	return 0;

}

int pt_destroy(page_table_node*** ht_array){

	if(*ht_array==NULL)return -1;
	
	pt_clear(*ht_array);
	
	for(int bucket=0; bucket<NUM_OF_BUCKETS; bucket++){
		(*ht_array)[bucket]=NULL;	
	}
	free(*ht_array);

	return 0;

}

page_table_entry * pt_insert(page_table_node** ht_array, unsigned int page_number){
	
	if(ht_array==NULL)return NULL;

	int bucket=hash_function(page_number);	
	page_table_node * new_node;
	new_node=(page_table_node*)malloc(sizeof(page_table_node));
	new_node->next=NULL;
	new_node->page_entry.page_number=page_number;
	new_node->page_entry.frame_number=-1;
	new_node->page_entry.dirty_bit=0;
	
	if(ht_array[bucket]==NULL){
		ht_array[bucket]=new_node;
	}
	else{
		page_table_node* temp_node=ht_array[bucket];
		while(temp_node->next!=NULL){
			temp_node=temp_node->next;	
		}
		temp_node->next=new_node;
	}
	
	return &new_node->page_entry;

}

page_table_entry * pt_get(page_table_node** ht_array, unsigned int page_number){
	

	if(ht_array==NULL)return NULL;

	int bucket=hash_function(page_number);

	page_table_node* temp_node=ht_array[bucket];

	if(temp_node==NULL)return NULL;
	


	while(temp_node!=NULL){
		if(temp_node->page_entry.page_number==page_number){
			return &temp_node->page_entry;
		}
		temp_node=temp_node->next;
	}
	return NULL;

}

int pt_display(page_table_node** ht_array){
	
	if(ht_array==NULL)return -1;

	for(int i=0;i<NUM_OF_BUCKETS;i++){
		printf("Bucket NO: %d \n",i);
		if(ht_array[i]==NULL){
			continue;
		}
		else{
			struct page_table_node* temp_node=ht_array[i];
			while(temp_node!=NULL){
				printf("%d [%d]->",temp_node->page_entry.page_number,temp_node->page_entry.frame_number);
				temp_node=temp_node->next;	
			}
		}
		printf("\n~~~~~~~~~~~~~~~~~~~~~\n");
	}

	return 0;

}

int page_in_memory(page_table_entry* page){
	
	if(page==NULL)return -1;
	
	if(page->frame_number==-1){
		return 0;
	}
	else{
		return 1;
	}
}

int insert_page_to_memory(page_table_entry* page, int frame){
	
	if(page==NULL)return -1;

	page->frame_number=frame;

	return 0;

}

int remove_page_from_memory(page_table_entry* page){
	
	if(page==NULL)return -1;

	page->dirty_bit=0;
	page->frame_number=-1;	

	return 0;

}

int page_get_page_number(page_table_entry* page){

	if(page==NULL)return -1;

	return page->page_number;

}

int page_get_frame_number(page_table_entry* page){

	if(page==NULL)return -1;
	return page->frame_number;

}

int page_set_dirty_bit(page_table_entry* page, int i){

	if(page==NULL)return -1;

	page->dirty_bit=i;

	return 0;

}

int page_get_dirty_bit(page_table_entry* page){

	if(page==NULL)return -1;

	return page->dirty_bit;

}