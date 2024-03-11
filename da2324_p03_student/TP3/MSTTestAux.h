#ifndef TEST_AUX_H_
#define TEST_AUX_H_

#include "../data_structures/Graph.h"
#include <random>
#include <map>
#include <set>

using namespace std;

template <class T>
Graph<T> createMSTTestGraph();

template <class T>
void generateRandomGridGraph(int n, Graph<T> & g);

template <class T>
bool isSpanningTree(const std::vector<Vertex<T> *> &res);

template <class T>
double spanningTreeCost(const std::vector<Vertex<T> *> &res);


template <class T>
Graph<T> createMSTTestGraph() {
    Graph<int> myGraph;

    for(int i = 1; i <= 7; i++)
        myGraph.addVertex(i);

    myGraph.addBidirectionalEdge(1, 2, 2);
    myGraph.addBidirectionalEdge(1, 4, 7);
    myGraph.addBidirectionalEdge(2, 4, 3);
    myGraph.addBidirectionalEdge(2, 5, 5);
    myGraph.addBidirectionalEdge(3, 1, 2);
    myGraph.addBidirectionalEdge(3, 6, 5);
    myGraph.addBidirectionalEdge(4, 3, 1);
    myGraph.addBidirectionalEdge(4, 5, 1);
    myGraph.addBidirectionalEdge(4, 7, 4);
    myGraph.addBidirectionalEdge(5, 7, 2);
    myGraph.addBidirectionalEdge(6, 4, 3);
    myGraph.addBidirectionalEdge(7, 6, 4);

    return myGraph;
}

template <class T>
void generateRandomGridGraph(int n, Graph<T> & g) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            g.addVertex(i*n + j);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (i < n-1)
                g.addBidirectionalEdge(i*n + j, (i+1)*n + j, dis(gen));
            if (j < n-1)
                g.addBidirectionalEdge(i*n + j, i*n + (j+1), dis(gen));
        }
}

template <class T>
bool isSpanningTree(const std::vector<Vertex<T> *> &res){
    std::map<int, std::set<int> > adj;
    for(const Vertex<T> *v: res) {
        adj[v->getInfo()];
        if (v->getPath() != nullptr) {
            Vertex<T> *u = v->getPath()->getOrig();
            adj[u->getInfo()].emplace(v->getInfo());
            adj[v->getInfo()].emplace(u->getInfo());
        }
    }

    std::queue<int> q;
    std::set<int> visited;
    q.push(res.at(0)->getInfo());
    while(!q.empty()){
        int u = q.front(); q.pop();
        if(visited.count(u)) continue;
        visited.emplace(u);
        for(const int &v: adj.at(u)){
            q.emplace(v);
        }
    }

    for(const Vertex<T> *v: res)
        if(!visited.count(v->getInfo())) return false;
    return true;
}

template <class T>
double spanningTreeCost(const std::vector<Vertex<T> *> &res){
    double ret = 0;
    for(const Vertex<T> *v: res){
        if(v->getPath() == nullptr) continue;
        const Vertex<T> *u = v->getPath()->getOrig();
        for(const auto e: u->getAdj()){
            if(e->getDest()->getInfo() == v->getInfo()){
                ret += e->getWeight();
                break;
            }
        }
    }
    return ret;
}



#endif //TEST_AUX_H_
