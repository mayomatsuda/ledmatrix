#ifndef WEATHERMODE_H
#define WEATHERMODE_H

#include <string>
#include "led-matrix.h"
#include "graphics.h"
#include "mode.h"
#include "api.h"

class WeatherMode: public Mode {
    private:
       /**
        * Uses the API to scan and parse weather data at a specific location
        * @param lon The longitude
        * @param lat The latitude
        * @return A vector of the times the bus is scheduled to come
        */
        std::vector<std::string> parseWeatherData(float lon, float lat);
       /**
        * Format function that takes parsed route data and puts it in a string that displayFunction can interpret
        * @return Formatted string, returned to displayFunction
        */
        std::string formatData(float lon, float lat);
    public:
       /**
        * Constructor. Unlike busmode, the constructor does not create the API because the API URL must be generated with the lon/lat provided later.
        * @param mtx Reference to the matrix to display on
        */
        WeatherMode(rgb_matrix::RGBMatrix* mtx);
        ~WeatherMode();
       /**
        * Overridded display function that takes input parameters and displays relevant data
        * @param text Text to display, formatted
        */
        void displayFunction(std::vector<std::string> input);

};

#endif