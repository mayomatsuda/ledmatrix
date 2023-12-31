#include "api.h"
#include <sstream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Easy.hpp>
using namespace std;

Api::Api(string url) {
    apiUrl = url;
}

Api::~Api() {

}

string Api::getData() {
    stringstream response;
    curlpp::Easy request;

    // Set request options to retrieve from URL and write to response
    request.setOpt( new curlpp::options::Url( apiUrl ) );
    request.setOpt( new curlpp::options::WriteStream( &response ) );

    // Perform and return request
    request.perform();
    return response.str();
}