//
//  ScoreManager.cpp
//  popStar
//
//  Created by huangwen on 16/3/14.
//
//

#include "ScoreManager.hpp"
#include "Appconfig.hpp"

void ScoreManager::resetScore() {
    m_score = 0;
    xUser->setIntegerForKey(POPSTAR_SCORE, m_score);
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
    return xUser->getIntegerForKey(POPSTAR_SCORE);
}

