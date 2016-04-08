//
//  NumberScroller.hpp
//  popStar
//
//  Created by huangwen on 16/4/7.
//
//

#ifndef NumberScroller_hpp
#define NumberScroller_hpp

#include "cocos2d.h"

USING_NS_CC;

class NumberScroller : public Node{
public :
    static NumberScroller* create(int level);
    
    virtual bool init();
    
    void setDigitalLevel(int level);
    
    void setFontSize(int size);
    
    void addNumber(int num);
    
    void setNumber(int tag, int time);
private:
    
    int m_level;
    
    int m_fontSize = 50;
    
    int m_mindiff = 10;
    
    int m_cur_num;
    
    std::vector<Node*> m_scroller;
};

#endif /* NumberScroller_hpp */
