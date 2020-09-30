#ifndef MYDRAWING_H
#define MYDRAWING_H

#include "drawbase.h" // forward reference
#include "image.h"    //Stores image
#include <fstream>    //Use fstream library to read in from file
#include "viewcontext.h"

class GraphicsContext;

class mydrawing : public DrawingBase
{
public:
    /*Default constructor(mydrawing md();) */
    mydrawing(GraphicsContext *gc);
        /* This will draw every image onto the screen.
		 * 
		 * Parameters:
		 * 	gc - Handles the screen pixels which to draw things on
		 */
    virtual void paint(GraphicsContext *gc, viewcontext *vc);
        /* This will detect when the mouse is clicked and run functions based on that. 
		 * 
		 * Parameters:
		 * 	gc - Handles the screen pixels which to draw things on
         *  button - Knows which button is clicked, right or left.
         *  x,y - Pixel coordinates of cursor on screen
		 */
    virtual void mouseButtonDown(GraphicsContext *gc, unsigned int button, int x, int y);
        /* This will detect when the mouse is released and run functions based on that. 
		 * 
		 * Parameters:
		 * 	gc - Handles the screen pixels which to draw things on
         *  button - Which button is pressed(Right or Left Click)
         *  x,y - Pixel coordinates of cursor on screen
		 */
    virtual void mouseButtonUp(GraphicsContext *gc, unsigned int button, int x, int y);
        /* This will detect when the mouse is moved and run functions based on that. 
		 * 
		 * Parameters:
		 * 	gc - Handles the screen pixels which to draw things on
         *  x,y - Pixel coordinates of cursor on screen
		 */
    virtual void mouseMove(GraphicsContext *gc, int x, int y);
        /* This will detect when a key is released and run a command based on
         * which key was released  
		 * 
		 * Parameters:
		 * 	gc - Handles the screen pixels which to draw things on
         *  keycode - Keycode of which button was pressed.
		 */
    void keyDown(GraphicsContext *gc, unsigned int keycode);
        /* This will detect when a key is pressed and run a command based on
         * which key was pressed  
		 * 
		 * Parameters:
		 * 	gc - Handles the screen pixels which to draw things on
         *  keycode - Keycode of which button was pressed.
		 */
    void keyUp(GraphicsContext *gc, unsigned int keycode);
    /* Destructor */
    ~mydrawing();

private:
    // We will only support one "remembered" line
    // In an actual implementation, we would also have one of our "image"
    // objects here to store all of our drawn shapes.
    int x0;
    int y0;
    int x1;
    int y1;
    int x2;
    int y2;
    bool dragging; // flag to know if we are dragging
    image im;      //Stores drawings with image object
    viewcontext vc; //Makes sure all shapes and lines are on the screen
    //Hold states for different shapes and colors
    enum shapeMode
    {
        LINE,
        TRIANGLE
    } draw;
    enum states
    {
        NONE,
        POINT1,
        POINT2,
        POINT3
    } state;
    enum colors
    {
        GREEN,
        CYAN,
        MAGENTA,
        RED
    } color;
};

#endif