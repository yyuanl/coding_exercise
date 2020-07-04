#include<iostream>
using namespace std;
int LastRemaining_Solution(int n, int m){
    if(n < 1 || m < 1 )
        return -1;
    
    if(n == 1)
        return 0;

    return (LastRemaining_Solution(n-1, m) + m) % n ;

}
int main(){

    cout<<LastRemaining_Solution(5, 3);

    return 0;
}

