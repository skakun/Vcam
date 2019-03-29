#ifndef VCAM_SOLID_H
#define VCAM_SOLID_H

#pragma once
#include <memory>
#include <vector>
#include "Edge.h"
#include "../Utils.h"

using namespace std;
class Solid
{
    private:
        vector<shared_ptr<_3dvec>> nodes;
public:
     vector<shared_ptr<_3dvec>> &getNodes() ;

    void setNodes(const vector<shared_ptr<_3dvec>> &nodes);

private:

    const vector<_3dedge> &getEdges() const;

    void setEdges(const vector<_3dedge> &edges);

private:
    vector<_3dedge> edges;
    public:
        void addEdge(_3dvec n1,_3dvec n2);
        void addNode(_3dvec n);
        ~Solid();

};

#endif //VCAM_SOLID_H
