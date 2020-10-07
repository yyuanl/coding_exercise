#include "./Graph.h"
#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <list>
using namespace std;
int row,col;
enum state{M_UNVISITED,M_VISITED,M_CHANGE};
struct point{
    int x, y;
    state s;
    point():x(-1), y(-1), s(M_UNVISITED){}
};
using z_chain = vector<pair<int,int>>;
#define index_leg(i, j) ( ( (i > 0) && (i < row) && (j > 0) && (j < col) )   ? (true):(false))
 
#define inboundary(i, j)  (  (((i) == (row - 1))||((j) == (col - 1))) ? (true) : (false))

// 找一个未被访问过的符合条件 的邻接结点
pair<int, int> randAdj(vector<vector<char>>&v,vector<vector<point>>&flag, int i, int j){
    if(index_leg(i-1,j) && v[i-1][j] == 'z' && flag[i-1][j].s == M_UNVISITED){
        return {i-1,j};
    }
    if(index_leg(i+1,j) && v[i+1][j] == 'z' && flag[i+1][j].s == M_UNVISITED){
        return {i+1,j};
    }
    if(index_leg(i,j-1) && v[i][j-1] == 'z' && flag[i][j-1].s == M_UNVISITED){
        return {i,j-1};
    }
    if(index_leg(i,j+1) && v[i][j+1] == 'z' && flag[i][j+1].s == M_UNVISITED){
        return {i,j+1};
    }
    return {-1,-1};
}

void dfs(vector<vector<char>>&v, int r, int c, vector<vector<point>>&flag, z_chain &zc, bool &zc_okay){
    if(flag[r][c].s == M_VISITED)return ;
    //if(!index_leg(r,c))return ;
    flag[r][c].s = M_VISITED;  //当前结点标记为访问
    cout<<r<<" "<<c<<endl;
    zc.push_back({r,c});
    if(inboundary(r,c)){  //在边界上
        zc_okay = false;
    }
    for(pair<int, int> adj_index = randAdj(v, flag, r,c);index_leg(adj_index.first, adj_index.second);adj_index = randAdj(v, flag, adj_index.first, adj_index.second)){
        dfs(v, adj_index.first, adj_index.second, flag, zc, zc_okay);
    }
    
}
int main(){
    // vector<char>v = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    // vector<pair<int, int>>e = {{0,2},{0,4},{0,7},{2,1},{2,7},{3,7},{3,1},{4,5},{4,6},{5,6},{1,6}};
    // Graph test(v,e);
    // //test.BFS();
    // test.DFS(0);
    //替换z变为x，与边界连接的z不能被替换。岛屿问题。
    
    vector<vector<char>>v = {
                             {'x','x','x','x','x'}, 
                             {'x','z','z','z','x'},
                             {'x','x','z','x','x'},
                             {'x','z','x','z','x'},
                             {'x','x','z','z','x'},
                             {'x','z','z','z','x'},
                             {'x','z','x','z','x'},
                             {'x','z','x','x','x'}
                            };
    row = v.size();
    col = v[0].size();
    list<z_chain>res;
    vector<vector<point>>flags(row, vector<point>(col, point()));
    for(int i = 0; i < row;i++){
        for(int j = 0; j < col;j++){
            if(v[i][j] == 'x' || flags[i][j].s == M_VISITED)continue;
            z_chain t; // 以v[i][j]为起点进行dfs搜索 结点记录在t里面
            bool zc_is_ok = true;
            dfs(v, i, j, flags, t, zc_is_ok);
            if(zc_is_ok){
                res.push_back(t);
            }
        }
    }
    // 遍历res  获得结果
    for(auto e:res){
        for(auto ee: e){
            v[ee.first][ee.second] = 'x';
        }
    }
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col;j++){
            cout<<v[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}


/*
a b c d e f g h
0 1 2 3 4 5 6 7

*/