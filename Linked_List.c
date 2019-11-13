#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int element;
typedef struct position{
	struct node *cur;
	struct node *tail;
	struct node *head;
}position;

typedef struct node{
	element data; 
	struct node* next;
}node;//구조체 생성
void insert_node(position *target,int data){
	node *new_node = malloc(sizeof(node));
	new_node-> next = NULL;
	new_node-> data = data;
	if(target->head == NULL && target->tail == NULL)
		target->head = target->tail = new_node;
	else{
		target->tail->next = new_node;
		target->tail = new_node;
	}
}
int main(int argc,char* argv[]){
	int data;
	
	FILE *fp=fopen(argv[1],"r");
	if(fp==NULL)
		printf("file not exist");
	position *L = (position *)malloc(sizeof(position));
	L->head = NULL;
	L->tail = NULL;
	while(fscanf(fp,"%d",&data)!=EOF){
		if(data == 32 || data == 43 || data == 45 || data == 46 || (data > 47 && data < 58)){//다 통과 
			insert_node(L,data);
		}
		else continue;
	}
	fclose(fp);
	node *curr = L->head;
	while(curr!=NULL){
		printf("%c",curr->data);
		/*
		   지금 이 부분에 printf하는 부분을 빼고 후위 표기법에 대한 함수를 넣으면 될 것이다.
		   */
		curr = curr->next;
	}//curr에 있는 data 소환하는 부분
	curr = L->head;
	while(curr != NULL){
		node *next = curr->next;
		free(curr);
		curr = next;
	}//free 하는 부분
	free(L);
	
	return 0;
 }

