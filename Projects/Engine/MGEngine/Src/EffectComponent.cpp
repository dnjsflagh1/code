/******************************************************************************/
#include "stdafx.h"
#include "Scene.h"
#include "ISceneObject.h"
#include "MGSceneNode.h"
#include "ResourceManager.h"
#include "PUEffect.h"
#include "EffectComponentTimeLine.h"
#include "EffectEventFactory.h"
#include "EffectXmlSerializer.h"
#include "EffectComponent.h"
/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------
	EffectComponent::EffectComponent(CChar* name, Scene* scene)
		:mScene(scene)
		,mEffectResID(0)
		,mEffectSerialzer(NULL)
		,mEffectComponentTimeLine(NULL)
		,mSceneNode(NULL)
		,mIsAutoStart(false)
		,mIsAutoDestroy(false)
		,mEntityNameGenerator("Entity")
		,mPUNameGenerator("PUEffect")
	{
		DYNAMIC_ASSERT(mScene!=NULL);

		setName(name);

		//创建节点
		mSceneNode = MG_NEW MGSceneNode(mScene->getOgreSceneManager()->getRootSceneNode(),mScene);

		mEffectSerialzer= MG_NEW EffectXmlSerializer( this ) ;

		mEffectComponentTimeLine = MG_NEW EffectComponentTimeLine(this, mTimeList, 10.0f);
		if (mIsAutoStart)
			mEffectComponentTimeLine->start();
	}
	//-----------------------------------------------------------------------
	EffectComponent::EffectComponent(CChar* entityName, U32 effectResID, Scene* scene,Bool isAutoDestroy,Bool isAutoStart)
		:mScene(scene)
		,mEffectResID(effectResID)
		,mEffectSerialzer(NULL)
		,mEffectComponentTimeLine(NULL)
		,mSceneNode(NULL)
		,mIsAutoStart(isAutoStart)
		,mIsAutoDestroy(isAutoDestroy)
		,mEntityNameGenerator("Entity")
		,mPUNameGenerator("PUEffect")
	{
		DYNAMIC_ASSERT(mScene!=NULL);

		setName(entityName);

		//创建节点
		mSceneNode = MG_NEW MGSceneNode(mScene->getOgreSceneManager()->getRootSceneNode(),mScene);

		mEffectComponentTimeLine = MG_NEW EffectComponentTimeLine(this, mTimeList, 10.0f);

		mEffectSerialzer= MG_NEW EffectXmlSerializer( this ) ;
		loadEffectFile(effectResID);

		if (mIsAutoStart)
			mEffectComponentTimeLine->start();
	}
	//-----------------------------------------------------------------------
	EffectComponent::EffectComponent( CChar* entityName, CChar* fullfilename, Scene* scene, Bool isAutoDestroy,Bool isAutoStart )
		:mScene(scene)
		,mEffectFullPath(fullfilename)
		,mEffectSerialzer(NULL)
		,mEffectComponentTimeLine(NULL)
		,mSceneNode(NULL)
		,mIsAutoStart(isAutoStart)
		,mIsAutoDestroy(isAutoDestroy)
		,mEntityNameGenerator("Entity")
		,mPUNameGenerator("PUEffect")
	{
		DYNAMIC_ASSERT(mScene!=NULL);

		setName(entityName);
		//创建节点
		mSceneNode = MG_NEW MGSceneNode(mScene->getOgreSceneManager()->getRootSceneNode(),mScene);

		mEffectComponentTimeLine = MG_NEW EffectComponentTimeLine(this, mTimeList, 10.0f);

		mEffectSerialzer= MG_NEW EffectXmlSerializer( this ) ;
		loadEffectFile(fullfilename);

		if (mIsAutoStart)
			mEffectComponentTimeLine->start();
	}
	//-----------------------------------------------------------------------
	EffectComponent::~EffectComponent()
	{
		destroyAllPUEffect();
		destroyAllModelEffect();

		if ((mPUEffectList.size() == 0) && (mEntityList.size() == 0))
			MG_SAFE_DELETE( mSceneNode );

		MG_DELETE(mEffectComponentTimeLine);
		MG_DELETE(mEffectSerialzer);
	}

	//-----------------------------------------------------------------------
	ISceneNode* EffectComponent::getSceneNode()
	{
		return mSceneNode;
	}

	//-----------------------------------------------------------------------
	SceneObjectTypes EffectComponent::getType()
	{
		return SOT_EFFECTCOMPONENT;
	}

	//-----------------------------------------------------------------------
	void EffectComponent::start()
	{
		if (mEffectComponentTimeLine)
			mEffectComponentTimeLine->start();
	}

	//-----------------------------------------------------------------------
	Bool EffectComponent::update( Flt delta )
	{
		if ( mSceneNode )
			mSceneNode->update( delta ); 

		if (mEffectComponentTimeLine)
		{
			mEffectComponentTimeLine->update( delta );

			// 条件:是否自动销毁,不循环,并且开始了
			if (mIsAutoDestroy && !mEffectComponentTimeLine->getIsLoop() &&
				mEffectComponentTimeLine->isStarted())
			{
				if (mEffectComponentTimeLine->isRunTimeListEmpty() ||
					mEffectComponentTimeLine->isTimeLinePassThought() )
				{
					return false; 
				}
			}
		}

		return true;
	} 

	//-----------------------------------------------------------------------
	void EffectComponent::setScale( Vec3 scale )
	{
		if ( mSceneNode )
			mSceneNode->setScale(Vec3( scale.x, scale.y, scale.z));
		
	}

	//-----------------------------------------------------------------------
	Bool EffectComponent::initialised()
	{
		return mEffectResID != 0;
	}
	//-----------------------------------------------------------------------
	IEntity* EffectComponent::getSlotEntity( U32 index )
	{
		SlotEntityMap::iterator iter = mSlotEntityMap.find(index);
		if (iter != mSlotEntityMap.end())
			return iter->second;
		else
			return NULL;
	}
	//-----------------------------------------------------------------------
	void EffectComponent::loadEffectFile( U32 effectResID )
	{
		EffectComponentResourceDeclaration* effectComponentElmResDecls = 
			ResourceManager::getSingletonPtr()->getEffectComponentResourceDeclaration(effectResID);
		
		if ( !effectComponentElmResDecls ||
			effectComponentElmResDecls->filePath.empty() ||
			effectComponentElmResDecls->fileName.empty() )
		{
			return;
		}
		
		Str8 filePath = effectComponentElmResDecls->filePath;
		Str8 fileName = effectComponentElmResDecls->fileName;
		MGStrOp::str_replace(filePath, "\\\\", "/");
		char fullfilename[1024];
		wsprintf(fullfilename, "%s/%s%s", filePath.c_str(), fileName.c_str(), ".effect");

		if (mEffectSerialzer)
			mEffectSerialzer->loadEffectComponentFormat(fullfilename);
	}
	//-----------------------------------------------------------------------
	void EffectComponent::loadEffectFile( CChar* fullfilename )
	{
		Str8 filename = fullfilename;
		MGStrOp::str_replace(filename, "\\\\", "/");

		char fullfilenametemp[1024];
		wsprintf(fullfilenametemp, "%s", filename.c_str());

		if (mEffectSerialzer)
			mEffectSerialzer->loadEffectComponentFormat(fullfilenametemp);
	}
	//-----------------------------------------------------------------------
	PUEffect* EffectComponent::createPUEffect(CChar* templateName, Str name)
	{
		PUEffect* puEffect = NULL; 
		puEffect = mScene->createPUEffect(templateName, mScene);

		DYNAMIC_ASSERT(puEffect!=NULL);

		Int i = 0;
		if (!name.empty())
		{
			mPUEffectList[name] = puEffect;
		}
		else
		{
			while( i++<1000 )
			{    
				String puname = mPUNameGenerator.generate();
				mPUEffectList[puname] = puEffect;
				break;
			}
		}

		return puEffect;
	}
	//-----------------------------------------------------------------------
	PUEffect* EffectComponent::createPUEffect( U32 effectResID, Str name /*= ""*/ )
	{
		PUEffect* puEffect = NULL; 
		puEffect = mScene->createPUEffect(effectResID, mScene);

		DYNAMIC_ASSERT(puEffect!=NULL);

		Int i = 0;
		if (!name.empty())
		{
			mPUEffectList[name] = puEffect;
		}
		else
		{
			while( i++<1000 )
			{    
				String puname = mPUNameGenerator.generate();
				PUEffectMap::iterator iter = mPUEffectList.find(puname);
				if (iter != mPUEffectList.end())
					continue;
				else
				{
					mPUEffectList[puname] = puEffect;
					break;
				}
			}
		}

		return puEffect;
	}
	//-----------------------------------------------------------------------
	PUEffect* EffectComponent::getPUEffect( const Str8& puName )
	{
		PUEffectMap::iterator iter = mPUEffectList.find(puName);
		if (iter == mPUEffectList.end())
			return NULL;
		else		
			return (PUEffect*)(iter->second);
	}
	//-----------------------------------------------------------------------
	PUEffectMap EffectComponent::getPUEffectMap()
	{
		return mPUEffectList;
	}
	//-----------------------------------------------------------------------
	void EffectComponent::destroyPUEffect( const Str8& puName )
	{
		PUEffectMap::iterator iter = mPUEffectList.begin();
		for ( ; iter != mPUEffectList.end(); iter++)
		{
			if ( StrCmp((iter->first).c_str(), puName.c_str()) == 0)
			{
				mScene->destroyPUEffect(iter->second->getName().c_str());
				mPUEffectList.erase(iter);
				return;
			}
		}
	}
	//-----------------------------------------------------------------------
	void EffectComponent::destroyAllPUEffect()
	{
		PUEffectMap::iterator iter = mPUEffectList.begin();
		for ( ; iter != mPUEffectList.end(); iter++)
		{
			PUEffect* puEffect = (PUEffect*)(iter->second);
			if ( puEffect )
				mScene->destroyPUEffect(puEffect->getName().c_str());
		}
		mPUEffectList.clear();
	}
	//-----------------------------------------------------------------------
	Str EffectComponent::getEffectName( IPUEffect* effect )
	{
		PUEffectMap::iterator iter = mPUEffectList.begin();
		for ( ; iter != mPUEffectList.end(); iter++)
		{
			if (effect == (iter->second))
				return iter->first;
		}

		return "";
	}
	//-----------------------------------------------------------------------
	Entity* EffectComponent::createModelEffect( U32 resID, Str name)
	{
		// 创建模型
		Entity* newEntity = mScene->createEntity(resID, "EffectComponent");

		DYNAMIC_ASSERT(newEntity!=NULL);

		Int i = 0;
		if (!name.empty())
		{
			mEntityList[name] = newEntity;
		}
		else
		{
			while( i++<1000 )
			{    
				String entityname = mEntityNameGenerator.generate();
				EntityMap::iterator iter = mEntityList.find(entityname);
				if (iter != mEntityList.end())
					continue;
				else
				{
					mEntityList[entityname] = newEntity;
					break;
				}
			}
		}

		return newEntity;
	}
	//-----------------------------------------------------------------------
	Entity* EffectComponent::createSlotModelEffect( U32 resID )
	{
		// 创建模型
		Entity* newEntity = mScene->createSlotEntity(resID, "Slot_");

		DYNAMIC_ASSERT(newEntity!=NULL);

		return newEntity;
	}
	//-----------------------------------------------------------------------
	Entity* EffectComponent::getModelEffect( const Str8& entityName )
	{
		EntityMap::iterator iter = mEntityList.find(entityName);
		if (iter == mEntityList.end())
			return NULL;
		else
			return (Entity*)(iter->second);
	}
	//-----------------------------------------------------------------------
	EntityMap EffectComponent::getModelEffectMap()
	{
		return mEntityList;
	}
	//-----------------------------------------------------------------------
	Entity* EffectComponent::getSlotModelEffect( const Str8& entityName )
	{
		return mScene->getEntityfromSlot(entityName.c_str());
	}
	//-----------------------------------------------------------------------
	void EffectComponent::destroyModelEffect( const Str8& entityName )
	{
		EntityMap::iterator iter = mEntityList.begin();
		for ( ; iter != mEntityList.end(); iter++)
		{
			if ( StrCmp((iter->first).c_str(), entityName.c_str()) == 0)
			{
				mScene->destroyEntity(iter->second->getName().c_str());
				mEntityList.erase(iter);
				return;
			}
		}
	}
	//-----------------------------------------------------------------------
	void EffectComponent::destroyAllModelEffect()
	{
		EntityMap::iterator iter = mEntityList.begin();
		for ( ; iter != mEntityList.end(); iter++)
		{
			Entity* entity = (Entity*)(iter->second);
			if ( entity )
				mScene->destroyEntity(entity->getName().c_str());
		}
		mEntityList.clear();
	}
	//-----------------------------------------------------------------------
	Str EffectComponent::getModelName( IEntity* entity )
	{
		EntityMap::iterator iter = mEntityList.begin();
		for ( ; iter != mEntityList.end(); iter++)
		{
			if (entity == iter->second)
				return iter->first;
		}

		return "";
	}
	//-----------------------------------------------------------------------
	void EffectComponent::setBindSlot( U32 slotindex, IEntity* bindEntity )
	{
		if (bindEntity)
			mSlotEntityMap[slotindex] = bindEntity;
	}
	//-----------------------------------------------------------------------
	EffectComponentTimeLine* EffectComponent::getTimeLine()
	{
		return mEffectComponentTimeLine;
	}
	//-----------------------------------------------------------------------
	IEffectEvent* EffectComponent::createEffectEvent(const Str& eventname, Flt timePoint )
	{
		IEffectEvent* event = EffectEventFactory::getInstance().createInstance(eventname, timePoint, this);

		mTimeList.push_back(event);
		return event;
	}
	//-----------------------------------------------------------------------
	IEffectEvent* EffectComponent::getEffectEvent( const Str& eventname)
	{
		if (mTimeList.size() < 1)
			return NULL;

		TimeList::iterator iter = mTimeList.begin();
		for ( ; iter != mTimeList.end(); iter++)
		{
			if (StrCmp((*iter)->getName().c_str(), eventname.c_str()) == 0)
				return 	(*iter);
		}
		
		return NULL;
	}
	//-----------------------------------------------------------------------
	MG::TimeList EffectComponent::getTimeEventList()
	{
		return mTimeList;
	}
	//-----------------------------------------------------------------------
	void EffectComponent::destroyEffectEvent( const Str& eventname)
	{
		if (mTimeList.size() < 1)
			return;

		TimeList::iterator iter = mTimeList.begin();
		for ( ; iter != mTimeList.end(); iter++)
		{
			if (StrCmp((*iter)->getName().c_str(), eventname.c_str()) == 0)
			{
				mTimeList.erase(iter);

				if (mTimeList.size() > 0)
				{
					iter = mTimeList.begin();
				}
				else
					break;
			}
		}
	
	}
	//-----------------------------------------------------------------------
	IEffectXmlSerializer* EffectComponent::getEffectXmlSerializer()
	{
		return mEffectSerialzer;
	}

	//-----------------------------------------------------------------------
}

