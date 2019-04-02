//
//

#ifndef VCAM_CAMERA_H
#define VCAM_CAMERA_H

#include "../Figure/Figure.h"
#include <memory>

class Camera
{
    t_3dvec position;
    t_3dvec orientation;
    t_3dvec displ_pos;
public:
    const t_3dvec &getPosition() const;

    void setPosition(const t_3dvec &position);

    const t_3dvec &getOrientation() const;

    void setOrientation(const t_3dvec &orientation);

    const t_3dvec &getDispl_pos() const;

    void setDispl_pos(const t_3dvec &displ_pos);

    Camera(t_3dvec position,t_3dvec orientation,t_3dvec displ_pos);
};


#endif //VCAM_CAMERA_H
