//
//

#pragma once

#include <memory>
#include <math.h>
using namespace std;
typedef struct   t_3dvec
{
    double x;
    double y;
    double z;
    int route_id;
   t_3dvec(double x, double y,double z,int route_id)
    {
        this->x=x;
        this->y=y;
        this->z=z;
        this->route_id=route_id;
    }
    t_3dvec()
    {
        t_3dvec(0,0,0,0);
    }

    double norm()
    {
        return sqrt (x*x+y*y+z*z);
    }

}t_3dvec;
inline bool operator ==(const t_3dvec& lhs, const t_3dvec& rhs)
{
   return  lhs.x==rhs.x && lhs.y==rhs.y&&lhs.z==rhs.z;
//    return lhs.route_id=rhs.route_id;
}
