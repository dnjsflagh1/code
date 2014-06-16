//***********************************************************************************************************
#include "stdafx.h"
#include "UIPopupMenu.h"
#include "ClientMain.h"
//***********************************************************************************************************
#define DEFUALT_POPUPMENU_DEAD_TIME 4000
#define POPUPMENU_ITEM_NUM 10
//***********************************************************************************************************
namespace MG
{
    UIPopupMenu::UIPopupMenu()
        :mPopupMenuFunc(NULL)
        ,mStartTime(0)
        ,mSpaceTime(DEFUALT_POPUPMENU_DEAD_TIME)
        ,mCurItemCount(0)
    {

    }
    //---------------------------------------------------------------------------------------------
    UIPopupMenu::~UIPopupMenu()
    {

    }
    //---------------------------------------------------------------------------------------------
    void UIPopupMenu::setEvent()
    {
        Char8 tempName[16] = "";
        IText* pText = NULL;

        for (Int i=1; i<=POPUPMENU_ITEM_NUM; i++)
        {
            sprintf_s(tempName, 16, "text%d", i);
            pText = getLayout()->getText(tempName);
            pText->getWidget()->setMouseButtonClickEvent(onClickItem);
            pText->getWidget()->setMouseSetFocusEvent(notifyMouseSetFocusEvent);
        }

        IWidget* pWidget = getLayout()->getWidget(MAIN_WIDGET);
        pWidget->setKeyLostFocusEvent(notifyKeyLostFocusEvent);
        
    }
    //---------------------------------------------------------------------------------------------
    MG::Bool UIPopupMenu::openGui()
    {
        //设置位置
        Vec2 tempPiont = ClientMain::getInstance().getEngine()->input()->getMousePos();
        IWidget* pWidget = getLayout()->getWidget(MAIN_WIDGET);
        pWidget->setPosition(tempPiont);

        //设置焦点。
        pWidget->setKeyFocus(true);

        mCurItemCount = 0;

        //设置时间
        mStartTime = MGTimeOp::getCurrTick();

        return UIObject::openGui();
    }
    //---------------------------------------------------------------------------------------------
    void UIPopupMenu::onClickItem( void* widget )
    {
        IWidget* pWidget = (IWidget*)widget;

        IAny* pAny = pWidget->getUserData(); 
        assert(pAny);
        UInt* pId = pAny->castType<UInt>();
        assert(pId);

        UIPopupMenu::getInstance().handlEvent(*pId);
    }
    //---------------------------------------------------------------------------------------------
    void UIPopupMenu::addItem( Str16 caption, UInt id )
    {
        //检查是否超过最大数。
        ++mCurItemCount;
        if ( mCurItemCount > POPUPMENU_ITEM_NUM )
            DYNAMIC_ASSERT(0);

        //设置信息
        Char8 tempName[16] = "";
        sprintf_s(tempName, 16, "text%d", mCurItemCount);
        IWidget* pWidget = getLayout()->getWidget(tempName);
        pWidget->setCaption(caption);
        pWidget->setUserData(id);

        //编辑
        Vec2 sizeMenu;
        //获得高
        sizeMenu.y = 6 + mCurItemCount * ( pWidget->getSize().y + 2 ); 
        //获得宽
        IWidget* pWidgetMain = getLayout()->getWidget(MAIN_WIDGET);
        sizeMenu.x = pWidgetMain->getSize().x;
        UInt strLength = ClientMain::getInstance().getGui()->getLengthStr(caption) + 30;
        if ( mCurItemCount == 1 )
        {
            sizeMenu.x = strLength ;
        }
        else
        { 
            if ( strLength > sizeMenu.x )
                sizeMenu.x = strLength;
        }
        //设置大小
        pWidgetMain->setSize(sizeMenu);
    }
    //---------------------------------------------------------------------------------------------
    void UIPopupMenu::setSelectEvent( PopupMenuFunc func )
    {
        mPopupMenuFunc = func; 
    }
    //---------------------------------------------------------------------------------------------
    void UIPopupMenu::handlEvent( UInt id )
    {
        //设置焦点。
        IWidget* pWidget = getLayout()->getWidget(MAIN_WIDGET);
        pWidget->setKeyFocus(false);

        if ( mPopupMenuFunc )
            mPopupMenuFunc(id);
        closeGui();
    }
    //---------------------------------------------------------------------------------------------
    void UIPopupMenu::update(Flt delta)
    {
        if ( isOpen() )
        {
            if ( MGTimeOp::getCurrTick() > mStartTime + mSpaceTime )
            {  
                Vec2 point = ClientMain::getInstance().getEngine()->input()->getMousePos();
                IWidget* pMain = getLayout()->getWidget(MAIN_WIDGET);
                CoordI tempMainCoord = pMain->getCoord();
                if ( point.x < tempMainCoord.left  ||  point.x > tempMainCoord.left + tempMainCoord.width  
                    ||  point.y < tempMainCoord.top  ||  point.y > tempMainCoord.top + tempMainCoord.height)
                    closeGui();
                else
                    mStartTime = MGTimeOp::getCurrTick();
            }
        }
    }
    //---------------------------------------------------------------------------------------------
    MG::Bool UIPopupMenu::closeGui()
    {
        mStartTime = 0;
        mPopupMenuFunc = NULL;
        mCurItemCount = 0;
        IWidget* pImageOver = getLayout()->getWidget("imageOver");
        pImageOver->setVisible(false);

        return UIObject::closeGui();
    }
    //---------------------------------------------------------------------------------------------
    void UIPopupMenu::notifyKeyLostFocusEvent( void* widget, void* newWidget )
    {
        UIPopupMenu::getInstance().closeGui(); 
    }
    //---------------------------------------------------------------------------------------------
    void UIPopupMenu::notifyMouseSetFocusEvent( void* widget, void* newWidget )
    {
        DYNAMIC_ASSERT(widget);
        UIPopupMenu::getInstance().setHighLight(widget);
    }
    //---------------------------------------------------------------------------------------------
    void UIPopupMenu::setHighLight( void* widget )
    {
        IWidget* pImageOver = getLayout()->getWidget("imageOver");
        IWidget* pMain = getLayout()->getWidget(MAIN_WIDGET);
        CoordI tempMainCoord = pMain->getCoord();

        IWidget* pText = (IWidget*)widget;
        CoordI tempCoordItem = pText->getCoord();

        CoordI tempCoord;
        tempCoord.left = 0;
        tempCoord.top = tempCoordItem.top;
        tempCoord.width = tempMainCoord.left;
        tempCoord.height = tempCoordItem.height;
        pImageOver->setCoord(tempCoord);
        pImageOver->setVisible(true);
    }
}