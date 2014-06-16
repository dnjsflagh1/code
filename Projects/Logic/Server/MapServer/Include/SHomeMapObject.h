
/******************************************************************************/

#ifndef _S_HOMEMAPOBJECT_H_
#define _S_HOMEMAPOBJECT_H_

/******************************************************************************/

#include "MapServerPreqs.h"
#include "SMapObject.h"
#include "SSceneObjectFactory.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //  家园地图管理器
    /******************************************************************************/
    class SHomeMapObject : public SMapObject
    {
    public:

        SHomeMapObject();
        virtual ~SHomeMapObject();

        //-----------------------------------------------------------------------------------
        // Main
        //-----------------------------------------------------------------------------------

        virtual Bool            initialize(){return 0;}
        virtual Bool            unInitialize(){return 0;}
        virtual void            clear(){return ;}
        virtual void            update(Flt delta){return ;}

        //-----------------------------------------------------------------------------------
        // Base Data
        //-----------------------------------------------------------------------------------



        //-----------------------------------------------------------------------------------
        // Scene
        //-----------------------------------------------------------------------------------

        //副本列表
		void		createScene(SHomeSceneObjectPtr& ptr, InstanceUIdType instanceUid);
		Bool		getScene(SHomeSceneObjectPtr& ptr, InstanceUIdType instanceUid);
		void		destroyScene(InstanceUIdType instanceUid);
		void		destroyAllScene();

    private:

		// 【家园副本地图】工厂
		SHomeSceneObjectFactory		mSHomeSceneObjectFactory;

		//【家园副本地图】列表
		std::map<InstanceUIdType,SHomeSceneObjectPtr> mSHomeSceneObjecList;

		RWLocker    mSHomeSceneObjectListCs;



    };


}

#endif	