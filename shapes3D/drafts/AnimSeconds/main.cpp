#include <thread>
#include <chrono>

#include "screenUtils.hpp"
#include "geometry.hpp"


int main(){
    
    ScreenParams screenParams(63,204,29,15);
    char* screen = new char[screenParams.hight*screenParams.width];


    float ms = 0;
    int N = 5;
    Object** objects = new Object*[N];
    Sphere* s0 = new Sphere(0,1 + 0.1*sin(6.28*ms/1000 * 0.5 + 5),0,1);
    Sphere* s1 = new Sphere(-1,0.5 + 0.1*sin(6.28*ms/1000 * 1+4),-1,0.5);
    Sphere* s2 = new Sphere(-3,2 + 0.1*sin(6.28*ms/1000 * 0.3+3),-1,2);
    Sphere* s3 = new Sphere(2,0.75 + 0.1*sin(6.28*ms/1000 * 0.7+2),2,0.75);
    Sphere* s4 = new Sphere(4,0.5 + 0.1*sin(6.28*ms/1000 * 1+1),0,0.5);
    objects[0] = s0;
    objects[1] = s1;
    objects[2] = s2;
    objects[3] = s3;
    objects[4] = s4;


    using clock = std::chrono::steady_clock;
    int FPSlimit = 25;
    auto frame = std::chrono::milliseconds(1000/FPSlimit);

    int Time;
    std::cin >> Time;


    auto start = clock::now();
    auto dur = clock::now() - start;
    while(dur < std::chrono::milliseconds(Time*1000)){

        auto nextFrame = clock::now() + frame;
        ms = std::chrono::duration<float, std::milli>(dur).count();

        
        vec3 cameraPos(10*sin(6.28 * ms/1000/100),3,10*cos(6.28 *ms/1000/100));
        vec3 cameraAngle = vec3(0,1,0) - cameraPos;
        float matrixToCamera = 3;
        vec3 lightSource(10*sin(6.28 * ms/1000/10),1,10*cos(6.28 * ms/1000/10));


        s0->center.y = 1 + 0.1*sin(6.28*ms/1000 * 0.5 + 5);
        s1->center.y = 0.5 + 0.1*sin(6.28*ms/1000 * 1+4);
        s2->center.y = 2 + 0.1*sin(6.28*ms/1000 * 0.3+3);
        s3->center.y = 0.75 + 0.1*sin(6.28*ms/1000 * 0.7+2);
        s4->center.y = 0.5 + 0.1*sin(6.28*ms/1000 * 1+1);


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
        
        std::this_thread::sleep_until(nextFrame);
        dur = clock::now() - start;
    }

    for(int n = 0; n<N; n++) delete objects[n];
    delete[] objects;
    delete[] screen;


    return 0;
}