#ifndef VCAM_SOLID_H
#define VCAM_SOLID_H

#pragma once
#include <memory>
#include <vector>
#include "t_3dvec.h"
#include "../Utils.h"
#include "t_Edge.h"
#include "t_Wall.h"
#include <algorithm>

using namespace std;
class Figure
{
    private:
        vector<shared_ptr<t_3dvec>> nodes;
        vector<shared_ptr<t_Edge>> edges;
public:
     vector<shared_ptr<t_Edge>> &getEdges() ;

     vector<t_Wall> &getWalls() ;

private:
    vector<t_Wall> walls;
public:
     vector<shared_ptr<t_3dvec>> &getNodes() ;

    void setNodes(const vector<shared_ptr<t_3dvec>> &nodes);
    void gatherEdgesFromWalls();

private:


private:
    public:
        void addNode(t_3dvec * n);
        shared_ptr<t_3dvec> getRoutedNode(int route_id);
        ~Figure();

};

#endif //VCAM_SOLID_H
