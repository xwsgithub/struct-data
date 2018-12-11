#include <iostream>

using namespace std;
class Object{
public:
    virtual void Print()=0;
    virtual int getData()=0;
    
};        //存放数据域
struct Node
{
    Node* next;   //next 指针
    Node* pre;
    Object* data;  //指向数据域的指针
    Node()
    {
        next=NULL;
        pre=NULL;
    }
    Node(Object* m_data,Node*add_front=NULL,Node*add_after=NULL)      //a可初始化的f构造函数
    {
        data=m_data;
        pre=add_front;
        next=add_after;
    }
    void linkObj(Object* obj)
    {
        data=obj;
    }
};
class Link_List
{
protected:        //方便后面继承
    Node*head;   //头节点,哨兵节点
    Node*tail;   //尾节点
    int count;
public:
    Link_List();
    ~Link_List();
    int getLength() const;
    void printList() const;
    void addListTail(Node*node);   //在尾部插入一个节点
    void addListHead(Node*node);   //在头部插入一个节点
    void insertList(int position, Node*node);   //在第n个元素后面插入一个节点
    void deleteList(int position);     //删除某一个位置的节点
    bool isEmpty() const;   //判断链表是否为空
    
};                           //有头节点的链表，位置0为头节点
Link_List::Link_List()
{
    head=new Node();
    tail=head;
    count=0;
}
Link_List::~Link_List()
{
    delete head;
}
int Link_List::getLength() const
{
    return count;
}
void Link_List:: printList() const
{
    Node* first=head->next;
    while(first!=NULL)
    {
        first->data->Print();
        first=first->next;
    }
}
void Link_List::addListTail(Node*node)
{
    node->pre=tail;
    tail->next=node;
    tail=node;
    tail->next=NULL;
    count++;
}
void Link_List::addListHead(Node*node)
{
    node->next=head->next;
    head->next=node;
    count++;
    if(node->next!=NULL)
    {
        node->next->pre=node;
        node->pre=head;
    }
    else
    {
        node->pre=head;
    }
}
void Link_List::insertList(int position, Node*node)
{
    Node* new_node=head;
    for(int i=0;i<position;i++)
    {
        new_node=new_node->next;
    }
    node->next=new_node->next;
    new_node->next=node;
    node->next->pre=new_node;
    node->pre=new_node;
    count++;
}
void Link_List::deleteList(int position)
{
    Node* new_node=head;
    for(int i=0;i<position-1;i++)     //要删除第n个节点，指针便利到前一个位置
    {
        new_node=new_node->next;
    }
    Node*old_Node=new_node->next;
    new_node->next=new_node->next->next;
    new_node->next->pre=new_node;
    delete old_Node;
    count--;
}
bool Link_List::isEmpty() const
{
    return (count==0)? true:false;
}

