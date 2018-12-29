class task{
    int num;
    double x,y;
    double step;
    digraph<int,10> lake;
    
  
public:
    void read();
    void run();
};

void task::read(){
    cout<<"请输入一步跨出的最大的距离：";
    cin>>step;
    lake.set_stepsize(step);
    cout<<"请输入有多少条鳄鱼：";
    cin>>num;
    for(int i=0;i<num;i++){
        cout<<"请输入鳄鱼"<<char('a'+i)<<"的坐标:";
        vertex *p_ver=new vertex();
        cin>>x>>y;
        object *p_obj=new object();
        p_obj->set(x, y);
        string str="";
        str+=char('a'+i);
        p_obj->lable=str;
        p_ver->data=p_obj;
        lake.add_vertex(p_ver);
    }
}
void task::run(){
    lake.update_related();
    lake.update();
    lake.update_weight_adjacency();
    lake.run();
}
