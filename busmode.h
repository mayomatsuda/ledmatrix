#ifndef BUSMODE_H
#define BUSMODE_H

#include <string>
#include "rpi-rgb-led-matrix/include/led-matrix.h"
#include "mode.h"
#include "api.h"

class BusMode: public Mode {
    private:
       /**
        * Uses the API to scan and parse bus time data for a specific stop on a specific route
        * @param route The bus route
        * @param stop The bus stop
        * @return A vector of the times the bus is scheduled to come
        */
        std::vector<std::string> parseRouteData(std::string route, std::string stop);
       /**
        * Checks if the current time is daylight savings
        * @return True if daylight savings, false otherwise
        */
        bool isDaylightSavings();
    public:
       /**
        * Constructor that handles creating the Api class based on the unique URL for the bus times
        * @param mtx Reference to the matrix to display on
        */
        BusMode(rgb_matrix::RGBMatrix* mtx);
        ~BusMode();
       /**
        * Overridded display function that takes formatted data and displays bus time info on matrix
        * @param text Text to display, formatted
        */
        void displayFunction(std::string text);
       /**
        * Overridded format function that takes parsed route data and puts it in a string that displayFunction can interpret
        * @return Formatted string, interpretable by displayFunction
        */
        std::string formatData();
};

#endif