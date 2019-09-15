#include <iostream>
#include "WorldTransformer.h"

void WorldTransformer::project(t_World &world,Camera& cam)
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
         double bx=cam.getDistToDiplPlaneComponents().z/r(2,0)*r(0,0)+cam.getDistToDiplPlaneComponents().x ;
          double by=cam.getDistToDiplPlaneComponents().z/r(2,0)*r(1,0)+cam.getDistToDiplPlaneComponents().y;
           node->x=bx;
           node->y=by;
           node->z=0;
//		   return world;
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

void WorldTransformer::triangulWorld(t_World & world,int steps)
{
		t_VVV nwalls,nnwalls;
		std::vector<t_Edge> nedges;
		std::vector<std::array<int,3>> colors;
		for(auto & wall:world.walls)
		{
				p_3dvec mid=std::make_shared<t_3dvec>(wall.mid());
				p_3dvec color=std::make_shared<t_3dvec>(t_3dvec(wall.color[0],wall.color[1],wall.color[2]));
				world.nodes.push_back(mid);
				
				for(auto & edge :wall.edges)
				{
						t_VV triangle={};
						triangle.push_back(edge->n1);
						triangle.push_back(mid);
						triangle.push_back(edge->n2);
						triangle.push_back(color);
						nwalls.push_back(triangle);
				}

		}
		for(int i=0;i<steps;i++)
		{
				for(auto & nn:nwalls)
				{
						p_3dvec mid=std::make_shared<t_3dvec>(t_3dvec::mid(nn,1));
						world.nodes.push_back(mid);
						nnwalls.push_back(t_VV{nn[0],mid,nn[1],nn[3]});
						nnwalls.push_back(t_VV{nn[1],mid,nn[2],nn[3]});
						nnwalls.push_back(t_VV{nn[0],mid,nn[2],nn[3]});
				}
				nwalls=nnwalls;
		}
		int j=0;
		world.walls.clear();
		for( auto & triangle:nwalls)
		{
	//			rep_walls.emplace_back(triangle,colors[i].data());
				p_3dvec pcolor=triangle.back();
				triangle.pop_back();
				int color[3];
				color[0]=(int)pcolor->x;
				color[1]=(int)pcolor->y;
				color[2]=(int)pcolor->z;
				world.walls.emplace_back(triangle,color);
		}

}
t_3dvec WorldTransformer::sphericalToCart(double r, double theta, double phi, t_3dvec mid)
{
		//remove
		double x=r*sin(theta)*cos(phi);
		double y=r*sin(theta)*sin(phi);
		double z=r*cos(theta);
		return t_3dvec(x,y,z)+mid;
}
void WorldTransformer::aproxBall(t_World & world,t_Ball & ball,int step)
{
		double dt=2*M_PI/step;
		double dp=2*M_PI/step;
		std::cout<<"dt:"<<dt<<endl;
		std::cout<<"dp:"<<dp<<endl;
		double phi;
		double theta;
		int color[]={ball.r,ball.g,ball.b};
		for(phi=0;phi<2*M_PI;phi+=dp)
		{	
				for(theta=0;theta<2*M_PI;theta+=dt)
				{
						vector<t_3dvec> newSquare=
						{
								sphericalToCart(ball.radius, theta, phi,ball.mid),
								sphericalToCart(ball.radius, theta +dt, phi,ball.mid),
								sphericalToCart(ball.radius, theta +dt, phi +dp,ball.mid),
								sphericalToCart(ball.radius, theta, phi +dp,ball.mid)

						};
						t_Wall nwall=t_Wall(newSquare,color);
						std::cout<<"pushed wall"<<endl;
						world.walls.push_back(nwall);
//						world.grabNodes(nwall);

				}
				
		}

}
void WorldTransformer::aproxBallColorfull(t_World & world,t_Ball & ball,int step)
{
		/*
		double dt=2*M_PI/step;
		double dp=2*M_PI/step;
		std::cout<<"dt:"<<dt<<endl;
		std::cout<<"dp:"<<dp<<endl;
		double phi;
		double theta;
		int color[]={ball.r,ball.g,ball.b};
		for(phi=0;phi<2*M_PI;phi+=dp)
		{	
				for(theta=0;theta<2*M_PI;theta+=dt)
				{
						vector<t_3dvec> newSquare=
						{
								sphericalToCart(ball.radius, theta, phi,ball.mid),
								sphericalToCart(ball.radius, theta +dt, phi,ball.mid),
								sphericalToCart(ball.radius, theta +dt, phi +dp,ball.mid),
								sphericalToCart(ball.radius, theta, phi +dp,ball.mid)

						};
						t_ColorfullWall nwall=t_ColorfullWall(newSquare,color);
						std::cout<<"pushed wall"<<endl;
						world.walls.push_back(nwall);
						world.grabNodes(nwall);

				}
				
		}
		*/

}
