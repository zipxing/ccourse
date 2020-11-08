#include <stdio.h>


//4大类型：基本类型 构造类型 指针类型 空类型(void专用于表示函数不返回值)
//各种基本类型变量定义
//常量写法，输出格式串写法
void chapter1_basic_type() {
    int a = 1000000;

    a = 0x1000; //十六进制常量
    a = 010000; //八进制常量
    a = 0b100111000; //二进制常量（c语言最早的标准里没有，现在的编译器很多支持）

    //字符的本质是整数，也就是ascii码表中的顺序号
    char c = 'A';
    c += 2; //'A'加2变成了'C'
    printf("A+2=%c\n", c);

    float f = 3.19e20;
    double d = 3.3e30;
    //%.1e表示指数形式，保留一位小数
    //%08d表示不够长度8的补0，%8d表示不够长度的补空格（多用于对齐）
    printf("%08d %8d %o %.1e %lf\n\n", a, a, a, f, d);

    int *pi = &a;
    char *pc = &c;
    //指针表示一个变量的地址...
    printf("pointer to a:%p pointer to c:%p\n", pi, pc);
    //指向各种类型的指针，运算时，以这种类型占有的字节为基本单位
    //例如，整数指针加一地址后跳4个字节，字符型后跳1个字节
    printf("pointer to a +1 :%p pointer to c +1 :%p\n", pi+1, pc+1);
}

//打印各种基本类型占的字节数
//注意不同的电脑架构，长度不一定一样
void chapter1_type_size() {
    char c1;
    short sh1;
    int i1;
    long l1;
    long long ll1;
    float f1;
    double d1;
    long double d2;

    printf("CHAR(%lu) SHORT(%lu) INT(%lu) LONG(%lu) LONGLONG(%lu) FLOAT(%lu) DOUBLE(%lu) LONGDOUBLE(%lu)\n\n",
    sizeof(c1), sizeof(sh1), sizeof(i1), sizeof(l1), sizeof(ll1), sizeof(f1), sizeof(d1), sizeof(d2));

    char *p1 = &c1;
    double *p2 = &d1;
    //指针表示一个变量的地址，各种指针在64位系统里，都是8字节
    printf("sizeof(p1)=%lu sizeof(p2)=%lu\n", sizeof(p1), sizeof(p2));
}

//c语言里面各种变量可以互相强行转换，但不保证结果正确
void chapter1_type_convert() {
    int a;
    float f = 3.6;

    //自动类型转换，可能损失数据
    a = f;
    //浮点数转成整数，直接丢掉小数部分
    printf("CONVERT Float(%f) To Int: %d\n", f, a);

    //强制类型转换
    //最常用的是指针类型的显式强制转换
    //另外就是让编译器不发出警告
    double d = 8.0;
    a = (char)d;
    char *p;
    p = (char *)&d;
    int count = (sizeof(double) / sizeof(*p));
    for(int i=0; i<count; i++) {
        printf("DOUBLE D(%d):%d\n", i, (int)*p);
        //指针加一，内存往后跳指针类型的sizeof，例如 char *跳1，int *跳4
        p++;
    }
}

//组合类型之结构
void chapter1_complex_type() {
    struct student
    {
        char sex;
        char c, d, e, f;
        int score;
    } s1, sarr[100];
    printf("SIZE OF STRUCT:%lu SIZE OF STRUCT ARRAY:%lu\n", sizeof(s1), sizeof(sarr));
    s1.sex = 'm';
    s1.score = 0;
    printf("%c %d\n", s1.sex, s1.score);

    /*
    | c |   | s | s |
    | i | i | i | i |
    */
    struct st1 {
        char a;
        short b;
        int c;
    } ss1;

    /*
    | c |   |   |   |
    | i | i | i | i |
    | s | s |   |   |
    */
    struct st2 {
        char a;
        int c;
        short b;
    } ss2;

    //缺省结构体按4字节对齐，但可以用如下语句指定按1对齐
    //#pragma pack(1)
    //内存对齐是为了cpu快速读取一个变量，cpu读数据一般不是1个字节一个字节读，
    //而是4个字节倍数的块读，所以如果不对齐，可能要两次或者更多
    //上面那两个结构体，类型顺序变了，导致占用的内存是不同的
    printf("sizeof(st1)=%lu sizeof(st2)=%lu\n", sizeof(ss1), sizeof(ss2));

    struct st2 *p1 = &ss2, *p2 = &ss2;
    p2++;
    printf("p2-p1=%ld, addr~p2-addr~p1=%ld\n", p2-p1, (long)p2-(long)p1);
}

void chapter2_control_flow() {
    int i = 8;
    int j = 0;

    //c语言中没有bool类型，只要非零就是真，否则为假
    if(i) {
        printf("i=%d true\n", i);
        //惊叹号表示取非
        if(!j) {
            printf("j=%d false\n", j);
        }
    }

    //switch语句 特别注意，每种情况的处理语句后要加break，否则后面也会执行
    //只决定跳转到哪个入口，只跳转一次
    char ss[10] = "ABCD";
    for(int i=0; i<4; i++) {
        char c = ss[i];
        switch (c) {
            case 'A':
            case 'B':
                printf("SWITCH AorB......\n");
                break;
            case 'C':
                printf("SWITCH C......\n");
                break;
            default:
                printf("SWITCH DEFAULT\n");
        }
    }

    //for语句中break和continue的区别
    for(int i=0; i<10; i++) {
        if(i == 5) break; //跳出
        printf("TEST BREAK:%d\n", i);
    }
    for(int i=0; i<10; i++) {
        if(i == 5) continue; //跳过本次，但循环继续
        printf("TEST CONTINUE:%d\n", i);
    }

    //while循环等
    while(i) {
        printf("i in while = %d\n", i--);
    }
}

void chapter3_array() {
    //数组的初始化
    int aaa1[5] = {1,2,3,4,5};
    int aaa2[2][2] = {{1,2}, {3,4}};
    printf("TEST ARRAY:aaa1[0]=%d aaa2[0][0]=%d\n", aaa1[0], aaa2[0][0]);

    //数组就是一段连续的内存空间，占用的内存是基本类型*元素个数
    printf("SIZEOF int[5]=%lu SIZEOF int[2][2]=%lu\n", sizeof(aaa1), sizeof(aaa2));

    //字符数组初始化方式
    char s1[3] = {'a', 'b', 'c'};
    //字符数组可以以字符串的形式初始化，注意这样其实占用多了一个字符：最后的0
    char s2[4] = "abc";

    //注意不能用%s输出s1，因为s1没有以0结尾，按字符串打印printf不知道到哪里结束
    printf("s[0]=%c s1=%s s1[3]=%d\n", s1[0], s2, s2[3]);
    printf("sizeof(s1)=%lu sizeof(s2)=%lu\n", sizeof(s1), sizeof(s2));

    //数组的名字其实就代表了数组首地址，但不能对数组名进行加减运算
    int *p = (int *)aaa2;
    int i=1, j=1;
    printf("use pointer access array:aaa[%d][%d]=%d\n", i, j, *(p+i*2+j));

    printf("sizeof int[5]=%lu, sizeof int[2][2]=%lu, sizeof pointer->aaa2=%lu\n",
            sizeof(aaa1), sizeof(aaa2), sizeof(p));
}

int main()
{
    chapter1_type_size();
    chapter1_basic_type();
    chapter1_type_convert();
    chapter1_complex_type();
    chapter2_control_flow();
    chapter3_array();
}
