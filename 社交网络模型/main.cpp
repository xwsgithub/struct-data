#include "m_digraph.h"


//开始输入多个人的信息，在这里我们输入人名和他认识的人，之后根据输入的两个人的名字来找到最短路径，而每条边的Weight为1

int main(){
    
    m_digraph graph;
    string name,related_name;
    int num;
    for(int i=0;i<6;i++){
        cout<<"请输入人的昵称,及与他相关的人的个数：";
        cin>>name>>num;
        object *ob=new object(name);
        cout<<"请输入与他相关人的名字：";
        for (int i=0;i<num;i++) {
            cin>>related_name;
            ob->set_lated(related_name);
        }
        vertex ve;
        ve.info=new m_information(name);
        ve.data=ob;
        graph.add_vertex(ve);
    }
    graph.update();
    graph.update_weight_adjacency();
    //graph.print();
    m_information info1("a");
    m_information info2("d");
    m_information info3("f");
    cout<<"a到b的最短路径为："<<graph.return_shorst_wight(info1, info2)<<endl;
    
    cout<<"d到f的最短路径为："<<graph.return_shorst_wight(info2, info3);
    
    
    
}
