#

## shell 的基本生命周期

- 初始化：读以及执行配置文件
- 翻译：从 stdin 中读命令(可以是输入可以是文件)然后执行
- 停止：shotdown commands,释放空间然后 terminates

* 简单的框架

```c
int main(int argc,char **argv){

//load config files

//run command loop

lsh_loop();

//perform any shutdown/cleanup

return EXIT_SUCCESS;


}


```

## 循环做什么

- 三步：
  1. read:读取命令
  2. parse:将字符串分离
  3. execute:执行命令
- 框架如下：

```c
void lsh_loop(void){
    //变量声明
    char *line;
    char **args;
    int status;

    do{
        printf(">");
        line= lsh_read_line();
        args=lsh_split_line(line);
        status=lsh_execute(args);


        free(line);
        free(args);

    }
    while(status);
}



```

- 使用 do while 的原因 在检查值之前线执行一次

## lsh_read_line()

```c
#define LSH_RL_BUFSIZE 1024

char * lsh_read_line(void)
{
    int bufsize=LSH_RL_BUFSIZE;
    int position=0;
    char*buffer=malloc(sizeof(char)*bufsize);
    int c;


    if(!buffer){
        fprint(stderr,"lsh:allocation error\n");
        exit(EXIT_FAILURE);
    }

    while(1){
        //read a character
        c=getchar();

        //if we hit eof,replace it with a null character and return.
        if(c==EOF||c=='\n'){
            buffer[position]='\0';
            return buffer;
        }
        else{
            buffer[position]=c;
        }
        position++;


        //如果超了大小，重新分配

        if(position>=bufsize){
            bufsize+=LSH_RL_BUFSIZE;
            buffer=realloc(buffer,bufsize);
            if(!buffer){
            fprint(stderr,"lsh:allocation error\n");
            exit(EXIT_FAILURE);
        }
    }
}
}
```

- 将字符用整数来存，因为 eof 是一个整数

- getline 版本

```c
char * lsh_read_line(void){
    char* line=null;
    ssize_t bufsize=0; //不需要手动分配空间了

    if (getline(&line,&bufsize,stdin) == -1){
        if(feof(stdin)){
            exit(EXIT_SUCCESS);
        }
        else{
            perror("readline");
            exit(EXIT_FAILURE);
        }
    }
    return line;
}


```

## parsint the line

* 同样也是简化了的，只有空格分隔开来


```c
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM "\t\r\n\a"

char **lsh_split_line(char *line){*
    int bufsize =LSH_TOK_BUFSIZE,position=0;
    char **tokens=malloc(bufsize*sizeof(char*));
    char *token;

    if(!tokens){
        fprintf(stderr,"lsh:allocation error\n");
        exit(EXIT_FAILURE);
    }
    token = stetok(line,LSH_TOK)
}






```