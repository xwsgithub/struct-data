//本实验，对于两长整数相加相减相乘皆转化为两整数的运算
//即两负数相加相乘化为他们的绝对值相加再加个负号
//两负数相减化为两正数相减
//一正一负相加化为两正数相减
//一正一负相减化为两正数相加
//一正一负相乘化为两正数相乘再加一个负号


#include<iostream>
#include"m_list.h"
#include "Link_List.h"
#include "Circle_LInk_List.h"
#include<string>

using namespace std;

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

class m_int :public m_list<int>
{
    bool flag;        //记录这个数的正负，正为true，负为false，可变
    
    m_int add(m_int&temp);           //3个私有函数作为加减乘
    m_int minus(m_int&temp);
    m_int multiply(m_int&temp);
    
public:
    m_int(string num);
    m_int ();
    void set_num(int position, const int&x);       //在position位置插入一个数
    void add_num(int position, const int&x);       //在position后面加一个数
    bool judge(m_int temp) const;                  //判断两个长整数的大小
    m_int operator-( m_int &temp);
    m_int operator*( m_int &temp);
    m_int operator+( m_int&temp);
    void print();
};

m_int::m_int(){
    for(int i=0;i<101;i++)
        arry[i]=-1;
}

m_int::m_int(string num)    //把string化为一个m_int
{
    if(num[0]=='-'){
        flag=false;
        count=(int)num.size()-1;
        for(int i=1;i<num.size();i++)
            arry[i-1]=num[i]-'0';
        for(int i=(int)num.size();i<101;i++)
            arry[i]=-1;
    }
    else{
        flag=true;
        count=(int)num.size();
        for(int i=0;i<num.size();i++)
            arry[i]=num[i]-'0';
        for(int i=(int)num.size();i<101;i++)
            arry[i]=-1;
    }
}
m_int m_int::add(m_int&temp){
    m_int exist_int;
    int temp_num = 0;
    if (count <= temp.size())       //如果走这个if语句说明两个数同号
    {
        for (int i = count-1; i >=0; i--)
        {
            exist_int.set_num(temp.size() - count + i+1, (arry[i] + temp.arry[i+temp.size()-count] + temp_num) % 10);
            temp_num = (arry[i] + temp.arry[i+temp.size()-count]+temp_num) / 10;
        }
        for (int i = temp.size()-count; i >0; i--){
            exist_int.set_num(i, (temp.arry[i-1]+ temp_num) % 10);
            temp_num = (temp.arry[i-1] + temp_num) / 10;
        }
        exist_int.set_num(0, temp_num);
        exist_int.flag=(flag)?true:false;
        return exist_int;
    }
    else
    {
        for (int i = temp.size()-1; i >= 0; i--)
        {
            exist_int.set_num(-temp.size() + count + i+1, (arry[i+count-temp.size()] + temp.arry[i] + temp_num) % 10);
            temp_num = (arry[i+count-temp.size()] + temp.arry[i]+temp_num) / 10;
        }
        for (int i = count-temp.size(); i >0; i--){
            exist_int.set_num(i, (arry[i-1]+ temp_num) % 10);
            temp_num = (arry[i-1] + temp_num) / 10;
        }
        exist_int.set_num(0, temp_num);
        exist_int.flag=(flag)?true:false;
        return exist_int;
    }
}

m_int m_int:: minus(m_int&temp){
    m_int exist_int;
    int temp_num = 0;           //temp_num为借位
    if (judge(temp))                 //若judge为true，说明被减数大于减数
    {
        for (int i = temp.size() - 1; i >= 0; i--)
        {
            if (arry[i + count - temp.size()]+temp_num >= temp.arry[i])
            {
                exist_int.set_num(i + count - temp.size(), arry[i + count - temp.size()]+temp_num - temp.arry[i]);
                temp_num = 0;
            }
            else
            {
                exist_int.set_num(i + count - temp.size(), arry[i + count - temp.size()] +10 +temp_num - temp.arry[i]);
                temp_num = -1;
            }
        }
        for (int i = count-temp.size()-1; i >=0; i--)
        {
            if (arry[i] + temp_num < 0)
            {
                exist_int.set_num(i, arry[i] + 10+temp_num);
                temp_num = -1;
            }
            else
            {
                exist_int.set_num(i, arry[i]+temp_num);
                temp_num = 0;
            }
        }
        exist_int.flag=true;
        return exist_int;
    }
    else
    {
        exist_int.flag=false;
        for (int i = count - 1; i >= 0; i--)                       //如果只进行这个循环说明是同位相减
        {
            if (arry[i] <= temp.arry[i+temp.size()-count]+temp_num)
            {
                exist_int.set_num(i - count + temp.size(), -arry[i] + temp_num + temp.arry[i+temp.size()-count]);
                temp_num = 0;
            }
            else
            {
                exist_int.set_num(i - count + temp.size(), -arry[i] + 10 + temp_num + temp.arry[i+temp.size()-count]);
                temp_num = -1;
            }
        }
        for (int i = -count + temp.size() - 1; i >= 0; i--)
        {
            if (temp.arry[i] + temp_num < 0)
            {
                exist_int.set_num(i, temp.arry[i] + 10 - temp_num);
                temp_num = -1;
            }
            else if(i!=0)
            {
                exist_int.set_num(i, temp.arry[i]+temp_num);
                temp_num = 0;
            }
            else
            {
                exist_int.set_num(i, temp.arry[i]+temp_num);
            }
        }
        return exist_int;
    }
}

m_int m_int::multiply(m_int&temp){
    m_int exist_int;
    int temp_num = 0;
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < temp.size(); j++)
        {
            exist_int.add_num(i + j + 1, arry[i] * temp.arry[j]);
        }
    }
    for (int i = count+temp.size(); i >= 1; i--)
    {
        int temp = exist_int.arry[i];
        if (temp+temp_num > 9)
        {
            exist_int.set_num(i, (exist_int.arry[i]+temp_num) % 10);
        }
        else{
            exist_int.set_num(i, exist_int.arry[i]+temp_num);
        }
        temp_num = (temp + temp_num) / 10;
    }
    if (exist_int.arry[1] > 9)
    {
        exist_int.set_num(0, temp_num);
        exist_int.flag=(flag==temp.flag)?true:false;
        return exist_int;
    }
    else
    {
        for (int i = 0; i < exist_int.size(); i++)
        {
            exist_int.arry[i] = exist_int.arry[i + 1];
        }
         exist_int.flag=(flag==temp.flag)?true:false;
        return exist_int;
    }
    
}



void m_int::set_num(int position, const int&x)
{
    arry[position] = x;
    count++;
}

void m_int::add_num(int position, const int&x)    //吧x加到position位置上
{
    if (arry[position] == -1)
    {
        arry[position] = x;
        count++;
    }
    else
        arry[position] += x;
}

bool m_int::judge(m_int temp) const
{
    if(count>temp.size())
        return true;
    else if(count==temp.size()){
        for(int i=0;i<count;i++){
            if(arry[i]>temp.arry[i])
                return true;
            else if(arry[i]<temp.arry[i])
                return false;
        }
    }
    return false;
}




m_int m_int::operator+(m_int&temp)        //加法所用的原理是小学时加法的原理
{
    m_int exist_int;
    if(flag&&!temp.flag){     //说明一个正数加一个负数
        return minus(temp);
    }
    else if(!flag&&temp.flag){   //说明一个负数加一个正数
        return temp.minus(*this);
    }
    return add(temp);
}

m_int m_int::operator-(m_int&temp)         //减法同理
{
    if(flag&&!temp.flag){    //一正一负相减
        return add(temp);
    }
    else if(!flag&&temp.flag){   //一负一正相减
        return add(temp);
    }
    else if(!flag&&!temp.flag){    //两负数相减
        return temp.minus(*this);
    }
    return minus(temp);
}

m_int m_int::operator*(m_int&temp)           //乘法也适用小学乘法原理
{
    return multiply(temp);
}

void m_int::print()
{
    int count=0;        //记下非零的第一位
    while(!arry[count])
        count++;
    if(arry[count]<0)
        cout<<0;
    else{
        if(!flag)
            cout<<'-';
        for(int i=count;arry[i]>=0;i++)
            cout<<arry[i];
    }
}

int main()
{
    m_int C,D,E;
    cout << "请输入两个数：";
    string num;
    cin >> num;
    m_int A(num);
    cin >> num;
    m_int B(num);
    E = A * B;
    C = A + B;
    D = A - B;
    cout<<"两数相加得：";
    C.print();
    cout << endl;
    cout<<"两数相减得：";
    D.print();
    cout << endl;
    cout<<"两数相乘得：";
    E.print();
    cout<<endl;
    cout<<"---------------------------"<<endl<<"下方为链表实验区域："<<endl;
    Link_List list;
    for(int i=0;i<9;i++){
        integer *pnum=new integer (i);
        Node*pnode=new Node(pnum);
        list.addListHead(pnode);
    }
    list.printList();
    cout<<"数据加载成功，输出成功！"<<endl<<"长度为："<<list.getLength()<<endl;
    
    if(!list.isEmpty())
        cout<<"链表不为空"<<endl;
}
