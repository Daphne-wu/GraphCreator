#include "Edge.h"

#include <iostream>
Edge::Edge() {
    start = NULL;
    end = NULL;
    weight = 0;
}

Edge::~Edge() {
    delete start;
    delete end;
}

Vertex* Edge::getStart() {
    return start;
}

Vertex* Edge::getEnd() {
    return end;
}

void Edge::setEnd(Vertex* e) {
    end = e;
}

void Edge::setStart(Vertex* s) {
    start = s;
}

void Edge::setWeight(int w) {
    weight = w;
}

int Edge::getWeight() {
    return weight;
}