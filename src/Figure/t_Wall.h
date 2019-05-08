#pragma once
#include <vector>
#include <memory>
#include "t_Edge.h"

using namespace std;
typedef struct t_Wall{
		vector<int> signatures;
    vector<shared_ptr<t_Edge> >edges;
}t_Wall;
