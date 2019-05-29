#pragma once
#include "t_3dvec.h"
#include <memory>
using namespace std;
typedef struct  t_Edge{
    shared_ptr<t_3dvec> n1;
    shared_ptr<t_3dvec> n2;
	t_Edge()
	{
			;
	}
    t_Edge(shared_ptr<t_3dvec> n1, shared_ptr<t_3dvec> n2)
    {
            this->n1=n1;
            this->n2=n2;
    }
	t_Edge valCopy()
	{
			return t_Edge( std::make_shared<t_3dvec>(n1->x,n1->y, n1->z),
							std::make_shared<t_3dvec>(n2->x,n2->y,n2->z));



	}
    string toString()
    {
        return n1->toString()+"\t=>\t"+n2->toString()+"\n";
    }
	t_3dvec extPoint(double val, int pos)
	{
			double t=(val-(*n1)[pos])/ (*n2)[pos];
			return t_3dvec(n1->x+t*n2->x,n1->y+t*n2->y,n1->z+t*n2->z);
	}
	t_3dvec diff()
	{
			return *n1-*n2;
	}
	t_3dvec getVec()
	{
			return t_3dvec(n2->x-n1->x,n2->y-n1->y,n2->z-n1->z);
	}

}t_Edge;
inline bool operator ==(const t_Edge& lhs, const t_Edge& rhs)
{
        return (lhs.n1==rhs.n1 &&lhs.n2==rhs.n2)||(lhs.n1==rhs.n2 &&lhs.n2==rhs.n1);
}
typedef std::shared_ptr<t_Edge> p_Edge;
