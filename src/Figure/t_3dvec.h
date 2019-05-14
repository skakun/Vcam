//
//

#pragma once

#include <memory>
#include <math.h>
#include <iostream>

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
    t_3dvec(double x, double y,double z)
    {
        this->x=x;
        this->y=y;
        this->z=z;
        this->route_id=0;
    }
    t_3dvec()
    {
        t_3dvec(0,0,0);
    }

    double norm()
    {
        return sqrt (x*x+y*y+z*z);
    }
    string toString()
    {
        return "x: "+to_string(x)+" y: "+to_string(y)+" z : "+to_string(z)+" ["+to_string(route_id)+"]";
    }
		double & operator[](int pos)
		{
				switch (pos)
				{
						case 0:
								return x;
						case 1:
								return y;
						case 2:
								return z;
	//					default:
	//							returnNULL;
				}
		}
		bool* checkLimitsOnPos(double limits[])
		{
				/* min x
				 * min y
				 * min z
				 * max x
				 * max y
				 * max z
				 * */
				bool *flags=new bool[6] { x<limits[0]&&x>limits[3],y<limits[1]&&y>limits[4],z<limits[2]&&z>limits[5]};
				return flags;
		}
		t_3dvec operator +(const t_3dvec &v)
		{
				return t_3dvec(x+v.x,y+v.y,z+v.z);
		}
		t_3dvec operator +=(const t_3dvec &v)
		{
				x+=v.x;
				y+=v.y;
				z+=v.z;
				return *this;
		}
		t_3dvec operator /(const int &i)
		{
				return t_3dvec(x/i,y/i,z/i);
		}
		t_3dvec operator -(const t_3dvec & v)
		{
				return t_3dvec(x-v.x,y-v.y,z-v.z);
		}

}t_3dvec;
inline bool operator ==(const t_3dvec& lhs, const t_3dvec& rhs)
{
   return  lhs.x==rhs.x && lhs.y==rhs.y&&lhs.z==rhs.z;
//    return lhs.route_id=rhs.route_id;
}
