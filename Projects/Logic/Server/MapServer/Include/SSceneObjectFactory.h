

/******************************************************************************/
#ifndef _SSCENEOBJECTFACTORY_H_
#define _SSCENEOBJECTFACTORY_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "ObjectPool.h"

#include "SPlaceSceneObject.h"
#include "SHomeSceneObject.h"
#include "SPveSceneObject.h"
#include "STiroSceneObject.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //【攻城副本地图】工厂
    /******************************************************************************/
   
    class SSceneObjectFactory
    {
    public:

        virtual void    destroySceneObject( SSceneObject* sceneObj ) = 0;
    };



	/******************************************************************************/
	//【攻城副本地图】工厂
	/******************************************************************************/
    class SPlaceSceneObjectFactory : public SSceneObjectFactory
	{
		friend class SPlaceSceneObjectPtr;

	public:
		SPlaceSceneObjectFactory();
		~SPlaceSceneObjectFactory();

	public:

		void    createPlaceSceneObjectPtr( SPlaceSceneObjectPtr& ptr, InstanceUIdType instanceUid );

	protected:

		void    destroyPlaceSceneObjectPtr( SPlaceSceneObjectPtr& ptr );
        void    destroySceneObject( SSceneObject* sceneObj );

	private:    

		ObjectPool<SPlaceSceneObject,false> mPlaceSceneObjectPool;
		Critical    mPlaceSceneObjectPoolCs;

	};


	/******************************************************************************/
	//【家园副本地图】工厂
	/******************************************************************************/
	class SHomeSceneObjectFactory : public SSceneObjectFactory
	{
		friend class SHomeSceneObjectPtr;

	public:

		SHomeSceneObjectFactory();
		~SHomeSceneObjectFactory();

	public:

		void    createSHomeSceneObjectPtr(SHomeSceneObjectPtr& ptr, InstanceUIdType instanceUid);

	protected:

		void    destroySHomeSceneObjectPtr( SHomeSceneObjectPtr& ptr );
        void    destroySceneObject( SSceneObject* sceneObj );

	private:    

		ObjectPool<SHomeSceneObject,false> mSHomeSceneObjectPool;
		Critical    mSHomeSceneObjectPoolCs;
	};


	/******************************************************************************/
	//【Pve副本地图】工厂
	/******************************************************************************/
	class SPveSceneObjectFactory : public SSceneObjectFactory
	{
		friend class SPveSceneObjectPtr;

	public:

		SPveSceneObjectFactory();
		~SPveSceneObjectFactory();

	public:

		void    createSPveSceneObjectPtr( SPveSceneObjectPtr& ptr, InstanceUIdType instanceUid);

	protected:

		void    destroySPveSceneObjectPtr( SPveSceneObjectPtr& ptr );
        void    destroySceneObject( SSceneObject* sceneObj );

	private:    

		ObjectPool<SPveSceneObject,false> mSPveSceneObjectPool;
		Critical    mSPveSceneObjectPoolCs;
	};



	/******************************************************************************/
	//【新手村副本地图】工厂
	/******************************************************************************/
	class STiroSceneObjectFactory : public SSceneObjectFactory
	{

		friend class STiroSceneObjectPtr;

	public:

		STiroSceneObjectFactory();
		~STiroSceneObjectFactory();

	public:

		void    createSTiroSceneObjectPtr( STiroSceneObjectPtr& ptr, InstanceUIdType instanceUid);

	protected:

		void    destroySTiroSceneObjectPtr( STiroSceneObjectPtr& ptr );
        void    destroySceneObject( SSceneObject* sceneObj );

	private:    

		ObjectPool<STiroSceneObject,false> mSTiroSceneObjectPool;
		Critical    mSTiroSceneObjectPoolCs;
	};
}

#endif