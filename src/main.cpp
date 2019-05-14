#include<stdio.h>
#include <iostream>
#include "SolidParser/JsonParser.h"
#include "WorldTransformer/WorldTransformer.h"
#include <math.h>
#include <SFML/Graphics.hpp>
#include "Drawer/Drawer.h"

using namespace std;
int main (int argc,char** argv)
{
//        vector<Figure> world=JsonParser::readWorld("../sworld.json");
     //   vector<Figure> world=JsonParser::readWorld("../sworld.json");
		t_World tworld;
		JsonParser::parseWorld("../world.json",tworld);
    Camera cam(t_3dvec(10,10,-50),t_3dvec(0,0,0),t_3dvec(1,1,1));
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	t_Wall frame;
	frame.nodes.emplace_back(new t_3dvec(0,0,0));
	frame.nodes.emplace_back(new t_3dvec(0,600,0));
	frame.nodes.emplace_back(new t_3dvec(800,600,0));
	frame.nodes.emplace_back(new t_3dvec(800,0,0));
	
	for(auto  it=frame.nodes.begin();it<frame.nodes.end();it++)
	{
			frame.edges.emplace_back(new t_Edge(shared_ptr<t_3dvec>(*it), shared_ptr<t_3dvec>((it+1==frame.nodes.end() ? *frame.nodes.begin():*(it+1)))));
	}
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
            cam.getPosition().x-=0.1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            cam.getPosition().x+=0.1;
        }
		
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            cam.getPosition().y+=0.1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            cam.getPosition().y-=0.1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
        {
            cam.getPosition().z+=0.1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
        {
            cam.getPosition().z-=0.1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        {
            cam.getOrientation().x-=0.001;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
        {
            cam.getOrientation().y-=0.001;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        {
            cam.getOrientation().z-=0.001;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
        {
            cam.getDispl_pos().x-=0.001;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))
        {
            cam.getDispl_pos().x+=0.001;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
        {
            cam.getDispl_pos().y-=0.001;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))
        {
            cam.getDispl_pos().y+=0.001;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0))
        {
            cam.getDispl_pos().z-=0.001;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5))
        {
            cam.getDispl_pos().z+=0.001;
        }
		t_World projected=WorldTransformer::project(tworld,cam);
		for(auto & node:projected.nodes)
		{
				node->x*=100;
				node->y*=100;
		}
		window.clear();
		Drawer::drawWorld(projected,window,true);
		for (auto & wall:projected.walls)
				for(auto edge:wall.edges)
				std::cout<<edge->toString()<<endl;
		cout<<"======================================================================\n"<<endl;
		cout<<"Cam position"<<cam.getPosition().toString()<<endl;
		cout<<"Cam display position"<<cam.getDispl_pos().toString()<<endl;
		cout<<"Cam orientation"<<cam.getOrientation().toString()<<endl;
        window.display();
		while(! sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				sf::sleep(sf::Time());
		}
}
