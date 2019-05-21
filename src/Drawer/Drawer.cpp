#include"Drawer.h"
using namespace std;
void Drawer::drawWorld(t_World & world, sf::RenderWindow &window,bool transparent)
{
		for( auto wall:world.walls)
		{
				sf::ConvexShape convex;
				convex.setFillColor(sf::Color(wall.color[0],wall.color[1],wall.color[2]));
//				convex.setFillColor(sf::Color::Transparent);
				convex.setOutlineColor(sf::Color::White);
				convex.setOutlineThickness(1);
				convex.setPointCount(wall.edges.size());
				int i=0;
				for (auto & edge :wall.edges)
				{
			//			std::cout<<"Polygon size:"<<wall.nodes.size()<<endl;
						convex.setPoint(i++,sf::Vector2f(edge->n1->x*100,edge->n1->y*100));
				}
				window.draw(convex);
		}
}
