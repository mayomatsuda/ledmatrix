DEPENDENCIES

curlpp (https://github.com/jpbarrette/curlpp)
    Requires curl and libcurl (sudo apt install curl libcurl-dev)
    Installation guide is here: https://github.com/jpbarrette/curlpp/blob/master/doc/guide.pdf
    Our project's Makefile should handle necessary imports for curlpp. However, if installation is done differently
    on your machine, be sure to include the /include folder from wherever curlpp is intalled. This can be done by
    adding -I <path to curlpp folder>/include to line 2 of the Makefile. Depending on your Pi's configuration, other
    dependencies of curlpp may exist that need to be installed. Follow compiler instructions accordingly. If curlpp
    is still not working, ensure all necessary flags are in our project's Makefile by running `curlpp-config cflags`
    for a list of flags to add to line 2, and `curlpp-config --libs` for a list of flags to add to line 3.

nlohmann/json (https://github.com/nlohmann/json)
    This can be cloned directly into the root folder of our project. To set up, we recommend running `make amalgamate`
    and 'make check-amalgamation' from the /json folder. Our project's Makefile should handle importing and loading
    the library.

ImageMagick (https://github.com/ImageMagick/ImageMagick)
    This acts as a dependency for CImg. This can be cloned directly into the root folder of our project. It can be
    installed by running `./configure`, `make`, `sudo make install`, and `sudo ldconfig /usr/local/lib` in that order
    from the /ImageMagick-7.1.0 folder.

CImg (https://github.com/GreycLab/CImg)
    This can be cloned directly into the root folder of our project. Our project's Makefile should handle importing
    and loading the library.

rpi-rgb-led-matrix (https://github.com/hzeller/rpi-rgb-led-matrix)
    This can be cloned directly into the root folder of our project. It can be built by running `make all` from the
    /rpi-rgb=led-matrix folder. Our project's Makefile should handle importing and loading the library. Note that
    code from this library may fail if an LED matrix is not actually plugged in to the Pi.


SETUP

Running `make` should handle compilation of the program. Ensure all libraries above are properly installed.
Hardware-wise, in addition to the Pi, the following pieces of equipment are needed for intended functionality:
    https://www.mouser.ca/ProductDetail/Adafruit/2278?qs=GURawfaeGuChGtvwWGYNVQ%3D%3D&countrycode=CA&currencycode=CAD
    https://www.mouser.ca/ProductDetail/Adafruit/3211?qs=byeeYqUIh0MkEV1wTTyO2w%3D%3D&countrycode=CA&currencycode=CAD
    https://www.mouser.ca/ProductDetail/Adafruit/1466?qs=GURawfaeGuB6hjSuX4SSQg%3D%3D&countrycode=CA&currencycode=CAD


RUNNING

The format of running is as follows:
    ./driver <mode> <params...>
    mode = 0 or "bus":
        ./driver 0 <stop> <route1> <route2>
        for example, ./driver 0 WHARMOIR 02 102
    mode = 1 or "weather":
        ./driver 1 <longitude> <latitude>
        for example, ./driver 1 -81 43
    Failure to specify a mode, or an erroneous parameter, will terminate the program.
