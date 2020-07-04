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
#include <cmath>
#include <set>

using namespace std;

struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
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


class Solution {
public:
    // Parameters:
    //        numbers:     an array of integers
    //        length:      the length of array numbers
    //        duplication: (Output) the duplicated number in the array number
    // Return value:       true if the input is valid, and there are some duplications in the array number
    //                     otherwise false
    bool duplicate(int numbers[], int length, int* duplication) {
        if(numbers == nullptr || length <= 0)return false;
        int ix;
        for(int i=0;i < length;i++){
            if(numbers[i] < 0 || numbers[i] > length-1)
                return false;
            while (numbers[i] != i)
            {
                ix = numbers[i];
                numbers[i] = numbers[i]^numbers[ix];
                numbers[ix] = numbers[i]^numbers[ix];
                numbers[i] = numbers[i]^numbers[ix];
                if(numbers[i] == numbers[ix]){
                    *duplication = numbers[i];
                    return true;
                }
            }
            
        }
        return false;
    }
};




int main(){
    int arr[] = {1,2,3,4,5};
    const vector<int>v(arr, arr + 5);
    Solution s;
    s.multiply(v);
    
    return 0;
}
/*
                                                            1
                                                236                     3
                                            4      5             6        7
*/


