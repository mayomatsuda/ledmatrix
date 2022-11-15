#include "busmode.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
using namespace std;

BusMode::BusMode(rgb_matrix::RGBMatrix* mtx) : Mode(mtx) {
    string URL = "http://gtfs.ltconline.ca/TripUpdate/TripUpdates.json";
    api = new Api(URL);
}

BusMode::~BusMode() {

}

void BusMode::displayFunction(std::string text) {

}

vector<string> BusMode::parseRouteData(string route, string stop) {
    // Get data from the Api
    // See TripUpdates.json for an example of what the data being processed here will look like

    string tx = api->getData();
    // ifstream t("TripUpdates.json");
    // stringstream buffer;
    // buffer << t.rdbuf();
    // string tx = buffer.str();

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

string BusMode::formatData() {
    string route_1 = "02";
    string route_2 = "102";
    string stop = "WHARMOIR";
    vector<string> data1 = parseRouteData(route_1, stop);
    for (string i : data1) {
        cout << i << endl;
    }
    return "hello";
}

int main() {
    BusMode* mb = new BusMode(NULL);
    mb->formatData();
}