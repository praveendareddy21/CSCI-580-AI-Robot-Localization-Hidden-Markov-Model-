/*
 * main.cpp
 *
 *  Created on: Oct 2, 2016
 *      Author: Praveen
 */

#include<stdlib.h>
#include<iostream>
#include"robot.h"

using namespace std;

/**
Driver

takes argument input from command line
constructs robot object
print the result for each sensor input in a loop


@param  command line argument
@return 0
*/
int main(int argc, char* argv[]){
	double rate = strtod(argv[2], NULL);
	Robot r(argv[1], rate);
	for (int n = 3; n < argc; n++){
		r.printMaxEstimationProbabilityResults(argv[n]);
	}
	return 0;
}
