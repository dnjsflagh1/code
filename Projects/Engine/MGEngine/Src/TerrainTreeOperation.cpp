/******************************************************************************/
#include "stdafx.h"
#include "TerrainTreeOperation.h"
#include "TerrainTreeOperationManager.h"
#include "Scene.h"
#include "ICollisionSystem.h"
#include "ISceneXmlSerializer.h"
#include "ResourceManager.h"
#include "TerrainChunk.h"
#include "BrushSystem.h"
#include "TerrainTiles.h"
#include "BrushStyle.h"
#include "BrushShape.h"
#include "EngineUtil.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //TerrainTreeOperation
    /******************************************************************************/
    TerrainTreeOperation::TerrainTreeOperation()
    {

    }

    //-----------------------------------------------------------------------
    TerrainTreeOperation::~TerrainTreeOperation()
    {

    }


    //-----------------------------------------------------------------------
    void TerrainTreeOperation::rollback()
    {

    }

    /******************************************************************************/
    //TerrainAddTreeOperation
    /******************************************************************************/
    TerrainAddTreeOperation::TerrainAddTreeOperation()
    {

    }

    //-----------------------------------------------------------------------
    TerrainAddTreeOperation::~TerrainAddTreeOperation()
    {

    }

    //-----------------------------------------------------------------------
    void TerrainAddTreeOperation::influenceTree(Int x, Int y, Flt influence)
    {

    }

    //-----------------------------------------------------------------------
    void TerrainAddTreeOperation::execute()
    {
		if ( getScene() )
		{
			ICollisionSystem* collisionSystem = getScene()->getCollisionSystem();
			if ( !collisionSystem )
				return;

			ISceneXmlSerializer* serializer = getScene()->getXmlSerializer();
			if ( !serializer )
				return;

			BrushSystem brushSystem = BrushSystem::getInstance();

			U32	opModelID	= TerrainTreeOperationManager::getInstance().getOpModel();

			Vec3 brushPos   = brushSystem.getStartPos();
			Flt brushSize   = brushSystem.getSize();

			Flt distance = 1.0f;
			if (TerrainTreeOperationManager::getInstance().getTreeType() == TerrainTreeOperationManager::TREE)
			{
				distance = TerrainAddTreeOperationManager::getInstance().getTreeDistance();
			}
			else if (TerrainTreeOperationManager::getInstance().getTreeType() == TerrainTreeOperationManager::GRASS)
			{
				distance = TerrainAddTreeOperationManager::getInstance().getGrassDistance();
			}

			//根据笔刷形状过滤不在笔刷内的点
			const IBrushShape* brushShape = brushSystem.getActiveShape();
			const IBrushShape* circleShape = brushSystem.getBrushCircleShape();
			const IBrushShape* rectShape = brushSystem.getBrushRectShape();
			const IBrushShape* RhombusShape = brushSystem.getBrushRhombusShape();
			U32 numToCreate = 0;
			bool align = TerrainAddTreeOperationManager::getInstance().getAlign();
			Flt offset = TerrainAddTreeOperationManager::getInstance().getPositionOffset();
			std::vector<Vec3> pos_list;
			if (brushShape == circleShape)//圆形
			{
				U32 distributeType = TerrainAddTreeOperationManager::getInstance().getDistribute();
				if (distributeType == 1)
				{
					calculateColumPos(brushPos,brushSize,distance,pos_list);
				}
				else if (distributeType == 2)
				{
					calculateCirclePos(brushPos,brushSize,distance,pos_list);
				}
			}
			else if (brushShape == rectShape)//正方形
			{
				//将正方形里的所有种植点保存起来
				Vec2 originPoint(brushPos.x-brushSize,brushPos.z-brushSize);
				for (Flt x=0.0f; x<=2*brushSize; x+=distance)
				{
					for (Flt y=0.0f; y<=2*brushSize; y+=distance)
					{
						Vec2 pos(originPoint.x+x,originPoint.y+y);
						pos_list.push_back(Vec3(pos.x,0,pos.y));
					}
				}
			}
			else if (brushShape == RhombusShape)//菱形
			{
			}

			numToCreate = pos_list.size();

			//获取当前范围内已经创建的树木
			std::vector<ISceneObject*> plant_exist_vec;

			ISceneObjectCollisionCallback callback;
			callback.isCheckQueryFlagsMask = false;
			callback.isCheckSingle = false;

			if (brushShape == circleShape)//圆形
			{
				collisionSystem->checkCircleCollision( brushPos, brushSize, &callback );
			}
			else if (brushShape == rectShape)//正方形
			{
				//MG::RectF rect(brushPos.x-brushSize,brushPos.z-brushSize,brushPos.x+brushSize,brushPos.z+brushSize);
				MG::RectF rect(brushPos.x-brushSize,brushPos.x+brushSize,brushPos.z-brushSize,brushPos.z+brushSize);
				collisionSystem->checkRectCollision( rect, &callback );
			}
			else if (brushShape == RhombusShape)//菱形
			{
				MG::RectF rect(brushPos.x-brushSize,brushPos.z-brushSize,brushPos.x+brushSize,brushPos.z+brushSize);
				collisionSystem->checkRectCollision( rect, &callback );
			}
			

			//将选中的树木过滤，只留下有相同MODELID的树木
			for ( UINT i = 0; i < callback.collisionList.size(); i++ )
			{
				ISceneObject* sceneObject = callback.collisionList[i].second;

				if ( sceneObject )
				{
					if (sceneObject->getType() == SOT_TREE )
					{
						ITree* tree = dynamic_cast<ITree*>(sceneObject);
						if ( tree )
						{
							if ( tree->getBaseTreeId() == opModelID )
							{
								plant_exist_vec.push_back( tree );
							}
						}
					}
					else if (sceneObject->getType() == SOT_GRASS)
					{
						IGrass* grass = dynamic_cast<IGrass*>(sceneObject);
						if ( grass )
						{
							if ( grass->getBaseGrassId() == opModelID )
							{
								plant_exist_vec.push_back( grass );
							}
						}
					}
				}
			}

			//当存在的树木数量大于需要创建的数量，去掉一部分存在的树木
			while ( plant_exist_vec.size() > numToCreate )
			{
				ISceneObject* sceneObject = plant_exist_vec[plant_exist_vec.size() - 1];
				plant_exist_vec.pop_back();

				//从XML信息中去除
				serializer->removeSceneObjectFormat(sceneObject->getName().c_str(), sceneObject->getType(), false);

				//从场景中去除
				getScene()->destroySceneObject(sceneObject->getName().c_str(),sceneObject->getType());
			}

			/////////////////////////////////////////////////////////////////////////
			//重新设置已存在的树的位置
			std::vector<ISceneObject*>::iterator iter = plant_exist_vec.begin();
			for (; iter != plant_exist_vec.end(); iter++)
			{
				ISceneObject* sceneObject = *iter;
				if ( sceneObject )
				{
					ISceneNode* sceneNode = sceneObject->getSceneNode();
					if ( sceneNode )
					{
						Vec3 pos = pos_list.back();
						pos_list.pop_back();

						Flt y;
						collisionSystem->getStickHeight(Vec3(pos.x,pos.y,pos.z),y);
						Vec3 newPos = Vec3(pos.x, y, pos.z);
						if (!align)
						{
							Flt treeRadiu = distance/2.0;
							Flt treeOffestX = (rand() % int(offset*100.0))/100.0 * distance - treeRadiu;
							Flt treeOffestZ = (rand() % int(offset*100.0))/100.0 * distance - treeRadiu;
							newPos.x += treeOffestX;
							newPos.z += treeOffestZ;
						}

						sceneNode->setPosition( newPos );

						Flt lowRange = TerrainAddTreeOperationManager::getInstance().getMinScale();
						Flt highRange = TerrainAddTreeOperationManager::getInstance().getMaxScale();
						Flt scale	 = Ogre::Math::RangeRandom(lowRange/highRange, highRange/highRange)*highRange;
						sceneNode->setScale(Vec3(scale, scale, scale));

						if (sceneObject->getType() == SOT_TREE)
						{
							Flt radian = (Ogre::Math::UnitRandom() - 0.5f) * Ogre::Math::PI;
							sceneNode->yaw(radian);
						}
					}

					//将数据放入xml信息中
					ISceneObjectXmlFormat* format = serializer->getSceneObjectFormat(sceneObject->getName().c_str(), sceneObject->getType(), false);
					if ( format )
					{
						format->fill();
					}
				}
			}

			//为空位置创建新树
			numToCreate -= plant_exist_vec.size();
			for (int i=0; i<numToCreate; i++)
			{
				Str groupName = "ART_PLANT";
				Str prefix = groupName + "_";

				Vec3 pos = pos_list.back();
				pos_list.pop_back();

				Flt y;
				collisionSystem->getStickHeight(Vec3(pos.x,pos.y,pos.z),y);

				Vec3 newPos = Vec3(pos.x, y, pos.z);

				//Flt	& radian = pos.w;

				Flt lowRange = TerrainAddTreeOperationManager::getInstance().getMinScale();
				Flt highRange = TerrainAddTreeOperationManager::getInstance().getMaxScale();
				Flt scale	 = Ogre::Math::RangeRandom(lowRange/highRange, highRange/highRange)*highRange;

				//加入场景
				ISceneObject* newObj = NULL;
				if (TerrainTreeOperationManager::getInstance().getTreeType() == TerrainTreeOperationManager::TREE)
				{
					newObj = getScene()->getTreeManager()->createTree(opModelID,newPos);
				}
				else if (TerrainTreeOperationManager::getInstance().getTreeType() == TerrainTreeOperationManager::GRASS)
				{
					newObj = getScene()->getTreeManager()->createGrass(opModelID,newPos);
				}
				if (newObj == NULL)
					break;

				ISceneNode* sceneNode = newObj->getSceneNode();
				if (sceneNode)
				{
					if (!align)
					{
						Flt treeRadiu = distance/2.0;
						Flt treeOffestX = (rand() % int(offset*100.0))/100.0 * distance - treeRadiu;
						Flt treeOffestZ = (rand() % int(offset*100.0))/100.0 * distance - treeRadiu;
						newPos.x += treeOffestX;
						newPos.z += treeOffestZ;
					}

					sceneNode->setPosition( newPos );
					sceneNode->setScale(Vec3(scale, scale, scale));

					if (newObj->getType() == SOT_TREE)
					{
						Flt radian = (Ogre::Math::UnitRandom() - 0.5f) * Ogre::Math::PI;
						sceneNode->yaw(radian);
					}
				}

				newObj->setGroup(groupName);

				//加入XML信息
				serializer->addSceneObjectFormat(newObj);

			}
		}
    }

	void TerrainAddTreeOperation::calculateCirclePos( const Vec3 brushPos, const Flt brushSize, const Flt distance, std::vector<Vec3>& pos_list )
	{
		Flt brushRadiu = brushSize;
		Flt treeRadiu = distance;
		if (brushRadiu < treeRadiu) //笔刷太小容纳不下一棵树
		{
			return;
		}
		else if (brushRadiu>=treeRadiu && brushRadiu <= 2*treeRadiu) //笔刷大小只能容下一棵树
		{
			Vec3 pos(brushPos.x,brushPos.y,brushPos.z);
			pos_list.push_back(pos);
		}
		else //笔刷大小可以容下多棵树
		{
			//先把中心点添加进去
			Vec3 pos(brushPos.x,brushPos.y,brushPos.z);
			pos_list.push_back(pos);

			//把圆圈上的点都添加进去
			U32 nCircle = (U32)brushRadiu/treeRadiu;
			for (U32 i=1; i<=nCircle; i++) //遍历圆的所有圈
			{
				U32 num = 6*i;
				double angle = 2*MG_PI/(double)num;
				double tempRadiu = brushRadiu/nCircle*i;
				for (U32 n=0; n<num; n++) //遍历圈上的所有点
				{
					float x = tempRadiu*cos(n*angle)+brushPos.x;
					float z = tempRadiu*sin(n*angle)+brushPos.z;
					Vec3 pos(x,brushPos.y,z);
					pos_list.push_back(pos);
				}
			}
		}
	}

	void TerrainAddTreeOperation::calculateColumPos( const Vec3 brushPos, const Flt brushSize, const Flt distance, std::vector<Vec3>& pos_list )
	{
		//先算找出矩形Brush框里边的点
		std::vector<Vec2> rectPoints;
		Vec2 originPoint(brushPos.x-brushSize,brushPos.z-brushSize);
		Vec2 center(brushPos.x,brushPos.z);
		Flt radiu = brushSize;
		for (Flt x=0.0f; x<=2*brushSize; x+=distance)
		{
			for (Flt y=0.0f; y<=2*brushSize; y+=distance)
			{
				Vec2 pos(originPoint.x+x,originPoint.y+y);
				Flt distance= (pos - center).length();
				rectPoints.push_back(pos);
				if (distance <= radiu)
				{
					pos_list.push_back(Vec3(pos.x,0,pos.y));
				}
			}
		}
	}
	/******************************************************************************/
    //TerrainRemoveTreeOperation
    /******************************************************************************/
    TerrainRemoveTreeOperation::TerrainRemoveTreeOperation()
    {

    }

    //-----------------------------------------------------------------------
    TerrainRemoveTreeOperation::~TerrainRemoveTreeOperation()
    {

    }

    //-----------------------------------------------------------------------
    void TerrainRemoveTreeOperation::influenceTree(Int x, Int y, Flt influence)
    {

    }
    //-----------------------------------------------------------------------
    void TerrainRemoveTreeOperation::execute()
    {
		if ( getScene() )
		{
			ICollisionSystem* collisionSystem = getScene()->getCollisionSystem();
			if ( !collisionSystem )
				return;

			ISceneXmlSerializer* serializer = getScene()->getXmlSerializer();
			if ( !serializer )
				return;

			BrushSystem brushSystem = BrushSystem::getInstance();

			U32	opModelID	= TerrainTreeOperationManager::getInstance().getOpModel();
			Vec3 brushPos   = brushSystem.getStartPos();
			Flt brushSize   = brushSystem.getSize();

			//获取当前范围内已经创建的树木
			std::vector<ISceneObject*> plant_exist_vec;

			ISceneObjectCollisionCallback callback;
			callback.isCheckQueryFlagsMask = false;
			callback.isCheckSingle = false;

			const IBrushShape* brushShape = brushSystem.getActiveShape();
			const IBrushShape* circleShape = brushSystem.getBrushCircleShape();
			const IBrushShape* rectShape = brushSystem.getBrushRectShape();
			const IBrushShape* RhombusShape = brushSystem.getBrushRhombusShape();
			if (brushShape == circleShape)//圆形
			{
				collisionSystem->checkCircleCollision( brushPos, brushSize, &callback );
			}
			else if (brushShape == rectShape)//正方形
			{
				MG::RectF rect(brushPos.x-brushSize,brushPos.x+brushSize,brushPos.z-brushSize,brushPos.z+brushSize);
				collisionSystem->checkRectCollision( rect, &callback );
			}
			else if (brushShape == RhombusShape)//菱形
			{
			}
			

			//将选中的树木过滤，只留下有相同MODELID的树木
			for ( UINT i = 0; i < callback.collisionList.size(); i++ )
			{
				ISceneObject* sceneObject = callback.collisionList[i].second;

				if ( sceneObject)
				{
					if (sceneObject->getType() == SOT_TREE )
					{
						ITree* tree = dynamic_cast<ITree*>(sceneObject);
						if ( tree )
						{
							if ( tree->getBaseTreeId() == opModelID )
							{
								plant_exist_vec.push_back( tree );
							}
						}
					}
					else if (sceneObject->getType() == SOT_GRASS )
					{
						IGrass* grass = dynamic_cast<IGrass*>(sceneObject);
						if ( grass )
						{
							if ( grass->getBaseGrassId() == opModelID )
							{
								plant_exist_vec.push_back( grass );
							}
						}
					}
				}
			}

			//全部删除
			for ( U32 i = 0; i < plant_exist_vec.size(); i++ )
			{
				ISceneObject* object = plant_exist_vec[i];

				if ( object )
				{
					//从XML信息中去除
					serializer->removeSceneObjectFormat(object->getName().c_str(), object->getType(), false);

					//从场景中去除
					getScene()->destroySceneObject(object->getName().c_str(),object->getType());
				}
			}
		}
    }

    /******************************************************************************/
    //TerrainDefineTreeOperation
    /******************************************************************************/
    TerrainDefineTreeOperation::TerrainDefineTreeOperation()
    {
    }

    //-----------------------------------------------------------------------
    TerrainDefineTreeOperation::~TerrainDefineTreeOperation()
    {

    }

    //-----------------------------------------------------------------------
    void TerrainDefineTreeOperation::influenceTree(Int x, Int y, Flt influence)
    {

    }
    //-----------------------------------------------------------------------
	//SpeedTree刷的树还没批次概念，所以这个函数先不实现功能
    void TerrainDefineTreeOperation::defineTree( U32 model, std::vector<ISceneObject*>& entity_vec )
    {
		/*
		if ( entity_vec.size() <= 0 )
			return;

		Str groupName;

		//通过不同的模式来确定批次名称
		if ( model == ITerrainDefineTreeOperationManager::DEFINE_BATCH_MODE_COMMON )
		{
			std::map<Str, U32> batchMap;
			std::map<Str, U32>::iterator iter;

			U32	useCount = 0;

			batchMap.clear();

			//寻找使用了最多的那个批次名称
			for ( U32 i = 0; i < entity_vec.size(); i++ )
			{
				IEntity* entity = entity_vec[i];

				//假设是空的批次名或者是默认批次名，要先过滤掉
				if ( !entity || 
					entity->getDeclaration().batchGroup.empty() ||
					entity->getDeclaration().batchGroup.compare("DefaultStaticGroup") == 0 )
				{
					continue;
				}

				iter = batchMap.find(entity->getDeclaration().batchGroup);
				if ( iter != batchMap.end() )
				{
					++(iter->second);
				}
				else
				{
					batchMap[entity->getDeclaration().batchGroup] = 1;
				}
			}

			for ( iter = batchMap.begin(); iter != batchMap.end(); iter++ )
			{
				if (  iter->second > useCount )
				{	
					groupName = iter->first;
					useCount = iter->second;
				}
			}
		}
		else if ( model == ITerrainDefineTreeOperationManager::DEFINE_BATCH_MODE_REGION )
		{

		}
		else if ( model == ITerrainDefineTreeOperationManager::DEFINE_BATCH_MODE_SPECIALIZE )
		{
			groupName = ITerrainDefineTreeOperationManager::getInstance().getGroupName();
		}

		//假设名字为空， 随机取一个批次名
		if ( groupName.empty() )
		{
			groupName = entity_vec[0]->getName();
		}

		//修改批次名
		for ( U32 i = 0; i < entity_vec.size(); i++ )
		{
			IEntity* entity = entity_vec[i];
			if ( entity )
			{
				entity->getDeclaration().batchGroup = groupName;
			}
		}
		*/
    }

    //-----------------------------------------------------------------------
    void TerrainDefineTreeOperation::execute()
    {
		if ( getScene() )
		{
			ICollisionSystem* collisionSystem = getScene()->getCollisionSystem();
			if ( !collisionSystem )
				return;

			Vec3 brushPos   = BrushSystem::getInstance().getStartPos();
			Flt brushSize   = BrushSystem::getInstance().getSize();
			U32	opModelID	= TerrainTreeOperationManager::getInstance().getOpModel();

			//获取当前范围内已经创建的树木
			std::vector<ISceneObject*> plant_exist_vec;

			ISceneObjectCollisionCallback callback;
			callback.isCheckQueryFlagsMask = false;
			callback.isCheckSingle = false;

			collisionSystem->checkCircleCollision( brushPos, brushSize, &callback );

			//将选中的树木过滤，只留下有相同MODELID的树木
			for ( UINT i = 0; i < callback.collisionList.size(); i++ )
			{
				ISceneObject* sceneObject = callback.collisionList[i].second;

				if ( sceneObject )
				{
					if (sceneObject->getType() == SOT_TREE )
					{
						ITree* tree = dynamic_cast<ITree*>(sceneObject);
						if ( tree )
						{
							if ( tree->getBaseTreeId() == opModelID )
							{
								plant_exist_vec.push_back( tree );
							}
						}
					}
					else if (sceneObject->getType() == SOT_GRASS)
					{
						IGrass* grass = dynamic_cast<IGrass*>(sceneObject);
						if ( grass )
						{
							if ( grass->getBaseGrassId() == opModelID )
							{
								plant_exist_vec.push_back( grass );
							}
						}
					}
				}
			}

			defineTree( TerrainDefineTreeOperationManager::getInstance().getMode(), plant_exist_vec );
		}
    }
}


