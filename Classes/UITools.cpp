//
//  UITools.cpp
//
//  Created by luoxp on 14-9-22.
//
//

#include "UITools.h"
#include "GUI/CCEditBox/CCEditBox.h"
#include <random>


void quickBackToOriginal(Node * node, Vec2 &original)
{
    FiniteTimeAction* action = EaseElasticOut::create(MoveTo::create(0.5f, original), 0.8f);
    node->runAction(action);
}

bool quickIfAInB(Widget * a, Widget * b)
{
    Vec2 pos = b->getWorldPosition();
    Size contentSize = b->getContentSize();
    
    Rect rect = Rect(pos.x - contentSize.width/2, pos.y - contentSize.height/2, contentSize.width, contentSize.height);
    if (rect.containsPoint(a->getWorldPosition()))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void quickSetLocalZOrder(Widget * widget, int localZOrder)
{
    widget->setLocalZOrder(localZOrder);
    widget->getVirtualRenderer()->setLocalZOrder(localZOrder);
}

bool quickIsOutsideOfScreen(Widget * widget)
{
    Size win = Director::getInstance()->getVisibleSize();
    Size size = widget->getContentSize();
    Vec2 pos = widget->getWorldPosition();
    
    //先检查x
    if (pos.x - size.width/2 < 0 || pos.x + size.width/2 > win.width) {
        return true;
    }
    else if (pos.y - size.height/2 < 0 || pos.y + size.height/2 > win.height)
    {
        return true;
    }
    
    return false;
}

Vec2 rotateWithDegree(Vec2 &point, float fDegree)
{
    //角度转弧度
    float angle = M_PI * fDegree /180;
    return point.rotateByAngle(Vec2::ZERO, angle);
}

int cycleNum(int iCount, bool bAdd, int *idx)
{
    if (bAdd == true)
    {
        if (*idx >= iCount - 1)
        {
            *idx = 0;
        }
        else
        {
            (*idx)++;
        }
    }
    else if (bAdd == false)
    {
        if ((*idx) <= 0)
        {
            (*idx) = iCount - 1;
        }
        else
        {
            (*idx)--;
        }
    }
    
    return (*idx);
}

int quickRandom(int min, int max)
{
    std::default_random_engine engine(std::random_device{}());
    std::uniform_int_distribution <> distribution(min, max);
    return distribution(engine);
}

float quickRandomFloat(float min, float max)
{
    std::default_random_engine engine(std::random_device{}());
    std::uniform_real_distribution <> distribution(min, max);
    return distribution(engine);
}

