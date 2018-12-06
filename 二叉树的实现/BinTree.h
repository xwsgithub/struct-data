
#include <iostream>
#include <string>
using namespace std;

struct BiTreeNode{       //二叉树的节点
    char data;
    BiTreeNode *lnode,*rnode;    //左节点，右节点
    BiTreeNode(){
        lnode=NULL;
        rnode=NULL;
    }
};

class BinTree{
    BiTreeNode* root;
    int height,width;
    
    BiTreeNode* recursive_create(string str,int &pos);   //将string拆分成char并化为节点的构造函数
    void recursive_preOrder(BiTreeNode* node,void(*visit)(char &));     //前序遍历的递归函数
    void recursive_midOrder(BiTreeNode* node,void(*visit)(char &));     //中序遍历的递归函数
    void recursive_postOrder(BiTreeNode* node,void(*visit)(char &));     //后序遍历的递归函数
    int recursive_getHight(BiTreeNode*node);                      //用于getHight的递归
    void recursive_insert(BiTreeNode*node,BiTreeNode* &return_node);                 //用于insert的递归
    bool recursive_findNode(BiTreeNode*node,char ch);      //findNode的递归函数
    void recursive_deleteNode(BiTreeNode*node,char ch);     //deleteNode的递归函数
    
    
public:
    BinTree();
    void create(string str);
    void preOrder(void(*visit)(char &));     //前序遍历
    void midOrder(void(*visit)(char &));     //中序遍历
    void postOrder(void(*visit)(char &));    //后序遍历
    int getHeight();                         //返回树的高度
    int getWidth();                          //返回树的宽度
    void insert(char ch);         //插入键值为ch的字符,在矮的末端插，若高度相同，则插左边
    int getNumberOfNoun(int noun);    //返回度数为noun的个数，若noun大于2且noun小于0，返回-1
    void deleteNode(char ch);         //删除给定健的节点
    bool findNode(char ch);           //查找键值为ch的节点
};
BinTree::BinTree(){     //初始化
    root=NULL;
    height=0;
    width=0;
}

BiTreeNode* BinTree::recursive_create(string str,int &pos){
    BiTreeNode *node=new BiTreeNode();
    pos++;
    if(pos > str.size()-1)
        return NULL;
    else{
        node=new BiTreeNode();
        node->data=str[pos];
        node->lnode=recursive_create(str, pos);
        node->rnode=recursive_create(str, pos);
    }
    return node;
}
void BinTree:: create(string str){
    int pos=-1;
    root=recursive_create(str, pos);
}
void BinTree::recursive_preOrder(BiTreeNode* node,void(*visit)(char &)){
    if(node!=NULL){
        (*visit)(node->data);
        recursive_preOrder(node->lnode,visit);
        recursive_preOrder(node->rnode,visit);
    }
}
void BinTree::preOrder(void(*visit)(char &)){
    recursive_preOrder(root,visit);
}

void BinTree::recursive_midOrder(BiTreeNode* node,void(*visit)(char &)){
    if(node!=NULL){
        recursive_midOrder(node->lnode,visit);
        (*visit)(node->data);
        recursive_midOrder(node->rnode,visit);
    }
}
void BinTree::midOrder(void(*visit)(char &)){
    recursive_midOrder(root,visit);
}

void BinTree::recursive_postOrder(BiTreeNode* node,void(*visit)(char &)){
    if(node!=NULL){
        recursive_postOrder(node->lnode,visit);
        recursive_postOrder(node->rnode,visit);
        (*visit)(node->data);
    }
}
void BinTree::postOrder(void(*visit)(char &)){
    recursive_postOrder(root,visit);
}
int BinTree:: getHeight(){
    return recursive_getHight(root);
}

int BinTree::recursive_getHight(BiTreeNode*node){
    if(node==NULL)
        return 0;
    int l_hight=recursive_getHight(node->lnode);
    int r_hight=recursive_getHight(node->rnode);
    return (l_hight>r_hight)? l_hight+1:r_hight+1;
}

int BinTree::getWidth(){
    int max_width;
    BiTreeNode* node=root;
    m_queue<BiTreeNode*> queue;
    if(node==NULL)      //如果root为空，直接返回0
        return 0;
    else{
        max_width=1;                //若不为0，初始化max_width为1
        queue.append(node);
    }
    while(!queue.empty()){       //若列表不为空，说明整个树遍历完毕
        int size=queue.size();
        max_width=(max_width>size)?max_width:size;
        BiTreeNode* temp_node;
        for(int i=0;i<size;i++){       //循环队列里现在有的节点数量，若有左节点或右节点，则append进队列
            queue.retrieve(temp_node);
            if(temp_node->lnode!=NULL){
                queue.append(temp_node->lnode);
            }
            if(temp_node->rnode!=NULL){
                queue.append(temp_node->rnode);
            }
            queue.server();          //去除头节点
        }
    }
    return max_width;
}
void BinTree::insert(char ch){
    BiTreeNode* node=new BiTreeNode(),*temp_node;
    node->data=ch;
    if(root==NULL){      //为空树的情况
        root=node;
        return ;
    }
    else{
        recursive_insert(root,temp_node);
    }
    if(node->lnode!=NULL){
        temp_node->lnode=node;
    }
    else
        temp_node->rnode=node;
}
void BinTree::recursive_insert(BiTreeNode*node,BiTreeNode* &return_node){
    if(node->lnode==NULL||node->rnode==NULL){       //若满足此次情况，说明找到了该插入的地方
        return_node=node;
        return;
    }
    if(recursive_getHight(node->lnode)<=recursive_getHight(node->rnode)){   //递归高度比较小的部分
        recursive_insert(node->lnode,return_node);
    }
    else{
        recursive_insert(node->rnode,return_node);
    }
}
int BinTree::getNumberOfNoun(int noun){
    if(noun<0||noun>2)
        return -1;
    if(root==NULL)      //若树为空，不管noun为多少，返回0
        return 0;
    if(noun==2){
        int noun_count=0;    //计数器
        m_queue<BiTreeNode*> queue;
        queue.append(root);
        BiTreeNode*node;
        while (!queue.empty()) {
            int size=queue.size();
            for(int i=0;i<size;i++){      //循环队列的size次
                queue.retrieve(node);
                if(node->lnode!=NULL&&node->rnode!=NULL)
                    noun_count++;
                if(node->lnode!=NULL)
                    queue.append(node->lnode);
                if(node->rnode!=NULL)
                    queue.append(node->rnode);
                queue.server();
            }                        //循环完之后将上一层全部清除，把下一层的节点全部加进来
        }
        return noun_count;
    }
    else if(noun==1){
        int noun_count=0;    //计数器
        m_queue<BiTreeNode*> queue;
        queue.append(root);
        BiTreeNode*node;
        while (!queue.empty()) {
            int size=queue.size();
            for(int i=0;i<size;i++){      //循环队列的size次
                queue.retrieve(node);
                if(node->lnode!=NULL||node->rnode!=NULL)
                    noun_count++;
                if(node->lnode!=NULL)
                    queue.append(node->lnode);
                if(node->rnode!=NULL)
                    queue.append(node->rnode);
                queue.server();
            }                        //循环完之后将上一层全部清除，把下一层的节点全部加进来
        }
        return noun_count;
    }
    else{
        int noun_count=0;    //计数器
        m_queue<BiTreeNode*> queue;
        queue.append(root);
        BiTreeNode*node;
        while (!queue.empty()) {
            int size=queue.size();
            for(int i=0;i<size;i++){      //循环队列的size次
                queue.retrieve(node);
                if(node->lnode==NULL&&node->rnode==NULL)
                    noun_count++;
                if(node->lnode!=NULL)
                    queue.append(node->lnode);
                if(node->rnode!=NULL)
                    queue.append(node->rnode);
                queue.server();
            }                        //循环完之后将上一层全部清除，把下一层的节点全部加进来
        }
        return noun_count;
    }
}
void BinTree::deleteNode(char ch){
    recursive_deleteNode(root, ch);
}

void BinTree:: recursive_deleteNode(BiTreeNode*node,char ch){
    if(node==NULL)   //如果走到null，return
        return;
    if(node->lnode!=NULL&&node->lnode->data==ch)
        node->lnode=NULL;
    if(node->rnode!=NULL&&node->rnode->data==ch)
        node->rnode=NULL;
    recursive_deleteNode(node->lnode, ch);
    recursive_deleteNode(node->rnode, ch);
}

bool BinTree:: findNode(char ch){
    return recursive_findNode(root, ch);
}
bool BinTree::recursive_findNode(BiTreeNode*node,char ch){
    if(node==NULL)
        return false;
    if(node->data==ch)
        return true;
    return recursive_findNode(node->lnode, ch)||recursive_findNode(node->rnode, ch);  //只要满足一个便为true
}



