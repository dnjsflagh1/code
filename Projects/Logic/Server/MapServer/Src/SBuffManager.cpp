//***************************************************************************************
#include "stdafx.h"
#include "SBuffManager.h"
#include "SBuffCharacterObject.h"
//***************************************************************************************
namespace MG
{
	SBuffManager::SBuffManager(void* parent)
		:BuffManager(parent)
	{
		init();
	}
	//-----------------------------------------------------------------------
	SBuffManager::~SBuffManager()
	{
		clear();
	}
	//-----------------------------------------------------------------------
	BuffObject* SBuffManager::createBuff( STATUS_TYPE type )
	{
		switch (type)
		{
		case STATUS_TYPE_CHARACTER:
			return dynamic_cast<BuffObject*>( new SBuffCharacterObject(getVoidParent()) );
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
	void SBuffManager::deleteBuffByDisappearTypeEvent( STATUS_DISAPPEARTYPE type )
	{
		std::map<UInt, BuffObject*>::iterator front = mMapBuffObject.begin();
		std::map<UInt, BuffObject*>::iterator back = mMapBuffObject.end();
		while (front != back)
		{
			if ( dynamic_cast<SBuffCharacterObject*>(front->second)->isCanDisappear(type) )
			{	
				deleteBuff(front);
				continue;
			}
			++front;
		}
	}
	//-----------------------------------------------------------------------
	MG::Bool SBuffManager::isHaveSpecialEffect( STATUS_STATUSSYSTYPE type )
	{
		std::map<UInt, BuffObject*>::iterator front = mMapBuffObject.begin();
		std::map<UInt, BuffObject*>::iterator back = mMapBuffObject.end();
		while (front != back)
		{
			if ( dynamic_cast<SBuffCharacterObject*>(front->second)->isHaveSpecialEffect(type) )
			{	
				return true;
			}
			++front;
		}

		return false;
	}
	//-----------------------------------------------------------------------
	MG::Bool SBuffManager::isHaveVitiateFlag( STATUS_VITIATEFLAG type )
	{
		std::map<UInt, BuffObject*>::iterator front = mMapBuffObject.begin();
		std::map<UInt, BuffObject*>::iterator back = mMapBuffObject.end();
		while (front != back)
		{
			if ( dynamic_cast<SBuffCharacterObject*>(front->second)->isHaveVitiateFlag(type) )
			{	
				return true;
			}
			++front;
		}

		return false;
	}
	//-----------------------------------------------------------------------
	void SBuffManager::deleteBuffByAbsorbType( STATUS_ABSORBTYPE type )
	{
		std::map<UInt, BuffObject*>::iterator front = mMapBuffObject.begin();
		std::map<UInt, BuffObject*>::iterator back = mMapBuffObject.end();
		while (front != back)
		{
			if ( dynamic_cast<SBuffCharacterObject*>(front->second)->isHaveAbsorbType(type) )
			{	
				deleteBuff(front);
				continue;
			}
			++front;
		}
	}
	//-----------------------------------------------------------------------
	void SBuffManager::getBuffData( std::map<U32, BuffData>& vecBuffData )
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
	void SBuffManager::calAttrAllBase()
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