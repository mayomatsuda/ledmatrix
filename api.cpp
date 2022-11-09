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

// EXAMPLE MAIN FUNCTION
// This is temporary and is for testing the Api class
int main() {
    Api* api = new Api("https://lipsum.com/");
    string data = api->getData();
    cout << data;
}