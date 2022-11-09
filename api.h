#ifndef API_H
#define API_H

#include <string>

class Api {
    private:
       /**
        * The URL of the resource the Api is accessing
        */
        std::string apiUrl;
    public:
       /**
        * Constructor that sets URL to access from class
        * @param url URL of resource to access
        */
        Api(std::string url);
        ~Api();
       /**
        * Accesses resource at URL and returns as a string
        * @return String response of JSON retrieved from URL
        */
        std::string getData();
};

#endif