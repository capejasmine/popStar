//
//  ScoreManager.hpp
//  popStar
//
//  Created by huangwen on 16/3/14.
//
//

#ifndef ScoreManager_hpp
#define ScoreManager_hpp
#define xUser       UserDefault::getInstance()
#define xScor       ScoreManager::getInstace()

#include "SingleTon.hpp"
#include "cocos2d.h"

USING_NS_CC;

class ScoreManager : public SingleTon<ScoreManager>,public Ref{
public:
    void initScore();
    
    void resetScore();
    
    void saveScore();
    
    void addScore(int pair);
    
    int getScore();
    
    int getTaskScore(int level);
private:
    
    int m_score;
    
};

#endif /* ScoreManager_hpp */
