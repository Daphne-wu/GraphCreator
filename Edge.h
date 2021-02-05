#pragma once
#include "Vertex.h"

class Edge
{
public: 

	Edge();
	~Edge();

	Vertex* getStart();
	Vertex* getEnd();

	void setStart(Vertex* s);
	void setEnd(Vertex* e);
	void setWeight(int w);
	int getWeight();

	Vertex* start;
	Vertex* end;
	int weight; 
};
