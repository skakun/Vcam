#pragma once
#include <vector>
#include <memory>
#include "t_Edge.h"

using namespace std;
typedef struct t_Wall{
		vector<int> signatures;
    vector<shared_ptr<t_Edge>>edges;
	vector<shared_ptr<t_3dvec>>nodes;
	int color[3];
	std::string toString()
	{
			std::string ret;
			for(auto & edge:edges)
			{
				ret+=edge->toString();
			}
			return ret;
	}
	t_3dvec mid()
	{
			t_3dvec ret;
			for(auto  edge =edges.begin();edge<edges.end(); edge++)
			{
					ret+= *(*edge)->n1;
			}
			return ret/edges.size();
	}
	double dist(const t_3dvec& p)
	{
			return (mid()-p).norm();
	}
	t_Wall(){;}
}t_Wall;
