#include "FIB.h"
#include <iostream>
vector<int> FIB::fib;
FIB::FIB(){
    cout << "FIB::FIB()"<<endl;
    fib.push_back(1);
    fib.push_back(1);
}
int FIB::operator()(int k){
    if(fib.size() < k)
        setFib(k);
    
    return fib[k - 1];
}
void FIB::setFib(int k){
    cout <<"FIB::setFib(int k) "<<endl;

    if(k >= 3){
        int fib_len = fib.size();
        for(int ix = fib.size() - 1;fib_len < k; ix++,fib_len++){
            fib.push_back(fib[ix] + fib[ix - 1]);
        }
    }
            
}