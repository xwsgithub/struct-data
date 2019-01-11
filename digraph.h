#include <iostream>
#include <string>
#include <cmath>
#include <ctime>

using namespace std;

class object{
public:
    int count;        //记录关联的标签有多少个
    string lable;
    string related_lale[100];        //最大关联的标签暂定为100个。。。
    object(string str);
    object();
    void set_lated(string str);
    double x;        //新增坐标 x,y
    double y;
    void set(double m_x,double m_y);
};      //object类里添加两个比较基础的变量，标签和与他有关的标签数组

object::object(string str){
    lable=str;
    count=0;
}
object::object(){
    count=0;
}

void object::set(double m_x,double m_y){
    x=m_x;
    y=m_y;
}

void object::set_lated(string str){
    related_lale[count]=str;
    count++;
}

class information{   //这个类将被用户继承，即通过什么能决定两个结点是否是同一个节点
protected:
    string data;
public:
    bool operator==(information info);
    
};
bool information::operator==(information info){
    return (data==info.data)? true:false;
}



class Edge;

class vertex{     //顶点类
public:
    vertex();
    int mark_number;          //标记这是第几号结点，方便于后面的权重邻接矩阵
    vertex *next_vertex;      //next无实际意义，可以理解为按编号排，0，1，2，3，4，5
    Edge *fisrt_edge;         //该结点关联的一条边
    object *data;             //该节点的一个标签以及和它关联的标签，可用来继承存数据
    information *info;        //为判断这个结点的关键信息，因为有时候不方便通过data来判断是不是一个结点，data的信息可能
};                            //过于复杂，可能我们只需要其中的一些信息便能b判断是不是同一个
vertex::vertex(){
    data=new object();
}

class Edge{
public:
    vertex *end_vertex;
    Edge *next_edge;      //next_edge为最开始结点关联的另一条边，next并无顺序关系，边的链表为并列关系，一个顶点包含一个边链表
    //里面都是它关联的边
};

template<class Weight,int graph_size>    //Weight根据用户自己的需求用户自定义
class digraph{    //有向图
protected:
    int count;        //拥有的结点数
    vertex *root_vertex;     //随便的一个根结点
    Weight weight_adjacency[graph_size][graph_size];       //权重邻接矩阵
    void update_ver(vertex* ver);      //更新邻接表中的某个结点，用于辅导下面的update函数
    bool is_neighbor(vertex *v1,vertex *v2);
    int path_vertex[graph_size];    //存放对应marknumber对应最短路径的上一个结点的marknumber
    vertex* get_vertex_by_marknumber(int mark_number);     //给定mark_number，返回对应的结点
    vertex* p_in;
    vertex* p_out;
public:
    
    digraph();
    void add_vertex(vertex *ver);      //增加结点
    void update();        //更新整个图
    void print();        //打印
    void update_weight_adjacency(); //更新权重邻接矩阵,这个根据各种情况来定，所以用虚函数
    Weight return_shorst_wight(vertex *first_ver,vertex *sec_ver);
    void update_related();
    void run();
};

template<class Weight,int graph_size>
vertex* digraph<Weight, graph_size>::get_vertex_by_marknumber(int mark_number){
    vertex* p_ver=root_vertex;
    while(p_ver!=NULL){
        if(p_ver->mark_number==mark_number)
            return p_ver;
        p_ver=p_ver->next_vertex;
    }
    return root_vertex;
}

template<class Weight,int graph_size>
digraph<Weight, graph_size>::digraph(){
    
    root_vertex=NULL;      //初始化指向空节点
    count=0;
    for(int i=0;i<graph_size;i++){
        path_vertex[i]=-1;     //全部初始化为NULL
    }
    
}


template<class Weight,int graph_size>
bool digraph<Weight, graph_size>::is_neighbor(vertex *p_v1, vertex *p_v2){          //给定两个结点，判断是否相邻
    if(abs(p_v1->data->x-p_v2->data->x)<=1&&abs(p_v1->data->y-p_v2->data->y)<=1){
        p_v1->data->set_lated(p_v2->data->lable);
        p_v2->data->set_lated(p_v1->data->lable);
        return true;
    }
    return false;
}
template<class Weight,int graph_size>
void digraph<Weight, graph_size>::update_related(){
    vertex* p_ver=root_vertex;
    for(int i=1;i<graph_size;i++){
        vertex* temp_vertex=p_ver->next_vertex;
        for(int j=i;j<graph_size;j++){
            if(temp_vertex!=NULL){
                is_neighbor(p_ver,temp_vertex);
                temp_vertex=temp_vertex->next_vertex;
            }
        }
        p_ver=p_ver->next_vertex;
        if(p_ver==NULL)
            break;
        
    }

    
}


template<class Weight,int graph_size>
void digraph<Weight,graph_size>::add_vertex(vertex *ver){
    if(root_vertex==NULL){     //原图为空的情况
        root_vertex=new vertex();
        *root_vertex=*ver;
        root_vertex->next_vertex=NULL;
        ver->mark_number=count++;     //第0号元素
        return ;
    }
    
    vertex *p_vertex=root_vertex;
    while (p_vertex->next_vertex!=NULL)      //找到下一个结点为空的结点
        p_vertex=p_vertex->next_vertex;
    vertex *new_p=new vertex();
    *new_p=*ver;
    new_p->mark_number=count++;
    p_vertex->next_vertex=new_p;
    new_p->next_vertex=NULL;
}

template<class Weight,int graph_size>
void digraph<Weight,graph_size>::update_ver(vertex* ver){
    if(ver->data->x==0&&ver->data->y==0)    //把起点和终点确定
        p_in=ver;
    if(ver->data->x==7&&ver->data->y==7)
        p_out=ver;
    if(ver->data->count==0)    //如果没有邻接的结点，直接pass
    {
        ver->fisrt_edge=NULL;
        return;
        
    }
    Edge *fir_ed=new Edge();    //先把first_edge与结点连接起来
    
    vertex *p_ver=root_vertex;
    
    while(p_ver!=NULL&&p_ver->data->lable!=ver->data->related_lale[0]){   //退出循环有两种情况，一是找到了，而是所有结点
        p_ver=p_ver->next_vertex;                                         //都没有这个标签
    }
    if(p_ver==NULL){                       //说明没有这个标签,这时候得创个新结点
        vertex *new_p=new vertex();
        new_p->data->lable=ver->data->related_lale[0];
        new_p->mark_number=-1;           //若没有这个标签，把它的mark_number标为-1，这种做法有失妥当。。
        fir_ed->end_vertex=new_p;
    }
    else{
        fir_ed->end_vertex=p_ver;
        
    }
    fir_ed->next_edge=NULL;
    ver->fisrt_edge=fir_ed;
    
    Edge *p_ed=ver->fisrt_edge;   //找到first_edge，往下迭代
    
    for(int i=1;i<ver->data->count;i++){   //因为已经连了一条边，所以i从1开始
        Edge *ed=new Edge();
        
        vertex *p_ver=root_vertex;        //下面的操作和上面的几乎一模一样
        
        while(p_ver!=NULL&&p_ver->data->lable!=ver->data->related_lale[i]){   //退出循环有两种情况，一是找到了，而是所有结点
            p_ver=p_ver->next_vertex;                                         //都没有这个标签
        }
        if(p_ver==NULL){                       //说明没有这个标签,这时候得创个新结点
            vertex *new_p=new vertex();
            new_p->data->lable=ver->data->related_lale[i];
            ed->end_vertex=new_p;
        }
        else{
            ed->end_vertex=p_ver;
            
        }
        ed->next_edge=NULL;
        p_ed->next_edge=ed;
        p_ed=ed;
        
    }
}

template<class Weight,int graph_size>
void digraph<Weight,graph_size>::update(){
    vertex *p_vr=root_vertex;
    
    for(int i=0;i<graph_size;i++){
        update_ver(p_vr);
        p_vr=p_vr->next_vertex;
        if(p_vr==NULL)
            break;
    }
    
}


template<class Weight,int graph_size>
void digraph<Weight,graph_size>::print(){
    vertex *p_vr=root_vertex;
    for(int i=0;i<graph_size;i++){
        cout<<"第"<<i<<"个结点的标签为："<<p_vr->data->lable<<",与它有关的标签为："<<endl;
        for(int j=0;j<p_vr->data->count;j++)
            cout<<p_vr->data->related_lale[j]<<" ";
        p_vr=p_vr->next_vertex;
        if(p_vr==NULL)
            break;
    }
}



template<class Weight,int graph_size>
Weight digraph<Weight,graph_size>::return_shorst_wight(vertex *first_ver,vertex *sec_ver){
    int distance[graph_size];      //存放权重的数组
    bool visited[graph_size];       //若dis[i]为最小，则visited[i]为true
    
    for(int i=0;i<graph_size;i++){
        distance[i]=-1;         //初始都为-1
        visited[i]=false;     //初始化为false
    }
    //寻找first_info和sec_info对应的vertex
    int fir_mark=-1,sec_mark=-1;
    fir_mark=first_ver->mark_number;
    sec_mark=sec_ver->mark_number;
    for(int i=0;i<graph_size;i++){
        if(weight_adjacency[fir_mark][i]!=-1)
            path_vertex[i]=fir_mark;             //若可达，则进行第一次赋值
        distance[i]=weight_adjacency[fir_mark][i];     //将最开始的权重数组赋值过去
        
    }
    visited[fir_mark]=true;
    
    for(int i=1;i<graph_size;i++){  //向visited加graph_size-1个结点
        int index=-1;
        int min_weight=-1;
        
        for(int j=0;j<graph_size;j++){
            if(!visited[j]){
                if(min_weight<0&&distance[j]>=0){    //小于0的数就认为是断路，即无穷大
                    index=j;
                    min_weight=distance[j];
                }
                else if(min_weight>=0){
                    if(distance[j]>=0&&min_weight>distance[j]){
                        index=j;
                        min_weight=distance[j];
                    }
                }
            }
        }
        //走到这，新加的结点的mark为index,如果index为-1，说明它到下面未加入visited的结点的距离为无穷
        if(index==-1)
            return distance[sec_mark];
        visited[index]=true;
        vertex *root=root_vertex;
        for(int i=0;i<graph_size;i++){
            if(root->mark_number==index)
                break;
            else
                root=root->next_vertex;     //找到index所对应的顶点
        }
        for(int j=0;j<graph_size;j++){
            if(!visited[j]){
                if(distance[j]<0&&weight_adjacency[index][j]>=0){
                    distance[j]=min_weight+weight_adjacency[index][j];
                    path_vertex[j]=index;
                }
                else if(weight_adjacency[index][j]>=0&&min_weight+weight_adjacency[index][j]<distance[j]){
                    distance[j]=min_weight+weight_adjacency[index][j];
                    path_vertex[j]=index;
                }
            }
            
        }
    }
    return distance[sec_mark];
}

template<class Weight,int graph_size>
void digraph<Weight,graph_size>::update_weight_adjacency(){
    vertex *p_vr=root_vertex;
    for(int i=0;i<graph_size;i++)
        for(int j=0;j<graph_size;j++){
            if(i!=j)
                weight_adjacency[i][j]=-1;      //先全部初始化为-1
            else
                weight_adjacency[i][j]=0;
        }
    
    for(int i=0;i<graph_size;i++){
        Edge *p_edge=p_vr->fisrt_edge;
        while (p_edge!=NULL) {
            if(p_edge->end_vertex->mark_number>=0)
                weight_adjacency[i][p_edge->end_vertex->mark_number]=1;
            p_edge=p_edge->next_edge;
        }
        p_vr=p_vr->next_vertex;
        if(p_vr==NULL)
            break;
    }
}
template<class Weight,int graph_size>
void digraph<Weight,graph_size>::run(){
    if(return_shorst_wight(p_in, p_out)<0){     //如果路径长度小于0就说明没有出路
        cout<<"没有出路"<<endl;
        return ;
    }
    int in_number=p_in->mark_number;
    int out_number=p_out->mark_number;
    vertex* temp[graph_size];
    for(int i=0;i<graph_size;i++){
        temp[i]=NULL;
    }
    int count=0;
    while(true){
        temp[count++]=get_vertex_by_marknumber(out_number);
        out_number=path_vertex[out_number];
        if(out_number==in_number){   //直到找到了出口，终止循环
            if(temp[count-1]!=get_vertex_by_marknumber(out_number))
                temp[count++]=get_vertex_by_marknumber(out_number);
            break;
        }
    }
    cout<<"出去的路为：";
    for(int i=count-1;i>=0;i--){
        cout<<'('<<temp[i]->data->x<<','<<temp[i]->data->y<<')'<<' ';
    }
}

