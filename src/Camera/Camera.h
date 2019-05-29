#pragma once
#include "../Figure/Figure.h"
#include <memory>

class Camera
{
    t_3dvec position;
    t_3dvec orientation;
    t_3dvec displ_pos;
	double AOV=2.96706;//170°
	double frameRatio=1;
	t_3dvec startSightCorners[4];
public:
     t_3dvec &getPosition() ;

     const t_3dvec &getPosition_const() const;
	double minDispX,maxDispX,minDispY,maxDispY;
    void setPosition(const t_3dvec &position);

    t_3dvec &getOrientation();

    void setOrientation(const t_3dvec &orientation);

    t_3dvec &getDispl_pos() ;

    void setDispl_pos(const t_3dvec &displ_pos);
    double& getAOV();
	double& getFrameRatio();	
    Camera(t_3dvec position,t_3dvec orientation,t_3dvec displ_pos,	double minDispX=0,double maxDispX=800,double minDispY=0,double maxDispY=600);

};

