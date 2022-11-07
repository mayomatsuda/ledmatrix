#ifndef API_H
#define API_H

#include <string>

class Api {
    private:
        std::string apiUrl;
    public:
        Api(std::string url);
        ~Api();
        std::string getData();
};

#endif