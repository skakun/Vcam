#include"ConeLightSource.h"
ConeLightSource::ConeLightSource(t_3dvec orientation,t_3dvec position, double maxIntensity)
{
		this->orientation=orientation;
		this->position=position;
		this->maxIntensity=maxIntensity;
}
double ConeLightSource::getDist(t_3dvec& v)
{
		return (v-position).norm();
}
double ConeLightSource::cosPropagate(t_3dvec& pos)
{
		t_3dvec v=pos-position;
		double cosalpha=v*orientation/v.norm()/orientation.norm();
		cosalpha=cosalpha;
		return maxIntensity*abs(cosalpha); 
}
