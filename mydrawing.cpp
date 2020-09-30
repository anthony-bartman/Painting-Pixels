/**
 * Anthony Bartman
 * Dr. Varnell
 * Computer Graphics:  CS 3210 021
 * 05/010/2020
 * 
 * Desc:
 *   This file what happens when user uses keybinds to execute event based programming. 
 */

#include "mydrawing.h"
#include "gcontext.h"

void helpUser();

// Constructor
mydrawing::mydrawing(GraphicsContext *gc)
{
    //Variables
    dragging = false;
    x0 = x1 = y0 = y1 = 0;
    draw = LINE;
    color = GREEN;
    state = NONE;
    vc = viewcontext(gc);
    //Tells user how to use the program
    helpUser();
}

//Destructor
mydrawing::~mydrawing() {}

void mydrawing::paint(GraphicsContext *gc, viewcontext *vc)
{
    //When image is exposed, draw image
    this->im.draw(gc, vc);
}

void mydrawing::mouseButtonDown(GraphicsContext *gc, unsigned int button, int x, int y)
{
    // mouse button pushed down
    // -clear context
    // -set origin of new line
    // -set XOR mode for rubber-banding
    // -draw new line in XOR mode.  Note, at this point, the line is
    //  degenerate (0 length), but need to do it for consistency

    //Draw shape based on mode
    if (draw == LINE)
    {
        x0 = x1 = x;
        y0 = y1 = y;
        gc->setMode(GraphicsContext::MODE_XOR);
        gc->drawLine(x0, y0, x1, y1);
        //Update flags
        dragging = true;
    }
    else if (draw == TRIANGLE)
    {
        if (state == NONE)
        {
            x0 = x1 = x2 = x;
            y0 = y1 = y2 = y;
            gc->setMode(GraphicsContext::MODE_XOR);
            gc->drawLine(x0, y0, x1, y1);
            dragging = true;
            state = POINT1;
        }
    }
}

void mydrawing::mouseButtonUp(GraphicsContext *gc, unsigned int button, int x, int y)
{
    if (dragging)
    {
        if (draw == LINE)
        {                                 // undraw old line
            gc->drawLine(x0, y0, x1, y1); // just in x and y here do not match x and y of last mouse move
            x1 = x;
            y1 = y;
            // go back to COPY mode
            gc->setMode(GraphicsContext::MODE_NORMAL);
            // new line drawn in copy mode
            gc->drawLine(x0, y0, x1, y1);
            // clear flag
            dragging = false;

            //Add Line to image based on color
            if (color == GREEN)
            {
                line l(x0, y0, x1, y1, GraphicsContext::GREEN);
                this->im.add(&l,&vc);
            }
            else if (color == CYAN)
            {
                line l(x0, y0, x1, y1, GraphicsContext::CYAN);
                this->im.add(&l,&vc);
            }
            else if (color == MAGENTA)
            {
                line l(x0, y0, x1, y1, GraphicsContext::MAGENTA);
                this->im.add(&l,&vc);
            }
            else if (color == RED)
            {
                line l(x0, y0, x1, y1, GraphicsContext::RED);
                this->im.add(&l,&vc);
            }
        }
        else if (draw == TRIANGLE)
        {
            if (state == POINT1)
            {
                gc->drawLine(x0, y0, x1, y1); // just in x and y here do not match x and y of last mouse move
                x1 = x;
                y1 = y;
                gc->drawLine(x0, y0, x1, y1);
                //Set state to draw second point
                state = POINT2;
            }
            else if (state == POINT2)
            {
                gc->drawLine(x1, y1, x2, y2); // just in x and y here do not match x and y of last mouse move
                gc->drawLine(x0, y0, x2, y2);
                gc->drawLine(x0, y0, x1, y1);
                x2 = x;
                y2 = y;
                // go back to COPY mode
                gc->setMode(GraphicsContext::MODE_NORMAL);
                // new line drawn in copy mode
                gc->drawLine(x1, y1, x2, y2);
                gc->drawLine(x0, y0, x2, y2);
                gc->drawLine(x0, y0, x1, y1);
                // clear flag
                dragging = false;
                state = NONE;

                //Add Triangle to image(Save it by current color)
                if (color == GREEN)
                {
                    triangle t(x0, y0, x1, y1, x2, y2, GraphicsContext::GREEN);
                    this->im.add(&t,&vc);
                }
                else if (color == CYAN)
                {
                    triangle t(x0, y0, x1, y1, x2, y2, GraphicsContext::CYAN);
                    this->im.add(&t,&vc);
                }
                else if (color == MAGENTA)
                {
                    triangle t(x0, y0, x1, y1, x2, y2, GraphicsContext::MAGENTA);
                    this->im.add(&t,&vc);
                }
                else if (color == RED)
                {
                    triangle t(x0, y0, x1, y1, x2, y2, GraphicsContext::RED);
                    this->im.add(&t,&vc);
                }
            }
        }
    }
}

void mydrawing::mouseMove(GraphicsContext *gc, int x, int y)
{
    if (dragging)
    {
        if (draw == LINE)
        {
            // mouse moved -"undraw" old line, then re-draw in new position
            //will already be in XOR mode if dragging
            // old line undrawn
            gc->drawLine(x0, y0, x1, y1);
            // update
            x1 = x;
            y1 = y;
            // new line drawn
            gc->drawLine(x0, y0, x1, y1);
        }
        else if (draw == TRIANGLE)
        {
            if (state == POINT1)
            {
                // mouse moved -"undraw" old line, then re-draw in new position
                //will already be in XOR mode if dragging
                // old line undrawn
                gc->drawLine(x0, y0, x1, y1);
                // update
                x1 = x;
                y1 = y;
                // new line drawn
                gc->drawLine(x0, y0, x1, y1);
            }
            else if (state == POINT2)
            {
                // mouse moved -"undraw" old line, then re-draw in new position
                //will already be in XOR mode if dragging
                gc->drawLine(x0, y0, x2, y2);
                gc->drawLine(x1, y1, x2, y2);

                // update
                x2 = x;
                y2 = y;
                // new line drawn
                gc->drawLine(x0, y0, x2, y2);
                gc->drawLine(x1, y1, x2, y2);
                gc->drawLine(x0, y0, x1, y1);
            }
        }
    }
}

void mydrawing::keyDown(GraphicsContext *gc, unsigned int keycode)
{
    if (keycode == 49)
    { // '1' //Changes what shape to draw
        if (draw != LINE)
        {
            cout << "=> Drawing LINE <=" << endl;
            draw = LINE;
        }
    }
    else if (keycode == 50)
    { // '2'
        if (draw != TRIANGLE)
        {
            cout << "=> Drawing TRIANGLE <=" << endl;
            draw = TRIANGLE;
        }
    }
}

void mydrawing::keyUp(GraphicsContext *gc, unsigned int keycode)
{
    //45 is '-' key, 61 is '+', 122 is 'z' for rotate by 90 deg
    if (keycode == 104)
    { // 'h'
        helpUser();
    }
    else if (keycode == 114)
    { // 'r'
        this->im.erase();
        gc->clear();
        cout << "=> Image Cleared and Deleted <=" << endl;
    }
    else if (keycode == 115)
    { // 's'
        //Grabs input from user
        string filename;
        cout << "Type in a name for a file to save: " << endl;
        cin >> filename;
        cout << "Saving " << filename << "..." << endl;

        //Output drawing to a txt file
        filebuf fb;
        fb.open(filename, ios::out);
        ostream os(&fb);
        this->im.out(os);
    }
    else if (keycode == 111)
    { // 'o'
        //Grabs Output file name from user
        string filename;
        cout << "What file would you like to load?" << endl;
        cin >> filename;
        cout << "Opening " << filename << "..." << endl;

        //Populate Image
        ifstream filein(filename);
        this->im.in(filein,&vc);
        filein.close();

        //Draw Images
        this->im.draw(gc, &vc);
    }
    else if (keycode == 99)
    { //If u hit 'c' it goes through all colors
        if (color == GREEN)
        {
            gc->setColor(GraphicsContext::CYAN);
            color = CYAN;
        }
        else if (color == CYAN)
        {
            gc->setColor(GraphicsContext::MAGENTA);
            color = MAGENTA;
        }
        else if (color == MAGENTA)
        {
            gc->setColor(GraphicsContext::RED);
            color = RED;
        }
        else if (color == RED)
        {
            gc->setColor(GraphicsContext::GREEN);
            color = GREEN;
        }
        cout << "=> Color has been changed <=" << endl;
    }
    else if (keycode == 122)
    {//If you hit 'z' key, it will rotate by 60
        this->vc.rotate(60);
        //Erase old image and clear screen
        gc->clear();
        //Redraw new image with transformation
        this->im.draw(gc,&vc);
        cout << "=> Image has been rotated clockwise by 60 Degrees <=" << endl;
    }
    else if (keycode == 61)
    { // Scales image by a factor of 1.25; '+' key
        this->vc.scale(1.25);
        //Clear screen
        gc->clear();
        //Redraw new image with transformation
        this->im.draw(gc,&vc);
        cout << "=> Image has been scaled up by a factor of 1.25 <=" << endl;
    } else if(keycode == 45)
    { //Scales image by a factor of 0.75; '-' key
        this->vc.scale(0.75);
        //Clear screen
        gc->clear();
        //Redraw new image with transformation
        this->im.draw(gc,&vc);
        cout << "=> Image has been scaled down by a factor of 0.75 <=" << endl;
    }
}

//Helper Method
void helpUser()
{
    cout << "-------------------------------------" << endl;
    cout << "  <<    Program Instructions    >>  " << endl
         << endl;
    cout << " 'h' :  Pulls up help menu" << endl;
    cout << " 'r' :  Resets the current image" << endl;
    cout << " 'o' :  Opens up an image file" << endl;
    cout << " 's' :  Saves the image to a file" << endl;
    cout << " 'c' :  Changes the color to 3 unique options" << endl;
    cout << " '1' :  Sets Draw Line Mode" << endl;
    cout << " '2' :  Sets Draw Triangle Mode" << endl;
    cout << " 'z' :  Rotates image by 90 Degrees" << endl;
    cout << " '+' :  Scale Image to be larger; Zoom in" << endl;
    cout << " '-' :  Scale Image to be smaller; Zoom out" << endl;
    cout << "-------------------------------------" << endl;
}