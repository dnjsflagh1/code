/******************************************************************************/
#include "stdafx.h"
#include "CAISoldierInTroopMove.h"
#include "IActionManager.h"
#include "CCharacterSceneEntity.h"
#include "IBlockManager.h"
#include "PlayCharacterNetPacketProcesser.h"
#include "MonsterNetPacketProcesser.h"
#include "CTroopSoldierEntity.h"
#include "CTroopEntity.h"
#include "TroopNetPacketProcesser.h"
#include "IDynamicBlockObject.h"
#include "CPlayer.h"
#include "CAIGroup.h"
#include "CSceneManager.h"
#include "ClientMain.h"
#include "CharacterList.h"
#include "CActionManager.h"

/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------

	Str CAISoldierInTroopMove::STATE_NAME = "CAISoldierInTroopMove";

	//--------------------------------------------------------------------------
	CAISoldierInTroopMove::CAISoldierInTroopMove( CTroopEntity* troopEntity )
		:mTroopEntity(troopEntity)
		,mIsFinished(false)
		,mIsDestroy(false)
		,mIsCheckBlock(true)
		,mMoveToPathFindType(ISceneNodeGridLineMoveToAction::PFT_DYNAMIC)
	{
	}

	//--------------------------------------------------------------------------
	CAISoldierInTroopMove::~CAISoldierInTroopMove()
	{
	}

	//-----------------------------------------------------------------------
	void CAISoldierInTroopMove::update( Flt delta )
	{
		if(mTroopEntity->getDynamicData()->isDied || !mTroopEntity->getIsCanMove())
		{
			mIsDestroy = true;
			return;
		}

		if(mIsFinished || mIsDestroy)
		{
			return;
		}

	}

	//-----------------------------------------------------------------------
	void CAISoldierInTroopMove::onStartMove()
	{
		Vec3 startPos = mTroopEntity->getPos();
		CCSEntityLineMoveAcion* troopEntityLineMoveAcion = CActionManager::getInstance().createCCSEntityLineMoveAcion( mTroopEntity, startPos, mDestination, 0 );
		if(!troopEntityLineMoveAcion)
		{
			return;
		}

		troopEntityLineMoveAcion->setMoveSpeed( mTroopEntity->getDynamicData()->moveSpeed );
		troopEntityLineMoveAcion->setYawSpeed( mTroopEntity->getDynamicData()->yawSpeed );
		troopEntityLineMoveAcion->setBlockCheck( mIsCheckBlock );
		troopEntityLineMoveAcion->setMoveToPathFindType(mMoveToPathFindType);

		if ( mTroopEntity->isBattleState() )
			troopEntityLineMoveAcion->setAnimation("march");
		else
			troopEntityLineMoveAcion->setAnimation("move");

		mIsFinished = false;
		mIsDestroy = false;

		std::vector<Vec3> destinationSoldierPosList;

		clacTroopSoldierPos(mDestination, destinationSoldierPosList);

		CTroopSoldierEntity* troopSoldierEntity = NULL;

		Vec3 tempStartPos;
		Vec3 tempDestination;

		std::map<UInt, CTroopSoldierEntity*>* troopSoldierEntityList = mTroopEntity->getSoldierEntitysList();
		if(!troopSoldierEntityList)
		{
			mIsDestroy = true;
			return;
		}


		CCSEntityLineMoveAcion* troopSoldierEntityLineMoveAcion = NULL;
		for(std::map<UInt, CTroopSoldierEntity*>::iterator it = troopSoldierEntityList->begin(); it != troopSoldierEntityList->end(); ++it)
		{
			troopSoldierEntity = it->second;
			if(!troopSoldierEntity)
			{
				continue;
			}

			tempStartPos = troopSoldierEntity->getPos();

			troopSoldierEntityLineMoveAcion = CActionManager::getInstance().createCCSEntityLineMoveAcion( troopSoldierEntity, tempStartPos, destinationSoldierPosList[it->first], 0 );
			if(!troopSoldierEntityLineMoveAcion)
			{
				continue;
			}

			troopSoldierEntityLineMoveAcion->setMoveSpeed( troopSoldierEntity->getDynamicData()->moveSpeed );
			troopSoldierEntityLineMoveAcion->setYawSpeed( troopSoldierEntity->getDynamicData()->yawSpeed );
			troopSoldierEntityLineMoveAcion->setBlockCheck( false );

			if ( troopSoldierEntity->isBattleState() )
				troopSoldierEntityLineMoveAcion->setAnimation("march");
			else
				troopSoldierEntityLineMoveAcion->setAnimation("move");

			troopEntityLineMoveAcion->addEntityLineMoveAcionListener(troopSoldierEntityLineMoveAcion);

			troopSoldierEntity->getActionStateManager().push(troopSoldierEntityLineMoveAcion/*, false*/);
		}

		mTroopEntity->getActionStateManager().push(troopEntityLineMoveAcion/*, false*/);
	}

	//-----------------------------------------------------------------------
	void CAISoldierInTroopMove::onEndMove()
	{
		std::map<UInt, CTroopSoldierEntity*>* troopSoldierEntityList = mTroopEntity->getSoldierEntitysList();
		if(!troopSoldierEntityList)
		{
			mIsDestroy = true;
			return;
		}

		CTroopSoldierEntity* troopSoldierEntity = NULL;

		for(std::map<UInt, CTroopSoldierEntity*>::iterator it = troopSoldierEntityList->begin(); it != troopSoldierEntityList->end(); ++it)
		{
			troopSoldierEntity = it->second;
			if(!troopSoldierEntity)
			{
				continue;
			}

			troopSoldierEntity->stopMoveToAction();
		}

		mIsDestroy = true;
	}

	//-----------------------------------------------------------------------
	Bool CAISoldierInTroopMove::isFinished()
	{
		return mIsFinished;
	}

	//-----------------------------------------------------------------------
	void CAISoldierInTroopMove::setDestination(Vec3 pos)
	{
		mDestination = pos;
		mDestination.y = 0;
	}

	//-----------------------------------------------------------------------
	void CAISoldierInTroopMove::setIsCheckBlock( Bool isCheckBlock )
	{
		mIsCheckBlock = isCheckBlock;
	}

	//-----------------------------------------------------------------------
	void CAISoldierInTroopMove::setMoveToPathFindType( ISceneNodeGridLineMoveToAction::MoveToPathFindType moveToPathFindType )
	{
		mMoveToPathFindType = moveToPathFindType;
	}

	//-----------------------------------------------------------------------
	Vec3 CAISoldierInTroopMove::getDestination()
	{
		return mDestination;
	}

	//---------------------------------------------------------------------------------------
	void CAISoldierInTroopMove::clacTroopSoldierPos( Vec3 pos, std::vector<Vec3>& soldierPosList )
	{
		soldierPosList.clear();

		Flt patherRadius = mTroopEntity->getEntity()->getModelObject()->getPatherRadius();
		Flt soldierPatherRadius = mTroopEntity->getSoldierEntitysByIndex(0)->getEntity()->getModelObject()->getPatherRadius();
		UInt partInterval = mTroopEntity->getCharacterTempInfo()->getArmyArmyX();
		UInt soldierNum = mTroopEntity->getSoldierEntitysNum();

		if(soldierNum == 1)
		{
			soldierPosList.push_back(pos);
			return;
		}

		UInt partNum = patherRadius / partInterval;
		if(partNum * partInterval < patherRadius)
		{
			partNum++;
		}

		Flt angle = 360 / soldierNum;

		UInt partStart = 0;

		for(UInt i = 0; i < soldierNum; ++i)
		{
			Vec3 dir(1,0,0);
			dir = MGMath::rotateVector(dir, angle * i * (MG_PI / 180));
			UInt partIndex = MGRandom::getInstance().rand_ab_One(partStart, partNum + 1);
			if(partIndex == 0)
			{
				partIndex = 1;
			}
			Flt interval = (Flt)MGRandom::getInstance().rand_ab_One(0, partInterval * 10);
			Vec3 soldierPos = pos + dir * (partIndex * (interval / 10 + soldierPatherRadius)/*partIndex * partInterval + interval / 10*/);

			soldierPosList.push_back(soldierPos);
		}

		//UInt partNum = 3;
		//Flt partInterval = patherRadius / partNum;

		//Flt angle = 360 / soldierNum;

		//for(UInt i = 0; i < soldierNum; ++i)
		//{
		//	UInt partIndex = MGRandom::getInstance().rand_ab_One(1, partNum + 1);

		//	Vec3 dir(1,0,0);
		//	dir = MGMath::rotateVector(dir, angle * i * (MG_PI / 180));
		//	Flt dis = MGRandom::getInstance().rand_ab_One((partIndex - 1) * partInterval * 10, (UInt)(partIndex * partInterval * 10));
		//	dis /= 10;
		//	Vec3 soldierPos = pos + dir * dis;

		//	soldierPosList.push_back(soldierPos);
		//}
	}

	//---------------------------------------------------------------------------------------
	void CAISoldierInTroopMove::clacTroopSoldierPos( Vec3 pos, Vec3 dir, std::map<UInt, MoveToPosRow>& soldierPosList )
	{
		soldierPosList.clear();

		Flt patherRadius = mTroopEntity->getEntityGroup()->getModelObject()->getPatherRadius();
		UInt soldierNum = mTroopEntity->getSoldierEntitysNum();
		UInt intervalRow = /*patherRadius * 4*/patherRadius * 2 + mTroopEntity->getCharacterTempInfo()->getArmyArmyX();
		UInt intervalCol = patherRadius * 2 + mTroopEntity->getCharacterTempInfo()->getArmyArmyY()/*intervalRow*/;
		UInt colNum = mTroopEntity->getCharacterTempInfo()->getArmyListNum()/*(sqrt((Flt)soldierNum / 2))* 2*/;
		UInt rowNum = soldierNum / colNum;
		if(colNum * rowNum < soldierNum)
		{
			rowNum++;
		}

		/*Vec3 dir(0,0,1);*/

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
		Flt colGap = 0;
		Flt rowGap = 0;
		Vec3 tempPos;

		MoveToPosRow moveToPosRow;

		Flt row = 1;
		soldierPosList[row] = moveToPosRow;

		for(UInt i = 0; i < soldierNum; ++i)
		{
			elementPos = startPoint - colDir * col * intervalCol;
			elementPos.y = 0;
			soldierPosList[row].moveToPos.push_back(elementPos);

			col++;

			if(col == colNum)
			{
				row++;
				moveToPosRow.moveToPos.clear();
				soldierPosList[row] = moveToPosRow;
				startPoint = startPoint - dir * intervalRow;
				col = 0;
			}
		}
	}

	//---------------------------------------------------------------------------------------
	void CAISoldierInTroopMove::clacTroopSoldierMoveToPos( Vec3 pos, Vec3 dir, std::map<UInt, Vec3>& soldierPosList )
	{
		std::map<UInt, MoveToPosRow> tempSoldierPosList;
		clacTroopSoldierPos(pos, dir, tempSoldierPosList);

		std::vector<UInt> soldierList;
		for(UInt i = 0; i < mTroopEntity->getSoldierEntitysNum(); ++i)
		{
			soldierList.push_back(i);
		}

		Flt tempDis;
		Vec3 soldierPos;
		Flt minDis = 0;

		std::vector<Vec3>::iterator minPosIt;
		std::vector<UInt>::iterator minSoldierIt;

		for(std::map<UInt, MoveToPosRow>::iterator rowPosIt = tempSoldierPosList.begin(); rowPosIt != tempSoldierPosList.end(); ++rowPosIt)
		{
			while(rowPosIt->second.moveToPos.size() != 0)
			{
				for(std::vector<Vec3>::iterator posIt = rowPosIt->second.moveToPos.begin(); posIt != rowPosIt->second.moveToPos.end(); ++posIt)
				{
					for(std::vector<UInt>::iterator soldierIt = soldierList.begin(); soldierIt != soldierList.end(); ++soldierIt)
					{
						soldierPos = mTroopEntity->getSoldierEntitysByIndex((*soldierIt))->getPos();
						tempDis = ((*posIt) - soldierPos).length();

						if(minDis > tempDis || posIt == rowPosIt->second.moveToPos.begin() && soldierIt == soldierList.begin())
						{
							minDis = tempDis;
							minPosIt = posIt;
							minSoldierIt = soldierIt;
						}
					}
				}

				soldierPosList[(*minSoldierIt)] = (*minPosIt);
				rowPosIt->second.moveToPos.erase(minPosIt);
				soldierList.erase(minSoldierIt);
			}
		}
	}



}