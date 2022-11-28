#ifndef MODE_H
#define MODE_H

#include <string>
#include "led-matrix.h"
#include "api.h"
/** 
 * @brief Abstract mode class
 * @details Abstract class to be inherited by concrete modes.
 * @authors mmacd327
 */
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
        * @brief Mode constructor with pointer to matrix
        * @details Constructor that defines reference to matrix to display information on.
        * @param mtx Reference to the matrix to display on
        */
        Mode(rgb_matrix::RGBMatrix* mtx);
        virtual ~Mode();
       /**
        * @brief Displays content on matrix
        * @details Virtual display function to be overriden by specific modes. Each mode will have different
        * specifications for the formatting of the input; for example, bus mode accepts { route, stop1, stop2}.
        * @param input Options for display
        */
        virtual void displayFunction(std::vector<std::string> input) = 0;
};

#endif