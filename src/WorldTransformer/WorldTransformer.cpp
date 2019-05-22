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
void WorldTransformer::clip(t_Wall &wall, t_Edge edge,std::vector<shared_ptr<t_3dvec>> nodeContext )
{
		std::vector<shared_ptr<t_3dvec>> newPoints;	
		for(auto  it=wall.edges.begin();it<wall.edges.end();it++)
		{
				shared_ptr<t_3dvec> currentPoint=(*it)->n1;
				shared_ptr<t_3dvec> nextPoint=(*it)->n2;
				t_Edge e(currentPoint,nextPoint);
				double side=crossProduct22(*currentPoint.get(),edge);
				double side1=crossProduct22(*nextPoint.get(),edge);
				if(side <0 && side1 <0)
				{
						newPoints.push_back(nextPoint);
				}
				else if(side >=0 && side1<0)
				{
						shared_ptr<t_3dvec> npoint;
						newPoints.push_back(npoint=std::make_shared<t_3dvec>(intersection(edge,e)));
						nodeContext.push_back(npoint);
						newPoints.push_back(nextPoint);
				}
				else if(side <0 && side1>=0)
				{
						shared_ptr<t_3dvec> npoint;
						newPoints.push_back(npoint=std::make_shared<t_3dvec>(intersection(edge,e)));
						nodeContext.push_back(npoint);
				}
		}
		wall=t_Wall(newPoints,wall.color);
}
void WorldTransformer::suthHoClip(t_World &world , t_Wall & frame)
{
		for (t_Wall & wall :world.walls)
		{
				for(auto & edge:frame.edges)
				{
						clip(wall,*edge,world.nodes);
				}
		}
}
void WorldTransformer::triangul(t_VV & input,t_VVV &output)
{
		p_3dvec mid=make_shared<t_3dvec>((*input[0]+*input[1]+*input[2])/3);
		output.push_back(t_VV {input[0],input[1],mid});
		output.push_back(t_VV {input[1],input[2],mid});
		output.push_back(t_VV {input[2],input[0],mid});
}
void WorldTransformer::triangul(t_VVV & input,t_VVV & output)
{
		for(t_VV &triangle :input)
		{
				triangul(triangle, output);
		}
}
void WorldTransformer::triangul(t_Wall & wall,t_VVV &output)
{
		p_3dvec mid=make_shared<t_3dvec>(wall.mid());
		cout<<"mid:"<<mid->toString()<<endl;
		for ( p_Edge edge:wall.edges)
		{
				output.push_back(t_VV {edge->n1,mid,edge->n2});

		}
}
void WorldTransformer::triangulWorld(t_World & world,int steps)
{
    t_World nworld;
	for(t_Wall & wall:world.walls)	
	{
		t_VVV output;
		triangul(wall,output);
		for(int i=0;i<steps;i++)
		{
				t_VVV noutput;
				triangul(output,noutput);
				output=noutput;
		}
		for(t_VV & triangle:output)
		{
				nworld.walls.emplace_back(triangle,wall.color);
		}
	}
	world=nworld;
}
