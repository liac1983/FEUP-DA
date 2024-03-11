#include <list>
#include "../data_structures/Graph.h"
#include <stack>
using namespace std;

// Declare dfs_scc function before using it
template <typename T>
void dfs_scc(Graph<T> *g, Vertex<T> *v, stack<T> &s, list<list<T>> &l, int &i);

template <typename T>
list<list<T>> sccTarjan(Graph<T>* g) {
    int index = 1;
    stack<T> s;
    list<list<T>> res;
    for(auto j : g->getVertexSet()){
        j->setVisited(false);
    }
    for(auto i : g->getVertexSet()){
        if(!i->isVisited()){
            dfs_scc(g, i,s, res, index);
        }
    }
    return res;
}

template <typename T>
void dfs_scc(Graph<T> *g, Vertex<T> *v, stack<T> &s, list<list<T>> &l, int &i) {
    v->setVisited(true);
    v->setLow(i);
    v->setNum(i);
    v->setProcessing(true);
    s.push(v->getInfo());
    i++;
    for (auto & e : v->getAdj()) {
        auto w = e.getDest();
        if (!w->isVisited()) {
            dfs_scc(g, w, s, l, i);
            v->setLow(min(v->getLow(), w->getLow()));
        } else if (w->isProcessing())
            v->setLow(min(v->getLow(), w->getNum()));
    }
    if (v->getNum() == v->getLow()) {
        Vertex<int> *w;
        list<int> scc;
        do {
            w = g->findVertex(s.top());
            w->setProcessing(false);
            scc.push_front(w->getInfo());
            s.pop();
        } while (w != v);
        l.push_front(scc);
    }
}
