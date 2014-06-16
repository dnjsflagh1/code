//**********************************************************************************************************************
#include "stdafx.h"
#include "ShortestPath.h"
#include "AccessListCsv.h"
//**********************************************************************************************************************
namespace MG
{
    ShortestPath::~ShortestPath()
    {
        unInit();
    }
    //--------------------------------------------------------------------------------------------------
    MG::Bool ShortestPath::getShortestPath( U32 regionId, U32 startPlaceId, U32 endPlaceId, std::vector<U32>& placeVector )
    {
        return false;
    }
    //--------------------------------------------------------------------------------------------------
    void ShortestPath::initRegionMap()
    {
        if ( mNomeGameMap.size() > 0 )
        {    
            DYNAMIC_ASSERT(0);
            unInit(); 
        }
        std::map<U32, AccessInfo*>* pMapAccessInfo = AccessListCsv::getInstance().getMapAccessInfo();
        std::map<U32, AccessInfo*>::iterator front = pMapAccessInfo->begin();
        std::map<U32, AccessInfo*>::iterator back = pMapAccessInfo->end();
        while (front != back)
        {
            addPlace(front->second);

            ++front;
        }
    }
    //--------------------------------------------------------------------------------------------------
    void ShortestPath::unInit()
    {
        nomeMap* tempplaceIdMap = NULL;
        nomeGameMap::iterator frontRegion = mNomeGameMap.begin();
        nomeGameMap::iterator backRegion = mNomeGameMap.end();
        while (frontRegion != backRegion)
        {
            tempplaceIdMap = frontRegion->second;
            nomeMap::iterator frontPlace = tempplaceIdMap->begin();
            nomeMap::iterator backPlace = tempplaceIdMap->end();
            while (frontPlace != backPlace)
            {
                MG_DELETE frontPlace->second;

                ++frontPlace;
            }
            tempplaceIdMap->clear();

            ++frontRegion;
        }
        mNomeGameMap.clear();
        mCityGameMap.clear();
    }
    //--------------------------------------------------------------------------------------------------
    void ShortestPath::addPlace( AccessInfo* pAccessInfo )
    {
        // yuanlinhu ∏„∂®placeID”Î
        //regionMap::iterator iter = mRegionMap.find(1);
    }
}