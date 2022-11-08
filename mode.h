#ifndef MODE_H
#define MODE_H

#include <string>
#include "rpi-rgb-led-matrix/include/led-matrix.h"
#include "api.h"

class Mode {
    private:
        rgb_matrix::RGBMatrix* matrix;
    protected:
        Api* api;
    public:
        Mode(rgb_matrix::RGBMatrix* mtx);
        ~Mode();
        virtual void displayFunction();
        virtual std::string formatData();
};

#endif