#include <stdio.h>

int main()
{
    char s1[10]="s1", s2[10]="s2";
    scanf("%[\"float \"]%s", s1, s2);
    printf("%s\n%s\n", s1, s2);
    return 0;
}
