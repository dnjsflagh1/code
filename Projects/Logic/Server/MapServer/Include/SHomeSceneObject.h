
/******************************************************************************/

#ifndef _SHOMESCENEOBJECT_H_
#define _SHOMESCENEOBJECT_H_

/******************************************************************************/

#include "MapServerPreqs.h"
#include "SSceneObject.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //  家园场景管理器
    /******************************************************************************/
    class SHomeSceneObject : public SSceneObject
    {
    public:

        SHomeSceneObject();
        virtual ~SHomeSceneObject();

        //-----------------------------------------------------------------------------------
        // Main
        //-----------------------------------------------------------------------------------

        virtual Bool                initialize();
        virtual Bool                unInitialize();
        virtual void                clear();
        virtual void                update(Flt delta);


		virtual GameType			getGameType() { return GameType_Rpg; }

    private:

        
        

    };


	/******************************************************************************/
	//服务端【家园副本地图】智能指针
	/******************************************************************************/

	class SHomeSceneObjectPtr : public SharedPtr<SHomeSceneObject> 
	{

		friend class SHomeSceneObjectFactory;

	public:

		SHomeSceneObjectFactory* mFactory;

	public:

		virtual ~SHomeSceneObjectPtr() { release(); }
		SHomeSceneObjectPtr() : SharedPtr<SHomeSceneObject>(),mFactory(NULL){}
		explicit SHomeSceneObjectPtr(SHomeSceneObject* rep) : SharedPtr<SHomeSceneObject>(rep),mFactory(NULL){}
		SHomeSceneObjectPtr(const SHomeSceneObjectPtr& r) : SharedPtr<SHomeSceneObject>(r),mFactory(r.mFactory) {} 

		SHomeSceneObjectPtr& operator=(const SHomeSceneObjectPtr& r) 
		{
			if (pRep == r.pRep)
				return *this;

			SHomeSceneObjectPtr tmp(r);
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