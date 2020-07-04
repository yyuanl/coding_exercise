#pragma once
#include <iostream>
template <typename T>
class Visit
{
public:
    void operator()(T data){
        cout<<data<<" ";
    }
};

