#pragma once
#include"../Figure/t_3dvec.h"
typedef struct t_ColorfullNode:t_3dvec
{
		t_3dvec color;
		t_ColorfullNode(t_3dvec base,t_3dvec color)
		{
				x=base.x;
				y=base.y;
				z=base.z;
				this->color=color;
		}
		t_ColorfullNode(t_3dvec base,int* color)
		{
				x=base.x;
				y=base.y;
				z=base.z;
				this->color.x=color[0];
				this->color.y=color[1];
				this->color.z=color[2];
		}
		virtual bool isColorfull() override 
		{
				return true;
		}
		
} t_ColorfullNode;
