//
//  ScoreManager.cpp
//  popStar
//
//  Created by huangwen on 16/3/14.
//
//

#include "ScoreManager.hpp"
#include "Appconfig.hpp"

void ScoreManager::initScore() {
    m_score = xUser->getIntegerForKey(POPSTAR_SCORE, 0);
    m_PreScore = m_score;
}

void ScoreManager::resetScore() {
    xUser->setIntegerForKey(POPSTAR_SCORE, 0);
    xUser->flush();
}

void ScoreManager::saveScore() {
    xUser->setIntegerForKey(POPSTAR_SCORE, m_score);
    xUser->flush();
}

void ScoreManager::addScore(int pair) {
    m_score += pair * pair * 5;
    
    log("score = %d",m_score);
}

int ScoreManager::getScore() {
    log("result socre = %d ", m_score);
    return m_score;
}

int ScoreManager::getTaskScore() {
    log("task socre = %f ",1000 * (1 + m_level) * m_level/2);
    return 1000 * (1 + m_level) * m_level/2;
}

void ScoreManager::settlementScore(int count) {
    if(count < 10)
    {
        m_score = m_score + (2000 - count * count * 20);
    }
    
//    m_PreScore = m_score;
}

#pragma mark- Level

void ScoreManager::initLevel() {
    m_level = xUser->getIntegerForKey(POPSTAR_LEVEL, 1);
    m_PreLevel = m_level;
}

void ScoreManager::resetLevel() {
    xUser->setIntegerForKey(POPSTAR_LEVEL, 1);
    xUser->flush();
}

int  ScoreManager::getLevel() {
    return m_level;
}

void ScoreManager::addLevel() {
    m_level += 1;
    xUser->setIntegerForKey(POPSTAR_LEVEL, m_level);
    xUser->flush();
    
    m_PreLevel = m_level;
}

#pragma mark- preScore and preLevel

void ScoreManager::resetPreScoreAndLevel() {
    xUser->setIntegerForKey(POPSTAR_SCORE, m_PreScore);
    xUser->setIntegerForKey(POPSTAR_LEVEL, m_PreLevel);
    xUser->flush();
}


