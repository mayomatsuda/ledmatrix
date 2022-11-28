#include "busmode.h"
#include "weathermode.h"
#include "led-matrix.h"
#include "graphics.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
using namespace std;
using namespace rgb_matrix;

int main(int argc, char *argv[]) {
    int mode;
    vector<string> input;
    if (argc==1) {
        cout << "Please specify mode." << endl;
        return 0;
    } else {
        string modestr(argv[1]);
        // Bus mode
        if ((modestr == "0" || modestr == "bus") && argc >= 5) {
            mode = 0;
            input = { argv[2], argv[3], argv[4] };
        // Weather mode
        } else if ((modestr == "1" || modestr == "weather") && argc >= 4) {
            mode = 1;
            input = { argv[2], argv[3]};
        } else {
            cout << "Invalid mode." << endl;
            return 0;
        }
    }

    RGBMatrix::Options matrix_options;
    rgb_matrix::RuntimeOptions runtime_opt;
    matrix_options.brightness = 50;
    matrix_options.cols = 64;
    matrix_options.hardware_mapping = "adafruit-hat";
    RGBMatrix *matrix = RGBMatrix::CreateFromOptions(matrix_options, runtime_opt);

    Mode* display;
    if (mode == 0) {
        display = new BusMode(NULL);
        // input = {"WHARMOIR", "02", "102"};
    } else if (mode == 1) {
        display = new WeatherMode(NULL);
        // input = {"-81.247528", "42.984268"};
    }
    try {
        display->displayFunction(input);
    } catch (...) {
        cout << "Invalid input." << endl;
    }
}