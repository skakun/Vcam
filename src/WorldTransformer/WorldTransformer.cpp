//
//

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
    }
    return  world;
}
