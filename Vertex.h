#pragma once
class Vertex
{
public: 
	
	Vertex(char v);
	//~Vertex();

	char getLabel();
	void setLabel(char v);
	int getDistance();
	void setDistance(int d);

	char label; 
	int distance;
};
