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

int ScoreManager::getTaskScore(int level) {
    return 1000 * (1 + level) * level/2;
}
