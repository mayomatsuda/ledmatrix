#ifndef WEATHERMODE_H
#define WEATHERMODE_H

#include <string>
#include "led-matrix.h"
#include "graphics.h"
#include "mode.h"
#include "api.h"

/** 
 * @brief Weather info mode
 * @details Displays the time, the temperature, and the weather at a specific longitude and latitude using
 * OpenWeatherMap's API.
 * @authors mmacd327
 */
class WeatherMode: public Mode {
    private:
       /**
        * @brief Gather and parse weather data
        * @details Uses the API to scan and parse weather data at a specific location.
        * @param lon The longitude
        * @param lat The latitude
        * @return A vector of weather info for interpretation by displayFunction
        */
        std::vector<std::string> parseWeatherData(float lon, float lat);
       /**
        * @brief Formats parsed data for display
        * @details Format function that takes parsed route data and puts it in a string that displayFunction can interpret.
        * @return Formatted string, returned to displayFunction
        */
        std::string formatData(float lon, float lat);
    public:
       /**
        * @brief Constructor for WeatherMode
        * @details Constructor. Unlike busmode, the constructor does not create the API because the API URL must be
        * generated with the lon/lat provided later.
        * @param mtx Reference to the matrix to display on
        */
        WeatherMode(rgb_matrix::RGBMatrix* mtx);
        ~WeatherMode();
       /**
        * @brief Displays weather info on matrix
        * @details Overridded display function that takes input parameters and displays relevant data.
        * @param text Options for display. Format is { longitude, latitude }
        */
        void displayFunction(std::vector<std::string> input);

};

#endif