#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//预处理之宏定义，这个是在预处理阶段执行的，原理很简单，对源码进行字符串替换
#define _PRINT_SEP_LINE_  printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");

void chapter1_helloworld() {
    printf("Hello, world!\n");
}

//4大类型：基本类型 构造类型 指针类型 空类型(void专用于表示函数不返回值)
//各种基本类型变量定义
//常量写法，输出格式串写法
void chapter2_basic_type() {
    _PRINT_SEP_LINE_
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
void chapter2_type_size() {
    _PRINT_SEP_LINE_
    char c1;
    short sh1;
    int i1;
    long l1;
    long long ll1; //8字节
    float f1;
    double d1;
    long double d2; //16字节

    printf("CHAR(%lu) SHORT(%lu) INT(%lu) LONG(%lu) LONGLONG(%lu) FLOAT(%lu) DOUBLE(%lu) LONGDOUBLE(%lu)\n\n",
    sizeof(c1), sizeof(sh1), sizeof(i1), sizeof(l1), sizeof(ll1), sizeof(f1), sizeof(d1), sizeof(d2));

    char *p1 = &c1;
    double *p2 = &d1;
    //指针表示一个变量的地址，各种指针在64位系统里，都是8字节
    printf("sizeof(point p1)=%lu sizeof(point p2)=%lu\n", sizeof(p1), sizeof(p2));
}

//c语言里面各种变量可以互相强行转换，但结果可能有损失
void chapter2_type_convert() {
    _PRINT_SEP_LINE_
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

    //用一个char指针，指向一个8字节的double变量，然后打印这8个字节都是什么值
    char *p;
    p = (char *)&d;
    int count = (sizeof(double) / sizeof(*p));
    for(int i=0; i<count; i++) {
        printf("DOUBLE D(%d):%d\n", i, (int)*p);
        //指针加一，内存往后跳指针类型的sizeof，例如 char *跳1，int *跳4
        p++;
    }
}

void chapter3_control_flow() {
    _PRINT_SEP_LINE_
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

void chapter4_array() {
    _PRINT_SEP_LINE_
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

    //注意，字符串类型变量，要多定义一个字节，用于存放结尾的0
    //char name[1000][10+1];

    char lfj1[10] = "abc";
    char lfj2[10] = "def";
    char fjg[20];

    //strcpy拷贝, strcat连接，用这两个函数把s1和s2连起来，放到ss中
    strcpy(fjg, lfj1);
    strcat(fjg, lfj2);
    printf("%s\n", fjg);

    //简单方法！
    sprintf(fjg, "%s--lfj--%s", lfj1, lfj2);
    printf("%s\n",fjg);

    //解决sprintf的越界问题，snprintf可以指定最大长度，就不会越界造成程序crash了
    snprintf(fjg, sizeof(fjg)-1, "%s--lfj--%s", lfj1, lfj2);

    //strtok可以按delim指定的分割符把一个字符串切开，但有个坏处，就是会破坏原来的字符串
    char fenges[64] = "zhangsan,100-99;45 66";
    char delim[5]=",-; ";
    char *pf;
    printf("before strtok fenges=%s\n", fenges);
    pf = strtok(fenges, delim);
    while(pf) {
        printf("%s\n", pf);
        pf = strtok(NULL, delim);
    }
    printf("after strtok fenges=%s\n", fenges);
}

struct sta {
    char a;
    int b;
};

//c语言里内存有几种存储区域：堆，栈，全局存储区，静态存储区，常量存储区
struct sta global_instance; //全局变量，名字不能重复，存在全局存储区

void chapter5and6_function_trans(int a, int *b, int *c, struct sta s1, struct sta *s2) {
    _PRINT_SEP_LINE_
    a+=10;
    (*b)+=10;
    c[0]+=10;
    *(c+0) += 10;

    //值传递...在复制出来的副本上操作，不影响原本
    s1.a+=1;
    s1.b+=1;

    //地址传递...直接在原本上操作
    s2->a+=1; //(*s2).a
    s2->b+=1;
}

//函数和指针，注意值传递与地址传递的用法，以及几种内存区域
//代码区：存放程序的代码，即CPU执行的机器指令，并且是只读的。
//常量区：存放常量(程序运行期间不能够被改变的量，如: 10，”abcde”，数组的名字等)
//静态区（全局区）：静态和全局变量的存储区域是一起的，静态区内存直到程序全部结束才会被释放
//堆区：调用malloc()函数来主动申请的，需使用free()函数来释放内存，不释放会泄露
//栈区：存放函数内的局部变量，形参和函数返回值。栈区之中的数据的作用范围过了之后
//      系统就会回收自动管理栈区的内存(分配内存 , 回收内存),不需要开发人员来手动
//      管理。栈区就像是一家客栈，里面有很多房间，客人来了之后自动分配房间，
//      房间里的客人可以变动，是一种动态的数据变动。
char *chapter5and6_function() {
    _PRINT_SEP_LINE_
    int x=1, y=2; //函数内部定义的临时变量，叫做栈，函数退出后，会自动释放，函数内不能重名
    int z[3] = {1,2,3};
    struct sta ss1 = {'A', 10};
    struct sta ss2 = {'A', 10};

    static int static_a = 10;

    //静态变量放在静态区，退出函数后仍然有效，直到退出程序才释放
    static_a+=10;
    printf("static a=%d\n", static_a);

    //x是值传递，复制了一份
    //y是地址传递，复制了个指针，但实际内容指向的是一份
    chapter5and6_function_trans(x, &y, z, ss1, &ss2);
    printf("after function x=%d y=%d z[0]=%d ss1.a=%c ss2.a=%c\n", x, y, z[0], ss1.a, ss2.a);

    char *dui = (char *)malloc(40); //动态分配的内存，位于堆
    return dui;
}

//组合类型之结构
void chapter7_complex_type() {
    _PRINT_SEP_LINE_
    struct student
    {
        int score;
        char sex;
        char c, d, e, f;
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

    //注意union各个字段的内存是共用的，这样就给访问同一段内存，提供了
    //不同的访问方式，例如下面例子里，这个联合会占4字节，然后可以用
    //ui按整数访问，又可以按us按字节访问
    union uu {
        unsigned int ui;
        struct c4i {
            unsigned char a, b, c, d;
        } us;
    } u;

    u.ui = 0xFFFFFFFF;
    printf("us.a=%x us.b=%x us.c=%x us.d=%x\n", u.us.a, u.us.b, u.us.c, u.us.d);
}

//枚举，位联合，类型定义...
void chapter8_enum_bit_typedef() {
    _PRINT_SEP_LINE_
    enum COLOR { 
        RED=1,
        GREEN,
        BLUE
    } c;
    c = GREEN;
    printf("COLOR GREEN=%d\n", c);

    //一个字节value，提供hi,lo两个按位访问的方式
    //联合的本质是共享内存空间
    //给联合定义了一个方便使用的名字BitField
    typedef union _bf {
        unsigned char value;
        struct {
            unsigned char hi:4;
            unsigned char lo:4;
        } bv;
    } BitField;

    BitField a;
    a.bv.hi = 10;
    a.bv.lo = 10;
    printf("union bitfield value=%X\n", a.value);
    union _bf b;
    b.value = 0xbb;
    b.value ^= 0xFF;
    printf("union bitfield hi=%X lo=%X\n", b.bv.hi, b.bv.lo);
}

//预处理的原理要理解清楚，是在编译之前，对源代码进行处理
//
#define DEBUG 1
void chapter9_preprocess() {
    _PRINT_SEP_LINE_
#if DEBUG
    printf("debug define true!!!\n");
#endif
}

//文件读写...
void chapter10_file() {
    _PRINT_SEP_LINE_
    //以写入创建方式打开test.txt...
    FILE *fp = fopen("test.txt", "w+");
    if(fp) {
        //如果打开成功写入如下文本到test.txt文件中，并关闭文件
        fprintf(fp, "%s %d\n", "hahaha", 20);
        fclose(fp);
    } else {
        printf("Open file test.txt error!\n");
    }

    typedef struct _stdudent {
        char sex;
        char nianling;
        unsigned int id;
        char loc[64];
        char name[32];
    } STUDENT;

    STUDENT s1, s2, s3;

    //给两个结构体分别赋值
    s2.sex = 0; 
    s2.nianling = 20;
    s2.id = 1;
    sprintf(s2.loc, "BEIJING");
    sprintf(s2.name, "ZHOUXIN");

    s1.sex = 0; 
    s1.nianling = 20;
    s1.id = 1;
    sprintf(s1.loc, "BEIJING");
    sprintf(s1.name, "ZHOUXIN");

    //以二进制读写创建方式打开student.dat...
    fp = fopen("student.dat", "wb+");
    if(fp) {
        //如果打开成功，把两个结构写入文件...
        fwrite(&s1, sizeof(STUDENT), 1, fp);
        fwrite(&s2, sizeof(STUDENT), 1, fp);
        //从文件头开始，跳过第一个结构体...
        //SEEK_SET表示文件开头，SEEK_END表示文件尾，SEEK_CUR表示当前位置
        fseek(fp, sizeof(STUDENT), SEEK_SET);
        //把第二个结构体读入到s3里
        fread(&s3, sizeof(STUDENT), 1, fp);
        //打印确认是否正确到从文件里读入了一个结构体
        printf("read from student.dat s3.name=%s\n", s3.name);
        fclose(fp);
    } else {
        printf("Open file student.dat error!\n");
    }
    //读取一个excel导出的csv文件,其实是以逗号分割字段的文本
    fp = fopen("score.csv", "r");
    char f1[32], f2[32], f3[32], f4[32], f5[32];
    int sc1, sc2, sc3, sc4;
    if(fp) {
        while(1) {
            //scanf的返回值，是实际读取的数据个数，注意读取到逗号的写法
            int ret = fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%s", f1,f2,f3,f4,f5);
            if(ret!=5) break;
            sc1 = atoi(f2);
            sc2 = atoi(f3);
            sc3 = atoi(f4);
            sc4 = atoi(f5);
            printf("%d %d %d %d\n", sc1,sc2,sc3,sc4);
        }
    }
}

int main()
{
    chapter1_helloworld();
    chapter2_type_size();
    chapter2_basic_type();
    chapter2_type_convert();
    chapter3_control_flow();
    chapter4_array();
    chapter5and6_function();
    //再次调用，观察static变量static_a的值
    chapter5and6_function();
    chapter7_complex_type();
    chapter8_enum_bit_typedef();
    chapter9_preprocess();
    chapter10_file();
}
