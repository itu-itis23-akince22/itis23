#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct Node
{
    void *dataPtr;
    struct Node *next;
} Node;
typedef struct Stack
{
    int count;
    Node *top;
} Stack;
Stack *createStack(void)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (stack)
    {
        stack->count = 0;
        stack->top = NULL;
    }
    return stack;
}
bool emptyStack(Stack *stack)
{
    return (stack->count == 0);
}
void *stackTop(Stack *stack)
{
    if (stack->count == 0)
        return NULL;
    return stack->top->dataPtr;
}
void *pop(Stack *stack)
{
    void *dataOutPtr = NULL;
    Node *temp;
    if (stack->count == 0)
        return dataOutPtr;
    temp = stack->top;
    stack->top = stack->top->next;
    dataOutPtr = temp->dataPtr;
    free(temp);
    stack->count--;
    return dataOutPtr;
}
bool push(Stack *stack, void *dataInPtr)
{
    // Local Definitions
    Node *newPtr;
    // Statements
    newPtr = (Node *)malloc(sizeof(Node));
    if (!newPtr)
        return false;
    newPtr->dataPtr = dataInPtr;
    newPtr->next = stack->top;
    stack->top = newPtr;
    (stack->count)++;
    return true;
}
Stack *destroyStack(Stack *stack)
{
    Node *temp;
    if (stack)
    {
        while (stack->top != NULL)
        {
            free(stack->top->dataPtr);
            Node *temp = stack->top;
            stack->top = stack->top->next;
            free(temp);
            stack->count--;
        }
        free(stack);
    }
    return NULL;
}
int main(void)
{
    unsigned int num;
    int *digit;
    Stack *stack;
    stack = createStack();
    printf("enter an integer: ");
    scanf("%d\n", &num);
    while (num > 0)
    {
        digit = (int *)malloc(sizeof(int));
        *digit = num % 2;
        push(stack, digit);
        num = num / 2;
    }
    while (!emptyStack(stack))
    {
        digit = (int *)pop(stack);
        printf("%ld ", *digit);
    }
    destroyStack(stack);
    return 0;
}