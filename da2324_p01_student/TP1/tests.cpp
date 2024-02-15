#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../data_structures/Graph.h"
#include "ex1.cpp"
#include "ex2.cpp"
#include "ex3.cpp"
#include "ex4.cpp"

using testing::Eq;

TEST(TP1_Ex1, test_topsort) {
    Graph<int> myGraph;
    myGraph.addVertex(1); myGraph.addVertex(2); myGraph.addVertex(3); myGraph.addVertex(4);
    myGraph.addVertex(5); myGraph.addVertex(6); myGraph.addVertex(7);

    myGraph.addEdge(1, 2, 0);
    myGraph.addEdge(1, 4, 0);
    myGraph.addEdge(1, 3, 0);
    myGraph.addEdge(2, 5, 0);
    myGraph.addEdge(2, 4, 0);
    myGraph.addEdge(3, 6, 0);
    myGraph.addEdge(4, 3, 0);
    myGraph.addEdge(4, 6, 0);
    myGraph.addEdge(4, 7, 0);
    myGraph.addEdge(5, 4, 0);
    myGraph.addEdge(5, 7, 0);
    myGraph.addEdge(7, 6, 0);

    std::vector<int> topOrder = topsort(&myGraph);
    EXPECT_EQ(topOrder.size(), 7);

    // to test including a cycle in the graph
    myGraph.addEdge(3, 1, 0);


    topOrder = topsort(&myGraph);
    EXPECT_EQ(topOrder.size(), 0);
}

TEST(TP1_Ex2, test_isDAG) {
    Graph<int> myGraph;

    for( int i = 0; i < 6; i++) {
        myGraph.addVertex(i);
    }

    myGraph.addEdge(1, 2, 0);
    myGraph.addEdge(2, 5, 0);
    myGraph.addEdge(5, 4, 0);
    myGraph.addEdge(3, 1, 0);
    myGraph.addEdge(0, 4, 0);

    EXPECT_EQ(isDAG(&myGraph), true);

    myGraph.addEdge(4, 1, 0);

    EXPECT_EQ(isDAG(&myGraph), false);
}

TEST(TP1_Ex3, test_SCC_kosaraju) {
    Graph<int>  graph;

    for( int i = 0; i <= 7; i++) {
        graph.addVertex(i);
    }

    graph.addEdge(0,1,0);
    graph.addEdge(1,2,0);
    graph.addEdge(2,0,0);
    graph.addEdge(2,3,0);
    graph.addEdge(3,4,0);
    graph.addEdge(4,7,0);
    graph.addEdge(4,5,0);
    graph.addEdge(5,6,0);
    graph.addEdge(6,7,0);
    graph.addEdge(6,4,0);

    vector<vector<int>> sccs =SCCkosaraju(& graph);

    EXPECT_EQ(sccs.size(), 4);

}

TEST(TP1_Ex4, test_SCC_Tarjan) {
    Graph<int> g;
    for (int i = 1; i <= 8; i++)
        g.addVertex(i);
    g.addEdge(1, 2, 0);
    g.addEdge(2, 3, 0);
    g.addEdge(4, 3, 0);
    g.addEdge(5, 1, 0);
    g.addEdge(2, 6, 0);
    g.addEdge(7, 3, 0);
    g.addEdge(3, 8, 0);
    g.addEdge(8, 4, 0);
    g.addEdge(6, 5, 0);
    g.addEdge(8, 7, 0);

    list<list<int>> lscc = sccTarjan(&g);
    EXPECT_EQ(2, lscc.size());
    for (auto &l: lscc) l.sort();
    lscc.sort();
    list<list<int>> res = {{1, 2, 5, 6},
                           {3, 4, 7, 8}};
    EXPECT_EQ(lscc, res);
}