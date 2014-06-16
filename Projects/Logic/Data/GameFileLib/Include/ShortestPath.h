//**********************************************************************************************************************
#ifndef _H_SHORTEST_PATH_
#define _H_SHORTEST_PATH_
//**********************************************************************************************************************
#include "GameFilePreqs.h"
//**********************************************************************************************************************
namespace MG
{

    class ShortestPath
    {
    public:
        ShortestPath(){;}
        ~ShortestPath();
        SINGLETON_INSTANCE(ShortestPath);

    public: //程序专用接口
        Bool                getShortestPath(U32 regionId, U32 startPlaceId, U32 endPlaceId, std::vector<U32>& placeVector);

    public:
        // 初始化节点。
        void                initRegionMap();

    private:
        // 反初始化。
        void                unInit();
        // 加place
        void                addPlace(AccessInfo* pAccessInfo);

    private:
        typedef std::vector<U32>                    placeIdVector;       //据点联通的据点集合
        typedef std::map<U32, placeIdVector*>       placeIdMap;          //据点对应的据点集合

        typedef placeIdMap                          cityMap;             //一个郡下的据点集合
        typedef std::map<U32, cityMap*>             cityGameMap;         //游戏中的郡集合

        typedef placeIdMap                          nomeMap;             //一个州下的据点集合
        typedef std::map<U32, nomeMap*>             nomeGameMap;         //游戏中的州集合

        nomeGameMap                                 mNomeGameMap;
        cityGameMap                                 mCityGameMap;
    };
}
//**********************************************************************************************************************
#endif
//**********************************************************************************************************************