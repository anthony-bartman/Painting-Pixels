/**
 * Anthony Bartman
 * Dr. Varnell
 * Computer Graphics:  CS 3210 021
 * 05/03/2020
 * 
 * Desc:
 *   This file handles all of the triangle method functions.
 */

#include "triangle.h"

/*********************************************************
* Construction / Destruction
*********************************************************/
//Constructor (triangle s;)
triangle::triangle()
{
	//Initializes 4x1 Matrices on the heap
	this->c0 = matrix(4, 1);
	this->c1 = matrix(4, 1);
	this->c2 = matrix(4, 1);
	//Set 1 Vertex Coordinates
	this->c0[3][0] = 1.0;
	//Set 2nd Vertex Coordinates
	this->c1[3][0] = 1.0;
	//Set 3rd Vertex Coordinates
	this->c2[3][0] = 1.0;
	//Set color (Black)
	this->color = 0x000000;
}
//Parameterized Constructor (triangle s(red);)
triangle::triangle(double x0, double y0, double x1, double y1, double x2, double y2, unsigned int color)
{
	//Initializes 4x1 Matrices on the heap
	this->c0 = matrix(4, 1);
	this->c1 = matrix(4, 1);
	this->c2 = matrix(4, 1);
	//Set 1 Vertex Coordinates
	this->c0[0][0] = x0;
	this->c0[1][0] = y0;
	this->c0[2][0] = 0;
	this->c0[3][0] = 1.0;
	//Set 2nd Vertex Coordinates
	this->c1[0][0] = x1;
	this->c1[1][0] = y1;
	this->c1[2][0] = 0;
	this->c1[3][0] = 1.0;
	//Set 3rd Vertex Coordinates
	this->c2[0][0] = x2;
	this->c2[1][0] = y2;
	this->c2[2][0] = 0;
	this->c2[3][0] = 1.0;
	//Set color (Black)
	this->color = color;
}
//Copy Constructor (triangle s = s1;)
triangle::triangle(const triangle &rhs)
{
	//Initializes 4x1 Matrices on the heap
	this->c0 = matrix(4, 1);
	this->c1 = matrix(4, 1);
	this->c2 = matrix(4, 1);
	//Sets memory address to the line memory addreses
	this->c0 = matrix(rhs.c0);
	this->c1 = matrix(rhs.c1);
	this->c2 = matrix(rhs.c2);
	//Set color
	this->color = rhs.color;
}
//Destructor
triangle::~triangle() {}

/*********************************************************
* Assignement Operators
*********************************************************/
//Equals Operator (s1 = s2;) Virtual makes only children do this
triangle &triangle::operator=(const triangle &rhs)
{
	//Checks if the line is not equalling itself; for efficiency purposes
	if (this != &rhs)
	{
		//Set Vertex 1 Coordinates
		this->c0[0][0] = rhs.c0[0][0];
		this->c0[1][0] = rhs.c0[1][0];
		this->c0[2][0] = rhs.c0[2][0];
		this->c0[3][0] = rhs.c0[3][0];
		//Set Vertex 2 Coordinates
		this->c1[0][0] = rhs.c1[0][0];
		this->c1[1][0] = rhs.c1[1][0];
		this->c1[2][0] = rhs.c1[2][0];
		this->c1[3][0] = rhs.c1[3][0];
		//Set Vertex 3 Coordinates
		this->c2[0][0] = rhs.c2[0][0];
		this->c2[1][0] = rhs.c2[1][0];
		this->c2[2][0] = rhs.c2[2][0];
		this->c2[3][0] = rhs.c2[3][0];
		//Set color
		this->color = rhs.color;
	}
}

/*********************************************************
* Drawing operations
*********************************************************/
//Draws the triangle
void triangle::draw(GraphicsContext *gc,viewcontext *vc)
{
	//Sets Color
	gc->setColor(this->color);
	//Calculates device coordinates
	matrix newCoordStart(4,1);
	matrix newCoordMid(4,1);
	matrix newCoordEnd(4,1);
	newCoordStart = vc->modelToDevice * this->c0;
	newCoordMid = vc->modelToDevice * this->c1;
	newCoordEnd = vc->modelToDevice * this->c2;

	//Draw Triangle
	gc->drawLine(newCoordStart[0][0],newCoordStart[1][0],newCoordMid[0][0],newCoordMid[1][0]);
	gc->drawLine(newCoordMid[0][0],newCoordMid[1][0],newCoordEnd[0][0],newCoordEnd[1][0]);
	gc->drawLine(newCoordStart[0][0],newCoordStart[1][0],newCoordEnd[0][0],newCoordEnd[1][0]);

}

//Clears a specific triangle off of the screen. WILL ALWAYS GO TO CHILD CLASS
void triangle::erase() {}

//Used to make copies of triangles for memory purposes
shape *triangle::clone()
{
	return new triangle(*this);
}

void triangle::deviceToModel(viewcontext *vc){
	//Multiply coordinates to change them to model coordinates
	//Translate then flip
	this->c0 = vc->deviceToModel * this->c0; 
	this->c1 = vc->deviceToModel * this->c1;
	this->c2 = vc->deviceToModel * this->c2;
}


/*********************************************************
* Utility operations
*********************************************************/
//Dumps triangle properties to the output stream
ostream &triangle::out(ostream &os) const
{
	os << "T:" << endl;
	os << this->c0[0][0] << " " << this->c0[1][0] << " " << this->c0[2][0] << " " << this->c0[3][0] << endl;
	os << this->c1[0][0] << " " << this->c1[1][0] << " " << this->c1[2][0] << " " << this->c1[3][0] << endl;
	os << this->c2[0][0] << " " << this->c2[1][0] << " " << this->c2[2][0] << " " << this->c2[3][0] << endl;
	//Outputs color
	shape::out(os);
}

//Read triangle properties from a text file
istream &triangle::in(istream &is)
{
	double x, y, z, num;
	is >> x >> y;
	this->c0[0][0] = x;
	this->c0[1][0] = y;
	is >> z >> num;

	is >> x >> y;
	this->c1[0][0] = x;
	this->c1[1][0] = y;
	is >> z >> num;

	is >> x >> y;
	this->c2[0][0] = x;
	this->c2[1][0] = y;
	is >> z >> num;

	//Gets Color
	shape::in(is);

}
