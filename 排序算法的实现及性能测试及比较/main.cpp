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
#include <fstream>
#include <sstream>

void compare(string filename);

class list:public m_list<int>
{
    time_t time_start,time_end;        //记录时间
    int compar_count;                  //记录比较次数
    int move_count;                    //记录移动次数
    unsigned int time;
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
    void readData(string filename);       //读文件
    list()
    {
        compar_count=0;        //初始化为0
        move_count=0;
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
    time=difftime(time_end, time_start);
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
    time=difftime(time_end, time_start);
}

void list::shellSort()
{
    time_start=clock();    //初始时间
    for(int increment=count/2;increment>0;increment/=2)     //初始间隔为长度的一半，每次循环减少一半，直到间隔等于0终止循环
    {
        for(int i=0;i<increment;i++)
        {                                                      //将间隔为increment的数排序
            compar_count++;                                     //也就相当于把原来的插入排序间隔为1变成间隔为increment
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
    time=difftime(time_end, time_start);
}

void list::recursive_quickSort(int to_sort_first,int to_sort_last){
    int first=to_sort_first;
    int last=to_sort_last;
    compar_count++;
    if(first>=last)    //停止递归条件
        return ;
    int key=arry[to_sort_first];            //健值为要排序的位置的第一个
    while (first<last) {               // 只要first和last没有碰头，就一直循环
        compar_count+=3;
        move_count+=2;
        while (key<=arry[last]&&first<last) {   //若key小于后面的数以及first小于last，last便往前走
            last--;
        }
            arry[first]=arry[last];         //当循环结束的时候，说明有一个数比key小或者first和last碰面，当符合第一种情况时，将较小的数放在
        while (key>=arry[first]&&first<last) {    //first上，若符合第二种情况，结果也不变
            first++;                         //下面的同理
        }
            arry[last]=arry[first];
    }
    move_count++;       //当走出while循环后，说明first左边的数全是小于等于key的数，右边的数全是大于等于key的数
    arry[first]=key;
    recursive_quickSort(to_sort_first, first-1);    //进行递归
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

void list::print(){
//    for(int i=0;i<count;i++){
//        cout<<arry[i]<<" ";
//    }
    cout<<"比较次数为："<<compar_count<<" 移动次数为："<<move_count<<" 比较时间为："<<time<<"ms"<<endl;
}

void list::readData(string filename){
    ifstream in(filename);
    int pos=0;
    for(string str;getline(in,str);){
        stringstream sstr(str);
        int num;
        while(sstr>>num){
         this->setnum(pos, num);
            pos++;
        }
    }
}





int main(int argc, const char * argv[]) {
    // insert code here...
    cout<<"插入排序试验情况如下所示："<<endl;
    cout<<"排序数量为20时："<<endl;
    cout<<"顺序："<<endl;
    compare("/Users/xiongwei/Desktop/orded_less.txt");
    cout<<"逆序："<<endl;
    compare("/Users/xiongwei/Desktop/reverse_orded_less.txt");
    cout<<"随机数："<<endl;
    compare("/Users/xiongwei/Desktop/random_less.txt");
    cout<<"---------------------------------------------"<<endl;

    cout<<"排序数量为200时："<<endl;
    cout<<"顺序："<<endl;
    compare("/Users/xiongwei/Desktop/orded_midle.txt");
    cout<<"逆序："<<endl;
    compare("/Users/xiongwei/Desktop/reverse_orded_midle.txt");
    cout<<"随机数："<<endl;
    compare("/Users/xiongwei/Desktop/random_midle.txt");
     cout<<"---------------------------------------------"<<endl;

    cout<<"排序数量为2000时："<<endl;
    cout<<"顺序："<<endl;
    compare("/Users/xiongwei/Desktop/orded_large.txt");
    cout<<"逆序："<<endl;
    compare("/Users/xiongwei/Desktop/reverse_orded_large.txt");
    cout<<"随机数："<<endl;
    compare("/Users/xiongwei/Desktop/random_large.txt");
    

}


void compare(string filename){
    list l1;
    l1.readData(filename);
    l1.insetionSort();
    cout<<"插入排序：";
    l1.print();
    list l2;
    l2.readData(filename);
    l2.selectionSort();
    cout<<"选择排序：";
    l2.print();
    list l3;
    l3.readData(filename);
    l3.shellSort();
    cout<<"希尔排序：";
    l3.print();
    list l4;
    l4.readData(filename);
    l4.quickSort();
    cout<<"快速排序：";
    l4.print();
    list l5;
    l5.readData(filename);
    l5.mergeSort();
    cout<<"归并排序：";
    l5.print();
    list l6;
    l6.readData(filename);
    l6.heapSort();
    cout<<"堆排序";
    l6.print();
}
