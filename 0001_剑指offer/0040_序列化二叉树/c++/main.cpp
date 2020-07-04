#include<iostream>
#include<vector>
#include<stack>
#include <algorithm> 
#include <queue>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
using namespace std;


struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};
void printVector(vector<int>& v){
    cout<<"----------"<<endl;
    int s = v.size();
    cout<<"[";
    for(int i = 0;i < s;i++)
        cout<<v[i]<<" ";
    cout<<"]\n"<<endl;
}
void printEveryLeve(vector<vector<int> > &res){
    cout<<"----------"<<endl;
    int s = res.size();
    cout<<"-*********---"<<s<<endl;
    for(int i = 0; i < s; i++){
        cout<<"-*********---"<<endl;
        cout<<i<<": ";
        printVector(res[i]);
    }
}


class MySolution {
public:
    char* Serialize(TreeNode *root) {    
        if(root == NULL){
            char* res = new char[3];
            strcpy(res, "#,");
            return res;
        }
        string str;
        
        resuString(root, str);
        const char* resuChar = str.c_str();
        //printf("%s\n",resuChar);
        char* res = new char[str.length() + 1];
        strcpy(res, resuChar);
        return res;

    }
    void resuString(TreeNode* node, string& str){
        if(node == NULL){
            str += "#,";
            return ;
        }
            
        str += (to_string(node -> val) + ",");
        //cout<<str<<"\n"<<endl;
        resuString(node->left, str);
        resuString(node->right, str);
    }
    TreeNode* Deserialize(char *str) {
        if(str == NULL || *str == '\0')
            return NULL;
        int index = 0;
        return createNodeByStr(str, index);
    }
    TreeNode* createNodeByStr(char* str, int &index){

        if(str[index] != '\0'){
            //cout<<"current char is "<<str[index]<<endl;
        }
        if(str[index] == '#' ){
            index += 2;
            return NULL;
        }
        int val = 0;
        
        while(str[index] != ',' && str[index] != '\0'){
            //cout<<"call createNodeBystr\n"<<endl;
            val = val*10 + (str[index] - '0');
            index++;
        }
        index++;
        TreeNode* root = new TreeNode(val);
        root->left = createNodeByStr(str, index);
        root->right = createNodeByStr(str, index);
        return root;
    }
};


void freeTree(TreeNode* root){
  if(root == NULL)
    return ;
  freeTree(root -> left);
  freeTree(root -> right);
  delete root;
}
void LDR(TreeNode* root){
  /*TreeNode* curr_node = root;
  stack<TreeNode*>tree_stack;
  
  while(!tree_stack.empty() || curr_node != NULL){
    cout<<"...................\n"<<endl;
    while(curr_node != NULL){
      tree_stack.push(curr_node);
      curr_node = curr_node -> left;
    }
    curr_node = tree_stack.top();
    cout<<curr_node->val<<"\n"<<endl;
    tree_stack.pop();
    curr_node = curr_node->right;
  }*/
  if(root == NULL)
    return ;
   
   cout<<root->val<<endl;
   LDR(root->left);
   LDR(root->right);

}

int main(){
   
//    int testarr[] = {5,2,3,4,1,6,7,0,8};
//    vector<int>tes(testarr, testarr + 9);
//    Solution test;
//    for(int i = 0; i < 9; i++){
//        cout<<"insert "<<tes[i]<<endl;
//        test.Insert(tes[i]);
//        printVector(test.frontHalfMaxHeap.my_heap);
//        printVector(test.backHalfMinHeap.my_heap);
//        cout<<"midle number is:"<<test.GetMedian()<<endl;
//    }

    Solution test;
    MySolution mytest;
    TreeNode n1(1);
    TreeNode n2(289);
    TreeNode n3(3);
    TreeNode n4(4);
    TreeNode n5(5);
    TreeNode n6(6);
    TreeNode n7(7);
    n1.right = &n3; n1.left = &n2;
    n2.right = &n5; n2.left = &n4;
    n3.right = &n7; n3.left = &n6;
    // test.Print(&n1);
    // cout<<"here.."<<endl;
    // printEveryLeve(test.res);
    
    char* tt;
    char* my_tt;
    // test.resuString(&n1, str);
    // cout<<str<<endl;
    tt = test.Serialize(&n1);
    my_tt = mytest.Serialize(&n1);
    printf("corrent resutl is %s\n", tt);
    printf("my result is %s\n", my_tt);
    TreeNode* test_node = test.Deserialize(tt);
    TreeNode* my_test_node = mytest.Deserialize(my_tt);




    LDR(test_node);
    cout<<"----------"<<endl;
    LDR(my_test_node);


    delete tt;
    delete my_tt;
    freeTree(my_test_node);
    freeTree(test_node);

    return 0;
}
/*
                                                            1
                                                236                     3
                                            4      5             6        7
*/


