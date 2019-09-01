#pragma once
#include "t_3dvec.h"

typedef struct t_Ball
{
		t_3dvec mid;
		double radius;
		int r,g,b;
		t_Ball(double x, double y, double z,double radius,int r, int g, int b)
		{
				mid=t_3dvec(x,y,z);
				this->radius=radius;
				this->r=r;
				this->g=g;
				this->b=b;
		}
} t_Ball;
