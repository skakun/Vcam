#pragma once
#include <math.h>
#include <SFML/Graphics.hpp>
#include "../Figure/Figure.h"
#include "../Figure/t_World.h"
using namespace std;
class Drawer
{
		public:
		static void drawTransparentFigure(Figure &fig,sf::RenderWindow &window);
		static void drawByWalls(Figure &fig, sf::RenderWindow &window);
		static void drawWorld(vector<Figure>,sf::RenderWindow window,bool transparent);
		static void drawWorld(t_World & world, sf::RenderWindow &window,bool transparent);
};
