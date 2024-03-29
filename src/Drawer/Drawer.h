#pragma once
#include <math.h>
#include <SFML/Graphics.hpp>
#include "../Figure/Figure.h"
#include "../Figure/t_World.h"
#include "../Config/Config.h"
#include "../Camera/Camera.h"
#include "../LightHandler/LightHandler.h"
#include "../ColorfullFigure/ColorfullNode.h"
using namespace std;
class Drawer
{
		private:
				static void drawFilled(t_World & world, sf::RenderWindow &window);
				static void drawTrans(t_World & world, sf::RenderWindow &window);
		public:
				static void draw(t_World & world,sf::RenderWindow &window,Config& conf);
				static void drawGradient(t_World & world,Camera& cam, sf::RenderWindow &window);
};
