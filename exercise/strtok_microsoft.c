#include <stdio.h> 

#define ISCTRL(n) (map[(n)])
#define SETCTRL(n, bit) (map[(n)]=(bit))

char * mystrtok(char * string, const char * control) {
    unsigned char *str;
    const unsigned char *ctrl = (const unsigned char *)control; 
    unsigned char map[256];

    //静态变量，程序运行时一直有效
    //退出函数后也不释放
    //如果不加static，则退出函数后就释放了，起不到保存位置的作用
    static char *nextoken;
 
    //初始化一个256个位置的map，对应control字符的位置置1，其他位置置0
    //用于快速判断一个字符是否为control字符
    for (int count = 0; count < 256; count++) 
        SETCTRL(count, 0);
    do { 
        SETCTRL(*ctrl, 1);
    } while (*ctrl++);
 
    //首次调用str指向源字符串string，
    //以后调用str指向保存下一个词的静态变量nexttoken
    if (string)
        str = (unsigned char *)string;
    else
        str = (unsigned char *)nextoken;
 
    //把最前面的控制字符过滤掉
    while(ISCTRL(*str) && *str)
        str++;
 
    string = (char *)str;
 
    //向后查找控制字符，如果找到就把这个位置设置为'\0'
    //这时string为这个词的首地址，str指向这个词的结尾'\0'
    for (; *str; str++)
        if(ISCTRL(*str)) {
            *str++ = '\0';
            break;
        }
 
    //nextoken指向下一个词的开始
    //因为nextoken是一个静态变量，所以下一次调用时
    //仍然保存着，指向下一个词的开始
    nextoken = (char *)str;
 
    //如果string和str仍然一致，
    //表明已经找到了结尾
    if (string == (char *)str)
        return NULL;
    else
        return string;
}

int main()
{
    char fg[] = "111-222-333";
    char del[] = "-";
    char *pf;
    printf("origin string: %s\n", fg);
    pf = mystrtok(fg, del);
    while (pf)
    {
        printf("%s\n", pf);
        pf = mystrtok(NULL, del);
    }
    //printf("%s\n",fg);
    return 0;
}


