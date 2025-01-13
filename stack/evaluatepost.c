#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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
void *popStack(Stack *stack)
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
bool pushStack(Stack *stack, void *dataInPtr)
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
bool isOperator(char token)
{
    if (token == '*' || token == '/' || token == '+' || token == '-')
        return true;
    return false;
}
int calc(int operand1, int oper, int operand2)
{
    int result = 0;
    switch (oper)
    {
    case '+':
        result = operand1 + operand2;
        break;
    case '-':
        result = operand1 - operand2;
        break;
    case '*':
        result = operand1 * operand2;
        break;
    case '/':
        result = operand1 / operand2;
    }
    return result;
}
int main(void)
{
    char token;
    int operand1;
    int operand2;
    int value;
    int *dataPtr;
    Stack *stack;
    stack = createStack();
    printf("Input formula: ");
    while ((token = getchar()) != '\n')
    {
        if (!isOperator(token))
        {
            dataPtr = (int *)malloc(sizeof(int));
            *dataPtr = atoi(&token);
            pushStack(stack, dataPtr);
        }
        else
        {
            dataPtr = (int *)popStack(stack);
            operand2 = *dataPtr;
            dataPtr = (int *)popStack(stack);
            operand1 = *dataPtr;
            value = calc(operand1, token, operand2);
            dataPtr = (int *)malloc(sizeof(int));
            *dataPtr = value;
            pushStack(stack, dataPtr);
        }
    }
    dataPtr = (int *)popStack(stack);
    value = *dataPtr;
    printf("Result: %d\n", value);
    destroyStack(stack);
    return 0;
}