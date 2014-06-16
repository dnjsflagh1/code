//*************************************************************************************************************
#ifndef _H_BIGMAP_RES_
#define _H_BIGMAP_RES_
//*************************************************************************************************************
#include "GameFilePreqs.h"
//*************************************************************************************************************
namespace MG
{
    class BigMapResCsv
    {
    public:
        BigMapResCsv(){;}
        ~BigMapResCsv();
        SINGLETON_INSTANCE(BigMapResCsv);

    public:
		// MG_CN_MODIFY
        //加载placeId与控件名的关系
        Bool                        load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
        //获得placeID
        U32                         getPlaceId( std::string widgetName );

    protected:
        void                        clear();

    private:
        std::map<std::string, U32>  mMapWidgetNamePlaceId;

    };
}
//*************************************************************************************************************
#endif
//*************************************************************************************************************