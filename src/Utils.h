//
//

#ifndef VCAM_UTILS_H
#define VCAM_UTILS_H

#include <vector>
#include <math.h>
using namespace std;
class Utils
{
public:
    template <class  T,class U>
    static T *getMatchInVec(vector<T> vec,T elem);
};

template<class T,class U>
T *Utils::getMatchInVec(vector <T> vec, T elem)
{
    auto ret= nullptr;
    for (auto it=vec.begin();it!=vec.end();++it )
    {
        if(*it==elem)
            ret=&(*it);
    }
}
void trimAngle(double &a)
{
		while(a>2*M_PI) a-=2*M_PI;
		while(a<-2*M_PI) a+=2*M_PI;
}
bool getBit(int n,int pos)
{
		return (n>>pos)&0x1;
}
#endif //VCAM_UTILS_H
