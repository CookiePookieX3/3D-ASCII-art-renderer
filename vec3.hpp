#pragma once

#include <cmath>


struct vec3{
    float x, y, z;

    vec3() = default;
    vec3(float _x, float _y, float _z): x(_x), y(_y), z(_z) {}

    vec3 operator+(const vec3& other) const {return vec3(x+other.x, y+other.y, z+other.z);}
    vec3 operator-(const vec3& other) const {return vec3(x-other.x, y-other.y, z-other.z);}
    float operator*(const vec3& other) const {return x*other.x + y*other.y + z*other.z;}
    vec3 operator*(float other) const {return vec3(x*other, y*other, z*other);}
    vec3 operator/(float other) const {return vec3(x/other, y/other, z/other);}
    void normalize(){
        float len = std::sqrt(x*x + y*y + z*z);
        x/=len;
        y/=len;
        z/=len;
    }
};

inline vec3 operator*(float k, const vec3& v) {return v*k;}

inline float distance(const vec3& a, const vec3& b){
    return std::sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z));
}

inline vec3 unit_vector(const vec3& start, const vec3& end){
    vec3 norm(end.x - start.x, end.y - start.y, end.z - start.z);
    return norm/distance(start, end);
}