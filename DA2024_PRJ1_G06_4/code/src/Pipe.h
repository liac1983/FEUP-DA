#ifndef PIPE_H
#define PIPE_H

class Node;

/**
 * @brief Class representing a pipe connecting two nodes in the water supply network graph.
 */
class Pipe {
public:
	friend class Node;
    friend class Network;

    /* Constructor */
    Pipe(Node *src, Node *dest, int capacity);

    /* Getters */
    Node *getSrc() const;
    Node *getDest() const;
    int getFlow() const;
    int getCapacity() const;
    int getResidual() const;

    /* Setters */
    void setSrc(Node *newNode);
    void setDest(Node *newNode);
    void setFlow(int newFlow);
    void setCapacity(int newCapacity);
    void setResidual(int newResidual);

    /* Functions */
    /**
     * @brief Reset the pipe to its initial state.
     */
    void resetPipe();

private:

    Node *src;
    Node *dest;
    int flow;
    int capacity;
    int residual;

};

#endif //PIPE_H
