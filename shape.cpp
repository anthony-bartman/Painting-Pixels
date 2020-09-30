/**
 * Anthony Bartman
 * Dr. Varnell
 * Computer Graphics:  CS 3210 021
 * 05/03/2020
 * 
 * Desc:
 *   This file handles all of the shape method functions.
 */

#include "shape.h"

/*********************************************************
* Construction / Destruction
*********************************************************/
//Constructor (Shape s;)
shape::shape()
{
    //Sets shape color to black
    this->color = 0x000000;
}
//Parameterized Constructor (Shape s(red);)
shape::shape(unsigned int color)
{
    //Set color (Make it a 24-bit value)
    //color &= !(0xFFFFFF00);
    this->color = color;
}
//Copy Constructor (Shape s = s1;)
shape::shape(const shape &rhs)
{
    //Set color
    this->color = rhs.color;
}
//Virtual Destructor
shape::~shape() {}

/*********************************************************
* Assignement Operators
*********************************************************/
//Equals Operator (s1 = s2;)
shape &shape::operator=(const shape &rhs)
{
    //Checks if the shape is not equalling itself; for efficiency purposes
    if (this != &rhs)
    {
        //Set color
        this->color = rhs.color;
    }
}

/*********************************************************
 * Utility operations
 *********************************************************/
//Dumps shape properties to the output stream
ostream &shape::out(ostream &os) const {
    os << this->color << endl;
}

//Read shape properties from a text file
istream &shape::in(istream &is){
    int color;
    is >> color;
    this->color = color;
}