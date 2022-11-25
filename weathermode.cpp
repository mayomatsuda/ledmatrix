#include "weathermode.h"
#include "led-matrix.h"
#include "graphics.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <unistd.h>
#include <algorithm>
#include <nlohmann/json.hpp>
#include <curl/curl.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace rgb_matrix;
using namespace cv;
using json = nlohmann::json;

WeatherMode::WeatherMode(rgb_matrix::RGBMatrix* mtx) : Mode(mtx) {

}

WeatherMode::~WeatherMode() {

}

void WeatherMode::displayFunction(vector<string> input) {
    // Format of input for BusMode's display function should be {stop, route1, route2}
    string lon = input[0];
    string lat = input[1];
    string API_KEY = "9f1b0c1d0f611f5ffb437e3ebbeb98c5";
    
    string URL = "https://api.openweathermap.org/data/2.5/weather?lat=" + lat + "&lon=" + lon + "&appid=" + API_KEY + "&units=metric";
    api = new Api(URL);

    string IMAGE = "out.jpg";

    FrameCanvas *canvas = matrix->CreateFrameCanvas();
    Font *font = new Font();
    font->LoadFont("./rpi-rgb-led-matrix/fonts/7x13.bdf");
    Font *fontsmall = new Font();
    fontsmall->LoadFont("./rpi-rgb-led-matrix/fonts/6x9.bdf");
    Color colorOne = Color(255, 255, 255);

    while (true) {
        vector<string> data = parseWeatherData(stof(lon), stof(lat));

        canvas->Clear();

        const int LEFT_POS = 1;
        const int TOP_POS = 13;
        const int BOTTOM_POS = 25;
        const int RIGHT_POS = 19;

        Mat image = imread(IMAGE);
        resize(image, image, Size(16,16), 0, 0, INTER_LINEAR);

        if (data[1] == "Thunderstorm") {
            data[1] = "Thunder";
        }

        DrawText(canvas, *font, LEFT_POS, TOP_POS, colorOne, data[0]);
        DrawText(canvas, *fontsmall, RIGHT_POS, BOTTOM_POS, colorOne, data[1]);

        int nx = image.cols;
        int ny = image.rows;

        for (int a = 0; a < ny; ++a) {
            for (int b = 0; b < nx; ++b) {
                matrix->SetPixel(a + TOP_POS, b + LEFT_POS,
                    ScaleQuantumToChar(image[y][x][0]),
                    ScaleQuantumToChar(image[y][x][1]),
                    ScaleQuantumToChar(image[y][x][2])
                );
            }
        }

        canvas = matrix->SwapOnVSync(canvas);
        break;
        sleep(60);
    }
}

// https://stackoverflow.com/questions/10112959/download-an-image-from-server-curl-however-taking-suggestions-c
size_t callbackfunction(void *ptr, size_t size, size_t nmemb, void* userdata)
{
    FILE* stream = (FILE*)userdata;
    if (!stream)
    {
        printf("!!! No stream\n");
        return 0;
    }

    size_t written = fwrite((FILE*)ptr, size, nmemb, stream);
    return written;
}

// https://stackoverflow.com/questions/10112959/download-an-image-from-server-curl-however-taking-suggestions-c
bool download_jpeg(const char* url)
{
    FILE* fp = fopen("out.jpg", "wb");
    if (!fp)
    {
        printf("!!! Failed to create file on the disk\n");
        return false;
    }

    CURL* curlCtx = curl_easy_init();
    curl_easy_setopt(curlCtx, CURLOPT_URL, url);
    curl_easy_setopt(curlCtx, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curlCtx, CURLOPT_WRITEFUNCTION, callbackfunction);
    curl_easy_setopt(curlCtx, CURLOPT_FOLLOWLOCATION, 1);

    CURLcode rc = curl_easy_perform(curlCtx);
    if (rc)
    {
        printf("!!! Failed to download: %s\n", url);
        return false;
    }

    long res_code = 0;
    curl_easy_getinfo(curlCtx, CURLINFO_RESPONSE_CODE, &res_code);
    if (!((res_code == 200 || res_code == 201) && rc != CURLE_ABORTED_BY_CALLBACK))
    {
        printf("!!! Response code: %d\n", res_code);
        return false;
    }

    curl_easy_cleanup(curlCtx);

    fclose(fp);

    return true;
}

vector<string> WeatherMode::parseWeatherData(float lon, float lat) {
    string tx = api->getData();
    json js = json::parse(tx);

    string weather = js["weather"][0]["main"];
    string icon = js["weather"][0]["icon"];
    string icon_url = "http://openweathermap.org/img/wn/" + icon + "@2x.png";
    int temp = (int) round((float) js["main"]["feels_like"]);
    string temps = to_string(temp) + "°";

    download_jpeg(icon_url.c_str());

    time_t currentTime;
    struct tm *localTime;

    time( &currentTime );                   // Get the current time
    localTime = localtime( &currentTime );  // Convert the current time to the local time

    int Hour = localTime->tm_hour;
    int Min = localTime->tm_min;
    string time = to_string(Hour) + ":" + to_string(Min);

    return { time + " " + temps, weather };
}