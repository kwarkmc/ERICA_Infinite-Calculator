#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"

/*
	getNode 함수 생성
	doubly로의 변경
	38번째 줄의 주석
	72-74 번째 사용 예제
	*/

typedef char element;
typedef struct pointer{
	struct node_info *head;
	struct node_info *tail;
}pointer;// pointer

typedef struct node_info{
	element data; 
	struct node_info* next_pointer;
	struct node_info* prev_pointer;
}node_info;// node에 있는 data

void insert_node(pointer *target,int data){
	node_info *new_node = malloc(sizeof(node_info));//new_node를 하기 전이 미리 초기화
	new_node -> next_pointer = NULL;
	new_node -> prev_pointer = NULL;
	new_node -> data = data;
	if(target->head == NULL) // insert할때, 처음일 경우 head와 tail에 node를 넣어준다.
		target->head = target->tail = new_node;

	else{ // 처음이 아닐 경우
		target->tail-> next_pointer = new_node;//tail다음에 new_node를 넣어준다.
		new_node->prev_pointer = target->tail;
		target->tail = new_node; // 그 다음  tail은 new_node로 설정한다.
	}
}
node_info* getNode(node_info *target,char index_char){
	while(target != NULL){
		if(index_char == target->data) break;
		target = target->next_pointer;
	/*
	   이 부분을 stack으로 구현하면 될 듯 하다. target에 원하는 char(예: +)를 찾는 함수이다.
		break 부분을 지우고 다음을 계속 진행하면 된다.
		*/
	}
	return target;
}

int prec(char op) {
	swtich(op) {
		case'(':case')':
		return 0;
		case'+':case'-':
		return 1;
		case'*':
		return 2;
	}
	return -1;
}

void infix_to_postfix(char exp[]) {
	int i = 0;
	char ch, top_op;
	int len = strlen(exp);
	StackType s;

	init(&s);

	for(i=0;i<len;i++) {
		ch = exp[i];

		switch(ch) {
			case'+':case'-':case'*':
			while (!is_empty(&s) && (prec(ch)) <= prec(peek(&s)))
				pop(&s); // pop값을 어디로 반환?
		}
	}
}

int main(int argc,char* argv[]){
	StackType s; // Stack 선언
	char data;
	FILE *fp=fopen(argv[1],"r");// argv[1]에는 input이 있다.
	if(fp==NULL)
		printf("file not exist"); // file이 존재하지 않을 경우의 예외처리 이거 segmentation Error가 뜨네? 이거 수정 해야함
	pointer *L = (pointer *)malloc(sizeof(pointer)); // L은 linkedlist의 약자
	L->head = NULL;
	L->tail = NULL;
	while(fscanf(fp,"%c",&data)!=EOF){
		if(data == 32 || data == 43 || data == 45 || data == 46 || (data > 47 && data < 58)){// 숫자 혹은 +,-,공백일 경우에는 insert 하는 것
			insert_node(L,data);
		}
		else continue;// 숫자등이 아닐 경우 다음으로 넘긴다.
	}
	fclose(fp);// 메모리를 위해 fp를 닫는다.
	node_info *curr = L->head; 
	while(curr!=NULL){
		printf("%c",curr->data);
		/*
		   지금 이 부분에 printf하는 부분을 빼고 후위 표기법에 대한 함수를 넣으면 될 것이다.
		   새로운 linked list를 만들어서 다시 insert해야한다.
		   1)공백이 나올 때 까지 
		   */
		curr = curr->next_pointer;
	}//curr에 있는 data 소환하는 부분
	printf("\n");
	curr = L->head;
	node_info *test= getNode(curr,' ');
	printf("%c",test->data); 
	printf("%c",test->prev_pointer->data); 
	// 지금은 data를 소환하는 부분이지만, 나중에는 후위 표기법을 넣는 부분으로 주석을 바꿔 적어야 한다.
	curr = L->head;// 초기화를 위해 다시 L의 head 포인터로 이동
	while(curr != NULL){
		node_info *next = curr->next_pointer;
		free(curr);
		curr = next;
	}//초기화하는 부분
	free(L);
	
	return 0;

	/*
	   주석이 많으면 오히려 가독성이 떨어진다.
	   이거에 대해 논의 해야 한다.
	   */


 }