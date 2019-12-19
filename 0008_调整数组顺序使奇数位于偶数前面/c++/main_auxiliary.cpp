#include<iostream>
#include<vector>
using namespace std;
void reOrderArray(vector<int> &array){
    vector<int>temp_vector;
    vector<int>::iterator iter1 = array.begin();
    while(iter1 != array.end()){
        if(*iter1 % 2 == 0){
            temp_vector.push_back(*iter1);
            array.erase(iter1);
        }else{
            iter1++;
        }
    }
    vector<int>::iterator iter2 = temp_vector.begin();
    while(iter2 != temp_vector.end()){
        array.push_back(*iter2);
        iter2++;
    }
}

void print_vector(const vector<int> &vec){
    for(int i =0; i < vec.size(); i++)
        cout<<vec[i]<<" ";
    cout<<"\n";
}

int main(){
    int arr[11] = {1, 4, 3, 4, 8, 10, 13, 11, 0, 6, 17};
    vector<int>vec(arr, arr + 11);
    print_vector(vec);
    reOrderArray(vec);
    print_vector(vec); 
    return 0;
}