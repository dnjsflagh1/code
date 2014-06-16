/******************************************************************************/
#ifndef _IINPUT_H_
#define _IINPUT_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //��Ϸ�������ӿ�
    /******************************************************************************/
    class IInput
    {
    public:
    
        /// �Ƿ���̱���ס
        virtual Bool isKeyHolded (KeyCode key) = 0;
        /// �Ƿ���̰���
        virtual Bool isKeyPressed(KeyCode key) = 0; 
        /// �Ƿ���̵���
        virtual Bool isKeyReleased(KeyCode key) = 0;

        /// �Ƿ������Ctrl��������
        virtual Bool isCtrlOn ()  = 0;
        /// �Ƿ������Shift��������
        virtual Bool isShiftOn()  = 0;
        /// �Ƿ������Alt��������
        virtual Bool isAltOn  ()  = 0;

    public:

        /// �õ������Ļ������
        virtual Vec2 getMousePos() = 0;
		/// �õ������Ļ������
		virtual Vec2 getMouseScreenPos() = 0;
        /// �õ�����ƶ��������
        virtual Vec2 getMouseMoveDelta() = 0;
        
        /// �õ�����ٶ�
        virtual Flt getMouseSpeed() = 0;
        /// ��������ٶ�
        virtual void setMouseSpeed(Flt speed) = 0;

        /// �õ���������
        virtual Int getMouseWheel() = 0;
        /// �Ƿ���걻��ס
        virtual Bool isMouseHolded (MouseCode mouse) = 0;
        /// �Ƿ���갴��
        virtual Bool isMousePressed(MouseCode mouse) = 0; 
        /// �Ƿ���굯��
        virtual Bool isMouseReleased(MouseCode mouse) = 0;
        /// �Ƿ����˫��
        virtual Bool isMouseDoubleClicked(MouseCode mouse) = 0;

		//�Ƿ�ʧȥ����
		virtual Bool isFocusLastFrame() = 0;

    };

}

/******************************************************************************/
#endif
