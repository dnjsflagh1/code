//*************************************************************************************************************************
#ifndef _H_UI_BIGMAP_
#define _H_UI_BIGMAP_
//*************************************************************************************************************************
#include "ClientMain.h"
#include "UIObject.h"
//*************************************************************************************************************************
namespace MG
{
    class UIBigMap : public UIObject
    {
    public:
        UIBigMap(){;}
        virtual ~UIBigMap(){;}
        SINGLETON_INSTANCE(UIBigMap);

    public:
		virtual     void        setEvent();
		virtual		void		update(Flt delta);
		virtual		Bool		openBigMap( RegionIdType regionIdType, REGION_OBJ_TYPE regionObjType );

    private:
		static		void		onClickReturnDistributionMap(void* widget);

	private:
					void		handleReturnDistributionMap();


	private:
		CRegionObject*		mpCRegionObject;

    };
}
//*************************************************************************************************************************
#endif
//*************************************************************************************************************************