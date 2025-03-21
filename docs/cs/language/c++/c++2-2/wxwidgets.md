#

## 2/15

* 编译
mingw32-make -f makefile.gcc BUILD=release SHARED=1 MONOLITHIC=1 UNICODE=1 CXXFLAGS=-fno-keep-inline-dllexport

变量

build: wxwidgets的生成类型。大多数情况下使用release.因为不会去调试wxwidgets本身。可以调试你自己的程序链接到一个release 版本的wxwidgets

shared: 定义链接类型：动态链接(shared=1)下必须把所需的dll和程序一同发布，而静态链接（0）只需发布程序本身，动态链接下生成的程序体积更小，但需要相应的dll才能运行它

monolithic:控制编译生成一个dll(1)还是多个(0)当为1时开发更简单，只需在发布程序时携带一个dll但关闭时连接过程会更有效，这样避免了链接整个wxwidgets代码库

unicode: 定义wxwidgets和你的程序时使用宽字符字符串（1
）还是ansi.**建议使用wxwidgets的_("string")和_T("string")宏来确保你的硬编码字符串格式正确**