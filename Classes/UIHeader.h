//
//  UIHeader.h
//
//  Created by lxp on 15-5-1.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/UIWidget.h"

//////////////////////////////////////////////////  前置声明

namespace cocos2d {
namespace ui {
    class Button;
    class ImageView;
    class Text;
    class TextField;
    class ScrollView;
    class Layout;
    class LoadingBar;
	class ListView;
    class CheckBox;
    class ListView;
    class PageView;
    class RichText;
}
    
namespace extension {
    class EditBox;
    class EditBoxDelegate;
}
}

namespace cocostudio {
    class Armature;
    class ArmatureAnimation;
    class Bone;
}

enum class TouchEventType;

//////////////////////////////////////////////////  命名空间

using std::shared_ptr;
using std::make_shared;
using std::function;
using std::vector;
using std::deque;
using std::map;
using std::string;
using std::size_t;

using namespace cocos2d;
using namespace ui;
using extension::EditBox;
using extension::EditBoxDelegate;
using cocostudio::ArmatureAnimation;
using cocostudio::Armature;
using cocostudio::Bone;

#define xScheduler      Director::getInstance()->getScheduler()
