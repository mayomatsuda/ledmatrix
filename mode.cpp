#include "mode.h"
#include "api.h"
using namespace std;

Mode::Mode(std::string url, rgb_matrix::RGBMatrix matrix) {
    api = new Api(url);
}

Mode::~Mode() {

}