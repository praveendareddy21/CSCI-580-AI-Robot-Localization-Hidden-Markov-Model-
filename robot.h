/*
 * robot.h
 *
 *  Created on: Oct 5, 2016
 *      Author: Praveen
 */

#ifndef ROBOT_H_
#define ROBOT_H_
#include"matrix.h"
#include<map>

class Robot{
private:
	std::vector<std::vector<int> > GridTable;
	std::map<int, long double> SensoryTable;
	int States;
	Matrix mat_T;
	Matrix mat_J;
	Matrix mat_O;
	Matrix mat_Y;


	std::map<int, long double> initSensoryTable(double error);
	std::vector<std::vector<int> > initGridTable(char* filename);
	void initMatrixT();
	void initMatrixJ();
	void consturctMatrixO(char *sensor_input);

public:
	Robot(char * filename, double error);
    void printMaxEstimationProbabilityResults(char * sensor_input);
};

#endif /* ROBOT_H_ */
