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

    vector<string> route1times = parseRouteData(route1, stop);
    vector<string> route2times = parseRouteData(route2, stop);

    // Prepare matrix
    FrameCanvas *canvas = matrix->CreateFrameCanvas();
    Font *font = new Font();
    font->LoadFont("./rpi-rgb-led-matrix/fonts/7x13.bdf");
    Color colorOne = Color(255, 128, 0);
    Color colorTwo = Color(255, 255, 255);

    int counter = 0;

    // While true is used because, in theory, the matrix should be on perpetually until it's powered off
    while (true) {
        // Every 12*5 = 60 seconds, re-fetch data
        if (counter == 12) {
            route1times = parseRouteData(route1, stop);
            route2times = parseRouteData(route2, stop);

            counter = 0;
        }
        counter += 1;
        canvas->Clear();

        const int LEFT_POS = 1;
        const int RIGHT_POS = 29;
        const int TOP_POS = 13;
        const int BOTTOM_POS = 27;

        // Draw text on matrix
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
    string tx = api->getData();

    // NOTE: the json provided by LTC has errors, and thus, reading it like a normal json wasn't working.
    // This workaround reads it like a long string and finds necessary fields manually.

    // First occurence of desired route, indicated by '"route_id":"<route>"' in the data
    int ind1_low = tx.find("route_id\":\"" + route);
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
        // This will eventually happen when the entire string has been read, terminating the loop
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
                    // Convert the time from the json (in UNIX time) to readable time
                    int timeunix = stoi(tx.substr(ind3+6,ind3+16));
                    time_t tmp = timeunix;
                    tm* t = gmtime(&tmp);
                    int hour = t->tm_hour;
                    string hourStr;
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
        // Search the next group of indexes for more times
        ind1_low = ind1_high;
        ind_between = tx.find("route_id\":\"", ind1_low + 1);
        ind1_high = tx.find("route_id\":\"" + route, ind1_low + 1);
        if (ind1_high == -1)
            ind1_high = tx.find("route_id\": \"" + route, ind1_low + 1);
    }
    return times;
}