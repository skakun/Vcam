#pragma once
#include "../Figure/t_Wall.h"
#include<vector>
#include<math.h>
#include"../Camera/Camera.h"
#include "EnlightElems/t_EnlightNode.h"
#include "ConeLightSource.h"
class LightHandler
{
		std::vector<ConeLightSource> sources;
		double baseIntensity=255;
		public:
				LightHandler();
				void enlight(t_Wall& wall,double intensity);
				void pseudoRayCast(std::vector<t_Wall> & walls, Camera & cam);
	   	        static t_3dvec pseudoRcAtPoint(t_3dvec node, int* baseColor,Camera & cam);
	   	        t_3dvec pseudoRcAtPoint(t_3dvec node, int* baseColor);
	   	        t_3dvec phongReflect(t_3dvec node, int* baseColor);
				void emplaceLightSource(t_3dvec orientation,t_3dvec position, double maxIntensity);

};		

