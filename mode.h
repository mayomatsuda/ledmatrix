#ifndef MODE_H
#define MODE_H

#include <string>
#include "led-matrix.h"
#include "api.h"

class Mode {
    protected:
       /** 
        * Protected reference to the matrix to be accessed by specific modes
        */
        rgb_matrix::RGBMatrix* matrix;
       /** 
        * Protected reference to the Api, initialized by specific modes
        */
        Api* api;
    public:
       /**
        * Constructor that defines reference to matrix to display information on
        * @param mtx Reference to the matrix to display on
        */
        Mode(rgb_matrix::RGBMatrix* mtx);
        virtual ~Mode();
       /**
        * Virtual display function to be overriden by specific modes
        * @param text Text to display, formatted
        */
        virtual void displayFunction(std::vector<std::string> input) = 0;
};

#endif