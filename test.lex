%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENS 10
#define MAX_NUM 20
const char *keywords[] = {
    "int",
    "float",
    NULL,
};
const char ops[][LENS] = {
    "+", "-", "*", "/",
};
struct threeAddressCode{
    char keyword[LENS];
    char id[LENS];
    char op[LENS];
    union {
        int iValue;
	float fValue;
    }value;
}tokens[MAX_NUM];
int cnt = 0;
%}

letter [A-Za-z_]

%%
 /*{letter}+ {printf("length of input:%d", yyleng);} */
"float"(" "+)(letter+)";" {
    printf("input: %s", yytext);
    scanf("%s", tokens[cnt].keyword);
    while (getchar()==' ') ;
    scanf("%s", tokens[cnt].id);
    cnt++;
    printf("keywords: %s\nid: %s\n", tokens[0].keyword, tokens[0].id);
}
[0-9]+ {printf("%d", atoi(yytext));}
%%

int main()
{
    printf("Analysis start\n");
    yylex();
    printf("Analysis finished\n");
    return 0;
}
