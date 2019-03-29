//
//

#include "Camera.h"

const _3dvec &Camera::getPosition() const
{
    return position;
}

void Camera::setPosition(const _3dvec &position)
{
    Camera::position = position;
}

const _3dvec &Camera::getOrientation() const
{
    return orientation;
}

void Camera::setOrientation(const _3dvec &orientation)
{
    Camera::orientation = orientation;
}

const _3dvec &Camera::getDispl_pos() const
{
    return displ_pos;
}

void Camera::setDispl_pos(const _3dvec &displ_pos)
{
    Camera::displ_pos = displ_pos;
}

Camera::Camera(_3dvec position, _3dvec orientation, _3dvec displ_pos)
{
    this->position=position;
    this->orientation=orientation;
    this->displ_pos=displ_pos;
}
