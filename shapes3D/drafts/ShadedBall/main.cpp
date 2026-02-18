#include <chrono>
#include <thread>
#include <iostream>

#include "screenUtils.hpp"
#include "geometry.hpp"

int main(){
    
    ScreenParams screenParams(63, 204, 29, 15);
    char* screen = new char[screenParams.hight*screenParams.width];

    //time check starts-------------------------------------------------
    using clock = std::chrono::steady_clock;
    auto start = clock::now();

    vec3 cameraPos(0,2,-5);
    vec3 cameraAngle(0,-0.4,1);
    float matrixToCamera = 2;
    vec3 lightSource(2,3,-2);
    
    Sphere A = Sphere(-0.5,0,0,1);

    cameraAngle.normalize();
    vec3 MatrixYAxis = getMatrixYAxisNN(cameraAngle);
    MatrixYAxis.normalize();
    vec3 MatrixXAxis = getMatrixXAxisNN(cameraAngle);
    MatrixXAxis.normalize();
    vec3 screenCentre = cameraPos + matrixToCamera*cameraAngle;



    for(int i = 0; i<screenParams.hight; i++){
        for(int j = 0; j<screenParams.width; j++){
            vec2 matrixXY = screenParams.pixelsToVector(i,j);
            vec3 pixelPos = screenCentre + matrixXY.x*MatrixXAxis + matrixXY.y*MatrixYAxis;
            vec3 rayAngle = unit_vector(cameraPos, pixelPos);

            float dist = A.closestRayIntercection(cameraPos, rayAngle);
            if(dist<0){
                screen[screenParams.width*i + j] = ' ';
            } else {
                vec3 intercetion = cameraPos + dist*rayAngle;
                vec3 lightAngle = unit_vector(intercetion, lightSource);
                vec3 pointNormal = unit_vector(A.center, intercetion);
                screen[screenParams.width*i + j] = brightness(pointNormal*lightAngle);
        }
    }
}

    screenParams.drawFrame(screen);

    auto end = clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();


    std::cout << time;
    return 0;
}