# 计算机和编程语言史话趣闻
## 编程语言的基础知识
- 计算机硬件进化
[硬件发展历史](https://www.jianshu.com/p/6fb655c286bc)
- 编程语言发展简史
[编程语言进化](https://www.cnblogs.com/zzp-biog/p/9835580.html)
- C的地位超然
<br/><font size=2>　　　　C语言可以说是最成功的用于开发操作系统的语言，和现代操作系统发展密不可分的（Unix Linux MacOS WindowsNT iOS Android）C语言也起源于电报电话公司AT&T的贝尔Bell实验室，所以和通信行业密不可分的
<br/>　　　　故事还要从半个世纪前Internet的鼻祖ARPAnet说起。1969年「美国国防部高级研究计划管理局」希望通过专门的接口信号处理机（IMP）和专门的通信线路，把美国的几个军事和研究用的电脑主机联接起来，其4个结点分别分布在：加州大学洛杉矶分校、加州大学圣巴巴拉分校、斯坦福大学和犹他州立大学的4台大型机上。因为ARPAnet的初衷是为了方便学校间的资源共享，所以那时很多研究员在合作一个项目时会经常共享代码和信息，这为日后开源的可行性提供了参考。1965年，通用电气和麻省理工学院发现当时的分时操作系统，只能支持30台终端访问主机，于是拉上了「美国电话电报公司」，也就是大名鼎鼎的AT&T旗下的贝尔实验室，计划合作开发一套多用户、多用途、分时的操作系统，他们给这个系统起名叫「复杂指令和计算服务」，简称Multics。Multics被设计运行在GE-645大型主机上。要知道那时的计算机还处在石器时代，距离第一台重30吨的计算机鼻祖ENIAC的发明也仅仅过了十几年，微处理器要在未来十年后才会出现，更没有现代意义上的「电脑」，要实现这样一个操作系几乎是不可能完成的任务。所以没过多久，Multics这个项目就宣告完结，AT&T也从这个项目中撤了出来。
<br/>　　　　然而故事到这里才刚刚开始，话说贝尔实验室里有两个参与了Multics开发的大神——Ken Thompson和他的同事Dennis Ritchie。他们当时在Multics下开发了一款叫《太空旅行》的游戏，现在操作系统没了，游戏也没法跑了。于是这两个大神一言不合就要开发一个新系统。当时主流的操作系统是「批处理操作系统」，但他们对此并不感冒。所以就在DEC PDP-7 小型机上开发一个「阉割版」的Multics系统，取名叫Unics。后来，这个名字被神秘地改成了Unix。Unix是现代操作系统的启蒙，从Unix中衍生出了一个相当相当长的操作系统列表：SunOS、Linux、Mac OS、Windows NT，以及IBM和微软合作开发的DOS。它还间接促成了C语言的诞生，它所遵循的KISS法则，即「保持简单和笨拙」，成为了后世工程师们神圣的铁律。Ken Thompson和Dennis Ritchie就如同牛顿，用几个简单的物理定律把计算机世界里的复杂规律概括的层次分明。后来，他们还在1983年获得了计算机领域里的最高荣誉「图灵奖」。
<br/><br/><B>　　　操作系统的进化历史</B>
   - 1965年贝尔实验室（Bell Labs）、通用电气（General Electric）和麻省理工学院（MIT）欲共同打造MULTICS（Multiplexed Information and Computing Service）操作系
   - 1969年贝尔实验室退出MULTICS
   - 1969年MULTICS计划成员Ken Thompson为了使其编写的“star travel”可运行在PDP-7上，使用汇编语言编写了原始的UNIX
   - 1970年Brian Kernighan戏称其系统为"UNiplexed Information and Computing Service"（UNICS）
   - 1970年Ken Thompson尝试用Fortran重写UNIX失败后整合BCPL成B语言
   - 1971年Ken Thompson使用B语言在PDP-11/24上编写了第一个正式版UNIX
   - 1972年Dennis M.Ritchie为了能早点玩上游戏加入了项目
   - 1973年Dennis M.Ritchie对B语言进行改造创造了C语言
   - 1973年Ken Thompson和Dennis M.Ritchie使用C语言编写了第三个UNIX版本
   - 1977年SUN创始人Bill Joy获得UNIX6核心原始代码对其进行改造后发布为BSD（Berkeley Software Distribution）版本，其他主要UNIX版本也在此时形成
   - 1979年UNIX7开始AT&T收回UNIX版权并不再开放新版UNIX源代码
   - 1983年Richard Matthew Stallman发起GUN（GNU's Not UNIX）计划
   - 1984年由于不能再使用UNIX源代码荷兰Vrije大学的Andrew S. Tanenbaum教授仿照UNIX着手开发Minix并于1987年完成
   - 1991年Linus Benedict Torvalds仿造Minix开发了Linux，并将Linux0.02发布到网络上
   - 1992年GUN放弃Hurd改以Linux为其内核（Hurd项目至今仍存在）
   - 1993年AT&T将UNIX所有版权买给Novell，IBM等由于早期授权不受影响
   - 1995年Bob Young创建RedHat
   - 1995年Novell将Unix卖给SCO21世纪初受Windows和Linux两面夹击下江河日下的SCO，在Windows的挑唆下控告IBM侵犯其源代码并意指Linux阵营
   - 2007年Novell在各大公司的支持下状告SCO夺回UNIX版权
<br/><B>苹果和UNIX</B>
   - 1984年System 1发布直接来源是BSD，该系统首次实现GUI
   - 1985年9月乔布斯被迫离开苹果
   - 1988年苹果起诉Windows抄袭System界面
   - 1996年乔布斯回归苹果
   - 1997年乔布斯与盖茨合解
   - 1997年System 7.6开始更名为Mac OS
   - 2001年重新设计的Mac OS并命名为OS X
   - 2007年基于OS X的ios随iphone一同发布
<br/><B>微软和UNIX</B>
   - 1975年盖茨从哈佛退学创立微软
   - 1979年微软从AT&T获取授权并开发了运行于intel平台的Xenix
   - 1980年微软买下QDOS改名MSDOS应付了与IBM的合作协议
   - 1985年6月看到操作系统的潜力的IBM欲借与微软共同开发OS/2之名将操作系统把控回自己手中
   - 1985年11月基于MSDOS的Windows1.0发布
   - 1987年微软将Xenix出售给SCO应付IBM的同时发Windows3.0
   - 1987年11月微软发布Windows2.0
   - 1990年具有使用价值的Windows3.0发布
<br/><B>Android和UNIX</B>
   - 2002年Andy Rubin创立Android公司，Android系统基于Linux内核
   - 2005年google收购Android公司
   - 2008年Android1.1发布</font>
- 现代编程语言的功能进化
# 编程相关的周边工具和技巧
## 基本命令行
- 操作目录
- 操作文件
- 编译
- 运行
## 多文件编译
- 为啥要用多文件
- 头文件和extern
- 简单的make工程文件
## 制作静态链接库.a
- 代码的复用
- 制作静态库的命令
- 规避符号重复
## 程序的调试
- 打印暴力调试
- 调试工具lldb
## 版本管理工具
- 为什么要进行版本管理
- git的原理和使用
## markdown文档的撰写
## mac下运行win
- bootcamp安装原生win10
- Parallels Desktop for Mac调用bootcamp
# C语言编程
## C语言基础
## 数据结构与算法
- 字符串处理练习（指针与数组加深理解）
- 线性表数据结构
- 哈希算法
- 树算法
- 高级练习
## 系统编程
- 多线程并发
- 网络编程
- 进程间通信-共享内存
## 图形编程
- GUI程序
- 3D程序
