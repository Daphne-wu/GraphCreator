#include "Vertex.h"


Vertex::Vertex(int v) {
	label = v; 
	distance = -1;
}

int Vertex::getLabel() {
	return label;
}

void Vertex::setLabel(int inLabel) {
	label = inLabel;
}

int Vertex::getDistance() {
	return distance;
}

void Vertex::setDistance(int d) {
	distance = d;
}
