
/******************************************************************************/

#ifndef _S_SATKMAPMANAGER_H_
#define _S_SATKMAPMANAGER_H_

/******************************************************************************/

#include "MapServerPreqs.h"
#include "SMapManager.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //  整个主城世界地图管理器
    /******************************************************************************/
    class SPlaceMapManager : public SMapManager
    {
    public:

        SPlaceMapManager();
        virtual ~SPlaceMapManager();

        //-----------------------------------------------------------------------------------
        // Main
        //-----------------------------------------------------------------------------------

        virtual Bool            initialize(){return 0;}
        virtual Bool            unInitialize(){return 0;}
        virtual void            clear(){return ;}
        virtual void            update(Flt delta){return ;}


		virtual	SMapObject*		createPlaceMapObject(PlaceListCsvInfo* placeInfo, DistrictIdType districtId);
        //-----------------------------------------------------------------------------------
        // Base Data
        //-----------------------------------------------------------------------------------

		virtual	REGION_OBJ_TYPE getRegionType() const;

	
        

    };


}

#endif	