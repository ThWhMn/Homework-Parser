%{
#include "head.h"
%}

keyword [a-z]
id 	    [A-Za-z]
digit  [0-9.]
operation [+\-*/()]
expression {id}|{digit}|{operation}|" "
operand {id}|{digit}

%%
^{keyword}+" "+{id}+" "*$ {
    sscanf(yytext, "%[a-z]%*[ ]%[A-Za-z]", var[cnt].keyword, &var[cnt].id);
    // printf("keyword: %s\nid: %c\n", var[cnt].keyword, var[cnt].id);
    if (isKeyword(var[cnt].keyword)) {
        init(&var[cnt]);
        cnt++;
        // printf("cnt: %d\n", cnt);
    } else {
        printf("Value type error! Check and input again.\n");
    }
}
^{id}+" "*"="" "*{expression}+" "*$ {
    int index;
    sscanf(yytext, "%[A-Za-z]%*[ =]%[A-Za-z0-9.() +/*-]", &line.id, line.exp);
    // printf("id: %c\nexp: %s\n", line.id, line.exp);
    if ((index = existId(line.id)) != -1) {
        if (check(line.exp, &line.expHasId, index)) {
            compute(&line);
        } else {
            printf("Unrecognized expression!\n");
        }
    } else {
        printf("Variable not declared!\n");
    }
}
^"write("" "*{id}" "*")"" "*$ {
    sscanf(yytext, "%*[write]%*[( ]%[A-Za-z]", &line.id);
    int i;
    if ((i = existId(line.id)) != -1) {
        writeValue(i);
    } else {
        printf("Variable not exist!\n");
    }
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
