make: driver.cpp busmode.cpp weathermode.cpp mode.cpp api.cpp
	g++ -Dcimg_display=0 -Irpi-rgb-led-matrix/include -Ijson/include -ICImg -Wall -O3 -g -Wextra -Wno-unused-parameter -c driver.cpp -c busmode.cpp -c weathermode.cpp -c mode.cpp -c api.cpp
	g++ driver.o busmode.o weathermode.o mode.o api.o -o driver -Lrpi-rgb-led-matrix/lib -lrgbmatrix -lrt -lm -lpthread -lcurlpp -lcurl

# make: driver.cpp busmode.cpp weathermode.cpp mode.cpp api.cpp
# 	g++ -std=c++14 -Dcimg_display=0 -Irpi-rgb-led-matrix/include -I/opt/homebrew/opt/curlpp/include -Ijson/include -ICImg -Wall -O3 -g -Wextra -Wno-unused-parameter -c driver.cpp -c busmode.cpp -c weathermode.cpp -c mode.cpp -c api.cpp
# 	g++ driver.o busmode.o weathermode.o mode.o api.o -o driver -Lrpi-rgb-led-matrix/lib -L/opt/homebrew/opt/curlpp/lib -lpthread -lcurlpp -lcurl
