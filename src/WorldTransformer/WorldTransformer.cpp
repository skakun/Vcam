#include <iostream>
#include "WorldTransformer.h"

void WorldTransformer::changeCordSys(vector<Figure> &world, t_3dvec zeroPoint)
{
    for(auto& solid :world)
    {
        for(auto & node :solid.getNodes())
        {
            node->x-=zeroPoint.x;
            node->y-=zeroPoint.y;
            node->z-=zeroPoint.z;
        }
    }
}

vector<Figure> WorldTransformer::project(vector<Figure> world,Camera& cam)
{
    Matrix<double,3,3> l;
    Matrix<double,3,3> m;
    Matrix<double ,3,1>r;
	double tmp;
    for(auto &solid:world)
    {
        for (auto & node :solid.getNodes())
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
//		limitToFront(solid);
    }
    return  world;
}
void WorldTransformer::limitToFront(Figure & fig)
{
		for(auto & node:fig.getNodes())
		{
				if (node->x<0) node->x=0;
				if (node->y<0) node->y=0;
				if (node->z<0) node->z=0;
		}
}
void WorldTransformer::trimOffscreenEdges( Camera &cam,Figure & fig)
{
		double limits[]={cam.minDispX,cam.minDispY,-1,cam.maxDispX,cam.maxDispY,INF};
		for(auto & edge: fig.getEdges())
		{
				bool * n1_lim=edge->n1->checkLimitsOnPos(limits);
				bool * n2_lim=edge->n2->checkLimitsOnPos(limits);
				int n1_found,n2_found;;
				for (n1_found=0;n1_found<3;n1_found++)
						if(! n1_lim[n1_found]) break;
				for (n2_found=0;n2_found<3;n2_found++)
						if(! n2_lim[n2_found]) break;
				if(n1_found<3)
				{
						if(n2_found<3)
						{
				//				std::shared_ptr<
						}
				}
				delete[] n1_lim;
				delete[] n2_lim;
		}
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
void WorldTransformer::suthHoClip(t_Wall & subject, t_Wall & frame ,Figure & context)
{
		std::vector<shared_ptr<t_3dvec>> inputList;
		std::vector<shared_ptr<t_3dvec>> outputList=subject.nodes;
		int intersect_count=0;
		for (auto & clipEdge: frame.edges)
		{
				inputList=outputList;
				outputList.clear();
				for( int i=0;i<inputList.size();i++)
				{
						shared_ptr<t_3dvec> currentPoint=inputList[i];
						t_3dvec *crossPointRaw;
						shared_ptr<t_3dvec> crossPoint;
						shared_ptr<t_3dvec> prev_point=inputList[(i+inputList.size()-1)%inputList.size()];
						bool intersects=crossEdges2d(t_Edge(currentPoint,prev_point),*(clipEdge.get()),&crossPointRaw);
						if (intersects)
								crossPointRaw->route_id=(--intersect_count);

						if(isOnRight(*currentPoint.get(),*clipEdge.get()))
						{
								if(! isOnRight(*prev_point.get(),*clipEdge.get()))
								{
									outputList.emplace_back(crossPointRaw);	
								}
								else (outputList.push_back(currentPoint));
						}
						else if (isOnRight(*prev_point.get(),*clipEdge.get()))
								outputList.emplace_back(crossPointRaw);
				}
		}
		for(auto & edge: subject.edges)
		{
//				if(edge.count_use()<3) edge=nullptr;
				/* one for reference in Figure.nodes
				 * two for reference in subject.nodes
				 * three+ means some other wall uses is*/
				edge=nullptr;
				edge.reset();
		}
		subject=t_Wall();
		std::cout<<"======================================"<<std::endl;
		for(auto  it=outputList.begin();it<outputList.end();it++)
		{
				auto n1=*it;
				cout<<n1->toString()<<std::endl;
				auto n2=it+1==outputList.end() ? *outputList.begin() : *(it+1);//pseudo modulo to get next node
				subject.nodes.push_back(n1);
//				if(n1->route_id<0)
				context.getNodes().push_back(n1);
				subject.edges.emplace_back(new t_Edge(n1,n2));
				//if(n1.route_id<0;n1.route_id

		}

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
void WorldTransformer::clip(t_Wall &wall, t_Edge edge)
{
		std::vector<shared_ptr<t_3dvec>> newPoints;	
		for(auto  it=wall.nodes.begin();it<wall.nodes.end();it++)
		{
				shared_ptr<t_3dvec> currentPoint=*it;
				shared_ptr<t_3dvec> nextPoint= (it+1)== wall.nodes.end() ? *wall.nodes.begin() : *(it+1);
				t_Edge e(currentPoint,nextPoint);
				double side=crossProduct22(*currentPoint.get(),edge);
				double side1=crossProduct22(*nextPoint.get(),edge);
				if(side <0 && side1 <0)
				{
						newPoints.push_back(nextPoint);
				}
				else if(side >=0 && side1<0)
				{
						newPoints.push_back(std::make_shared<t_3dvec>(intersection(edge,e)));
						newPoints.push_back(nextPoint);
				}
				else if(side <0 && side1>=0)
				{
						newPoints.push_back(std::make_shared<t_3dvec>(intersection(edge,e)));
				}
		}
		wall.nodes=newPoints;
}
void WorldTransformer::suthHodgClip(Figure& fig,t_Wall& frame )
{
		for(auto & wall:fig.getWalls())
		{
				for(auto & edge:frame.edges)
				{
						clip(wall,*edge.get());
				}
				wall.edges.clear();
				shared_ptr<t_3dvec> cn,nn;
				for(auto it=wall.nodes.begin();it<wall.nodes.end();it++)
				{
						cn=*it;
						nn= it+1==wall.nodes.end() ? *wall.nodes.begin() : *(it+1);
						wall.edges.emplace_back(new t_Edge(cn,nn));
				}
		}
}

