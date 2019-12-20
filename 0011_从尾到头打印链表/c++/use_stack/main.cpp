#include<iostream>
#include<stack>
#include<vector>
using namespace std;
struct ListNode{
    public:
        int value;
        struct ListNode *next;
};
vector<int> printListFromTailToHead(ListNode* head) {
    stack<int>st;
    ListNode *node = head;
    int count = 0;
    while(node != NULL){
        st.push(node->value);
        count++;
        node = node->next;
    }
    vector<int>vec(count);
    vector<int>::iterator it = vec.begin();
    while(it < vec.end()){
        if(!st.empty()){
            *it = st.top();
            st.pop();
        }
        it++;
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