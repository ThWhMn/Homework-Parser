#include <stdio.h>

int main()
{
    char s[] = "float abcd;";
    char keyword[10], id[10];
    sscanf(s, "%[^ ]", keyword);
    sscanf(s, "%*[^ ] %[^;]", id);
    printf("keyword: %s\nid: %s\n", keyword, id);
    return 0;
}
