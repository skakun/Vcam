//
//

#include "Camera.h"

const t_3dvec &Camera::getPosition() const
{
    return position;
}

void Camera::setPosition(const t_3dvec &position)
{
    Camera::position = position;
}

const t_3dvec &Camera::getOrientation() const
{
    return orientation;
}

void Camera::setOrientation(const t_3dvec &orientation)
{
    Camera::orientation = orientation;
}

const t_3dvec &Camera::getDispl_pos() const
{
    return displ_pos;
}

void Camera::setDispl_pos(const t_3dvec &displ_pos)
{
    Camera::displ_pos = displ_pos;
}

Camera::Camera(t_3dvec position, t_3dvec orientation, t_3dvec displ_pos)
{
    this->position=position;
    this->orientation=orientation;
    this->displ_pos=displ_pos;
}
