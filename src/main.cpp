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
        vector<Figure> world=JsonParser::readWorld("../sworld.json");
    Camera cam(t_3dvec(10,10,-50),t_3dvec(0,M_PI,0),t_3dvec(1,1,1));
    vector<Figure>  projected=WorldTransformer::project(vector<Figure>(world),cam);
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
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
        projected=WorldTransformer::project(vector<Figure>(world),cam);
		window.clear();
/*		cout<<"======================================================================\n"<<endl;
		cout<<"ORGINAL"<<endl;
		cout<<"Cam position"<<cam.getPosition().toString()<<endl;
		cout<<"Cam display position"<<cam.getDispl_pos().toString()<<endl;
		cout<<"Cam orientation"<<cam.getOrientation().toString()<<endl;
		world[0].print_edges();*/
        // clear the window with black color
		cout<<"======================================================================\n"<<endl;
		cout<<"PROJECTEDn"<<endl;
		cout<<"Cam position"<<cam.getPosition().toString()<<endl;
		cout<<"Cam display position"<<cam.getDispl_pos().toString()<<endl;
		cout<<"Cam orientation"<<cam.getOrientation().toString()<<endl;
		projected[0].print_edges();
		for(auto &fig :projected)
		{
				Drawer::drawTransparentFigure(fig,window);
		}
        // draw everything here...
        // window.draw(...);

        // end the current frame
        window.display();
       // sf::sleep(sf::Time());
		while(! sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				sf::sleep(sf::Time());
    // world[0].print_edges();
		}
}
