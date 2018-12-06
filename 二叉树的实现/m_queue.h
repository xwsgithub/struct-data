
#pragma once
#include<iostream>

using namespace std;
const int maxsize = 100;

template<typename T>
class m_queue
{
    int count, front, rear;
    T array[maxsize];
public:
    m_queue();
    void append(T entry);
    T server();
    void retrieve(T &entry_x);
    bool empty();
    int size();
    
    
};
template<typename T>
m_queue<T>::m_queue()
{
    count = 0;
    front = 0;
    rear = -1;
}
template<typename T>
void m_queue<T>::append(T entry)
{
    if (count >= maxsize - 1)
    {
        cout << "Overflow!!!";
    }
    else
    {
        rear = (rear + 1) % maxsize;
        array[rear] = entry;
        count++;
    }
}
template<typename T>
T m_queue<T>::server()
{
    if (count <= 0)
    {
        cout << "Underflow!!!";
        return array[0];
    }
    else
    {
        int temp = front;
        front = (front + 1) % maxsize;
        count--;
        return array[temp];
    }
}
template<typename T>
void m_queue<T>::retrieve(T&entry_x)
{
    if (count <= 0)
        cout << "Underflow!!!";
    else
        entry_x = array[front];
}
template<typename T>
bool m_queue<T>::empty()
{
    return (count > 0 ? false : true);
}
template<typename T>
int m_queue<T>::size(){
    return count;
}

