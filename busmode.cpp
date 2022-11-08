#include "busmode.h"
using namespace std;

BusMode::BusMode(rgb_matrix::RGBMatrix* mtx) : Mode(mtx) {
    string URL = "http://gtfs.ltconline.ca/TripUpdate/TripUpdates.json";
    api = new Api(URL);
}

BusMode::~BusMode() {

}

void BusMode::displayFunction() {

}

vector<string> BusMode::parseRouteData(string route, string stop) {
    string tx = api->getData();

    // lowest occurence of desired route
    int ind1_low = tx.find("route_id\":\"" + route);
    if (ind1_low == -1) {
        ind1_low = tx.find("route_id\": \"" + route);
    }

    // next occurence of route id
    int ind_between = tx.find("route_id\":\"", ind1_low + 1);

    // next occurence of desired route
    int ind1_high = tx.find("route_id\":\"" + route, ind1_low + 1);
    if (ind1_high == -1) {
        ind1_high = tx.find("route_id\": \"" + route, ind1_low + 1);
    }

    vector<string> times;

    while (true) {
        // this will eventually happen, terminating the loop
        if (ind1_low == -1) {
            sort(times.begin(), times.end());
            return times;
        }

        // ensure instance of the stop exists on the route
        int here = tx.find(stop.c_str(), ind1_low, ind1_high);
        if (here != -1) {
            // find occurence of desired stop
            int ind2 = tx.find("stop_id\":\"" + stop, ind1_low);
            if (ind2 == -1) {
                ind2 = tx.find("stop_id\": \"" + stop, ind1_low);
            }

            if (ind_between > ind2) {
                // find occurence of time at most 50 characters before stop
                int ind3 = tx.find("time", ind2 - 50)

                // convert UNIX time to UTC, then to EST
                timeunix = int(tx[ind3+6:ind3+16])
                hour = int(datetime.utcfromtimestamp(timeunix).strftime('%H'))
                if (daylightSavings):
                    hour = str((hour - 4) % 12)
                else:
                    hour = str((hour - 5) % 12)
                if (hour == '0'): hour = '12'
                minute = str(datetime.utcfromtimestamp(timeunix).strftime('%M'))
                time = hour + ":" + minute
                times.append(time)
            }
        }
        
        ind1_low = ind1_high
        ind_between = tx.find('route_id":"', ind1_low + 1)
        ind1_high = tx.find('route_id":"' + route, ind1_low + 1)
        if ind1_high == -1:
            ind1_high = tx.find('route_id": "' + route, ind1_low + 1)
    }
}

bool isDaylightSavings() {
    today = date.today()
    m = int(today.strftime("%m"))
    d = int(today.strftime("%d"))

    if (m >= 3 and m <= 11):
        if (m == 3):
            if (d >= 13):
                return True
        elif (m == 11):
            if (d <= 6):
                return True
        else:
            return True
}

string BusMode::formatData() {
    string route_1 = "02";
    string route_2 = "102";
    string stop = "WHARMOIR";
}

