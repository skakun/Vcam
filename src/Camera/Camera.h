//
//

#ifndef VCAM_CAMERA_H
#define VCAM_CAMERA_H

#include "../Solid/Edge.h"
#include <memory>

class Camera
{
    _3dvec position;
    _3dvec orientation;
    _3dvec displ_pos;
public:
    const _3dvec &getPosition() const;

    void setPosition(const _3dvec &position);

    const _3dvec &getOrientation() const;

    void setOrientation(const _3dvec &orientation);

    const _3dvec &getDispl_pos() const;

    void setDispl_pos(const _3dvec &displ_pos);

    Camera(_3dvec position,_3dvec orientation,_3dvec displ_pos);
};


#endif //VCAM_CAMERA_H
