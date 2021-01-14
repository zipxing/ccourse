#include <stdio.h>
#include <string.h>

#define TRUE  1
#define FALSE 0

void strip_space(char *src, char *dst) {
    if(src==NULL || src[0]==0)
        return;
    char *pd = dst;
    int is_space = FALSE, is_leader = TRUE;
    int len = strlen(src);

    for(int i=0; i<len; i++) {
        //跳过开头的空格
        if(is_leader && src[i]==' ') {
            continue;
        } else {
            is_leader = FALSE;
        }
        //遇到了空格设置标志
        if(src[i] == ' ') {
            is_space = TRUE;
        } else { //遇到非空格
            //如果上一个是空格标志,加一个空格
            if(is_space)
                *pd++ = ' ';
            //把当前值加上,并设置空格标志为False
            *pd++ = src[i];
            is_space = FALSE;
        }
    }
    *pd=0;
}

int main() {
    char a[256] = "  111    222 333   444 555    666     ";
    char b[256];
    strip_space(a, b);
    printf("b=|%s|\n", b);
}
