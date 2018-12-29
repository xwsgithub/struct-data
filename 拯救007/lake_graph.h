//#include"digraph.h"
//#include <cmath>
//const int crocodile_size=4;
//
//
//class m_object:public object{
//public:
//    double x;        //新增坐标 x,y
//    double y;
//public:
//    void set(float x,float y);
//};
//
//void m_object::set(float x, float y){
//    x=x;
//    y=y;
//}
//
//class m_vertex:public vertex{
//public:
//    m_object *m_data;
//};
//
//class lake_graph: public digraph<int,crocodile_size>{
//    double step_size;    //一步跨出的最大距离
//    vertex out_vertex[crocodile_size];   //能够出去的鳄鱼
//    vertex in_vertex[crocodile_size];    //起始点的鳄鱼
//    bool is_neighbor(m_vertex *v1,m_vertex *v2);
//public:
//    void update_related();
//    virtual void update_weight_adjacency();
//    void set_stepsize(double num);
//};
//
//void lake_graph::set_stepsize(double num){
//    step_size=num;
//}
//
//void lake_graph::update_related(){
//    vertex* p_ver=root_vertex;
//    for(int i=1;i<crocodile_size;i++){
//        is_neighbor((m_vertex*)p_ver,(m_vertex*)p_ver->next_vertex);
//        p_ver=p_ver->next_vertex;
//    }
//}
//
//
//bool lake_graph::is_neighbor(m_vertex *p_v1, m_vertex *p_v2){          //给定两个结点，判断是否相邻
//    if(pow(pow(p_v1->m_data->x-p_v2->m_data->x,2)+pow(p_v1->m_data->y-p_v2->m_data->y,2),0.5)<=step_size){
//        p_v1->m_data->set_lated(p_v2->m_data->lable);
//        p_v2->m_data->set_lated(p_v1->m_data->lable);
//        return true;
//    }
//    return false;
//}
//void lake_graph::update_weight_adjacency(){
//    vertex *p_vr=root_vertex;
//    for(int i=0;i<crocodile_size;i++)
//        for(int j=0;j<crocodile_size;j++)
//            weight_adjacency[i][j]=-1;      //先全部初始化为-1
//
//    for(int i=0;i<crocodile_size;i++){
//        Edge *p_edge=p_vr->fisrt_edge;
//        while (p_edge!=NULL) {
//            if(p_edge->end_vertex->mark_number>=0)
//                weight_adjacency[i][p_edge->end_vertex->mark_number]=1;
//            p_edge=p_edge->next_edge;
//        }
//        p_vr=p_vr->next_vertex;
//    }
//}
