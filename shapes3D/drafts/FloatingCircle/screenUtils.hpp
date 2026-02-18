#pragma once

#include <iostream>


void DrawFrame(int* screen, int height, int width);
void pixelToPoint(int row, int colon, double&x, double& y, int height, int width, int charcterHeight, int characterWidth);



void DrawFrame(char* screen, int height, int width){
    for(int i = 0; i<height; i++){
        for(int j = 0; j<width; j++){
            std::cout << screen[i*width + j];
        }
        std::cout << '\n';
    }
}

void PixelToPoint(int row, int colon, double&x, double& y, int height, int width, int characterHeight, int characterWidth){
    y = 1 - 2*(((double)row)/(height-1));
    x = ((double)characterWidth*width)/(characterHeight*height)*(-1 + 2*((double)colon)/(width-1));
}