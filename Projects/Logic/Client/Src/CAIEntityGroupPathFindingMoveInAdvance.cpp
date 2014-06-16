/******************************************************************************/
#include "stdafx.h"
#include "CAIEntityGroupPathFindingMoveInAdvance.h"
#include "CAIEntityPathFindingMoveInAdvance.h"
#include "CAIManager.h"
#include "CCharacterSceneEntity.h"
#include "CTroopSoldierEntity.h"
#include "CTroopEntity.h"
#include "ClientMain.h"
#include "CharacterList.h"
/******************************************************************************/

namespace MG
{

    //--------------------------------------------------------------------------

    Str CAIEntityGroupPathFindingMoveInAdvance::STATE_NAME = "CAIEntityGroupPathFindingMoveInAdvance";

    //--------------------------------------------------------------------------
    CAIEntityGroupPathFindingMoveInAdvance::CAIEntityGroupPathFindingMoveInAdvance()
        :CAIEntityGroup(STATE_NAME)
    {

    }

    //--------------------------------------------------------------------------
    CAIEntityGroupPathFindingMoveInAdvance::~CAIEntityGroupPathFindingMoveInAdvance()
    {

    }

    //-----------------------------------------------------------------------
    void CAIEntityGroupPathFindingMoveInAdvance::update( Flt delta )
    {
        /// TODO:
        /// 除了判断组元素的逻辑死亡状态还需要判断元素在场景中是否被释放。
        /// 然后次过滤判断不需要在update中执行，因为update中没有元素的相关操作

		CAIEntityGroup::update(delta);
		AIEntityTypeGroupList* aiEntityTypeGroupList = NULL;
		for(UInt i = 0; i < mGameObjectList.size(); ++i)
		{
			aiEntityTypeGroupList = getAIEntityTypeGroupList(i);
			if(!aiEntityTypeGroupList)
			{
				continue;
			}

			for(std::map<IdType, AIEntityGroupList>::iterator iter = aiEntityTypeGroupList->objectGroupList.begin(); iter != aiEntityTypeGroupList->objectGroupList.end(); ++iter)
			{
				for(std::map<IdType, AIEntity>::iterator jter = iter->second.objectList.begin(); jter != iter->second.objectList.end();)
				{
					if(!jter->second.entity)
					{
						++jter;
						continue;
					}

					if(jter->second.entity->getDynamicData()->isDied || !jter->second.entity->getIsCanMove())
					{
						jter = iter->second.objectList.erase(jter);
					}
					else
					{
						++jter;
					}
				}
			}
		}

    }

    //-----------------------------------------------------------------------
    Bool CAIEntityGroupPathFindingMoveInAdvance::isFinished()
    {
        return false;
    }

    //-----------------------------------------------------------------------
    void CAIEntityGroupPathFindingMoveInAdvance::onEnter()
    {
        /// 采用移动时自动计算目标点， 来保持组内元素的阵型功能
        /// TODO。之后需要独立此功能，用来满足不同阵型的需求。

		Int intersectionResult = GameObjectOpCtrl::getInstance().getIntersectionResult();
		std::map<UInt, GroupRowMoveToPos> moveToPosList;

		if(intersectionResult != 2)
		{
			Vec3 groupPos = calcGroupCenterPos();
			Vec3 dir = mDestination - groupPos;
			dir.y = 0;
			dir.normalise();
			calcGroupCharacterEntityPos(mDestination, dir, moveToPosList);

			if(moveToPosList.size() == 0)
			{
				destroy();
				return;
			}

			calcGroupCharacterEntityMoveToPos(moveToPosList);
		}

		Vec3 moveToPos;
		IdType parentId = 0;
		IdType id = 0;
		CCharacterSceneEntity* characterEntity = NULL;

		//UInt index = 0;

		for( std::map<GAMEOBJ_TYPE,AIEntityTypeGroupList>::iterator gameObjectIt = mGameObjectList.begin(); gameObjectIt != mGameObjectList.end(); ++gameObjectIt )
		{			
			for(std::map<IdType, AIEntityGroupList>::iterator entityGroupIt = gameObjectIt->second.objectGroupList.begin(); entityGroupIt != gameObjectIt->second.objectGroupList.end(); ++entityGroupIt)
			{
				//switch(gameObjectIt->first)
				//{
				//case GOT_PLAYERCHARACTER:
					for(std::map<IdType, AIEntity>::iterator entityTypeGroupIt = entityGroupIt->second.objectList.begin(); entityTypeGroupIt != entityGroupIt->second.objectList.end(); ++entityTypeGroupIt)
					{
						characterEntity = entityTypeGroupIt->second.entity;
						if(!characterEntity || characterEntity->getDynamicData()->isDied)
						{
							continue;
						}

						parentId = characterEntity->getID();
						id = parentId;

						if(intersectionResult != 2)
						{
							moveToPos = mEntityTypePosGroupList.posGroupList[parentId].posList[id];
						}
						else
						{
							moveToPos = mDestination;
						}
						
						CAIEntityPathFindingMoveInAdvance* ai = CAIManager::getInstance().createCAIEntityPathFindingMoveInAdvance(entityTypeGroupIt->second.entity);
						ai->setUnblockPosDestination(moveToPos);
						//ai->setDestination(moveToPos);
						ai->addListener(this);
						ai->setAIEntityGroup(this);
						entityTypeGroupIt->second.entity->getAIStateManager().push(ai);
					}

				//	break;

				//case GOT_SOLDIER:
				//	for(std::map<IdType, AIEntity>::iterator entityTypeGroupIt = entityGroupIt->second.objectList.begin(); entityTypeGroupIt != entityGroupIt->second.objectList.end(); ++entityTypeGroupIt)
				//	{
				//		characterEntity = entityTypeGroupIt->second.entity;
				//		if(!characterEntity || characterEntity->getDynamicData()->isDied)
				//		{
				//			continue;
				//		}

				//		parentId = ((CTroopSoldierEntity*)characterEntity)->getTroopEntity()->getID();
				//		id = entityTypeGroupIt->second.entity->getID();

				//		if(intersectionResult != 2)
				//		{
				//			moveToPos = mEntityTypePosGroupList.posGroupList[parentId].posList[id];
				//		}
				//		else
				//		{
				//			moveToPos = mDestination;
				//		}
				//		
				//		CAIEntityPathFindingMoveInAdvance* ai = CAIManager::getInstance().createCAIEntityPathFindingMoveInAdvance(entityTypeGroupIt->second.entity); 
				//		ai->setDestination(moveToPos);
				//		ai->addListener(this);
				//		ai->setAIEntityGroup(this);
				//		entityTypeGroupIt->second.entity->getAIStateManager().push(ai);
				//	}

				//	break;
				//}

				//index++;
			}
		}
    }

    //-----------------------------------------------------------------------
    void CAIEntityGroupPathFindingMoveInAdvance::onLeave()
    {

    }

    //--------------------------------------------------------------------------
    void CAIEntityGroupPathFindingMoveInAdvance::setDestination(Vec3 pos)
    {
        mDestination = pos;
    }

	//--------------------------------------------------------------------------
	void CAIEntityGroupPathFindingMoveInAdvance::calcGroupCharacterEntityPos(Vec3 pos, Vec3 dir, std::map<UInt, GroupRowMoveToPos>& moveToPosList)
	{
		
		UInt gameObjectNum = 0;
        UInt intervalRow = 0;
        UInt intervalCol = 0;
		UInt tempIntervalRow = 0;
		Flt	 patherRadius = 0;

		for( std::map<GAMEOBJ_TYPE,AIEntityTypeGroupList>::iterator gameObjectIt = mGameObjectList.begin(); gameObjectIt != mGameObjectList.end(); ++gameObjectIt )
		{
			for( std::map<IdType,AIEntityGroupList>::iterator groupIt = gameObjectIt->second.objectGroupList.begin(); groupIt != gameObjectIt->second.objectGroupList.end(); ++groupIt )
			{
				gameObjectNum += groupIt->second.objectList.size();
                std::map<IdType, AIEntity>::iterator it = groupIt->second.objectList.begin();

				patherRadius = it->second.entity->getEntity()->getModelObject()->getPatherRadius();

                tempIntervalRow = patherRadius;
				if(it->second.entity->getType() == GOT_TROOP)
				{
					tempIntervalRow += 1;
				}

				if(tempIntervalRow > intervalRow)
				{
					intervalRow = patherRadius * 5;

					if(it->second.entity->getType() == GOT_TROOP)
					{
						intervalRow += 1;
					}

					intervalCol = intervalRow;
				}        
			}	
		}

		if(gameObjectNum == 0)
		{
			return;
		}
	
		//UInt intervalRow = 3;
		//UInt intervalCol = 3;
		UInt colNum = (sqrt((Flt)gameObjectNum / 2))* 2;
		UInt rowNum = gameObjectNum / colNum;
		if(colNum * rowNum < gameObjectNum)
		{
			rowNum++;
		}

		Vec3 colDir = MGMath::rotateVector(dir, (Flt)90 * (MG_PI / 180));

		Flt offsetRow = 0;
		Flt offsetCol = 0;

		if(colNum % 2 == 1)
		{
			offsetCol = colNum / 2;
		}
		else
		{
			offsetCol = (Flt)colNum / 2 - 0.5;
		}

		if(rowNum % 2 == 1)
		{
			offsetRow = rowNum / 2;
		}
		else
		{
			offsetRow = (Flt)rowNum / 2 - 0.5;
		}

		Vec3 startPoint = pos + dir * offsetRow * intervalRow + colDir * offsetCol * intervalCol;
		
		startPoint.y = 0;
		Vec3 elementPos = startPoint;

		Flt col = 0;
		Flt row = 1;
		Flt colGap = 0;
		Flt rowGap = 0;
		Vec3 tempPos;

		GroupRowMoveToPos groupRowMoveToPos;

		for(UInt i = 0; i < gameObjectNum; ++i)
		{
			elementPos = startPoint - colDir * col * intervalCol;
			//colGap = MGRandom::getInstance().rand_ab_One(1, mMaxGapFaceSlot);
			//colGap = colGap / mPrecision;
			//rowGap = MGRandom::getInstance().rand_ab_One(1, mMaxGapFaceSlot);
			//rowGap = rowGap / mPrecision;
			//tempPos = elementPos + colDir /** colGap*/ +  dir /** rowGap*/;
			//tempPos.y = 0;
			elementPos.y = 0;
			groupRowMoveToPos.moveToPos.push_back(elementPos);

			col++;

			if(col == colNum)
			{
				moveToPosList[row] = groupRowMoveToPos;
				row++;
				groupRowMoveToPos.moveToPos.clear();
				startPoint = startPoint - dir * intervalRow;
				col = 0;
			}else if( i == gameObjectNum - 1)
			{
				moveToPosList[row] = groupRowMoveToPos;
			}
		}
	}

	//--------------------------------------------------------------------------
	void CAIEntityGroupPathFindingMoveInAdvance::calcGroupCharacterEntityMoveToPos(std::map<UInt, GroupRowMoveToPos>& moveToPosList)
	{
		std::vector<CCharacterSceneEntity*> characterSceneEntityList;
		for( std::map<GAMEOBJ_TYPE,AIEntityTypeGroupList>::iterator entityTypeGroupIt = mGameObjectList.begin(); entityTypeGroupIt != mGameObjectList.end(); ++entityTypeGroupIt )
		{
			for( std::map<IdType,AIEntityGroupList>::iterator entityGroupIt = entityTypeGroupIt->second.objectGroupList.begin(); entityGroupIt != entityTypeGroupIt->second.objectGroupList.end(); ++entityGroupIt )
			{
				for( std::map<IdType ,AIEntity>::iterator entityIt = entityGroupIt->second.objectList.begin(); entityIt != entityGroupIt->second.objectList.end(); ++entityIt )
				{
					characterSceneEntityList.push_back(entityIt->second.entity);
				}
			}
		}
		
		Flt tempDis;
		Vec3 characterSceneEntityPos;
		GAMEOBJ_TYPE gameObjectType;

		Flt minDis = 0;
		std::vector<Vec3>::iterator minPosIt;
		std::vector<CCharacterSceneEntity*>::iterator minCharacterSceneEntityIt;
		
		//while(moveToPosList.size() != 0)
		//{
		for(std::map<UInt, GroupRowMoveToPos>::iterator groupRowPosIt = moveToPosList.begin(); groupRowPosIt != moveToPosList.end(); ++groupRowPosIt)
		{
			while (groupRowPosIt->second.moveToPos.size() != 0)
			{
				for(std::vector<Vec3>::iterator rowPosIt = groupRowPosIt->second.moveToPos.begin(); rowPosIt != groupRowPosIt->second.moveToPos.end(); ++rowPosIt)
				{
					for(std::vector<CCharacterSceneEntity*>::iterator characterSceneEntityIt = characterSceneEntityList.begin(); characterSceneEntityIt != characterSceneEntityList.end(); ++characterSceneEntityIt)
					{
						characterSceneEntityPos = (*characterSceneEntityIt)->getPos();
						characterSceneEntityPos.y = 0;

						tempDis = ((*rowPosIt) - characterSceneEntityPos).length();

						if(rowPosIt == groupRowPosIt->second.moveToPos.begin() && characterSceneEntityIt == characterSceneEntityList.begin())
						{
							minDis = tempDis;
							minPosIt = rowPosIt;
							minCharacterSceneEntityIt = characterSceneEntityIt;

							continue;
						}
						else if(minDis > tempDis)
						{
							minDis = tempDis;
							minPosIt = rowPosIt;
							minCharacterSceneEntityIt = characterSceneEntityIt;

							continue;
						}
					}
				}

				gameObjectType = (*minCharacterSceneEntityIt)->getType();
				if(gameObjectType == GOT_SOLDIER)
				{
					CTroopSoldierEntity* troopSoldierEntity = (CTroopSoldierEntity*)(*minCharacterSceneEntityIt);
					mEntityTypePosGroupList.posGroupList[troopSoldierEntity->getTroopEntity()->getID()].posList[troopSoldierEntity->getID()] = (*minPosIt);
				}
				else
				{
					mEntityTypePosGroupList.posGroupList[(*minCharacterSceneEntityIt)->getID()].posList[(*minCharacterSceneEntityIt)->getID()] = (*minPosIt);
				}


				groupRowPosIt->second.moveToPos.erase(minPosIt);
				characterSceneEntityList.erase(minCharacterSceneEntityIt);
			}
		}
			

		//}

	}

	//--------------------------------------------------------------------------
	Vec3 CAIEntityGroupPathFindingMoveInAdvance::calcGroupCenterPos()
	{
		Flt minX = 0.0f;
		Flt minZ = 0.0f;
		Flt maxX = 0.0f;
		Flt maxZ = 0.0f;
		Vec3 pos;

		for( std::map<GAMEOBJ_TYPE,AIEntityTypeGroupList>::iterator gameObjectIt = mGameObjectList.begin(); gameObjectIt != mGameObjectList.end(); ++gameObjectIt )
		{
			for(std::map<IdType,AIEntityGroupList>::iterator groupIt = gameObjectIt->second.objectGroupList.begin(); groupIt != gameObjectIt->second.objectGroupList.end(); ++groupIt)
			{
				for(std::map<IdType, AIEntity>::iterator entityTypeGroupIt = groupIt->second.objectList.begin(); entityTypeGroupIt != groupIt->second.objectList.end(); ++entityTypeGroupIt)
				{
					pos = entityTypeGroupIt->second.entity->getPos();
					if(gameObjectIt == mGameObjectList.begin() && groupIt == gameObjectIt->second.objectGroupList.begin() && entityTypeGroupIt == groupIt->second.objectList.begin())
					{
						minX = pos.x;
						minZ = pos.z;
						maxX = minX;
						maxZ = minZ;
					}
					else if(minX > pos.x)
					{
						minX = pos.x;
					}
					else if(minZ > pos.z)
					{
						minZ = pos.z;
					}
					else if(maxX < pos.x)
					{
						maxX = pos.x;
					}
					else if(maxZ < pos.z)
					{
						maxZ = pos.z;
					}
				}
			}
		}

		return Vec3((minX + maxX) / 2, 0, (minZ + maxZ) / 2);
	}

	//--------------------------------------------------------------------------
	void CAIEntityGroupPathFindingMoveInAdvance::onLinedStateLeave(LinedStateObject* obj)
	{
        /// TODO: 需要释放元素

		CAIEntityPathFindingMoveInAdvance* ai = (CAIEntityPathFindingMoveInAdvance*)obj;
		CCharacterSceneEntity* characterSceneEntity = ai->getOwner();
		/*removeSceneEntity(characterSceneEntity);*/
	}
    

    
}