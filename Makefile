make: driver.cpp busmode.cpp weathermode.cpp mode.cpp api.cpp
	g++ -Irpi-rgb-led-matrix/include -Ijson/include -Wall -O3 -g -Wextra -Wno-unused-parameter -c driver.cpp -c busmode.cpp -c weathermode.cpp -c mode.cpp -c api.cpp
	g++ driver.o busmode.o weathermode.o mode.o api.o -o driver -Lrpi-rgb-led-matrix/lib -lrgbmatrix -lrt -lm -lpthread -lcurlpp -lcurl