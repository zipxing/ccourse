#include <stdio.h>
char *mystrtok(char *a, const char *del)
{
    static char *head = NULL; //记录非分隔串字符位置
    const char *delptr = del;
    int mark1 = 1, del_found = 0; //mark1用于记录第一个非分隔符位置
    char *return1 = NULL;
    if (a == NULL)
    {
        a = head;
    }
    
    for (; *a; a++)
    {
        del = delptr;
        for (; *del; del++)
        {
            if (*a == *del)
            {
                *a = '\0'; 
                del_found = 1;
                break;
            }
        }
        if (*a!='\0' && mark1 == 1)
        {
            return1 = a;
            mark1 = 0;
        }
        if (*a != '\0' && mark1 == 0 && del_found == 1)
        {
            head = a;
            return return1;
        }
    }
    head = a;
    return return1;
}
int main()
{
    char fg[] = "da-LiFujin;jia,JiaShuhua teisha";
    char del[] = ",-; ";
    char *pf;
    printf("%s\n", fg);
    pf = mystrtok(fg, del);
    while (pf)
    {
        printf("%s\n", pf);
        pf = mystrtok(NULL, del);
    }
    //printf("%s\n",fg);
    return 0;
}