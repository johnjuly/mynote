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