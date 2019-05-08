//
//
#pragma once


#include "Figure.h"

void Figure::addNode(t_3dvec *n)
{
    nodes.emplace_back(n);
}




Figure::~Figure()
{
}

 vector<shared_ptr<t_3dvec>> &Figure::getNodes()
{
    return nodes;
}
const vector<shared_ptr<t_3dvec>>  &Figure::const_getNodes()const 
{
    return nodes;
}


void Figure::setNodes(const vector<shared_ptr<t_3dvec>> &nodes)
{
    Figure::nodes = nodes;
}

shared_ptr<t_3dvec> Figure::getRoutedNode(int rid)
{
    return *find_if(nodes.rbegin(),nodes.rend(),[rid](const shared_ptr<t_3dvec>  & p_node){ return p_node->route_id == rid;});
}

void Figure::gatherEdgesFromWalls()
{
    for (auto & wall:walls)
    {
        for(auto& edge:wall.edges)
        {
            if ( find_if(edges.rbegin() ,edges.rend(),[edge](shared_ptr<t_Edge> p_edge){return *p_edge.get()==*edge;})==edges.rend())
            {
                edges.push_back(edge);
            }
        }
    }
}

vector<shared_ptr<t_Edge>> &Figure::getEdges()
{
    return edges;
}

 vector<t_Wall> &Figure::getWalls()
{
    return walls;
}
const vector<t_Wall> &Figure::const_getWalls()const 
{
    return walls;
}

void Figure::print_edges()
{
    for (auto & edge:edges)
    {
        cout<<edge->toString()<<endl;
    }
}
Figure::Figure(const Figure & to_copy)
{
		for(auto  node :to_copy.const_getNodes())
		{
				nodes.emplace_back(make_shared<t_3dvec>(node->x,node->y,node->z,node->route_id));
		}
		for(auto  wall:to_copy.const_getWalls())
		{
				t_Wall n_wall;
				n_wall.signatures=wall.signatures;
				for (auto & edge :wall.edges)
				{
						n_wall.edges.emplace_back(make_shared<t_Edge>(getRoutedNode(edge->n1->route_id),getRoutedNode(edge->n2->route_id)));
				}
				walls.push_back(n_wall);
		}
		gatherEdgesFromWalls();

}

Figure::Figure()
{
		;
}
