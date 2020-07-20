#include <iostream>
#include <vector>
#pragma once
using namespace std;
class FIB{
    public:
        FIB();
        int operator()(int k);
        void setFib(int k);
    private:
        static vector<int> fib;

};