typedef struct {
  int data;
  struct Node *next;
} Node;

typedef struct {
  Node *top;
}StackType;

void init(StackType *s) {
  stack->top = NULL;
}

int is_empty(StackType *s) {
  return s->top == NULL;
}

void push(StackType *s, int data) {
  Node *now = (Node *)malloc(sizeof(Node));
  now->data = data;
  now->next = stack->top;
  stack->top = now;
}

int pop(StackType *s) {
  Node *now;
  int re;
  if(is_empty(s)) {
    return 0;
  }
  now = s->top;
  re = now->data;

  stack->top = now->next;
  free(now);
  return re;
}
