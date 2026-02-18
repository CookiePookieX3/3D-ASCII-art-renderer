#include <iostream>
#include <chrono>
#include <thread>

#include "screenUtils.hpp"


int main(){

    int x = 40000;
    const auto frame = std::chrono::microseconds(x); 
    using clock = std::chrono::steady_clock;

    int height = 63, width = 204;
    int characterHeight = 29, characterWidth = 15;
    char* screen = new char[height*width];

    auto perv = clock::now();

    for(double t = 0; t<800; t++){


        for(int i = 0; i<height; i++){
            for(int j = 0; j<width; j++){
                double x, y;
                PixelToPoint(i, j, x, y, height, width, characterHeight, characterWidth);
                screen[i*width + j] = ((pow(x-sin(t/50), 2) + pow(y - 0.1*sin(t/10), 2)) < 0.25 ||
                                    (pow(x - sin(t/50), 2) + pow(-6*(y+0.75), 2)) < 0.18) ? '#' : ' ';
            }
        }

        DrawFrame(screen, height, width);

        auto now = clock::now();
        auto work = now - perv;
        perv = now;

        if (work < frame){
            std::this_thread::sleep_for(frame - work);
    }
    }

    return 0;
}