#include "funWithGraphs.h"


//=============================================================================
// Exercise 2: Vertex degrees
//=============================================================================
// Subexercise 2.1: outDegree
//=============================================================================
int FunWithGraphs::outDegree(const Graph<int> g, const int &v) {
    if (g.findVertex(v) == NULL) return -1;
    Vertex<int>* v1 = g.findVertex(v);
    return v1->getAdj().size();
}


//=============================================================================
// Subexercise 2.1: inDegree
//=============================================================================
int FunWithGraphs::inDegree(const Graph<int> g, const int &v) {
    int indegree = 0;
    Vertex <int>* v1 = g.findVertex(v);
    if (v1 == NULL) return -1;
    for (auto v2 : g.getVertexSet())
        for (auto & e : v2->getAdj())
            if (e.getDest() == v1)
                indegree++;
    return indegree;
}

//=============================================================================
// Subexercise 2.3: weightedOutDegree
//=============================================================================
// TODO
int FunWithGraphs::weightedOutDegree(const Graph<int> g, const int &v) {
    if (g.findVertex(v) == NULL) return -1;
    int sum = 0;
    Vertex<int>* v1 = g.findVertex(v);
    for (auto & e : v1->getAdj())
        sum += e.getWeight();
    return sum;
}
