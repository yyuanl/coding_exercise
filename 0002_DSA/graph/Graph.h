#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <vector>
#include <utility>
#include <queue>
#include <iostream>
using namespace std;
enum STATUS_V{UNDISCOVERED,DISCOVERED, VISITED};
enum STATUS_E{START,TREE, CORSS};
/*顶点简单的顶点类型*/
struct vertex{
    int rank;
    char data;  // 顶点数据
    STATUS_V status_v;  // 顶点装填
    vertex(char a = '0'):rank(-1),data(a),status_v(UNDISCOVERED){}
};
/*简单的边类型*/
struct edge{
    int weight;  // 权重
    STATUS_E status_e;  // 边状态
    edge(int w = 0):weight(w),status_e(START){} 
};
class Graph{
private:
    vector<vertex>_vertexs; // 顶点集合
    //vector<edge>_deges; // 边集合
    vector<vector<edge>>_adjacency;//邻接矩阵
private:
    // 辅助函数
    int nextNbr(int i,int j);   // 第i个节点与第j个节点相连  返回下一个相连节点
    int firstNbr(int i);        // 某个节点的第一个与之相连的结点， 启动作用
public: // 算法
    void BFS();
    void DFS(int i);
    
public:
    Graph(vector<char>&vx, vector<pair<int, int>>&e);//构造函数
};


int Graph::nextNbr(int i,int j){
    for(int x = j-1;x >= 0; --x){
        //cout<<i<<" "<<x<<" "<<_adjacency[i][x].weight<<endl;
        if(_adjacency[i][x].weight == 1){
            return x;
        }
    }
    return -1;
}
int Graph::firstNbr(int i){
    return nextNbr(i, _vertexs.size());
}
int dqueue(queue<int>&q){
    int res = q.front();
    q.pop();
    return res;
}
void Graph::BFS(){
    
    queue<int>qe;
    qe.push(_vertexs[0].rank);
    _vertexs[0].status_v = DISCOVERED;
    while(!qe.empty()){  // 反复从队列取节点  队列一段保存的是某个节点的所有邻接结点 参考树的层次遍历算法
        int curr_index = dqueue(qe);
        std::cout<<"visit node "<<_vertexs[curr_index].data<<std::endl;  // 访问当前节点
        for(int adj_node_ix = firstNbr(curr_index); adj_node_ix > -1; adj_node_ix = nextNbr(curr_index, adj_node_ix)){
            /*找到当前节点所有邻接节点， 放入队列，静候访问*/
            if(_vertexs[adj_node_ix].status_v == UNDISCOVERED){
                qe.push(adj_node_ix);
                _vertexs[adj_node_ix].status_v = DISCOVERED;
            }else{
                    //...过门
            }
        }
        _vertexs[curr_index].status_v = VISITED;  // 访问结束，节点标记为已经被访问
    }
}
void Graph::DFS(int curr_ix){
    cout<<_vertexs[curr_ix].data<<endl;
    _vertexs[curr_ix].status_v = VISITED;
    for(int adj_node_ix = firstNbr(curr_ix);adj_node_ix > -1; adj_node_ix = nextNbr(curr_ix,adj_node_ix)){
        if(_vertexs[adj_node_ix].status_v == UNDISCOVERED){
            _vertexs[adj_node_ix].status_v = VISITED;
            DFS(adj_node_ix);
        }else{

        }
    }

}

/**
 * 外部传入一个顶点向量和顶点有连接向量来初始化一个图
 * [a,b,c,d,e,f,g]   [{0,4},{0,7},{0,2},{2,7},{3,7},{1,2},{1,3},{1,6},{4,5},{4,6},{5,6}]
*/
Graph::Graph(vector<char>&vx, vector<pair<int, int>> &edges)
:_vertexs(vx.size(),vertex()),_adjacency(vx.size(), vector<edge>(vx.size(), edge()))
{
    for(int i = 0; i < vx.size(); i++){
        _vertexs[i].rank = i;
        _vertexs[i].data = vx[i];
    }
    // 建立邻接矩阵
    for(auto e: edges){
        _adjacency[e.first][e.second].weight = 1;
        _adjacency[e.second][e.first].weight = 1;
    }
    for(auto e:_vertexs){
        cout<<e.data<<" ";
    }
    cout<<endl;
    for(auto e:_adjacency){
        for(auto x:e){
            cout<<x.weight<<" ";
        }
        cout<<endl;
    }
}


#endif