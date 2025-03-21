#

## linkedlist

```c++
struct listNode{
  int val;//节点值
  listNode *next;//指向下一节点的指针
  listNode(int x): val(x),next(nullptr){}//构造函数
}；
/*初始化链表*/
//初始化各个结点
listNode* n0=new listNode(1);
listNode* n1=new listNode(3);
listNode* n2=new listNode(4);
listNode* n3=new listNode(5);
listNode* n4=new listNode(6);
//构建节点之间的引用
n0->next=n1;
n1->next=n2;
n2->next=n3;
n3->next=n4;



/*插入在结点n0后插入结点p*/
void insert(listNode *n0,listNode* P)
{
  listnode *n1=n0->next;
  P->next=n1;
  n0->next=P;//修改两个结点
}

/*删除链表的结点n0后的首个结点*/

void remove(listNode *n0){
//改变一个结点的指针
if(n0->next == nullptr)
  return;
//n0->P->n1
listNode*P=n0->next;
listNode*n1=P->next;
n0->next=n1;
//释放内存
delete P;

}

/*访问索引为index的结点*/

listNode *access(listNode *head,int index){
  for(int i=0;i<index;i++){
    if(head==nullptr)
      return nullptr;
    head=head->next;
  }
  return head
}


/*查找*/

int find(listNode* head,int target)
{
  int index=0;
  while(head!=nullptr){
    if(head->val==target)
      return index;
    head=head->next;
    index++;
  }
  return -1;
}

```

## stack

```cpp
/*初始化栈*/
stack<int>stack;
/*元素入栈*/
stack.push(1);
stack.push(2);
stack.push(3);
stack.push(4);
/*访问栈顶元素*/
int top=stack.top();
/*元素出栈*/
stack.pop();//无返回值

int size=stack.size();
bool empty=stack.empty();

/*基于链表实现的栈*/

class LinkedListStack{
private:
  listNode *stacktop;//将头节点作为栈顶
  int stkSize;

public:
  LinkedListStack(){
    stacktop=nullptr;
    stkSize=0;
  }

~LinkedListStack(){
  //遍历链表删除结点，释放内存
  while(stackTop){
    listNode*temp=stackTop;
    stackTop=stackTop->next;
    delete temp;

  }
}



}






```





