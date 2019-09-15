#pragma once
#include "../Figure/t_Wall.h"
#include<vector>
#include<math.h>
#include"../Camera/Camera.h"
#include "EnlightElems/t_EnlightNode.h"
class LightHandler
{
		public:
				LightHandler();
				void enlight(t_Wall& wall,double intensity);
				void pseudoRayCast(std::vector<t_Wall> & walls, Camera & cam);
	   	        static t_3dvec pseudoRcAtPoint(t_3dvec node, int* baseColor,Camera & cam);
};		

