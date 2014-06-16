/******************************************************************************/
#ifndef _IINPUT_H_
#define _IINPUT_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //游戏输入主接口
    /******************************************************************************/
    class IInput
    {
    public:
    
        /// 是否键盘被按住
        virtual Bool isKeyHolded (KeyCode key) = 0;
        /// 是否键盘按下
        virtual Bool isKeyPressed(KeyCode key) = 0; 
        /// 是否键盘弹起
        virtual Bool isKeyReleased(KeyCode key) = 0;

        /// 是否左或右Ctrl键被按下
        virtual Bool isCtrlOn ()  = 0;
        /// 是否左或右Shift键被按下
        virtual Bool isShiftOn()  = 0;
        /// 是否左或右Alt键被按下
        virtual Bool isAltOn  ()  = 0;

    public:

        /// 得到鼠标屏幕中坐标
        virtual Vec2 getMousePos() = 0;
		/// 得到鼠标屏幕中坐标
		virtual Vec2 getMouseScreenPos() = 0;
        /// 得到鼠标移动间隔距离
        virtual Vec2 getMouseMoveDelta() = 0;
        
        /// 得到鼠标速度
        virtual Flt getMouseSpeed() = 0;
        /// 设置鼠标速度
        virtual void setMouseSpeed(Flt speed) = 0;

        /// 得到滚轮数据
        virtual Int getMouseWheel() = 0;
        /// 是否鼠标被按住
        virtual Bool isMouseHolded (MouseCode mouse) = 0;
        /// 是否鼠标按下
        virtual Bool isMousePressed(MouseCode mouse) = 0; 
        /// 是否鼠标弹起
        virtual Bool isMouseReleased(MouseCode mouse) = 0;
        /// 是否鼠标双击
        virtual Bool isMouseDoubleClicked(MouseCode mouse) = 0;

		//是否失去焦点
		virtual Bool isFocusLastFrame() = 0;

    };

}

/******************************************************************************/
#endif
