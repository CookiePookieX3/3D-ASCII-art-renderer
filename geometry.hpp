#pragma once

#include <cmath>
#include "vec3.hpp"

char gradient[] = {'$','8','W','@','H','9','Z','4','{','r','[','(','/','!','"'};


struct Object{

    int type = 0;//0 - normal; 1 - light shadow, 2 - plane;

    virtual ~Object() = default;
    char brightness(float scalarMul){
        if(type == 0){
                if(scalarMul > 0.98) return gradient[0];
                if(scalarMul > 0.95) return gradient[1];
                if(scalarMul > 0.90) return gradient[2];
                if(scalarMul > 0.85) return gradient[3];
                if(scalarMul > 0.75) return gradient[4];
                if(scalarMul > 0.70) return gradient[5];
                if(scalarMul > 0.65) return gradient[6];
                if(scalarMul > 0.60) return gradient[7];
                if(scalarMul > 0.55) return gradient[8];
                if(scalarMul > 0.50) return gradient[9];
                if(scalarMul > 0.40) return gradient[10];
                if(scalarMul > 0.20) return gradient[11];
                if(scalarMul > 0.15) return gradient[12];
                if(scalarMul > 0.00) return gradient[13];
                if(scalarMul >-0.10) return gradient[14];
                return ' ';
        } else if(type == 1){
                if(scalarMul > 0.98) return gradient[0];
                if(scalarMul > 0.95) return gradient[1];
                if(scalarMul > 0.90) return gradient[2];
                if(scalarMul > 0.85) return gradient[3];
                if(scalarMul > 0.75) return gradient[4];
                if(scalarMul > 0.70) return gradient[5];
                if(scalarMul > 0.65) return gradient[6];
                if(scalarMul > 0.60) return gradient[7];
                if(scalarMul > 0.55) return gradient[8];
                if(scalarMul > 0.50) return gradient[9];
                if(scalarMul > 0.40) return gradient[10];
                if(scalarMul > 0.20) return gradient[11];
                if(scalarMul > 0.15) return gradient[12];
                if(scalarMul > 0.00) return gradient[13];
                if(scalarMul >-0.10) return gradient[14];
                return '.';
        } else if(type == 2){
            if(scalarMul > -1) return ':';
            return ' ';
        }
        return '#';
    }
    virtual float closestRayIntercection(const vec3& rayStart, const vec3& rayDirection) const = 0;
    virtual bool RayIntercection(const vec3& rayStart, const vec3& rayDirection) const = 0;
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

    bool RayIntercection(const vec3& rayStart, const vec3& rayDirection) const override {
        float A = rayDirection.x*rayDirection.x + rayDirection.y*rayDirection.y + rayDirection.z*rayDirection.z;
        float B = 2*(rayDirection.x*(rayStart.x - center.x) + 
                     rayDirection.y*(rayStart.y - center.y) + 
                     rayDirection.z*(rayStart.z - center.z));
        float C = rayStart.x*rayStart.x + center.x*center.x - 2*rayStart.x*center.x +
                  rayStart.y*rayStart.y + center.y*center.y - 2*rayStart.y*center.y +
                  rayStart.z*rayStart.z + center.z*center.z - 2*rayStart.z*center.z - radius*radius;

        float D = B*B - 4*A*C;
        if(D>0){
            if((-B+std::sqrt(D))/(2*A) > 0) return 1;
            return 0;
        } else {
            return 0;
        }
    }

    virtual vec3 getNormal(const vec3& point) const override{
        vec3 norm = point - center;
        norm.normalize();
        return norm;
    }
};

struct Plane : Object{
    vec3 point;
    vec3 normal;

    Plane() = default;
    Plane(const vec3& _point, const vec3& _normal): point(_point), normal(_normal) {}

    float closestRayIntercection(const vec3& rayStart, const vec3& rayDirection) const override {
        if(rayDirection*normal == 0){
            return -1;
        }
        float temp1 = normal.x*rayDirection.x +
                      normal.y*rayDirection.y +
                      normal.z*rayDirection.z;
        float temp2 = normal.x*(rayStart.x - point.x) + 
                      normal.y*(rayStart.y - point.y) + 
                      normal.z*(rayStart.z - point.z);
        return -temp2/temp1;
    }
    
    bool RayIntercection(const vec3& rayStart, const vec3& rayDirection) const override {
        float scalMul = rayDirection*normal;
        if(scalMul<0){
            return 1;
        } else {
            return 0;
        }
    }

    vec3 getNormal(const vec3& point) const override{
        return normal;
    }
};