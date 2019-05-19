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

    static vector<Figure> project(vector<Figure> world,Camera& cam);
    static t_World project( t_World  world,Camera& cam);
	static void limitToFront(Figure & fig);
	static void trimEdge(Figure &fig,t_Edge edge);
    static void trimOffscreenEdges(Camera &cam,Figure& fig);
	static bool crossEdges2d(t_Edge e1, t_Edge e2,t_3dvec ** crossPoint,bool prolong);
	static double crossProduct2d(Vector2d U,Vector2d V);
	static double crossProduct2d(t_3dvec U,t_3dvec V);
	static bool splitEdge(t_Edge e1,t_Edge e2, t_Edge * split);
	static bool pBelongsToWall(t_3dvec& p,t_Wall& wall);
	static void suthHoClip(t_Wall & subject, t_Wall & frame ,Figure & context);
	static bool isOnRight(t_3dvec &point,t_Edge &edge);
	static t_3dvec intersection(t_Edge &v1,t_Edge &v2);
	static t_3dvec intersection(double x1,int y1,double x2,double y2,double x3, double y3,double x4,double y4);
	static double crossProduct22(t_3dvec& p,t_Edge& e);
	static void clip(t_Wall &wall, t_Edge edge);
	static void suthHodgClip(Figure& fig,t_Wall& frame );
	static void splitRectWalls(t_World & oldWorld,t_World &newWorld, int steps,double eps);
};
#endif //VCAM_WORLDTRANSFORMER_H
