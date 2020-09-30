#ifndef LINE_H
#define LINE_H

#include "matrix.h" //Stores Coordinates in a 4x1 Matrix
#include "shape.h" //Abstract Base Class
#include "gcontext.h" //Graphics Context to draw pixels
#include "viewcontext.h"

using namespace std;

/**
 * This class will draw lines and store them in memory
 * 
 * Inherits from a Shape Class methods and a 'color' attribute 
 */    

class line : public shape
{
	public:
		/*********************************************************
		 * Construction / Destruction
		 *********************************************************/
        /*Default constructor(line l();) */
        line();
        /* Parameterized Constructor(line l(x,y,x,y,red);)
		 * 
		 * Parameters:
		 * 	x0, y0 - Starting point
		 *  x1, y1 - Ending Point
		 *  color - color of shape 
		 */
        line(double x0,double y0,double x1, double y1, unsigned int color);
        /* Copy Constructor(line l = l1;)
		 * 
		 * Parameters:
		 * 	rhs - line being copied from that has already been created, l1 above
		 */
        line(const line &rhs);
        /* Destructor */
		~line();

		/*********************************************************
		 * Drawing operations
		 *********************************************************/
		/* This will use a Bresingham line drawing algorithm to draw a line.
		 * 
		 * Parameters:
		 * 	gc - Handles the screen pixels which to draw the line on
		 */		
		void draw(GraphicsContext *gc,viewcontext *vc);
		/* This will use erase all lines off of the screen
		 * (Not Implemented Yet)
		 */				
		void erase();

		/* This will use clone a line to the heap when the image
		 * class wants to add a stack-variable line to the image.
		 */			
		shape* clone();

		/*  This method converts the deviceCoords to the Model Coordinates
		 *  for the triangle.
		 */ 
		void deviceToModel(viewcontext *vc);
		/*********************************************************
		 * Utility operations
		 *********************************************************/
		/* This will output all of the line's properties to a file
	  	 * in a specific format.
		 * 
		 * Parameters:
		 * 	os - Output stream to a file or console
		 */           
		ostream &out(ostream &os) const;

		/* This will read in the line attributes from a text file and
		 * set them to a new line object on the heap
		 * 
		 * Parameters:
		 * 	is - Input stream holding the input text file
		 */				
		istream &in(istream &is);

        /*********************************************************
		 * Assignement Operators
		 *********************************************************/
	    /* This method allows lines contents to be equal to each other.
		 * Copies rhs contents into left side line.
		 * 
		 * Parameters:
		 * 	rhs =  right hand side of equals operator (line = rhs;)
		 */
        line &operator=(const line &rhs);

	private:		
        //These hold the 2 different coordinates for the 2 vertices of the line
        matrix c0;
        matrix c1;

};

#endif