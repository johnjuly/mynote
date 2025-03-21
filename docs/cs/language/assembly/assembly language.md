#

## 前言

### 教学思想

* 信息组织和加工的艺术--相互关联的知识在一本书中如何组织
* 学习 航线 港口

## 第一章 基础知识

### 1.1 机器语言

机器指令的集合

* 写读 晦涩难懂 不宜查找

### 1.2 汇编语言的产生

编译器 将汇编指令转换为机器码

### 1.3 汇编语言的组成

* 汇编指令：机器码的助计符，有对应的机器码
* 伪指令：没有对应的机器码，由编译器执行，计算机并不执行
* 其他符号：如+ — * /等，由编译器识别，没有对应的机器码

### 1.4 存储器

aka 内存
指令和数据的存放位置

### 1.5 指令和数据

应用上的概念
在内存中都是指二进制信息

### 1.6 存储单元

微机存储器 128 字节

### 1.7 cpu对存储器的读写

3类交互

1. 存储单元的地址信息
2. 器件的选择 读或写的命令 控制信息
3. 读或写的数据 数据信息

总线：连接cpu和其他芯片的导线 物理上来讲 一根根导线的集合

* 地址总线的宽度决定了cpu的寻址能力
* 数据总线的宽度决定了   与其他器件进行数据传送时的一次数据传送量
* 控制总线的宽度决定了 对系统中其他器件的控制能力

## 第二章 寄存器

### “段地址*16+偏移地址=物理地址”的本质含义

cpu在访问内存时，用一个基础地址和一个相对于基础地址的偏移地址相加，给出内存单元的物理地址

### 段 segment

地址连续 起始地址为16的倍数的一组内存单元

### 检测点2.2

1.给定段地址为0001H,仅通过变化偏移地址寻址,cpu的寻址范围为**0010H* 到 *100FH*.

* 最小为偏移地址为0，段地址左移4位
* 最大偏移地址位FFFFH，FFFFH+00010H为最终结果

### 2.9 段寄存器

提供段地址
cs: 代码段寄存器
ip:指令指针寄存器

### 修改cs ip的指令

jmp 段地址：偏移地址
只修改Ip jmp 合法寄存器

## 第五章 [bx]和loop

### 5.1 [bx]和内存单元的描述

[bx]与[0]类似，[0]表示内存单元
例子：
mov ax,[0]
将一个内存单元的内容送入ax这个内存单元的长度为2字节
存放一个字，偏移地址为0.段地址在ds中
要完整地描述一个内村单元需要两种信息：地址+长度（类型）
段地址加偏移地址

### 5.2 loop指令

loop指令实现循环功能 cx存放循环次数

```asm

assume cs:code

code segment
  mov ax,2

  mov cx,11
s: add ax,ax
  loop s
  mov ax,4c00h
  int 21h
code ends
end

```

```asm
assume cs:codesg

codesg segment

           mov ax,0ffffh
           mov ds,ax
           mov bc,0         ;初始化ds:bx指向ffff:0

           mov dx,0         ;初始化累加寄存器，（dx）=0

           mov cx,12        ;初始化循环计数寄存器

    s:     mov al,[bx]
           mov ah,0         
           add dx,ax        ;j间接向dx中加上((ds)*16+(bx))单元的数值
           inc bx
           loop s



           mov ax,4c00h     ;程序返回
           int 21h
codesg ends

end

```

### 5.8 段前缀的使用

将内存ffff:0~ffff:b单元的数据复制到0：200~0：20b中

复制过程用：初始化加循环

```asm
assume cs:code
 code segment
    mov bx,0      ；偏移地址从0开始
    mov cx,12     ;(cx)=12.循环12次


 s: mov ax,0ffffh
    mov ds,ax     ;(ds)=0020h
    mov[bx],dl    ;将dl的数据送入0020：bx
    inc bx
    loop s

  mov  ax,4c00h
  int 21h
 code ends

end

```

* 不足 原始单元和目标单元相距
  大于64kb在不同的64kb段中，每次循环要设置两次ds 16位 64KB等于64 * 1024 = 65,536字节

* 于是分别用两个寄存器分别存放原始单元和目标单元的段地址

改进

```asm
assume cs:code

code segment
      mov ax,0ffffh
      mov ds,ax         ;(ds)=0ffffh

      mov ax,0020h
      mov es,ax          ;(es)=0020h

      mov bx,0           ;此时ds:bx指向 ffff:0.es:bx指向 0020：0

      mov cx,12

  s:  mov dl,[bx]
      mov es:[bx],dl
      inc bx
      loop s

      mov ax,4c00h
      int 21h

  code ends
  end












```