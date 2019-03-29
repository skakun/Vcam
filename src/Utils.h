//
//

#ifndef VCAM_UTILS_H
#define VCAM_UTILS_H

#include <vector>

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


#endif //VCAM_UTILS_H
