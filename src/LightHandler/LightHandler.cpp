#include "LightHandler.h"
LightHandler::LightHandler()
{
}
void LightHandler::enlight(t_Wall& wall,double intensity)
{
		for(int i=0;i<3;i++)
		{
				float tmp=wall.color[i]*intensity/255;
				if(tmp>255)
				{
						wall.color[i]=tmp;
				}
				else
				{
						wall.color[i]=tmp;
				}
		}
		
}
void  LightHandler::pseudoRayCast(std::vector<t_Wall> & walls, Camera & cam)
{
		double i0=255;
		t_3dvec v,orientation;
		double cosalpha;
		for(auto & wall:walls)
		{
				v=wall.mid()-cam.getPosition();
				orientation=cam.getPosition();
				cosalpha=v*orientation/v.norm()/orientation.norm();
				enlight(wall,i0*cosalpha);
		}
}
static t_3dvec LightHandler::pseudoRcAtPoint(t_3dvec node, int* baseColor,Camera & cam)
{
		t_3dvec color;
		t_3dvec v=node-cam.getPosition();
		t_3dvec orientation=cam.getDistToDiplPlaneComponents();

		double cosalpha=v*orientation/v.norm()/orientation.norm();
//		double intensity=500*(pow(cosalpha,4));
		double intensity=255*cosalpha;
		for(int i=0;i<3;i++)
		{
				float tmp=baseColor[i]*intensity/255;
				switch (i)
				{
						case 0:
								{
										color.x= tmp>255?255:tmp;
										break;
								}
						case 1:
								{
										color.y= tmp>255?255:tmp;
										break;
								}
						case 2:
								{
										color.z= tmp>255?255:tmp;
										break;
								}
				}
		}
		return color;
}
t_3dvec LightHandler::pseudoRcAtPoint(t_3dvec node, int* baseColor)
{
		double intensity=0;
		t_3dvec color;
		for(auto & lsource:sources)
		{
				intensity+=lsource.cosPropagate(node);
		}
		std::cout<<"Intensity: "<<intensity<<std::endl;
		for(int i=0;i<3;i++)
		{
				float tmp=baseColor[i]*intensity/255;
				switch (i)
				{
						case 0:
								{
										color.x= tmp>255?255:tmp;
										break;
								}
						case 1:
								{
										color.y= tmp>255?255:tmp;
										break;
								}
						case 2:
								{
								std::cout<<"Intensity z: "<<tmp<<std::endl;
										color.z= tmp>255?255:tmp;
										break;
								}
				}
		}
		return color;
}
void LightHandler::emplaceLightSource(t_3dvec orientation,t_3dvec position, double maxIntensity)
{
		sources.emplace_back(orientation,position, maxIntensity);
}
