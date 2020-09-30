/* This is an abstract base class representing a generic graphics
 * context.  Most implementation specifics will need to be provided by
 * a concrete implementation.  See header file for specifics. */

#define _USE_MATH_DEFINES // for M_PI
#include <cmath>		  // for trig functions
#include "gcontext.h"

/*
 * Destructor - does nothing
 */
GraphicsContext::~GraphicsContext()
{
	// nothing to do
	// here to insure subclasses handle destruction properly
}

void GraphicsContext::plotEigthCircle(int xcenter, int ycenter, int x, int y)
{
	//Plots 1/8th of the circle at once
	setPixel(xcenter + x, ycenter + y);
	setPixel(xcenter + y, ycenter + x);
	setPixel(xcenter - y, ycenter + x);
	setPixel(xcenter + x, ycenter - y);
	setPixel(xcenter - x, ycenter - y);
	setPixel(xcenter - y, ycenter - x);
	setPixel(xcenter + y, ycenter - x);
	setPixel(xcenter - x, ycenter + y);
}


void GraphicsContext::drawLine(int x0, int y0, int x1, int y1){}

void GraphicsContext::drawCircle(int x0, int y0, unsigned int radius){}

void GraphicsContext::endLoop()
{
	run = false;
}
