#include "weathermode.h"
#include "led-matrix.h"
#include "graphics.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <unistd.h>
#include <algorithm>
#include <nlohmann/json.hpp>
using namespace std;
using namespace rgb_matrix;
using json = nlohmann::json;

WeatherMode::WeatherMode(rgb_matrix::RGBMatrix* mtx) : Mode(mtx) {

}

WeatherMode::~WeatherMode() {

}

void WeatherMode::displayFunction(vector<string> input) {
    // Format of input for BusMode's display function should be {stop, route1, route2}
    string lon = input[0];
    string lat = input[1];
    string API_KEY = "9f1b0c1d0f611f5ffb437e3ebbeb98c5";
    
    string URL = "https://api.openweathermap.org/data/2.5/weather?lat=" + lat + "&lon=" + lon + "&appid=" + API_KEY + "&units=metric";
    api = new Api(URL);

    string data = formatData(stof(lon), stof(lat));
}

vector<string> WeatherMode::parseWeatherData(float lon, float lat) {
    string tx = api->getData();
    json js = json::parse(tx);

    cout << js["weather"][0] << endl;
    // json weatherjs = json::parse(weather[0]);

    // cout << weatherjs["description"] << endl;
    // string icon = js["weather"][0]["icon"];
    // int temp = (int) round(stof(js["weather"][0]["feels_like"]));

    return {"42.984268", "-81.247528"};
}

string WeatherMode::formatData(float lon, float lat) {
    parseWeatherData(lon, lat);
    return "L";
}