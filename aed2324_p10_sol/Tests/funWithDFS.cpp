#include "funWithDFS.h"


//=============================================================================
// Exercise 2.1: Nodes at distance k
//=============================================================================
// Subexercise 2.1.1: Nodes at distance k (DFS)
//=============================================================================
void nodesAtDistanceDFSVisit(const Graph<Person> *g, Vertex<Person> *v, int k, vector<Person> &res);
vector<Person> FunWithDFS::nodesAtDistanceDFS(const Graph<Person> *g, const Person &source, int k) {
    vector<Person> res;
    auto s = g->findVertex(source);
    if (s == nullptr)
        return res;

    for (auto v: g->getVertexSet())
        v->setVisited(false);

    nodesAtDistanceDFSVisit(g, s, k, res);
    return res;
}

void nodesAtDistanceDFSVisit(const Graph<Person> *g, Vertex<Person> *v, int k, vector<Person> &res) {
    if (k == 0) {
        res.push_back(v->getInfo());
        return;
    }

    v->setVisited(true);

    for (auto & e : v->getAdj()) {
        auto w = e.getDest();
        if (! w->isVisited()) {
            nodesAtDistanceDFSVisit(g, w, k - 1, res);
        }
    }
}


//=============================================================================
// Exercise 2.3: Directed Acyclic Graph
//=============================================================================
bool dfsIsDAG(Vertex<int> *v);
bool FunWithDFS::isDAG(Graph<int> g) {
    for (auto v : g.getVertexSet()) {
        v->setVisited(false);
        v->setProcessing(false);
    }
    for (auto v : g.getVertexSet())
        if (! v->isVisited())
            if ( ! dfsIsDAG(v) )
                return false;
    return true;
}

bool dfsIsDAG(Vertex<int> *v) {
    v->setVisited(true);
    v->setProcessing(true);
    for (auto & e : v->getAdj()) {
        auto w = e.getDest();
        if (w->isProcessing())
            return false;
        if (! w->isVisited())
            if (! dfsIsDAG(w))
                return false;
    }
    v->setProcessing(false);
    return true;
}
