/******************************************************************************/
#include "stdafx.h"
#include "CFightManager.h"
#include "CTroopEntity.h"
#include "CCharacterSceneEntity.h"
#include "CSceneManager.h"

/******************************************************************************/

namespace MG
{

	////-----------------------------------------------------------------------
	//CFightManager::CFightManager( CSceneObject* sceneObject )
	//	:FightManager(sceneObject->getType(), sceneObject->getID())
	//{

	//}

	////-----------------------------------------------------------------------
	//CFightManager::~CFightManager()
	//{

	//}

	////-----------------------------------------------------------------------
	//void CFightManager::update()
	//{
	//	IdType currTime = MGTimeOp::getCurrTick();
	//	IdType intervalTime = 0;

	//	Flt dis = 0;

	//	for(std::map<IdType, FightInfo>::iterator it = mFightList.begin(); it != mFightList.end();)
	//	{
	//		intervalTime = currTime - it->second.endTime;

	//		if(intervalTime >= FIGHTINFOINTERVALTIME)
	//		{
	//			it = mFightList.erase(it);
	//		}
	//		else
	//		{
	//			++it;
	//		}
	//	}
	//}


}