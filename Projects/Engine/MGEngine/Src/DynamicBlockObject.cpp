/******************************************************************************/
#include "stdafx.h"
#include "Scene.h"
#include "BlockManager.h"
#include "MGEngineUtility.h"
#include "OgreSceneQuery.h"
#include "EngineMain.h"
#include "DynamicBlockObject.h"
/******************************************************************************/

namespace MG
{
    
    //-----------------------------------------------------------------------
    DynamicBlockObject::DynamicBlockObject( Scene* scene, IEntity* entity, Flt objectRadius )
        :mEnable(false)
        ,mScene(scene)
		,mBlockManager(NULL)
		,mEntity(entity)
		,mObjectRadius(objectRadius)
        //,mObjectRadius(10)
        ,mCollideBlockObject(NULL)
        ,mStructureMode(false)
        ,mBlockDirty(true)
		,mShowBlock(false)
        ,mStaticBlockEnable(false)
    {
        mBlockManager = scene->getBlockManager();

        mEntity->getSceneNode()->addSceneNodeLisitener( "MGEngine_DynamicBlockObject", this );

        setObjectRadius( mObjectRadius );

        loadLocalBlockTriangle();
    }

    //-----------------------------------------------------------------------
    DynamicBlockObject::~DynamicBlockObject()
    {
        mEntity->getSceneNode()->removeSceneNodeLisitener( "MGEngine_DynamicBlockObject" );
        removeBlock();
    }

    //-----------------------------------------------------------------------
    ISceneObject* DynamicBlockObject::getSceneObject()
    {
        return mEntity;
    }
    
    //-----------------------------------------------------------------------
    void DynamicBlockObject::setEnable(Bool enable)
    {
        if (mEnable!=enable)
        {
            mEnable = enable;
            if (mEnable)
            {
                Vec3 pos;
                mEntity->getSceneNode()->getPosition(pos);
				refreshWorldBlockTriangle();
                refreshBlock( mOldPos, pos );
            }else
            {
                removeBlock();
            }
        }
    }

    //-----------------------------------------------------------------------
    Bool DynamicBlockObject::getEnable()
    {
        return mEnable;
    }

	//-----------------------------------------------------------------------
	void DynamicBlockObject::setShowBlock(Bool enable)
	{
		mShowBlock = enable;
	}

    //-----------------------------------------------------------------------
    void DynamicBlockObject::setStaticBlockEnable(Bool enable)
    {
        mStaticBlockEnable = enable;
    }

    //-----------------------------------------------------------------------
    void DynamicBlockObject::setStructureMode(Bool enable)
    {
        mStructureMode = enable;
    }

    //-----------------------------------------------------------------------
    void DynamicBlockObject::addBlock( Vec3 oldPos, Vec3 pos )
    {
		if(!mBlockManager->getDynamicBlockList()->getIsGridCreated())
		{
			return;
		}

        BlockManager::BLOCK_FLAG blockFlag = BlockManager::BLF_ENTITY_ALLSIDE_BLOCK;
		addBlock( oldPos, pos,  BlockManager::BLF_ENTITY_ALLSIDE_BLOCK);
		addBlock( oldPos, pos,  BlockManager::BLF_STRUCTURE_ALLSIDE_BLOCK);
		addBlock( oldPos, pos,  BlockManager::BLF_STRUCTURE_INSIDE_BLOCK );
		addBlock( oldPos, pos,  BlockManager::BLF_STRUCTURE_OUTSIDE_BLOCK );
		addBlock( oldPos, pos,  BlockManager::BLF_STRUCTURE_ROAD );
		addBlock( oldPos, pos,  BlockManager::BLF_STRUCTURE_PASSAGE );
    }

    //-----------------------------------------------------------------------
    void DynamicBlockObject::addBlock( Vec3 oldPos, Vec3 pos, Byte flag )
    {
        std::map<UInt, UInt> locationDynamicBlockIndexList;
        std::vector<UInt> locationStaticBlockIndexList;
        std::map<UInt,Bool> filterLocationDynamicBlockIndexList;
        std::map<UInt,Bool> filterLocationStaticBlockIndexList;
		VecI2 minPoint;
		VecI2 maxPoint;


        ///////////////////////////////////////////////////////////////////////////////////////////////////

        StrutureMeshs* strutureMeshs = getStrutureMeshs( flag );

        std::vector< Triangle3D >& worldTriangle3DList = strutureMeshs->mWorldTriangle3DList;

        Bool isLoadStructure = true;

		if( mStructureMode == false )
		{
			isLoadStructure = false;
		}
        else
		if(worldTriangle3DList.size() == 0)
        {
            isLoadStructure = false;
            return;
        }

        if ( isLoadStructure == false ) 
        {
            if ( BlockManager::BLF_ENTITY_ALLSIDE_BLOCK == flag )
            {
                //mBlockManager->getBlockGridListByRect(pos, locationDynamicBlockIndexList, minPoint, maxPoint, mBlockDiameter);
				//mBlockManager->getNewAddBlockGridListByRect(oldPos, pos, locationDynamicBlockIndexList, minPoint, maxPoint, getDynamicBlockGridDiameter());
				//if(locationDynamicBlockIndexList.size() == 0)
				//{
				//	return;
				//}
				//else
				//{
				//	int a = 0;
				//}
            }
        }else
        {
            if(worldTriangle3DList.size() == 0)
                return;

            std::map<UInt, VecU2> gridPointList;

            mBlockManager->getBlockGridListByTriangle3DList( gridPointList, worldTriangle3DList, false );

			for(std::map<UInt, VecU2>::iterator it = gridPointList.begin(); it != gridPointList.end(); ++it)
            {
                locationDynamicBlockIndexList[it->first] = it->first;

				//test
				//if(mShowBlock && BlockManager::BLF_STRUCTURE_ROAD != flag && BlockManager::BLF_STRUCTURE_PASSAGE != flag)
				//{
				//	Vec3 blockPos = mBlockManager->getDynamicBlockGridCenterPosByIndex(it->first);
				//	IEntity* entity = mEntity->getSceneNode()->getScene()->createEntity(10010);
				//	entity->getSceneNode()->setPosition(blockPos);
				//	entity->getSceneNode()->stickTerrain();
				//	mTestEntityList.push_back(entity);
				//}

				//if(mShowBlock && BlockManager::BLF_STRUCTURE_PASSAGE == flag)
				//{
				//	Vec3 blockPos = mBlockManager->getDynamicBlockGridCenterPosByIndex(it->first);
				//	IEntity* entity = mEntity->getSceneNode()->getScene()->createEntity(80001);
				//	entity->getSceneNode()->setScale(Vec3(0.5,0.5,0.5));
				//	entity->getSceneNode()->setPosition(blockPos);
				//	entity->getSceneNode()->stickTerrain();
				//	mTestEntityList.push_back(entity);
				//}
            }

            if ( mStaticBlockEnable )
            {
                mBlockManager->getBlockGridListByTriangle3DList( gridPointList, worldTriangle3DList, true );
                for(std::map<UInt, VecU2>::iterator it = gridPointList.begin(); it != gridPointList.end(); ++it)
                {
                    locationStaticBlockIndexList.push_back(it->first);

					//test
					//if(mShowBlock && BlockManager::BLF_STRUCTURE_ROAD != flag && BlockManager::BLF_STRUCTURE_PASSAGE != flag)
					//{
					//	Vec3 blockPos = mBlockManager->getStaticBlockGridCenterPosByIndex(index);
					//	IEntity* entity = mEntity->getSceneNode()->getScene()->createEntity(10010);
					//	entity->getSceneNode()->setPosition(blockPos);
					//	entity->getSceneNode()->stickTerrain();
					//	mTestEntityList.push_back(entity);
					//}
                }
            }
        }
            
        //////////////////////////////////////////////////////////////////////////////////////////////////////
		UInt index = 0;
        // 如果障碍已经有其他元素暂居，则移除掉从自身的位置
		for(std::map<UInt, UInt>::iterator it = locationDynamicBlockIndexList.begin(); it != locationDynamicBlockIndexList.end(); ++it)
        {
            index = it->first;
            Bool isValid = true;

            // 查看所有的碰撞组
            if ( isBelongCurrLocationDynamicBlockIndex( index, flag ) == false )
            //if ( isBelongCurrLocationDynamicBlockIndex( index ) == false )
            {
                if ( mBlockManager->hasDynamicBlockFlagByIndex( index, flag ) )
                //if ( mBlockManager->isDynamicBlockByIndex( index ) )
                {
                    isValid = false;
                }
            }else
            {
                isValid = false;
            }

            if ( isValid )
            {
                filterLocationDynamicBlockIndexList[ index ] = true;
            }
        }

        if ( mStaticBlockEnable )
        {
            for(UInt i = 0; i < locationStaticBlockIndexList.size(); ++i)
            {
                index = locationStaticBlockIndexList[i];
                Bool isValid = true;

                // 查看所有的碰撞组
                //if ( isBelongCurrLocationStaticBlockIndex( index ) == false )
                if ( isBelongCurrLocationStaticBlockIndex( index, flag ) == false )
                {
                    if ( mBlockManager->hasStaticBlockFlagByIndex( index, flag ) )
                    {
                        isValid = false;
                    }
                }else
                {
                    isValid = false;
                }

                if ( isValid )
                {
                    filterLocationStaticBlockIndexList[ index ] = true;
                }
            }
        }


        //////////////////////////////////////////////////////////////////////////////////////////////////////

        // 设置和更新障碍记录
        {
            //strutureMeshs->mCurrLocationDynamicBlockIndexList.clear();
  
            std::map<UInt,Bool>::iterator iter = filterLocationDynamicBlockIndexList.begin();
            for(; iter != filterLocationDynamicBlockIndexList.end(); ++iter)
            {
                UInt index = iter->first;

                strutureMeshs->mCurrLocationDynamicBlockIndexList[index] = index;

                mBlockManager->setDynamicBlockByIndex( index, (BlockManager::BLOCK_FLAG)flag );

                mBlockManager->addDynamicBlockObjectToGridBlock(index, this, flag);

				if(mShowBlock && BlockManager::BLF_STRUCTURE_ROAD != flag && BlockManager::BLF_STRUCTURE_PASSAGE != flag)
				{
					Vec3 blockPos = mBlockManager->getDynamicBlockGridCenterPosByIndex(index);
					IEntity* entity = mEntity->getSceneNode()->getScene()->createEntity(180012);
					entity->getSceneNode()->setScale(Vec3(0.5,0.5,0.5));
					entity->getSceneNode()->setPosition(blockPos);
					entity->getSceneNode()->stickTerrain();
					mTestEntityList[index] = entity;
				}
            }
			
			strutureMeshs->mMinPoint = minPoint;
			strutureMeshs->mMaxPoint = maxPoint;

        }


        {
            if ( mStaticBlockEnable )
            {
                strutureMeshs->mCurrLocationStaticBlockIndexList.clear();

                std::map<UInt,Bool>::iterator iter = filterLocationStaticBlockIndexList.begin();
                for(; iter != filterLocationStaticBlockIndexList.end(); ++iter)
                {
                    UInt index = iter->first;

                    strutureMeshs->mCurrLocationStaticBlockIndexList.push_back( index );

                    mBlockManager->setStaticBlockByIndex( index, (BlockManager::BLOCK_FLAG)flag );
                }
            }
        }
    }

    //-----------------------------------------------------------------------
    void DynamicBlockObject::removeBlock( Vec3 newPos )
    {
		//std::map<Byte, StrutureMeshs>::iterator iter = mStrutureMeshMap.begin();

		//std::map<UInt, UInt> blockGridList;

		//for ( ; iter != mStrutureMeshMap.end(); iter++ )
		//{
		//	blockGridList.clear();

		//	Byte flag = iter->first;
		//	StrutureMeshs& strutureMeshs = iter->second;
		//	
		//	VecI2 minPos, maxPos;
		//	//Bool ret = mBlockManager->getNewAddBlockGridListByRect(newPos, mOldPos, blockGridList, minPos, maxPos, mBlockDiameter);
		//	Bool ret = mBlockManager->getOldBlockGridListByRect(newPos, strutureMeshs.mMinPoint, strutureMeshs.mMaxPoint, blockGridList, getDynamicBlockGridDiameter());
		//	if(newPos != Vec3(0,0,0) && ret == true)
		//	{
		//		for(std::map<UInt, UInt>::iterator oldIt = blockGridList.begin(); oldIt != blockGridList.end(); ++oldIt)
		//		{
		//			if(mBlockManager->removeDynamicBlockObjectFromGridBlock(oldIt->first, this, (BlockManager::BLOCK_FLAG)flag))
		//			{
		//				mBlockManager->clearDynamicBlock(oldIt->first, (BlockManager::BLOCK_FLAG)flag);
		//				
		//				std::map<UInt, UInt>::iterator it = strutureMeshs.mCurrLocationDynamicBlockIndexList.find(oldIt->first);
		//				if(it != strutureMeshs.mCurrLocationDynamicBlockIndexList.end())
		//				{
		//					strutureMeshs.mCurrLocationDynamicBlockIndexList.erase(it);
		//				}

		//				if(mShowBlock)
		//				{
		//					std::map<UInt, IEntity*>::iterator entityIt = mTestEntityList.find(oldIt->first);
		//					if(entityIt != mTestEntityList.end())
		//					{
		//						IEntity* entity = entityIt->second;
		//						mEntity->getSceneNode()->getScene()->destroyEntity(entity->getName().c_str());
		//						mTestEntityList.erase(entityIt);
		//					}
		//				}
		//			}
		//		}
		//	}
		//	else
		//	{
		//		for(std::map<UInt, UInt>::iterator it = strutureMeshs.mCurrLocationDynamicBlockIndexList.begin(); it != strutureMeshs.mCurrLocationDynamicBlockIndexList.end(); ++it)
		//		{
		//			if(mBlockManager->removeDynamicBlockObjectFromGridBlock(it->first, this, (BlockManager::BLOCK_FLAG)flag))
		//			{
		//				mBlockManager->clearDynamicBlock(it->first, (BlockManager::BLOCK_FLAG)flag);

		//				if(mShowBlock)
		//				{
		//					std::map<UInt, IEntity*>::iterator entityIt = mTestEntityList.find(it->first);
		//					if(entityIt != mTestEntityList.end())
		//					{
		//						IEntity* entity = entityIt->second;
		//						mEntity->getSceneNode()->getScene()->destroyEntity(entity->getName().c_str());
		//						mTestEntityList.erase(entityIt);
		//					}
		//				}

		//			}
		//		}

		//		strutureMeshs.mCurrLocationDynamicBlockIndexList.clear();	
		//	}

		//	for(UInt i = 0; i < strutureMeshs.mCurrLocationStaticBlockIndexList.size(); ++i)
		//	{
		//		mBlockManager->clearStaticBlock(strutureMeshs.mCurrLocationStaticBlockIndexList[i], (BlockManager::BLOCK_FLAG)flag);
		//	}
		//	strutureMeshs.mCurrLocationStaticBlockIndexList.clear();

		//}

		//for(UInt i = 0; i < mTestEntityList.size(); ++i)
		//{
		//	IEntity* entity = mTestEntityList[i];
		//	mEntity->getSceneNode()->getScene()->destroyEntity(entity->getName().c_str());
		//}

  //      std::map<Byte, StrutureMeshs>::iterator iter = mStrutureMeshMap.begin();

  //      for ( ; iter != mStrutureMeshMap.end(); iter++ )
  //      {
  //          StrutureMeshs& strutureMeshs = iter->second;
  //          Byte flag = iter->first;

  //          for(UInt i = 0; i < strutureMeshs.mCurrLocationDynamicBlockIndexList.size(); ++i)
  //          {
  //              mBlockManager->clearDynamicBlock(strutureMeshs.mCurrLocationDynamicBlockIndexList[i], (BlockManager::BLOCK_FLAG)flag);
  //              mBlockManager->removeDynamicBlockObjectFromGridBlock(strutureMeshs.mCurrLocationDynamicBlockIndexList[i], this, (BlockManager::BLOCK_FLAG)flag);
  //          }

  //          for(UInt i = 0; i < strutureMeshs.mCurrLocationStaticBlockIndexList.size(); ++i)
  //          {
  //              mBlockManager->clearStaticBlock(strutureMeshs.mCurrLocationStaticBlockIndexList[i], (BlockManager::BLOCK_FLAG)flag);
  //          }

  //          strutureMeshs.mCurrLocationDynamicBlockIndexList.clear();
  //          strutureMeshs.mCurrLocationStaticBlockIndexList.clear();
  //      }

		//for(UInt i = 0; i < mTestEntityList.size(); ++i)
		//{
		//	IEntity* entity = mTestEntityList[i];
		//	mEntity->getSceneNode()->getScene()->destroyEntity(entity->getName().c_str());
		//}

		//mTestEntityList.clear();
    }

	//-----------------------------------------------------------------------
	void DynamicBlockObject::update( Flt delta )
	{
		if ( mBlockDirty )
		{
			refreshWorldBlockTriangle();

			//refreshBlock( mOldPos, mPos );

			mBlockDirty = false;
		}
	}

    //-----------------------------------------------------------------------
    void DynamicBlockObject::refreshBlock( Vec3 oldPos, Vec3 newPos )
    {
        //TODO:JJJ
        // 只移除变化网格， 只新增加变化网格
		if(oldPos.x == newPos.x && oldPos.z == newPos.z)
		{
			return;
		}

		//for(UInt i = 0; i < mTestEntityList.size(); ++i)
		//{
		//	IEntity* entity = mTestEntityList[i];
		//	mEntity->getSceneNode()->getScene()->destroyEntity(entity->getName().c_str());
		//}
		
		mBlockPosRect.top = newPos.z - mObjectRadius;
		mBlockPosRect.bottom = newPos.z + mObjectRadius;
		mBlockPosRect.left = newPos.x - mObjectRadius;
		mBlockPosRect.right = newPos.x + mObjectRadius;

		//if(mTestEntityList.size() == 0)
		//{
		//	IEntity* entity = mEntity->getSceneNode()->getScene()->createEntity(180012);
		//	entity->getSceneNode()->setScale(Vec3(0.5,0.5,0.5));
		//	mTestEntityList[0] = entity;

		//	entity = mEntity->getSceneNode()->getScene()->createEntity(180012);
		//	entity->getSceneNode()->setScale(Vec3(0.5,0.5,0.5));
		//	mTestEntityList[1] = entity;

		//	entity = mEntity->getSceneNode()->getScene()->createEntity(180012);
		//	entity->getSceneNode()->setScale(Vec3(0.5,0.5,0.5));
		//	mTestEntityList[2] = entity;

		//	entity = mEntity->getSceneNode()->getScene()->createEntity(180012);
		//	entity->getSceneNode()->setScale(Vec3(0.5,0.5,0.5));
		//	mTestEntityList[3] = entity;
		//}

		mScene->getDynamicBlockObjectSceneManager()->refreshBlock(this);

		//IEntity* entity = mTestEntityList[0];
		//entity->getSceneNode()->setPosition(Vec3(mBlockPosRect.left, 0, mBlockPosRect.top));
		//entity->getSceneNode()->stickTerrain();
	
		//entity = mTestEntityList[1];
		//entity->getSceneNode()->setPosition(Vec3(mBlockPosRect.left, 0, mBlockPosRect.bottom));
		//entity->getSceneNode()->stickTerrain();
	
		//entity = mTestEntityList[2];
		//entity->getSceneNode()->setPosition(Vec3(mBlockPosRect.right, 0, mBlockPosRect.top));
		//entity->getSceneNode()->stickTerrain();
		//
		//entity = mTestEntityList[3];
		//entity->getSceneNode()->setPosition(Vec3(mBlockPosRect.right, 0, mBlockPosRect.bottom) );
		//entity->getSceneNode()->stickTerrain();



        //removeBlock(newPos);

        //addBlock(oldPos, newPos);
    }

    //-----------------------------------------------------------------------
    void DynamicBlockObject::onPositionChanged( Vec3& oldPos, Vec3 newPos )
    {
		mBlockDirty = true;
		mOldPos = mPos;
		mPos = newPos;
    }

    //-----------------------------------------------------------------------
    void DynamicBlockObject::onOrientationChanged( Qua& oldQua, Qua newQua )
    {
        mBlockDirty = true;
		mQua.w = newQua.w;
		mQua.x = newQua.x;
		mQua.y = newQua.y;
		mQua.z = newQua.z;
    }

    //-----------------------------------------------------------------------
    void DynamicBlockObject::onVisibleChanged( Bool visible )
    {
        if ( visible == false )
        {
			setEnable( false );
        }
    }

    //-----------------------------------------------------------------------
  //  Int DynamicBlockObject::getDynamicBlockGridDiameter()
  //  {
		//return mDynamicBlockGridDiameter;
  //  }

    //-----------------------------------------------------------------------
    Int DynamicBlockObject::getStaticBlockGridDiameter()
    {
		return mStaticBlockGridDiameter;
    }

	//-----------------------------------------------------------------------
	void DynamicBlockObject::setObjectRadius( Flt objectRadius )
	{
		mObjectRadius = objectRadius;
		//mDynamicBlockGridDiameter   = mObjectRadius * 2 / mBlockManager->getDynamicBlockGridSize();
        mStaticBlockGridDiameter    = mObjectRadius * 2 / mBlockManager->getStaticBlockGridSize();
	}

	//-----------------------------------------------------------------------
	Flt	DynamicBlockObject::getObjectRadius()
	{
		return mObjectRadius;
	}

    //-----------------------------------------------------------------------
    Bool DynamicBlockObject::isBelongCurrLocationDynamicBlockIndex( UInt index, Byte flag )
    {
        StrutureMeshs* strutureMeshs = getStrutureMeshs( flag );

		std::map<UInt, UInt>::iterator it = strutureMeshs->mCurrLocationDynamicBlockIndexList.find(index);
		if(it != strutureMeshs->mCurrLocationDynamicBlockIndexList.end())
		{
			return true;
		}

        return false;
    }

    //-----------------------------------------------------------------------
    void DynamicBlockObject::getCurrLocationDynamicBlockIndexList( std::map<UInt, UInt>& list )
    {
        getCurrLocationDynamicBlockIndexList( list, BlockManager::BLF_ENTITY_ALLSIDE_BLOCK );
		getCurrLocationDynamicBlockIndexList( list, BlockManager::BLF_STRUCTURE_ALLSIDE_BLOCK );
        getCurrLocationDynamicBlockIndexList( list, BlockManager::BLF_STRUCTURE_INSIDE_BLOCK );
        getCurrLocationDynamicBlockIndexList( list, BlockManager::BLF_STRUCTURE_OUTSIDE_BLOCK );
    }

    //-----------------------------------------------------------------------
    void DynamicBlockObject::getCurrLocationDynamicBlockIndexList( std::map<UInt, UInt>& list, Byte flag )
    {
        StrutureMeshs* strutureMeshs = getStrutureMeshs( flag );

		for(std::map<UInt, UInt>::iterator it = strutureMeshs->mCurrLocationDynamicBlockIndexList.begin(); it != strutureMeshs->mCurrLocationDynamicBlockIndexList.end(); ++it)
        {
            list[it->first] = it->second;
        }
    }

    //-----------------------------------------------------------------------
    Bool DynamicBlockObject::isBelongCurrLocationDynamicBlockIndex( UInt index )
    {
        if ( isBelongCurrLocationDynamicBlockIndex( index, BlockManager::BLF_ENTITY_ALLSIDE_BLOCK ) )
            return true;
		if ( isBelongCurrLocationDynamicBlockIndex( index, BlockManager::BLF_STRUCTURE_ALLSIDE_BLOCK ) )
			return true;
        if ( isBelongCurrLocationDynamicBlockIndex( index, BlockManager::BLF_STRUCTURE_INSIDE_BLOCK ) )
            return true;
        if ( isBelongCurrLocationDynamicBlockIndex( index, BlockManager::BLF_STRUCTURE_OUTSIDE_BLOCK ) )
            return true;

        return false;
    }

    //-----------------------------------------------------------------------
    Bool DynamicBlockObject::isBelongCurrLocationStaticBlockIndex( UInt index, Byte flag )
    {
        StrutureMeshs* strutureMeshs = getStrutureMeshs( flag );

        for(UInt i = 0; i < strutureMeshs->mCurrLocationStaticBlockIndexList.size(); ++i)
        {
            if ( strutureMeshs->mCurrLocationStaticBlockIndexList[i] == index )
            {
                return true;
            }
        }

        return false;
    }

    //-----------------------------------------------------------------------
    Bool DynamicBlockObject::isBelongCurrLocationStaticBlockIndex( UInt index )
    {
        if ( isBelongCurrLocationStaticBlockIndex( index, BlockManager::BLF_ENTITY_ALLSIDE_BLOCK ) )
            return true;
		if ( isBelongCurrLocationStaticBlockIndex( index, BlockManager::BLF_STRUCTURE_ALLSIDE_BLOCK ) )
			return true;
        if ( isBelongCurrLocationStaticBlockIndex( index, BlockManager::BLF_STRUCTURE_INSIDE_BLOCK ) )
            return true;
        if ( isBelongCurrLocationStaticBlockIndex( index, BlockManager::BLF_STRUCTURE_OUTSIDE_BLOCK ) )
            return true;

        return false;
    }

	//-----------------------------------------------------------------------
	IDynamicBlockObject* DynamicBlockObject::getCollideBlockObject()
	{
		return mCollideBlockObject;
	}

	//-----------------------------------------------------------------------
	void DynamicBlockObject::setCollideBlockObject( IDynamicBlockObject* collideBlockObject )
	{
		mCollideBlockObject = collideBlockObject;
	}

 //   //-----------------------------------------------------------------------
 //   UInt DynamicBlockObject::getCollideBlockIndex()
 //   {
 //       return mCollideBlockIndex;
 //   }

	////-----------------------------------------------------------------------
	//void DynamicBlockObject::setCollideBlockIndex( UInt index )
	//{
	//	mCollideBlockIndex = index;
	//}

    //-----------------------------------------------------------------------
    DynamicBlockObject::StrutureMeshs* DynamicBlockObject::getStrutureMeshs( Byte flag )
    {
        std::map<Byte, StrutureMeshs>::iterator iter = mStrutureMeshMap.find( flag );
        if ( iter == mStrutureMeshMap.end() )
        {
            mStrutureMeshMap[flag] = StrutureMeshs();
        }

        return &mStrutureMeshMap[flag];
    }
    
    //-----------------------------------------------------------------------
    void DynamicBlockObject::loadLocalBlockTriangle()
    {
        if ( !mEntity )
            return;
        
        U32 modelDeclID = mEntity->getModelObject()->getModelDeclarationID();

        ModelDeclaration* modelDecl = MG::ResourceManager::getSingletonPtr()->getModelDeclaration(modelDeclID);

        if ( modelDecl )
        {
            // BLF_ENTITY_STRUCTURE_ALLSIDE_BLOCK
            if ( ( modelDecl->blockAllSideMeshFileName  != "0" ) &&
                ( modelDecl->blockAllSideMeshFileName.empty() == false ) )
            {
				//if (modelDecl->modelUsage == MODEL_USEAGE_WALL)
				{
					StrutureMeshs* strutureMeshs = getStrutureMeshs( BlockManager::BLF_STRUCTURE_ALLSIDE_BLOCK );

					strutureMeshs->mMesh = MeshManager::getSingleton().load( modelDecl->blockAllSideMeshFileName, modelDecl->path );

					ManualMeshManager::getInstance().getTriangle3DList( strutureMeshs->mMesh, strutureMeshs->mTriangle3DList );
				}
            }

			if ( ( modelDecl->blockInSideMeshFileName  != "0" ) &&
				( modelDecl->blockInSideMeshFileName.empty() == false ) )
			{
				StrutureMeshs* strutureMeshs = getStrutureMeshs( BlockManager::BLF_STRUCTURE_INSIDE_BLOCK );

				strutureMeshs->mMesh = MeshManager::getSingleton().load( modelDecl->blockInSideMeshFileName, modelDecl->path );

				ManualMeshManager::getInstance().getTriangle3DList( strutureMeshs->mMesh, strutureMeshs->mTriangle3DList );
			}

			if ( ( modelDecl->blockOutSideMeshFileName  != "0" ) &&
				( modelDecl->blockOutSideMeshFileName.empty() == false ) )
			{
				StrutureMeshs* strutureMeshs = getStrutureMeshs( BlockManager::BLF_STRUCTURE_OUTSIDE_BLOCK );

				strutureMeshs->mMesh = MeshManager::getSingleton().load( modelDecl->blockOutSideMeshFileName, modelDecl->path );

				ManualMeshManager::getInstance().getTriangle3DList( strutureMeshs->mMesh, strutureMeshs->mTriangle3DList );
			}

			if ( ( modelDecl->RoadMeshFileName  != "0" ) &&
				( modelDecl->RoadMeshFileName.empty() == false ) )
			{
					StrutureMeshs* strutureMeshs = getStrutureMeshs( BlockManager::BLF_STRUCTURE_ROAD );

					strutureMeshs->mMesh = MeshManager::getSingleton().load( modelDecl->RoadMeshFileName, modelDecl->path );

					ManualMeshManager::getInstance().getTriangle3DList( strutureMeshs->mMesh, strutureMeshs->mTriangle3DList );
			}

			if ( ( modelDecl->PassageMeshFileName  != "0" ) &&
				( modelDecl->PassageMeshFileName.empty() == false ) )
			{
				StrutureMeshs* strutureMeshs = getStrutureMeshs( BlockManager::BLF_STRUCTURE_PASSAGE );

				strutureMeshs->mMesh = MeshManager::getSingleton().load( modelDecl->PassageMeshFileName, modelDecl->path );

				ManualMeshManager::getInstance().getTriangle3DList( strutureMeshs->mMesh, strutureMeshs->mTriangle3DList );
			}

            //TODO://

            //BLF_STRUCTURE_INSIDE_BLOCK:

            //BLF_STRUCTURE_OUTSIDE_BLOCK:

            //BLF_STRUCTURE_ROAD:

            //BLF_STRUCTURE_PASSAGE:

        }
    }

    //-----------------------------------------------------------------------
    Vector3 DynamicBlockObject::getWorldPos(Vector3 localPos)
    {
        Vec3 worldPos = mQua * Vec3(localPos.x,localPos.y,localPos.z);

        worldPos = worldPos + mPos;

        return Vector3(worldPos.x,worldPos.y,worldPos.z);
    }

    //-----------------------------------------------------------------------
    void DynamicBlockObject::refreshWorldBlockTriangle(StrutureMeshs* strutureMeshs)
    {
        UInt triCount =  strutureMeshs->mTriangle3DList.size();

        if ( triCount > 0 )
        {
            if ( strutureMeshs->mWorldTriangle3DList.size() != triCount )
            {
                strutureMeshs->mWorldTriangle3DList.resize( triCount );
            }

            for (UInt i = 0; i < triCount; i++)
            {
                Triangle3D& tri     = strutureMeshs->mTriangle3DList[i];
                Triangle3D& wTri    = strutureMeshs->mWorldTriangle3DList[i];

                wTri.t0 = getWorldPos(tri.t0);
                wTri.t1 = getWorldPos(tri.t1);
                wTri.t2 = getWorldPos(tri.t2);
            }
        }
    }

    //-----------------------------------------------------------------------
    void DynamicBlockObject::refreshWorldBlockTriangle()
    {
        if ( !mEntity )
            return;

		mEntity->getSceneNode()->getPosition( mPos );
		mEntity->getSceneNode()->getOrientation( mQua );

        std::map<Byte, StrutureMeshs>::iterator iter = mStrutureMeshMap.begin();
        for ( ; iter != mStrutureMeshMap.end(); iter++ )
        {
            StrutureMeshs* strutureMeshs = &iter->second;
            refreshWorldBlockTriangle( strutureMeshs );
        }
    }

	//-----------------------------------------------------------------------
	RectF DynamicBlockObject::getBlockRect()
	{
		return mBlockPosRect;
	}


}