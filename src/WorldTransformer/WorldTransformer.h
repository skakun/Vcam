//
//

#ifndef VCAM_WORLDTRANSFORMER_H
#define VCAM_WORLDTRANSFORMER_H

#include "../Camera/Camera.h"
#include "../Figure/Figure.h"
#include  <eigen3/Eigen/Dense>
#include <memory>


using namespace std;
using namespace Eigen;
class WorldTransformer
{
public:
    static void changeCordSys(vector<Figure> &world, t_3dvec zeroPoint);

    static vector<Figure> project(vector<Figure> world,Camera& cam);
};
#endif //VCAM_WORLDTRANSFORMER_H
