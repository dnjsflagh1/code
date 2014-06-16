
/******************************************************************************/

#ifndef _S_TIROMAPOBJECT_H_
#define _S_TIROMAPOBJECT_H_

/******************************************************************************/

#include "MapServerPreqs.h"
#include "SMapObject.h"
#include "SSceneObjectFactory.h"
#include "STiroSceneObject.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //  新手村地图管理器
    /******************************************************************************/
    class STiroMapObject : public SMapObject
    {
    public:

        STiroMapObject();
        virtual ~STiroMapObject();

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
		void		createScene(STiroSceneObjectPtr& ptr, InstanceUIdType instanceUid);
		Bool		getScene(STiroSceneObjectPtr& ptr, InstanceUIdType instanceUid);
		void		destroyScene(InstanceUIdType instanceUid);
		void		destroyAllScene();

    private:

		// 【新手村副本地图】工厂
		STiroSceneObjectFactory		mSTiroSceneObjectFactory;

		//【新手村副本地图】列表
		std::map<InstanceUIdType,STiroSceneObjectPtr> mSTiroSceneObjecList;


		RWLocker    mSTiroSceneObjectListCs;



    };


}

#endif	