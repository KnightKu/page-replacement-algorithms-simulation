/*********************************************/
/*        LRU/LRU Queue Implementation       */
/*********************************************/


#include "LRU.h"

struct lru_queue_node{
	unsigned int page_number;
	int pid;
	struct lru_queue_node* next;
};

struct lru_queue_head{
	struct lru_queue_node* first;
	struct lru_queue_node* last;
};

int lru_queue_init(lru_queue_head** head){
	
	if(*head!=NULL)return -1;	//queue already initialized

	(*head)=(lru_queue_head*)malloc(sizeof(lru_queue_head));
	(*head)->first=NULL;
	(*head)->last=NULL;

	return 0;

}

int lru_queue_destroy(lru_queue_head** head){
	
	if(*head==NULL)return -1;

	lru_queue_node* temp=(*head)->first;
	lru_queue_node* next;

	//deallocate all queue nodes
	while(temp!=NULL){
		next=temp->next;
		free(temp);
		temp=next;
	}

	(*head)->first=NULL;
	(*head)->last=NULL;

	//deallocate queue head
	free(*head);

	*head=NULL;

	return 0;
  
}

int lru_queue_size(lru_queue_head* head){

	if(head==NULL)return -1;

	int counter=0;
	
	lru_queue_node* temp_node=head->first;
	
	//count sum of queue nodes
	while(temp_node!=NULL){
		counter++;
		temp_node=temp_node->next;
	}

	return counter;
}

int lru_queue_push(lru_queue_head* head, unsigned int page_number, int pid, int page_in_memory){

	if(head==NULL)return -1;

	if(page_in_memory==1)lru_queue_delete(head,page_number, pid);  //delete duplicates
	
	//allocate and set new node
	lru_queue_node* new_node=(lru_queue_node*)malloc(sizeof(lru_queue_node));
	new_node->next=NULL;
	new_node->page_number=page_number;
	new_node->pid=pid;
	
	//if queue was empty before
	if(head->first==NULL){
		head->first=new_node;
		head->last=new_node;
	}
	
	else{
		head->last->next=new_node;
		head->last=new_node;
	}

	return 0;
}

int lru_queue_pop(lru_queue_head* head, int *pid){

	if(head==NULL || lru_queue_size(head)==0)return -1;	//if queue is unitialized or empty

	//if queue has a single element
	else if(lru_queue_size(head)==1){
		unsigned int page_number=head->first->page_number;
		*pid=head->first->pid;
		free(head->first);
		head->first=NULL;
		head->last=NULL;	
		return page_number;
	}
	
	else{
		unsigned int page_number=head->first->page_number;
		*pid=head->first->pid;
		lru_queue_node* to_be_deleted=head->first;
		head->first=head->first->next;
		free(to_be_deleted);	
		return page_number;
	}
}

int lru_queue_delete(lru_queue_head* head, unsigned int page_number, int pid){
	
	if(head->first==NULL)return -1;

	lru_queue_node* temp_node=head->first;
	lru_queue_node* to_be_deleted=NULL;
	
	while(temp_node->next!=NULL){
		if(temp_node->next->page_number==page_number && temp_node->next->pid==pid){
			to_be_deleted=temp_node->next;
			if(temp_node->next!=NULL){
				temp_node->next=temp_node->next->next;
				if(temp_node->next==NULL){
					head->last=temp_node;
				}
			}
			else{
				temp_node->next=NULL;
				head->last=temp_node;
				free(to_be_deleted);
				break;	
			}
			free(to_be_deleted);
		}
		else{
			temp_node=temp_node->next;
		}
	}
	
	if(head->first->page_number==page_number && head->first->pid==pid){
		if(lru_queue_size(head)==1){
			free(head->first);
			head->first=NULL;
			head->last=NULL;
		}
		
		else{
			to_be_deleted=head->first;
			head->first=head->first->next;
			free(to_be_deleted);
		}
	}
	
	return 0;

}

void lru_queue_display(lru_queue_head* head){
	
	if(head==NULL)return;

	lru_queue_node* temp_node=head->first;
	
	while(temp_node!=NULL){
		printf("%d->",temp_node->page_number);
		temp_node=temp_node->next;
	}
}

int LRU(lru_queue_head* queue_head, int* page, int* pid){
	
	if(queue_head==NULL)return -1;

	int free_frame=-1;

	*page=lru_queue_pop(queue_head,pid);

	return 0;
}