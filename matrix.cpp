/**
 * Anthony Bartman
 * Dr. Varnell
 * Computer Graphics:  CS 3210 021
 * 04/12/2020
 * 
 * Desc:
 *   This file handles all of the matrix method functions.
 */

#include "matrix.h"
#include <string>
#include <cmath>
using namespace std;

//Parameterized constructor for mrow  *With Initializer List
mrow::mrow(double *matrix_row, unsigned int size) : matrix_row(matrix_row), size(size) {}

matrix::matrix(){
	//Creates a 1x1 matrix on heap
	this-> rows = 1;
	this-> cols = 1;

	//Allocates the rows array memory on the heap
	this->the_matrix = new double *[this->rows];

	//Set values to 0 when created
	for (int i = 0; i < this->rows; i++)
	{
		this->the_matrix[i] = new double[this->cols];
		for (int j = 0; j < this->cols; j++)
		{
			this->the_matrix[i][j] = 0;
		}
	}
}

// Parameterized constructor (':' at the end sets the private variables for you, "initializer list")
matrix::matrix(unsigned int rows, unsigned int cols) : rows(rows), cols(cols)
{
	if (rows < 1 || cols < 1)
	{
		throw std::runtime_error("Parameterized constructor: bad arguments");
	}
	//Allocates the rows array memory on the heap
	this->the_matrix = new double *[rows];

	//Set values to 0 when created
	for (int i = 0; i < rows; i++)
	{
		this->the_matrix[i] = new double[cols];
		for (int j = 0; j < cols; j++)
		{
			this->the_matrix[i][j] = 0;
		}
	}
}

// Copy constructor
matrix::matrix(const matrix &from) : rows(from.rows), cols(from.cols)
{
	//Allocates the rows array memory on the heap
	this->the_matrix = new double *[rows];

	//Set values to from.matrix values when created
	for (int i = 0; i < rows; i++)
	{
		this->the_matrix[i] = new double[cols];
		for (int j = 0; j < cols; j++)
		{
			this->the_matrix[i][j] = from.the_matrix[i][j];
		}
	}
}

// Destructor
matrix::~matrix()
{
	//Deletes the second pointer part of the double-pointer Matrix; Cols Part
	for (int i = 0; i < this->rows; i++)
	{
		delete[] this->the_matrix[i];
	}

	//Deletes the first part of the double-pointer matrix; Rows Part
	delete[] this->the_matrix;
}

// Assignment operator
matrix &matrix::operator=(const matrix &rhs)
{
	//This will copy rhs, into an exisiting matrix. NOT CREATE A NEW ONE
	//Checks if the matrix is not equalling itself; for efficiency purposes
	if (this != &rhs)
	{
		//Delete Old Matrix's data on heap, Creates a Dangling Pointer
		this->~matrix();
		//Updates old matrix to rhs matrix rows and cols size
		this->rows = rhs.rows;
		this->cols = rhs.cols;

		//Make the new matrix have different sized memory on heap based on the rhs matrix size
		//Copy RHS matrix data into a new matrix based on RHS size
		this->the_matrix = new double *[rows];
		for (int i = 0; i < rows; i++)
		{
			this->the_matrix[i] = new double[cols];
			for (int j = 0; j < cols; j++)
			{
				this->the_matrix[i][j] = rhs.the_matrix[i][j];
			}
		}
	}

	//Return this new Matrix
	return *this;
}

// Named constructor (static)
matrix matrix::identity(unsigned int size)
{
	if (size < 1)
	{
		throw std::runtime_error("Matrix Size Needs to Be Larger than 0: bad arguments");
	}
	//Allocates the new identity matrix on the heap
	matrix identity(size, size);

	//Create an identity matrix
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i == j)
			{
				identity.the_matrix[i][j] = 1;
			}
		}
	}

	return identity;
}

// Binary operations
matrix matrix::operator+(const matrix &rhs) const
{
	//Checks if size of matrices are equal
	if ((this->rows * this->cols) != (rhs.rows * rhs.cols))
	{
		throw std::runtime_error("Matrix Size Needs to Be Equal In Order to Add: bad arguments");
	}
	//New Resultant Matrix
	matrix result(this->rows, this->cols);
	//Adds Matrices together
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			result[i][j] = this->the_matrix[i][j] + rhs.the_matrix[i][j];
		}
	}
	return result;
}

//Multiplies Matrices Together
matrix matrix::operator*(const matrix &rhs) const
{
	//Checks if size of matrices are equal
	if (this->cols != rhs.rows)
	{
		throw std::runtime_error("M1 Cols and M2 Rows Need to Be Equal In Order to Multiply: bad arguments");
	}

	//Stores resultant Matrix
	matrix result(this->rows, rhs.cols);

	//Multiply Matrices
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < rhs.cols; j++)
		{
			for (int k = 0; k < rhs.rows; k++)
			{
				result.the_matrix[i][j] += (this->the_matrix[i][k] * rhs.the_matrix[k][j]);
			}
		}
	}
	return result;
}

//Multiply matrix together by a number
matrix matrix::operator*(const double scale) const
{
	//Stores resultant Matrix
	matrix result(this->rows, this->cols);

	//Multiply Matrices
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			result.the_matrix[i][j] = this->the_matrix[i][j] * scale;
		}
	}
	return result;
}

// Unary operations
//Transpose Matrix
matrix matrix::operator~() const
{
	//Creates Resultant Matrix
	matrix result(this->cols, this->rows);

	//Transposes Matrix
	for (int i = 0; i < this->cols; i++)
	{
		for (int j = 0; j < this->rows; j++)
		{
			result.the_matrix[i][j] = this->the_matrix[j][i];
		}
	}
	return result;
}

//Sets all values inside matrix to 0
void matrix::clear()
{
	//Clears contents of matrix
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			this->the_matrix[i][j] = 0;
		}
	}
}

//Makes this work; m1[n][n] = number;
mrow matrix::operator[](unsigned int row)
{
	if (this->rows <= row)
	{
		throw std::runtime_error("Row Index is too large!");
	}
	mrow mr(the_matrix[row], cols);
	return mr;
}

//Makes this work; cout << m[n][n];
mrow matrix::operator[](unsigned int row) const
{
	//Check if there are enough rows in the matrix
	if (this->rows <= row)
	{
		throw std::runtime_error("Row Index is too large!");
	}

	mrow mr(the_matrix[row], cols);
	return mr;
}

//This will check, based on mrow, if the column is too large
double &mrow::operator[](unsigned int col)
{
	//Check if the column is within the size of the matrix
	if (this->size <= col)
	{
		throw std::runtime_error("Column index is too large");
	}

	return this->matrix_row[col];
}

//This will check, based on mrow, if the column is too large using const
double mrow::operator[](unsigned int col) const
{
	//Check if the column is within the size of the matrix
	if (this->size <= col)
	{
		throw std::runtime_error("Column index is too large");
	}
	
	return this->matrix_row[col];
}

// Global insertion and operator
std::ostream &operator<<(std::ostream &os, const matrix &rhs)
{
	for (int i = 0; i < rhs.rows; i++)
	{
		for (int j = 0; j < rhs.cols; j++)
		{
			os << rhs.the_matrix[i][j] << " ";
		}
		os << endl;
	}
	return os;
}

// Global scalar multiplication
matrix operator*(const double scale, const matrix &rhs)
{
	//Stores resultant Matrix
	matrix result(rhs.rows, rhs.cols);

	//Multiply Matrices
	for (int i = 0; i < rhs.rows; i++)
	{
		for (int j = 0; j < rhs.cols; j++)
		{
			result.the_matrix[i][j] = rhs.the_matrix[i][j] * scale;
		}
	}
	return result;
}
