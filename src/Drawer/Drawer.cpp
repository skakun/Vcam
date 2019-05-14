#include"Drawer.h"
using namespace std;
void Drawer::drawTransparentFigure(Figure& fig,sf::RenderWindow &window)
{
        for(auto & edge : fig.getEdges())
        {
                
				sf::Vertex line[2];
                line[0]=sf::Vector2f(edge->n1->x,edge->n1->y);
                line[1]=sf::Vector2f(edge->n2->x,edge->n2->y);
                window.draw(line, 2, sf::Lines);

        }
}
void Drawer::drawByWalls(Figure &fig, sf::RenderWindow &window)
{	
		for( auto wall:fig.getWalls())
		{
				sf::ConvexShape convex;
				convex.setFillColor(sf::Color::Green);
	//			convex.setOutlineColor(sf::Color::White);
//				convex.setOutlineThickness(1);
				convex.setPointCount(wall.nodes.size());
				int i=0;
				for (auto & node :wall.nodes)
				{
			//			std::cout<<"Polygon size:"<<wall.nodes.size()<<endl;
						convex.setPoint(i++,sf::Vector2f(node->x,node->y));
				}
				window.draw(convex);
		}
}
void Drawer::drawWorld(vector<Figure>,sf::RenderWindow window,bool transparent)
{}
void Drawer::drawWorld(t_World & world, sf::RenderWindow &window,bool transparent)
{
		for( auto wall:world.walls)
		{
				sf::ConvexShape convex;
//				convex.setFillColor(sf::Color::Green);
				convex.setFillColor(sf::Color::Transparent);
				convex.setOutlineColor(sf::Color::White);
				convex.setOutlineThickness(1);
				convex.setPointCount(wall.edges.size());
				int i=0;
				for (auto & edge :wall.edges)
				{
			//			std::cout<<"Polygon size:"<<wall.nodes.size()<<endl;
						convex.setPoint(i++,sf::Vector2f(edge->n1->x,edge->n1->y));
				}
				window.draw(convex);
		}
}
