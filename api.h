#ifndef API_H
#define API_H

#include <string>

/** 
 * @brief Api data access class
 * @details Creates an Api that accesses data from a specific internet URL.
 * @authors mmacd327
 */
class Api {
    private:
       /**
        * The URL of the resource the Api is accessing
        */
        std::string apiUrl;
    public:
       /**
        * @brief Creates an Api that can access URL
        * @details Constructor that sets URL to be accessed by Api.
        * @param url URL of resource to access
        */
        Api(std::string url);
        ~Api();
       /**
        * @brief Access data at URL
        * @details Accesses resource at URL and gathers all data as a string.
        * @return String response of data retrieved from URL
        */
        std::string getData();
};

#endif