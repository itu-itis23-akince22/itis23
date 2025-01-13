#include <stdio.h>
#include <string.h>
#define OPERATORS "+-*/"
// Prototype Declarations
void preToPostFix(char *preFixIn, char *exprOut);
int findExprLen(char *exprIn);
int main(void)
{
    char preFixExpr[256] = "-+*ABC/EF";
    char postFixExpr[256] = "";
    printf("Begin prefix to postfix conversion\n\n");
    preToPostFix(preFixExpr, postFixExpr);
    printf("Prefix expr:  %-s\n", preFixExpr);
    printf("Postfix expr: %-s\n", postFixExpr);
    printf("\nEnd prefix to postfix conversion\n");
    return 0;
}
void preToPostFix(char *preFixIn, char *postFix)
{
    // Local Definitions
    char operator[2];
    char postFix1[256];
    char postFix2[256];
    char temp[256];
    int lenPreFix;
    // Statements
    if (strlen(preFixIn) == 1)
    {
        *postFix = *preFixIn;
        *(postFix + 1) = '\0';
        return;
    } // if only operand

    *operator= * preFixIn;
    *(operator+ 1) = '\0';
    // Find first expression
    lenPreFix = findExprLen(preFixIn + 1);
    strncpy(temp, preFixIn + 1, lenPreFix);
    *(temp + lenPreFix) = '\0';
    preToPostFix(temp, postFix1);
    strcpy(temp, preFixIn + 1 + lenPreFix);
    preToPostFix(temp, postFix2);
    // Concatenate to postFix
    strcpy(postFix, postFix1);
    strcat(postFix, postFix2);
    strcat(postFix, operator);
    return;
}
int findExprLen(char *exprIn)
{
    // Local Definitions
    int len1;
    int len2;
    // Statements
    if (strcspn(exprIn, OPERATORS) == 0)
    // General Case: First character is operator
    // Find length of first expression
    {
        len1 = findExprLen(exprIn + 1);
        // Find length of second expression
        len2 = findExprLen(exprIn + 1 + len1);
    }
    else
        len1 = len2 = 0;
    return len1 + len2 + 1;
}