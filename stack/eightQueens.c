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
typedef struct
{
    int row;
    int col;
} POSITION;
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
int getSize(void)
{
    int boardSize = 0;
    printf("\nPlease enter the board size: ");
    scanf("%d", &boardSize);
    while (boardSize < 4 || boardSize > 8)
    {
        printf("Board size must be greater than 3 \n"
               "and less than 9. You entered %d.\n"
               "Please re-enter. Thank you.\a\a\n\n"
               "Your board size: ",
               boardSize);
        scanf("%d", &boardSize);
    }
    return boardSize;
}
bool guarded(int board[][9], int chkrow,
             int chkcol, int boardSize)
/*true : Pozisyon tehdit altında(guarded).Yeni bir kraliçe koymak güvenli değil.
false : Pozisyon güvenli(unguarded).Yeni bir kraliçe koyulabilir.*/
{
    int row, col;
    col = chkcol;
    for (row = 1; row <= chkrow; row++)
    {
        if (board[row][col] == 1)
        {
            return true;
        }
    }
    for (row = chkrow - 1, col = chkcol + 1; row > 0 && col <= boardSize; row--, col++)
    {
        if (board[row][col] == 1)
            return true;
    }
    for (row = chkrow - 1, col = chkcol - 1; row > 0 && col > 0; row--, col--)
    {
        if (board[row][col] == 1)
            return true;
    }
    return false;
}
void fillBoard(Stack *stack, int boardSize)
{
    int row;
    int col;
    int board[9][9] = {0};
    POSITION *pPos;
    row = 1;
    col = 0;
    while (row <= boardSize)
    {
        while (col <= boardSize && row <= boardSize)
        {
            col++;
            if (!guarded(board, row, col, boardSize))
            {
                board[row][col] = 1;
                pPos = (POSITION *)malloc(sizeof(POSITION));
                pPos->row = row;
                pPos->col = col;
                pushStack(stack, pPos);
                row++;
                col = 0;
            }
            while (col >= boardSize)
            {
                pPos = popStack(stack);
                row = pPos->row;
                col = pPos->col;
                board[row][col] = 0;
                free(pPos);
            }
        }
    }
    return;
}
void printBoard(Stack *stack, int boardSize)
{
    int col;
    POSITION *pPos;
    Stack *pOutStack;
    if (emptyStack(stack))
    {
        printf("There are no positions on this board\n");
        return;
    }
    printf("\nPlace queens in following positions:\n");
    // reverse stack for printing
    pOutStack = createStack();
    while (!emptyStack(stack))
    {
        pPos = popStack(stack);
        pushStack(pOutStack, pPos);
    }
    while (!emptyStack(pOutStack))
    {
        pPos = popStack(pOutStack);
        printf("Row %d-Col %d: \t|",
               pPos->row, pPos->col);
        for (col = 1; col <= boardSize; col++)
        {
            if (pPos->col == col)
                printf(" Q |");
            else
                printf("   |");
        } // for
        printf("\n");
    }
    destroyStack(pOutStack);
    return;
}

int main(void)
{
    // Local Definitions
    int boardSize;
    Stack *stack;
    // Statements
    boardSize = getSize();
    stack = createStack();
    fillBoard(stack, boardSize);
    printBoard(stack, boardSize);
    destroyStack(stack);
    printf("\nWe hope you enjoyed Eight Queens.\n");
    return 0;
} // main