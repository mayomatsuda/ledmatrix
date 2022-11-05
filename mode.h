#ifndef MODE_H
#define MODE_H

#include <string>
#include "api.h"

class Mode {
    private:
        std::string apiUrl;
        Api api;
    public:
        // Mode(RGBMatrix matrix);
        ~Mode();
        void displayFunction();
        std::string formatData();
};

#endif