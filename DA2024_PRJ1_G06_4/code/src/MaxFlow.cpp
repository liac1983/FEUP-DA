#include "Network.h"

#include "Pipe.h"

#include <queue>

using namespace std;

bool Network::findAugmentingPath(Node *s, Node *t)
{
    for (const auto& pair : nodeSet)
    {
        pair.second->setVisited(false);
        pair.second->setParent(nullptr);
    }

    std::queue<Node *> q;
    q.push(s);
    s->setVisited(true);

    while (!q.empty())
    {
        Node *current = q.front();
        q.pop();

        for (auto pipe : current->getAdj())
        {
            Node *neighbour = pipe->getDest();

            if (!neighbour->isVisited() && pipe->getResidual() > 0 && neighbour->getCapacity() > 0)
            {
                neighbour->setVisited(true);
                neighbour->setParent(current);
                if (neighbour == t) return true;
                q.push(neighbour);
            }
        }
    }

    return false;
}

int Network::findMinResidualAlongPath(Node *s, Node *t)
{
    Node *current = t;

    int minResidual = current->getCapacity();

    while (current != s)
    {
        Pipe *pipe = current->getParent()->getPipeTo(current);

        minResidual = min(minResidual, pipe->getResidual());

        current = current->getParent();

        minResidual = min(minResidual, current->getCapacity());
    }

    return minResidual;
}

void Network::augmentFlowAlongPath(Node *s, Node *t, int f)
{
    Node *current = t;

    current->setCapacity(current->getCapacity() - f);

    while (current != s)
    {
        Node *parent = current->getParent();

        parent->setCapacity(parent->getCapacity() - f);

        Pipe *pipe = parent->getPipeTo(current);
        pipe->setFlow(pipe->getFlow() + f);
        pipe->setResidual(pipe->getResidual() - f);

        Pipe *inversePipe = current->getPipeTo(parent);
        if (inversePipe != nullptr)
            inversePipe->setResidual(inversePipe->getResidual() + f);

        current = parent;
    }
}

int Network::edmondsKarp()
{
    resetNetwork();

    int maxFlow = 0;

    while (findAugmentingPath(superSrc, superSink))
    {
        int minResidual = findMinResidualAlongPath(superSrc, superSink);
        augmentFlowAlongPath(superSrc, superSink, minResidual);
        maxFlow += minResidual;
    }

    return maxFlow;
}
