//
//
#pragma once
#include "Solid.h"

void Solid::addEdge(_3dvec n1,_3dvec n2)
{
    bool occuredN1=false;
    bool occuredN2=false;
    _3dedge toAdd;
    for (auto  node :nodes)
    {
        if(!occuredN1)
        {
            occuredN1 = (*node.get() == n1);
            if(occuredN1)
            {
                toAdd.n1=node;
            }
        }

        if(!occuredN2)
        {
            occuredN2 = (*node.get() == n2);
            if(occuredN2)
            {
                toAdd.n2=node;
            }
        }
    }
    if(!occuredN1)
    {
        toAdd.n1=make_shared<_3dvec>(n1.x,n1.y,n1.z);
        nodes.push_back(move(toAdd.n1));
      //  nodes.push_back(*toAdd.n1.get());
       // nodes.push_back(move(*toAdd.n1.get()));
    }
    if(!occuredN2)
    {
        toAdd.n2=make_shared<_3dvec>(n2.x,n2.y,n2.z);
        nodes.push_back(move(toAdd.n2));
      //  nodes.push_back(*toAdd.n2.get());
      //nodes.push_back(move(*toAdd.n2.get()));
    }
    edges.push_back(toAdd);
}

void Solid::addNode(_3dvec n)
{
    //this->nodes.push_back(n);
}



const vector<_3dedge> &Solid::getEdges() const
{
    return edges;
}

void Solid::setEdges(const vector<_3dedge> &edges)
{
    Solid::edges = edges;
}

Solid::~Solid()
{
}

 vector<shared_ptr<_3dvec>> &Solid::getNodes()
{
    return nodes;
}

void Solid::setNodes(const vector<shared_ptr<_3dvec>> &nodes)
{
    Solid::nodes = nodes;
}

