#include "m_list.h"

using namespace std;

enum Error_Code{success,fail};

class list:public m_list<int>{
    Error_Code recursive_binaryFind(int bottom,int top,int target);     //递归二分查找的递归部分
    time_t start_time,end_time;      //开始时间，结束时间
    int success_time,fail_time;          //成功，失败使用的时间
    long int suc_compare_cnt,fail_compare_cnt,temp_compare_count;      //成功，失败比较次数
    int success_amount,fail_amount;           //成功，失败的次数,用来算平均时间，平均比较次数
public:
    list();
    Error_Code createOrderList(int num); //初始化一个数量为num的有序顺序表
    Error_Code createRandomList(int num); //初始化一个数量为num的无序表
    Error_Code orderFind(int target);     //顺序查找
    Error_Code binaryFind(int target);    //非递归二分查找
    Error_Code recBinaryFind(int target);  //递归二分查找
    
    void success_update(int used_time);    //更新使用的时间
    void fail_update(int used_time);
    
    void printList_time_compare();    //打印时间和平均比较此事
    void prinstList_time();          //打印时间
};

list::list(){
    success_time=0;
    fail_time=0;
    suc_compare_cnt=0;
    fail_compare_cnt=0;
    count=0;
    success_amount=0;
    fail_amount=0;
}

Error_Code list::createOrderList(int num){
    if(num>10000)
        return fail;    //越界,m_list类里定义最大值为10000
    for(int i=0;i<num;i++){
        arry[i]=i;      //有序表定义每个数隔2
        count++;
    }
    return success;
}
Error_Code list::createRandomList(int num){
    if(num>10000)
        return fail;    //越界,m_list类里定义最大值为10000
    srand(unsigned(time(NULL)));
    for(int i=0;i<num;i++){
        arry[i]=rand()%num;      //随机数的范围为0-num-1
        count++;
    }
    return success;
}
Error_Code list::orderFind(int target){
    temp_compare_count=0;
    for(int i=0;i<count;i++){
        temp_compare_count++;
        if(arry[i]==target)
            return success;
    }
    return fail;
}
Error_Code list::binaryFind(int target){
    temp_compare_count=0;
    int bottom=0,top=count-1;
    while(bottom<top){
        temp_compare_count++;
        int mid=(bottom+top)/2;
        if(target>arry[mid]){
            bottom=mid+1;
        }
        else{              //因为target可能等于mid，所以top等于mid
            top=mid;
        }
    }
    if(top<bottom)
        return fail;
    else{                 //说明bottom和top撞到一起
        if(arry[bottom]==target)
            return success;
        else
            return fail;
    }
}
Error_Code list::recursive_binaryFind(int bomttom, int top, int target){
    if(bomttom>top)
        return fail;
    else if(bomttom==top){
        if(arry[bomttom]==target)
            return success;
        else
            return fail;
    }
    else{
        temp_compare_count++;
        int mid=(bomttom+top)/2;
        if(arry[mid]<target)
            return recursive_binaryFind(mid+1, top, target);
        else
            return recursive_binaryFind(bomttom, mid, target);
    }
}

Error_Code list::recBinaryFind(int target){
    temp_compare_count=0;
    return recursive_binaryFind(0, count-1, target);
}

void list::success_update(int used_time){
    success_time+=used_time;
    suc_compare_cnt+=temp_compare_count;
    success_amount++;
    
}
void list::fail_update(int used_time){
    fail_time+=used_time;
    fail_compare_cnt+=temp_compare_count;
    fail_amount++;
}
void list::printList_time_compare(){
    cout<<"查找成功所用的平均时间为："<<success_time*1.0/success_amount<<"ms   平均比较"<<suc_compare_cnt*1.0/success_amount<<"次"<<endl;
    cout<<"查找失败所用的平均时间为："<<fail_time*1.0/fail_amount<<"ms    平均比较"<<fail_compare_cnt*1.0/fail_amount<<"次"<<endl;
}

void list::prinstList_time(){
    cout<<"查找成功所用的平均时间为："<<success_time*1.0/success_amount<<"ms"<<endl;
    cout<<"查找失败所用的平均时间为："<<fail_time*1.0/fail_amount<<"ms"<<endl;
}

