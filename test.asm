DATA SEGMENT
    MESG DB "This is an Assembly Language Programe.", 0DH, 0AH, "$"
    SPACE DB " ", "$"
DATA ENDS
CODE SEGMENT
    ASSUME CS:CODE, DS:DATA
    START:
        MOV AX, DATA
        MOV DS, AX              ; 将 DATA 段的段首址存入 DS
        MOV BX, 01H             ; BX 初始值设为 1
    AGAIN:
        MOV DX, OFFSET MESG     ; 取欲显示的字符偏移量赋给 DX
        MOV AH, 09H             ; 调用 9号(显示)DOS功能子程序
        INT 21H
        MOV CX, BX              ; 将 BX 的值赋给 CX
        INC BX
    NEXT:
        MOV DX, OFFSET SPACE    ; 取空格字符偏移量赋给 DX
        MOV AH, 09H
        INT 21H
        LOOP NEXT               ; 继续显示空格字符，直到 CX 为 0
        CMP BX, 10              ; BX 与 10 比较
         JBE AGAIN               ; 没显示 10 次，转移到 AGAIN 继续执行程序
        MOV AH, 4CH
        INT 21H                 ; 返回 DOS
CODE ENDS
END START