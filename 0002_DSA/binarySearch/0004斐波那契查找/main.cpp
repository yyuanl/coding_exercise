#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>
#include "FIB.h"
using namespace std;
void printV(vector<int>&vec){
    vector<int>::iterator it = vec.begin();
    while(it != vec.end()){
        cout << *it <<" "<<endl;
        it++;
    }


}
int fibSearch(vector<int>&vec, int elem, int lo, int hi){
    if(vec.back() == elem)
        return vec.size() - 1;
    vector<int>temp;
    copy(vec.begin(), vec.end(), back_inserter(temp));
    printV(temp);
    
    FIB myfib;
    int k = 1;
    while(myfib(k) < (temp.size() + 1)){ k++;}
    cout<<"------------"<<myfib(k)<<endl;
    if(myfib(k) != (temp.size() + 1)){
       cout<<"------------"<<endl;
        int lastNum = temp[temp.size() - 1];
        while(temp.size() < (myfib(k) - 1)){
            temp.push_back(lastNum);
            cout<<"****"<<endl;
        }
    }
    hi = temp.size();
    cout<<"extend :"<<endl;
    printV(temp);

    int mi;
    while(lo < hi){
        cout<<"range is ["<<temp[lo]<<","<<temp[hi - 1]<<"]"<<endl;
        mi = lo + myfib(k - 1) - 1;
        cout<<"elem < temp[mi] ,mi is "<<mi<<endl;
        if(elem < temp[mi]){
            hi = mi;
            k--;
           
        }else{
            lo = mi + 1;
          
            k-=2;
        }
       
    }
    return --lo;

}
int main(){
    vector<int>vec{2, 3, 5, 8, 8, 9, 10, 15};
    //printV(vec);
    cout<<"result is:"<<fibSearch(vec, 10, 0, vec.size())<<endl;
    

    
    
    return 0;
}