//***********************************************************************************************
#ifndef _H_UIARTRECOUSE_
#define _H_UIARTRECOUSE_
//***********************************************************************************************
#include "GameFilePreqs.h"
//***********************************************************************************************
namespace MG
{
        //ArtIconRes_Id	序列id
        //Notes	        策划备注
        //Type	        图标类型
        //ResName	        资源名
        //GroupName	    群名
        //ItemName	    物件名

    //--------------------------------------------------------------------------
    struct  ArtIconResCsvInfo
    {
        U32             ArtIconRes_Id   ;	       
        IOCN_ART_TYPE   Type	        ;
        Str8            ResName	        ;
        Str8            GroupName	    ;
        Str8            ItemName	    ;
		Str8            SmallResName	;
		Str8            SmallGroupName	;
		Str8            SmallItemName	;
        
    };
    //--------------------------------------------------------------------------
    class ArtIconResCsv
    {
    public:
        ArtIconResCsv(){;}
        ~ArtIconResCsv();
        SINGLETON_INSTANCE(ArtIconResCsv);

    public:
		// MG_CN_MODIFY
        Bool                    load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
        const ArtIconResCsvInfo*   getIconArtResInfo(U32 id);
        Bool                    getIconArtResInfo(U32 id, const ArtIconResCsvInfo*& info);
		bool                    getIconArtResInfo(IOCN_ART_TYPE type,std::map<U32, ArtIconResCsvInfo*>& mapinfo);

    private:
        void                    clear();

    private:
        std::map<U32, ArtIconResCsvInfo*>  mArtIconResCsvMap;

    };
}
//***********************************************************************************************
#endif
//***********************************************************************************************