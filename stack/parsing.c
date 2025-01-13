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
const char closMiss[] = "Close paren missing at line";
const char openMiss[] = "Open paren missing at line";
int main(void)
{
    Stack *stack;
    char token;
    char *dataPtr;
    char fileID[25];
    FILE *fpIn;
    int lineCount = 1;
    stack = createStack();
    printf("Enter file ID for file to be parsed: ");
    scanf("%s", fileID);
    fpIn = fopen(fileID, "r");
    if (!fpIn)
        printf("Error opening %s\n", fileID), exit(100);
    while ((token = fgetc(fpIn)) != EOF)
    {
        if (token == '\n')
            lineCount++;
        if (token == '(')
        {
            dataPtr = (char *)malloc(sizeof(char));
            pushStack(stack, dataPtr);
        }
        else
        {
            if (token == ')')
            {
                if (emptyStack(stack))
                {
                    printf("%s %d\n",
                           openMiss, lineCount);
                    return 1;
                }
                else
                    popStack(stack);
            }
        }
    }
    if (!emptyStack(stack))
    {
        printf("%s %d\n", closMiss, lineCount);
        return 1;
    }
    destroyStack(stack);
}