#include "../data_structures/Graph.h"
#include <stack>
#include <unordered_set>

using namespace std;

// Helper function to reverse the edges of a directed graph
template <typename T>
void aux_reverseGraphEdges(Graph<T>* g) {
    for (auto v : g->getVertexSet()) {
        vector<Edge<T>> reversedAdj;
        for (auto e : v->getAdj()) {
            auto dest = e.getDest();
            g->removeEdge(v->getInfo(), dest->getInfo());
            g->addEdge(dest->getInfo(), v->getInfo(), e.getWeight());
        }
    }
}

// Kosaraju-Sharir algorithm to find strongly connected components
template <typename T>
vector<vector<T>> SCCkosaraju(Graph<T>* g)  {
    stack<Vertex<T> *> vertexStack;
    // Step 1: Perform first DFS on the original graph
    for (auto v : g->getVertexSet()) {
        if (!v->isVisited()) {
            firstDFSKosarajuSharir(v, vertexStack);
        }
    }

    // Step 2: Reverse the edges of the graph
    aux_reverseGraphEdges(g);

    // Step 3: Perform second DFS on the transpose graph
    vector<vector<T>> sccs;
    unordered_set<T> visited;
    while (!vertexStack.empty()) {
        auto v = vertexStack.top();
        vertexStack.pop();
        if (visited.find(v->getInfo()) == visited.end()) {
            vector<T> scc;
            secondDFSKosarajuSharir(v, visited, scc);
            sccs.push_back(scc);
        }
    }

    return sccs;
}

// First depth-first search in Kosaraju-Sharir algorithm
template <typename T>
void firstDFSKosarajuSharir(Vertex<T> *v, stack<Vertex <T> *> *vertexStack)  {
    v->setVisited(true);
    for (auto e : v->getAdj()) {
        auto w = e.getDest();
        if (!w->isVisited()) {
            firstDFSKosarajuSharir(w, vertexStack);
        }
    }
    vertexStack->push(v);
}

// Second depth-first search in Kosaraju-Sharir algorithm
template <typename T>
void secondDFSKosarajuSharir(Vertex<T> *v, std::vector<int> & res)  {
    visited.insert(v->getInfo());
    scc.push_back(v->getInfo());
    for (auto e : v->getAdj()) {
        auto w = e.getDest();
        if (visited.find(w->getInfo()) == visited.end()) {
            secondDFSKosarajuSharir(w, visited, scc);
        }
    }
}
