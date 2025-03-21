#

## overview

provide a unified interface for interacting with external input

stream:a character buffer automatically interacts with the external source

 把变量转换成字符串的形式 （可以写入buffer）


## stringstream

not connected to any external source
creat extract insert

* constructors
    istringstream iss("initial");
    osstringstream oss("initial");

    //can provide "modes"such as ate(start at end位置 )or bin(read as binary)
    isstringstream iss("initial",stringstream::bin);
    ostringstream oss("initial",osstringstream::ate)





### key takeaways

* >>做什么？
    >>extracts the next variable of a certain type,up to the next whitespace
* 为什么>>和<<可以chain 起来？
    the >>and<< operators return a reference to the stream itself,so in each instance the stream is the left hand operand
* 有没有一个stringstream可以读和写
    有，reading and writing 同时但 can often lead to subtle bugs

## input streams

从目标源或外部员读取数据的一种方法

### std::cin是console input stream

* std::cin is buffered
* 是一个用户可以存 取数据的一个地方
* std::nufferstops at a whitespace
* whitespace in c++ includes:
  * " "
  * \n
  * \t


## statebits

四种

* good bit:ready for read/write;   nothing unusual,on when other bits areoff
* fail bit: previous operation failed, all future operations frozen type mismatch,file cannot beopened,seekg failed
* eof bit: previous operation reached the end of buffer content reach ed the end of the buffer
* bad bit:external error,likely irrecoverable   could not move characters to buffer from external source(正在读取的文件突然被删除了)




## main takeaways

* streams are a general interface to read and write data in programs
* input and output streams on the same source/destination type compliment each other
* 不要将getline()和std::cin()一起使用，一般情况下,getline()会读入空格
  * std::cin() - leaves the newline in the buffer
  * getline() - gets rid of the newline

