
/******************************************************************************/

#ifndef _S_MAPOBJECT_H_
#define _S_MAPOBJECT_H_

/******************************************************************************/

#include "MapServerPreqs.h"
#include "DistrictList.h"
#include "SceneFileLoader.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //  ĳ����ͼ������
    //  ��Ҫ���ڹ���һ����ͼ��������س�������
    /******************************************************************************/
    class SMapObject	//��Ӧ SBigRegionObject
    {
    public:

        SMapObject(RegionObjectData* regionData);
        virtual ~SMapObject();

        //-----------------------------------------------------------------------------------
        // Main
        //-----------------------------------------------------------------------------------

        virtual Bool                initialize(){return 0;}
        virtual Bool                unInitialize(){return 0;}
        virtual void                clear(){return ;}
        virtual void                update(Flt delta){return ;}

        //-----------------------------------------------------------------------------------
        // Base Data
        //-----------------------------------------------------------------------------------

		virtual SInstanceBase*      getInstanceBase() {return NULL;}
		
		virtual	DistrictIdType		getDistrictId()				= NULL;		//�󶨵�����ID
		virtual DistrictRankType	getDistrictRankType()		= NULL;		//����������
		virtual RegionIdType		getRegionId()				= NULL;

		RegionObjectData*			getRegionData();
        //-----------------------------------------------------------------------------------
        // Scene
        // �������������
        //-----------------------------------------------------------------------------------


    private:
		//������Ϣ
		RegionObjectData*			mRegionData;

        SceneFileObject             mSceneFileObject;
        

	private:
		//SMapObject();
    };


}

#endif	