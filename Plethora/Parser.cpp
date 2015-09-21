/*
* Code for parsing the .json.txt file and storing the information in classes
* It reads the file line by line and then stores the information in memory 
* profile given in Profile.h

* Uses get() and set() functions to store data in vector for each edge and vector 
*/


#include"Parser.h"
#include"main.h"
#include"Profile.h"
#include<vector>


using namespace std;

/*following are the vectors where data will be stored. They are extern vectors*/

std::vector<Edge> edges_data;
std::vector<Vertex> vertices_data;

/*Temporary objects to store in the vector*/
Edge temp_data;
Vertex temp_vert;

/*
This function takes the input file given at main and reads it line by line
for each line the program will saperate and store data in it's respective data structure
*/
int parsefile(char* filename)
{
	std::ifstream inputfile;

	inputfile.open(filename);

	if (inputfile.fail())
	{
		std::cout << "Error in opening the file";
	}

	else
	{

		while (!inputfile.eof())
		{
			char line[50];
			char *token[MAX_TOKENS_PER_LINE] = {}, *first_element = {};


			inputfile.getline(line, 50, '\n');

			first_element = strtok(line, " :\"{}[],");

			/*starting here checking for whether the next set of information if for edges or vertices*/

			if (first_element != NULL)
			{

				if (std::strcmp(first_element, "Edges") == 0)
				{
					int brace_count = 0;								//add 1 for opening brace and subtract 1 for closing
					int n = 0;
					
					token[0] = strtok(0, " :\",");				// to encounter the first brace after the edges

					if (std::strcmp(token[0], "{") == 0)
						brace_count++;
					else if (std::strcmp(token[0], "}") == 0)
						brace_count--;
						
			/*For subsequent edges, keeping brace count for identifying hierarchy*/					
	
					while (brace_count > 0)
					{
						n = 0;

						inputfile.getline(line, 50, '\n');
						
						token[0] = strtok(line, " :\"[],");

						if (std::strcmp(token[0], "{") == 0)
						{
							brace_count++;
							inputfile.getline(line, 50, '\n');
							token[0] = strtok(line, " :\"[],");
						}
						
						else if (std::strcmp(token[0], "}") == 0)
						{
							brace_count--;

							//cout << "edge:" << brace_count << endl;
							edges_data.push_back(temp_data);

							inputfile.getline(line, 50, '\n');
							token[0] = strtok(line, " :\"[],");
						}
							

						//cout << token[n] << '\t';
						if (brace_count == 1)
						{
							//std::cout << "storing edge id here:"<<token[0]<<endl;	//store edge id
							
							temp_data.setEdge_id(atol(token[0]));		//storing edge id 
							
							while (token[n])
							{
								//std::cout << brace_count << '\t' << token[n] << '\t';

								if (std::strcmp(token[n], "{") == 0)
									brace_count++;

								else if (std::strcmp(token[n], "}") == 0)
									brace_count--;

								n++;
								token[n] = strtok(0, " :\"[],");	//subsequent tokens of that line

							}

						}

						
						if (brace_count == 2)
						{
							if (strcmp(token[0], "Type") == 0)
							{
								//std::cout << "store type" << token[0] << endl;
								
								token[1] = strtok(0, " :\"[],");	//subsequent tokens
								
								temp_data.setEdge_type(token[1]);	//storing edge 
								
							}

							else if (strcmp(token[0], "Vertices") == 0)
							{
								//std::cout << "store vertex information:" << token[0] << endl;	//storing vertex information : vertices id
								long v_id[2];
								
								inputfile.getline(line, 50, '\n');
								v_id[0] = atol(strtok(line, " :\"[],"));		//id1
								//std::cout << v_id[0] << '\t';
								
								inputfile.getline(line, 50, '\n');
								v_id[1] = atol(strtok(line, " :\"[],"));			//id2
								//std::cout << v_id[1] << '\t';


								inputfile.getline(line, 50, '\n');		//takes the last bracket
								
								
								
								temp_data.setVertices_id(v_id);
							}

							else if (strcmp(token[0], "Center") == 0)
							{
								char *v1 = {}, *v2 = {};
								Point temp_point;

								//std::cout << "store Center information:" << token[0];
								inputfile.getline(line, 50, '\n');
								token[1] = strtok(line, " :\"[],");
								temp_point.X = stod(strtok(0, " :\"[],"));
								//std::cout << token[1]<<'\t'<<temp_point.X<<endl;

								inputfile.getline(line, 50, '\n');
								token[2] = strtok(line, " :\"[],");
								temp_point.Y = stod(strtok(0, " :\"[],"));
								//std::cout << token[2]<<'\t'<<temp_point.Y<<endl;

								inputfile.getline(line, 50, '\n');		//takes the last bracket

								temp_data.setCenter(temp_point);
								temp_point;
							}

							else if (strcmp(token[0], "ClockwiseFrom") == 0)
							{
								//std::cout << "store clockwise information:" << token[0];

								while (token[n])
								{
									//std::cout << token[n] << '\t';
									n++;
									token[n] = strtok(0, " :\"[],");	//subsequent tokens
								}
								temp_data.setEdge_clockwisefrom_id(atol(token[1]));

							}
						}
						
					//std::cout << "here"<<endl;
					
						//edges_data.push_back(temp_data);
								

					}
					
				}

				/*Following snippet for storing information in Vertex class*/

				else if (std::strcmp(first_element, "Vertices") == 0)
				{
					int brace_count = 0;								//add 1 for opening brace and subtract 1 for closing
					int n = 0;

					token[0] = strtok(0, " :\"[],");				// to encounter the first brace after the edges

					if (std::strcmp(token[0], "{") == 0)
						brace_count++;
					
					else if (std::strcmp(token[0], "}") == 0)
						brace_count--;


					while (brace_count > 0)
					{
						n = 0;
						if (brace_count == 1)
						{
							inputfile.getline(line, 50, '\n');		//takes edge id
							token[0] = strtok(line, " :\"[],");
							
							if (std::strcmp(token[0], "}") == 0)
								brace_count--;
							
							else
							{
								//std::cout << "vertex id stored here:" << token[0] << endl;
								temp_vert.setVertex_id(atol(token[0]));			//save vertex id

								while (token[n])
								{

									token[n] = strtok(0, " :\"[],");
									if (std::strcmp(token[n], "{") == 0)
										brace_count++;

									else if (std::strcmp(token[n], "}") == 0)
										brace_count--;
									n++;
								}
							}
						}

						if (brace_count == 2)
						{
							char *x = {}, *y = {};
							Point P;
							inputfile.getline(line, 50, '\n');		//takes position
							token[0] = strtok(line, " :\"[],{}");
							//std::cout << "Position stored here:" << token[0]<<'\t';

							inputfile.getline(line, 50, '\n');		//takes X
							token[0] = strtok(line, " :\"[],{}");
							x = strtok(0, " :\"[],{}");
							P.X = std::stod(x);
							//std::cout << "x co-ordinate:" << token[0]<<'\t'<<x;

							inputfile.getline(line, 50, '\n');		//takes Y
							token[0] = strtok(line, " :\"[],{}");
							y = strtok(0, " :\"[],{}");
							P.Y = stod(y);
							//std::cout << "y co-ordinate:" << token[0]<<'\t'<<y<<endl;
																					
							inputfile.getline(line, 50, '\n');		//for final brace

							temp_vert.setVertexpoints(P);

						}

						
						
						inputfile.getline(line, 50, '\n');

						token[0] = strtok(line, " :\"[],");

						
						if (std::strcmp(token[0], "{") == 0)
							brace_count++;
						

						else if (std::strcmp(token[0], "}") == 0)
						{
							brace_count--;
							
							if (brace_count>= 1)
								vertices_data.push_back(temp_vert);
								
							//cout << "vertex:" << brace_count<<endl;
							
							
						}
						//std::cout << endl;

						
					}
					
				}

			}
		}
	}
	return 0;
}


