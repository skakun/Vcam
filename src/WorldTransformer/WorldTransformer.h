//
//

#ifndef VCAM_WORLDTRANSFORMER_H
#define VCAM_WORLDTRANSFORMER_H

#include "../Solid/Solid.h"
#include "../Camera/Camera.h"
#include  <eigen3/Eigen/Dense>
#include <memory>


using namespace std;
using namespace Eigen;
class WorldTransformer
{
public:
    static void changeCordSys(vector<Solid> &world, _3dvec zeroPoint);

    static vector<Solid> project(vector<Solid> world,Camera& cam);
};
#endif //VCAM_WORLDTRANSFORMER_H
