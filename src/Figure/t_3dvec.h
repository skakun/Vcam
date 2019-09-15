//
//

#pragma once

#include <memory>
#include <math.h>
#include <iostream>
#include <vector>
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
    t_3dvec(double x, double y,double z)
    {
        this->x=x;
        this->y=y;
        this->z=z;
        this->route_id=0;
    }
	/*
	t_3dvec(const t_3dvec& v)
	{
        this->x=v.x;
        this->y=v.y;
        this->z=v.z;
        this->route_id=v.route_id;
	}
	*/
    t_3dvec()
    {
        t_3dvec(0,0,0,0);
    }

    double norm()
    {
        return sqrt (x*x+y*y+z*z);
    }
	double theta()
	{
			return acos(z/norm());
	}
	double phi()
	{
			return atan(y/x);
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
		double operator *(const t_3dvec &v)//dot product
		{
				return x+v.x+y*v.y+z*v.z;
		}
		double getAngle(t_3dvec &v)
		{
				double dotproduct=x+v.x+y*v.y+z*v.z;
				return acos(dotproduct/norm()/v.norm());
		}
		t_3dvec operator*(const int & n)
		{
				return t_3dvec(x*n,y*n,z*n);
		}
		t_3dvec operator*(const double & n)
		{
				return t_3dvec(x*n,y*n,z*n);
		}
		t_3dvec unitize()
		{
				return *this/norm();
		}
		static t_3dvec mid(std::vector<t_3dvec> vecs)
		{
				t_3dvec ret;
				for(t_3dvec v:vecs)
						ret+=v;
				return ret/vecs.size();
		}
		static t_3dvec mid(std::vector<std::shared_ptr<t_3dvec>> vecs)
		{
				t_3dvec ret;
				for(auto v:vecs)
						ret+=(*v);
				return ret/vecs.size();
		}
		static t_3dvec mid(std::vector<std::shared_ptr<t_3dvec>> vecs,int skip)
		{
				t_3dvec ret;
				for(auto  it=vecs.begin();it<vecs.end()-skip;it++)
				{
						auto v=*it;
						ret+=(*v);
				}
				return ret/(vecs.size()-skip);
		}
		virtual bool isColorfull()
		{
				return false;
		}
}t_3dvec;
inline bool operator ==(const t_3dvec& lhs, const t_3dvec& rhs)
{
   return  lhs.x==rhs.x && lhs.y==rhs.y&&lhs.z==rhs.z;
//    return lhs.route_id=rhs.route_id;
}
typedef std::shared_ptr<t_3dvec> p_3dvec;
typedef std::vector<p_3dvec> t_VV;
typedef std::vector<t_VV> t_VVV;
