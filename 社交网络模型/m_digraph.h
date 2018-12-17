#include"digraph.h"
const int graph_size=6;


class m_information: public information{
public:
    bool operator==(m_information info);
    m_information(string str);
};

class m_digraph:public digraph<int,graph_size>{
public:
    void update_weight_adjacency();
    int return_shorst_wight(m_information first_info,m_information sec_info);
};



bool m_information::operator==(m_information info){
    if(data==info.data)
        return true;
    else
        return false;
}
m_information::m_information(string str){
    data=str;
}

void m_digraph::update_weight_adjacency(){
    vertex *p_vr=root_vertex;
    for(int i=0;i<graph_size;i++){
        Edge *p_edge=p_vr->fisrt_edge;
        while (p_edge!=NULL) {
            weight_adjacency[i][p_edge->end_vertex->mark_number]=1;
            p_edge=p_edge->next_edge;
        }
        p_vr=p_vr->next_vertex;
    }
    for(int i=0;i<graph_size;i++){
        for(int j=0;j<graph_size;j++)
            if(weight_adjacency[i][j]!=1)
                weight_adjacency[i][j]=-1;
    }
}
int m_digraph::return_shorst_wight(m_information first_info,m_information sec_info){
    int distance[graph_size];      //存放权重的数组
    
    bool visited[graph_size];       //若dis[i]为最小，则visited[i]为true
    
    for(int i=0;i<graph_size;i++){
        distance[i]=-1;         //初始都为-1
        visited[i]=false;     //初始化为false
    }
    //寻找first_info和sec_info对应的vertex
    vertex *p_ver=root_vertex;
    int fir_mark=-1,sec_mark=-1;
    while(p_ver!=NULL){
        if(*(m_information*)(p_ver->info)==first_info)
            fir_mark=p_ver->mark_number;
        if(*(m_information*)(p_ver->info)==sec_info)
            sec_mark=p_ver->mark_number;
        p_ver=p_ver->next_vertex;
    }
    for(int i=0;i<graph_size;i++)
        distance[i]=weight_adjacency[fir_mark][i];     //将最开始的权重数组赋值过去
    visited[fir_mark]=true;
    
    for(int i=1;i<graph_size;i++){  //向visited加graph_size-1个结点
        int index=-1;
        int min_weight=-1;
        
        for(int j=0;j<graph_size;j++){
            if(!visited[j]){
                if(min_weight<0&&distance[j]>=0){    //小于0的数就认为是不同路，即无穷大
                    index=j;
                    min_weight=distance[j];
                }
                else if(min_weight>=0){
                    if(distance[j]>=0&&min_weight<distance[j]){
                        index=j;
                        min_weight=distance[j];
                    }
                }
            }
        }
        //走到这，新加的结点的mark为index
        visited[index]=true;
        for(int j=0;j<graph_size;j++){
            if(!visited[j]){
                if(distance[j]<0&&weight_adjacency[index][j]>=0)
                    distance[j]=min_weight+weight_adjacency[index][j];
                else if(weight_adjacency[index][j]>=0&&min_weight+weight_adjacency[index][j]<distance[j])
                    distance[j]=min_weight+weight_adjacency[index][j];
            }
            
        }
    }
    return distance[sec_mark];
}
