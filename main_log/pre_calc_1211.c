#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef char element;
typedef struct pointer {
    struct node_info *head;
    struct node_info *tail;
} pointer;

typedef struct node_info {
    element data;
    struct node_info *next_pointer;
    struct node_info *prev_pointer;
} node_info;

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Stack {
    Node *top;
} Stack;

bool flag = 0;

void insert_node(pointer *target,int data){
    node_info *new_node = malloc(sizeof(node_info));
    new_node -> next_pointer = NULL;
    new_node -> prev_pointer = NULL;
    new_node -> data = data;
    if(data != ' '){
        if(target->head == NULL)
            target->head = target->tail = new_node;
        else{
            target->tail-> next_pointer = new_node;
            new_node->prev_pointer = target->tail;
            target->tail = new_node;
        }
    }
}//target의 tail에 inster 하는 것

void insert_next_node(node_info *target, int data) {
    node_info *new_node = malloc(sizeof(node_info));
    new_node->data = data;
    new_node->prev_pointer = target;
    if(target->next_pointer == NULL){ //예외처리 추가
        target->next_pointer = new_node;
        new_node->next_pointer = NULL;
        target = target->next_pointer;
    }
    else {
        new_node->next_pointer = target->next_pointer;
        target->next_pointer->prev_pointer = new_node;
        target->next_pointer = new_node;
    }
}// target의 뒷부분에 data를 넣는 부분

void insert_prev_node(node_info *target, int data) {
    node_info *new_node = malloc(sizeof(node_info));
    new_node->data = data;
    new_node->next_pointer = target;
    new_node->prev_pointer = target->prev_pointer;
    target->prev_pointer->next_pointer = new_node;
    target->prev_pointer = new_node;
}// target의 앞부분에 data를 넣는 부분

void insert_head_node(pointer *target, int data) {
    node_info *curr = target->head;
    node_info *new_node = malloc(sizeof(node_info));
    new_node->data = data;
    new_node->next_pointer = curr;
//    new_node->prev_pointer = curr->prev_pointer;
    new_node->prev_pointer = NULL;
    curr->prev_pointer = new_node;
    target->head = target->head->prev_pointer;
}//head에 insert하는 부분 --수정

void insert_tail_node(pointer *target, int data) {
    node_info *curr = target->tail;
    node_info *new_node = malloc(sizeof(node_info));
    new_node->data = data;
    new_node->prev_pointer = curr;
    new_node->next_pointer = NULL;
    curr->next_pointer = new_node;
    target->tail = target->tail->next_pointer;
}//tail에 insert하는 부분 -- 추가

void Display(pointer *list) {
    node_info *curr = list->head;
    printf("\n=====Display Node=====\n");
    while (curr != NULL) {
        if (curr->data >= -18 && curr->data <= 18)
            printf("%d", curr->data);
        else
            printf("%c", curr->data);
        curr = curr->next_pointer;
    }
    printf("\n=====Display terminated=====\n");
}//linked list를 display하는 기능 // -- 음수때문에 잠시 변경 -- 잠시변경

void setHead(pointer *target){
    while(target->head != NULL) {
        if (target->head->prev_pointer == NULL) {
            break;
        }
        target->head = target->head->prev_pointer;
    }
}// -- 추가함

void setTail(pointer *target){
    while(target->tail != NULL){
        if (target->tail->next_pointer == NULL){
            break;
        }
        target->tail = target->tail->next_pointer;
    }
}// -- 추가함

node_info *setCurr(pointer *target) {
    node_info *curr = malloc(sizeof(node_info));
    curr = target->head;
    return curr;
}//head로 돌리는 부분

void delNode(node_info *target) {
    if (target->prev_pointer == NULL) {
        target->data = target->next_pointer->data;
        if(target->next_pointer->next_pointer == NULL){ //예외처리 추가
            target->next_pointer = NULL;
        }
        else {
            target->next_pointer = target->next_pointer->next_pointer;
            target->next_pointer->prev_pointer = target;
        }
    }
    else if(target->next_pointer == NULL){
        target->data = target->prev_pointer->data;
        target->prev_pointer->prev_pointer->next_pointer = target;
        target->prev_pointer = target->prev_pointer->prev_pointer;
    }

    else {
        target->prev_pointer->next_pointer = target->next_pointer;
        target->next_pointer->prev_pointer = target->prev_pointer;
    }
}//target을 지우는 함수 -- 변경

void init_stack(Stack *stack) {
    stack->top = NULL;
}

int is_empty(Stack *stack) {
    return (stack->top == NULL);
}

void Push(Stack *stack, int data) {
    Node *now = (Node *) malloc(sizeof(Node));
    now->data = data;
    now->next = stack->top;
    stack->top = now;
}

int Pop(Stack *stack) {
    Node *now;
    int re;

    if (is_empty(stack)) {
        fprintf(stderr, "Stack Empty_Pop\n");
        exit(1);
    }

    now = stack->top;
    re = now->data;
    stack->top = now->next;
    free(now);
    return re;
}

int Peek(Stack *stack) {
    if (is_empty(stack)) {
        fprintf(stderr, "Stack Empty_Peek\n");
        exit(1);
    }
    return stack->top->data;
}

int prec(char op){
	switch(op){
		case'(': return 1;
		case'+':case'-': return 2;
		case'*': return 3;
	}
	return -1;
}

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
        curr->next_pointer = curr->next_pointer->next_pointer;
    }

    /*
       처음 시작했을 경우에 +인 경우를 위한 처리
       */
    while(curr !=NULL){
        if(curr->data == '-'){
            if(curr->prev_pointer->prev_pointer->data == '*' || curr->prev_pointer->prev_pointer->data == '('){
                curr->data = 'N';
                curr->next_pointer = curr->next_pointer->next_pointer;
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
        if(curr->data == '+' || curr-> data == '*' || curr->data == '('){
            if(curr->next_pointer->next_pointer->data != '-' && \
                    curr->next_pointer->next_pointer->data != '('){
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
        if(curr->data == '+' || curr->data == '-' || curr-> data == '*' || curr->data == '(' ||curr->data == ')'||curr->data == 'N'||curr->data == 'P'){
            if((curr != target->head)&&curr->prev_pointer->data != ' '){
                node_info *new_node = malloc(sizeof(node_info));
                new_node->data = ' ';
                new_node->next_pointer = curr;
                new_node->prev_pointer = curr->prev_pointer;
                curr->prev_pointer->next_pointer = new_node;
                curr->prev_pointer = new_node;
            }
        }
        if(curr->data == '+' || curr->data == '-' || curr-> data == '*' || curr->data == '(' ||curr->data == ')'){
            if((curr != target->tail) && curr->next_pointer->data != ' '){
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

void infix_to_postfix(pointer *L3, node_info *curr, node_info *curr_3) {

    int i = 0;
    char top_op;
    Stack s;
    init_stack(&s);
    while(curr != NULL) {
		if(curr->data != '+'&&curr->data != '-'&&curr->data != '*'&&curr->data != '('&&curr->data     != ')'){
			insert_node(L3,curr->data);
		}

        switch(curr->data) {
            case'+':case'-':case'*':
                while(!is_empty(&s)&& prec(curr->data) <= prec(Peek(&s))&&(Peek(&s)!='(')){
                    insert_node(L3, Pop(&s));
				}
                Push(&s, curr->data);
                curr = curr->next_pointer;
                break;
            case'(':
                Push(&s, curr->data);
                curr = curr->next_pointer;
                break;
            case')': //왼쪽 괄호를 만날 때 까지 출력.
                while((top_op=Pop(&s)) != '(') {
                    insert_node(L3, top_op);
                }
                break;
        }
        curr = curr->next_pointer;
    }
    while (!is_empty(&s)) {
        insert_node(L3, Pop(&s)); //마지막에 스택에 있는 연산자들 insert.
    }
}

int main(int argc, char *argv[]) {
    char data;
	FILE *fp = fopen(argv[1],"r");

    pointer *L = (pointer *) malloc(sizeof(pointer));
    L->head = NULL;
    L->tail = NULL;

    pointer *L3 = (pointer *)malloc(sizeof(pointer));
    L3->head = NULL;
    L3->tail = NULL;

    pointer *L2 = (pointer *)malloc(sizeof(pointer));
    L2->head = NULL;
    L2->tail = NULL;

    while(fscanf(fp,"%c",&data)!=EOF){
        if(data >= '0' && data <= '9'){
            /*
               숫자 - int로의 형변환
               */
            insert_node(L,atoi(&data));
        }
        else if(data == '.'|| data == '+' || data == '-' || data == ')'|| data == '(' ||data == '*'){            /*
               char - 그대로 유지
                */
            insert_node(L,data);
        }
        else continue; // 잘못된 입력 예외처리
    }
    fclose(fp);
    node_info *curr;
    curr = setCurr(L);
    setSpace(L);
    setNode(L);
	Display(L);
	node_info *curr_3;
    curr_3 = setCurr(L3);
    curr = setCurr(L);
    infix_to_postfix(L3, curr, curr_3);
    setSpace(L3);
	insert_next_node(L3->tail,' ');
    Display(L3);
	
	I_Calculator(L3);
	
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
}
