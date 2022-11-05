#ifndef API_H
#define API_H

#include <string>

class Api {
    private:
        std::string apiUrl;
        // curlpp api;
    public:
        Api(std::string apiUrl);
        ~Api();
        std::string getData();
};

#endif