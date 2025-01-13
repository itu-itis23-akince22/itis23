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
int priority(char token)
{
    // Statements
    if (token == '*' || token == '/')
        return 2;
    if (token == '+' || token == '-')
        return 1;
    return 0;
}
bool isOperator(char token)
{
    if (token == '*' || token == '/' || token == '+' || token == '-')
        return true;
    return false;
}
int main(void)
{
    char postfix[80] = {0};
    char temp[2] = {0};
    char token;
    char *dataPtr;
    Stack *stack;
    stack = createStack();
    printf("Enter an infix formula: ");
    while ((token = getchar()) != '\n')
    {
        if (token == '(')
        {
            dataPtr = (char *)malloc(sizeof(char));
            *dataPtr = token;
            pushStack(stack, dataPtr);
        } // if
        else if (token == ')')
        {
            dataPtr = (char *)popStack(stack);
            while (*dataPtr != '(')
            {
                temp[0] = *dataPtr;
                strcat(postfix, temp);
                dataPtr = (char *)popStack(stack);
            } // while
        } // else if
        else if (isOperator(token))
        {
            // test priority of token at stack top
            dataPtr = (char *)stackTop(stack);
            while (!emptyStack(stack) && priority(token) <= priority(*dataPtr))
            {
                dataPtr = (char *)popStack(stack);
                temp[0] = *dataPtr;
                strcat(postfix, temp);
                dataPtr = (char *)stackTop(stack);
            } // while
            dataPtr = (char *)malloc(sizeof(char));
            *dataPtr = token;
            pushStack(stack, dataPtr);
        } // else if
        else // character is operand
        {
            temp[0] = token;
            strcat(postfix, temp);
        } // else
    } // while get token
    // Infix formula empty. Pop stack to postfix
    while (!emptyStack(stack))
    {
        dataPtr = (char *)popStack(stack);
        temp[0] = *dataPtr;
        strcat(postfix, temp);
    } // while
    // Print the postfix
    printf("The postfix formula is: ");
    puts(postfix);
    // Now destroy the stack
    destroyStack(stack);
    return 0;
}
