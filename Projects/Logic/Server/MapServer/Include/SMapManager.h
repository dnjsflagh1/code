
/******************************************************************************/

#ifndef _S_MAPMANAGER_H_
#define _S_MAPMANAGER_H_

/******************************************************************************/

#include "MapServerPreqs.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //  ���������ͼ������
    //  ��Ҫ���ڹ���һ�����͵ĵ�ͼ
    /******************************************************************************/
    class SMapManager
    {
    public:

        SMapManager();
        virtual ~SMapManager();

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

		virtual	REGION_OBJ_TYPE getRegionType() const   = NULL;

        //-----------------------------------------------------------------------------------
        // MapObject
        //-----------------------------------------------------------------------------------

		virtual	SMapObject*		createPlaceMapObject(PlaceListCsvInfo* placeInfo, DistrictIdType districtId){ return 0; }
        virtual SMapObject*     getMapObject(RegionIdType regionId){ return 0; }
        
    private:
        std::map<RegionIdType,SMapObject*> mSMapObjectMap;

    };


}

#endif	//_S_MAPMANAGER_H_