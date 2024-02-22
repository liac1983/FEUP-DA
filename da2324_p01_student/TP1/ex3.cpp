#include "../data_structures/Graph.h"
#include "stack"
#include <unordered_set>
#include <vector>

using namespace std;

// First depth-first search in Kosaraju-Sharir algorithm
template <typename T>
void firstDFSKosarajuSharir(Vertex<T> *v, stack<Vertex<T> *> &vertexStack) {
    v->setVisited(true);
    for (auto edge : v->getAdj()) {
        auto w = edge.getDest();
        if (!w->isVisited()) {
            firstDFSKosarajuSharir(w, vertexStack);
        }
    }
    vertexStack.push(v);
}

// Second depth-first search in Kosaraju-Sharir algorithm
template <typename T>
void secondDFSKosarajuSharir(Vertex<T> *v, stack<Vertex<T> *> &vertexStack, vector<vector<T>> &sccs) {
    v->setVisited(true);
    vector<T> scc;
    scc.push_back(v->getInfo());
    while (!vertexStack.empty() && !vertexStack.top()->isVisited()) {
        auto w = vertexStack.top();
        vertexStack.pop();
        scc.push_back(w->getInfo());
        w->setVisited(true);
    }
    if (!scc.empty()) {
        sccs.push_back(scc);
    }
}

// Helper function to reverse the edges of a directed graph
template <typename T>
void aux_reverseGraphEdges(Graph<T>* g) {
    // Create a new graph for storing the reversed edges
    Graph<T> reversedGraph;

    // Add vertices to the reversed graph
    for (auto vertex : g->getVertexSet()) {
        reversedGraph.addVertex(vertex->getInfo());
    }

    // Reverse the edges and add them to the reversed graph
    for (auto vertex : g->getVertexSet()) {
        for (auto edge : vertex->getAdj()) {
            reversedGraph.addEdge(edge.getDest()->getInfo(), vertex->getInfo(), edge.getWeight());
        }
    }

    // Clear the original graph and copy the reversed edges back
    g->getVertexSet().clear();
    for (auto vertex : reversedGraph.getVertexSet()) {
        g->addVertex(vertex->getInfo());
        for (auto edge : vertex->getAdj()) {
            g->addEdge(vertex->getInfo(), edge.getDest()->getInfo(), edge.getWeight());
        }
    }
}

template <typename T>
vector<vector<T>> SCCkosaraju(Graph<T>* g)  {
    vector<vector<T>> sccs;
    stack<Vertex<T> *> vertexStack;

    // Step 1: Perform DFS on the original graph and fill the stack
    for (auto vertex : g->getVertexSet()) {
        if (!vertex->isVisited()) {
            firstDFSKosarajuSharir(vertex, vertexStack);
        }
    }

    // Step 2: Reverse the edges of the graph
    aux_reverseGraphEdges(g);

    // Step 3: Perform DFS on the modified graph using elements from the stack
    while (!vertexStack.empty()) {
        auto v = vertexStack.top();
        vertexStack.pop();
        if (!v->isVisited()) {
            secondDFSKosarajuSharir(v, vertexStack, sccs);
        }
    }

    return sccs;
}
