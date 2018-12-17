#include <iostream>
#include <string>

using namespace std;

class object{
public:
    int count;        //记录关联的标签有多少个
    string lable;
    string related_lale[100];        //最大关联的标签暂定为100个。。。
    object(string str);
    void set_lated(string str);
};      //object类里添加两个比较基础的变量，标签和与他有关的标签数组

object::object(string str){
    lable=str;
    count=0;
}

void object::set_lated(string str){
    related_lale[count]=str;
    count++;
}

class information{   //这个类将被用户继承，即通过什么能决定两个结点是否是同一个节点
protected:
    string data;
};



class Edge;

class vertex{     //顶点类
public:
    int mark_number;          //标记这是第几号结点，方便于后面的权重邻接矩阵
    vertex *next_vertex;      //next无实际意义，可以理解为按编号排，0，1，2，3，4，5
    Edge *fisrt_edge;         //该结点关联的一条边
    object *data;
    information *info;        //为判断这个结点的关键信息，因为有时候不方便通过data来判断是不是一个结点，data的信息可能
};                            //过于复杂，可能我们只需要其中的一些信息便能b判断是不是同一个

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
public:
    
    digraph();
    void add_vertex(vertex ver);      //增加结点
    void update();        //更新整个图
    void print();        //打印
    virtual void update_weight_adjacency()=0; //更新权重邻接矩阵,这个根据各种情况来定，所以用虚函数
    //Weight return_shorst_wight(information first_info,information sec_info);    //返回最短权重之和
    
};

template<class Weight,int graph_size>
digraph<Weight, graph_size>::digraph(){
    
    root_vertex=NULL;      //初始化指向空节点
    count=0;
    
}

template<class Weight,int graph_size>
void digraph<Weight,graph_size>::add_vertex(vertex ver){
    
    if(root_vertex==NULL){     //原图为空的情况
        root_vertex=new vertex();
        *root_vertex=ver;
        root_vertex->next_vertex=NULL;
        ver.mark_number=count++;     //第0号元素
        return ;
    }
    
    vertex *p_vertex=root_vertex;
    while (p_vertex->next_vertex!=NULL)      //找到下一个结点为空的结点
        p_vertex=p_vertex->next_vertex;
    vertex *new_p=new vertex();
    *new_p=ver;
    new_p->mark_number=count++;
    p_vertex->next_vertex=new_p;
    new_p->next_vertex=NULL;
}

template<class Weight,int graph_size>
void digraph<Weight,graph_size>::update_ver(vertex* ver){
    if(ver->data->count==0)    //如果没有邻接的结点，直接pass
        return;
    Edge *fir_ed=new Edge();    //先把first_edge与结点连接起来
    
    vertex *p_ver=root_vertex;
    
    while(p_ver->data->lable!=ver->data->related_lale[0]&&p_ver!=NULL){   //退出循环有两种情况，一是找到了，而是所有结点
        p_ver=p_ver->next_vertex;                                         //都没有这个标签
    }
    if(p_ver==NULL){                       //说明没有这个标签,这时候得创个新结点
        vertex *new_p=new vertex();
        new_p->data->lable=ver->data->related_lale[0];
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
        
        while(p_ver->data->lable!=ver->data->related_lale[i]&&p_ver!=NULL){   //退出循环有两种情况，一是找到了，而是所有结点
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
    }
    
}


template<class Weight,int graph_size>
void digraph<Weight,graph_size>::print(){
    vertex *p_vr=root_vertex;
    for(int i=0;i<graph_size;i++){
        cout<<"第"<<i<<"个结点的标签为："<<p_vr->data->lable<<",与它有关的标签为：";
        for(int j=0;j<p_vr->data->count;j++)
            cout<<p_vr->data->related_lale[j]<<" ";
        p_vr=p_vr->next_vertex;
    }
}





