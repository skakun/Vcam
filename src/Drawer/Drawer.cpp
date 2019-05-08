#include"Drawer.h"
using namespace std;
void Drawer::drawTransparentFigure(Figure& fig,sf::RenderWindow &window)
{
        for(auto & edge : fig.getEdges())
        {
                
				sf::Vertex line[2];
                line[0]=sf::Vector2f(edge->n1->x*100,edge->n1->y*100);
                line[1]=sf::Vector2f(edge->n2->x*100,edge->n2->y*100);
                window.draw(line, 2, sf::Lines);

        }
}
void Drawer::drawWorld(vector<Figure>,sf::RenderWindow window,bool transparent)
{}
