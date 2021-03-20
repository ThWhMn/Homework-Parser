#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "polish.h"

#define MAXLEN 100
#define MAXNUM 200

typedef struct data{
	char keyword[MAXLEN];
    char id;
    int isDetermine;
    int deterBy;
    int deterIt;
    union {
		int iValue;
	    float fValue;
    }value;
} Data;
Data var[MAXNUM]; 

typedef struct line{
    char id;
    char exp[MAXLEN];
    int expHasId;
} Oneline;
Oneline line;
int cnt=0;

int isKeyword(char keyword[]);
void init(Data *var);
int existId(char id);
void rmSpace(char str[]);
void change2polish(char exp[]);
int checkBracket(char exp[]);
int check(char exp[], int *expHasId, int index);
void compute(Oneline *line);
void writeValue(int id);


int isKeyword(char keyword[])
{
    const char keywords[][MAXLEN] = {
        "int", "float", NULL,
    };
    int i = 0;
    while(keywords[i]!=NULL) {
        if(strcmp(keywords[i], keyword)==0){
            return 1;
        }
        i++;
    }
    return 0;
}

void init(Data *var)
{
    var->isDetermine = 0;
    var->deterBy = var->deterIt = -1;
    var->value.iValue = 0;
}

int existId(char id)
{
    for (int i = 0; i < cnt; i++) {
        if (var[i].id == id) {
            return i;
        }
    }
    return -1;
}

void rmSpace(char str[])
{
    char tmp[MAXLEN];
    int j = 0;
    for (int i = 0; i < strlen(str); i++){
        if (str[i] != ' ') {
            tmp[j] = str[i];
            j++;
        }
    }
    tmp[j] = '\0';
    strcpy(str, tmp);
}

int checkBracket(char exp[])
{
    char stack[MAXLEN];
    int top = -1, i;
    for (i = 0; i < strlen(exp); i++) {
        if (exp[i] == '('){
            stack[++top] = '(';
        } else if (exp[i] == ')') {
            if (top == -1)
                return 0;
            else
                top--;
        }
    }
    if (top != -1)
        return 0;
    else
        return 1;
}

int check(char exp[], int *expHasId, int index)
{
    rmSpace(exp);
    char id;
    int deterBy;
    int len = 0, hasId = 0;
    // if (!checkBracket(exp)) {
    //     return 0;
    // }
    for (int i = 0; i < strlen(exp); i++) {
        if (isalpha(exp[i])) {
            *expHasId = hasId = 1;
        }
        if (hasId && (deterBy = existId(id)) == -1) {
            return 0;
        } else if (hasId) {
            var[index].deterBy = deterBy;
        }
        len = hasId = 0;
    }
    return 1;
}

void compute(Oneline *line)
{
    int index = existId(line->id);
    if (line->expHasId) {
        ;
    } else {
        if (strcmp("int", var[index].keyword) == 0) {
            var[index].value.iValue = (int)calculate(line->exp);
        } else if (strcmp("float", var[index].keyword) == 0) {
            ;
        }
    }
}

void writeValue(int id)
{
    const char *k = var[id].keyword;
    if (strcmp(k, "int") == 0) {
        printf(">>> %d\n", var[id].value.iValue);
    } else if (strcmp(k, "float") == 0) {
        printf(">>> %.2f\n", var[id].value.fValue);
    }
}