#include <iostream>
#include "WorldTransformer.h"

t_World WorldTransformer::project(t_World world,Camera& cam)
{
    Matrix<double,3,3> l;
    Matrix<double,3,3> m;
    Matrix<double ,3,1>r;
	double tmp;
        for (auto & node : world.nodes)
        {
            m=Matrix<double ,3,3>::Identity();
            l=Matrix<double ,3,3>::Identity();
            l(1,1)=cos(cam.getOrientation().x);
            l(2,2)=l(1,1);
            l(1,2)=sin(cam.getOrientation().x);
            l(2,1)=-l(1,2);

            m(0,0)=cos(cam.getOrientation().y);
            m(2,2)=m(0,0);
            m(2,0)=sin(cam.getOrientation().y);
            m(0,2)=-m(2,0);
            l=l*m;

            m=Matrix<double ,3,3>::Identity();
            m(0,0)=cos(cam.getOrientation().z);
            m(1,1)=m(0,0);
            m(0,1)=sin(cam.getOrientation().z);
            m(1,0)=-m(0,1);
            l=l*m;
           r=Matrix<double,3,1>::Identity();
           r(0,0)=node->x-cam.getPosition().x;
            r(1,0)=node->y-cam.getPosition().y;
            r(2,0)=node->z-cam.getPosition().z;
           r=l*r;
          double bx=cam.getDispl_pos().z/r(2,0)*r(0,0)+cam.getDispl_pos().x ;
           double by=cam.getDispl_pos().z/r(2,0)*r(1,0)+cam.getDispl_pos().y;
        //double bx=r(0,0);
     //   double by=r(1,0); b
           node->x=bx;
           node->y=by;
           node->z=0;
        }
    return  world;
}
double WorldTransformer::crossProduct2d(Vector2d U,Vector2d V)
{
		return U[0]*V[1]-U[1]*V[0];
}
double WorldTransformer::crossProduct2d(t_3dvec U,t_3dvec V)
{
		return crossProduct2d( Vector2d(U.x,U.y),Vector2d(V.x,V.y));
}
bool WorldTransformer::crossEdges2d(t_Edge e1, t_Edge e2,t_3dvec ** crossPoint,bool prolong=false)
{
		Vector2d p(e1.n1->x,e1.n1->y),r(e1.getVec().x,e1.getVec().y),q(e2.n1->x,e2.n1->y),s(e2.getVec().x,e2.getVec().y),v0(0,0);
		if(crossProduct2d(r,s)==0) return false; //lets assume collinear dosen't count
		double t=crossProduct2d((q-p),s)/crossProduct2d(r,s);
		double u=crossProduct2d((q-p),r)/crossProduct2d(r,s);
		if( prolong&&(t<0 || t>1 || u<0 || u>1)) return false;
		*crossPoint=new t_3dvec(p[0]+t*r[0],p[1]+t*r[1],0);
		return true;
}
bool WorldTransformer::splitEdge(t_Edge e1,t_Edge e2, t_Edge * split)
{
		t_3dvec * crossPoint;
		if(crossEdges2d(e1,e2,&crossPoint))
		{
				split=new t_Edge[2];
				split[0]=t_Edge(e1.n1,std::shared_ptr<t_3dvec>(crossPoint));
				split[0]=t_Edge(split[0].n1,e1.n2);
				return true;
		}
		else return false;
}

bool WorldTransformer::isOnRight(t_3dvec &point,t_Edge &edge)
{
		return ! crossProduct2d(point,edge.getVec())>=0;
}
 t_3dvec WorldTransformer::intersection(t_Edge &v1,t_Edge &v2)
{
		return intersection(v1.n1->x,v1.n1->y,
						v1.n2->x,v1.n2->y,
						v2.n1->x,v2.n1->y,
						v2.n2->x,v2.n2->y);
}
t_3dvec WorldTransformer::intersection(double x1,int y1,double x2,double y2,double x3, double y3,double x4,double y4)
{
		double num=(x1*y2 - y1*x2) * (x3-x4) - 
              (x1-x2) * (x3*y4 - y3*x4);
		double den=(x1-x2) * (y3-y4) - (y1-y2) * (x3-x4); 
		double X=num/den;
		num=(x1*y2 - y1*x2) * (y3-y4) - 
              (y1-y2) * (x3*y4 - y3*x4);
		den=(x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
		double Y=num/den;
		return t_3dvec(X,Y,0,-1);
}
double WorldTransformer::crossProduct22(t_3dvec& p,t_Edge& e)
{
		return (e.n2->x-e.n1->x)*(p.y-e.n1->y)-(e.n2->y-e.n1->y)*(p.x-e.n1->x);
}


void WorldTransformer::convexToTriangles( t_World & outputWorld)
{
		std::vector<t_Wall> nwalls;
		for( auto & wall:outputWorld.walls)
		{
				shared_ptr<t_3dvec> middle =std::make_shared<t_3dvec>(wall.mid());
				outputWorld.nodes.push_back(middle);
				for(auto & edge: wall.edges)
				{
						nwalls.emplace_back(std::initializer_list<std::shared_ptr<t_3dvec>>{edge->n1,edge->n2,middle});
		//				outputWorld.nodes.push_back(edge->n1);
		//				outputWorld.edges.push_back(new_wall.edges.back());
						t_Wall * new_wall =&nwalls.back();
						new_wall->color[0]=wall.color[0];
						new_wall->color[1]=wall.color[1];
						new_wall->color[2]=wall.color[2];
						new_wall->signatures={};
				}
		}
//		outputWorld.walls.clear();
		outputWorld.walls=nwalls;
}
