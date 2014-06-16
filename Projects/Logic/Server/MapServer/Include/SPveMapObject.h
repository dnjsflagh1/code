
/******************************************************************************/

#ifndef _S_PVEMAPOBJECT_H_
#define _S_PVEMAPOBJECT_H_

/******************************************************************************/

#include "MapServerPreqs.h"
#include "SMapObject.h"
#include "SSceneObjectFactory.h"

/******************************************************************************/

namespace MG
{


    /******************************************************************************/
    //  Pve地图管理器
    /******************************************************************************/
    class SPveMapObject : public SMapObject
    {
    public:

        SPveMapObject();
        virtual ~SPveMapObject();

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
		void		createScene(SPveSceneObjectPtr& ptr, InstanceUIdType instanceUid);
		Bool		getScene(SPveSceneObjectPtr& ptr, InstanceUIdType instanceUid);
		void		destroyScene(InstanceUIdType instanceUid);
		void		destroyAllScene();

    private:

		// 【Pve副本地图】工厂
		SPveSceneObjectFactory		mSPveSceneObjectFactory;

		//【Pve副本地图】列表
		std::map<InstanceUIdType,SPveSceneObjectPtr> mSPveSceneObjecList;


		RWLocker    mSPveSceneObjectListCs;
        


    };


}

#endif	