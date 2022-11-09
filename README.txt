3307 Group 45 Assignment 3

What has been built
- Api class
- Mode class
- RGBMatrix library integration
- 3D-printed casing CAD design

What is in progress
- BusMode class

To-do
- Other modes
- Driver
- Print casing


SETUP

curlpp library will need to be installed.
On Mac, run `brew install curlpp` to install
View http://www.curlpp.org/ for more info on installation

To compile, use g++ with the following flags:
    -std=c++14
    -I /opt/homebrew/opt/curlpp/include
    -L /opt/homebrew/opt/curlpp/lib
    -l curl
    -l curlpp
The path to curlpp might differ depending on where you homebrew is saved.

Depending on your setup, some of these libraries may need to be installed using brew.

As the Driver class has not yet been built, the classes will have to be tested individually.
A main() function has been added to api.cpp to demonstrate. To compile, try:
    g++ -std=c++14 -I /opt/homebrew/opt/curlpp/include -L /opt/homebrew/opt/curlpp/lib -l curl -l curlpp api.cpp -o api
And running ./api