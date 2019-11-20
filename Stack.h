#define MAX_STACK_SIZE 100

typedef struct {
    int top;
    int stack[MAX_STACK_SIZE];
} StackType;

void init(StackType *s) {
    s->top = -1;
}

int is_empty (StackType *s) {
    return (s->top == -1);   
}

int is_full (StackType *s) {
    return (s->top == (MAX_STACK_SIZE-1));
}

void push(StackType *s, int item) {
    if(is_full(s)) {
        printf("Stack Full Error\n");
        exit(1);
    }
    else
    {
        s->stack[++(s->top)] = item;
    }
}

int pop (StackType *s) {
    if(is_empty(s)) {
        printf("Stack Empty Error\n");
    }
    else {
        return s->stack[(s->top)--];
    }
}

int peek (StackType *s) {
    if(is_empty(s)) {
        printf("Stack Empty Error\n");
    }
    else
    {
        return (s->stack[s->top]);
    }
}