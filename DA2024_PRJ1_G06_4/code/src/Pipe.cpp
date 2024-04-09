#include "Pipe.h"

/* Constructor */

Pipe::Pipe(Node *src, Node *dest, int capacity) : src(src), dest(dest), capacity(capacity), flow(0), residual(capacity) {}

/* Getters */

Node *Pipe::getSrc() const { return src; }

Node *Pipe::getDest() const { return dest; }

int Pipe::getFlow() const { return flow; }

int Pipe::getCapacity() const { return capacity; }

int Pipe::getResidual() const { return residual; }

/* Setters */

void Pipe::setSrc(Node *newNode) { src = newNode; }

void Pipe::setDest(Node *newNode) { dest = newNode; }

void Pipe::setFlow(int newFlow) { flow = newFlow; }

void Pipe::setCapacity(int newCapacity) { capacity = newCapacity; }

void Pipe::setResidual(int newResidual) { residual = newResidual; }

/* Functions */

void Pipe::resetPipe() { flow = 0; residual = capacity; }
