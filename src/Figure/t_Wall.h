//
//

#ifndef VCAM_T_WALL_H
#define VCAM_T_WALL_H

#include <vector>
#include <memory>
#include "t_Edge.h"

using namespace std;
typedef struct {
    vector<shared_ptr<t_Edge> >edges;
}t_Wall;
#endif //VCAM_T_WALL_H
