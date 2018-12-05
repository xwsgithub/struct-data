//
//  main.cpp
//  排序算法的实现及性能测试及比较
//
//  Created by xiongwei on 2018/11/27.
//  Copyright © 2018年 xiongwei. All rights reserved.
//
//本次试验插入排序，选择排序，希尔排序，快速排序，堆排序的实验对象为顺序表，归并排序实验的对象为链表
//

#include <iostream>
#include "m_list.h"
#include "Link_List.h"     //有哑结点的链表

class list:public m_list<int>
{
    time_t time_start,time_end;        //记录时间
    int compar_count;                  //记录比较次数
    int move_count;                    //记录移动次数
    int time;
    void recursive_quickSort(int to_sort_first,int to_sort_last);   //快速排序里的递归部分
    void insertHeap(int current,int low,int high);           //私有函数用于堆排序
    void recursive_heapSort(int low,int high);               //堆排序中的递归部分
    void recursive_mergeSort(list* &l);        //归并排序中的递归部分
    list* merge(list*l1,list*l2);           //将l1和l2合并成一个list
public:
    void setnum(int position,int num){
        if(position>=count){
             count++;
        }
        arry[position]=num;
    }
    void insetionSort();    //插入排序
    void selectionSort();   //选择排序
    void shellSort();       //希尔排序
    void quickSort(){
        time_start=clock();
        recursive_quickSort(0,count-1);
        time_end=clock();
        time=difftime(time_end, time_start);
    }                        //快速排序
    void mergeSort();         //归并排序
    void buildHeap();        //初始化最大堆组
    void heapSort();          //堆排序
    void print();
    list()
    {
        compar_count=0;        //初始化为0
        move_count=0;
    }
    
};

class integer:public Object    //继承数据域，用于链表操作
{
    int data;
public:
    void Print()
    {
        cout<<data<<" ";
    }
    integer(int num)
    {
        data=num;
    }
    int getData(){
        return data;
    }
    
};

class link_list:public Link_List{
    time_t time_start,time_end;
    int time,compare_count,move_count;
public:
    link_list(){
        compare_count=0;
        move_count=0;
    }
    void mergeSort(){
        time_start=clock();      //初始时间
        recursive_mergeSort(head);
        time_end=clock();        //截止时间
        time=difftime(time_end, time_start);
        
    }       //归并排序
    void recursive_mergeSort(Node* &sub_list); //归并排序的递归函数,注意用引用
    Node* divide_half(Node*sub_list);      //返回中间的指针
    Node* merge(Node* first,Node* second);
    void printList(){
        Node* first=head->next;
        while(first!=NULL)
        {
            first->data->Print();
            first=first->next;
        }
        cout<<"比较次数为："<<compare_count<<","<<"移动次数为："<<move_count<<"排序时间："<<difftime(time_end, time_start)<<"ms"<<endl;
    }

};

void list::insetionSort()
{
    time_start=clock();    //初始时间
    for(int i=1;i<count;i++)  //进行count-1次的循环
    {
        compar_count++;
        for(int j=0;j<=i;j++)
        {
            compar_count+=2;
            if(arry[i]<arry[j])
            {
                int temp=arry[i];  //存储数据
                for(int k=i;k>j;k--)
                {
                    compar_count++;
                    move_count++;       //移动数据
                    arry[k]=arry[k-1];
                }
                arry[j]=temp;
            }
        }
    }
    time_end=clock();     //结束时间
}

void list::selectionSort()
{
    time_start=clock();    //初始时间
    for(int i=0;i<count-1;i++)
    {
        compar_count++;
        int min=arry[i];
        int position=i;
        for(int j=i;j<count;j++)
        {
            compar_count++;
            if(min>arry[j])
            {
                min=arry[j];
                position=j;
            }
        }
        move_count+=2;
        int temp=arry[position];
        arry[position]=arry[i];
        arry[i]=temp;
    }
    time_end=clock();     //结束时间
}

void list::shellSort()
{
    time_start=clock();    //初始时间
    for(int increment=count/2;increment>0;increment/=2)
    {
        for(int i=0;i<increment;i++)
        {
            compar_count++;
            for(int j=i+increment;j<count;j+=increment)
            {
                compar_count++;
                int temp=arry[j];
                if(temp<arry[j-increment])
                {
                    compar_count++;
                    while (temp<arry[j-increment]&&j-increment>=0) {
                        compar_count++;
                        move_count++;
                        arry[j]=arry[j-increment];
                        j-=increment;
                    }
                    arry[j]=temp;
                }
            }
        }
    }
    time_end=clock();     //结束时间
}

void list::recursive_quickSort(int to_sort_first,int to_sort_last){
    int first=to_sort_first;
    int last=to_sort_last;
    compar_count++;
    if(first>=last)
        return ;
    int key=arry[to_sort_first];
    while (first<last) {
        compar_count+=3;
        move_count+=2;
        while (key<=arry[last]&&first<last) {
            last--;
        }
            arry[first]=arry[last];
        while (key>=arry[first]&&first<last) {
            first++;
        }
            arry[last]=arry[first];
    }
    move_count++;
    arry[first]=key;
    recursive_quickSort(to_sort_first, first-1);
    recursive_quickSort(first+1, to_sort_last);
}

void list::mergeSort(){
    time_start=clock();
    list*l=this;
    recursive_mergeSort(l);
    for(int i=0;i<l->count;i++){
        compar_count++;
        move_count+=2;
        int num;
        l->retrieve(i, num);
        this->setnum(i, num);
    }
    time_end=clock();
    time=difftime(time_end, time_start);
}

void list::recursive_mergeSort(list* &l){
    list *fir=new list(),*sec=new list();
    compar_count++;
    if(l->count>1){
        move_count+=2;
        for(int i=0;i<l->count/2;i++)      //两个循环把l里的指给fir和sec
            fir->setnum(i, l->arry[i]);
        for(int i=l->count/2;i<l->count;i++)
            sec->setnum(i-l->count/2, l->arry[i]);
        recursive_mergeSort(fir);
        recursive_mergeSort(sec);
        l=merge(fir,sec);
    }
}

list* list::merge(list*l1,list*l2){
    list* l=new list();
    int p1=0,p2=0,time=0;     //p1指l1的位置，p2指l2的位置,time记录l中加了多少个数
    int num1,num2;     //num1存l1的数，num2存l2的数
    while(p1<l1->count&&p2<l2->count){
        compar_count+=2;
        move_count+=2;
        l1->retrieve(p1, num1);
        l2->retrieve(p2, num2);
        if(num1<=num2){
            l->setnum(time, num1);
            time++;
            p1++;
        }
        else{
            l->setnum(time, num2);
            time++;
            p2++;
        }
    }
    compar_count+=2;
    if(p1==l1->count){
        for(int i=p2;i<l2->count;i++){
            compar_count++;
            move_count++;
            l2->retrieve(i, num2);
            l->setnum(time,num2);
            time++;
        }
    }
    else{
        for(int i=p1;i<l1->count;i++){
            compar_count++;
            move_count++;
            l1->retrieve(i, num1);
            l->setnum(time,num1);
            time++;
        }
    }
    return l;
}

void list::buildHeap(){
    for(int low=count/2-1;low>=0;low--){
        int current=arry[low];
        insertHeap(current, low, count-1);
    }
}

void list::insertHeap(int current,int low,int high){
    int large=low*2+1;
    while(large<=high){
        compar_count+=3;
        if(large+1<=high&&arry[large]<arry[large+1])
            large++;                      //到了这一步large一定是左右孩子最大的那一个
        if(current>=arry[large])         //若此次判断成立，直接break,current的位置不变
            break;
        else{
            move_count++;
            arry[low]=arry[large];        //否则左右孩子最大的那一个代替原来的low位置的current，low位置下移
            low=large;
            large=2*low+1;
        }
    }
    move_count++;
    arry[low]=current;
}

void list::heapSort(){
    time_start=clock();
    buildHeap();
    recursive_heapSort(0, count-1);
    time_end=clock();
    time=difftime(time_end, time_start);
}

void list::recursive_heapSort(int low,int high){
    if(high==low)
        return;
    int current=arry[high];
    arry[high]=arry[low];
    move_count+=2;
    insertHeap(current, low, high-1);
    recursive_heapSort(low, high-1);
}




void link_list::recursive_mergeSort(Node* &sub_list)
{
    compare_count++;
    if(sub_list->next!=NULL&&sub_list->next->next!=NULL){        //终止递归的条件
        Node*half_position=divide_half(sub_list);
        recursive_mergeSort(half_position);
        recursive_mergeSort(sub_list);
        sub_list=merge(sub_list,half_position);
    }
}

Node* link_list::divide_half(Node*sub_list){  //带有哑结点的二分法,n2移动的速度是n1的两倍
    Node *n1,*n2,*half_position=new Node();
    compare_count++;
    if(sub_list==NULL) return NULL;
    n1=sub_list;
    n2=sub_list;
    while(n2!=NULL){
        compare_count+=2;
        n2=n2->next;
        if(n2!=NULL){
            n1=n1->next;
            n2=n2->next;
        }
    }
    half_position->next=n1->next;
    n1->next=NULL;
    return half_position;     //返回一个哑结点
}

Node* link_list::merge(Node* first,Node* second){        //我们将返回first
    Node *firNode,*secNode,*last_sorted=first;
    firNode=first->next;
    secNode=second->next;
    while(firNode!=NULL&&secNode!=NULL){
        compare_count+=2;
        if(firNode->data->getData()<secNode->data->getData()){
            last_sorted->next=firNode;
            last_sorted=firNode;
            firNode=firNode->next;
        }
        else{
            last_sorted->next=secNode;
            last_sorted=secNode;
            secNode=secNode->next;
        }
    }
    compare_count++;
    if(firNode==NULL){
        last_sorted->next=secNode;
    }
    else{
        last_sorted->next=firNode;
    }
    return first;
}

void list::print()
{
    for(int i=0;i<count;i++)
        cout<<arry[i]<<" ";
    cout<<"比较次数为："<<compar_count<<","<<"移动次数为："<<move_count<<"排序时间："<<difftime(time_end, time_start)<<"ms"<<endl;
}




int main(int argc, const char * argv[]) {
    // insert code here...
    list l;
    srand((unsigned)time(NULL));
    for(int i=0;i<500;i++)
        l.insert(i, rand()%1000);
    
//    l.setnum(0, 2);
//    l.setnum(1, -1);
//    l.setnum(2, 3);
//    l.setnum(3, 6);
//    l.setnum(4, 0);
//    l.setnum(5, 10);

    //l.insetionSort();
    //l.selectionSort();
    //l.shellSort();
    //l.quickSort();
    l.mergeSort();
    //l.heapSort();
    l.print();
    link_list list;
//    for(int i=0;i<500;i++){
//        integer *pnum=new integer (rand()%1000);
//        Node*pnode=new Node(pnum);
//        list.addListHead(pnode);
//    }
//    list.mergeSort();
//    list.printList();
}
