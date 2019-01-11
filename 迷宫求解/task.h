#include "digraph.h"
class task{
    int num;
    double path;
    double step;
    digraph<int,64> labyrinth;
    
    
public:
    void read();
    void run();
};

void task::read(){
    srand((unsigned)time(NULL));
    cout<<"请问是手动输入还是自动生成（输入0为手动输入，输入1为自动生成）：";
    int sel;
    cin>>sel;
    if(sel==0)
        cout<<"请输入初始迷宫(二维矩阵):";
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(sel==0)
                cin>>path;
            else{
                if(i==0&&j==0||i==7&&j==7)             //保证一定有入口和出口
                    path=0;
                else
                    path=rand()%2;
            }
            cout<<path<<" ";
            if(path==0){
                vertex *p_ver=new vertex();
                object *p_obj=new object();
                p_obj->set(i, j);
                string str="";
                str+=char('a'+i);
                str+=char('a'+i+j);
                p_obj->lable=str;
                p_ver->data=p_obj;
                labyrinth.add_vertex(p_ver);
            }
        }
        cout<<endl;
    }
}
void task::run(){
    labyrinth.update_related();
    labyrinth.update();
    labyrinth.update_weight_adjacency();
    labyrinth.run();
}

