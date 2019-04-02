//
//

#ifndef VCAM_EDGE_H
#define VCAM_EDGE_H

#include "t_3dvec.h"
#include <memory>
using namespace std;
typedef struct  t_Edge{
    shared_ptr<t_3dvec> n1;
    shared_ptr<t_3dvec> n2;
    t_Edge(shared_ptr<t_3dvec> n1, shared_ptr<t_3dvec> n2)
    {
            this->n1=n1;
            this->n2=n2;
    }
}t_Edge;
inline bool operator ==(const t_Edge& lhs, const t_Edge& rhs)
{
        return (lhs.n1==rhs.n1 &&lhs.n2==rhs.n2)||(lhs.n1==rhs.n2 &&lhs.n2==rhs.n1);
}
#endif //VCAM_EDGE_H
