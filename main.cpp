/**
 * Anthony Bartman
 * Dr. Varnell
 * Computer Graphics:  CS 3210 021
 * 05/03/2020
 * 
 * Desc:
 *   This file handles all of the main method functions.
 */

#include <iostream> // <iostream.h> is outdated
#include <fstream>	//Use fstream library to read in from file
#include <sstream>	//Read words from string
#include <string>
#include <iomanip>	//Format input/output
#include <limits>	//Holds Int Min and Max
#include <unistd.h> //Sleep
using namespace std;

#include "x11context.h"
#include "image.h"
#include "shape.h"
#include "mydrawing.h"
#include "viewcontext.h"

//This Main method will test all of the matrix.cpp method constructors
int main(int argc, char *argv[])
{
	GraphicsContext *gc = new X11Context(800,600,GraphicsContext::BLACK);

	gc->setColor(GraphicsContext::GREEN);

	//make a drawing
	mydrawing md(gc);

	//Start event loop
	gc->runLoop(&md);

	delete gc;

	return 0;
}
