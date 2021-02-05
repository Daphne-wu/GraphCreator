//Daphne Wu
//Graph creator program holds vertex and edge connections
//Using a vector implementation

#include <iostream>
#include <vector>
#include <cstring>
#include <limits.h>
#include "Vertex.h"
#include "Edge.h"

using namespace std;

//function prototypes
void addVertex(char v, vector<Vertex*> &vertices);
void removeVertex(char v, vector<Vertex*> &vertices, vector<Edge*> &edges);
void addEdge(char start, char end, int weight, vector<Vertex*> &vertices, vector<Edge*> &edges);
void removeEdge(char start, char end, vector<Vertex*> &vertices, vector<Edge*> &edges);
void visual(vector<Vertex*> &vertices, vector<Edge*> &edges);
void shortestPath(char start, char end, vector<Vertex*> &vertices, vector<Edge*> &edges);


int main() {

	 // using vectors to store info of vertices and edges
    vector<Vertex*> vertices;
    vector<Edge*> edges;
    bool running = true;


    cout << "The Graph Creator Program." << endl;

    while(running) {
    	cout << "What would you like to do? ADD, REMOVE, PRINT, FINDSP, or QUIT" << endl;
    	char* input = new char();
        cin.getline(input, 80, '\n');
        // if add
        if (strcmp(input, "ADD") == 0) {
            cout << "Would you like to add a VERTEX or EDGE?" << endl;
            cin.getline(input, 80, '\n');
            // if Vertex
            if (strcmp(input, "VERTEX") == 0) {
                cout << "Enter the label for the vertex: ";
                char v;
                cin >> v;
                cin.get();
                addVertex(v, vertices);
            }
            // if Edge
            else if (strcmp(input, "EDGE") == 0) {
                cout << "Enter the label of the starting vertex: ";
                char s;
                cin >> s;
                cin.get();
                cout << "Enter the label of the ending vertex: ";
                char e;
                cin >> e;
                cin.get();
                cout << "Enter the weight of the edge: ";
                char weight;
                cin >> weight;
                cin.get();
                addEdge(s, e, weight, vertices, edges);
            }
            else {
                cout << "Oops, improper command. Try again:)" << endl;
            }
        }
        // if  remove 
        else if(strcmp(input, "REMOVE") == 0) {
            cout << "Would you like to remove a VERTEX or EDGE?" << endl;
            cin.getline(input, 80, '\n');
            // if vertex
            if (strcmp(input, "VERTEX") == 0) {
                cout << "Enter the label of the vertex you would like to remove: ";
                char v;
                cin >> v;
                cin.get();
                removeVertex(v, vertices, edges);
            }
            // if edge
            else if (strcmp(input, "EDGE") == 0) {
                cout << "Enter the label of the starting vertex: ";
                char s;
                cin >> s;
                cin.get();
                cout << "Enter the label of the ending vertex: ";
                char e;
                cin >> e;
                cin.get();
                removeEdge(s, e, vertices, edges);
            }
        }
        // if want to find the shortest path between two vertices
        else if(strcmp(input, "FINDSP") == 0) {
            cout << "Enter the label of the starting vertex: ";
            char s;
            cin >> s;
            cin.get();
            cout << "Enter the label of the ending vertex: ";
            char e;
            cin >> e;
            cin.get();
            shortestPath(s, e, vertices, edges);

        }
        // if want to print adjacency matrix
        else if (strcmp(input, "PRINT") == 0) {
            visual(vertices, edges);
        }
        // if want quit
        else if (strcmp(input, "QUIT") == 0) {
        	 cout << "Hope to see you soon!" << endl;
        	 cout << " ________________________" << endl;
            running = false;
        }
    }

	return 0;
}





// checks to see if the vertex label already is in the list, otherwise, the label is pushed to the vector
void addVertex(char v, vector<Vertex*> &vertices) {
    Vertex* vertex = new Vertex(v);
    bool found = false; 
    for (vector<Vertex*>::iterator it = (vertices).begin(); it != (vertices).end(); ++it) {
        if ((*it)->getLabel() == v) {
            found = true; 
        }
    }

    if (found == false) {
        vertices.push_back(vertex);
    }
    else {
        cout << "Oops, looks like this label is already in the graph. Try again?" << endl;
        delete vertex;
    }
}

// adds an edge that connects two vertices
void addEdge(char startLabel, char endLabel, int weight, vector<Vertex*> &vertices, vector<Edge*> &edges) {
    Edge* edge = new Edge();
    Vertex* start = NULL;
    Vertex* end = NULL;
    bool exists = false;

    // iterates through the verticies to find starting and end vertices
    for (vector<Vertex*>::iterator it = (vertices).begin(); it != (vertices).end(); ++it) {
        if ((*it)->getLabel() == startLabel) {
            start = *it;
        }

        if ((*it)->getLabel() == endLabel) {
            end = *it;
        }
    }

    // if start and end are the same node, prints error message 
    if (start == end) {
        cout << "Oops! A node cannot connect to itself. In spirit, it's connect though :)." << endl;
        return;
    }

    // iterate through edges to detemine if the edge already exists
    for (vector<Edge*>::iterator it = (edges).begin(); it != (edges).end(); ++it) {
        if ((*it)->getStart() == start && (*it)->getEnd() == end) {
            exists = true; 
        }
    }

    // if vertices exists and the edge doesn't exist, the edge is created and added to the edges vector
    if (start != NULL && end != NULL && exists == false) {
        edge = new Edge();
        edge->setStart(start);
        edge->setEnd(end);
        edge->setWeight(weight);
        edges.push_back(edge);
    }
    //display error message if edge already exists
    else if (exists == false) {
        cout << "Opps, this edge already exists." << endl;
        delete edge;
    }
    // otherwise one of the vertices cannot be found, cout error message
    else {
        cout << "Oops, one of the vertices you entered does not exist. Enter it's long lost soulmate!" << endl;
        delete edge;
    }
}

// removes the edge connecting two vertices
void removeEdge(char startLabel, char endLabel, vector<Vertex*> &vertices, vector<Edge*> &edges) {
    Vertex* start = NULL;
    Vertex* end = NULL;
    bool exists = false;
    int count = 0;
    int index = -1;

    // iterates through the vector finds the start and end vertices of edge 
    for (vector<Vertex*>::iterator it = (vertices).begin(); it != (vertices).end(); ++it) {
        if ((*it)->getLabel() == startLabel) {
            start = *it;
        }

        if ((*it)->getLabel() == endLabel) {
            end = *it;
        }
    }

    // error message is printed if vertices aren't be found
    if (start == NULL && end == NULL) {
        cout << "Sorry, those vertices do not exist" << endl;
        return;
    }

    // finds the index of the edge, and checks to see if the edge exists
    for (vector<Edge*>::iterator it = (edges).begin(); it != (edges).end(); ++it) {
        if ((*it)->getStart() == start && (*it)->getEnd() == end) {
            index = count;
            exists = true;
        }
        count++;
    }

    // if exists, removed at said index
    if (index != -1) {
        edges.erase(edges.begin() + index);
    }

    // if does not exist, error message is displayed
    if (exists == false) {
        cout << "It seems the edge you want to remove doesn't exist. Try again?" << endl;
        return;
    }
}

// removes vertex from  graph
void removeVertex(char v, vector<Vertex*> &vertices, vector<Edge*> &edges) {
    bool connected = false;
    int max = edges.size();
    int count = 0;
    Edge* arr[20];
    int index = 0;
    for (int i = 0; i < 20; i++) {
        arr[i] = NULL;
    }

    // iterates through vertices to find vertex to be deleted
    for (vector<Vertex*>::iterator it = (vertices).begin(); it != (vertices).end(); ++it) {
        if ((*it)->getLabel() == v) {
            // if found checks to see if vertex has is connected to an edge 
            for (vector<Edge*>::iterator itt = (edges).begin(); itt != (edges).end(); ++itt) {
                if ((*itt)->getStart() == *it || (*itt)->getEnd() == *it) {
                    connected = true;
                }
            }
            // if is connected
            if (connected == true) {
                //cout << "connected to edge" << endl;
                bool looped = false;
                    // itertates through edges to findedge to be deleted. Stores the edges in the array
                    for (vector<Edge*>::iterator itt = (edges).begin(); itt != (edges).end(); ++itt) {
                        if (count + 1 == max) {
                            looped = true;
                        }

                        if ((*itt)->getStart() == *it || (*itt)->getEnd() == *it) {
                            
                            arr[index] = *itt;
                            index++;
                            
                        }
                        count++;
                        if (looped == true) {
                            itt = (edges).end() - 1;
                        }
                    }
                // deletes  edges connected to vertex
                if (arr[0] != NULL)
                    for (int i = index; i > 0; i--) {
                        Edge* e = arr[i - 1];
                        removeEdge(e->getStart()->getLabel(), e->getEnd()->getLabel(), vertices, edges);
                    }
                    
            }
            // deletes the vertex
            vertices.erase(it);
            return;
        }
    }
}

//dijkstra algorithm to find shortes path with help from wiki and pranav sharma
void shortestPath(char startLabel, char endLabel, vector<Vertex*> &vertices, vector<Edge*> &edges) {
    Vertex* start = NULL;
    Vertex* end = NULL;

    // finds the vertices of the start and end labels 
    for (vector<Vertex*>::iterator it = (vertices).begin(); it != (vertices).end(); ++it) {
        if ((*it)->getLabel() == startLabel) {
            start = *it;
        }

        if ((*it)->getLabel() == endLabel) {
            end = *it;
        }
    }

    // if vertices arent found or are the same , error message is displayed
    if (start == NULL || end == NULL || start == end) {
        cout << "Oops! A vertices does not exist or you've entered the same vertex for start and end :(. Try again?" << endl;
        return;
    }

    // if there are edges stores in graph, find the shortest path 
    // visits every unvisited vertex and updates distance from currently held vertex. After moving through every vertex conenction from current vertex, current gets replaced by the next closest vertex until all vertexs are visited
    if (edges.empty() == false) {
        vector<Vertex*> visited;
        vector<Vertex*> unvisited = vertices;
        Vertex* current = NULL;

        start->setDistance(0);
        current = start;

        //while have not visited all vertecies 
        while (unvisited.empty() == false) {
            int distance = current->getDistance();
            //iterate through the unvisited verticies and for each thats not current find the path through the edges to the current 
            for (vector<Vertex*>::iterator it = (unvisited).begin(); it != (unvisited).end(); ++it) {
                if ((*it)->getLabel() != current->getLabel()) {
                    for (vector<Edge*>::iterator ite = (edges).begin(); ite != (edges).end(); ++ite) {
                        Edge* e = *ite;
                        //and if the unvisited connects back to the current hold the disctance value
                        if (e->getStart()->getLabel() == current->getLabel() && e->getEnd()->getLabel() == (*it)->getLabel()) {
                            if ((*it)->getDistance() == -1 || (*it)->getDistance() > distance + e->getWeight()) {
                                (*it)->setDistance(distance + e->getWeight());
                            }
                        }
                    }
                }
            }

            //erases current vertex from the vector of unvisted vertexs
            for (vector<Vertex*>::iterator it = (unvisited).begin(); it != (unvisited).end(); ++it) {
                if ((*it)->getLabel() == current->getLabel()) {
                    unvisited.erase(it);
                    visited.push_back(current);
                    break;
                }
            }
            Vertex* held = NULL;
            // updates current vertex
            for (vector<Vertex*>::iterator it = (unvisited).begin(); it != (unvisited).end(); ++it) {
                if (held == NULL) {
                    held = *it;
                }
                //if distabce value of held vertex is > it then update it to held and held to current
                if (held->getDistance() > (*it)->getDistance() && (*it)->getDistance() > 0) {
                    held = *it;
                }
                current = held;
            }

            // finds ending vertex and displays the shortes distance to the vertex
            for (vector<Vertex*>::iterator it = (visited).begin(); it != (visited).end(); ++it) {
                if ((*it)->getLabel() == endLabel) {
                    if ((*it)->getDistance() > 0) {
                        cout << "The shortest distance between " << startLabel << " and " << endLabel << " is: " << (*it)->getDistance() << endl;
                        return;
                    }
                    else if ((*it)->getDistance() == -1) {
                        cout << "Seems like the vertices are not connected :(. Try again?" << endl;
                    }
                }
            }
        }

    }
    // if there are no edges
    else if (edges.empty()) {
        cout << "There are currently no edges to be searched" << endl;
    }
    else {
        // vertices cannot be found
        cout << "One of the vertices don't exist" << endl;
        // reset variables
        for (vector<Vertex*>::iterator it = (vertices).begin(); it != (vertices).end(); ++it) {
            (*it)->setDistance(-1);
        }
        start = NULL;
        end = NULL;
    }

}


void visual(vector<Vertex*> &vertices, vector<Edge*> &edges) {
    cout << "\t";
    // prints the top row holding vertices 
    for (vector<Vertex*>::iterator it = (vertices).begin(); it != (vertices).end(); ++it) {
        cout << (*it)->getLabel() << "\t";
    }
    cout << endl;

    // prints the body
    for (vector<Vertex*>::iterator it = (vertices).begin(); it != (vertices).end(); ++it) {
        // prints the side column with vertices
        cout << (*it)->getLabel() << "\t";
        // iterate through vertcits and edges if there are connections between verticies display weight of connection
        for (vector<Vertex*>::iterator it1 = (vertices).begin(); it1 != (vertices).end(); ++it1) {
            bool connect = false;
            if (it == it1) {
                connect = true;
            }
            else {
                for (vector<Edge*>::iterator ite = (edges).begin(); ite != (edges).end(); ++ite) {
                    if ((*ite)->getStart() == *it && (*ite)->getEnd() == *it1) {
                        cout << (*ite)->getWeight();
                        connect = true;
                    }
                }
            }
            cout << "\t";

        }
        cout << endl;
    }
}
