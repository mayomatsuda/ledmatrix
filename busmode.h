#ifndef BUSMODE_H
#define BUSMODE_H

#include <string>
#include "led-matrix.h"
#include "graphics.h"
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
       /**
        * Format function that takes parsed route data and puts it in a string that displayFunction can interpret
        * @return Formatted string, returned to displayFunction
        */
        std::string formatData(std::string route, std::string stop);
    public:
       /**
        * Constructor that handles creating the Api class based on the unique URL for the bus times
        * @param mtx Reference to the matrix to display on
        */
        BusMode(rgb_matrix::RGBMatrix* mtx);
        ~BusMode();
       /**
        * Overridded display function that takes input parameters and displays relevant data
        * @param text Text to display, formatted
        */
        void displayFunction(std::vector<std::string> input);

};

#endif