#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "matrix.h" //Stores Coordinates in a 4x1 Matrix
#include "shape.h" //Abstract Base Class
#include "gcontext.h" //Graphics Context to draw pixels
#include "viewcontext.h"

using namespace std;

/**
 * This class will draw triangles and handle how they are
 * stored in memory.
 * 
 * Inherits from a Shape Class methods and a 'color' attribute
 */    
class triangle : public shape
{
	public:
		/*********************************************************
		 * Construction / Destruction
		 *********************************************************/
        /*Default constructor(triangle t();) */
        triangle();
        /* Parameterized Constructor(triangle t(x,y,x,y,x,y,red);)
		 * 
		 * Parameters:
		 * 	x0, y0 - Vertex 1
		 *  x1, y1 - Vertex 2
		 *  x2, y2 - Vertex 3
		 *  color - color of shape 
		 */
        triangle(double x0,double y0,double x1, double y1,double x2,double y2, unsigned int color);
        /* Copy Constructor(triangle t = t1;)
		 * 
		 * Parameters:
		 * 	rhs - triangle being copied from that has already been created, t1 above
		 */
        triangle(const triangle &rhs);
        /* Destructor */
		~triangle();

		/*********************************************************
		 * Drawing operations
		 *********************************************************/
        /* This will use a Bresingham line drawing algorithm to draw 3 lines
		 * in order to make a triangle.
		 * 
		 * Parameters:
		 * 	gc - Handles the screen pixels which to draw the triangle on
		 */
		void draw(GraphicsContext *gc,viewcontext *vc);
		/* This will erase all triangles off of the screen
		 * (Not Implemented Yet)
		 */		
		void erase();
		
		/* This will use clone a triangle to the heap when the image
		 * class wants to add a stack-variable triangle to the image.
		 */	
		shape* clone();

		/** This method converts the deviceCoords to the Model Coordinates
		 *  for the triangle.
		 */ 
		void deviceToModel(viewcontext *vc);
		/*********************************************************
		 * Utility operations
		 *********************************************************/
		/* This will output all of the triangle's properties to a file
	  	 * in a specific format.
		 * 
		 * Parameters:
		 * 	os - Output stream to a file or console
		 */        
		ostream &out(ostream &os) const;

		/* This will read in the triangle attributes from a text file and
		 * set them to a new triangle object on the heap
		 * 
		 * Parameters:
		 * 	is - Input stream holding the input text file
		 */		
		istream &in(istream &is);

        /*********************************************************
		 * Assignement Operators
		 *********************************************************/
	    /* This method allows triangles contents to be equal to each other.
		 * Copies rhs contents into left side triangle.
		 * 
		 * Parameters:
		 * 	rhs =  right hand side of equals operator (tri = rhs;)
		 */
        triangle &operator=(const triangle &rhs);

	private:		
        //These hold the 3 different coordinates for the 3 vertices of the triangle
        matrix c0;
        matrix c1;
        matrix c2;
};

#endif