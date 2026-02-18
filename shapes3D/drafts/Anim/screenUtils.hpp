#pragma once

#include <iostream>

#include "vec2.hpp"
#include "vec3.hpp"

struct ScreenParams{

    int hight, width, charH, charW;

    ScreenParams() = default;
    ScreenParams(int _hight, int _width, int _charH, int _charW):
        hight(_hight), width(_width), charH(_charH), charW(_charW) {}


    vec2 pixelsToVector(int row, int col) const {return vec2(
        ((((float)charW)*width)/(charH*hight)*(-1+2*((float)col)/(width-1))),
        1 - 2*(((float)row)/(hight-1))
    );}

    void drawFrame(const char* screen) const {
        for(int i = 0; i<hight; i++){
            for(int j = 0; j<width; j++){
                std::cout << screen[i*width+j];
            }
            std::cout << '\n';
        }
    }
};

inline vec3 getMatrixYAxisNN(const vec3& cameraAngle){
    float a = cameraAngle.x;
    float b = cameraAngle.y;
    float c = cameraAngle.z;
    return vec3(-a*b,a*a + c*c,-b*c);
}

inline vec3 getMatrixXAxisNN(const vec3& cameraAngle){
    float a = cameraAngle.x;
    float b = cameraAngle.y;
    float c = cameraAngle.z;
    return vec3(c,0,-a);
}

inline char brightness(float brightness){
    if(brightness>0.98) return '@';
    if(brightness>0.95) return '$';
    if(brightness>0.9) return '8';
    if(brightness>0.85) return 'W';
    if(brightness>0.75) return 'H';
    if(brightness>0.7) return '9';
    if(brightness>0.65) return 'Z';
    if(brightness>0.6) return '4';
    if(brightness>0.55) return '1';
    if(brightness>0.5) return 'l';
    if(brightness>0.4) return 'r';
    if(brightness>0.2) return '(';
    if(brightness>0.15) return '/';
    if(brightness>0.1) return '!';
    if(brightness>-0.3) return '.';
    return '.';
}