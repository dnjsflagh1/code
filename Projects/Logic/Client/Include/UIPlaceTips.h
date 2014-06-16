//*****************************************************************************************************
#ifndef _H_UIPLACE_TIPS_
#define _H_UIPLACE_TIPS_
//*****************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//*****************************************************************************************************
namespace MG
{
    class UIPlaceTips  : public UIObject
    {
    public:
        UIPlaceTips();
        ~UIPlaceTips(){;}
        SINGLETON_INSTANCE(UIPlaceTips);

    public:
        void    openPlaceTips(U32 placeId, CoordI coord);

    private:
        void    addInfo();
        void    addName(Vec2& size);
        void    adjustPos(Vec2& size); 

    private:
        U32 mPlaceId;
        CoordI mCoord;
    };
}
//*****************************************************************************************************
#endif
//*****************************************************************************************************