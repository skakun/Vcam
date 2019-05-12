#pragma once
#include <memory>
#include <vector>
#include "t_3dvec.h"
#include "t_Edge.h"
#include "t_Wall.h"
#include <algorithm>
using namespace std;
class Figure
{
private:
        vector<shared_ptr<t_3dvec>> nodes;
        vector<shared_ptr<t_Edge>> edges;
        vector<t_Wall> walls;
public:
		vector<shared_ptr<t_Edge>> &getEdges() ;
		vector<t_Wall> &getWalls() ;
		const vector<t_Wall> &const_getWalls() const ;
		vector<shared_ptr<t_3dvec>> &getNodes() ;
		const vector<shared_ptr<t_3dvec>> &const_getNodes() const ;
		void setNodes(const vector<shared_ptr<t_3dvec>> &nodes);
		void gatherEdgesFromWalls();
		void addNode(t_3dvec * n);
		shared_ptr<t_3dvec> getRoutedNode(int route_id);
		void print_edges();
		void cleanOprhanedEdges();
		void cleanOrphanedNodes();
		Figure(const Figure & toCopy);
		Figure();
		~Figure();

};
