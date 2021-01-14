#include <stdio.h>
#include <string.h>
void strip_space(char *a, char *b)
{
    //去掉头部的空格
    while (*a == ' ' && *a)
        a++;

    //去掉尾部空格
    char *c = a + strlen(a) - 1;
    while (*c == ' ')
        c--;
    *(c + 1) = 0;

    while (*a)
    {
        //处理真正的词语
        while (*a != ' ' && *a)
        {
            *b = *a;
            a++;
            b++;
        }
        //处理多个空格
        while (*a == ' ' && *a)
        {
            if (*(a + 1) != ' ')
            {
                *b = ' ';
                b++;
            }
            a++;
        }
    }
    *b = 0;
}

int main()
{
    char a[256] = "111      222       333 444  555    666 ";
    char b[256];
    strip_space(a, b);
    printf("b=|%s|\n", b);
}