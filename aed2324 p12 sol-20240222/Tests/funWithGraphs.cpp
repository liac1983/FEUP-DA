#include "funWithGraphs.h"

//=============================================================================
// Exercise 2.1: Connected Components
//=============================================================================
// TODO
void dfsVisit(Vertex<int> *v);
int funWithGraphs::connectedComponents(Graph<int> *g) {
    int count = 0;
    for (auto v : g->getVertexSet())
        v->setVisited(false);
    for (auto v : g->getVertexSet())
        if (! v->isVisited()) {
            dfsVisit(v);
            count++;
        }

    return count;
}

void dfsVisit(Vertex<int> *v) {
    v->setVisited(true);
    for (auto & e : v->getAdj()) {
        auto w = e.getDest();
        if ( ! w->isVisited())
            dfsVisit(w);
    }
}


//=============================================================================
// Exercise 2.2: Giant Component
//=============================================================================
// TODO
int dfsGC(Vertex<int> *v);
int funWithGraphs::giantComponent(Graph<int> *g) {
    int giant = 0;
    for (auto v : g->getVertexSet())
        v->setVisited(false);
    for (auto v : g->getVertexSet())
        if (! v->isVisited()) {
            int count = dfsGC(v);
            if (count > giant) giant = count;
        }
    return giant;
}

// DFS extended to count nodes (made new version to leave original dfs untouched for the student package)
int dfsGC(Vertex<int> *v) {
    v->setVisited(true);
    int count = 1;
    for (auto & e : v->getAdj()) {
        auto w = e.getDest();
        if ( ! w->isVisited())
            count += dfsGC(w);
    }
    return count;
}




//=============================================================================
// Exercise 2.3: Strongly Connected Components
//=============================================================================
// TODO
// Auxiliary functions for Tarjan's algorithm
void dfs_scc(Graph<int> *g, Vertex<int> *v, stack<int> &s, list<list<int>> &l, int &i);

/*
// Auxiliary functions for Kosaraju's algorithm
void dfs_pass_one(const Graph<int> *g, Vertex<int> *v, stack<int> &s);
void dfs_pass_two(const Graph<int> *g, Vertex<int> *v, list<int>&l);
*/

list<list<int>> funWithGraphs::scc(Graph<int> *g){
    list<list<int>> res;
    stack<int> s;
    int index = 1;
    for (auto v : g->getVertexSet())
        v->setVisited(false);

    for (auto v : g->getVertexSet()) {
        if (! v->isVisited())
            dfs_scc(g, v, s, res, index);
    }

    return res;
}

void dfs_scc(Graph<int> *g, Vertex<int> *v, stack<int> &s, list<list<int>> &l, int &i){
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


/*
// Auxiliary functions
list<list<int>> scc(Graph<int> *g) {
    // Step 1: Create an empty stack and mark all vertices as unvisited.
    stack<int> s;
    for (auto v : g->getVertexSet())
        v->setVisited(false);


    // Step 2: For each unvisited vertex in the graph, perform a depth-first search.
    for (auto v : g->getVertexSet()) {
        if (! v->isVisited())
            dfs_pass_one(g, v, s);
    }

    // Step 3: Create a reverse graph by reversing the direction of all edges.
    Graph<int> rg;
    for (auto v : g->getVertexSet()) {
        rg.addVertex(v->getInfo());
        for (auto &e: v->getAdj()) {
            auto w = e.getDest();
            rg.addVertex(w->getInfo());
            rg.addEdge(w->getInfo(), v->getInfo(), e.getWeight());
        }
    }

    // Step 4: Pop vertices from the stack and perform a depth-first search on the reverse graph.
    for (auto v : rg.getVertexSet())
        v->setVisited(false);
    list<list<int>> lscc;
    while (!s.empty()) {
        auto v = rg.findVertex(s.top());
        s.pop();
        if (!v->isVisited()) {
            list<int> scc;
            dfs_pass_two(&rg, v, scc);
            lscc.push_back(scc);
        }
    }

    // Step 5: Return the set of strongly connected components.
    return lscc;
}

void dfs_pass_one(const Graph<int> *g, Vertex<int> *v, stack<int> &s) {
    v->setVisited(true);
    for (auto & e : v->getAdj()) {
        auto w = e.getDest();
        if ( ! w->isVisited())
            dfs_pass_one(g, w, s);
    }
    s.push(v->getInfo());
}

void dfs_pass_two(const Graph<int> *g, Vertex<int> *v, list<int>&l) {
    v->setVisited(true);
    l.push_back(v->getInfo());
    for (auto & e : v->getAdj()) {
        auto w = e.getDest();
        if ( ! w->isVisited())
            dfs_pass_two(g, w, l);
    }
}
*/


//=============================================================================
// Exercise 2.4: Articulation Points
//=============================================================================
// TODO
void dfs_art(Graph<int> *g, Vertex<int> *v, stack<int> &s, unordered_set<int> &res, int &i);
unordered_set<int> funWithGraphs::articulationPoints(Graph<int> *g) {
    unordered_set<int> res;
    stack<int> s;
    int index = 1;
    for (auto v : g->getVertexSet())
        v->setVisited(false);

    for (auto v : g->getVertexSet()) {
        if (! v->isVisited())
            dfs_art(g, v, s, res, index);
    }

    return res;
}

void dfs_art(Graph<int> *g, Vertex<int> *v, stack<int> &s, unordered_set<int> &l, int &i){
    v->setVisited(true);

    v->setLow(i);
    v->setNum(i);
    v->setProcessing(true);
    s.push(v->getInfo());
    i++;

    int count = 0;

    for (auto & e : v->getAdj()) {
        auto w = e.getDest();
        if (!w->isVisited()) {
            count++;
            dfs_art(g, w, s, l, i);
            v->setLow(min(v->getLow(), w->getLow()));
            if (w->getLow() >= v->getNum() && v->getNum() != 1)
                l.insert(v->getInfo());
        } else if (w->isProcessing())
            v->setLow(min(v->getLow(), w->getNum()));
        if (count > 1 && v->getNum() == 1)
            l.insert(v->getInfo());
    }

    v->setProcessing(false);
    s.pop();
}