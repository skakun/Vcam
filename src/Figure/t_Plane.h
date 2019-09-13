#include "t_3dvec.h"
typedef struct t_Plane
{
		t_3dvec abc;
		double d;
		t_Plane(t_3dvec abc, double d)
		{
				this->abc=abc;
				this->d=d;
		}
		double pointDist(t_3dvec point)
		{
				double dist=abc.x*point.x+abc.y*point.y+abc.z*point.z;
				return dist/abc.norm();
		}
} t_Plane;
