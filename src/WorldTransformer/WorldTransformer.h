//
//

#ifndef VCAM_WORLDTRANSFORMER_H
#define VCAM_WORLDTRANSFORMER_H

#include "../Camera/Camera.h"
#include "../Figure/Figure.h"
#include "../Figure/t_World.h"
#include  <eigen3/Eigen/Dense>
#include <memory>
#include <algorithm>
#include <iterator>
#define INF (unsigned)!((int)0)

using namespace std;
using namespace Eigen;
class WorldTransformer
{
public:
    static void changeCordSys(vector<Figure> &world, t_3dvec zeroPoint);

    static t_World project( t_World world,Camera& cam);
	static bool crossEdges2d(t_Edge e1, t_Edge e2,t_3dvec ** crossPoint,bool prolong);
	static double crossProduct2d(Vector2d U,Vector2d V);
	static double crossProduct2d(t_3dvec U,t_3dvec V);
	static bool splitEdge(t_Edge e1,t_Edge e2, t_Edge * split);
	static bool pBelongsToWall(t_3dvec& p,t_Wall& wall);
	static bool isOnRight(t_3dvec &point,t_Edge &edge);
	static t_3dvec intersection(t_Edge &v1,t_Edge &v2);
	static t_3dvec intersection(double x1,int y1,double x2,double y2,double x3, double y3,double x4,double y4);
	static double crossProduct22(t_3dvec& p,t_Edge& e);
	static void clip(t_Wall &wall, t_Edge edge,std::vector<shared_ptr<t_3dvec>> nodeContext );
	static void suthHoClip(t_World &world , t_Wall frame);
	static void splitRectWalls(t_World & oldWorld,t_World &newWorld, int steps,double eps);
	static void convexToTriangles( t_World & outputWorld);
};
#endif //VCAM_WORLDTRANSFORMER_H
