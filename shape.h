#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>	 // for std::ostream
#include <stdexcept> // for std::runtime_error
#include <sstream> //Used for string stream
#include <string>	 // used in exception
#include <unistd.h>  //Sleep

#include "gcontext.h" //Used to draw things on screen
#include "viewcontext.h"

using namespace std;
/**
 * This class is intended to be the abstract base class that will
 * have methods that all of it's children will use
 */    
class shape
{
	public:
		/*********************************************************
		 * Construction / Destruction
		 *********************************************************/
        /*Default constructor(shape s();) */
        shape();
		/* Parameterized Constructor(shape s(red);)
		 * 
		 * Parameters:
		 *  color - color of shape 
		 */        
		shape(unsigned int color);
		/* Copy Constructor(shape s = s1;)
		 * 
		 * Parameters:
		 * 	rhs - shape being copied from that has already been created, t1 above
		 */        
		shape(const shape &rhs);
        /* Destructor */
		virtual ~shape();

		/*Holds the color of the shape (Black Initially) */
		unsigned int color;
		/*********************************************************
		 * Drawing operations
		 *********************************************************/
		/* This is a pure virtual function that will be implemented individually
		 * depending on the child that uses it.
		 * 
		 * Parameters:
		 * 	gc - Handles the screen pixels which to draw the shapes on
		 */        
		virtual void draw(GraphicsContext *gc,viewcontext *vc)=0;

		/* This will erase all shapes off of the screen
		 * (Not Implemented Yet)
		 */			
		virtual void erase()=0;

		/* This will use clone a shape to the heap when the image
		 * class wants to add a stack-variable shape to the image.
		 * This is a pure virtual function that must be called from child
		 */	        
		virtual shape* clone()=0;

		/* This will change the device coordinates of the shape pointer
		 * into model coordinates to be stored in an image.
		 */  
		virtual void deviceToModel(viewcontext *vc)=0;
		/*********************************************************
		 * Utility operations
		 *********************************************************/
		/* This will output the color of the shape that called it to a file	
	  	 * in a specific format.
		 * 
		 * Parameters:
		 * 	os - Output stream to a file or console
		 */           
		virtual ostream &out(ostream &os) const;

		/* This will read in the shapes color attribute from a text file and
		 * set them to the new shape object that called it on the heap
		 * 
		 * Parameters:
		 * 	is - Input stream holding the input text file
		 */			
		virtual istream &in(istream &is);
		
	protected:
        /*********************************************************
		 * Assignement Operators
		 *********************************************************/
		/* This method allows shapes contents to be equal to each other.
		 * Copies rhs contents into left side shape. This method is protected
		 * so that a user cannot copy a shape to shape because this would
		 * invoke a memory leak.
		 * 
		 * Parameters:
		 * 	rhs =  right hand side of equals operator (s = rhs;)
		 */
        shape &operator=(const shape &rhs);		
};

#endif