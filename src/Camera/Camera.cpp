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
double& Camera::getAOV()
{
		return AOV;
}
double & Camera::getFrameRatio()
{
		return frameRatio;
}
float & Camera::getDisplPosDistance()
{
		return displPosDistance;
}
t_3dvec Camera::getDistToDiplPlaneComponents()
{
		t_3dvec normalVec;
		normalVec.x=displPosDistance*cos(orientation.x);
		normalVec.y=displPosDistance*cos(orientation.y);
		normalVec.z=displPosDistance*cos(orientation.z);
		return normalVec;
}
t_Plane Camera::getDisplPlane()
{
		t_3dvec normalVec=getDistToDiplPlaneComponents();
		t_3dvec pointOnPlane=normalVec+position;
		double d=-(normalVec*pointOnPlane);
		return t_Plane(normalVec,d);
}
void Camera::changeDisplPosDistance(double d)
{
		displPosDistance+=d;
}
