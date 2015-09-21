/*
Code for parsing the .json file and storing the information in classes
It reads the file line by line and then stores the information in following hirearchy

Edge
Type of Curve  : [id]
Vertices : [id]

get vertices (id)
get curve (id)

*/

#ifndef PROFILE_H
#define PROFILE_H

#include "main.h"

struct Point
{ 
public: 

	double X;
	double Y;

	Point(double a, double b)
	{
		X = a;
		Y = b;
	}

	Point()
	{
		;
	}
};

class Vertex
{
private:

	long Vertex_id;

	Point Vertexpoints;
public:
	long getVertex_id();
	int setVertex_id(long);

	Point getVertexpoints();
	int setVertexpoints(Point);
};

class Edge
{
private: 

	long Edge_id;

	std::string Edge_type;

	long Vertices_id[2];

	Point Center;

	long Edge_clockwisefrom_id;

	double Edge_length;

public:

	long getEdge_id();
	int setEdge_id(long);

	std::string getEdge_type();
	int setEdge_type(std::string);

	long* getVertices_id();
	int setVertices_id(long[]);

	int setCenter(Point);
	Point getCenter();

	long getEdge_clockwisefrom_id();
	int setEdge_clockwisefrom_id(long);

	int setEdge_length(double);
	double getEdge_length();
};

extern std::vector<Edge> edges_data;
extern std::vector<Vertex> vertices_data;

#endif