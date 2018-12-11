class task{
public:
    void run_first(int length,int find_time){
        srand((unsigned)time(NULL));
        list order_list,rand_list;
        time_t start,end;
        order_list.createOrderList(length);       //初始化
        rand_list.createOrderList(length);
        for(int i=0;i<find_time;i++){
            start=clock();
            if(order_list.orderFind(rand()%(2*length))==success){
                end=clock();
                order_list.success_update(difftime(end, start));
            }
            else{
                end=clock();
                order_list.fail_update(difftime(end, start));
            }
            
            
            start=clock();
            if(rand_list.orderFind(rand()%(2*length))==success){
                end=clock();
                rand_list.success_update(difftime(end, start));
            }
            else{
                end=clock();
                rand_list.fail_update(difftime(end, start));
            }
        }
        cout<<"有序表："<<endl;
        order_list.printList_time_compare();
        cout<<"无序表："<<endl;
        rand_list.printList_time_compare();
        
    }
    
    void run_second(int length,int find_time){
        srand((unsigned)time(NULL));
        list order_list;
        time_t start,end;
        order_list.createOrderList(length);
        list order_list2=order_list,order_list3=order_list;
        for(int i=0;i<find_time;i++){
            int temp_num=rand()%(2*length);
            start=clock();
            if(order_list.orderFind(temp_num)==success){
                end=clock();
                order_list.success_update(difftime(end, start));
            }
            else{
                end=clock();
                order_list.fail_update(difftime(end, start));
            }
            start=clock();
            if(order_list2.binaryFind(temp_num)==success){
                end=clock();
                order_list2.success_update(difftime(end, start));
            }
            else{
                end=clock();
                order_list2.fail_update(difftime(end, start));
            }
            start=clock();
            if(order_list3.recBinaryFind(temp_num)==success){
                end=clock();
                order_list3.success_update(difftime(end, start));
            }
            else{
                end=clock();
                order_list3.fail_update(difftime(end, start));
            }
        }
        cout<<"顺序查找："<<endl;
        order_list.prinstList_time();
        cout<<"非递归二分查找："<<endl;
        order_list2.prinstList_time();
        cout<<"递归二分查找："<<endl;
        order_list3.prinstList_time();
    }

    
};
