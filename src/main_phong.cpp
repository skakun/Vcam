#include <iostream>
#include<stdio.h>
#include <iostream>
#include <stdlib.h>
#include "SolidParser/JsonParser.h"
#include "WorldTransformer/WorldTransformer.h"
#include <math.h>
#include <SFML/Graphics.hpp>
#include "Drawer/Drawer.h"
#include "Config/Config.h"
#include <string>
#include <unistd.h>
#include "Figure/t_Ball.h"
#include "LightHandler/LightHandler.h"
#include "ColorfullFigure/ColorfullNode.h"
#include "_Control/Control.h"
using namespace std;
int main(int argc, char** argv)
{
		cout<<"Phong"<<endl;
	//	t_Ball ball(10,10,10,10,100,100,0);
		t_Ball ball3(10,10,10,10,255,255,0);
		Camera cam(t_3dvec(8,7,-10),t_3dvec(0,0,0),t_3dvec(1,1,1));
		Config conf={1};
		sf::RenderWindow window(sf::VideoMode(1200, 1200), "My window");
	    t_World tworld;
	 	WorldTransformer::aproxBall(tworld,ball3,30);
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop

		controlLoop(cam,window);
		t_World bckp(tworld);
		for(auto & wall:bckp.walls)
		{
				for(auto & edge:wall.edges)
				{
						if(!edge->n1->isColorfull())
						{
								t_3dvec color=LightHandler::pseudoRcAtPoint(*edge->n1,wall.color,cam);
							//	std::cout<<"Color"<<color.toString()<<endl;
								auto replace=std::shared_ptr<t_ColorfullNode>(new t_ColorfullNode(*edge->n1,color));
								edge->n1=replace;	
								if(!edge->n1->isColorfull())
										std::cout<<"chuj"<<std::endl;
						}
				}
				bckp.grabNodes(wall);
		}
		LightHandler lc;
		//lc.pseudoRayCast(bckp.walls,cam);
				std::sort(bckp.walls.begin(),bckp.walls.end(),[cam ](const t_Wall & a,const t_Wall&  b)->bool{
								return a.mid()*(cam.getPosition()+cam.getDistToDiplPlaneComponents()) > b.mid()*(cam.getDistToDiplPlaneComponents()+cam.getPosition());
								});

		WorldTransformer::project(bckp,cam);
		for (auto &node :bckp.nodes)
		{
				node->x*=100;
//				node->x+=400;
				node->y*=100;
//				node->y+=300;
		}

		cout<<endl;
		cout<<"Cam position"<<cam.getPosition().toString()<<endl;
		cout<<"Cam display position"<<cam.getDistToDiplPlaneComponents().toString()<<endl;
		cout<<"Cam orientation"<<cam.getOrientation().toString()<<endl;
		cout<<endl;

		window.clear();
//		Drawer::draw(bckp,window,conf);
		Drawer::drawGradient(bckp,cam,window);
		window.display();
	}
}
