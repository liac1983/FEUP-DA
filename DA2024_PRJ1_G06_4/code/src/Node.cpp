#include "Node.h"
#include "Pipe.h"

/* Constructor */

Node::Node(int id, std::string code) : id(id), code(std::move(code)),
    visited(false), capacity(INT16_MAX), capacityValue(INT16_MAX), parent(nullptr) {}

/* Destructor */

Node::~Node() { for(Pipe* pipe : adj) { delete pipe; } }

/* Getters */

int Node::getID() const { return id; }

std::string Node::getCode() const { return code; }

bool Node::isVisited() const { return visited; }

int Node::getCapacity() const { return capacity; }

int Node::getCapacityValue() const { return capacityValue; }

Node *Node::getParent() const { return parent; }

const std::vector<Pipe *> &Node::getAdj() const { return adj; }

/* Setters */

void Node::setID(int newID) { id = newID; }

void Node::setCode(std::string newCode) { code = std::move(newCode); }

void Node::setVisited(bool boolean) { visited = boolean; }

void Node::setCapacity(int newCapacity) { capacity = newCapacity; }

void Node::setCapacityValue(int newCapacityValue) { capacityValue = newCapacityValue; }

void Node::setParent(Node *newParent) { parent = newParent; }

void Node::setAdj(std::vector<Pipe *> &newAdj) { adj = newAdj; }

/* Operators */

bool Node::operator==(const Node &rhs) const { return id == rhs.id && code == rhs.code; }

bool Node::operator!=(const Node &rhs) const { return id != rhs.id || code != rhs.code; }

/* Functions */

void Node::addPipe(Node *dest, int cap)
{
    adj.push_back(new Pipe(this, dest, cap));
}

void Node::removePipe(Node *dest)
{
    for (auto it = adj.begin(); it != adj.end(); it++)
        if ((*it)->dest == dest) { adj.erase(it); return; }
}

Pipe* Node::getPipeTo(Node *dest)
{
    for (auto pipe : adj)
        if (pipe->dest == dest) return pipe;
    return nullptr;
}

void Node::resetNode()
{
    visited = false;
    capacity = capacityValue;
    parent = nullptr;
}
