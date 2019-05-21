#pragma once
#include <vector>
#include <memory>
#include "t_Edge.h"

using namespace std;
typedef struct t_Wall{
		vector<int> signatures;
    vector<shared_ptr<t_Edge>>edges;
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
	t_3dvec mid() const
	{
			t_3dvec ret;
			for(auto  edge =edges.begin();edge<edges.end(); edge++)
			{
					ret+= *(*edge)->n1;

			}
			return ret/edges.size();
	}
		t_Wall(std::initializer_list<t_3dvec> nodes)
		{
				for(auto   it=nodes.begin();it<nodes.end();it++)
				{
						shared_ptr<t_3dvec> current=std::make_shared<t_3dvec>(*it);
						shared_ptr<t_3dvec> next=std::make_shared<t_3dvec>( *(it==nodes.end()-1?nodes.begin():it+1));
						edges.emplace_back(new t_Edge(current,next));
				}
		}
		t_Wall(std::vector<shared_ptr<t_3dvec>> nodes)
		{
				for(auto   it=nodes.begin();it<nodes.end();it++)
				{
						shared_ptr<t_3dvec> current=*it;
						shared_ptr<t_3dvec> next=*(it==nodes.end()-1?nodes.begin():it+1);
						edges.emplace_back(new t_Edge(current,next));
				}
		}
		t_Wall(std::vector<shared_ptr<t_3dvec>> nodes, int * color):t_Wall(nodes)
		{
				for(int i=0;i<3;i++)
						this->color[i]=color[i];
		}
		t_Wall(std::initializer_list<shared_ptr<t_3dvec>> nodes)
		{

				signatures={};
				for(auto   it=nodes.begin();it<nodes.end();it++)
				{
						shared_ptr<t_3dvec> current=(*it);
						shared_ptr<t_3dvec> next=it+1==nodes.end()?*nodes.begin():*(it+1);
						edges.emplace_back(make_shared<t_Edge>(current,next));
				}
		}
		/*
		 t_Wall operator=(const t_Wall& wall)
		{
				for(auto& edge:wall.edges)
				{
						edges.push_back(edge);
				}
				signatures=wall.signatures;
				wall.signatures.clear();
				return *this;
		}
		t_Wall(t_Wall && wall)
		{
				for(auto& edge:wall.edges)
				{
						edges.emplace_back(edge);
				}
				wall.edges.clear();
				signatures=wall.signatures;
				wall.signatures.clear();

		}
		t_Wall(const t_Wall & wall)
		{
				for(auto& edge:wall.edges)
				{
						edges.push_back(edge);
				}
				signatures=wall.signatures;
				wall.signatures.clear();

		}
		*/
		/*
		t_Wall(const t_Wall & wall)
		{
				for(auto& edge:wall.edges)
				{
						edges.push_back(edge);
				}
				signatures=wall.signatures;

		}
		*/
	double dist(const t_3dvec& p)
	{
			return (mid()-p).norm();
	}
	t_Wall()
    {
			signatures={};
	}
}t_Wall;
