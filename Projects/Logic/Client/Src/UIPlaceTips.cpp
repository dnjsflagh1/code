//*****************************************************************************************************
#include "stdafx.h"
#include "UIPlaceTips.h"
#include "PlaceListCsv.h"
#include "ClientMain.h"
//*****************************************************************************************************
namespace MG
{
    UIPlaceTips::UIPlaceTips()
        :mPlaceId(0)
    {

    }
    //--------------------------------------------------------------------------------
    void UIPlaceTips::openPlaceTips( U32 placeId, CoordI coord )
    {
        mPlaceId = placeId;
        mCoord = coord;
        addInfo();
        openGui();
    }
    //--------------------------------------------------------------------------------
    void UIPlaceTips::addInfo()
    {
        Vec2 tempSize;

        addName(tempSize);

        adjustPos(tempSize);
    }
    //--------------------------------------------------------------------------------
    void UIPlaceTips::addName( Vec2& size )
    {
#if 0	//yuanlinhu
        const PlaceListCsvInfo* tempInfo = PlaceListCsv::getInstance().getPlaceListInfo(mPlaceId);
        DYNAMIC_ASSERT(tempInfo);

        U32 height = ClientMain::getInstance().getGui()->getHeightChar();
        U32 width = ClientMain::getInstance().getGui()->getLengthStr(tempInfo->placeName);
        
        IWidget* pWidget = getLayout()->getWidget("textname");
        DYNAMIC_ASSERT(pWidget);
        pWidget->setCaption(tempInfo->placeName);
        pWidget->setCoord( CoordI(2, size.y+2, width, height) );

        size.y += ( height+2 );
        if ( size.x < width + 4 )
            size.x = width + 4;
#endif
    }
    //--------------------------------------------------------------------------------
    void UIPlaceTips::adjustPos( Vec2& size )
    {
        Vec2 tempPos;
        size.y += 2;
        U32 curScreenHeight = ClientMain::getInstance().getEngine()->display()->getHeight();
        U32 curScreenWidth =  ClientMain::getInstance().getEngine()->display()->getWidth();
        
        IWidget* pWidget = getLayout()->getWidget(MAIN_WIDGET);
        
        if ( mCoord.left + mCoord.width + size.x > curScreenWidth )
            tempPos.x = mCoord.left - size.x;
        else
            tempPos.x = mCoord.left + mCoord.width;

        if ( mCoord.top - size.y < 0 )
            tempPos.y = mCoord.top + mCoord.height;
        else
            tempPos.y = mCoord.top - mCoord.height;

        pWidget->setCoord(CoordI(tempPos.x, tempPos.y, size.x, size.y));
    }
}