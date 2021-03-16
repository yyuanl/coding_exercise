#include <iostream>
#include <vector>
using namespace std;
int majCandiate(vector<int>&v){
    int ret;
    for(int diff = 0, i = 0;i < v.size();i++){ // diff代表当前前缀中ret个数与其他元素总数差
        if(diff == 0){
            ret = v[i];
            diff = 1;
        }else{
            (ret == v[i]) ? diff++ : diff--;
        }
    }
    return ret;
}
bool majCheck(vector<int>&v, int maj){ // 检查候选者maj是否为众数
    int num = v.size() / 2;
    int c = 0;
    for(int i = 0; i < v.size(); i++){
        if(v[i] == maj)
            c++;
    }
    return c > num;
}
bool majority(vector<int>&v, int &maj){
    return majCheck(v, maj = majCandiate(v));
}
int main(){
    vector<int>v;
    int maj = -1;
    for(int i = 0; i < 15;i++){
        v.push_back(rand() % 2 + 1);
    }
    for(auto e:v){
        cout<<e<<" ";
    }
    cout<<endl;
    bool ishavemaj = majority(v, maj);
    cout<<"Does it have majority ? "<<ishavemaj<<" maj = "<<maj<<endl;
    return 0;
}