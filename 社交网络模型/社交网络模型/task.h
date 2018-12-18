#include"m_digraph.h"
int people_num;
class task{
    m_digraph graph;
public:
    void read();
    void run();
};
void task::read(){
    string name,related_name;
    int related_num;
    cout<<"请输入人的个数：";
    cin>>people_num;
    for(int i=0;i<people_num;i++){
        cout<<"请输入人的昵称,及与他相关的人的个数：";
        cin>>name>>related_num;
        object *ob=new object(name);
        cout<<"请输入与他相关人的名字：";
        for (int i=0;i<related_num;i++) {
            cin>>related_name;
            ob->set_lated(related_name);
        }
        vertex *p_ve=new vertex();
        m_information *p_info=new m_information(name);
        p_ve->info=p_info;
        p_ve->data=ob;
        graph.add_vertex(*p_ve);
    }
    graph.update();
    graph.update_weight_adjacency();
}
void task::run(){
    string fir_name,sec_name;
    cout<<"输入 # #结束"<<endl;
    while(true){
        cout<<"请输入这两人的名字：";
        cin>>fir_name>>sec_name;
        if(fir_name+sec_name=="##")
            break;
        m_information info1(fir_name);
        m_information info2(sec_name);
        if(graph.return_shorst_wight(&info1, &info2)<0)
            cout<<"没有联系！"<<endl;
        else
            cout<<"至少经过"<<graph.return_shorst_wight(&info1, &info2)<<"个人构成联系"<<endl;
    }
}

