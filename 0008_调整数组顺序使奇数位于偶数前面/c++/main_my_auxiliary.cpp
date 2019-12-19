#include<iostream>
#include<vector>
using namespace std;
bool is_even(const int &value){
    return value%2 == 0 ? true :false;
}

void reOrderArray(vector<int> &array) {
    vector<int>even;
    vector<int>odd;
    int ix = 0;
    while(ix < array.size()){
        if(is_even(array[ix])){
            even.push_back(array[ix]);
        }else{
            odd.push_back(array[ix]);
        }
        ix ++;
    }
    int ix1 = 0;
    for(int ix2 = 0;ix2 < odd.size(); ix1++, ix2++)
        array[ix1] = odd[ix2];
    for(int ix3 = 0;ix3 < even.size(); ix1++,ix3++)
        array[ix1] = even[ix3];  
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