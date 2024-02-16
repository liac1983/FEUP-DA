#include "../data_structures/Graph.h"

using namespace std;

/****************** isDAG  ********************/
/*
 * Performs a depth-first search in a graph, to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */
template <typename T>
bool isDAG(const Graph<T>* g)  {
    // Mark all vertices as not visited and not processing
    for (const auto& vertex : g->getVertexSet()) {
        vertex->setVisited(false);
        vertex->setProcessing(false);
    }

    // Perform DFS on each unvisited vertex
    for (const auto& vertex : g->getVertexSet()) {
        if (!vertex->isVisited()) {
            if (!dfsIsDAG(vertex))
                return false; // Cycle found, not a DAG
        }
    }

    // If DFS traversal completes without finding a cycle, the graph is a DAG
    return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
template<class T>
bool dfsIsDAG(Vertex<T> *v)  {
    // If the vertex is currently being processed, then a cycle is found
    if (v->isProcessing())
        return false;

    // Mark the vertex as being processed
    v->setProcessing(true);

    // Recursively visit adjacent vertices
    for (const auto& neighbor : v->getAdj()) {
        if (!dfsIsDAG(neighbor.getDest()))
            return false;
    }

    // Mark the vertex as visited and no longer being processed
    v->setVisited(true);
    v->setProcessing(false);
    return true;
}

