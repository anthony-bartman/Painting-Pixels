#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>	 // for ostream
#include <stdexcept> // for runtime_error
#include <string>	 // used in exception
#include <vector> //Used to store the shape pointers in an array
#include <sstream> //Used for i string stream

#include "gcontext.h"
#include "shape.h"
#include "line.h"
#include "triangle.h"
#include "viewcontext.h"

using namespace std;

/**
 * This class is will be the class the controls and stores
 * all of the shapes in an image.
 */    
class image
{
	public:
		/*********************************************************
		 * Construction / Destruction
		 *********************************************************/
        /*Default constructor(image i();) */
        image();
		/* Copy Constructor(image i = i1;)
		 * 
		 * Parameters:
		 * 	rhs - image being copied from that has already been created, i1 above
		 */     
		image(const image &rhs);
        /* Destructor */
		~image();

		/*********************************************************
		 * Drawing operations
		 *********************************************************/
		/* This will iterate through all shapes in image and draw it
		 * 
		 * Parameters:
		 * 	gc - Handles the screen pixels which to draw the line on
		 */			
		void draw(GraphicsContext *gc,viewcontext *vc);
		/* This will add the shapes to the list of shapes for the image
		 * 
		 * Parameters:
		 *  *shape - shape pointer being added to the list of shapes in image
		 */	
		void add(shape *shape, viewcontext *vc);
		/* This will use erase all shapes off of the screen and clear the list
		 * of shapes from the list.
		 */			
		void erase();

		/*********************************************************
		 * Utility operations
		 *********************************************************/
		/* This will output all of the shape's properties to a file
	  	 * in a specific format.
		 * 
		 * Parameters:
		 * 	os - Output stream to a file or console
		 */          
		ostream &out(ostream &os) const;

        /* This will read in the shape attributes from a text file and
		 * set them to a new shape object on the heap and store them
		 * in a list
		 * 
		 * Parameters:
		 * 	is - Input stream holding the input text file
		 */	
		istream &in(istream &is, viewcontext *vc);

		/*********************************************************
		 * Assignement Operators
		 *********************************************************/
		/* This method allows image's contents to be equal to each other.
		 * Copies rhs contents into left side image.
		 * 
		 * Parameters:
		 * 	rhs =  right hand side of equals operator (image = rhs;)
		 */        
		image &operator=(const image &rhs);
	private:
		//Holds list of integer shape pointers
		vector<shape*> shapeList;
};

#endif