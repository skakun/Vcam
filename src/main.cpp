#include<stdio.h>
#include <iostream>
#include "SolidParser/JsonParser.h"
#include "WorldTransformer/WorldTransformer.h"
#include <math.h>
#include <SFML/Graphics.hpp>
#include "Drawer/Drawer.h"
#include "Config/Config.h"
using namespace std;
int main (int argc,char** argv)
{
		t_World tworld,sworld;
		Config conf;
		JsonParser::parseWorld("../world.json",tworld);
    Camera cam(t_3dvec(20,1,1),t_3dvec(0.001,0.001,0.001),t_3dvec(1,1,1));
    sf::RenderWindow window(sf::VideoMode(1600, 1200), "My window");
	t_Wall frame(std::initializer_list<t_3dvec>{
		t_3dvec(0,0,0),
	t_3dvec(0,1200,0),
	t_3dvec(1600,1200,0),
	t_3dvec(1600,0,0) } );
	window.setFramerateLimit(60);
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
            cam.getPosition().x-=1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            cam.getPosition().x+=1;
        }
		
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            cam.getPosition().y+=1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            cam.getPosition().y-=1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
        {
            cam.getPosition().z+=1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
        {
            cam.getPosition().z-=1;
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
            cam.getDispl_pos().z-=1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5))
        {
            cam.getDispl_pos().z+=1;
        }
		t_World bckp(tworld);
		if(conf.fill)
		{
				WorldTransformer::triangulWorld(bckp,2);
		}
		for (auto & wall:bckp.walls)
		{
				std::cout<<"============================"<<std::endl;
				for(auto edge:wall.edges)
				{
						std::cout<<edge->toString()<<endl;
				}
		}
		/*
		if(conf.fill)
		{
				std::sort(bckp.walls.begin(),bckp.walls.end(),[cam ](const t_Wall & a,const t_Wall&  b)->bool{
								t_3dvec am=a.mid()-cam.getPosition_const()-cam.getDispl_pos();
								t_3dvec bm=b.mid()-cam.getPosition_const()-cam.getDispl_pos();
								return am.norm()>bm.norm();
								});
		}
		*/
		WorldTransformer::project(bckp,cam);
		if(conf.fill)
		{
				std::sort(bckp.walls.begin(),bckp.walls.end(),[cam ](const t_Wall & a,const t_Wall&  b)->bool{
								return a.mid().norm()>b.mid().norm();
								});
		}
		for (auto &node :bckp.nodes)
		{
				node->x*=100;
				node->y*=100;
		}

 
		window.clear();
		Drawer::draw(bckp,window,conf);
		cout<<"======================================================================\n"<<endl;
		cout<<"Cam position"<<cam.getPosition().toString()<<endl;
		cout<<"Cam display position"<<cam.getDispl_pos().toString()<<endl;
		cout<<"Cam orientation"<<cam.getOrientation().toString()<<endl;
        window.display();
		
		while( sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				sf::sleep(sf::Time());

		}
}
