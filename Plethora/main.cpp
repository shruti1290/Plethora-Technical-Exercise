/* This file calculates the Quotation information for the parsed file*/
/*It takes input .txt file (.json) file format, then from the data stored in the data structure, Cost is estimated*/
/*Cost Estimation is done based on the given equation, proportional to area and the perimeter of the stock and the nature of the cut*/
/*For Circular arc , first the type of cut is identified by taking cross product of the vertices. */


#include"main.h"
#include"Parser.h"
#include"Profile.h"


using namespace std;
int cross_product(Point, Point);
Point fetch_pointFromid(long);
double calculate_dist(Point, Point);
double calculate_angle(Point, Point, Point);

int main()
{
	
	//parsefile("Rectangle.json.txt");

	//parsefile("CutCircularArc.json.txt");
	
	//parsefile("ExtrudeCircularArc.json.txt");
	
		
	printf("%.2lf dollars", calculate_quote());
	
	_getch();
	return 0;
}

double calculate_quote()
{
	double material_cost, machine_cost, total_cost = 0.0;

	
	/*calculation of area of stock*/
	static double length = 0, breadth = 0, length_change = 0;
	double perimeter_line = 0, perimeter_arc = 0, R = 1, arc_edge_length = 0;
	//iterator of edges
	static int flag = 0;

	for (vector<Edge>::iterator i = edges_data.begin(); i != edges_data.end(); i++)
	{
		//for each edge retain vertices value
		//extract point value from the vertex value
			
		long *v_id = i->getVertices_id();		//get vertex id from edge data 
		
		//cout << fetch_pointFromid(v_id[0]).X << '\t' << fetch_pointFromid(v_id[0]).Y << endl;
		Point a = fetch_pointFromid(v_id[0]);
		//cout << fetch_pointFromid(v_id[1]).X << '\t' << fetch_pointFromid(v_id[1]).Y << endl;
		Point b = fetch_pointFromid(v_id[1]);
		i->setEdge_length(calculate_dist(a, b));	//setting edge length
	
		if (strcmp(i->getEdge_type().c_str(), "LineSegment") == 0)
		{
			perimeter_line += calculate_dist(a, b);
			
			if (length == 0)
			{
				//length = calculate_dist(a, b);
				length = i->getEdge_length();
			}

			else if ((breadth == 0) && (length != i->getEdge_length()))
			{
				breadth = i->getEdge_length();
				//breadth = calculate_dist(a, b);
			}

		}

		else if (strcmp(i->getEdge_type().c_str(), "CircularArc") == 0)
		{
			flag = 1;
			Point c;		//this point is the point from which the circular arc is drawn. Next step is to determine whether it is extrusion or cut
			int cp_data = 0;
			c = fetch_pointFromid(i->getEdge_clockwisefrom_id());

			R = calculate_dist(c, i->getCenter());

			arc_edge_length = calculate_dist(a, b);
			
			//perimeter_arc += PI*R;			//assuming that the arc is a semicircle
			
			perimeter_arc += calculate_angle(a, b, i->getCenter())*R;

			//for calculation of area:
			if (c.X == b.X && c.Y == b.Y)
			{
				cp_data = cross_product(a, c);
				//cout << "cross product data  " << cross_product(a, c) << endl;
			}

			else if (c.X == a.X && c.Y == a.Y)
			{
				cp_data = cross_product(b, c);
				//cout << "cross product data  " << cross_product(b, c) << endl;
			}

			/*If the cross product between vector Clockwise From and the other end of the vertex is negative , it is a cut*/
			/*Else it is an extrusion and the area of stock information would depend on that*/
			
			if (cp_data > 0)
			{
				length_change = R;
			}

			if (cp_data < 0)
			{
				length_change = 0;
			}
		}
	}

	
	if (length_change > 0)
	{
		if(arc_edge_length == breadth)
		{
			length = length + length_change;
		}

		else if (arc_edge_length == length)
		{
			breadth = breadth + length_change;
		}
	}

/*	cout << "Perimeter:" << perimeter_line << endl;
	cout << "Perimeter Arc:" << perimeter_arc << endl;
	cout << "length" << length << endl;
	cout << "breadth" << breadth << endl;
*/
		//if circular arc type then calculate extrude or cut 

	material_cost = (double)((length +  PADDING) * (breadth +  PADDING)) * MATERIAL_COST;

	/*Calculation of perimeter*/

	//add edge to edge to perimeter if line, if arc then add 

	machine_cost = (double) (((perimeter_line)/MAX_CUTTING_SPEED)+((flag * perimeter_arc )/(MAX_CUTTING_SPEED* exp(-1 / R)))) * MACHINE_TIME_COST;


	total_cost = machine_cost + material_cost;
/*
	cout << "machine cost:" << machine_cost << endl;
	cout << "material cost:" << material_cost << endl;
	cout << "extrude arc total cost:" << total_cost << endl;
*/
	return total_cost;
}
/* Cross product function, to be used to determine whether it's an extrusion or cut*/

int cross_product(Point a, Point b)
{
	return int(((a.X*b.Y) - (b.X*a.Y)));
}


/*Following function is witten to fetch Vertex co-ordinate data for corrosponding vertex id*/
/*This function returns Point data*/

Point fetch_pointFromid(long id)
{
	Point x;
	for (vector<Vertex>::iterator j = vertices_data.begin(); j != vertices_data.end(); j++)
	{
		if (j->getVertex_id() == id)
		{
				return j->getVertexpoints();
		}
	}

	//return x;
}
/* Following function calculates Cartesian distance between two input points*/

double calculate_dist(Point x, Point y)
{
	return sqrt((x.X - y.X)*(x.X - y.X) + (x.Y - y.Y)*(x.Y - y.Y));
}

/*
This function calculates the angle between two vectors represented by three points
for points a,b,c  if you want to find angle between vectors ac and bc (angle at c), then calculate angle takes

input as calculate_angle(a,b,c)

*/
double calculate_angle(Point a, Point b, Point c)
{
	double vector1_mag = calculate_dist(a, c);
	double vector2_mag = calculate_dist(b, c);

	Point vector1, vector2;

	vector1.X = a.X - c.X;
	vector1.Y = a.Y - c.Y;

	vector2.X = b.X - c.X;
	vector2.Y = b.Y - c.Y;

	double theta = acos(((vector1.X * vector2.X) + (vector1.Y*vector2.Y)) / (vector1_mag * vector2_mag));
	return theta;
}
