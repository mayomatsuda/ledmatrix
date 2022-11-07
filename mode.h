#ifndef MODE_H
#define MODE_H

#include <string>
#include "rpi-rgb-led-matrix/include/led-matrix.h"
#include "api.h"

class Mode {
    private:
        Api* api;
    public:
        Mode(std::string url, rgb_matrix::RGBMatrix matrix);
        ~Mode();
        virtual void displayFunction();
        virtual std::string formatData();
};

#endif