#include <list>
#include <unordered_map>
#include "../data_structures/Graph.h"
#include <stack>
using namespace std;

// Declare dfs_scc function before using it
template <typename T>
void dfs_scc(Graph<T> *g, Vertex<T> *v, stack<T> &s, list<list<T>> &l, int &i, unordered_map<T, pair<int, int>> &order_low);

template <typename T>
list<list<T>> sccTarjan(Graph<T>* g) {
    list<list<T>> res;
    stack<T> s;
    int i = 0;
    unordered_map<T, pair<int, int>> order_low;

    for (auto vertex : g->getVertexSet()) {
        if (order_low.find(vertex->getInfo()) == order_low.end()) {
            dfs_scc(g, vertex, s, res, i, order_low);
        }
    }

    return res;
}

template <typename T>
void dfs_scc(Graph<T> *g, Vertex<T> *v, stack<T> &s, list<list<T>> &l, int &i, unordered_map<T, pair<int, int>> &order_low) {
    s.push(v->getInfo());
    order_low[v->getInfo()] = make_pair(i, i);
    i++;

    for (auto edge : v->getAdj()) {
        auto w = edge.getDest();
        if (order_low.find(w->getInfo()) == order_low.end()) {
            dfs_scc(g, w, s, l, i, order_low);
            order_low[v->getInfo()].second = min(order_low[v->getInfo()].second, order_low[w->getInfo()].second);
        } else {
            bool found = false;
            stack<T> tempStack;
            while (!s.empty()) {
                T top = s.top();
                s.pop();
                tempStack.push(top);
                if (top == w->getInfo()) {
                    found = true;
                    break;
                }
            }
            while (!tempStack.empty()) {
                s.push(tempStack.top());
                tempStack.pop();
            }
            if (found) {
                order_low[v->getInfo()].second = min(order_low[v->getInfo()].second, order_low[w->getInfo()].first);
            }
        }
    }

    if (order_low[v->getInfo()].first == order_low[v->getInfo()].second) {
        list<T> scc;
        T w;
        do {
            w = s.top();
            s.pop();
            scc.push_back(w);
            // Removed scc_stack.erase(w); as it's not defined
        } while (w != v->getInfo());
        l.push_back(scc);
    }
}
