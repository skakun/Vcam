#pragma once
#include"../Camera/Camera.h"
#include <SFML/Graphics.hpp>
void inline controlLoop(Camera&cam, sf::RenderWindow & window)
{
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
			cam.changeDisplPosDistance(-0.1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5))
		{
			cam.changeDisplPosDistance(0.1);
		}

}
