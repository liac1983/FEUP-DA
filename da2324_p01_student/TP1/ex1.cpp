#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include "../data_structures/Graph.h"

using namespace std;
template <typename T>

/****************** toposort ********************/
/*
 * Performs a topological sorting of the vertices of a graph.
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */
vector<T> topsort(const Graph<T>* g) {
    vector<T> res;
    // Calculate indegrees for each vertex
    for (const auto& vertex : g->getVertexSet()) {
        vertex->setIndegree(0);
    }
    for (const auto& vertex : g->getVertexSet()) {
        for (const auto& neighbor : vertex->getAdj()) {
            neighbor.getDest()->setIndegree(neighbor.getDest()->getIndegree() + 1);
        }
    }
    // Queue to store vertices with indegree 0
    queue<Vertex<T>*> zeroIndegreeVertices;
    for (const auto& vertex : g->getVertexSet()) {
        if (vertex->getIndegree() == 0) {
            zeroIndegreeVertices.push(vertex);
        }
    }
    // Perform topological sort
    while (!zeroIndegreeVertices.empty()) {
        Vertex<T>* currVertex = zeroIndegreeVertices.front();
        zeroIndegreeVertices.pop();
        res.push_back(currVertex->getInfo());
        for (const auto& neighbor : currVertex->getAdj()) {
            neighbor.getDest()->setIndegree(neighbor.getDest()->getIndegree() - 1);
            if (neighbor.getDest()->getIndegree() == 0) {
                zeroIndegreeVertices.push(neighbor.getDest());
            }
        }
    }
    // Check for cycle (if not all vertices are visited)
    if (res.size() != g->getNumVertex()) {
        // Return empty vector if cycle exists
        return vector<T>();
    }
    return res;
}