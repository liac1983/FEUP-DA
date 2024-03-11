#include "../data_structures/Graph.h"
#include "stack"
using namespace std;

// First depth-first search in Kosaraju-Sharir algorithm
template <typename T>
void firstDFSKosarajuSharir(Vertex<T> *v, stack<Vertex<T> *> &vertexStack) {
    v->setVisited(true);
    for (auto e : v->getAdj()) {
        auto w = e.getDest();
        if(!w->isVisited()) {
            firstDFSKosarajuSharir(w,vertexStack);
        }
    }
    vertexStack->push(v);
}

// Second depth-first search in Kosaraju-Sharir algorithm
template <typename T>
void secondDFSKosarajuSharir(Vertex<T> *v, std::vector<int> & res) {
    v->setVisited(true);
    res.push_back(v->getInfo());
    for (auto & e : v->getAdj()) {
        auto w = e.getDest();
        if (!w->isVisited()) {
            secondDFSKosarajuSharir(w, res);
        }
    }
}

// Helper function to reverse the edges of a directed graph
template <typename T>
void aux_reverseGraphEdges(Graph<T>* g) {
    stack<int> edge_stack;
    for (auto v : g->getVertexSet()) {
        for (auto & e : v->getAdj()) {
            auto w = e.getDest();
            edge_stack.push(w->getInfo());
            edge_stack.push(v->getInfo());
        }
    }
// --- Now we invert the edges by removing them and then putting back in reverse.
    while (!edge_stack.empty()) {
        int src;
        int dst;
        dst = edge_stack.top();
        edge_stack.pop();
        src = edge_stack.top();
        edge_stack.pop();
        g->removeEdge(dst, src); // remove original edge
        g->addEdge(src,dst,0); // invert edge
    }
}

template <typename T>
vector<vector<T>> SCCkosaraju(Graph<T>* g)  {
    vector<vector<T>> sccs;
// Set that no vertex has been visited yet
    for (auto v : g->getVertexSet()) {
        v->setVisited(false);
    }
// Perform the first DFS and add push nodes to the stack before returning
    stack<Vertex<T> *> vertexStack;
    for (auto v : g->getVertexSet()) {
        if(!v->isVisited()) {
            firstDFSKosarajuSharir(v, &vertexStack);
        }
    }
// Reverse graph edges
    aux_reverseGraphEdges(g);
// Reset the visited field
    for (auto v : g->getVertexSet()) {
        v->setVisited(false);
    }

    // The incoming edge vector of the Vertex class will be used.
    while(!vertexStack.empty()) {
        Vertex<T> * v = vertexStack.top();
        vertexStack.pop();
        if(!v->isVisited()) {
            vector<T> scc;
            secondDFSKosarajuSharir(v,scc);
            sccs.push_back(scc);
        }
    }
    return sccs;
}
