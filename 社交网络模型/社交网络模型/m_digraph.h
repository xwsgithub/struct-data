#include"digraph.h"
const int graph_size=4;


class m_information: public information{
public:
    bool operator==(m_information info);
    m_information(string str);
};

class m_digraph:public digraph<int,graph_size>{
public:
    void update_weight_adjacency();
};



bool m_information::operator==(m_information info){     //重载用户自己定义的等号
    if(data==info.data)
        return true;
    else
        return false;
}
m_information::m_information(string str){
    data=str;
}

void m_digraph::update_weight_adjacency(){     //更新权重邻接表
    vertex *p_vr=root_vertex;
    
    for(int i=0;i<graph_size;i++)
        for(int j=0;j<graph_size;j++)
                weight_adjacency[i][j]=-1;      //先全部初始化为-1
        
    for(int i=0;i<graph_size;i++){
        Edge *p_edge=p_vr->fisrt_edge;
        while (p_edge!=NULL) {
            if(p_edge->end_vertex->mark_number>=0)
                weight_adjacency[i][p_edge->end_vertex->mark_number]=1;
            p_edge=p_edge->next_edge;
        }
        p_vr=p_vr->next_vertex;
    }
}
