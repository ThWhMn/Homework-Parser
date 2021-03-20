#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct Symbol {
    int  top;
    char s[400];
    char id[20][20];
} symbol;

struct Number {
    int  top;
    char n[400];
    int  s[100];
} number;

void initStack()
{
    symbol.top = -1;
    number.top = -1;
}

int replace(char a)
{
    switch (a) {
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
        case '(': return 0;
    }
}

int compare(char s, char e)
{
    return (replace(s) < replace(e)) ? 1 : 0;
}

int isOperator(char c)
{
    return (c == '+') || (c == '-') || (c == '*') || (c == '/');
}

void polishIt(char exp[])
{
    initStack();
    for (int i = 0; exp[i] != '\0'; i++) {
        if (isalpha(exp[i]) || isdigit(exp[i])) {
            number.n[++number.top] = exp[i];
        }

        else {
            if (symbol.top == -1) {
                symbol.s[++symbol.top] = exp[i];
                continue;
            }
            if (exp[i] == '(') {
                symbol.s[++symbol.top] = exp[i];
                continue;
            }
            if (exp[i] == ')') {
                while (symbol.s[symbol.top] != '(') {
                    number.n[++number.top] = symbol.s[symbol.top];
                    symbol.top--;
                }
                symbol.top--;
                continue;
            }

            if (compare(symbol.s[symbol.top], exp[i]))
                symbol.s[++symbol.top] = exp[i];
            else {
                number.n[++number.top] = symbol.s[symbol.top];
                symbol.s[symbol.top]   = exp[i];
                while (
                    !compare(symbol.s[symbol.top - 1], symbol.s[symbol.top]) &&
                    symbol.top > 0) {
                    number.n[++number.top]   = symbol.s[symbol.top - 1];
                    symbol.s[symbol.top - 1] = symbol.s[symbol.top];
                    symbol.top--;
                }
            }
        }
    }
    while (symbol.top != -1) {
        number.n[++number.top] = symbol.s[symbol.top];
        symbol.top--;
    }
    strcpy(exp, number.n);
}

int operate(char op, int left, int  right)
{
    switch (op) {
        case '+': return left + right;
        case '-': return left - right;
        case '/': if (right != 0) return left / right; else printf("Divided by zero!\n"); exit(0);
        case '*': return left * right;
        default:  printf("No such operation! How can this programm run?\n"); exit(0);
    }
}

void delstr(char str[], int l, int r)
{;}

int calculate(char exp[])
{
    int right, left;
    polishIt(exp);
    initStack();
    while(symbol.top != -1) {
        int i = strlen(exp) - 1;
        for (i; i >= 0; i--) {
            if (isOperator(exp[i])) {
                symbol.s[++symbol.top] = exp[i];
            } else {
                right = exp[i] - '0';
                left  = exp[i-1] - '0';
                delstr(exp, i-1, i+1);
                i--;
                number.s[++number.top] = operate(symbol.s[symbol.top], left, right);
                symbol.top--;
            }

        }
    }
}

int main()
{
    char str[] = "1+2+3*4-8/2";
    printf("%d\n", calculate(str));
    return 0;
}