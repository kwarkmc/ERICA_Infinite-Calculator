typedef struct {
  int data;
  struct Node *next;
} Node;

typedef struct {
  Node *top;
}StackType;

void init(StackType *s) {
  s->top = NULL;
}

int is_empty(StackType *s) {
  return s->top == NULL;
}

void push(StackType *s, int data) {
  Node *now = (Node *)malloc(sizeof(Node));
  now->data = data;
  now->next = s->top;
  s->top = now;
}

int pop(StackType *s) {
  Node *now;
  int re;
  if(is_empty(s)) {
    return 0;
  }
  now = s->top;
  re = now->data;

  s->top = now->next;
  free(now);
  return re;
}
