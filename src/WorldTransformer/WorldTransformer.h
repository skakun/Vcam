//
//

#ifndef VCAM_WORLDTRANSFORMER_H
#define VCAM_WORLDTRANSFORMER_H

#include "../Camera/Camera.h"
#include "../Figure/Figure.h"
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
};
#endif //VCAM_WORLDTRANSFORMER_H
