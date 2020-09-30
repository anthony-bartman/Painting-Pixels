/**
 * Anthony Bartman
 * Dr. Varnell
 * Computer Graphics:  CS 3210 021
 * 05/17/2020
 * 
 * Desc:
 *   This file handles all of the viewcontext method functions.
 */

#include "viewcontext.h"

//Constructor
viewcontext::viewcontext(){}

//Parameterized Constructor
viewcontext::viewcontext(GraphicsContext *gc){
    //Initialize
    modelToDevice = matrix::identity(4);
    deviceToModel = matrix::identity(4);

    //Flip matrix
    matrix flip = matrix::identity(4);
    flip[1][1] = -1;
    //Translate matrix
    matrix translate = matrix::identity(4);
    translate[0][3] = gc->getWindowWidth() / 2;
    translate[1][3] = gc->getWindowHeight() / 2;

    //Flip y, translate dX/2 and dY/2
    modelToDevice = flip * translate;
    modelToDevice[1][3] = modelToDevice[1][3] * -1;

    translate[0][3] = translate[0][3] * -1;

    //Translate -dX/2 and dY/2, Flip y
    deviceToModel = translate * flip;
}

//Destructor
viewcontext::~viewcontext(){}

//Will only rotate 60 degrees each time... maybe
void viewcontext::rotate(int degrees){
    matrix rotate = matrix::identity(4);
    rotate[0][0] = cos(degrees);
    rotate[0][1] = sin(degrees);
    rotate[1][0] = -sin(degrees);
    rotate[1][1] = cos(degrees);
    this->modelToDevice = this->modelToDevice * rotate;
    rotate[0][0] = cos(-degrees);
    rotate[0][1] = sin(-degrees);
    rotate[1][0] = -sin(-degrees);
    rotate[1][1] = cos(-degrees);
    this->deviceToModel = rotate * this->deviceToModel;
}

//Scale the image by a factor of 1.25 or 0.75
void viewcontext::scale(double scalar){
    matrix scale = matrix::identity(4);
    scale[0][0] = scalar;
    scale[1][1] = scalar;
    this->modelToDevice = this->modelToDevice * scale;
    scale[0][0] = scalar - 0.5;
    scale[1][1] = scalar - 0.5;
    this->deviceToModel = scale * this->deviceToModel;
}

