/*
 * matrix.cpp
 *
 *  Created on: Oct 2, 2016
 *      Author: Praveen
 */
#include"matrix.h"
#include<iostream>

/**
Matrix Default Constructor

*/
Matrix::Matrix(){

}
/**
Matrix Constructor


@param  std::vector<std::vector<long double> > m  2-d vector which stores matrix elements
@return Matrix matrix with 2-d vector as input
*/
Matrix::Matrix(std::vector<std::vector<long double> > m){
	_matrix=m;
}

/**
Constructor of Matrix
sets rows and cols , fills all elements as 0

@param  int rows rows to be set in matrix
@param  int cols columns to be set in matrix.
@return Matrix matrix of size row x cols
*/
Matrix::Matrix(int rows, int cols){
	std::vector<std::vector<long double> > m(rows, std::vector<long double>(cols,0));
	_matrix=m;
}


/**
Function for performing matrix multiplication

Multiplication n X n with n X 1 gives n X 1 matrix.

@param  Matrix & m1 matrix with which this matrix is multiplied with
@return Matrix matrix product of this matrix with matrix m1
*/
Matrix Matrix::multiply(Matrix & m1){
	std::vector<std::vector<long double> > A=_matrix;
	std::vector<std::vector<long double> >B=m1._matrix;
	std::vector<std::vector<long double> > C(B.size());

	if (A[0].size() != B.size())
	{
		std::cout<<"Size mismatch"<<std::endl;
		return C;
	}
	int col_no=0, out_row=0;
	long double row_sum=0.0;
	std::vector< std::vector <long double> >:: iterator it;
	std::vector <long double> :: iterator it_inner;

	for(it=A.begin();it!=A.end();it++){
		col_no=0;
		row_sum=0.0;
		for(it_inner=(*it).begin();it_inner!=(*it).end();it_inner++,col_no++){
			//std::cout<<"value " << (*it_inner) <<" "<<col_no <<" "<< B[col_no][0]<<std::endl;
			row_sum=row_sum+(*it_inner)*B[col_no][0];

		}
		C[out_row] = std::vector<long double>(1,row_sum);
		out_row++;

	}

	Matrix out(C);
	return out;
}

/**
Getter
Function for getting matrix element at given row and column

@param  int  row at which matrix element is required.
@param  int  col at which matrix element is required.
@return long double Matrix element
*/
long double Matrix::get(int row, int col){
	return _matrix[row][col];
}
/**
Setter
Function for setting matrix element at given rwo and column

@param  int  row at which matrix element is set.
@param  int  col at which matrix element is set.
@param  long double  matrix element to be set.
@return void
*/
void Matrix::set(int row, int col,long double value){
	_matrix[row][col]=value;
}

