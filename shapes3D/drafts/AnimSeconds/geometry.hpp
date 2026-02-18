#pragma once

#include <cmath>
#include "vec3.hpp"



struct Object{
    virtual ~Object() = default;
    virtual float closestRayIntercection(const vec3& rayStart, const vec3& rayDirection) const = 0;
    virtual vec3 getNormal(const vec3& point) const = 0;
};

struct Sphere : Object{
    vec3 center;
    float radius;

    Sphere() = default;
    Sphere(const vec3& _center, float _radius): center(_center), radius(_radius) {}
    Sphere(float x, float y, float z,float _radius): center(x, y, z), radius(_radius) {}

    float closestRayIntercection(const vec3& rayStart, const vec3& rayDirection) const override {
        float A = rayDirection.x*rayDirection.x + rayDirection.y*rayDirection.y + rayDirection.z*rayDirection.z;
        float B = 2*(rayDirection.x*(rayStart.x - center.x) + 
                     rayDirection.y*(rayStart.y - center.y) + 
                     rayDirection.z*(rayStart.z - center.z));
        float C = rayStart.x*rayStart.x + center.x*center.x - 2*rayStart.x*center.x +
                  rayStart.y*rayStart.y + center.y*center.y - 2*rayStart.y*center.y +
                  rayStart.z*rayStart.z + center.z*center.z - 2*rayStart.z*center.z - radius*radius;

        float D = B*B - 4*A*C;
        if(D<0){
            return -1.0;
        } else {
            float dist1 = (-B - std::sqrt(D))/(2*A);
            float dist2 = (-B + std::sqrt(D))/(2*A);
            if(dist1 >= 0){
                return dist1;
            } else {
                return dist2;
            }
        }
    }

    bool intercectsRay(const vec3& rayStart, const vec3& rayDirection){
        float A = rayDirection.x*rayDirection.x + rayDirection.y*rayDirection.y + rayDirection.z*rayDirection.z;
        float B = 2*(rayDirection.x*(rayStart.x - center.x) + 
                     rayDirection.y*(rayStart.y - center.y) + 
                     rayDirection.z*(rayStart.z - center.z));
        float C = rayStart.x*rayStart.x + center.x*center.x - 2*rayStart.x*center.x +
                  rayStart.y*rayStart.y + center.y*center.y - 2*rayStart.y*center.y +
                  rayStart.z*rayStart.z + center.x*center.z - 2*rayStart.z*center.z - radius*radius;

        float D = B*B - 4*A*C;
        if(D<0){
            return false;
        } else {
            return true;
        }
    }

    virtual vec3 getNormal(const vec3& point) const override{
        vec3 norm = point - center;
        norm.normalize();
        return norm;
    }
};