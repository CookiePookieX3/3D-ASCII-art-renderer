#include <chrono>
#include <thread>

#include "screenUtils.hpp"
#include "geometry.hpp"

int main(){
    
    ScreenParams screenParams(63, 204, 29, 15);
    char* screen = new char[screenParams.hight*screenParams.width];


    //time check starts-------------------------------------------------
    //max FPS 360
    using clock = std::chrono::steady_clock;
    auto start = clock::now();


    vec3 cameraPos(0,3,-10);
    vec3 cameraAngle = vec3(0,1,0) - cameraPos;
    float matrixToCamera = 3;
    vec3 lightSource(2,3,-2);
    
    int N = 5;
    Object** objects = new Object*[N];
    objects[0] = new Sphere(0,1,0,1);
    objects[1] = new Sphere(-1,0.5,-1,0.5);
    objects[2] = new Sphere(-3,2,-1,2);
    objects[3] = new Sphere(2,0.75,2,0.75);
    objects[4] = new Sphere(4,0.5,0,0.5);

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

            Object* closestObj = nullptr;
            float closest = -1;
            for(int n = 0; n<N; n++){
                float dist = objects[n]->closestRayIntercection(cameraPos, rayAngle);
                if((dist<closest || closest<0) && dist>0){
                    closest = dist;
                    closestObj = objects[n];
                }

            }

            if(closest<0){
                screen[screenParams.width*i + j] = ' ';
            } else {
                vec3 intercetion = cameraPos + closest*rayAngle;
                vec3 lightAngle = unit_vector(intercetion, lightSource);
                vec3 pointNormal = closestObj->getNormal(intercetion);
                screen[screenParams.width*i + j] = brightness(pointNormal*lightAngle);
            }
        }
    }


        screenParams.drawFrame(screen);

    delete[] screen;
    for(int n = 0; n<N; n++){
        delete objects[n];
    }
    delete[] objects;


    auto end = clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();


    std::cout << time;




    return 0;
}