#pragma once
#include "../Figure/t_3dvec.h"
#include <math.h>
class ConeLightSource
{
		public:
		t_3dvec orientation;
		t_3dvec position;
		double maxIntensity;
		ConeLightSource(t_3dvec orientation,t_3dvec position, double maxIntensity);
		double getDist(t_3dvec& v);
		double cosPropagate(t_3dvec& pos);
		double constPropagate();
};

