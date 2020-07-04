/**
右上角的元素是行最大值，列最小值
因此， 比此值小，则列不考虑
比此值大， 则行不考虑
**/
#include<iostream>
#include<vector>
using namespace std;
bool find(const int &target, const vector< vector<int> > &vec){

    if(vec.empty()){
        cout<<"This vector is empty!"<<endl;
        return 1;
    }
    int row = 0;
    int column = vec[0].size() - 1;
    while((row < vec.size())&&(column>=0)){
        cout<<"================"<<row<<"---"<<column<<endl;
        if(vec[row][column] == target){
            cout<<row<<"--"<<column<<endl;
            return 1;
        }else if(vec[row][column] < target){
            cout<<"row plus"<<endl;
            row ++ ;
        }else{
            cout<<"column descrease"<<endl;
            column --;
        }
    }
    
    if(row < 0 || column <0) return 0;
    cout<<"================"<<row<<"---"<<column<<endl;

}
int main(){
    int a1[4] = {1, 2, 3, 4};
    int a2[4] = {3, 4, 5, 6};
    int a3[4] = {7, 8, 11, 12};
    int a4[5] = {9, 10, 14, 16};
    vector<int>vec1(a1, a1 + 4);
    vector<int>vec2(a2, a2 + 4);
    vector<int>vec3(a3, a3 + 4);
    vector<int>vec4(a4, a4 + 4);
    vector< vector<int> > vec;
    vec.push_back(vec1);
    vec.push_back(vec2);
    vec.push_back(vec3);
    vec.push_back(vec4);
    cout<<"-------"<<find(8, vec);
    return 0;
}