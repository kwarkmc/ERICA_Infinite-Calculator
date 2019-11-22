#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
   (,) 예외처리 추가
   Display 구현
   strtok(?)을 이용하는 방법 예제 추가
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
}node_info;

//Stack 함수 시작

typedef struct Node{
    int data;
    struct Node *next;
} Node;

typedef struct Stack {
    Node *top;
} Stack;

void init_stack(Stack *stack) {
    stack->top = NULL; // top을 NULL 로 설정
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
		fprintf(stderr, "Stack Empty\n");
		exit(1);
	}
	
	return stack->top->data;


}

//Stack 함수 끝

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
}
node_info* getNode(node_info *target,char index_char){
	while(target != NULL){
		if(index_char == target->data) break;
		target = target->next_pointer;
	}
	return target;
}
void Display(node_info *node){
	while(node != NULL){
		printf("%c",node->data);
		node=node->next_pointer;
	}
}

int prec(char op) {
		switch (test->prev_pointer) {
			case'(':case')': return 0;
			case'+':case'-': return 1;
			case'*': return 2;
		}
		return -1;
	}

	/*연산자의 우선순위를 반환.*/

	void infix_to_postfix(node_info *test) {
		int i = 0;
		char top_op;

		Stack s;
		init_stack(&s);

		//Linked-List Stack 설정

		switch(*(test->prev_pointer)) { // !issue, 포인터 관련 표현 질문
			case'+':case'-':case'*':
				while(!is_empty(&s) && (prec(test->prev_pointer) <= prec(peek(&s)))) {
					//스택에 있는 연산자의 우선순위가 더 크거나 같으면 출력 -> 출력방법
					Push(&s, test->prev_pointer);
					break;
				}
			case'(':
				Push(&s, test->prev_pointer);
				break;
			case')':
				top_op = Pop(&s);
				while (top_op != '(') {
					//왼쪽 괄호를 만날 때 까지 출력
					top_op = Pop(&s);
				}
				break;
			default:
				//피연산자를 만나면 출력
				break;
		}

		while (!is_empty(&s)) {
			//스택에 있는 연산자들 출력. pop
		}
		

	}

int main(int argc,char* argv[]){
	char data;

	FILE *fp=fopen(argv[1],"r");
	pointer *L = (pointer *)malloc(sizeof(pointer));
	L->head = NULL;
	L->tail = NULL;

	//받아온 파일의 Linked-List

	pointer *L_Stack = (pointer *)malloc(sizeof(pointer));
	L_Stack->head = NULL;
	L_Stack->tail = NULL;

	//Postfix 처리를 끝낸 식을 넣는 Linked-List.
	
	while(fscanf(fp,"%c",&data)!=EOF){
		if((data >= '1' && data <= '9')|| data == '.'|| data == '+' || data == '-' || data == ' ' || data == ')'|| data == '('){
			insert_node(L,data);
		}
		else continue; // 잘못된 입력 예외처리
	}
	fclose(fp);
	
	node_info *curr = L->head; 
	Display(curr);
	/* Display 구현*/

	curr = L->head;
	node_info *test= getNode(curr,' ');
	test = getNode(curr,' ');
	/* 이것을 이용해서 스페이스 바를 기준으로 나눌 수 있다.*/
	printf("\n");

	//예제 1
	curr = L->head;
	while(curr != NULL || curr != test){
		if(curr == test) {
			printf("\n같은 지점\n");
			break;
		}

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
	/*
	   위와 같이 pointer를 나눌 수 있다.
	   이거를 이용해야 할 듯 하다.
	   */
	curr = L->head;
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
