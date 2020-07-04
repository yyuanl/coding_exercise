#include<iostream>
#include<string>
using namespace std;
struct RandomListNode {
    int label;
    struct RandomListNode *next = NULL, *random = NULL;
    // RandomListNode(int x) :
    //         label(x), next(NULL), random(NULL) {
    // }
};

void print_random_list(RandomListNode *random_list){
    cout<<"\nprint listnode ..."<<endl;
    RandomListNode *p_random_list = random_list;
    int count_node = 0;
    if(random_list == NULL)
        return ;
    while(p_random_list != NULL){

        string str_random;
        string str_next;
        if(p_random_list -> random == NULL){
            str_random = "NULL";
        }else{
            str_random = to_string(p_random_list->random->label);
        }

        if(p_random_list->next == NULL){
            str_next = "NULL";
        }else{
            str_next = to_string(p_random_list->next->label);
        }
        cout<<count_node<<" node, its label is "<<p_random_list->label
        <<", its random node label is "<<str_random
        <<" and its next node label is "<<str_next<<endl;
        p_random_list = p_random_list->next;
        count_node ++;
    }
}

void new_node(RandomListNode *p_old_node){
    RandomListNode* p_1 = p_old_node;
    while(p_1 != NULL){
        cout<<"prepare to create a new node ..."<<endl;
        if(p_1->next != NULL){
            cout << "old node label is "<<p_1->label<<", old node's next node label is "<<p_1->next->label<<endl;
        }else{
            cout << "old node label is "<<p_1->label<<", old node's next node label is NULL"<<endl;
        }

        RandomListNode* p_new_node = new RandomListNode;
        p_new_node->label = p_1->label;
        p_new_node->next = p_1->next;
        p_1->next = p_new_node;

        if(p_1->random != NULL && p_1->next != NULL && p_new_node->next != NULL){
            cout<<"create a new successfully. now, the old node next node's label is "<<p_1->next->label
            <<" and its random node label is "<<p_1->random->label
            <<" [!]new node label is "<<p_new_node->label<<" and its next node label is "<<p_new_node->next->label<<endl;
        }

        p_1 = p_1 -> next->next;
    }  
}
void modify_random(RandomListNode* pHead){
    if(pHead == NULL)
        return ;
    RandomListNode* p_2 = pHead;
    while(p_2 != NULL){
        p_2->next->random = p_2->random;
        p_2 = p_2->next->next;
    }  

}

RandomListNode* separate(RandomListNode* pHead){
    if(pHead == NULL)
        return NULL;
    RandomListNode* p_3 = pHead;
    RandomListNode* newHead = p_3->next;
    RandomListNode* p_temp1 = NULL;
    RandomListNode* p_temp2 = NULL;
    while(p_3 != NULL){

        if(p_3->next->next != NULL){
            p_temp1 = p_3->next->next; // 老结点，当前的结点下一个老结点
            p_temp2 = p_3->next; //新结点
            p_3->next = p_temp1;
            p_temp2->next = p_temp1->next; 
            p_3 = p_temp1;
        }else{ // 最后一个结点
            p_3->next->next = NULL;
            p_3->next = NULL;
            p_3 = NULL;
        }
    }

    return newHead;

}




RandomListNode* Clone(RandomListNode* pHead){
    if(pHead == NULL)
        return NULL;
    RandomListNode* p_1 = pHead;
    while(p_1 != NULL){
        cout<<"prepare to create a new node ..."<<endl;
        if(p_1->next != NULL){
            cout << "old node label is "<<p_1->label<<", old node's next node label is "<<p_1->next->label<<endl;
        }else{
            cout << "old node label is "<<p_1->label<<", old node's next node label is NULL"<<endl;
        }

        RandomListNode* p_new_node = new RandomListNode;
        p_new_node->label = p_1->label;
        p_new_node->next = p_1->next;
        p_1->next = p_new_node;

        if(p_1->random != NULL && p_1->next != NULL && p_new_node->next != NULL){
            cout<<"create a new successfully. now, the old node next node's label is "<<p_1->next->label
            <<" and its random node label is "<<p_1->random->label
            <<" [!]new node label is "<<p_new_node->label<<" and its next node label is "<<p_new_node->next->label<<endl;
        }

        p_1 = p_1 -> next->next;
    } 

    RandomListNode* p_2 = pHead;
    while(p_2 != NULL){
        p_2->next->random = p_2->random;
        p_2 = p_2->next->next;
    }  


    RandomListNode* p_3 = pHead;
    RandomListNode* newHead = p_3->next;
    RandomListNode* p_temp1 = NULL;
    RandomListNode* p_temp2 = NULL;
    while(p_3 != NULL){

        if(p_3->next->next != NULL){
            p_temp1 = p_3->next->next; // 老结点，当前的结点下一个老结点
            p_temp2 = p_3->next; //新结点
            p_3->next = p_temp1;
            p_temp2->next = p_temp1->next; 
            p_3 = p_temp1;
        }else{ // 最后一个结点
            p_3->next->next = NULL;
            p_3->next = NULL;
            p_3 = NULL;
        }
    }
    return newHead;


    // if(pHead == NULL)
    //     return NULL;
    // // 每个结点后面新插入一个结点
    // new_node(pHead);

    // // 按照原来结点的random来修改新结点的random
    // modify_random(pHead);
    // print_random_list(pHead);

    // // 拆分旧结点和新结点
    // RandomListNode* newHead = separate(pHead);
    // return newHead;
}

int main(){
    RandomListNode random_list[4];
    random_list[0].label = 1;
    random_list[0].next = &random_list[1];
    random_list[0].random = &random_list[2];
    random_list[1].label = 3;
    random_list[1].next = &random_list[2];
    random_list[1].random = &random_list[1];
    random_list[2].label = 5;
    random_list[2].next = &random_list[3];
    random_list[2].random = &random_list[3];
    random_list[3].label = 9;
    random_list[3].next = NULL;
    random_list[3].random = &random_list[1];

    print_random_list(random_list);
    RandomListNode* p = Clone(random_list);
    print_random_list(p);
    return 0;
}