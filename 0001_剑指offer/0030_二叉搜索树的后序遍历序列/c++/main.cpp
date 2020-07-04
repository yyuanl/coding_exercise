#include<iostream>
#include<vector>
#include<queue>
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
    int size = v.size();
    cout<<"[";
    for(int i = 0;i < size;i++)
        cout<<v[i]<<" ";
    cout<<"]"<<endl;
}
bool judge(vector<int>& sequence){
    if(sequence.empty())
        return true;
    int size = sequence.size();
    int boundary = -1;
    int rootVal = sequence.back();
    vector<int>left_child, right_child;
    
    for(int i = 0; i < size; i++){
        if(boundary == -1 && sequence[i] > rootVal){
            boundary = i;
            continue;
        }
            
        if(boundary != -1 && sequence[i] < rootVal){
            return false;
        }
    }
    // 能运行到这里，说明是一个合格的二叉搜索树。就要合理的划分左右子树
    if(boundary == -1){// 无右子树的
        left_child.assign(sequence.begin(), sequence.end() - 1);
        return judge(left_child);

    }else{
        left_child.assign(sequence.begin(), sequence.begin() + boundary);
        right_child.assign(sequence.begin() + boundary, sequence.end() - 1);
        return judge(left_child) && judge(right_child);

    }


}
    
    bool VerifySquenceOfBST(vector<int> sequence) {
        if(sequence.empty())
            return false;
        return judge(sequence);
    }



int main(){
    int arr[] = {2,4,3,6,11,9,5};
    vector<int>ve(arr, arr + 6);
    cout<<VerifySquenceOfBST(ve)<<endl;
    return 0;
}


