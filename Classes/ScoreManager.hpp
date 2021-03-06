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
    
    void setBestScore(int score);
    
    int  getBestScore();
    
    //level
    
    void initLevel();
    
    void resetLevel();
    
    int  getLevel();
    
    void addLevel();
    
    // return preSocre and preLevel
    
    void resetPreScoreAndLevel();
    
private:
    int m_PreScore;
    
    int m_PreLevel;
    
    int m_score = 0;
    
    float m_level = 1;
};

#endif /* ScoreManager_hpp */
