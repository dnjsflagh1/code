//*************************************************************************************
#include "stdafx.h"
#include "TestPopupMenu.h"
#include "UIPopupMenu.h"
//*************************************************************************************
namespace MG
{
    static Str16 strList[ ] = 
    {
        L"画面设置"
        ,L"音效设置"
        ,L"搜索"
        ,L"退出游戏"
        ,L"退出程序"
    };
    void UITestPopupMenu::setEvent()
    {
        Char8 test[16] = "";
        IButton* pButton = NULL;

        for (Int i=1; i<6; i++)
        {
            sprintf_s(test, sizeof(test), "button%d", i);
            pButton = getLayout()->getButton(test);
            pButton->getWidget()->setMouseButtonClickEvent(onClickButton);

            pButton->getWidget()->setUserData(i);
        }
        
    }
    //------------------------------------------------------------------------------------
    void UITestPopupMenu::onClickButton( void* widget )
    {
        IButton* pButton = (IButton*)widget;

        IAny* pAny = pButton->getWidget()->getUserData(); 
        assert(pAny);
        UInt* pId = pAny->castType<UInt>();
        assert(pId);

        UITestPopupMenu::getInstance().handEvent(*pId);
    }
    //------------------------------------------------------------------------------------
    void UITestPopupMenu::handEvent( Int id )
    {
        if ( id == 1 )
        {
            for (Int i=0; i<5; i++)
            {
                UIPopupMenu::getInstance().addItem(strList[i].c_str(), id);
            }

            UIPopupMenu::getInstance().openGui();
        }
    }
    //------------------------------------------------------------------------------------
    void UITestPopupMenu::addMsg( Str16 msg, U32 showTime, Byte priority )
    {
        IRollingText* pIRollingText = getLayout()->getRollingText("rollingText");
        pIRollingText->addMsg(msg, showTime, priority);
    }
    //*************************************************************************************
    void UITestRollingText::setEvent()
    {
        IRollingText* pIRollingText = getLayout()->getRollingText(MAIN_WIDGET);
        pIRollingText->setEventRollingTextNone(onRollingTextNone);
    }
    //------------------------------------------------------------------------------------
    void UITestRollingText::onRollingTextNone( void* widget )
    {
        UITestRollingText::getInstance().closeGui();
    }
    //------------------------------------------------------------------------------------
    void UITestRollingText::addMsg( Str16 msg, U32 showTime, Byte priority )
    {
        
    }
}