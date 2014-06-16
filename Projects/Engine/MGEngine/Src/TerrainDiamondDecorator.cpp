/******************************************************************************/
#include "stdafx.h"
#include "TerrainDiamondDecorator.h"
#include "Scene.h"
#include "MGSceneNode.h"
#include "EngineMain.h"
#include "MGEngineUtility.h"
/******************************************************************************/

namespace MG
{

    /**
    -----------------------------------------------------------------------------
    TerrainDiamondLineList
    -----------------------------------------------------------------------------
    */
    TerrainDiamondLineList::TerrainDiamondLineList()
    {
        mLastBuildTime = MGTimeOp::getCurrTick();
		mOffset = 0.0f;
    }

    //-----------------------------------------------------------------------
    void TerrainDiamondLineList::build( TerrainManager* terrainMgr , Vec3 center, Flt length, Flt gap )
    {
		Flt sideLength = length;
		Flt halfSideLength = sideLength/2;
		Flt     girth           = 4*sideLength;
		UInt    sectorCount		= girth/gap;
		sectorCount = sectorCount + sectorCount%2; 
		Flt		angle = 3.14/4.0;
		Flt		s				= girth/sectorCount;

		RectF rect;
		rect.left = center.x-halfSideLength;
		rect.top = center.z-halfSideLength;
		rect.right = center.x + halfSideLength;
		rect.bottom = center.z + halfSideLength; 

		Flt delta       = MGTimeOp::getCurrTick() - mLastBuildTime;
		mLastBuildTime  = MGTimeOp::getCurrTick();
		Flt speed = 0.003f;
		mOffset += delta*speed;
		if (mOffset > girth)
			mOffset = .0f;

		mDiamondLine.clear();
		Vec3 pos;
		for (UInt i=0; i<sectorCount; ++i)
		{
			if (i*s+mOffset < halfSideLength)
			{
				Flt x = rect.left + (i*s+mOffset);
				Flt z = center.z - abs((x-rect.left)*tan(angle));
				pos = Vec3(x,0,z);
				terrainMgr->getStickHeight( Vec2(pos.x, pos.z), pos.y );
				mDiamondLine.push_back( pos );
			}
			else if (i*s+mOffset < sideLength)
			{
				Flt x = rect.left+(i*s+mOffset);
				Flt z = center.z - abs((rect.right-x)*tan(angle));
				pos = Vec3(x,0,z);
				terrainMgr->getStickHeight( Vec2(pos.x, pos.z), pos.y );
				mDiamondLine.push_back( pos );
			}
			else if (i*s+mOffset >2*sideLength && i*s+mOffset < 5*halfSideLength)
			{
				Flt x = rect.right-(i*s+mOffset-2*sideLength);
				Flt z = center.z + abs((rect.right-x)*tan(angle));
				pos = Vec3(x,0,z);
				terrainMgr->getStickHeight( Vec2(pos.x, pos.z), pos.y );
				mDiamondLine.push_back( pos );
			}
			else if (i*s+mOffset > 5*halfSideLength && i*s+mOffset < 3*sideLength)
			{
				Flt x = rect.right-(i*s+mOffset-2*sideLength);
				Flt z = center.z + abs((x-rect.left)*tan(angle));
				pos = Vec3(x,0,z);
				terrainMgr->getStickHeight( Vec2(pos.x, pos.z), pos.y );
				mDiamondLine.push_back( pos );
			}
			else if (i*s+mOffset > girth)
			{
				if (i*s+mOffset < girth+halfSideLength)
				{
					Flt x = rect.left+ (i*s+mOffset-girth);
					Flt z = center.z - abs((x-rect.left)*tan(angle));
					pos = Vec3(x,0,z);
					terrainMgr->getStickHeight( Vec2(pos.x, pos.z), pos.y );
					mDiamondLine.push_back( pos );
				}
				else if (i*s+mOffset < girth+sideLength)
				{
					Flt x = rect.left+(i*s+mOffset-girth);
					Flt z = center.z - abs((rect.right-x)*tan(angle));
					pos = Vec3(x,0,z);
					terrainMgr->getStickHeight( Vec2(pos.x, pos.z), pos.y );
					mDiamondLine.push_back( pos );
				}
				else if (i*s+mOffset >2*sideLength+girth && i*s+mOffset < 5*halfSideLength+girth)
				{
					Flt x = rect.right-(i*s+mOffset-2*sideLength-girth);
					Flt z = center.z + abs((rect.right-x)*tan(angle));
					pos = Vec3(x,0,z);
					terrainMgr->getStickHeight( Vec2(pos.x, pos.z), pos.y );
					mDiamondLine.push_back( pos );
				}
				else if (i*s+mOffset > 5*halfSideLength+girth && i*s+mOffset < 3*sideLength+girth)
				{
					Flt x = rect.right-(i*s+mOffset-2*sideLength-girth);
					Flt z = center.z + abs((x-rect.left)*tan(angle));
					pos = Vec3(x,0,z);
					terrainMgr->getStickHeight( Vec2(pos.x, pos.z), pos.y );
					mDiamondLine.push_back( pos );
				}
			}
		}

		//mDiamondLine.clear();
		//Vector3 pos;
		//for (UInt i=0; i<sectorCount; ++i)
		//{
		//	if (i*s+mOffset < sideLength)
		//	{
		//		pos = Vector3(rect.left+(i*s+mOffset),0,rect.top);
		//	}
		//	else if (i*s+mOffset < 2*sideLength)
		//	{
		//		pos = Vector3(rect.right, 0, rect.top+(i*s+mOffset)-sideLength);
		//	}
		//	else if (i*s+mOffset < 3*sideLength)
		//	{
		//		pos = Vector3(rect.right-(i*s+mOffset-2*sideLength), 0, rect.bottom);
		//	}
		//	else if (i*s+mOffset < 4*sideLength)
		//	{
		//		pos = Vector3(rect.left, 0, rect.bottom-(i*s+mOffset-3*sideLength));
		//	}
		//	else 
		//	{
		//		if (i*s+mOffset < girth+sideLength)
		//		{
		//			pos = Vector3(rect.left+(i*s+mOffset-girth),0,rect.top);
		//		}
		//		else if (i*s+mOffset < girth+2*sideLength)
		//		{
		//			pos = Vector3(rect.right, 0, rect.top+(i*s+mOffset-girth)-sideLength);
		//		}
		//		else if (i*s+mOffset < girth+3*sideLength)
		//		{
		//			pos = Vector3(rect.right-(i*s+mOffset-2*sideLength-girth), 0, rect.bottom);
		//		}
		//		else if (i*s+mOffset < girth+girth)
		//		{
		//			pos = Vector3(rect.left, 0, rect.bottom-(i*s+mOffset-3*sideLength-girth));
		//		}
		//	}
		//	Quaternion q(Radian(90),pos);
		//	pos = q*pos;
		//	terrainMgr->getStickHeight( Vec2(pos.x, pos.z), pos.y );
		//	mDiamondLine.push_back( Vec3(pos.x,pos.y,pos.z) );
		//}
    }


	/**
	-----------------------------------------------------------------------------
	TerrainDiamondDecorator
	-----------------------------------------------------------------------------
	*/
	TerrainDiamondDecorator::TerrainDiamondDecorator(const String& name, Scene* scene)
		:mScene(scene)
		,mBoldSize(1)
		,mColour(ColourValue::Green)
		,mOgreManualObject(NULL)
		,mSideLenght(2)
		,mBuildPointCount(-1)
	{
		buildMaterial();
		createOgreManualObject();
		buildMesh();
	}

	//-----------------------------------------------------------------------
	TerrainDiamondDecorator::~TerrainDiamondDecorator()
	{
		destroyOgreManualObject();
	}

	//-----------------------------------------------------------------------
	void TerrainDiamondDecorator::rebuild(void)
	{
		mTerrainDiamondLineList.build( mScene->getTerrainManager(), mCenter, mSideLenght );
		buildMesh();
	}

	//-----------------------------------------------------------------------
	void TerrainDiamondDecorator::refresh(void)
	{
		if ( getVisible() == false )
			return;

		mTerrainDiamondLineList.build( mScene->getTerrainManager(), mCenter, mSideLenght );
		if ( mBuildPointCount == mTerrainDiamondLineList.mDiamondLine.size() )
		{
			refreshMesh();
		}else
		{
			buildMesh();
		}
	}

	//-----------------------------------------------------------------------
	void TerrainDiamondDecorator::setBoldSize(Flt size)
	{
		mBoldSize = size;
	}

	//-----------------------------------------------------------------------
	Flt TerrainDiamondDecorator::getBoldSize(void)
	{
		return mBoldSize;
	}

	//-----------------------------------------------------------------------
	void TerrainDiamondDecorator::setColour(Color colour)
	{
		mColour = ColourValue(colour.r,colour.g,colour.b,colour.a);
		refresh();
	}

	//-----------------------------------------------------------------------
	Color TerrainDiamondDecorator::getColour()
	{
		return Color(mColour.r,mColour.g,mColour.b,mColour.a);
	}

	//-----------------------------------------------------------------------
	void TerrainDiamondDecorator::setVisible(Bool visible)
	{
		if (mSceneNode)
			mSceneNode->setVisible(visible);
		refresh();
	}

	//-----------------------------------------------------------------------
	Bool TerrainDiamondDecorator::getVisible()
	{
		if (mSceneNode)
			return mSceneNode->getVisible();
		return false;
	}

	//-----------------------------------------------------------------------
	void TerrainDiamondDecorator::setSideLength(Flt lenght) 
	{
		mSideLenght = lenght;
		refresh();
	}

	//-----------------------------------------------------------------------
	void TerrainDiamondDecorator::setCenter(Vec3 pos)
	{
		mCenter = pos;
		refresh();
	}

	//-----------------------------------------------------------------------
	void TerrainDiamondDecorator::createOgreManualObject()
	{
		//创建实体对象
		mOgreManualObject = mScene->getOgreSceneManager()->createManualObject();
		mOgreManualObject->setCastShadows(false);
		//mOgreManualObject->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY-1);
		mOgreManualObject->setRenderQueueGroup(Ogre::RENDER_QUEUE_9);

		DYNAMIC_ASSERT(mOgreManualObject!=NULL);

		if ( mOgreManualObject )
		{
			// 设置绑定实体对象的管理者
			//mOgreManualObject->setUserAny( Any((ISceneObject*)this) );

			// 创建实体节点
			mSceneNode = MG_NEW MGSceneNode(mScene->getOgreSceneManager()->getRootSceneNode(),mScene);

			// 绑定实体
			mSceneNode->getOgreSceneNode()->attachObject( mOgreManualObject );
		}
	}

	//-----------------------------------------------------------------------
	void TerrainDiamondDecorator::destroyOgreManualObject()
	{
		//销毁实体对象
		if ( mOgreManualObject )
		{
			mScene->getOgreSceneManager()->destroyManualObject(mOgreManualObject);
			mOgreManualObject = NULL;
		}

		//销毁实体节点
		MG_SAFE_DELETE( mSceneNode );
	}

	//-----------------------------------------------------------------------
	void TerrainDiamondDecorator::buildMaterial(void)
	{
		Str matName = getMaterialName();

		/// 得到或创建材质
		mOgreMaterialPtr = Ogre::MaterialManager::getSingleton().getByName(matName);
		if (mOgreMaterialPtr.isNull())
		{
			mOgreMaterialPtr = Ogre::MaterialManager::getSingleton().create(matName, 
				Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
			mOgreMaterialPtr->setReceiveShadows( false );

			/// 得到渲染通道
			Ogre::Pass* pass = mOgreMaterialPtr->getTechnique(0)->getPass(0);
			pass->setLightingEnabled(false);
			pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
			pass->setCullingMode(Ogre::CULL_NONE);
			pass->setDepthCheckEnabled( false );
		}
	}

	//-----------------------------------------------------------------------
	Str TerrainDiamondDecorator::getMaterialName(void)
	{
		return "_MATERIAL_TERRAINDIAMONDDECORATOR";
	}

	//-----------------------------------------------------------------------
	void TerrainDiamondDecorator::buildMesh(void)
	{
		if ( mTerrainDiamondLineList.mDiamondLine.size() >= 2 )
		{
			mOgreManualObject->clear();

			mOgreManualObject->setDynamic(true);

			mOgreManualObject->begin(  mOgreMaterialPtr->getName(), Ogre::RenderOperation::OT_LINE_LIST );
			{
				std::vector<Vec3>::iterator iter = mTerrainDiamondLineList.mDiamondLine.begin();
				for ( ; iter != mTerrainDiamondLineList.mDiamondLine.end(); iter++ )
				{
					Vec3 pos = *iter;
					mOgreManualObject->position( pos.x, pos.y, pos.z );
					mOgreManualObject->colour( mColour );
				}
			}
			mOgreManualObject->end();

			mBuildPointCount = mTerrainDiamondLineList.mDiamondLine.size();
		}
	}

	//-----------------------------------------------------------------------
	void TerrainDiamondDecorator::refreshMesh(void)
	{
		if ( mTerrainDiamondLineList.mDiamondLine.size() >= 2 )
		{
			if ( mBuildPointCount == mTerrainDiamondLineList.mDiamondLine.size() )
			{
				if ( mOgreManualObject )
				{
					mOgreManualObject->beginUpdate(0);
					{
						std::vector<Vec3>::iterator iter = mTerrainDiamondLineList.mDiamondLine.begin();
						for ( ; iter != mTerrainDiamondLineList.mDiamondLine.end(); iter++ )
						{
							Vec3 pos = *iter;
							mOgreManualObject->position( pos.x, pos.y, pos.z );
							mOgreManualObject->colour( mColour );
						}
					}

					mOgreManualObject->end();
				}
			}
		}
	}
}