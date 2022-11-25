#include "busmode.h"
#include "led-matrix.h"
#include "graphics.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <unistd.h>
#include <algorithm>
using namespace std;
using namespace rgb_matrix;

BusMode::BusMode(rgb_matrix::RGBMatrix* mtx) : Mode(mtx) {
    string URL = "http://gtfs.ltconline.ca/TripUpdate/TripUpdates.json";
    api = new Api(URL);
}

BusMode::~BusMode() {

}

void BusMode::displayFunction(vector<string> input) {
    // Format of input for BusMode's display function should be {stop, route1, route2}
    string stop = input[0];
    string route1 = input[1];
    string route2 = input[2];

    string route1data = formatData(route1, stop);
    string route2data = formatData(route2, stop);

    vector<string> route1times;
    vector<string> route2times;
    string tmp;
    stringstream r1ss(route1data);
    stringstream r2ss(route2data);

    while(getline(r1ss, tmp, ' ')){
        route1times.push_back(tmp);
    }
    while(getline(r2ss, tmp, ' ')){
        route2times.push_back(tmp);
    }

    FrameCanvas *canvas = matrix->CreateFrameCanvas();
    Font *font = new Font();
    font->LoadFont("./rpi-rgb-led-matrix/fonts/7x13.bdf");
    Color colorOne = Color(255, 128, 0);
    Color colorTwo = Color(255, 255, 255);

    int counter = 0;

    while (true) {
        if (counter == 12) {
            route1data = formatData(route1, stop);
            route2data = formatData(route2, stop);

            route1times = {};
            route2times = {};

            stringstream r1ss(route1data);
            stringstream r2ss(route2data);

            while(getline(r1ss, tmp, ' ')){
                route1times.push_back(tmp);
            }
            while(getline(r2ss, tmp, ' ')){
                route2times.push_back(tmp);
            }
            counter = 0;
        }
        counter += 1;
        canvas->Clear();

        const int LEFT_POS = 1;
        const int RIGHT_POS = 29;
        const int TOP_POS = 13;
        const int BOTTOM_POS = 27;

        DrawText(canvas, *font, LEFT_POS, TOP_POS, colorOne, (route1 + ": ").c_str());
        if (route1times.size() > 0) {
            DrawText(canvas, *font, RIGHT_POS, TOP_POS, colorTwo, route1times[counter % route1times.size()].c_str());
        }
        DrawText(canvas, *font, LEFT_POS, BOTTOM_POS, colorOne, (route2 + ": ").c_str());
        if (route2times.size() > 0) {
            DrawText(canvas, *font, RIGHT_POS, BOTTOM_POS, colorTwo, route2times[counter % route2times.size()].c_str());
        }
        canvas = matrix->SwapOnVSync(canvas);
        sleep(5);
    }
}

vector<string> BusMode::parseRouteData(string route, string stop) {
    // Get data from the Api
    // See TripUpdates.json for an example of what the data being processed here will look like

    string tx = api->getData();

    // First occurence of desired route, indicated by '"route_id":"<route>"' in the data
    int ind1_low = tx.find("route_id\":\"" + route);
    // TODO: ensure -1 is result of failed find in C++; if not, adjust 
    if (ind1_low == -1) {
        ind1_low = tx.find("route_id\": \"" + route);
    }

    // Next occurence of desired route
    int ind_between = tx.find("route_id\":\"", ind1_low + 1);

    // Third occurence of desired route
    int ind1_high = tx.find("route_id\":\"" + route, ind1_low + 1);
    // TODO: ensure -1 is result of failed find in C++; if not, adjust
    if (ind1_high == -1) {
        ind1_high = tx.find("route_id\": \"" + route, ind1_low + 1);
    }
    vector<string> times;

    // TODO: choose better loop condition than true
    while (true) {
        // This will eventually happen, terminating the loop
        if (ind1_low == -1) {
            // Sort times from soonest to latest and return
            sort(times.begin(), times.end());
            return times;
        }

        // Ensure instance of the stop exists on the route
        int here;
        if (ind1_high > ind1_low) {
            here = tx.find(tx.substr(ind1_low, ind1_high - ind1_low));
        }
        else
            here = -1;

        if (here != -1) {
            // Find occurence of desired stop, starting at ind1_low represented by '"stop_id":"<stop"'
            int ind2 = tx.find("stop_id\":\"" + stop, ind1_low);
            if (ind2 == -1) {
                ind2 = tx.find("stop_id\": \"" + stop, ind1_low);
            }

            if (ind_between > ind2) {
                // Find occurence of time at most 50 characters before stop
                int ind3 = tx.find("time", ind2 - 50);
                if (ind3 != -1) {
                    int timeunix = stoi(tx.substr(ind3+6,ind3+16));
                    time_t tmp = timeunix;
                    tm* t = gmtime(&tmp);
                    int hour = t->tm_hour;
                    string hourStr;
                    if (isDaylightSavings())
                        hourStr = to_string((hour - 4 + 12) % 12);
                    else
                        hourStr = to_string((hour - 5 + 12) % 12);
                    if (hourStr == "0")
                        hourStr = "00";
                    string minute = to_string(t->tm_min);
                    if (minute.length() == 1)
                        minute = "0" + minute;
                    string time = hourStr + ":" + minute;
                    times.push_back(time);
                }
            }
        }
        
        ind1_low = ind1_high;
        ind_between = tx.find("route_id\":\"", ind1_low + 1);
        ind1_high = tx.find("route_id\":\"" + route, ind1_low + 1);
        if (ind1_high == -1)
            ind1_high = tx.find("route_id\": \"" + route, ind1_low + 1);
    }
    return times;
}

// TODO: convert this python code to C++
// This function was coded as a proof of concept in Python before being added to C++
bool BusMode::isDaylightSavings() {
    // today = date.today()
    // m = int(today.strftime("%m"))
    // d = int(today.strftime("%d"))

    // if (m >= 3 and m <= 11):
    //     if (m == 3):
    //         if (d >= 13):
    //             return True
    //     elif (m == 11):
    //         if (d <= 6):
    //             return True
    //     else:
    //         return True
    return false;
}

string BusMode::formatData(string route, string stop) {
    vector<string> data1 = parseRouteData(route, stop);
    string result = "";
    for (string i : data1) {
        result = result + i + " ";
    }
    return result;
}