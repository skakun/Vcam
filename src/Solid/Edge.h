//
//

#pragma once

#include <memory>
#include <math.h>
using namespace std;
typedef struct   _3dnode
{
    double x;
    double y;
    double z;
    _3dnode(double x, double y,double z)
    {
        this->x=x;
        this->y=y;
        this->z=z;
    }
    _3dnode()
    {
        _3dnode(0,0,0);
    }

    double norm()
    {
        return sqrt (x*x+y*y+z*z);
    }

}_3dvec;
inline bool operator ==(const _3dvec& lhs, const _3dvec& rhs)
{
    return  lhs.x==rhs.x && lhs.y==rhs.y&&lhs.z==rhs.z;
}
typedef struct _3dedge
{
    shared_ptr<_3dvec> n1;
    shared_ptr<_3dvec> n2;

}_3dedge;
