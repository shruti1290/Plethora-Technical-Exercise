#include"Profile.h"
#include"main.h"


long Vertex::getVertex_id()
{
	return this->Vertex_id;
}


int Vertex::setVertex_id(long V)
{
	this->Vertex_id = V;
	return 0;
}

Point Vertex::getVertexpoints()
{
	return this->Vertexpoints;
}


int Vertex::setVertexpoints(Point P)
{
	this->Vertexpoints.X = P.X;
	this->Vertexpoints.Y = P.Y;
	return 0;
}

long Edges::getEdge_id()
{

	return this->Edge_id;

}
int Edges::setEdge_id(long id)
{
	this->Edge_id = id;
	return 0;
}

std::string Edges::getEdge_type()
{
	return this->Edge_type;
}
int Edges::setEdge_type(std::string n)
{
	this->Edge_type = n;
	return 0;
}

long* Edges::getVertices_id()
{
	return this->Vertices_id;
}
int Edges::setVertices_id(long V[2])
{
	this->Vertices_id[0] = V[0];
	this->Vertices_id[1] = V[1];
	return 0;
}

int Edges::setCenter(Point P)
{
	this->Center = P;
	return 0;
}
Point Edges::getCenter()
{
	return this->Center;
}

long Edges::getEdge_clockwisefrom_id()
{
	return this->Edge_clockwisefrom_id;
}

int Edges::setEdge_clockwisefrom_id(long form)
{
	this->Edge_clockwisefrom_id = form;
	return 0;
}


