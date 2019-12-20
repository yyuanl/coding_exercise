**利用栈实现：**链表读取的方向是从头到尾，而从尾到头输出恰好符合了栈先进后出的特点。
**利用递归实现：**有这样一个函数，它可以把链表当前结点之后的先按照倒序push_back到vector中。



```c++
using namespace std;
vector<int>vec;
struct ListNode{
    public:
        int value;
        struct ListNode *next;
};
vector<int> printListFromTailToHead(ListNode* head) {
    if(head != NULL){
        printListFromTailToHead(head->next); //后面的先倒序放入
        vec.push_back(head->value); //再放当前节点
    }
    return vec;  
}
```



