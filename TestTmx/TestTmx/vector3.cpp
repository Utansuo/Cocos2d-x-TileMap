//
//  vector3.cpp
//  TestTmx
//
//  Created by WU WUYUAN on 13-2-22.
//
//

#include "vector3.h"


inline float Vector3::length()
{
    return x*x+y*y+z*z;
}

Vector3 Vector3::normalize()
{
    float len=length();
    if(len==0) len=1;
    x/=len,y/=len,z/=len;
    return * this;
}

float Vector3::dotProduct(const Vector3 & v)
{
    return x*v.x+y*v.y+z*v.z;
}

Vector3 Vector3::crossProduct(const Vector3 & v)
{
    Vector3 vec;
    vec.x=y*v.z-z*v.y;
    vec.y=z*v.x-x*v.z;
    vec.z=x*v.y-y*v.x;
    return vec;
}

Vector3 Vector3::operator +(const Vector3 & v)
{
    return Vector3(x+v.x,y+v.y,z+v.z);
}

Vector3 Vector3::operator -(const Vector3 & v)
{
    return Vector3(x-v.x,y-v.y,z-v.z);
}

Vector3 Vector3::operator *(float scale)
{
    x*=scale,y*=scale,z*=scale;
    return * this;
}

Vector3 Vector3::operator /(float scale)
{
    if(scale!=0)
        x/=scale,y/=scale,z/=scale;
    return * this;
}


Vector3 Vector3::operator -()
{
    return Vector3(-x,-y,-z);
}
