#include"../../Figure/t_3dvec.h"
typedef struct t_EnlightNode:t_3dvec
{
		t_3dvec color;
		t_EnlightNode(t_3dvec base,t_3dvec color)
		{
				x=base.x;
				y=base.y;
				z=base.z;
				this->color=color;
		}
} t_EnlightNode;
