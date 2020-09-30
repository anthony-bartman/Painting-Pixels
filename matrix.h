/**
 * matrix.h - declaration of matrix class.  This class will be
 * capable of represting a Matrix as a first-class type.
 * 
 * Do not change any public methods in this file unless otherwise
 * instructed.
 *
 * For CS321.  (c) 2015 Dr. Darrin Rothe
 * Varnell 2020
 */

// compile guard
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>	 // for std::ostream
#include <stdexcept> // for std::runtime_error
#include <string>	 // used in exception

//This class will allow the matrix to know if a size of a row or column is too large to find
//based on the size of the matrix
class mrow
{
public:
	//Constructor for mrow
	mrow(double* matrix_row, unsigned int size);

	//Used for getting values of the matrix at a row,col vector; m1[1][2] = 5
	double& operator[](unsigned int col);
	//Used for outputting values with row,col vector using an output stream; cout << m1[3][2];
	double operator[](unsigned int col) const;

private:
	//Holds a list of pointers to all of the columns in this row
	double* matrix_row;
	//Number of columns within this row
	unsigned int size;
};

class matrix
{
public:
	//Insertion operator a friend so it can access matrix
	// class private variables
	friend std::ostream &operator<<(std::ostream &os, const matrix &rhs);

	// Default Constructor used to compile
	matrix();

	// Constructor: create Matrix and clear cells.  If rows or
	// cols is < 1, throw a matrixException. 
	matrix(unsigned int rows, unsigned int cols);

	// Copy constructor - make a new Matrix just like rhs
	matrix(const matrix &from);

	// Destructor.  Free allocated memory
	~matrix();

	// Assignment operator - make this just like rhs.  Must function
	// correctly even if rhs is a different size than this.
	matrix &operator=(const matrix &rhs);

	// Named Constructor - produce a square identity matrix of the
	// requested size.  Since we do not know how the object produced will
	// be used, we pretty much have to return by value.  A size of 0
	// would not make sense and should throw an exception.
	//
	// throw (matrixException)
	//
	static matrix identity(unsigned int size);

	// Matrix addition - lhs and rhs must be same size otherwise
	// an exception shall be thrown
	//
	// throw (matrixException)
	//
	matrix operator+(const matrix &rhs) const;

	// Matrix multiplication - lhs and rhs must be compatible
	// otherwise an exception shall be thrown
	//
	// throw (matrixException)
	//
	friend matrix operator*(const double scale, const matrix &rhs);

	matrix operator*(const matrix &rhs) const;

	// Scalar multiplication.  Note, this function will support
	// someMatrixObject * 5.0
	matrix operator*(const double scale) const;

	// Transpose of a Matrix - should always work, hence no exception
	matrix operator~() const;

	// Clear Matrix to all members 0.0
	void clear();

	// Access Operators - throw an exception if index out of range
	//
	// Note how these operators are to work.  Consider a Matrix
	// object being addressed with two sets of brackets - m1[1][2],
	// for example.  The compiler will execute this: (m1[1])[2].
	// The first set of brackets will call this function, and this
	// function should return a pointer to the first element of the
	// requested row.  The second set of brackets is applied to the
	// double*, which results in it being treated as an array, thus
	// the requested column is indexed.  The const version is
	// necessary if you would like to use the operator within other
	// const methods.  Both of these operators are extremely
	// dangerous as prototyped.  The nature of the danger and
	// a fix are left up to you to discover and fix.  A proper
	// fix will require a change to these function signatures
	// and the use of an internal "helper class."
	//
	// throw (matrixException)
	//
	mrow operator[](unsigned int row);

	// const version of above - throws an exception if indices are out of
	// range
	//
	// throw (matrixException)
	//
	mrow operator[](unsigned int row) const;

	// I/O - for convenience - this is intended to be called by the global
	// << operator declared below.
	std::ostream &out(std::ostream &os) const;

private:
	// The data - note, per discussion on arrays, you can store these data
	// as a 1-D dynamic array, thus the double* below.  Alternatively, and
	// perhaps preferred, you could store the data as an array of arrays
	// which would require the_Matrix to be changed to a double**.
	double** the_matrix;
	unsigned int rows;
	unsigned int cols;
};

/** Some Related Global Functions **/

// Overloaded global << with std::ostream as lhs, Matrix as rhs.  This method outputs
//matrix into pretty format
std::ostream &operator<<(std::ostream &os, const matrix &rhs);

// Scalar multiplication with a global function.  Note, this function will
// supports 5.0 * someMatrixObject
matrix operator*(const double scale, const matrix &rhs);

#endif