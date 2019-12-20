#include<iostream>
#include<stack>
#include<vector>
using namespace std;
vector<int>vec;
struct ListNode{
    public:
        int value;
        struct ListNode *next;
};
vector<int> printListFromTailToHead(ListNode* head) {
    if(head != NULL){
        printListFromTailToHead(head->next);
        vec.push_back(head->value);
    }
    return vec;  
}
int main(){
    ListNode LianBiao[4];
    LianBiao[0].value = 1;
    LianBiao[0].next = &LianBiao[1];
    LianBiao[1].value = 2;
    LianBiao[1].next = &LianBiao[2];
    LianBiao[2].value = 3; 
    LianBiao[2].next = &LianBiao[3];
    LianBiao[3].value = 4;
    LianBiao[3].next = NULL;
    // ListNode *head = &ListNode[0];
    vector<int>vec = printListFromTailToHead(LianBiao);
    for(int i = 0;i < vec.size(); i++)
        cout<<vec[i]<<" ";
    return 0;
}