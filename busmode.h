#ifndef BUSMODE_H
#define BUSMODE_H

#include <string>
#include "rpi-rgb-led-matrix/include/led-matrix.h"
#include "mode.h"
#include "api.h"

class BusMode: public Mode {
    public:
        void displayFunction();
        std::string formatData();
};

#endif