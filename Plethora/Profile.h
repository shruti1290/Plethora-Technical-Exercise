/*This file contains is the memory profile to store the Edge and Vertex information*/

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

/*Following class stores Vertex data . It has three attributes:
*  1. Vertex id
*	2. Point

	Functions are written to retrieve and set data.
*/
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
/*
Following Class stores Edge data :
*	1. Edge id
*	2. Edge type
*	3. Vertices id : array of two ids
*	4. Center : stores center for circular arc data
*	5. Edge length : to be calculated later, when estimating cost. 
*/
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

/*Extern Vector for Edge and Vertex objects are defined for storing parsed file data in the data structure*/

extern std::vector<Edge> edges_data;
extern std::vector<Vertex> vertices_data;

#endif