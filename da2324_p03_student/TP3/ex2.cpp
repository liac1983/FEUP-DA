// Original code by Gonçalo Leão
// Updated by DA 2023/2024 Team

#include "../data_structures/Graph.h"
#include "MSTTestAux.h"

template <class T>
std::vector<Vertex<T> *> prim(Graph<T> * g) {
    // Check if the graph is empty
    if (g->getVertexSet().empty()) {
        return g->getVertexSet(); // Return an empty set if the graph is empty
    }
// Initialize the vertices in the graph
    for(auto v : g->getVertexSet()) {
        v->setDist(INF); // Set distance to infinity
        v->setPath(nullptr); // Set path to null
        v->setVisited(false); // Mark as not visited
    }
// Select the first vertex as the starting point
    Vertex<T>* s = g->getVertexSet().front();
    s->setDist(0); // Set distance of the starting vertex to 0
// Priority queue to store vertices based on their distances
    MutablePriorityQueue<Vertex<T>> q;
    q.insert(s);
// Main loop for the Prim's algorithm
    while( ! q.empty() ) {
// Extract the vertex with the minimum distance from the priority queue
        auto v = q.extractMin();
        v->setVisited(true); // Mark the vertex as visited
// Iterate through the adjacent edges of the current vertex
        for(auto &e : v->getAdj()) {
            Vertex<T>* w = e->getDest(); // Get the destination vertex of the edge
// Check if the destination vertex is not visited
            if (!w->isVisited()) {
                auto oldDist = w->getDist(); // Get the current distance of the destination vertex
// Check if the weight of the edge is less than the current distance of the destination vertex
                if(e->getWeight() < oldDist) {
                    w->setDist(e->getWeight()); // Update the distance of the destination vertex
                    w->setPath(e); // Update the path to the current edge
// If the destination vertex had infinite distance, insert it into the priority queue
                    if (oldDist == INF) {
                        q.insert(w);
                    }
// If the destination vertex had finite distance, decrease its key in the priority queue
                    else {
                        q.decreaseKey(w);
                    }
                }
            }
        }
    }
// Return the set of vertices after the Prim's algorithm completes
    return g->getVertexSet();
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP3_Ex2, test_prim) {
    Graph<int> graph = createMSTTestGraph<int>();
    std::vector<Vertex<int> *> res = prim(&graph);

    std::stringstream ss;
    for(const auto v : res) {
        ss << v->getInfo() << "<-";
        if ( v->getPath() != nullptr ) {
            ss << v->getPath()->getOrig()->getInfo();
        }
        ss << "|";
    }
    std::cout << ss.str() << std::endl;

    EXPECT_TRUE(isSpanningTree(res));
    EXPECT_EQ(spanningTreeCost(res), 11);
}