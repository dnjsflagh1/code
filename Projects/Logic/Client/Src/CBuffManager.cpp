//***************************************************************************************
#include "stdafx.h"
#include "CBuffManager.h"
#include "CBuffCharacterObject.h"

//***************************************************************************************
namespace MG
{
	CBuffManager::CBuffManager(void* parent)
		:BuffManager(parent)
	{
		init();
	}
	//-----------------------------------------------------------------------
	CBuffManager::~CBuffManager()
	{
		clear();
	}
	//-----------------------------------------------------------------------
	BuffObject* CBuffManager::createBuff( STATUS_TYPE type )
	{
		switch (type)
		{
		case STATUS_TYPE_CHARACTER:
			return dynamic_cast<BuffObject*>( new CBuffCharacterObject(getVoidParent()) );
			break;
		case STATUS_TYPE_CLAN:
			break;
		case STATUS_TYPE_PLACE:
			break;
		case STATUS_TYPE_FORCE:
			break;
		}
		return NULL;
	}
	//-----------------------------------------------------------------------
	void CBuffManager::deleteBuffByDisappearTypeEvent( STATUS_DISAPPEARTYPE type )
	{
		std::map<UInt, BuffObject*>::iterator front = mMapBuffObject.begin();
		std::map<UInt, BuffObject*>::iterator back = mMapBuffObject.end();
		while (front != back)
		{
			if ( dynamic_cast<CBuffCharacterObject*>(front->second)->isCanDisappear(type) )
			{	
				deleteBuff(front);
				continue;
			}
			++front;
		}
	}
	//-----------------------------------------------------------------------
	MG::Bool CBuffManager::isHaveSpecialEffect( STATUS_STATUSSYSTYPE type )
	{
		std::map<UInt, BuffObject*>::iterator front = mMapBuffObject.begin();
		std::map<UInt, BuffObject*>::iterator back = mMapBuffObject.end();
		while (front != back)
		{
			if ( dynamic_cast<CBuffCharacterObject*>(front->second)->isHaveSpecialEffect(type) )
			{	
				return true;
			}
			++front;
		}

		return false;
	}
	//-----------------------------------------------------------------------
	MG::Bool CBuffManager::isHaveVitiateFlag( STATUS_VITIATEFLAG type )
	{
		std::map<UInt, BuffObject*>::iterator front = mMapBuffObject.begin();
		std::map<UInt, BuffObject*>::iterator back = mMapBuffObject.end();
		while (front != back)
		{
			if ( dynamic_cast<CBuffCharacterObject*>(front->second)->isHaveVitiateFlag(type) )
			{	
				return true;
			}
			++front;
		}

		return false;
	}
	//-----------------------------------------------------------------------
	void CBuffManager::deleteBuffByAbsorbType( STATUS_ABSORBTYPE type )
	{
		std::map<UInt, BuffObject*>::iterator front = mMapBuffObject.begin();
		std::map<UInt, BuffObject*>::iterator back = mMapBuffObject.end();
		while (front != back)
		{
			if ( dynamic_cast<CBuffCharacterObject*>(front->second)->isHaveAbsorbType(type) )
			{	
				deleteBuff(front);
				continue;
			}
			++front;
		}
	}
	//-----------------------------------------------------------------------
	void CBuffManager::getBuffData( std::map<U32, BuffData>& vecBuffData )
	{
		std::map<UInt, BuffObject*>::iterator front = mMapBuffObject.begin();
		std::map<UInt, BuffObject*>::iterator back = mMapBuffObject.end();
		while (front != back)
		{
			vecBuffData[front->first] = (*(front->second->getBuffData()));

			++front;
		}
	}
	//-----------------------------------------------------------------------
	void CBuffManager::calAttrAllBase()
	{
		std::map<UInt, BuffObject*>::iterator front = mMapBuffObject.begin();
		std::map<UInt, BuffObject*>::iterator back = mMapBuffObject.end();
		while (front != back)
		{
			front->second->calAttrBase();

			++front;
		}
	}
}