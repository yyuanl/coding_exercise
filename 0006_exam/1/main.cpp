#include <iostream>
#include <vector>
using namespace std;
void f(vector<bool>&isUsed, vector<int>&ret,int tailLen, vector<vector<int> >&allRet){
    if(tailLen == 0){
        vector<int>*p = new vector<int>;
        p->assign(ret.begin(), ret.end());
    }
    for(int i = 1; i <= isUsed.size(); ++i){ // [1, n]
        if(isUsed[i] || (ret.size()>0 && (i == ret.back()-1 || i == ret.back() + 1 )) )
            continue;
        isUsed[i] = true;
        vector<int>temp;
        temp.assign(temp.begin(), temp.end());
        temp.push_back(i);
        f(isUsed, temp, --tailLen, allRet);
        isUsed[i] = false;
    }
}

void printv(vector<int>&v){
    int len = v.size();
    for(int i = 0;i < len; ++i){
        cout<<v[i]<<" ";
    }
    cout<<" "<<endl;
}

int main(){

    int n;
    cin>>n;
    vector<vector<int> >allRet;
    vector<bool>isHead(n,false);
    vector<int>ret;
    int tailLen = n;
    f(isHead, ret, tailLen, allRet);

    for(int i = 0; i < allRet.size(); ++i){
        printv(res[i]);
    } 
    for(int i = 0; i < allRet.size(); ++i){
        delete &allRet[i];
    }

    return 0;
}