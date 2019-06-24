#pragma once
#include "t_Wall.h"
#include <vector>
#include<memory.h>
#include <initializer_list>
#include<tuple>
typedef struct t_World
{
		std::vector<t_Wall> walls;
		std::vector<std::shared_ptr<t_3dvec>> nodes;
		t_World()
		{
		}
t_World (const t_World & to_copy)
{
		for(auto  node : to_copy.nodes)
		{
//				nodes.emplace_back(make_shared<t_3dvec>(node->x,node->y,node->z));
				nodes.emplace_back(make_shared<t_3dvec>(node->x,node->y,node->z,node->route_id));
		}
		for(auto  wall:to_copy.walls)
		{
				t_Wall n_wall;
				for(int i=0;i<3;i++)
						n_wall.color[i]=wall.color[i];
				n_wall.signatures=wall.signatures;
				for (auto & edge :wall.edges)
				{
						n_wall.edges.emplace_back(make_shared<t_Edge>(nodes[edge->n1->route_id],nodes[edge->n2->route_id]));
				}
				walls.push_back(n_wall);
		}
		
}
} t_World;
