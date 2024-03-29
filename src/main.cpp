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
using namespace std;
int main (int argc,char** argv)
{
	std::string worldPath="../world.json";
	std::string configPath="../config.json";
	std::string usage="usage:\n\t $ vcam -w world file path -f [fill] true|false";
	Config conf;

    int opt;

	std::cout<<"world path pre opt: "<<worldPath<<std::endl;
    while ((opt=getopt(argc,argv,"w:f:")) !=-1)
	{
			switch (opt)
			{
				case 'w' :
						{
								worldPath=optarg;
								std::cout<<"went to opt: "<<worldPath<<std::endl;
								break;
						}
				case 'f':
						{
								conf.fill=atoi(optarg);
								std::cout<<"fill: "<<conf.fill<<std::endl;
								break;
						}
				default :
						{
								std::cout<<usage<<std::endl;
								return;
						}
			}
	}

	t_World tworld,sworld;


	JsonParser::parseWorld(worldPath.c_str(),tworld);
//t_Ball ball(10,10,10,10,100,100,0);
//t_Ball ball1(40,10,10,10,100,100,0);
//t_Ball ball2(80,10,10,10,100,100,0);
//t_Ball ball3(100,10,10,10,100,100,0);
//	WorldTransformer::aproxBall(tworld,ball,50);
//	WorldTransformer::aproxBall(tworld,ball1,20);
//	WorldTransformer::aproxBall(tworld,ball2,20);

    Camera cam(t_3dvec(-20,-20,-20),t_3dvec(0.001,0.001,0.001),t_3dvec(1,1,1));
    sf::RenderWindow window(sf::VideoMode(1600, 1200), "My window");
//	window.setFramerateLimit(60);
    /////////////////////////////////
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            cam.getPosition().x-=2;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            cam.getPosition().x+=2;
        }
		
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            cam.getPosition().y+=2;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            cam.getPosition().y-=2;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
        {
            cam.getPosition().z+=2;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
        {
            cam.getPosition().z-=2;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        {
            cam.getOrientation().x-=0.1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
        {
            cam.getOrientation().y-=0.1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        {
            cam.getOrientation().z-=0.1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
        {
            cam.getDispl_pos().x-=0.1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))
        {
            cam.getDispl_pos().x+=0.1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
        {
            cam.getDispl_pos().y-=0.1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))
        {
            cam.getDispl_pos().y+=0.1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0))
        {
//            cam.getDispl_pos().z-=0.1;
				cam.changeDisplPosDistance(-0.1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5))
        {
				cam.changeDisplPosDistance(0.1);
        }
		t_World bckp(tworld);
		if(conf.fill)
		{
				WorldTransformer::triangulWorld(bckp,3);
		}
		if(conf.fill)
		{
				std::sort(bckp.walls.begin(),bckp.walls.end(),[cam ](const t_Wall & a,const t_Wall&  b)->bool{
								/*
								t_3dvec bm=b.mid()-cam.getPosition_const();
								t_3dvec am=a.mid()-cam.getPosition_const();
								*/
/*
								t_3dvec bm=b.mid()-cam.getDistToDiplPlaneComponents()-cam.getPosition();
								t_3dvec am=a.mid()-cam.getDistToDiplPlaneComponents()-cam.getPosition();
*/

//								return bm.norm()>am.norm();
//								return cam.getDisplPlane().pointDist(a.mid()) > cam.getDisplPlane().pointDist(b.mid());
//								return a.mid().norm() > b.mid.norm();
								return a.mid()*(cam.getPosition()+cam.getDistToDiplPlaneComponents()) < b.mid()*(cam.getDistToDiplPlaneComponents()+cam.getPosition());
								});
		}
/*
		if(conf.fill)
		{
				std::sort(bckp.walls.begin(),bckp.walls.end(),[cam ](const t_Wall & a,const t_Wall&  b)->bool{
								return a.mid().norm()>b.mid().norm();
								});
		}
		*/
		WorldTransformer::project(bckp,cam);
		for (auto &node :bckp.nodes)
		{
				node->x*=100;
				node->x+=400;
				node->y*=100;
				node->y+=300;
		}
		for (auto & wall:bckp.walls)
		{
			std::cout<<"============================"<<std::endl;
				for(auto edge:wall.edges)
				{
						std::cout<<edge->toString()<<endl;
				}
		}

 
		window.clear();
		Drawer::draw(bckp,window,conf);
		cout<<"======================================================================\n"<<endl;
		cout<<"Cam position"<<cam.getPosition().toString()<<endl;
		cout<<"Cam display position"<<cam.getDistToDiplPlaneComponents().toString()<<endl;
		cout<<"Cam orientation"<<cam.getOrientation().toString()<<endl;
        window.display();
		
		while( sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				sf::sleep(sf::Time());

		}
}
