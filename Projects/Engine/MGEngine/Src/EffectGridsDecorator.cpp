/******************************************************************************/
#include "stdafx.h"
#include "IWireframeManager.h"
#include "EffectGridsDecorator.h"
#include "Scene.h"
#include "MGSceneNode.h"
#include "EngineMain.h"
#include "MGEngineUtility.h"

/******************************************************************************/

#define	GRID_SIZE			5
#define	GRID_ROW_COUNT		5
#define	GRID_COLUMN_COUNT	5

namespace MG
{
	EffectGridDecorator::EffectGridDecorator( const String& name, Scene* scene )
		:mScene(scene)
		,mBoldSize(1)
		,mColour(ColourValue::White)
		,mOgreManualObject(NULL)
	{
		createOgreManualObject();
		build();
		buildMesh();
	}

	EffectGridDecorator::~EffectGridDecorator()
	{
		destroyOgreManualObject();
	}

	void EffectGridDecorator::rebuild()
	{
		build();
		buildMesh();
	}

	void EffectGridDecorator::refresh()
	{
		if ( getVisible() == false )
			return;

		build();

		if (mLinePointCount != mLinePointList.size())
		{
			buildMesh();
		}else
		{
			refreshMesh();
		}
	}

	void EffectGridDecorator::setBoldSize( Flt size )
	{
		mBoldSize = size;
	}

	MG::Flt EffectGridDecorator::getBoldSize( void )
	{
		return mBoldSize;
	}

	void EffectGridDecorator::setColour( Color colour )
	{
		mColour = ColourValue(colour.r,colour.g,colour.b,colour.a);
		refresh();
	}

	Color EffectGridDecorator::getColour()
	{
		return Color(mColour.r,mColour.g,mColour.b,mColour.a);
	}

	void EffectGridDecorator::setVisible( Bool visible )
	{
		if (mSceneNode)
			mSceneNode->setVisible(visible);
		refresh();
	}

	MG::Bool EffectGridDecorator::getVisible()
	{
		if (mSceneNode)
			return mSceneNode->getVisible();
		return false;
	}

	void EffectGridDecorator::build()
	{
		mLinePointList.clear();

		for (int z = GRID_COLUMN_COUNT; z >= -1*GRID_COLUMN_COUNT; z--)
		{
			for ( int x = -1*GRID_ROW_COUNT; x < GRID_ROW_COUNT; x++)
			{
				mLinePointList.push_back( Vec3(x*GRID_SIZE, 0, z*GRID_SIZE) );
				mLinePointList.push_back( Vec3((x+1)*GRID_SIZE, 0, z*GRID_SIZE));
			}
		}


		for ( int x = -1*GRID_ROW_COUNT; x <= GRID_ROW_COUNT; x++)
		{
			for (int z = GRID_COLUMN_COUNT; z > -1*GRID_COLUMN_COUNT; z--)
			{
				mLinePointList.push_back( Vec3(x*GRID_SIZE, 0, z*GRID_SIZE) );
				mLinePointList.push_back( Vec3(x*GRID_SIZE, 0, (z-1)*GRID_SIZE));
			}
		}
		
	}

	void EffectGridDecorator::createOgreManualObject()
	{
		//创建实体对象
		mOgreManualObject = mScene->getOgreSceneManager()->createManualObject();
		mOgreManualObject->setCastShadows(false);
		mOgreManualObject->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY);

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

	void EffectGridDecorator::destroyOgreManualObject()
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

	void EffectGridDecorator::buildMesh( void )
	{
		mOgreManualObject->setDynamic(true);

		mOgreManualObject->begin("White", Ogre::RenderOperation::OT_LINE_LIST );
		{
			if (mLinePointList.size() >= 2 )
			{
				std::vector<Vec3>::iterator iter = mLinePointList.begin();
				for ( ; iter != mLinePointList.end(); iter++ )
				{
					Vec3 pos = *iter;
					mOgreManualObject->position( pos.x, pos.y, pos.z );
					mOgreManualObject->colour( mColour );
				}
				mLinePointCount = mLinePointList.size();
			}
		}

		mOgreManualObject->end();
	}

	void EffectGridDecorator::refreshMesh( void )
	{
		mOgreManualObject->beginUpdate(0);

		if ( mLinePointList.size() >= 2 )
		{
			if ( mLinePointCount == mLinePointList.size() )
			{
				if ( mOgreManualObject )
				{
					{
						std::vector<Vec3>::iterator iter = mLinePointList.begin();
						for ( ; iter != mLinePointList.end(); iter++ )
						{
							Vec3 pos = *iter;
							mOgreManualObject->position( pos.x, pos.y, pos.z );
							mOgreManualObject->colour( mColour );
						}
					}
				}
			}
		}
		mOgreManualObject->end();
	}

}
