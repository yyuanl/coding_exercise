#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int MoreThanHalfNum_Solution(vector<int> numbers) {
    int len_of_vector = numbers.size() / 2;
    vector<int>::iterator iter = numbers.begin();
    while(iter != numbers.end()){
        if(count(numbers.begin(),numbers.end(), *iter) > len_of_vector){
            return *iter;
        }
        iter ++;
    }
    return 0;
}

int main(){
    int arr[] = {1,2,3,2,2,2,5,4,2};
    vector<int> vec(arr, arr + 9);
    cout<<"the number is "<<MoreThanHalfNum_Solution(vec);
    return 0;
}