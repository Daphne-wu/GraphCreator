#pragma once
class Vertex
{
public: 
	
	Vertex(int v);
	//~Vertex();

	int getLabel();
	void setLabel(int v);
	int getDistance();
	void setDistance(int d);

	int label; 
	int distance;
};