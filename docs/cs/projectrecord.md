#

* 不用for循环而是while(true)执行次数不确定用户可能会出错

## 两个问题

1.overwrite 覆盖某一玩家的值
2.输入非法字符

### 解决


1.不用for循环而是while(true)执行次数不确定用户可能会出错 breakout 跳出循环当且仅当输入合法值p
2.conditions

3.cin.clear() allows cin to be used again after an error.
4.cin.ignore(10000, '\n') clears out any invalid or extra input to prepare for the next user input.