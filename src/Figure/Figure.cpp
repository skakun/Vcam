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

