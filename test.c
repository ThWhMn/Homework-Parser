#include <stdio.h>

int main()
{
    char s[] = "float abcd;";
    char keyword[10], id[10];
    sscanf(s, "%[a-z]%*[ ]%[a-z]", keyword, id);
    printf("keyword: %s\nid: %s\n", keyword, id);
    return 0;
}
