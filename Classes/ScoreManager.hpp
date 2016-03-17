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
    // score
    void initScore();
    
    void resetScore();
    
    void saveScore();
    
    void addScore(int pair);
    
    int getScore();
    
    int getTaskScore();
    
    void settlementScore(int count);
    
    //level
    
    void initLevel();
    
    void resetLevel();
    
    int  getLevel();
    
    void addLevel();
    
private:
    
    int m_score;
    
    int m_level;
};

#endif /* ScoreManager_hpp */
