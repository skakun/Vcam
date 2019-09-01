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
				/*
				for(auto  node : to_copy.nodes)
				{
		//				nodes.emplace_back(make_shared<t_3dvec>(node->x,node->y,node->z));
						nodes.emplace_back(make_shared<t_3dvec>(node->x,node->y,node->z,node->route_id));
				}
				*/
				for(auto  wall:to_copy.walls)
				{
						t_Wall n_wall;
						for(int i=0;i<3;i++)
								n_wall.color[i]=wall.color[i];
						n_wall.signatures=wall.signatures;
						for (auto & edge :wall.edges)
						{
						//		n_wall.edges.emplace_back(make_shared<t_Edge>(nodes[edge->n1->route_id],nodes[edge->n2->route_id]));
							//	n_wall.edges.emplace_back(make_shared<t_Edge>(new t_3dvec(edge->n1),new t_3dvec(edge->n2)));
								shared_ptr<t_3dvec> n1=make_shared<t_3dvec>(*edge->n1);
								shared_ptr<t_3dvec> n2=make_shared<t_3dvec>(*edge->n2);
								nodes.push_back(n1);
								nodes.push_back(n2);
								n_wall.edges.emplace_back(make_shared<t_Edge>(n1,n2));

						}
						walls.push_back(n_wall);
//						grabNodes(n_wall);
				}
				
		}
		void grabNodes(t_Wall & wall)
		{
				for(auto it=wall.edges.begin();it<wall.edges.end();it++)
				{
						nodes.push_back((*it)->n1);
						cout<<"grabbed:"<<(*it)->toString()<<endl;
				}
		}
} t_World;
