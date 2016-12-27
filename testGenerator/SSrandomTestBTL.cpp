//	SSrandomTestBTL
//	SSrandomTestBTL.cpp
//Trevor Brooks
//Using C++ Std Version 3.0
//Edited and compiled in VS 2015

//-------------
// C++ includes
//-------------

#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

//-----------------
// Global constants
//-----------------
const int NMBR_TESTS = 9; // How many test files to generate.
const int MAX_CASES = 9; //How many cases in each file (max).
const int MAX_TOWNS = 35; //How many towns (max).
const std::string PROJECT_CODE = "ssBTL0"; //We use this to label the files.
const std::string input = "in.txt"; //Labels that generated file should be input.

/** ******************************************************
DESCRIPTION - main
This function generates nine files for inputing into a service station program.
The output created for each file should be a valid test.

COMPILE INSTRUCTIONS
To compile and run on Katie:
g++ -std=c++11 -c -fprofile-arcs -ftest-coverage SSrandomTestBTL.cpp
#g++ -o SSrandomTestBTL SSrandomTestBTL.o
./SSrandomTestBTL

REQUIREMENTS
R01	SSrandomTestBTL is coded in C++.
R02	The source file will be in compliance with the MTM C++ Source File standard 3.0.
R03	The application will be launched from an executable file.
R04 A series of nine output files will be created.
R05 The file names will be in form of ssXXin.txt where XX is the two digit representation
	of the test case number.
R06	Each file will have between 1 and 9 cases.
R07 Each case will have between 3 and 35 towns inclusive.
R08	Each case will have between 0 and 99 pairs of towns connected.
R09	The first line of each case will be the number of towns, a space, and then the number of pairs.
R10	The following nmbrPair lines be a line of two integers between 1 and nmbrTowns. 
	There will be a number of lines matching the previous number of pairs. 
R11	After all cases the final line will be "0 0" without quotes.


DESIGN
Significant Data Items/Structures
--------------------------------------------
SS is used as a shorthand for ServiceStation

int NMBR_TESTS = 9; // How many test files to generate.
int MAX_CASES = 9; //How many cases in each file (max).
int MAX_TOWNS = 35; //How many towns (max).
std::string PROJECT_CODE = "ss0"; //We use this to label the files.
std::string input = "in.txt"; //Labels that generated file should be input.
int nmbrTowns, nmbrPairs, nmbrCases, townA, townB;

Solution Analysis
-----------------------
Using the random function and the modulus function we can create random data in the correct range for each file.


Algorithm
-------------
A00 Define:
int NMBR_TESTS = 9; // How many test files to generate.
int MAX_CASES = 9; //How many cases in each file (max).
int MAX_TOWNS = 35; //How many towns (max).
std::string PROJECT_CODE = "ss0"; //We use this to label the files.
std::string input = "in.txt"; //Labels that generated file should be input.
int nmbrTowns, nmbrPairs, nmbrCases, townA, townB;

A01	for (testNum iterates from 1 to NMBR_TESTS) {
A02		Set nmbrCases to a random integer between 1 and MAX_CASES; 
A03		Construct a file output;
A04		for (caseNum iterates from 0 to nmbrCases) {
A05			Set nmbrTowns to a random integer between 3 and MAX_TOWNS;
A06			Set nmbrPairs to a random integer between 0 and 99;
A07			Display nmbrTowns nmbrPairs with a new line;
A08			for (pairNum iterates from 0 to nmbrPairs) {
A09				Set townA to a random integer between 1 and nmbrTowns;
A10				Set townB to a random integer between 1 and nmbrTowns;
A11				Display townA townB with a new line; 
			}//for
		}//for
A12		Display "0 0" with a new line; 
	}//for
A13	return; 


ALGORITHM CORRECTNESS ARGUMENT
CR04	For each of the nine loops of A01, A03 creates an output file.
CR05	A03 opens a file with the correct name.
CR06	A02 sets the number of cases for the file. A04 loops to create each case.
CR07	A05 creates the correct range for nmbrTowns.
CR08	A06 creates the correct range for nmbrPairs
CR09	A07 states that the number of towns and number of pairs should be output.
CR10	A08 through A11 creates each pair and outputs it.
CR11	A12 creates the end file signal.

CODE CORRECTNESS ARGUMENT
Code Correctness Argument for function main:
CA01	The loop iterates over the correct values.
CA02	nmbrCases is set by a random function.
CA03	The file output is created an initialized.
CA04	The loop iterates over the correct values.
CA05	nmbrTowns is set by a random function.
CA06	nmbrPairs is set by a random function.
CA07	The values nmbrTowns and nmbrPairs values are output.
CA08	The loop iterates over the correct values.
CA09	townA is set by a random function.
CA10	townB is set by a random function.
CA11	The pair is output.
CA12	The "0 0" end of file signal is output to the file.
CA13	The program ends with a return.

*********************************************************/

int main(int argc, const char * argv[]) {
	/*A00 Define*/
	int nmbrTowns, nmbrPairs, nmbrCases, townA, townB;
	srand(time(NULL));
	for (int testNum = 1; testNum <= NMBR_TESTS; testNum++) { /*L01*/
		nmbrCases = (int)(rand() % MAX_CASES + 1); /*L02*/
		//Create output stream.
		std::ofstream output; /*L03*/
		//Open the output file. Removes old content from file listed.
		output.open(PROJECT_CODE + std::to_string(testNum) + input, std::ios::trunc);
		for (int caseNum = 0; caseNum < nmbrCases; caseNum++) { /*L04*/

			nmbrTowns = (int)(rand() % (MAX_TOWNS - 3) + 3);/*L05*/
			nmbrPairs = (int)(rand() % 100);/*L06*/
			output << nmbrTowns << " " << nmbrPairs << std::endl; /*L07*/
			for (int pairNum = 0; pairNum < nmbrPairs; pairNum++) {/*L08*/
				townA = (int)(rand() % nmbrTowns + 1);/*L09*/
				townB = (int)(rand() % nmbrTowns + 1);/*L10*/
				output << townA << " " << townB << std::endl; /*L11*/
			}//for
		}//for
		output << "0 0" << std::endl; /*L12*/
	}//for
	return 0; /*L13*/
}

