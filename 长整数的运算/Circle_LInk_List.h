//#include "Link_List.h"



class Circle_Link_List:public Link_List{
    
    
public:
    void addList(Node*node);
    void printList() const;
};

void Circle_Link_List::addList(Node*node){
    if(count==0){
        head=node;
        node->next=node;
        node->pre=node;
    }
    else{
        node->next=head->next;
        head->next->pre=node;
        head->next=node;
        node->pre=head;
    }
}
void Circle_Link_List::printList() const{
    Node *node=head;
    for(int i=0;i<count;i++){
        node->data->Print();
        node=node->next;
    }
}


