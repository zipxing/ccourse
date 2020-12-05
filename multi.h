//预防重复定义
//比如一个项目要3个文件A.c，B.c，C.c
//如果B.c和C.c里都需要调用一个函数
//则必须都include这个头文件
//如果不加这个ifndef那链接时会报错
//重复定义符号
#ifndef _MULTI_H_
#define _MULTI_H_

//正确的做法是在c文件里定义全局变量，
//在h文件里用extern声明这个变量
//如果不include这个h文件，链接时会报错
//找不到符号
extern int global_count;
void inc_global_count(int n); 

#endif
