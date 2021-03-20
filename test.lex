%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENS 10
#define MAX_NUM 20
struct data{
	char keyword[LENS];
    char id[LENS];
    char op[LENS];
	char exp[LENS];
    union {
		int iValue;
	    float fValue;
    }value;
} test; 
int cnt=0;
%}

keyword [A-Za-z]
id 	   [A-za-z_]
digit  [0-9.]
operation [+\-*/]
expression {id}|{digit}|{operation}
operand {id}|{digit}

%%
^{keyword}+" "+{id}+" "*";"" "*$ {
    sscanf(yytext, "%[a-z]%*[ ]%[A-Za-z]", test.keyword, test.id);
	printf("keyword: %s\nid: %s\n", test.keyword, test.id);
}
^{id}+" "*"="" "*{operand}+(" "*{operation}" "*{operand}+)*" "*";"" "*$ {
    sscanf(yytext, "%[A-Za-z_]%*[ =]%[A-Za-z0-9. +/*-]", test.id, test.exp);
	printf("id: %s\nexpression: %s\n", test.id, test.exp);
}
\n {;}
^.*$ {
    printf("Unrecognized grammer.\n");
}
%%

int main()
{
    printf("Analysis start\n");
    yylex();
    return 0;
}
