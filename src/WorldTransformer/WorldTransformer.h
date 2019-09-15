#pragma once
#include "../Camera/Camera.h"
#include "../Figure/Figure.h"
#include "../Figure/t_World.h"
#include  <eigen3/Eigen/Dense>
#include <memory>
#include <algorithm>
#include <iterator>
#include <tuple>
#include <array>
#include <vector>
#include <cmath>
#include "../Figure/t_Ball.h"
//#include "../ColorfullFigure/ColorfullNode.h"
//#include "../ColorfullFigure/ColorfullWall.h"
//#define INF (unsigned)!((int)0)
using namespace std;
using namespace Eigen;
class WorldTransformer
{
public:
    static void changeCordSys(vector<Figure> &world, t_3dvec zeroPoint);

    static void project( t_World  & world,Camera& cam);
	static double crossProduct2d(Vector2d U,Vector2d V);
	static double crossProduct2d(t_3dvec U,t_3dvec V);
	static t_3dvec intersection(t_Edge &v1,t_Edge &v2);
	static t_3dvec intersection(double x1,int y1,double x2,double y2,double x3, double y3,double x4,double y4);
	static double crossProduct22(t_3dvec& p,t_Edge& e);
	static void clip(t_Wall &wall, t_Edge edge,std::vector<shared_ptr<t_3dvec>> nodeContext );
	static void convexToTriangles( t_World & outputWorld);
	static void triangulWorld(t_World & world,int steps);
	static t_3dvec sphericalToCart(double r, double theta, double phi,t_3dvec mid);
	static void aproxBall(t_World & world,t_Ball &ball,int step);
	static void aproxBallColorfull(t_World & world,t_Ball &ball,int step);
};
