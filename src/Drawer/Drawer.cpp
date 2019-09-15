#include"Drawer.h"
#include <assert.h>
using namespace std;
void Drawer::drawFilled(t_World & world, sf::RenderWindow &window)
{
		for( auto & wall:world.walls)
		{
				sf::ConvexShape convex;
				convex.setFillColor(sf::Color(wall.color[0],wall.color[1],wall.color[2]));
//				convex.setFillColor(sf::Color::Transparent);
				convex.setOutlineColor(sf::Color::White);
				convex.setOutlineThickness(0);
				convex.setPointCount(wall.edges.size());
				int i=0;
				for (auto & edge :wall.edges)
				{
						convex.setPoint(i++,sf::Vector2f(edge->n1->x,edge->n1->y));
				}
				window.draw(convex);
		}
}
void Drawer::drawTrans(t_World & world, sf::RenderWindow &window)
{
		for( auto & wall:world.walls)
		{
				for (auto & edge :wall.edges)
				{
						sf::Vertex line[]=
						{
								sf::Vertex(sf::Vector2f(edge->n1->x,edge->n1->y)),
								sf::Vertex(sf::Vector2f(edge->n2->x,edge->n2->y))
						};
						window.draw(line,2,sf::Lines);
				}
		}
}
static void Drawer::drawGradient(t_World & world,Camera& cam, sf::RenderWindow &window)
{
		for( auto & wall:world.walls)
		{
				std::vector<sf::Vertex> poly;
				for (auto & edge :wall.edges)
				{
						assert(edge->n1->isColorfull() && "drawGradient has been called on non colourfull node");
						t_3dvec color= (dynamic_cast<t_ColorfullNode*>(edge->n1.get()))->color;
						std::cout<<"Color"<<color.toString()<<endl;
						poly.emplace_back(sf::Vector2f(edge->n1->x,edge->n1->y),sf::Color(color.x,color.y,color.z));
				}
				window.draw(&poly[0],poly.size(),sf::Quads);
		}
}
void Drawer::draw(t_World & world, sf::RenderWindow &window,Config & conf)
{
		if(conf.fill)
				drawFilled(world,window);
		else
				drawTrans(world,window);
}
