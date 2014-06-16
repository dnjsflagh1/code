
/******************************************************************************/

#ifndef _SPVESCENEOBJECT_H_
#define _SPVESCENEOBJECT_H_

/******************************************************************************/

#include "MapServerPreqs.h"
#include "SSceneObject.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //  PVE场景管理器
    /******************************************************************************/
    class SPveSceneObject : public SSceneObject
    {
    public:

        SPveSceneObject();
        virtual ~SPveSceneObject();

        //-----------------------------------------------------------------------------------
        // Main
        //-----------------------------------------------------------------------------------

        virtual Bool                initialize();
        virtual Bool                unInitialize();
        virtual void                clear();
        virtual void                update(Flt delta);

		virtual GameType			getGameType() { return GameType_Rpg; }


		//-----------------------------------------------------------------------------------
		// Scene
		//-----------------------------------------------------------------------------------
		virtual SPlaceSceneObject*    createScene(){ return 0; }
		virtual SPlaceSceneObject*    getScene(InstanceUIdType instanceUid){ return 0; }
		virtual void                destroyScene(){ return ; }
    private:




    };


	/******************************************************************************/
	//服务端【Pve副本地图】智能指针
	/******************************************************************************/

	class SPveSceneObjectPtr : public SharedPtr<SPveSceneObject> 
	{
		friend class SPveSceneObjectFactory;
	public:

		SPveSceneObjectFactory* mFactory;

	public:

		virtual ~SPveSceneObjectPtr() { release(); }
		SPveSceneObjectPtr() : SharedPtr<SPveSceneObject>(),mFactory(NULL){}
		explicit SPveSceneObjectPtr(SPveSceneObject* rep) : SharedPtr<SPveSceneObject>(rep),mFactory(NULL){}
		SPveSceneObjectPtr(const SPveSceneObjectPtr& r) : SharedPtr<SPveSceneObject>(r),mFactory(r.mFactory) {} 

		SPveSceneObjectPtr& operator=(const SPveSceneObjectPtr& r) 
		{
			if (pRep == r.pRep)
				return *this;

			SPveSceneObjectPtr tmp(r);
			if ( isNull() == false )
			{
				tmp.mFactory = mFactory;
			}

			swap(tmp);

			mFactory = r.mFactory;

			return *this;
		}

	protected:

		virtual void    destroy(void);

	};


}

#endif	