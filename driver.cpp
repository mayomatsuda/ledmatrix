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

int main() {
    RGBMatrix::Options matrix_options;
    rgb_matrix::RuntimeOptions runtime_opt;
    matrix_options.brightness = 50;
    matrix_options.cols = 64;
    matrix_options.hardware_mapping = "adafruit-hat";
    RGBMatrix *matrix = RGBMatrix::CreateFromOptions(matrix_options, runtime_opt);

    // BusMode* bm = new BusMode(matrix);
    // vector<string> input = {"WHARMOIR", "02", "102"};
    WeatherMode* bm = new WeatherMode(NULL);
    vector<string> input = {"42.984268", "-81.247528"};
    bm->displayFunction(input);
}