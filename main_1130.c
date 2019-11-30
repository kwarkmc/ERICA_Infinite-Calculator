#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef char element;
typedef struct pointer{
	struct node_info *head;
	struct node_info *tail;
}pointer;

typedef struct node_info{
	element data; 
	struct node_info* next_pointer;
	struct node_info* prev_pointer;
}node_info;

bool flag = 0;

//Stack 구현 시작

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Stack {
    Node *top;
} Stack;

void init_stack(Stack *stack) {
    stack->top = NULL;
}

int is_empty(Stack *stack) {
    return (stack->top == NULL);
}

void Push(Stack *stack, int data) {
    Node *now = (Node *)malloc(sizeof(Node));
    now->data = data;
    now->next = stack->top;
    stack->top = now;
}

int Pop(Stack *stack) {
    Node *now;
    int re;

    if(is_empty(stack)) {
        fprintf(stderr, "Stack Empty\n");
        exit(1);
    }

    now = stack->top;
    re = now->data;
    stack->top = now->next;
    free(now);
    return re;
}

int Peek(Stack *stack) {
    if(is_empty(stack)) {
        fprintf(stderr, "Stack Full\n");
        exit(1);
    }
    return stack->top->data;
}

//Stack 구현 완료

void insert_node(pointer *target,int data){
	node_info *new_node = malloc(sizeof(node_info));
	new_node -> next_pointer = NULL;
	new_node -> prev_pointer = NULL;
	new_node -> data = data;
	if(target->head == NULL)
		target->head = target->tail = new_node;
	else{
		target->tail-> next_pointer = new_node;
		new_node->prev_pointer = target->tail;
		target->tail = new_node; 
	}
}//target의 tail에 inster 하는 것

void insert_next_node(node_info *target,int data){
    node_info *new_node = malloc(sizeof(node_info));
    new_node -> data = data;
    new_node->prev_pointer = target;
    new_node->next_pointer = target->next_pointer;
    target->next_pointer->prev_pointer = new_node;
    target-> next_pointer = new_node;
}// target의 뒷부분에 data를 넣는 부분

void insert_prev_node(node_info *target,int data){
    node_info *new_node = malloc(sizeof(node_info));
	new_node->data = data;
    new_node->next_pointer = target;
    new_node->prev_pointer = target->prev_pointer;
	target->prev_pointer->next_pointer = new_node;
    target->prev_pointer = new_node;
}// target의 앞부분에 data를 넣는 부분

void insert_head_node(pointer *target,int data){
	node_info *curr = target->head;
	node_info *new_node = malloc(sizeof(node_info));
	new_node ->data = data;
	new_node -> next_pointer = curr;
	new_node -> prev_pointer = curr->prev_pointer;
	curr ->prev_pointer = new_node;
	target->head = target->head->prev_pointer;
}//head에 insert하는 부분

node_info* getNode(node_info *target,char index_char){
	/*
	   getNode를 하는 경우는 숫자가 아닌 문자를 찾는다.
	   만약에 숫자를 찾게 되는 경우 아무런 숫자가 안뜰것이다.
	   */
	while(target != NULL){
		if(index_char == target->data) 
			break;
		target = target->next_pointer;
	}
	return target;
}//특정 index_char를 target의 뒷부분부터 찾는 함수 

void Display(pointer *list){
	node_info *curr = list->head;
	printf("\n=====Display Node=====\n");
	while(curr != NULL){
		if(curr->data >= 0 && curr->data <= 9)
			printf("%d",curr->data); 
		else
			printf("%c",curr->data);
		curr=curr->next_pointer;
	}
	printf("\n=====Display terminated=====\n");
}//linked list를 display하는 기능

void setNode(pointer *target){
	node_info *curr = target->head;
	if(curr->data >= 0 && curr->data <= 9){
		node_info *new_node = malloc(sizeof(node_info));
		new_node -> data = 'P';
		new_node -> next_pointer = curr;
		new_node -> prev_pointer = curr->prev_pointer;
		curr -> prev_pointer = new_node;
		curr = curr->next_pointer;
		target->head = target->head->prev_pointer;
	}else if(curr->data == '-'){
		curr->data = 'N';
	}
	
	/*
	   처음 시작했을 경우에 +인 경우를 위한 처리
	   */
	while(curr !=NULL){
		if(curr->data == '+'){
			if(curr->next_pointer->next_pointer->data >=0 && curr->next_pointer->next_pointer->data <=9){
				curr = curr->next_pointer;
				node_info *new_node = malloc(sizeof(node_info));
				/*
				   연산자 및 피연산자 사이는 무조건 스페이스바로 되어있나?
				   예시2) 123 + 540 - ( 342)	||	123 + 540 - (354)
				   */
				new_node -> data = 'P';
				new_node -> next_pointer = curr->next_pointer;
				new_node -> prev_pointer = curr;
				curr -> next_pointer -> prev_pointer = new_node;
				curr -> next_pointer = new_node;
			}
		}
		
		if(curr->data == '-'){
			if(curr->prev_pointer->prev_pointer->data < 0 || curr->prev_pointer->prev_pointer->data > 9){
				curr->prev_pointer->prev_pointer->next_pointer = curr;
				curr->prev_pointer = curr->prev_pointer->prev_pointer;
				curr->next_pointer->next_pointer->prev_pointer =curr;
				curr->next_pointer = curr->next_pointer->next_pointer;
				curr->data = 'N';
			}else if(curr->next_pointer->next_pointer->data >= 0 && curr->next_pointer->next_pointer ->data<=9){
				curr = curr ->next_pointer;
				node_info *new_node2 = malloc(sizeof(node_info));
				new_node2 -> data = 'P';
				new_node2 ->next_pointer = curr ->next_pointer;
				new_node2 ->prev_pointer = curr;
				curr -> next_pointer ->prev_pointer = new_node2;
				curr -> next_pointer = new_node2;
			}
		}
		
		curr = curr->next_pointer;
	}
}//피연산자와 연산자를 구별하는 함수

void setSpace(pointer *target){
	node_info *curr = target->head;
	while(curr !=NULL){
		if(curr->data == '+' || curr->data == '-' || curr-> data == '*'){
			if(curr->prev_pointer->data != ' '){
				node_info *new_node = malloc(sizeof(node_info));
				new_node->data = ' ';
				new_node->next_pointer = curr;
				new_node->prev_pointer = curr->prev_pointer;
				curr->prev_pointer->next_pointer = new_node;
				curr->prev_pointer = new_node;
			}
			if(curr->next_pointer->data != ' '){
				node_info *new_node_next = malloc(sizeof(node_info));
				new_node_next->data = ' ';
				new_node_next->next_pointer = curr->next_pointer;
				new_node_next->prev_pointer = curr;
				curr->next_pointer->prev_pointer = new_node_next;
				curr->next_pointer = new_node_next;
			}
		}
		curr = curr ->next_pointer;

	}
}//space bar를 넣는 부분

node_info *setCurr(pointer *target){
	node_info *curr = malloc(sizeof(node_info));
	curr = target->head;
	return curr;
}//head로 돌리는 부분

void delNode(node_info *target){
	target->prev_pointer->next_pointer = target->next_pointer;
	target->next_pointer->prev_pointer = target->prev_pointer;
}//target을 지우는 함수 

//연산자의 우선순위 반환 함수 prec
int prec(char op) {
	switch(op) {
		case'(':case')': return 0;
		case'+':case'-': return 1;
		case'*': return 2;
	}
	return -1;
}

void infix_to_postfix(pointer *L3, node_info *curr, node_info *curr_3) {

	int i = 0;
	char top_op;
	Stack s;
	init_stack(&s);
	while(curr != NULL) {
        printf("switch loop\n");
		switch(curr->data) {
			case'+':case'-':case'*':
				while(!is_empty(&s) && (prec(curr->data) <= prec(Peek(&s)))) {
					insert_node(L3, Pop(&s));
				}
                printf("+-*\n");
				Push(&s, curr->data);
				break;
			case'(':
                printf("(\n");
				Push(&s, curr->data);
				break;
			case')': //왼쪽 괄호를 만날 때 까지 출력.
                printf(")\n");
				top_op = Pop(&s);
				while(top_op != '(') {
					insert_node(L3, Pop(&s));
				}
				break;
			default: // 피연산자를 만나면 node insert
                printf("default\n");
				insert_node(L3, curr->data);
				break;
		}
		while (!is_empty(&s)) {
			insert_node(L3, Pop(&s)); //마지막에 스택에 있는 연산자들 insert.
		}
        Display(L3);
		curr = curr->next_pointer;
	}
}

int main(int argc,char* argv[]){
	char data;
	FILE *fp=fopen(argv[1],"r");
	pointer *L = (pointer *)malloc(sizeof(pointer));
	L->head = NULL;
	L->tail = NULL;

    pointer *L3 = (pointer *)malloc(sizeof(pointer));
    L3->head = NULL;
    L3->tail = NULL;
	
	while(fscanf(fp,"%c",&data)!=EOF){
		if(data >= '0' && data <= '9'){
			/*
			   숫자 - int로의 형변환
			   */
			insert_node(L,atoi(&data));
		}
		else if(data == '.'|| data == '+' || data == '-' || data == ')'|| data == '('){
			/*
			   char - 그대로 유지
   				*/
			insert_node(L,data);
		}
		else continue; // 잘못된 입력 예외처리
	}
	fclose(fp);
	setSpace(L);
	setNode(L);
	Display(L);
	node_info *curr;
	curr = setCurr(L);

    node_info *curr_3;
    curr_3 = setCurr(L3);
    infix_to_postfix(L3, curr, curr_3);
    curr_3 = setCurr(L3);
    Display(L3);
    
	//예제 1
	/*
	curr =setCurr(L);
	while(curr != NULL || curr != test){
		if(curr == test) {
			break;
		}
		if(curr->data>=0 && curr->data <= 9) 
			printf("%d",curr->data);
		else
			printf("%c",curr->data);
		curr = curr ->next_pointer;
	}
	*/
	/*
	//예제 2
	curr = setCurr(L);
	while(test != NULL){
		printf("%c",test->data);
		test = test-> next_pointer;
	}
	*/
	//예제 3/
	/*
	Display(L);
	delNode(test);
	curr = setCurr(L);
	Display(L);
	*/
	//예제 4
	/*
	curr = setCurr(L);
	node_info *test= getNode(curr,'.');
	delNode(test);
	Display(L);
	*/
	//예제 5
	/*
	Display(L);
	curr = setCurr(L);
	node_info *test = getNode(curr,1);
	insert_prev_node(test,1);
//	insert_next_node(test,'.');
	*/
	/*
		test = getNode(curr,'1'); ->Error뜰것입니다.
		insert_~_node(test,'1'); string이 들어갈 것입니다.
		이 두 예시를 주의해서 작성하세요.
	*/
	//예제 6 - insert_head_node
	/*Display(L);
	curr = setCurr(L);
	insert_head_node(L,'T');
	Display(L);
	

	Display(L);
    */

	curr = setCurr(L);
	while(curr != NULL){
		node_info *next = curr->next_pointer;
		free(curr);
		curr = next;
	}//초기화하는 부분
	
    curr_3 = setCurr(L3);
    while(curr_3 != NULL) {
        node_info *next_3 = curr_3->next_pointer;
        free(curr_3);
        curr_3 = next_3;
    }

	free(L);

    free(L3);
	
	return 0;

	/*
	   주석이 많으면 오히려 가독성이 떨어진다.
	   이거에 대해 논의 해야 한다.
	   */


 }
