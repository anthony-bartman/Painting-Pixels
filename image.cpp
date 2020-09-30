/**
 * Anthony Bartman
 * Dr. Varnell
 * Computer Graphics:  CS 3210 021
 * 05/03/2020
 * 
 * Desc:
 *   This file handles all of the image method functions.
 */

#include "image.h"

/*********************************************************
* Construction / Destruction
*********************************************************/
//Constructor (image s;)
image::image()
{
}
//Copy Constructor (image s = s1;)
image::image(const image &rhs)
{
    //Make the new image have different sized memory on heap based on the rhs image size
    for (int i = 0; i < this->shapeList.size(); i++)
    {
        this->shapeList.push_back(rhs.shapeList[i]->clone());
    }
}
//Destructor(Iterate through to delete all shapes)
image::~image()
{
    //Erases all of the shapes from the image
    erase();
}

/*********************************************************
* Assignement Operators
*********************************************************/
//Equals Operator (s1 = s2;)
image &image::operator=(const image &rhs)
{
    //Checks if the image is not equalling itself; for efficiency purposes
    if (this != &rhs)
    {
        //Free the old allocated heap memory
        this->erase();

        //Make the new image have different sized memory on heap based on the rhs image size
        for (int i = 0; i < this->shapeList.size(); i++)
        {
            this->shapeList.push_back(rhs.shapeList[i]->clone());
        }
    }
    //Return this new image
    return *this;
}

/*********************************************************
* Drawing operations
*********************************************************/
//Draws the object based on the type of image it is. WILL GO TO CHILD CLASS ALWAYS
void image::draw(GraphicsContext *gc,viewcontext *vc)
{
    //Iterate through list of shapes draw methods
    for (int i = 0; i != shapeList.size(); i++)
    {
        shapeList[i]->draw(gc,vc);
    }
}

//Adds a shape to the image
void image::add(shape *cloneShape, viewcontext *vc)
{
    //Convert shape's Coordinates to modelCoordinates
    cloneShape->deviceToModel(vc);
    //Pushes every new shape to the 'back' of the list
    this->shapeList.push_back(cloneShape->clone());
}

//Clears a specific image off of the screen. WILL ALWAYS GO TO CHILD CLASS
void image::erase()
{
    //Free the allocated heap memory
    for (int i = 0; i < this->shapeList.size(); i++)
    {
        delete this->shapeList[i];
    }
    //Clear the shapeList data
    this->shapeList.clear();
}

/*********************************************************
* Utility operations
*********************************************************/
//Dumps image properties to the output stream
ostream &image::out(ostream &os) const
{
    //Go Through Each shape
    os << "Image" << endl;
    for (int i = 0; i < shapeList.size(); i++)
    {
        shapeList[i]->out(os);
    }
    os << "end_image" << endl;
}

//Read image properties from a text file
istream &image::in(istream &is,viewcontext *vc)
{
    string word;
    is >> word;
    if (word.compare("Image") == 0)
    {
        while (!is.eof())
        {
            is >> word;
            //Determine what shape it is
            if (word.compare("L:") == 0)
            {
                shape* l = new line();
                l->in(is);
                //Pushes every new shape to the 'back' of the list
                this->shapeList.push_back(l->clone());            }
            else if (word.compare("T:") == 0)
            {
                shape *t = new triangle();
                t->in(is);
                //Pushes every new shape to the 'back' of the list
                this->shapeList.push_back(t->clone());
            }
        }
    }
}
