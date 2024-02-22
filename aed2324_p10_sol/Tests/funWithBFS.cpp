#include "funWithBFS.h"


//=============================================================================
// Exercise 2.1: Nodes at distance k
//=============================================================================
// Subexercise 2.1.2: Nodes at distance k (BFS)
//=============================================================================
vector<Person> FunWithBFS::nodesAtDistanceBFS(const Graph<Person> *g, const Person &source, int k) {
    vector<Person> res;
    auto s = g->findVertex(source);
    if (s == nullptr)
        return res;
    queue<Vertex<Person> *> q;
    for (auto v : g->getVertexSet())
        v->setVisited(false);
    q.push(s);
    s->setVisited(true);

    int level = 0;

    while (!q.empty() && level <= k) {
        int size = q.size();

        for (int i = 0; i < size; ++i) {
            auto v = q.front();
            q.pop();

            if (level == k) {
                res.push_back(v->getInfo());
            }

            for (auto & e : v->getAdj()) {
                auto w = e.getDest();
                if ( ! w->isVisited() ) {
                    q.push(w);
                    w->setVisited(true);
                }
            }
        }

        ++level;

    }
    return res;
}

//=============================================================================
// Exercise 2.2: Max New Children
//=============================================================================
int FunWithBFS::maxNewChildren(const Graph<Person> *g, const Person &source, Person &info) {

    int res = 0;
    queue<Vertex<Person>*> q;

    Vertex<Person>* s = g->findVertex(source);

    if (s != nullptr) {
        for (Vertex<Person>* v : g->getVertexSet()) {
            v->setVisited(false);
        }

        q.push(s);
        s->setVisited(true);

        while (!q.empty()) {
            Vertex<Person>* v = q.front(); q.pop();

            int max = 0;

            for (const Edge<Person>& e : v->getAdj()) {
                if (!e.getDest()->isVisited()) {
                    max++;
                    q.push(e.getDest());
                    e.getDest()->setVisited(true);
                }
            }

            if (max > res) {
                res = max;
                info = v->getInfo();
            }
        }
    }

    return res;
}
