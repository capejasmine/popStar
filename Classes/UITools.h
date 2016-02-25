#pragma once

#include "UIHeader.h"
#include "ui/UICheckBox.h"

namespace cocos2d
{
    namespace extension
    {
        class EditBoxDelegate;
    }
}


void quickBackToOriginal(Node * node, Vec2 &original);

bool quickIfAInB(Widget * a, Widget * b);
void quickSetLocalZOrder(Widget * widget, int localZOrder);
bool quickIsOutsideOfScreen(Widget * widget);
Vec2 rotateWithDegree(Vec2 &point, float fDegree);
int cycleNum(int iCount, bool bAdd, int *idx);
int quickRandom(int min, int max);
float quickRandomFloat(float min, float max);
