//
//

#include "Camera.h"

 t_3dvec &Camera::getPosition() 
{
    return position;
}

 const t_3dvec &Camera::getPosition_const() const
{
    return position;
}

void Camera::setPosition(const t_3dvec &position)
{
    Camera::position = position;
}

t_3dvec &Camera::getOrientation() 
{
    return orientation;
}

void Camera::setOrientation(const t_3dvec &orientation)
{
    Camera::orientation = orientation;
}

t_3dvec &Camera::getDispl_pos() 
{
    return displ_pos;
}

void Camera::setDispl_pos(const t_3dvec &displ_pos)
{
    Camera::displ_pos = displ_pos;
}

Camera::Camera(t_3dvec position,t_3dvec orientation,t_3dvec displ_pos,	double minDispX,double maxDispX,double minDispY,double maxDispY)
{
    this->position=position;
    this->orientation=orientation;
    this->displ_pos=displ_pos;
	this->maxDispX=maxDispX;
	this->minDispX=minDispX;
	this->minDispY=minDispY;
	this->maxDispY=maxDispY;
}
