#include<fstream>
#include"list.h"



class task{
public:
    
    void compare(string filename);
    void help();
};
void task::compare(string filename){
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
void task::help(){
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
