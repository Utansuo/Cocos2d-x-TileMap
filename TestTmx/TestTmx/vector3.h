//
//  vector3.h
//  TestTmx
//
//  Created by WU WUYUAN on 13-2-22.
//
//

#ifndef __TestTmx__vector3__
#define __TestTmx__vector3__

#include <iostream>

#endif /* defined(__TestTmx__vector3__) */

#ifndef VECTOR_H
#define VECTOR_H

class Vector3
{
public:
    Vector3(){x=0;y=0;z=0;}
    Vector3(float xx,float yy,float zz):x(xx),y(yy),z(zz){}
    Vector3(const Vector3 & vec)
    {
        x=vec.x;
        y=vec.y;
        z=vec.z;
    }
    inline float length();
    Vector3 normalize();
    float dotProduct(const Vector3 & v);
    Vector3 crossProduct(const Vector3 & v);
    
    Vector3 operator +(const Vector3 & v);
    Vector3 operator -(const Vector3 & v);
    Vector3 operator *(float scale);
    Vector3 operator /(float scale);
    Vector3 operator -();
    
    float x,y,z;
};


#endif

/**************************Vector.cpp**************************/


