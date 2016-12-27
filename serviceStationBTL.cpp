//	ServiceStationBTL
//	ServiceStationBTL.cpp
//Trevor Brooks
//Using C++ Std Version 3.0
//Edited and compiled in VS 2015

//-------------
// C++ includes
//-------------

#include <stdlib.h>
#include <iostream>
#include <string>

//-----------------
// Global constants
//-----------------

const int MAX_TOWNS = 35;
const char ssTown = 'S';
const char ssAdjTown = 'A';
const char townInCluster = 'C';
const char notProcessedTown = 'N';
const char empty = 'E';
//Integer MAX_SEARCH allows us to control the depth of recursion.
//The greedy algorithm can handle the problem given that a few key stations
//are in place. This can help us eliminate large numbers of recursions and 
//a large chunk of the solution space. This means that we are not doing a full exhaustive
//search, but we can find the correct algorithm. Three seems to work by allowing enough
//manual searching to find an optimal solution with the greedy algorithm.
const int MAX_SEARCH = 3;

//-----------------
// Type definitions
//-----------------

struct Town {
    int neighbors[MAX_TOWNS + 1];
    int nmbrNeighbors = 0;
    char state = empty;
    int townNum;
};

struct TownCluster {
    int townArray[MAX_TOWNS];
    int nmbrTownsInCluster;
};



//---------------------
// Function prototypes
//---------------------

int recursiveSolver(Town[], TownCluster, int, int, int, int, int);
int greedyAlgorithm(Town[], TownCluster, int, int, int, int);
bool findNeighbor(Town[], int, int);
static TownCluster addLinkedTownsToCluster(Town[], int,TownCluster);

/** ******************************************************
DESCRIPTION - main
Brief description of the program for which this is
the main function.  When there is a spec sheet, this should be an exact copy of the description in the spec sheet.

REQUIREMENTS
Please see serviceStationSMDSv5BTL.docx for an up-to-date set of requirements.

SAMPLE RUN(S)
stdin:
3  2
1  2
2  3
0  0

stdout:
1

DESIGN
Significant Data Items/Structures
--------------------------------------------
SS is used as a shorthand for ServiceStation

int nmbrTowns
int nmbrPairs
int townNum
int[][] townMatrix
TownCluster	//Class to hold townArray as object.
int[]	townArray //used to signify which towns are in the
//cluster. These towns are denoted by a 1 in
//the array
int		nmbrTownsInCluster
townCluster[] clusters //Keep track of all clusters found.
int nmbrClusters
int ssCnt
int MAX_TOWNS = 35
int townA, townB
char[] townList



//Constants to be used for clarity. These give names to placeholder values used in
//townList
char ssTown 			= ‘S’	//Town has service station
char ssAdjTown 		= ‘A’	//Town next to service station
char	townInCluster 		= ‘C’	//Town has been placed in a cluster
char	notProcessedTown 	= ‘N’	//Town is not yet in cluster, but needs one
char	empty			= ‘E’	//Town does not exist. Array could be longer than
//	towns given

Solution Analysis
-----------------------
Each town configuration must be looked at independently. In each town configuration, we want to create groupings of towns that are connected. Each separate group in the town configuration can be solved separately and added up. We use a mixture of recursive backtracking and a greedy algorithm looking for the maximum number of connections that have not been serviced.



Algorithm
-------------
A00 Define:
const int MAX_TOWNS = 35;
const char ssTown = 'S';
const char ssAdjTown = 'A';
const char townInCluster = 'C';
const char notProcessedTown = 'N';
const char empty = 'E';
const int MAX_SEARCH = 3;

Town 
    	int neighbors[MAX_TOWNS + 1];
    	int nmbrNeighbors = 0;
    	char state = empty;
    	int townNum;

TownCluster
    	int townArray[MAX_TOWNS];
    	int nmbrTownsInCluster;
    int nmbrTowns, nmbrPairs, ssCnt, townA;
    int townB, nmbrTownsRemaining, nmbrClusters;
    Town townList[MAX_TOWNS + 1];
    
    String returnString;
    
A01	Read nmbrTowns and nmbrPairs from stdin;
    
A02	While(nmbrTowns is not zero or nmbrPairs is not zero){

A03		Set nmbrTownsRemaining to nmbrTowns;
A04		Set ssCnt to 0;
A05		Set nmbrClusters to 0;
A06		For(townNdx iterates from 0 to MAX_TOWNS){
A07			Set townList[townNdx].townNum to townNdx;
A08			If(townNdx is greater than 0 an townNdx less than or equal to 
   nmbrTowns){
A09				Set townList[townNdx].state to notProcessedTown;
            		}//If
A10            		Else{
A11				Set townList[townNdx].state to empty;
            		}//Else
A12			For(neighborNdx iterates from 0 to townList[townNdx].nmbrNeighbors){
A13				Set townList[townNdx].neighbors[neighborNdx] to 0;
            		}//For
A14			Set townList[townNdx].nmbrNeighbors to 0;
   		}//For
        
A15 		For (pairNdx: iterates from one to nmbrPairs){
A16			Read townA and townB from stdin;
A17			If(townA is not equal to townB and findNeighbor(townA, 
townB) is false){
A18				Set townMatrix[townA][townB] to 1;
A19				Set townMatrix[townB][townA] to 1;
}// If
}// For
        
        		//Set stations on all disconnected towns.
A20		For(townNdx iterates from 1 to nmbrTowns){
A21			If(townList[townNdx].nmbrNeighbors == 0){
A22				Set townList[townNdx].state to ssTown;
A23				Increment ssCnt by one;
A24				Decrement nmbrTownsRemaining by one;
   			}//If
        		}//For
        
A25		Construct clusters[MAX_TOWNS + 1];
        
       		 //Creates clusters
A26		For (townNdx iterates from 1 to nmbrTowns) {
A27			If (townList[townNdx].state == notProcessedTown) {
A28				Construct townCluster;
A29				Set townCluster.nmbrTownsInCluster to 0;
A30				Set townCluster.townArray
   [townCluster.nmbrTownsInCluster] 
                			      to townList[townNdx].townNum;
A31				Set townList[townNdx].state to townInCluster;
A32	      	           	Increment townCluster.nmbrTownsInCluster by one;
                
A33				For (searchNdx iterates from 0 to
        townList[townNdx].nmbrNeighbors) {
A34					If(townList[townList[townNdx]
    	    .neighbors[searchNdx]].state 
                    			    		== notProcessedTown) {

A35		Set townCluster.townArray
   [townCluster.nmbrTownsInCluster] 
                    					       to townList[townList[townNdx].
                    					       neighbors[searchNdx]].townNum;

A36						Set townList[townList[townNdx]
       .neighbors[searchNdx]].
   state to townInCluster;

A37						Increment townCluster.nmbrTownsInCluster 
     by one;
                        
A38						Set townCluster = 
addLinkedTownsToCluster(townList,
						townList[townList[townNdx]
   						.neighbors[searchNdx]].townNum,
                        	 				townCluster);
                    					}//If
                				}//For
                
A39					For(townNdx iterates from 0 to 
townCluster.nmbrTownsInCluster){
A40						Set townList[townCluster
   .townArray[townNdx]]
.state to townInCluster;
                				}//For
                
A41					Set clusters[nmbrClusters] to townCluster;
A42					Set nmbrClusters by one;

   				}//If
   			}//For

A43			For(clusterNdx iterates from 0 to nmbrClusters){
A44		Set threshold to greedyAlgorithm(townList,
clusters[clusterNdx], nmbrTowns, 0, 
clusters[clusterNdx].nmbrTownsInCluster,
            	  	      		clusters[clusterNdx].nmbrTownsInCluster);
A45				Increment ssCnt by recursiveSolver(townList, 
clusters[clusterNdx], nmbrTowns, 0,
 					clusters[clusterNdx].nmbrTownsInCluster,
            	  			threshold, 0);
        			}//For
          
A46			Display ssCnt;
A47			Read nmbrTowns and nmbrPairs from stdin

}//While nmbrTowns is not zero
	
A48	Return;

int recursiveSolver(Town townList[], TownCluster cluster, int nmbrTowns,
int ssCnt, int nmbrTownsRemaining, int threshold, int lowestTown){
A49	If(nmbrTownsRemaining is equal to 0 or ssCnt is equal to threshold){
A50		If(ssCnt is less than threshold){
A51			return ssCnt;
        		}//If
A52		Else{
A53			return threshold;
        		}//Else
    	}//If
A54	Else If(ssCnt is greater than threshold or threshold is equal to 1){
A55		return threshold;
    	}//Else If
A56	Else{

A57		Set tempCnt to ssCnt;
A58		For(townIdx iterates from lowestTown to cluster.nmbrTownsInCluster){
A59			Set tempCnt to ssCnt;
A60			Set tempRemaining to nmbrTownsRemaining;
A61			If(townList[cluster.townArray[townIdx]].state != ssTown){
A62				Increment tempCnt by one;
A63				Construct tempTowns[MAX_TOWNS + 1];
A64				For(copyNdx iterates from 0 to nmbrTowns){
A65					Set tempTowns[copyNdx] to townList[copyNdx];
                			}//For
                
A66				For (checkNdx iterates from 0 to 
tempTowns[cluster.townArray[townIdx]]
.nmbrNeighbors) { 
A67					Set townChk to 
tempTowns[cluster.townArray[townIdx]];
A68					If (tempTowns[townChk.neighbors[checkNdx]].state 
                    					Is equal to townInCluster) {
A69						Decrement tempRemaining by one; 
A70						Set 
tempTowns[townChk.neighbors[checkNdx]].state to ssAdjTown; 
                    				}//If
                			}//For each town directly connected to townNum
                
A71				If (tempTowns[cluster.townArray[townIdx]].state 
is not equal to  ssAdjTown) {
A72					Decrement tempRemaining by one; 
               			 }//If
A73				Set tempTowns[cluster.townArray[townIdx]].state to 
ssTown;           
A74				Set tempCnt to greedyAlgorithm(tempTowns, cluster, 
nmbrTowns, tempCnt, tempRemaining, threshold);
A75				If(tempCnt is less than threshold){
A76					Set threshold to tempCnt;
                			}//If
A77				If(lowestTown is less than MAX_SEARCH){
A78					Set tempCnt to recursiveSolver(tempTowns, 
cluster, nmbrTowns, ssCnt+1, tempRemaining, 
threshold, townIdx +1);
A79					If(tempCnt is less than threshold){
A80						Set threshold to tempCnt;
                    				}//If
                			}//If   
            		}//If
        		}//For
    	}//Else
A81	return threshold;
}//recursiveSolver

int greedyAlgorithm(Town townList[], TownCluster cluster, int nmbrTowns,
	int ssCnt, int nmbrTownsRemaining, int threshold){
    
A82	If(nmbrTownsRemaining is equal to 0 or ssCnt is equal to threshold){
A83		return ssCnt;
    	}//If
A84	Else{
A85		Set maxConnections, townNum, and maxDeadEnds to 0;
        
A86		Construct tempTowns[MAX_TOWNS + 1];
A87		For(icopyNdx iterates from  0 to nmbrTowns){
A88			tempTowns[copyNdx] = townList[copyNdx];
        		}//For
        
A89		For (townNdx iterates from 0 to cluster.nmbrTownsInCluster) {
A90			Set connectionNmbr, nmbrDeadEnds to 0;
A91			If (tempTowns[cluster.townArray[townNdx]].state is not equal to 
    ssTown) {
A92				Set townChk to tempTowns[cluster.townArray[townNdx]];
A93				For (connNdx iterates from 0 to townChk.nmbrNeighbors){
A94					If (tempTowns[townChk.neighbors[connNdx]].state 
                    					is equal to townInCluster) {
A95						Increment connectionNmbr by 1;
A96						Set isDeadEnd = true;
A97						For(deadCheckNdx iterates from 0 to 
tempTowns[townChk.neighbors[connNdx]]
.nmbrNeighbors){
A98							If(tempTowns[townChk.neighbors
   [connNdx]].townNum is not equal to 
   townChk.townNum){
A99								Set isDeadEnd to false;
A100								break;
                            					}//If
                        				}//For
A101						If(isDeadEnd is true){
A102							Increment nmbrDeadEnds by one;
A103							Increment connectionNmbr by one;
                        				}//If
A104					}//If
A105				}//For
                
A106				If (townChk.state is not equal to ssAdjTown) {
A107					Increment connectionNmbr by one;
   				}//If
A108				If (connectionNmbr is greater than maxConnections 
or (townNum is equal to 0 && townChk.state  is not equal to  ssAdjTown) or (connectionNmbr is equal to maxConnections 
                			and (townChk.state  is equal to ssAdjTown 
                			or nmbrDeadEnds is greater than maxDeadEnds))) {

A109					Set townNum to cluster.townArray[townNdx];
A110					Set maxConnections to connectionNmbr;
A111					Set maxDeadEnds to nmbrDeadEnds;
}//If
}//If
}//For
A112		For (checkNdx iterates from 0 to tempTowns[townNum].nmbrNeighbors;
        	 		) {
A113			If (tempTowns[tempTowns[townNum].neighbors[checkNdx]].state
                			 is equal to townInCluster) {
A114				Decrement nmbrTownsRemaining by one;
A115				Set tempTowns[tempTowns[townNum].neighbors[checkNdx]]
.state to ssAdjTown;
                		}//If
        		}//For each town directly connected to townNum
        
A116		If (tempTowns[townNum].state is not equal ssAdjTown) {
A117			Decrement nmbrTownsRemaining by one;
        		}//If
A118		Increment ssCnt by one;
A119		Set tempTowns[townNum].state to ssTown;
A120		return greedyAlgorithm(tempTowns, cluster, nmbrTowns,
         				ssCnt, nmbrTownsRemaining, threshold);
    	}//Else    
}

bool findNeighbor(Town townList[], int townA, int townB) {
	bool found = false;
A121	For (neighborNum iterates from 0 to townList[townA].nmbrNeighbors) {
A122		If (townList[townA].neighbors[neighborNum] is equal to townB) {
A123			Set found to true;
A124			break;
		}//If
	}//For

A125	return found;
}

static TownCluster addLinkedTownsToCluster(Town townList[],
						 int townNdx, TownCluster cluster) {

A126	For (linkNdx iterates from 0 to townList[townNdx].nmbrNeighbors) {
A127		If (townList[townList[townNdx].neighbors[linkNdx]].state 
        		    is equal to notProcessedTown) {
A128			Set cluster.townArray[cluster.nmbrTownsInCluster] 
        				to townList[townList[townNdx]
.neighbors[linkNdx]].townNum;
A129			Set townList[townList[townNdx].neighbors[linkNdx]].state to 
townInCluster;
A130			Increment cluster.nmbrTownsInCluster by one;
A131			Set cluster to addLinkedTownsToCluster(townList,
A132			townList[townList[townNdx].neighbors[linkNdx]].townNum, cluster);
        		}//If
    	}//For
A133	return cluster;
}//addLinkedTownsToCluster

//end ServiceStationv2BTL



INPUT SPACE PARTITIONS
1.	One set of town combinations is in the input
1.1.	nmbrTowns is 3
1.1.1.	nmbrPairs is 0
1.1.2.	nmbrPairs is 1
1.1.3.	nmbrPairs is greater than 1
1.2.	nmbrTowns is greater than 3 but less than 35
1.2.1.	nmbrPairs is 0
1.2.2.	nmbrPairs is 1
1.2.3.	nmbrPairs is greater than 1
1.3.	nmbrTowns is 35
1.3.1.	nmbrPairs is 0
1.3.2.	nmbrPairs is 1
1.3.3.	nmbrPairs is greater than 1
2.	Two sets of town combinations are in the input
Several pairs of town combinations that are variations on (1)
3.	More than two town combinations but no more than 10 combinations exist in the input
Several sets of town combinations that are variations on (1)


TEST CASES
Please see serviceStationSMDSv5BTL.docx for a grid view of the test cases.
Program can be tested against these test cases by running serviceStationBTLtestRun.sh


ALGORITHM CORRECTNESS ARGUMENT
CR01	This does not apply to algorithm correctness.
CR02	This does not apply to algorithm correctness.
CR03	This does not apply to algorithm correctness.
CR04	This does not apply to algorithm correctness.
CR05	nmbrTowns and nmbrPairs read in on A01 and checked on A02
CR06	 Read in by A15
CR07	 By reading each number separately into townA and townB we use the space
seperator
CR08	 A02 stops at a line of “0 0” (without quotes)
CR09	 townMatrix defined at A00 can hold up to 35 towns
CR10	 A17 tries to match values read in for each town into the town matrix
CR11	 A48 writes the output value.


CODE CORRECTNESS ARGUMENT
Code Correctness Argument for function main:
CA01	Reads in both the nmbrTowns and nmbrPairs from input.
CA02	Ensures that nmbrTowns and nmbrPairs 
		are not both 0 which is end of input.
CA03	Sets a tracking variable to nmbrTowns.
CA04	Sets ssCnt to 0.
CA05	Sets nmbrClusters to 0.
CA06	Variable townNdx does iterate from zero to MAX_TOWNS.
CA07	The townNum of the town with index townNdx is set to the townNdx.
CA08	Checks that townNdx is between 1 and nmbrTowns inclusively.
CA09	The state of the town with index townNdx is set to notProcessedTown.
CA10	Else catches all towns that do not fit criteria of CA08.
CA11	State of towns that fall into CA10 are set to empty.
CA12	neighborNdx does iterate from 0 to the number of neighbors that town has.
CA13	Each neighbor entry for the town is set to 0.
CA14	The nmbrNeighbors attribute of the town is set to 0.
CA15	pairNdx iterates from one to nmbrPairs
CA16	The pair of towns is read in from stdin
		and set into variables townA and townB
CA17	townA is found to be not equal to townB 
		(self-loop) and the towns are not already 
		neighbors. (see	CA121 through CA125).
CA18	This adds townB as a neighbor of townA.
CA19	The nmbrNeighbors attribute of townA is incremented by one.
CA20	townA is added as a neighbor of townB.
CA21	the nmbrNeighbors attribute of townB is incremented by one.
CA22	townNdx iterates from 1 to nmbrTowns in a for loop.
CA23	the nmbrNeighbors attribute of town with 
		index townNdx is checked to see if it is 0.
CA24	The town with index townNdx has its state set to ssTown.
CA25	ssCnt is incremented by one.
CA26	nmbrTownsRemaining is decremented by one.
CA27	The array clusters of type TownCluster is created with size MAX_TOWNS+1.
CA28	townNdx iterates from 1 to nmbrTowns.
CA29	Town with index townNdx is checked to have a state of notProcessedTown.
CA30	New variable townCluster is created with type TownCluster.
CA31	The attribute nmbrTownsInCluster of townCluster is set to 0.
CA32	The first town of townCluster is set to be the town with townNdx.
CA33	The town with index townNdx has its state set to townInCluster.
CA34	the nmbrTownsInCluster attribute is incremented.
CA35	searchNdx iterates from 0 to nmbrNeighbors.
CA36	The state of the town that matches 
		townList[townList[townNdx].neighbors[searchNdx]] is checked
		to have the state notProcessedTown.
CA37	The town we are currently looking at is added to the cluster.
CA38	The town we are currently looking at has its state 
		updated to be townInCluster.
CA39	The nmbrTownsInCluster attribute is incremented by one.
CA40	The town cluster uses the addLinkedTownsToCluster
		to find more towns that are linked
recursively. (See CA126 – CA133 for proof of the cluster creation)
CA41	townNdx iterates from 0 to nmbrTownsInCluster .
CA42	Each town in the cluster is set to be townInCluster for
		the corresponding iterations.
CA43	The townCluster is added to the array clusters.
CA44	nmbrClusters is incremented by one.
CA45	clusterNdx iterates from 0 to nmbrClusters.
CA46	The value of threshold is set to be the returned value of 
		the greedyAlgorithm call. (CA84-CA120)
CA47	The value of ssCnt is incremented by the returned value of 
		the recursiveSolver call. (CA51-CA83)
CA48	The value of ssCnt is displayed by adding it to a string and
		then displaying all values required for the problem.
CA49	New values for nmbrTowns and nmbrPairs are read in from stdin.
CA50	The value 0 is returned as the function exits.

Code Correctness Argument for function recursiveSolver:
CA51	Statement checks that nmbrTownsRemaining is 0 
		or that ssCnt is equal to the threshold.
CA52	Statement checks that ssCnt is less than the threshold.
CA53	ssCnt is returned.
CA54	The else catches all conditions outsid of CA52.
CA55	The value threshold is returned.
CA56	Statement checks if ssCnt is greater than threshold or if 
		threshold is equal to 1.
CA57	threshold is returned.
CA58	Values outside of CA51 and CA 56 are caught.
CA59	tempCnt is set to the value of ssCnt.
CA60	townIdx iterates from lowestTown to the nmbrTownsInCluster
CA61	tempCnt is reset back to ssCnt.
CA62	tempRemaining  is set to nmbrTownsRemaining.
CA63	Statement checks if town with index townIdx in the cluster 
		does not already have a service station.
CA64	Increment the tempCnt value by one.
CA65	New array is constructed (creating the new array allows us to 
		not mess with valid data as we test.)
CA66	copyNdx iterates from 0 to nmbrTowns.
CA67	Town with index copyNdx is copied to the temporary array.
CA68	checkNdx iterates from 0 to the number of neighbors the town has.
CA69	townChk shorthand variable is set to the town we are looking at.
CA70	Check if the neighbor of our current town has not been serviced yet.
CA71	Decrements tempRemaining by one.
CA72	The town’s state is set to be ssAdjTown.
CA73	Check if the town we have placed a service station at already 
		had been adjacent.
CA74	If it has not then decrement tempRemaining by one.
CA75	Current town has state set to ssTown.
CA76	tempCnt has value set to the return value of greedyAlgorithm 
		(CA84-CA120).
CA77	Checks if the tempCnt value is less than the current threshold.
CA78	The threshold is set to the value of tempCnt.
CA79	Check if lowestTown is less than MAX_SEARCH.
CA80	tempCnt is set to the return value of recursiveSolver.
CA81	Check if the new value of tempCnt is less than the current threshold.
CA82	Set the threshold to be tempCnt.
CA83	Returns the value we found as a threshold.

Code Correctness Argument for function greedyAlgorithm:
CA84	Checks if nmbrTownsRemaining is equal to 0 or if ssCnt is equal 
		to threshold.
CA85	Returns ssCnt.
CA86	If CA84 was not correct continue with next branch.
CA87	Sets value of maxConnections, townNum, and maxDeadEnds to 0.
CA88	Creates new array tempTowns.
CA89	copyNdx iterates from 0 to nmbrTowns.
CA90	Value of town with index copyNdx is copied to the temporary array.
CA91	copyNdx iterates from 0 to nmbrTownsInCluster for current cluster.
CA92	connectionNmbr and nmbrDeadEnds are both set to 0.
CA93	Check if the state is not already set to be ssTown.
CA94	Creates variable with name townChk to hold a town.
CA95	connNdx iterates from 0 to townChk.nmbrNeighbors.
CA96	Checks if the current neighbor being considered has not been serviced.
CA97	Increment connectionNmbr by 1.
CA98	Sets isDeadEnd to true.
CA99	deadCheckNdx iterates from 0 the number of neighbors the current 
		neighbor has.
CA100	Check if the neighbor listed is the same as townChk.
CA101	Set the value of isDeadEnd to false.
CA102	Breaks the loop.
CA103	Check that isDeadEnd is true.
CA104	nmbrDeadEnds is incremented by one.
CA105	connectionNmbr is incremented by one.
CA106	Check if the town set to townChk has state ssAdjTwon
CA107	connectionNmbr is incremented by one.
CA108	Checks if the town being considered is a better candidate for the 
		greedy algorithm.
CA109	Sets townNum to the current town being considered.
CA110	maxConnections is set to be connnectionNmbr.
CA111	maxDeadEnds is set to be nmbrDeadEnds.
CA112	checkNdx iterates from 0 to the number of neighbors the town has.
CA113	Check if town considered by checkNdx has not been serviced.
CA114	nmbrTownsRemaining is decremented by one.
CA115	State of neighbor is set to be ssAdjTown.
CA116	Check if the state is not already set to be ssAdjTown.
CA117	nmbrTownsRemaining is decremented by one.
CA118	ssCnt is incremented by one.
CA119	State of current town is updated to be ssTown.
CA120	Recursive call to greedyAlgorithm is returned.

Code Correctness Argument for function findNeighbor:
CA121	neighborNum is iterated from 0 to the nmbrNeighbors for townA.
CA122	Check if the neighbor with index neighborNum is equal to townB.
CA123	found is set to true.
CA124	The loop is broken.
CA125	The value of found is returned.

Code Correctness Argument for function addLinkedTownsInCluster:
CA126	linkNdx is iterated from 0 to nmbrNeighbors for town with index townNdx.
CA127	Check if the current neighbor has a state of notProcessedTown.
CA128	Adds the town to the cluster.
CA129	Sets the state of the town to townInCluster.
CA130	nmbrTownsInCluster is incremented by one.
CA131	Recursively calls addLinkedTownsInCluster to add more towns connected 
		to elements of the cluster.
CA132	The updated cluster is returned.



CALLING TREE/CALLS
recursiveSolver
greedyAlgorithm
findNeighbor
addLinkedTownsToCluster

*********************************************************/

int main()
{
    /*L00  Define : */
    int nmbrTowns, nmbrPairs, ssCnt, townA;
    int townB, nmbrTownsRemaining, nmbrClusters;
    Town townList[MAX_TOWNS + 1];
    
    std::string returnString = "";
    
    //Read in first case info
    std::cin >> nmbrTowns; /*L01*/
    std::cin >> nmbrPairs;
    
	//Iterate through all cases in input
    while (nmbrTowns != 0 || nmbrPairs != 0) {/*L02*/
		//Reset variables
        nmbrTownsRemaining = nmbrTowns;/*L03*/
        ssCnt = 0;/*L04*/
        nmbrClusters = 0; /*L05*/
		//Reset town info
        for(int townNdx = 0; townNdx <= MAX_TOWNS; townNdx++){ /*L06*/
            townList[townNdx].townNum = townNdx; /*L07*/
            if(townNdx > 0 && townNdx <= nmbrTowns){ /*L08*/
                townList[townNdx].state = notProcessedTown; /*L09*/
            }//if
            else{ /*L10*/
                townList[townNdx].state = empty; /*L11*/
            }//else
            for(int neighborNdx = 0;
            	neighborNdx < townList[townNdx].nmbrNeighbors; neighborNdx++){ 
				/*L12*/
                townList[townNdx].neighbors[neighborNdx] = 0; /*L13*/
            }//for
            townList[townNdx].nmbrNeighbors = 0; /*L14*/
        }//for
        
		//Read in town connections.
        for (int pairNdx = 1; pairNdx <= nmbrPairs; pairNdx++) { /*L15*/
            std::cin >> townA; /*L16*/
            std::cin >> townB;
            if(townA != townB && !findNeighbor(townList, townA, townB)){ /*L17*/
                townList[townA].neighbors[townList[townA].nmbrNeighbors] 
                	= townB; /*L18*/
                townList[townA].nmbrNeighbors++; /*L19*/
                townList[townB].neighbors[townList[townB].nmbrNeighbors] 
                	= townA; /*L20*/
                townList[townB].nmbrNeighbors++; /*L21*/
            }//if
            
        }// for
        
        //Set stations on all disconnected towns.
        for(int townNdx = 1; townNdx <= nmbrTowns; townNdx++){ /*L22*/
            if(townList[townNdx].nmbrNeighbors == 0){ /*L23*/
                townList[townNdx].state = ssTown; /*L24*/
                ssCnt++; /*L25*/
                nmbrTownsRemaining--; /*L26*/
            }//if
        }//for
        
        TownCluster clusters[MAX_TOWNS + 1]; /*L27*/
        
        //Creates clusters
        for (int townNdx = 1; townNdx <= nmbrTowns; townNdx++) { /*L28*/
            if (townList[townNdx].state == notProcessedTown) { /*L29*/
                TownCluster townCluster; /*L30*/
                townCluster.nmbrTownsInCluster = 0; /*L31*/
                townCluster.townArray[townCluster.nmbrTownsInCluster] 
                	= townList[townNdx].townNum; /*L32*/
                townList[townNdx].state = townInCluster; /*L33*/
                townCluster.nmbrTownsInCluster++; /*L34*/
                
				for (int searchNdx = 0; 
					searchNdx < townList[townNdx].nmbrNeighbors; searchNdx++) { 
					/*L35*/
                    if (townList[townList[townNdx].neighbors[searchNdx]].state 
                    	== notProcessedTown) { /*L36*/

                        townCluster.townArray[townCluster.nmbrTownsInCluster] 
                    		= townList[townList[townNdx].
                    			neighbors[searchNdx]].townNum; /*L37*/

                        townList[townList[townNdx].neighbors[searchNdx]].state 
                        	= townInCluster; /*L38*/

                        townCluster.nmbrTownsInCluster++; /*L39*/
                        
                        townCluster = addLinkedTownsToCluster(townList,
                        	 townList[townList[townNdx]
                        	 	.neighbors[searchNdx]].townNum,
                        	 	townCluster); /*L40*/
                    }//if
                }//for
                
                for(int townNdx = 0; townNdx < townCluster.nmbrTownsInCluster;
                	 townNdx++){ /*L41*/
                    townList[townCluster.townArray[townNdx]].state 
                		= townInCluster; /*L42*/
                }//for
                
                clusters[nmbrClusters] = townCluster; /*L43*/
                nmbrClusters += 1; /*L44*/

            }//if
        }//for
        for(int clusterNdx = 0; clusterNdx < nmbrClusters; clusterNdx++){ /*L45*/
            int threshold = greedyAlgorithm(townList, clusters[clusterNdx],
            	 nmbrTowns, 0, clusters[clusterNdx].nmbrTownsInCluster,
            	  clusters[clusterNdx].nmbrTownsInCluster); /*L46*/
            ssCnt += recursiveSolver(townList, clusters[clusterNdx],
            	 nmbrTowns, 0, clusters[clusterNdx].nmbrTownsInCluster,
            	  threshold, 0); /*L47*/
        }//for
        //Add the current answer to the complete answer and then read next case.
        returnString += std::to_string(ssCnt) + "\n"; /*L48*/
        std::cin >> nmbrTowns; /*L49*/
        std::cin >> nmbrPairs;
    }//while nmbrTowns is not zero
    
    std::cout << returnString; /*L48*/
    return 0; /*L50*/
}//main





/*---------------------------------------------------------
DESCRIPTION
Recursive solution that uses backtracking 
and thresholds to get around edge cases.
---------------------------------------------------------*/
int recursiveSolver(Town townList[], TownCluster cluster, int nmbrTowns,
	 int ssCnt, int nmbrTownsRemaining, int threshold, int lowestTown) {
    if(nmbrTownsRemaining == 0 || ssCnt == threshold){ /*L51*/
        if(ssCnt < threshold){ /*L52*/
            return ssCnt; /*L53*/
        }//if
        else{ /*L54*/
            return threshold; /*L55*/
        }//else
    }//if
    else if(ssCnt > threshold || threshold == 1){ /*L56*/
        return threshold; /*L57*/
    }//else if
    else{ /*L58*/

        int tempCnt = ssCnt; /*L59*/
        for(int idx = lowestTown; idx < cluster.nmbrTownsInCluster; idx++){ 
			/*L60*/
            tempCnt = ssCnt; /*L61*/
            int tempRemaining = nmbrTownsRemaining; /*L62*/
            if(townList[cluster.townArray[idx]].state != ssTown){ /*L63*/
                tempCnt++; /*L64*/
                Town tempTowns[MAX_TOWNS + 1]; /*L65*/
                for(int copyNdx = 0; copyNdx <= nmbrTowns; copyNdx++){ /*L66*/
                    tempTowns[copyNdx] = townList[copyNdx]; /*L67*/
                }//for
                
                for (int checkNdx = 0; checkNdx 
                	< tempTowns[cluster.townArray[idx]].nmbrNeighbors;
                	checkNdx++) {  /*L68*/
                   Town townChk = tempTowns[cluster.townArray[idx]]; /*L69*/
                    if (tempTowns[townChk.neighbors[checkNdx]].state 
                    	== townInCluster) { /*L70*/
                        tempRemaining--; /*L71*/
                        tempTowns[townChk.neighbors[checkNdx]].state 
                        	= ssAdjTown; /*L72*/
                    }//if
                    
                    
                }//for each town directly connected to townNum
                
                
                if (tempTowns[cluster.townArray[idx]].state != ssAdjTown) { 
					/*L73*/
                    tempRemaining -= 1; /*L74*/
                }//if
                tempTowns[cluster.townArray[idx]].state = ssTown; /*L75*/
                
                tempCnt = greedyAlgorithm(tempTowns, cluster, nmbrTowns,
                		 tempCnt, tempRemaining, threshold); /*L76*/
                if(tempCnt < threshold){ /*L77*/
                    threshold = tempCnt; /*L78*/
                }//if
                if(lowestTown < MAX_SEARCH){ /*L79*/
                    tempCnt = recursiveSolver(tempTowns, cluster,
                    	 nmbrTowns, ssCnt+1, tempRemaining, threshold, idx+1); 
					/*L80*/
                    if(tempCnt < threshold){ /*L81*/
                        threshold = tempCnt; /*L82*/
                    }//if
                }//if
                
            }//if
        }//for
    }//else

    return threshold; /*L83*/
}//recursiveSolver

/*---------------------------------------------------------
DESCRIPTION
The greedy algorithm can be used to create a loose bound on the problem.
We use this to set a threshold to allow us to more effectively prune the 
solution set.
---------------------------------------------------------*/
int greedyAlgorithm(Town townList[], TownCluster cluster, int nmbrTowns,
	int ssCnt, int nmbrTownsRemaining, int threshold){
    
    if(nmbrTownsRemaining == 0 || ssCnt == threshold){ /*L84*/
        return ssCnt; /*L85*/
    }//if
    else{ /*L86*/
        int maxConnections = 0; /*L87*/
        int townNum = 0;
        int maxDeadEnds = 0;
        
        Town tempTowns[MAX_TOWNS + 1]; /*L88*/
        for(int copyNdx = 0; copyNdx <= nmbrTowns; copyNdx++){ /*L89*/
            tempTowns[copyNdx] = townList[copyNdx]; /*L90*/
        }//for
        
        for (int townNdx = 0; townNdx < cluster.nmbrTownsInCluster; townNdx++) 
		{ /*L91*/
            int connectionNmbr = 0; /*L92*/
            int nmbrDeadEnds = 0;
            if (tempTowns[cluster.townArray[townNdx]].state != ssTown) { /*L93*/
                Town townChk = tempTowns[cluster.townArray[townNdx]]; /*L94*/
                
				for (int connNdx = 0; connNdx < townChk.nmbrNeighbors; connNdx++)
				{ /*L95*/
                    
                    if (tempTowns[townChk.neighbors[connNdx]].state 
                    	== townInCluster) { /*L96*/

                        connectionNmbr += 1; /*L97*/
                        
                        bool isDeadEnd = true; /*L98*/
                        for(int deadCheckNdx = 0; deadCheckNdx 
                        	< tempTowns[townChk.neighbors
							[connNdx]].nmbrNeighbors; deadCheckNdx++){ /*L99*/

                            if(tempTowns[townChk.neighbors[connNdx]].townNum 
                            	!= townChk.townNum){ /*L100*/
                                isDeadEnd = false; /*L101*/
                                break; /*L102*/
                            }//if
                        }//for
                        if(isDeadEnd){ /*L103*/
                            nmbrDeadEnds++; /*L104*/
                            connectionNmbr += 1; /*L105*/
                        }//if

                        
                    }//if
                }//for
                
                if (townChk.state != ssAdjTown) { /*L106*/
                    connectionNmbr += 1; /*L107*/
                }//if
                
                if (connectionNmbr > maxConnections 
                	|| (townNum == 0 && townChk.state  != ssAdjTown) 
                	|| (connectionNmbr == maxConnections 
                		&& (townChk.state  == ssAdjTown 
                			|| nmbrDeadEnds > maxDeadEnds))) { /*L108*/

                    townNum = cluster.townArray[townNdx]; /*L109*/
                    maxConnections = connectionNmbr; /*L110*/
                    maxDeadEnds = nmbrDeadEnds; /*L111*/
                }//if
            }//if
            
        }//for

        
        for (int checkNdx = 0; 
        	 checkNdx < tempTowns[townNum].nmbrNeighbors;
        	 checkNdx++) { /*L112*/
            
                if (tempTowns[tempTowns[townNum].neighbors[checkNdx]].state
                	 == townInCluster) { /*L113*/

                    nmbrTownsRemaining -= 1; /*L114*/
                    tempTowns[tempTowns[townNum].neighbors[checkNdx]].state
                     = ssAdjTown; /*L115*/

                }//if
            
        }//for each town directly connected to townNum
        
        if (tempTowns[townNum].state != ssAdjTown) { /*L116*/
            nmbrTownsRemaining -= 1; /*L117*/
        }//if
        ssCnt += 1; /*L118*/
        tempTowns[townNum].state = ssTown; /*L119*/
        return greedyAlgorithm(tempTowns, cluster, nmbrTowns,
         ssCnt, nmbrTownsRemaining, threshold); /*L120*/
    }//else
    
}//greedyAlgorithm

/*---------------------------------------------------------
DESCRIPTION
This checks to see if the two towns passed are connected.
---------------------------------------------------------*/
bool findNeighbor(Town townList[], int townA, int townB){
    bool found = false; /*L121*/
    for(int idx = 0; idx < townList[townA].nmbrNeighbors; idx++){ /*L122*/
        if(townList[townA].neighbors[idx] == townB){ /*L123*/
            found = true; /*L124*/
            break; /*L125*/
        }//if
    }//for
    
    return found; /*L126*/
}//findNeighbor


/*---------------------------------------------------------
DESCRIPTION
This recursively searches for towns that are linked to help build a cluster.
---------------------------------------------------------*/
static TownCluster addLinkedTownsToCluster(Town townList[],
						 int townNdx, TownCluster cluster) {

    for (int linkNdx = 0; linkNdx < townList[townNdx].nmbrNeighbors; linkNdx++) 
	{ /*L127*/
        if (townList[townList[townNdx].neighbors[linkNdx]].state 
        	== notProcessedTown) { /*L128*/
			cluster.townArray[cluster.nmbrTownsInCluster] 
        		= townList[townList[townNdx].neighbors[linkNdx]].townNum; 
			/*L129*/
            townList[townList[townNdx].neighbors[linkNdx]].state 
				= townInCluster; /*L130*/
            cluster.nmbrTownsInCluster++; /*L131*/
            cluster = addLinkedTownsToCluster(townList,
             townList[townList[townNdx].neighbors[linkNdx]].townNum, cluster); 
        }//if
    }//for

    return cluster; /*L132*/
}//addLinkedTownsToCluster

//end ServiceStationv2BTL
