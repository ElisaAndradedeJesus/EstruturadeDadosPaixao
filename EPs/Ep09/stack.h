#ifndef STACK_H
#define STACK_H

typedef struct stack Stack;
typedef struct stacknode StackNode;

Stack *s_create();

char s_pop(Stack *q);

char s_top(Stack *q);

void s_push(Stack *s, char v);

int s_is_empty(Stack *s);

void s_free(Stack *s);

void s_print(Stack *s);

#endif