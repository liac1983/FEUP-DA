#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

class Pipe;

/**
 * @brief Class representing a node in the water supply network graph.
 */
class Node {
public:
    friend class Pipe;
    friend class Network;

    /* Constructor */
    Node(int id, std::string code);

    /* Destructor */
    virtual ~Node();

    /* Getters */
    int getID() const;
    std::string getCode() const;
    bool isVisited() const;
    int getCapacity() const;
    int getCapacityValue() const;
    Node *getParent() const;
    const std::vector<Pipe *> &getAdj() const;

    /* Setters */
    void setID(int newID);
    void setCode(std::string newCode);
    void setVisited(bool visited);
    void setCapacity(int capacity);
    void setCapacityValue(int capacityValue);
    void setParent(Node *parent);
    void setAdj(std::vector<Pipe *> &adj);

    /* Operators */
    bool operator==(const Node &rhs) const;
    bool operator!=(const Node &rhs) const;

    /* Functions */
    /**
     * @brief Add a pipe to the node.
     * @param dest The destination node of the pipe.
     * @param cap The capacity of the pipe.
     */
    void addPipe(Node *dest, int capacity);
    /**
     * @brief Remove a pipe connected to the node.
     * @param dest The destination node of the pipe to be removed.
     */
    void removePipe(Node *dest);
    /**
     * @brief Get the pipe connected to the given destination node.
     * @param dest The destination node of the pipe.
     * @return A pointer to the pipe if found, nullptr otherwise.
     */
    Pipe* getPipeTo(Node *dest);
    /**
     * @brief Reset the node to its initial state.
     */
    void resetNode();

private:

    int id;
    std::string code;
    bool visited;
    int capacity;
    int capacityValue;
    Node* parent;
    std::vector<Pipe *> adj;

};

#endif /* NODE_H */
