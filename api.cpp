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
    curlpp::Easy foo;
    foo.setOpt( new curlpp::options::Url( apiUrl ) );
    foo.setOpt( new curlpp::options::WriteStream( &response ) );
    foo.perform();
    return response.str();
}