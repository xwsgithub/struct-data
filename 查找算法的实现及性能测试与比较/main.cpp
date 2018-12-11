#include <iostream>
#include<fstream>
#include "list.h"
#include "task.h"

using namespace std;

int main(){
    
    int length,find_time;
    task task;
    cout<<"请输入顺序组的长度以及需要查找的次数:";
    cin>>length>>find_time;
    task.run_first(length,find_time);
    task.run_second(length,find_time);
    return 0;
}






