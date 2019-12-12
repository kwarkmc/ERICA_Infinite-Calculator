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


void Preprocess_Add(pointer *L1, pointer *L2, int *fd1, int *bd1, int *fd2, int *bd2) { //점앞뒤로 점 개수 찾기
    int have_dot_1 = 0;
    int have_dot_2 = 0;
    setHead(L1);
    setHead(L2);
    while (L1 != NULL) {
        if (L1->head->next_pointer == NULL) {
            *fd1 += 1;
            break;
        }
        if (L1->head->data == '.') {
            have_dot_1 = 1;
            break;
        }
        *fd1 += 1;
        L1->head = L1->head->next_pointer;
    }

    while (L2 != NULL) {
        if (L2->head->next_pointer == NULL) {
            *fd2 += 1;
            break;
        }
        if (L2->head->data == '.') {
            have_dot_2 = 1;
            break;
        }
        *fd2 += 1;
        L2->head = L2->head->next_pointer;

    }


    if (have_dot_1 == 1) {
        L1->head = L1->head->next_pointer;
        while (L1->head != NULL) {
            if(L1->head->next_pointer == NULL){
                *bd1 += 1;
                break;
            }
            *bd1 += 1;
            L1->head = L1->head->next_pointer;
        }
    }

    if (have_dot_2 == 1) {
        L2->head = L2->head->next_pointer;
        while (L2->head != NULL) {
            if(L2->head->next_pointer == NULL){
                *bd2 += 1;
                break;
            }
            *bd2 += 1;
            L2->head = L2->head->next_pointer;
        }
    }
}

void Add(pointer *L1, pointer *L2, int *fd1, int *bd1, int *fd2, int *bd2) {//노드끼리 자리수 맞추고 더하기
    int K = *fd1 - *fd2;
    int J = *bd1 - *bd2;
    setHead(L1);
    setHead(L2);

    if (K < 0) {
        for (int i = 0; i < abs(K); i++) {
            insert_head_node(L1, 0);
        }
    }

    if (K > 0) {
        for (int i = 0; i < K; i++) {
            insert_head_node(L2, 0);
        }
    }

    if (J < 0) {
        if (*bd1 == 0) {
            while(L1->head != NULL){
                if(L1->head->next_pointer == NULL){
                    break;
                }
                L1->head = L1->head->next_pointer;
            }
            insert_next_node(L1->head, '.');
            L1->head = L1->head->next_pointer;
            for (int j = 0; j < abs(J); j++) {
                insert_next_node(L1->head, 0);
                L1->head = L1->head->next_pointer;
            }
        }
        else {
            while(L1->head != NULL){
                if(L1->head->next_pointer == NULL){
                    break;
                }
                L1->head = L1->head->next_pointer;
            }
            for (int i = 0; i < abs(J); i++) {
                insert_next_node(L1->head, 0);
            }
        }
    }

    if (J > 0) {
        if (*bd2 == 0) {
            while(L2->head != NULL){
                if(L2->head->next_pointer == NULL){
                    break;
                }
                L2->head = L2->head->next_pointer;
            }
            insert_next_node(L2->head, '.');
            L2->head = L2->head->next_pointer;
            for (int j = 0; j < J; j++) {
                insert_next_node(L2->head, 0);
                L2->head = L2->head->next_pointer;
            }
        }
        else {
            while(L2->head != NULL){
                if(L2->head->next_pointer == NULL){
                    break;
                }
                L2->head = L2->head->next_pointer;
            }
            for (int i = 0; i < J; i++) {
                insert_next_node(L2->head, 0);
            }
        }
    }

    setHead(L1);
    setHead(L2);
    while (L1->head != NULL) {
        if(L1->head->next_pointer == NULL){
            L1->head->data = L1->head->data + L2->head->data;
            break;
        }
        if (L1->head->data != '.') {
            L1->head->data = L1->head->data + L2->head->data;
        }
        L1->head = L1->head->next_pointer;
        L2->head = L2->head->next_pointer;
    }
    setHead(L1);
}

void Convert_Zero(pointer *L1) { // 앞뒤 0제거
    setHead(L1);
    if(L1->head->data == 0 && L1->head->next_pointer == NULL){
        return;
    }
    int have_dot = 0;
    while (L1->head->data == 0) { // 앞에서부터 0제거
        if (L1->head->next_pointer->data == '.') {
            break;
        } else {
            delNode(L1->head);
        }
    }
    while (L1->head != NULL) { //점찾기
        if (L1->head->next_pointer == NULL) {
            break;
        }
        if (L1->head->data == '.') {
            have_dot = 1;
            break;
        }
        L1->head = L1->head->next_pointer;
    }
    if (have_dot == 1) {
        setTail(L1);
        while (L1->tail->data == 0) { //뒤부터 0지우기
            if(L1->tail->prev_pointer->data == '.'){
                break;
            }
            delNode(L1->tail);
        }
    }
    setTail(L1);
    if(L1->tail->data == 0 && L1->tail->prev_pointer->data =='.'){
        delNode(L1->tail);
        delNode(L1->tail);
    }

}

void Convert_Number(pointer *L1,int *Its_P, int *Its_N) { //시작값이 양수인지 음수인지 구별하고 PN저장,변환후 자리수정리
    setHead(L1);
    while (L1->head != NULL) { //시작값이 양수인지 음수인지 판별
        if (L1->head->data > 0 && L1->head->data < 19) {
            *Its_P = 1;
            break;
        } else if (L1->head->data < 0 && L1->head->data > -19) {
            *Its_N = 1;
            break;
        } else { //0인경우
            if(L1->head->data == 0 && L1->head->next_pointer == NULL){
                *Its_P = 1;
                break;
            }
            else {
                L1->head = L1->head->next_pointer;
            }
        }
    }

    if (*Its_N == 1) { //앞자리가 음수인경우
        while (L1->head != NULL) { // 마지막 노드로 이동 하면서 -로 값 바꾸기
            if (L1->head->next_pointer == NULL) {
                L1->head->data *= (-1);
                break;
            }
            else if (L1->head->next_pointer->data == '.') {
                L1->head->data *= (-1);
                L1->head = L1->head->next_pointer->next_pointer;
            }
            else {
                L1->head->data *= (-1);
                L1->head = L1->head->next_pointer;
            }
        }
    }

    setHead(L1);
    while (L1->tail != NULL) { // 값변환
        if (L1->tail->data < 0) {
            L1->tail->data += 10;
            if(L1->tail->prev_pointer == NULL){
                insert_head_node(L1, 1);
                break;
            }
            else if (L1->tail->prev_pointer->data == '.') {
                L1->tail->prev_pointer->prev_pointer->data -= 1;
                L1->tail = L1->tail->prev_pointer->prev_pointer;
            }
            else {
                L1->tail->prev_pointer->data -= 1;
                L1->tail = L1->tail->prev_pointer;
            }
        }
        else if (L1->tail->data >= 10 && L1->tail->data < 19) {
            L1->tail->data -= 10;
            if(L1->tail->prev_pointer == NULL){
                insert_head_node(L1, 1);
                break;
            }
            else if (L1->tail->prev_pointer->data == '.') {
                L1->tail->prev_pointer->prev_pointer->data += 1;
                L1->tail = L1->tail->prev_pointer->prev_pointer;
            }
            else {
                L1->tail->prev_pointer->data += 1;
                L1->tail = L1->tail->prev_pointer;
            }
        }
        else {
            if(L1->tail->prev_pointer == NULL){
                break;
            }
            if (L1->tail->prev_pointer->data == '.') {
                L1->tail = L1->tail->prev_pointer->prev_pointer;
            }
            else {
                L1->tail = L1->tail->prev_pointer;
            }
        }
    }
}

void Preprocess_Multiply(pointer *L1, pointer *L2, int *node_num, int *decimal_place) {
    while (L1->head != NULL) {//'.'노드를 제거하면서 전체노드수와 소수점노드수 세기
        if (L1->head->data != '.') {
            *node_num += 1;
            if(L1->head->next_pointer == NULL){
                break;
            }
        }
        else {
            delNode(L1->head);
            L1->head = L1->head->next_pointer;
            while (L1->head->next_pointer != NULL) {
                *node_num += 1;
                *decimal_place += 1;
                L1->head = L1->head->next_pointer;
            }
            if(L1->head->next_pointer == NULL){
                *node_num += 1;
                *decimal_place += 1;
                break;
            }
        }
        L1->head = L1->head->next_pointer;
    }
    while (L2->head != NULL) {//'.'노드를 제거하면서 전체노드수와 소수점노드수 세기
        if (L2->head->data != '.') {
            *node_num += 1;
            if (L2->head->next_pointer == NULL) {
                break;
            }
        } else {
            delNode(L2->head);
            L2->head = L2->head->next_pointer;
            while (L2->head->next_pointer != NULL) {
                *node_num += 1;
                *decimal_place += 1;
                L2->head = L2->head->next_pointer;
            }
            if (L2->head->next_pointer == NULL) {
                *node_num += 1;
                *decimal_place += 1;
                break;
            }
        }
        L2->head = L2->head->next_pointer;
    }
}

void Multiply(pointer *L1, pointer *L2, pointer *L5, int *node_num, int *decimal_place) {
    for (int i = 0; i < *node_num; i++) {
        insert_node(L5, 0);
    }
    setTail(L5); //포인터 tail로 초기화(L1,L2,L5)
    int k = 0;
    while(L1->head != NULL){
        if(L1->head->next_pointer == NULL){
            break;
        }
        L1->head = L1->head->next_pointer;
    }
    while(L2->head != NULL){
        if(L2->head->next_pointer == NULL){
            break;
        }
        L2->head = L2->head->next_pointer;
    }
    while (L2->head != NULL) {
        while (L1->head != NULL) {
            if(L1->head->prev_pointer == NULL){
                L5->tail->data += ((L1->head->data) * (L2->head->data));
                break;
            }
            L5->tail->data += ((L1->head->data) * (L2->head->data));
            L5->tail = L5->tail->prev_pointer;
            L1->head = L1->head->prev_pointer;
        }
        k++;
        //여기서 multiply convert_num처리 필요
        while(L1->head != NULL){
            if(L1->head->next_pointer == NULL){
                break;
            }
            L1->head = L1->head->next_pointer;
        }
        L2->head = L2->head->prev_pointer;
        setTail(L5);
        for (int i = 0; i < k; i++) {
            L5->tail = L5->tail->prev_pointer;
        }
    }
    setTail(L5);
    while (L5->tail->prev_pointer != NULL) { //1의자리로 모두 변환
        if (L5->tail->data >= 10) {
            L5->tail->prev_pointer->data += (L5->tail->data) / 10;
            L5->tail->data -= ((L5->tail->data) / 10) * 10;
        }
        L5->tail = L5->tail->prev_pointer;
    }
    setHead(L5);
    while (L5->head->next_pointer != NULL) { //앞에 0제거
        if (L5->head->data == 0) {
            delNode(L5->head);
        } else {
            break;
        }
    }
    setTail(L5);
    for (int i = 0; i < *decimal_place; i++) {
        L5->tail = L5->tail->prev_pointer;
    }
    if(*decimal_place > 0) {
        insert_next_node(L5->tail, '.');
    }
}

void I_Calculator(pointer *L) {
    int sub = 0;
    int m_p = 0;
    int m_n = 0;
    Stack Num;
    init_stack(&Num);
    while (L->head != NULL) {
        if(L->head->next_pointer == NULL){
            break;
        }
        if ((L->head->data == '+') || (L->head->data == '-')) { // 덧셈과 뺄셈
            if(L->head->data == '-'){
                sub = 1;
            }
            if(L->head->data == '+'){
                sub = 0;
            }
            Pop(&Num);
            pointer *L2 = (pointer *) malloc(sizeof(pointer));
            L2->head = NULL;
            L2->tail = NULL;
            insert_node(L2, Pop(&Num));
            while(L2->head->data != 'P'){
                if(L2->head->data == 'N'){
                    break;
                }
                insert_head_node(L2, Pop(&Num));
            }
            Pop(&Num);
            pointer *L1 = (pointer *) malloc(sizeof(pointer));
            L1->head = NULL;
            L1->tail = NULL;
            insert_node(L1, Pop(&Num));
            while(L1->head->data != 'P'){
                if(L1->head->data == 'N'){
                    break;
                }
                if(is_empty(&Num) == 1){
                    break;
                }
                insert_head_node(L1, Pop(&Num));
            }

            if(L1->head->data == 'N'){
                delNode(L1->head);
                while(L1->head != NULL){
                    if(L1->head->data == '.'){
                        L1->head = L1->head->next_pointer;
                    }
                    if(L1->head->next_pointer == NULL){
                        L1->head->data *= (-1);
                        break;
                    }
                    if(L1->head->data != '.'){
                        L1->head->data *= (-1);
                        L1->head = L1->head->next_pointer;
                    }

                }
                setHead(L1);
            }
            if(L1->head->data == 'P'){
                delNode(L1->head);
            }
            if(sub == 0){
                if(L2->head->data == 'N'){
                    delNode(L2->head);
                    while(L2->head != NULL){
                        if(L2->head->data == '.'){
                            L2->head = L2->head->next_pointer;
                        }
                        if(L2->head->next_pointer == NULL){
                            L2->head->data *= (-1);
                            break;
                        }

                        if(L2->head->data != '.'){
                            L2->head->data *= (-1);
                            L2->head = L2->head->next_pointer;
                        }

                    }
                    setHead(L2);
                }
                if(L2->head->data == 'P'){
                    delNode(L2->head);
                }
            }
            if(sub == 1){
                if(L2->head->data == 'P'){
                    delNode(L2->head);
                    while(L2->head != NULL){
                        if(L2->head->data == '.'){
                            L2->head = L2->head->next_pointer;
                        }
                        if(L2->head->next_pointer == NULL){
                            L2->head->data *= (-1);
                            break;
                        }
                        if(L2->head->data != '.'){
                            L2->head->data *= (-1);
                            L2->head = L2->head->next_pointer;
                        }
                    }
                    setHead(L2);
                }
                if(L2->head->data == 'N'){
                    delNode(L2->head);
                }
            }
            int fd1=0, bd1=0, fd2=0, bd2=0;
            Preprocess_Add(L1,L2,&fd1,&bd1,&fd2,&bd2);
            Add(L1,L2,&fd1,&bd1,&fd2,&bd2);
            Convert_Zero(L1);

            setHead(L1);
            int Its_P = 0, Its_N = 0;
            Convert_Number(L1,&Its_P,&Its_N);

            Convert_Zero(L1);
            setHead(L1);

            if(Its_P == 1){
                insert_head_node(L1,'P');
            }
            if(Its_N == 1){
                insert_head_node(L1,'N');
            }
            while(L1->head != NULL){
                if(L1->head->next_pointer == NULL){
                    Push(&Num, L1->head->data);
                    break;
                }
                else {
                    Push(&Num, L1->head->data);
                    L1->head = L1->head->next_pointer;
                }
            }
            free(L1);
            free(L2);
            L->head = L->head->next_pointer;
        }

        else if (L->head->data == '*'){ // 곱셈
            Pop(&Num);
            pointer *L2 = (pointer *) malloc(sizeof(pointer));
            L2->head = NULL;
            L2->tail = NULL;
            insert_node(L2, Pop(&Num));
            while(L2->head->data != 'P') {
                if(L2->head->data == 'N') {
                    break;
                }
                insert_head_node(L2, Pop(&Num));
            }
            Pop(&Num);
            pointer *L1 = (pointer *) malloc(sizeof(pointer));
            L1->head = NULL;
            L1->head = NULL;
            insert_node(L1,Pop(&Num));
            while(L1->head->data != 'P'){
                if(L1->head->data == 'N'){
                    break;
                }
                if(is_empty(&Num) == 1){
                    break;
                }
                insert_head_node(L1,Pop(&Num));
            }
            if(L1->head->data == 'P'){ //m_p,m_n 찾기 연산후 초기화0으로 해야함
                m_p +=1 ;
                delNode(L1->head);
            }
            if(L1->head->data == 'N'){
                m_n +=1 ;
                delNode(L1->head);
            }
            if(L2->head->data == 'P'){
                m_p +=1 ;
                delNode(L2->head);
            }
            if(L2->head->data == 'N'){
                m_n +=1 ;
                delNode(L2->head);
            }

            int node_num = 0, decimal_place = 0; // 전체노드개수와 점노드수 초기화
            Preprocess_Multiply(L1,L2,&node_num,&decimal_place);
            setHead(L1);
            setHead(L2);
            pointer *L5 = (pointer *) malloc(sizeof(pointer));
            L5->head = NULL;
            L5->tail = NULL;
            Multiply(L1,L2,L5,&node_num,&decimal_place);
            if((m_p == 1) && (m_n == 1)){
                insert_head_node(L5,'N');
            }
            if((m_p == 2 || m_n == 2)){
                insert_head_node(L5,'P');
            }
            while(L5->head != NULL){
                if(L5->head->next_pointer == NULL){
                    Push(&Num, L5->head->data);
                    break;
                }
                else {
                    Push(&Num, L5->head->data);
                    L5->head = L5->head->next_pointer;
                }
            }
            free(L1);
            free(L2);
            free(L5);
            L->head = L->head->next_pointer;

        }

        else {
            Push(&Num, L->head->data);
            L->head = L->head->next_pointer;
        }

    }
    Stack result;
    init_stack(&result);
    while (is_empty(&Num) != 1) {
        Push(&result, Pop(&Num));
    }
    while (is_empty(&result) != 1){
        int K = Pop(&result);
        if(K >= 0 && K <= 9)
            printf("%d", K);
        else if(K == 'P'){

        }
        else if(K == 'N'){
            printf("-");
        }
        else{
            printf("%c", K);
        }
    }
}

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

void ReverseNode(pointer *target){
	node_info *curr = target->tail;
	printf("Reverse");
	while(curr != NULL){
		if(curr->data >= 0 && curr->data <= 9)
			printf("%d",curr->data);
		else if(curr->data == 'P')
			printf("+");
		else if(curr->data == 'N')
			printf("-");
		else
			printf("%c",curr->data);
		curr = curr->prev_pointer;
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
