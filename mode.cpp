#include "mode.h"
#include "api.h"
using namespace std;

Mode::Mode(rgb_matrix::RGBMatrix* mtx) {
    matrix = mtx;
}

Mode::~Mode() {
    delete api;
}