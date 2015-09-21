/*
This file contains software for parsing the data, from json file
*/


#ifndef PARSER_H
#define PARSER_H
#include "main.h"
#include"Profile.h"

int parsefile(char* filename);

/*Marking delimator for saperating tokens in json file*/

#define OPEN_BRACES	'{'
#define CLOSE_BRACES '}'
#define DELIM	" "
#define COLON	':'
#define OPEN_SQ_BRACES	'['
#define CLOSE_SQ_BRACES	']'
#define MAX_TOKENS_PER_LINE	3


#endif