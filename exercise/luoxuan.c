#include <stdio.h>
#include <string.h>

//四个方向,依次为右下左上
typedef enum dir {
    RIGHT,
    DOWN,
    LEFT,
    UP
} DIR;


//走下一步，并把新的xy通过指针返回
void
next_step(DIR d, int *x, int *y) {
    switch(d) {
        case RIGHT:
            *x+=1;
            break;
        case DOWN:
            *y+=1;
            break;
        case LEFT:
            *x-=1;
            break;
        case UP:
            *y-=1;
            break;
        default:
            ;
    }
    /*
    //还有下面的写法，也经常用到，
    //可读性稍微差一点，但代码很简洁
    //也经常用到
    //dnum记录对应四个方向的x，y坐标操作数
    int dnum[4][2] = {
        {1,  0},
        {0,  1},
        {-1, 0},
        {0, -1}
    };
    *x+=dnum[d][0];
    *y+=dnum[d][1];
    */
}

//判断是否为合法的x,y坐标
int
inbox(int x, int y, int n) {
    return((x>=0) && (x<n) && (y>=0) && (y<n));
}

//填充螺旋矩阵
void
luoxuan(int n, int buf[n][n]) {
    DIR d = RIGHT;
    int x=0, y=0;
    int count = n*n;

    //清零整个矩阵
    memset(buf, 0, n*n*sizeof(int));

    for(int i=0; i<count; i++) {
        //填充当前位置
        buf[y][x] = i+1;

        //备份xy，尝试走下一步
        int bx = x, by = y;
        next_step(d, &bx, &by);

        //走出格或者碰到了已经填充过的位置则调整方向...
        if(!inbox(bx, by, n) || buf[by][bx]!=0)
            d = (d+1)%4;

        //按正确方向操作xy
        next_step(d, &x, &y);
    }
}

int
main() {
    int n = 6;
    int buf[n][n];

    luoxuan(n, buf);

    //输出
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            printf("%d\t", buf[i][j]);
        }
        printf("\n");
    }
}
