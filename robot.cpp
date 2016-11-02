/*
 * robot.cpp
 *
 *  Created on: Oct 5, 2016
 *      Author: Praveen
 */
#include"robot.h"
#include <bitset>
#include<iostream>
#include<exception>
#include<sstream>
#include<math.h>
#include<iomanip>
#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;

/*********************** UTILITY FUNCTIONS ************************/
/**
Utility function

takes a number input and returns bit form as string
Ex: 15 as input will give "1111" as output

@param  int num integer input
@return string
*/
string get_binary(int num){
	string s = std::bitset< 4 >( num ).to_string();
	return s;
}

/**
Utility function

takes two string with binary data and returns the count of different bits
Ex: inputs "1101" and "1100" will return 1

@param  string input1
@param  string input2
@return string
*/
int countBinaryDiff(string a, string b)
{
	int count=0;
	for(int i=0;i<4;i++){
		if(a[i] != b[i])
			count++;
	}
	return count;
}

/**
Utility function

takes string with binary data and returns the count of different bits

Ex: input "NSE" will return 1101
	input "0" will return 0000

@param  char * sensor_input
@return string
*/
string calcDirection(char *sensor){
	string sensor_input(sensor);
	string output="";

	if(sensor_input.find("0")  != string::npos){
		output+="0000";
		return output;
	}

	if(sensor_input.find("N") != string::npos)
		output+="1";
	else
		output+="0";
	if(sensor_input.find("S") != string::npos)
		output+="1";
	else
		output+="0";
	if(sensor_input.find("W") != string::npos)
		output+="1";
	else
		output+="0";
	if(sensor_input.find("E") != string::npos)
		output+="1";
	else
		output+="0";
	return output;
}

/***********************END OF UTILITY FUNCTIONS ************************/

/**
Constructor for Robot Class

initializes Grid and Sensory precision table
constructs and initializes matrices T, O, J, Y

@param  string input filename
@param  double error sensor input precision
@return Robot
*/
Robot::Robot(char * filename, double error){
	GridTable=initGridTable(filename);
	SensoryTable=initSensoryTable(error);
	States=GridTable.size() * GridTable[0].size();

	mat_T = Matrix(States,States);
	mat_O = Matrix(States,States);
	mat_J = Matrix(States,1);
	mat_Y = Matrix(States,States);
	initMatrixJ();
	//mat_J.show();
	initMatrixT();
	//mat_T.show();

	mat_J = mat_T.multiply(mat_J);

}

/**
 Method for constructing Matrix O

constructs matrix O from sensor input by calculating bit difference.
uses data from Sensory Table for the Observation Probability for the given bit difference.

@param  string input filename
@return void
*/
void Robot::consturctMatrixO(char *sensor_input){
	int count=0, bitDiff=0 ;
		long double observationProb;
		string directionBits, sensorBits;
		sensorBits = calcDirection(sensor_input);

		for(unsigned i=0;i<GridTable.size();i++){
			for(unsigned j=0;j<GridTable[i].size();j++){
				directionBits = get_binary(GridTable[i][j]);
				bitDiff = countBinaryDiff(sensorBits, directionBits);
				observationProb = SensoryTable[bitDiff];
				mat_O.set(count,count,observationProb);
				count++;

			}
		}
}

/**
 Method for initializing SensoryTable

initializes Sensory precision table using precision error rate of sensor

@param  double error
@return map<int, long double>
*/
map<int, long double> Robot::initSensoryTable(double error){
	 map<int, long double> table;
	  double f1,f2;
	  long double value=0.0;
	 for(int i=0;i<5;i++){
		 f1=pow(error,i);
		 f2=pow((1-error),(4-i));
		 //cout<<"f1 "<<f1<<" f2 "<<f2<<endl;
		 value= f1*f2;
		 table.insert(std::make_pair(i,value));
	 }
	 return table;
}

/**
 Method for initializing Grid Table

initializes Grid Table
reads from input file and stores grid values in a 2-d vector

@param  string input filename
@return vector<vector<int> > 2-d vector holding grid values
*/
vector<vector<int> > Robot::initGridTable(char* filename){
	vector<vector<int> > GridTable;
	vector<int> temp;
	fstream inFile;   // input file
	int z;

	inFile.open(filename);
	if (!inFile)
	{
	   cout << "The input file could not be opened."<<endl;
	}

	while(true){
		if(inFile.peek() == EOF){
			break;
		}
	    while (inFile.peek() != '\n')
	    {
			inFile>>z;
			temp.push_back(z);
			//cout<<" "<<z<<endl;
	    }
	    GridTable.push_back(temp);
	    inFile>>z;
	    temp.clear();
	    temp.push_back(z);

		}

	return GridTable;

}

/**
 Method for initializing Matrix T

initializes transition probabilities using values in grid
uses binary form of grid value
calculates transition probability as 1.0 / no of free directions

set calculated transition probability to adjacent grid elements.

@param  void
@return void
*/
void Robot::initMatrixT(){
	int count=0, bitSum=0 ,rowSize=0;
	long double transitionProb;
	string directionBits;

	rowSize = GridTable[0].size();
	for(unsigned i=0;i<GridTable.size();i++){
		for(unsigned j=0;j<GridTable[i].size();j++){
			directionBits = get_binary(GridTable[i][j]);
			bitSum= 0;
			if(GridTable[i][j] != 15){
				for(int k=0;k<4;k++){
					if(directionBits[k] == '0')
						bitSum++;
				}
				transitionProb= 1.0/bitSum;
				if(directionBits[0]=='0')
					mat_T.set(count-rowSize,count,transitionProb);
				if(directionBits[1]=='0')
					mat_T.set(count+rowSize,count,transitionProb);
				if(directionBits[2]=='0')
					mat_T.set(count-1,count,transitionProb);
				if(directionBits[3]=='0')
					mat_T.set(count+1,count,transitionProb);
			}
			count++;

		}
	}
}

/**
 Method for initializing Matrix J

constructs matrix J by using grid data from GridTable.

@param  void
@return void
*/
void Robot::initMatrixJ(){
	int count=0;
	long double initialProb;
	for(unsigned i=0;i<GridTable.size();i++){
		for(unsigned j=0;j<GridTable[i].size();j++){
			if(GridTable[i][j] != 15)
				count++;
		}
	}

	initialProb = 1.0/count;
	//cout<<"count "<<count<<" prob : "<<initialProb<<endl;
	count=0;
	for(unsigned i=0;i<GridTable.size();i++){
		for(unsigned j=0;j<GridTable[i].size();j++){
			if(GridTable[i][j] != 15){
				mat_J.set(count,0,initialProb);
			}
			count++;

		}
	}
}

/**
 Method for printing Max EstmationProbability per iteration

called for each sensor input

constructs Matrix O for given sensor input
 Y= O x J
 print the max estimation probability from matrix Y
 update current J as
 J= T x Y

@param  string input filename
@return void
*/
void Robot::printMaxEstimationProbabilityResults(char * sensor_input){
	vector<long double> estimationProb;
	long double maxProb=0.0;
	consturctMatrixO(sensor_input);

	mat_Y =  mat_O.multiply(mat_J);
	mat_J =  mat_T.multiply(mat_Y);
	long double sum= 0.0;
	for(int i=0;i<States;i++){
		sum = sum + mat_Y.get(i,0);
	}

	for(int i=0;i<States;i++){
		if(mat_Y.get(i,0)/sum > maxProb)
			maxProb = mat_Y.get(i,0)/sum;
		estimationProb.push_back(mat_Y.get(i,0)/sum);
	}
	cout << std::showpoint << std::fixed << setprecision(12) << maxProb<<" " ;
	for(int i=0;i<States;i++){
		if(estimationProb[i] == maxProb) {
			cout<<i<<" ";
		}
	}
	cout<<endl;
	return;
}
