/*
 * matrix.h
 *
 *  Created on: Oct 2, 2016
 *      Author: Praveen
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include<vector>
class Matrix{
private:
	std::vector<std::vector<long double> > _matrix;
public:
	Matrix(std::vector<std::vector<long double> > m);
	Matrix(int,int);
	Matrix();
	long double get(int row, int col);
	void set(int row, int col, long double value);
	Matrix multiply(Matrix& m2);
};

#endif /* MATRIX_H_ */
