//************************************************************************************************************
#include "stdafx.h"
#include "MGPointer.h"
//************************************************************************************************************
namespace MG
{
    PVOID_CALLBACK MGPointer::mDropEvent = NULL;

    //------------------------------------------------------------------------------------
    void MGPointer::resetToDefaultPointer()
    {
        MyGUI::PointerManager::getInstance().resetToDefaultPointer();
    }
    //------------------------------------------------------------------------------------
    void MGPointer::setImage( Str8 resName, Str8 groupName, Str8 itemName, IAny any, int num /*= 1*/ )
    {
        MyGUI::PointerManager::getInstance().setImage(resName, groupName, itemName, any, num);
    }
    //------------------------------------------------------------------------------------
    IAny* MGPointer::getAnyData()
    {
        MyGUI::Any* pAny = MyGUI::PointerManager::getInstance().getAnyData();
        if ( pAny )
        {
            return pAny->castType<IAny>();
        }
        else
            return NULL;
    }
	//------------------------------------------------------------------------------------
    void MGPointer::setDropEvent( PVOID_CALLBACK func )
    {
        mDropEvent = func;
        MyGUI::PointerManager::getInstance().mEventPointerManagerPtr = MyGUI::newDelegate(this, &MGPointer::notifyDropEvent);
    }
	//------------------------------------------------------------------------------------
    void MGPointer::notifyDropEvent( MyGUI::PointerManager* pPointerManager )
    {
        mDropEvent(this);  
    }
	//------------------------------------------------------------------------------------
	void MGPointer::setVisible( bool visible )
	{
		MyGUI::PointerManager::getInstance().setVisible(visible);
	}
	//------------------------------------------------------------------------------------
	void MGPointer::setPointer( Str8 name, MGPOINTER_LEVEL level )
	{
		MyGUI::PointerManager::getInstance().setPointer(name, (MyGUI::POINTER_LEVEL)( (Int)level ));
	}
}