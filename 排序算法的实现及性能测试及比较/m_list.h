#pragma once
#include<iostream>

using namespace std;

template<typename T>
class m_list
{
protected:
    T arry[1000];
    int count;
public:
    m_list();
    ~m_list();
    int size() const;
    bool full() const;
    bool empty() const;
    void clear();
    void traverse(void(*visit)(T &));
    void retrieve(int position, T&x) const;
    void replace(int poisition, const T&x);
    void remove(int position, T&x);
    void insert(int position, const T&x);
    
};

template<typename T>
m_list<T>::m_list()
{
    count = 0;
}
template<typename T>
m_list<T>::~m_list()
{
}
template<typename T>
int m_list<T>::size() const
{
    return count;
}
template<typename T>
bool m_list<T>::full() const
{
    return(count == 100 ? true : false);
}
template<typename T>
bool m_list<T>::empty() const
{
    return (count == 0 ? true : false);
}
template<typename T>
void m_list<T>::clear()
{
    count = 0;
}
template<typename T>
void m_list<T>::traverse(void(*visit)(T &))
{
    for (int i = 0; i < count; i++)
        (*visit)(arry[i]);
}
template<typename T>
void m_list<T>::retrieve(int position, T&x) const
{
    if (position < count&&position >= 0)
        x = arry[position];
    else
        cout << "Error: Retrieve out of range";
}
template<typename T>
void m_list<T>::replace(int poisition, const T&x)
{
    if (poisition < count&&poisition >= 0)
    {
        arry[poisition] = x;
    }
    else
        cout << "Error: Replace out of range";
}
template<typename T>
void m_list<T>::remove(int position, T&x)
{
    x = arry[position];
    for (int i = position; i < count; i++)
    {
        arry[position] = arry[position + 1];
        if (i == position - 1)
            break;
    }
    count--;
}
template<typename T>
void m_list<T>::insert(int position, const T&x)
{
    count++;
    for (int i = count; i > position; i--)
    {
        arry[i] = arry[i - 1];
    }
    arry[position] = x;
}

