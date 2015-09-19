#include"Parser.h"
#include"main.h"

using namespace std;

enum { Edges , Vertices };

/*
This function takes the input file given and reads it line by line
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
			char *token[MAX_TOKENS_PER_LINE] = {};
			int n = 0;
			
			inputfile.getline(line, 50,'\n');
			
			token[0] = strtok(line, " :\"{}[],");
			
			
			while (token[n])
			{
				cout << token[n] << '\t';
				n++;
				token[n] = strtok(0, " :\"{}[],");	//subsequent tokens
							
					
			}				

			cout << endl;
				
				
			
			
			
			//cout << line<<"\n";
			
			
		}
	}

	return 0;
}


/*
char *rc = "";
std::string sample;

fscanf(inputfile, "%s", rc);
std::cout << rc;

std::cout << sample;

fscanf(inputfile, "%c", &sample);
std::cout << sample;

fscanf(inputfile, "%c", &sample);
std::cout << sample;*/