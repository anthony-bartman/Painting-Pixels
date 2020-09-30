#ifndef VIEWCONTEXT_H
#define VIEWCONTEXT_H

#include "matrix.h"
#include "gcontext.h"
#include <cmath>

using namespace std;

/**
 * This class is intended to determine where and how to draw
 * lines based on the context window
 */  
class viewcontext{

    public:
        /*********************************************************
		 * Construction / Destruction
		 *********************************************************/
        /*Default constructor(viewcontext vc();) */
        viewcontext();

        /* Parameterized constructor 
         *
         * Parameters:
		 * 	gc - GraphicsContext used to get height and width of window
         */
        viewcontext(GraphicsContext *gc);

        /* Destructor */
		~viewcontext();

        /*********************************************************
         * Transformation operations
         *********************************************************/
        /* Rotate
		 * 
		 * Parameters:
		 * 	degrees - This rotates the shape on focused on the center of page
		 */
        void rotate(int degrees);

        /* Scale
		 * 
		 * Parameters:
		 * 	scalar - Scales the image by a factor in the middle of the page
		 */
        void scale(double scalar);

        //Matrix that will change modelCoordinates to deviceCoordinates
        matrix modelToDevice;
        //Matrix that will change deviceCoordinates to modelCoordinates
        matrix deviceToModel;
};
#endif 