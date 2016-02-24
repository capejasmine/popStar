//
//  SingleTon.hpp
//  popStar
//
//  Created by huangwen on 16/2/24.
//
//

#ifndef SingleTon_hpp
#define SingleTon_hpp

#include <stdio.h>

template<class T>
class SingleTon
{
public:
    virtual ~SingleTon(){}
    
    static T* getInstace()
    {
        static T instance;
        return &instance;
    }
private:
};

#endif /* SingleTon_hpp */
