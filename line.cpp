/**
 * Anthony Bartman
 * Dr. Varnell
 * Computer Graphics:  CS 3210 021
 * 05/03/2020
 * 
 * Desc:
 *   This file handles all of the line method functions.
 */

#include "line.h"

/*********************************************************
* Construction / Destruction
*********************************************************/
//Constructor (line s;)
line::line()
{
	//Initializes 4x1 Matrices on the heap
	this->c0 = matrix(4,1);
	this->c1 = matrix(4,1);
	//Set Beginning Coordinates
	this->c0[0][0] = 0;
	this->c0[1][0] = 0;
	this->c0[2][0] = 0;
	this->c0[3][0] = 1.0;
	//Set Ending Coordinates
	this->c1[0][0] = 0;
	this->c1[1][0] = 0;
	this->c1[2][0] = 0;
	this->c1[3][0] = 1.0;
	//Set color (Black)
	this->color = 0x000000;
}
//Parameterized Constructor (line s(red);)
line::line(double x0, double y0, double x1, double y1, unsigned int color)
{
	//Initializes 4x1 Matrices on the heap
	this->c0 = matrix(4,1);
	this->c1 = matrix(4,1);
	//Set Beginning Coordinates
	this->c0[0][0] = x0;
	this->c0[1][0] = y0;
	this->c0[2][0] = 0;
	this->c0[3][0] = 1.0;
	//Set Ending Coordinates
	this->c1[0][0] = x1;
	this->c1[1][0] = y1;
	this->c1[2][0] = 0;
	this->c1[3][0] = 1.0;
	//Set color (Make it a 24-bit value)
	//color &= !(0xFFFFFF00);
	this->color = color;
}
//Copy Constructor (line s = s1;)
line::line(const line &rhs)
{
	//Sets memory address to the line memory addreses
	this->c0 = matrix(rhs.c0);
	this->c1 = matrix(rhs.c1);
	//Set color
	this->color = rhs.color;
}
//Destructor
line::~line() {}

/*********************************************************
* Assignement Operators
*********************************************************/
//Equals Operator (s1 = s2;) Virtual makes only children do this
line &line::operator=(const line &rhs)
{
	//Checks if the line is not equalling itself; for efficiency purposes
	if (this != &rhs)
	{
		//Set Beginning Coordinates
		this->c0 = matrix(rhs.c0);
		this->c1 = matrix(rhs.c1);
		//Set color
		this->color = rhs.color;
	}
}

/*********************************************************
* Drawing operations
*********************************************************/
void line::draw(GraphicsContext *gc,viewcontext *vc)
{
	//Set color of line
	gc->setColor(this->color);

	//New Coord Matrix
	matrix newCoordStart(4,1);
	matrix newCoordEnd(4,1);
	newCoordStart = vc->modelToDevice * this->c0;
	newCoordEnd = vc->modelToDevice * this->c1;
	
	//Coordinates to draw line
	gc->drawLine(newCoordStart[0][0],newCoordStart[1][0],newCoordEnd[0][0],newCoordEnd[1][0]);
}

//Clears a specific line off of the screen.
void line::erase(){}

//Used to make copies of lines for memory purposes
shape *line::clone()
{
	return new line(*this);
}

void line::deviceToModel(viewcontext *vc){
	//Multiply coordinates to change them to model coordinates
	//Translate then flip
	this->c0 = vc->deviceToModel * this->c0; 
	this->c1 = vc->deviceToModel * this->c1;
}


/*********************************************************
* Utility operations
*********************************************************/
//Dumps line properties to the output stream
ostream &line::out(ostream &os) const
{
	os << "L:" << endl;
	os << this->c0[0][0] << " " << this->c0[1][0] << " " << this->c0[2][0] << " " << this->c0[3][0] << endl;
	os << this->c1[0][0] << " " << this->c1[1][0] << " " << this->c1[2][0] << " " << this->c1[3][0] << endl;
	//Output color
	this->shape::out(os);
}

//Read line properties from a text file
istream &line::in(istream &is)
{
	double x,y,z,num;
	is >> x >> y;
	this->c0[0][0] = x;
	this->c0[1][0] = y;
	is >> z >> num;
	// this->c0[2][0] = z;
	// this->c0[3][0] = num;

	is >> x >> y;
	this->c1[0][0] = x;
	this->c1[1][0] = y;
	is >> z >> num;
	// this->c1[2][0] = z;
	// this->c1[3][0] = num;
	//Input color
	shape::in(is);
}
