
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
    //  Pve��ͼ������
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

		//�����б�
		void		createScene(SPveSceneObjectPtr& ptr, InstanceUIdType instanceUid);
		Bool		getScene(SPveSceneObjectPtr& ptr, InstanceUIdType instanceUid);
		void		destroyScene(InstanceUIdType instanceUid);
		void		destroyAllScene();

    private:

		// ��Pve������ͼ������
		SPveSceneObjectFactory		mSPveSceneObjectFactory;

		//��Pve������ͼ���б�
		std::map<InstanceUIdType,SPveSceneObjectPtr> mSPveSceneObjecList;


		RWLocker    mSPveSceneObjectListCs;
        


    };


}

#endif	