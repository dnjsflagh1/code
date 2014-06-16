//***************************************************************************************
#include "stdafx.h"
#include "UIObject.h"
#include "ClientMain.h"
#include "UIManage.h"
//***************************************************************************************
namespace MG
{
    UIObject::UIObject()
        :mLayout(NULL)
    {

    }
    //--------------------------------------------------------------------------------
    UIObject::~UIObject()
    {

    }
    //--------------------------------------------------------------------------------
    bool UIObject::initialize( const Str& filename, int level /*= 0*/ )
    {
        assert(filename.length() > 1);
        if ( loadLayout( filename ) )
        {
            UIManager::getInstance().addUIObj(this);
            setEvent();
            closeGui(true);
            return true;
        }
        return false;
    }
    //--------------------------------------------------------------------------------
    bool UIObject::unInitialize()
    {
        return true;
    }
    //--------------------------------------------------------------------------------
    bool UIObject::isOpen()
    {
        return mLayout->isVisible();
    }
    //--------------------------------------------------------------------------------
    bool UIObject::openGui()
    {
		DYNAMIC_ASSERT(NULL != mLayout);
        if (mLayout->isVisible() == false)    
        {    
            mLayout->setVisible(true);
        }
        return true;
    }
    //--------------------------------------------------------------------------------
    bool UIObject::closeGui(Bool isForceClose)
    {
		DYNAMIC_ASSERT(NULL != mLayout);
        if (mLayout->isVisible())
        {
            mLayout->setVisible(false);
        }
        return true;
    }
    //--------------------------------------------------------------------------------
    bool UIObject::loadLayout( Str fileName )
    {
        mLayout = ClientMain::getInstance().getGui()->loadLayOut(fileName);
         if ( mLayout )
         {
             mLayoutName = fileName;
             return true;
         }
         return false;
    }

}
