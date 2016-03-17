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
}

int ScoreManager::getScore() {
    return m_score;
}

int ScoreManager::getTaskScore() {
    return 1000 * (1 + m_level) * m_level/2;
}

void ScoreManager::settlementScore(int count) {
    m_score += 2000 - count * count * 20;
}

#pragma mark- Level

void ScoreManager::initLevel() {
    m_level = xUser->getIntegerForKey(POPSTAR_LEVEL, 1);
}

void ScoreManager::resetLevel() {
    xUser->setIntegerForKey(POPSTAR_LEVEL, 0);
    xUser->flush();
}

int  ScoreManager::getLevel() {
    return m_level;
}

void ScoreManager::addLevel() {
    m_level += 1;
    xUser->setIntegerForKey(POPSTAR_LEVEL, m_level);
    xUser->flush();
}


