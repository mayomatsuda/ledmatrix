#ifndef BUSMODE_H
#define BUSMODE_H

#include <string>
#include "led-matrix.h"
#include "graphics.h"
#include "mode.h"
#include "api.h"

/** 
 * @brief Bus schedule mode
 * @details Displays the next scheduled times for up to 2 bus routes at a specific stop by accessing LTC's public API.
 * @authors mmacd327
 */
class BusMode: public Mode {
    private:
       /**
        * @brief Gather and parse bus route data
        * @details Uses the API to scan and parse bus time data for a specific stop on a specific route.
        * @param route The bus route
        * @param stop The bus stop
        * @return A vector of the times the bus is scheduled to come
        */
        std::vector<std::string> parseRouteData(std::string route, std::string stop);
       /**
        * @brief Formats parsed data for display
        * @details Format function that takes parsed route data and puts it in a string that displayFunction can interpret.
        * @param route The bus route
        * @param stop The bus stop
        * @return Formatted string, returned to displayFunction
        */
        std::string formatData(std::string route, std::string stop);
    public:
       /**
        * @brief Constructor for BusMode, handling Api creation
        * @details Constructor that handles creating the Api class based on the unique URL for the bus times.
        * @param mtx Reference to the matrix to display on
        */
        BusMode(rgb_matrix::RGBMatrix* mtx);
        ~BusMode();
       /**
        * @brief Displays bus times on matrix
        * @details Overridded display function that takes input parameters and displays relevant bus data.
        * @param input Options for display. Format is { stop, route1, route2 }
        */
        void displayFunction(std::vector<std::string> input);

};

#endif