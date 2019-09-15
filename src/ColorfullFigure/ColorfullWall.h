#pragma once
#include "../Figure/t_Wall.h"
typedef struct t_ColorfullWall : t_Wall
{
		virtual bool isColorfull() override
		{
				return true;
		}
}t_ColorfullWall

