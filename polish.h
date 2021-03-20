#include <stdio.h>

float cal(float a, char op, float b) {
	switch (op) {
	case '+' : return (a+b);
	case '-' : return (a-b);
	case '*' : return (a*b);
	case '/' : return (a/b);
	}
	return 0;
}

int infix_to_suffix(char in[], char suf[]) {
	char stack[100]; int top=-1; //运算符的栈
	int i, j;

	j=0; //suf[]的指针
	for (i=0; in[i]!='\0'; ++i) { //遍历in
		// 是数字
		if ('0' <= in[i] && in[i] <= '9') {
			suf[j++] = in[i];
			continue;
		} 

		// 是符号
		if (top==-1) { //栈为空
			stack[++top] = in[i];
			continue;
		}
		
		// 栈不为空
		if (in[i]=='+' || in[i]=='-') {
			while (stack[top]=='+' || stack[top]=='-' || stack[top]=='*' || stack[top]=='/') {
				suf[j++] = stack[top--];
			}
			stack[++top] = in[i];
		} else if (in[i]=='*' || in[i]=='/') {
			while (stack[top]=='*' || stack[top]=='/') {
				suf[j++] = stack[top--];
			}
			stack[++top] = in[i];
		} else if (in[i]=='(') {
			stack[++top] = in[i];
		} else if (in[i]==')') {
			while (stack[top]!='(') {
				suf[j++] = stack[top--];
			}
			top--;
		} else {
			suf[0]='\0';
			return -1;
		}
	}
	while (top!=-1) {
		suf[j++] = stack[top--];
	}
	suf[j]='\0';

	return 0;
}

float cal_suffix(char str[]) {
	float stack[100]; int top=-1; //存放数字
	int i;
	float a,b;

	for (i=0; str[i]!='\0'; ++i) {
		if ('0' <= str[i] && str[i] <= '9') { //数字
			stack[++top]=(float)(str[i]-'0'); 
		} else {
			b=stack[top--];
			a=stack[top--];
			stack[++top]=cal(a, str[i], b);
		}
	}

	return stack[top];
}

float calculate(char exp[])
{
    char suf[100];
    infix_to_suffix(exp, suf);
    return cal_suffix(suf);
}