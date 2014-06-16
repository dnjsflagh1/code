/******************************************************************************/
#ifndef _GAMEFILEPREQS_H_
#define _GAMEFILEPREQS_H_
/******************************************************************************/

#include "CommonGameDefine.h"
#include "GameFileDefine.h"

/******************************************************************************/
namespace MG
{
/******************************************************************************/
	struct CalendarInfo;
	class CalendarInfos;
	struct AttributeAppendInfo;
	class AttributeAppend;
	struct AttributeInitInfo;
	class AttributeInit;
	struct AttributeJudgeInfo;
	class AttributeJudge;

	class CharacterVisionEvent;
	struct CharacterVisionEventInfo;

	struct StatusBaseInfo;
	struct StatusCharacterData;
	struct StatusData;

	class StatusCharacterList;
	class StatusList;

	// MG_CN_MODIFY
	// 资源打包类.
	class IMGExternalPackManager;

	struct CharacterGenrealInfo;
	class CharacterGenrealList;

	struct CharacterArmyInfo;
	class CharacterArmyList;

	struct CharacterBuildInfo;
	class CharacterBuildList;

	struct CharacterMonsterInfo;
	class CharacterMonsterList;

	struct CharacterNpcInfo;
	class CharacterNpcList;

	struct CharacterObjectInfo;
	class CharacterObjectList;

    struct PlaceListCsvInfo;
    class  PlaceListCsv;

    struct AccessInfo;
    class  AccessListCsv;

    class ShortestPath;



	struct DistrictTemplateInfo;
	struct DistrictObjectInfo;

    struct CharacterTempInfo;
    class  CharacterTemplate;

	class SceneFileObject;
	class SceneFileLoader;


	class BattleConfig;

	//音乐文件
	struct AudioResInfo;
	class AudioRes;
	
	//----------------------------------------------【 新版本】  元林虎 整理 开始--------------------------------------//
	//ArtIcon表
	struct  ArtIconResCsvInfo;
	class ArtIconResCsv;

	//政区 【新版本】
	struct DistrictData;
	class DistrictListCsv;

	struct DistrictTreeInfo;
	class DistrictTreeCsv;

	class DistrictListCsvInfo;
	class District;
	
	//地图 【新版本】
	
	struct ArtMapResCsvInfo;
	class ArtMapResCsv;

	struct AreaListCsvInfo;
	class AreaListCsv;

	struct MapListCsvInfo;
	class MapListCsv;

	struct PlaceListCsvInfo;
	class PlaceListCsv;

	struct MapDistributionCsvInfo;
	class MapDistributionCsv;

	//副本【新版本】
	struct InstanceListCsvInfo;
	class InstanceListCsv;
	
	struct InstanceTimeListCsvInfo;
	class InstanceTimeListCsv;

	struct InstanceAtkListCsvInfo;
	class InstanceAtkListCsv;
	struct InstanceAtkCampListCsvInfo;
	class InstanceAtkCampListCsv;
	struct InstanceAtkStrengthListCsvInfo;
	class InstanceAtkStrengthListCsv;

	struct InstanceHomeListCsvInfo;
	class InstanceHomeListCsv;

	struct InstancePVEListCsvInfo;
	class InstancePVEListCsv;

	struct InstanceTiroListCsvInfo;
	class InstanceTiroListCsv;
	//副本【新版本】 End
	
	//战斗统计数据
	struct BattleFieldNoticeListCsvInfo;
	class BattleFieldNoticeListCsv;

	struct BattleScoresParamListCsvInfo;
	class BattleScoresParamListCsv;

	struct BattleScoresRankListCsvInfo;
	class BattleScoresRankListCsv;
	
	//物品相关
	struct ItemShopInfo;
	class ItemShopTemplate;

	struct itemSiteInfo;
	class ItemSiteTemplate;

	struct ItemInfo;
	class ItemTemplate;

	struct ItemClanListCsvInfo;
	class ItemClanListCsv;

	struct ItemEquipInfo;
	class ItemEquipTemplate;

	struct ItemExpListCsvInfo;
	class ItemExpListCsv;

	struct ItemMoneyInfo;
	class ItemMoneyTemplate;
	
	struct ItemOtherInfo;
	class ItemOtherTemplate;

	struct ItemUseInfo;
	class ItemUseTemplate;

	//随机武将 begin
	struct GeneralRandomCsvInfo;
	class GeneralRandomCsv;

	struct GeneralRecruitCsvInfo;
	class GeneralRecruitCsv;
	//随机武将 end
	
	//----------------------------------------------【 新版本】  元林虎 整理 结束--------------------------------------//

	/******************************************************************************/

    //--------------------------------------------------------------------------------------
    struct ItemNum
    {
        U32		itemTemplate;
        U32     num;
        ItemNum()
            :itemTemplate(0)
            ,num(0)
        {
            ;
        }
        ItemNum(const ItemNum& A)
        {
            itemTemplate = A.itemTemplate;
            num = A.num;
        }
        ItemNum& operator=(const ItemNum& A)
        {
            itemTemplate = A.itemTemplate;
            num = A.num;

            return *this;
        }
    };

    //--------------------------------------------------------------------------------------
    struct RandomGroup
    {
        U32 itemGroupId;
        U32 num;
    };
	//-----------------------------------------------------------------------------
	struct AppendAttr
	{
		U32 id;
		Flt value;
	};

}

#endif	//_GAMEFILEPREQS_H_