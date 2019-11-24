#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/*
   getNode 변경에 대한 주석
   형변환으로 인해 신경 써야하는 부분 주석
   피연산자와 연산자 간의 간격에 대한 논의(조교님한테 여쭤봐야함)
   형변환하는 부분
   형변환으로 인해 바뀐것에 대한 예시
   '-'일 경우와 '+'일 경우
   첫 시작이 '+'일 경]
	*/

typedef char element;
typedef struct pointer{
	struct node_info *head;
	struct node_info *tail;
}pointer;

typedef struct node_info{
	element data; 
	struct node_info* next_pointer;
	struct node_info* prev_pointer;
} node_info;

//Stack 구현

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

bool flag = 0;

void insert_node(pointer *target,int data) {
	node_info *new_node = malloc(sizeof(node_info));
	new_node -> next_pointer = NULL;
	new_node -> prev_pointer = NULL;
	new_node -> data = data;
	if (target->head == NULL)
		target->head = target->tail = new_node;
	else {
		target->tail-> next_pointer = new_node;
		new_node->prev_pointer = target->tail;
		target->tail = new_node; 
	}
}

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
}

void Display(node_info *node) {
	while(node != NULL){
		if(node->data >= 0 && node->data <= 9)
			printf("%d",node->data); 
		else
			printf("%c",node->data);
		/*
		   숫자의 경우 int형, 문자의 경우 char형으로 입력이 되었기 때문에, 이 두가지를 구별 해야한다.
		   예시 - 131번째줄
		   */
		node=node->next_pointer;
	}
}

void setNode(node_info *target) {
	if(target->data >= 0 && target->data <= 9){
		node_info *new_node = malloc(sizeof(node_info));
		new_node -> data = 'P';
		new_node -> next_pointer = target;
		new_node -> prev_pointer = target->prev_pointer;
		target -> prev_pointer = new_node;
		target = target->next_pointer;
		flag =1;
	} else if(target->data == '-'){
		target->data = 'N';
		target->next_pointer = target->next_pointer->next_pointer;
		target = target->next_pointer;
	}
	
	/*
	   처음 시작했을 경우에 +인 경우를 위한 처리
	   */
	while(target !=NULL) {
		if(target->data == '+') {
			if(target->next_pointer->next_pointer->data >=0 && target->next_pointer->next_pointer->data <=9){
				target = target->next_pointer;
				node_info *new_node = malloc(sizeof(node_info));
				/*
				   연산자 및 피연산자 사이는 무조건 스페이스바로 되어있나?
                   -> 네 피연산자를 제외한 모든 부분은 스페이스바로 구별되어 있습니다. + 괄호 '()' 도 연산자로 구별됩니다.
				   예시2) 123 + 540 - ( 342)	||	123 + 540 - (354)
				   */
				new_node -> data = 'P';
				new_node -> next_pointer = target->next_pointer;
				new_node -> prev_pointer = target;
				target -> next_pointer -> prev_pointer = new_node;
				target -> next_pointer = new_node;
			}
		}
		
		if(target->data == '-') {
			if(target->prev_pointer->prev_pointer->data < 0 || target->prev_pointer->prev_pointer->data > 9){
				target->data = 'N';
				target -> next_pointer = target->next_pointer->next_pointer;
			}
		}
		
		target = target->next_pointer;
	}
}

node_info *setCurr(pointer *target) {
	node_info *curr = malloc(sizeof(node_info));
	if(flag == 1)
		curr = target->head->prev_pointer;
	else
		curr = target->head;
	return curr;
}



int main(int argc,char* argv[]) {
	char data;
	FILE *fp=fopen(argv[1],"r");
	pointer *L = (pointer *)malloc(sizeof(pointer));
	L->head = NULL;
	L->tail = NULL;
	
	while(fscanf(fp,"%c",&data)!=EOF) {
		if(data >= '0' && data <= '9') {
			/*
			   숫자 - int로의 형변환
			   */
			insert_node(L,atoi(&data));
		}
		else if(data == '.'|| data == '+' || data == '-' || data == ' ' || data == ')'|| data == '(') {
			/*
			   char - 그대로 유지
   				*/
			insert_node(L,data);
		}
		else continue; // 잘못된 입력 예외처리
	}
	fclose(fp);
	
	node_info *curr = L->head; 
	setNode(curr);
	curr =setCurr(L);
	Display(curr);
	curr = setCurr(L);
	node_info *test= getNode(curr,' ');
	test = getNode(curr,' ');
	printf("\n");
	
	//예제 1
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
	/*
	//예제 2
	while(test != NULL){
		printf("%c",test->data);
		test = test-> next_pointer;
	}
	*/
	curr = setCurr(L);
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
