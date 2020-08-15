#ifndef __TRIE__
#define __TRIE__
#include <string.h>
#include <string>
#define R 52
template <typename T>
struct trieNode
{
    T data;
    trieNode* next[R];  // 0 - 25:大写字母 char --> index: char-0x41 ; 26-51:小写字母：char --> index : char - 0x61 + 26
    trieNode(T e = 0):data(e){
        memset(next, '\0', sizeof(next));
    }
};
template <typename T>
class Trie{
public:
    void put(std::string str, T data);
    T get(std::string str);
    void remove(std::string str);

private:
    int _size;
    trieNode *_root;
};
template <typename T>
T Trie<T>::get(std::string str){
    
}
template <typename T>
void Trie<T>::put(std::string str, T data){

}
template <typename T>
void Trie<T>::remove(std::string str){
    
}

#endif