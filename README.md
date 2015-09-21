# Plethora-Technical-Exercise
This program calculates the quote for part to be made in 2-axis Laser Cutting Machine. 
The program takes 2D extrusion information in the from .json.txt file format and gives the output which is final quotation.
The software is written in C++.
This program folder contains main.cpp, main.h, Profile.cpp, Profile.h, Parser.cpp, Parser.h
To feed input to the code, modify line 21 of main.cpp and input your file, in the line parsefile("yourfilename").
The function parsefile(), is written in Parser.cpp. It reads line by line the json file and stores the data for Edge and Vertex information
The Profile .h and Profile.cpp files have memory profile in which the information is stored is a Vector of class Edges and class Vertices.

Class Edge has following attributes :
  1. Edge id
	2. Edge type
	3. Vertices id : array of two ids
	4. Center : stores center for circular arc data
  5. Edge length : to be calculated later, when estimating cost. 
Class Vertex has following attributes 
  1. Vertex id
	2. Point

Main.cpp has function compute_finalcost(), which Computes the quotation , based on Machine cost and Material cost. 
Material cost is proportional to area of stock and Machine cost to the time spent on the machine. 
