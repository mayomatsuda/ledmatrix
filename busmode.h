#ifndef BUSMODE_H
#define BUSMODE_H

#include <string>
#include "rpi-rgb-led-matrix/include/led-matrix.h"
#include "mode.h"
#include "api.h"

class BusMode: public Mode {
    private:
        std::vector<std::string> parseRouteData(std::string route, std::string stop);
        bool isDaylightSavings();
    public:
        BusMode(rgb_matrix::RGBMatrix* mtx);
        ~BusMode();
        void displayFunction();
        std::string formatData();
};

#endif