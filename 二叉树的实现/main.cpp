
#include <iostream>
#include "m_queue.h"
#include"BinTree.h"

using namespace std;
void help();

void print(char& ch)
{
    cout<<ch;
}
int main() {
    
    help();
}
void help(){
    BinTree bt;
    bool flag=true;
    cout<<"请根根据下列功能输入相对应的数字："<<endl;
    while(flag){
        cout<<"1.按照前序遍历的方法将一个字符串插进去 "<<"2.前序遍历输出 "<<"3.中序遍历输出 "<<"4.后序遍历输出 "<<endl;
        cout<<"5.树的深度 "<<"6.树的高度 "<<"7.度为0的节点数 "<<"8.度为1的节点数 "<<"9.度为2的节点数"<<"10.插入一个字符 "<<"11.删除对应键值的节点 "<<"12.查找节点 "<<"13.退出 "<<endl;
        int num;
        cin>>num;
        switch (num) {
            case 1:{
                cout<<"请输入一个字符串";
                string str;
                cin>>str;
                bt.create(str);
            }
                break;
            case 2:{
                bt.preOrder(print);
                cout<<endl;
            }
                break;
            case 3:{
                bt.midOrder(print);
                cout<<endl;
            }
                break;
            case 4:{
                bt.postOrder(print);
                cout<<endl;
            }
                break;
            case 5:{
                cout<<endl<<bt.getHeight()<<endl;
            }
                break;
            case 6:{
                cout<<endl<<bt.getWidth()<<endl;
            }
                break;
            case 7:{
                cout<<endl<<bt.getNumberOfNoun(0)<<endl;
            }
                break;
            case 8:{
                cout<<endl<<bt.getNumberOfNoun(1)<<endl;
            }
                break;
            case 9:{
                cout<<endl<<bt.getNumberOfNoun(2)<<endl;
            }
                break;
            case 10:{
                cout<<"请输入一个字符:";
                char ch;
                cin>>ch;
                bt.insert(ch);
            }
                break;
            case 11:{
                cout<<"请输入要删除对应节点的键值：";
                char ch;
                cin>>ch;
                bt.deleteNode(ch);
            }
                break;
            case 12:{
                cout<<"请输入要查找的键值：";
                char ch;
                cin>>ch;
                cout<<boolalpha<<bt.findNode(ch)<<endl;
            }
                break;
            case 13:{
                flag=false;
            }
                break;
            default:{
                cout<<"请输入正确的序列号"<<endl;
            }
                break;
        }
    }
    
}

