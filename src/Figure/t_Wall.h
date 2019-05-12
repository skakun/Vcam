#pragma once
#include <vector>
#include <memory>
#include "t_Edge.h"

using namespace std;
typedef struct t_Wall{
		vector<int> signatures;
    vector<shared_ptr<t_Edge>>edges;
	vector<shared_ptr<t_3dvec>>nodes;
	std::string toString()
	{
			std::string ret;
			for(auto & edge:edges)
			{
				ret+=edge->toString();
			}
			return ret;
	}
	t_Wall(){;}
}t_Wall;
