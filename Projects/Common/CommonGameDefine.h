/******************************************************************************/
#ifndef _COMMONGAMEDEFINE_H_
#define _COMMONGAMEDEFINE_H_
/******************************************************************************/

/******************************************************************************/
//游戏逻辑宏
/******************************************************************************/
namespace MG
{
	#define		MAX_ACCOUNT_LONGIN_NAME_LEN		32
	#define		MAX_ACCOUNT_LONGIN_PSW_LEN		32
	#define		MAX_ACCOUNT_SUPER_PSW_LEN		32
	#define		MAX_CHARACTER_NAME_LEN			32		//武将名字
	#define		MAX_TROOP_NAME_LEN				32		//军队名字
	#define		MAX_COMMON_NAME_LEN				32
	#define		MAX_SERVER_NAME_LEN				64
	#define		MAX_VERSION_NUM_LEN				64
	#define     MAX_CLAN_HOMELANDNAME_LEN		32
	#define     MAX_CLAN_NAME					32
	#define		MAX_CAMPAIGN_NAME				32		//战役的名字
	#define		MAX_PVE_NAME					32		//PVE的名字
    
    #define     MAX_CHAT_CONTENT_ROW_COUNT      1000   //最多显示的聊天行数
    #define     MAX_CHAT_CONTENT_ROW_SIZE       30      //每一行显示的字符数
    #define     MAX_CHAT_CONTENT_ENTER_LEN      100     //一次能输入的聊天字符数

	#define		MAX_REGION_NAME					32		//区域名字
	#define		MAX_CHARACTER_MODEL_NAME_LEN	32		//角色模型
	
	#define		MAX_ART_MAP_RES_PATH_NAME		64		//客户端场景资源
    #define     DB_RECORD_ATTR_NUM              6       //DB中需要记录武将的随机属性个数
    #define     MainGenreal_dead_default_recover_hp_val  1  //主武将死亡后自动复活的会血量（战斗中死亡后会踢出战斗地图）    
	/******************************************************************************/


	typedef 	I32					NetIdType;							//【 网络 】ID的类型
	typedef		U64					ServerUniqueFlagIdType;				// 服务器Flag类型
	typedef		U32					ServerIdType;						// 服务器ID

	typedef 	U64					AccountIdType;						//【 账号 】
	typedef 	U64					GameObjectIdType;					//【 所有的元素 】


	typedef 	U64					PlayerIdType;						//【 玩家 】ID的类型
	typedef		U64					ClanIdType;							//【 家族 】ID的类型	【 从DB读取 】
	typedef		GameObjectIdType	PlayerCharacterIdType;				//【 角色 】ID的类型	【 从DB读取 】

	typedef		GameObjectIdType	ThirdhPartCharacterIdType;			//【 第三方角色 】	ID的类型
	typedef		GameObjectIdType	MonsterIdType;						//【 怪物 】		ID的类型
	
	//新版本 军队
	typedef		GameObjectIdType	TroopSoldierIdType;					//【 士兵 】	ID的类型
	typedef		GameObjectIdType	TroopIdType;						//【 部队 】	ID的类型
	typedef		GameObjectIdType	TroopGroupIdType;					//【 部队组 】	ID的类型
	typedef		GameObjectIdType	ArmyIdType;							//【 军队 】	ID的类型
	typedef		GameObjectIdType	CampIdType;							//【 军营 】	ID的类型

	typedef		GameObjectIdType	TroopGroupIdType;					//【 军队 】ID的类型----旧版本
	typedef		GameObjectIdType	BuildingIdType;						//【 战斗建筑物 】ID的类型

	
	//typedef 	U64				MapObjectIdType;					//
	//typedef 	U64				PlaceObjectIdType;					//

	//【地图】相关
	typedef		U16				GameObjectIndexIdInSceneType;		//MapServer Scene里的GameObject 索引id

	typedef 	U32				RegionIdType;						// MapObject, PlaceObject 统一用
	typedef		I32				ArtMapResIdType;					//
	typedef		I32				ArtPointResId;						//跳转点 
	typedef 	RegionIdType	MapDistributionIdType;				//地图分布
	typedef 	RegionIdType	MapIdType;	
	typedef 	RegionIdType	PlaceIdType;//
	typedef 	RegionIdType	AreaIdType;//

	typedef 	RegionIdType	InstanceIdType;					// 【 副本 】ID的类型
	typedef 	RegionIdType	InstanceUIdType;				// 【 副本 】ID的实例类型 唯一

	//Relation
	typedef		I32				RelationIdType;

	//【政区】相关
	typedef 	I32				DistrictIdType;						//【 政区 】ID的类型
	typedef 	I32				DistrictTreeIdType;					//【 政区树 】ID的类型
	
	typedef 	U64				IdType;
	typedef 	U64				CampaignIdType;
	typedef 	I32				QuestIdType;

    //【道具】相关
    typedef 	U64				ItemIdType;
    typedef 	U32				ItemTempID;

	//【技能】相关
	typedef 	U32				SkillIdType;

	//配置表模板ID
	typedef		U32				TemplateIDType;
	typedef		TemplateIDType	ClanTemplateIDType;
		
	/******************************************************************************/

	const	I32	 MAX_QUEST_RECIEVE_NUM	= 10;					//	玩家可以接受的最大任务数量
	const	I32	 MAX_QUEST_ALL_NUM		= 2000;					//	整个任务的数量

	const Char16 TriggerVersion[] = L"ver1.0";

    /******************************************************************************/
    enum HEADDAMAGE_TYPE
    {
        HEADDAMAGE_TYPE_NULL,

        HEADDAMAGE_TYPE_HP,         
        HEADDAMAGE_TYPE_MP,
        HEADDAMAGE_TYPE_SP,
        HEADDAMAGE_TYPE_ALL,
        HEADDAMAGE_TYPE_MISS, 

        HEADDAMAGE_TYPE_MAX  
    };

    enum HEADDAMAGE_STATE
    {
        HEADDAMAGE_STATE_NULL,

        HEADDAMAGE_STATE_NORMAL,
        HEADDAMAGE_STATE_FADEOUT,

        HEADDAMAGE_STATE_MAX
    };

    enum ACCOUNT_OPERATE_TYPE
    {
        ACCOUNT_OPERATE_NULL,

        ACCOUNT_OPERATE_CREATE,               //帐号创建
        ACCOUNT_OPERATE_DELETE,               //帐号删除
        ACCOUNT_OPERATE_LOGIN,                //帐号登入
        ACCOUNT_OPERATE_LOGOUT,               //帐号登出

        ACCOUNT_OPERATE_MAX
    };

	enum PLAYERCHARACTER_OPERATE_TYPE
	{
		PLAYERCHARACTER_OPERATE_NULL,

		PLAYERCHARACTER_OPERATE_CREATE,               //武将创建
		PLAYERCHARACTER_OPERATE_DELETE,               //武将删除
		PLAYERCHARACTER_OPERATE_LOGIN,                //武将登入
		PLAYERCHARACTER_OPERATE_LOGOUT,               //武将登出

		PLAYERCHARACTER_OPERATE_MAX
	};

	enum PLAY_ANIMATION_TYPE
	{
		PLAY_ANIMATION_NULL,
		PLAY_ANIMATION_STAND,
		PLAY_ANIMATION_ATTACK,
		PLAY_ANIMATION_WALK,
		PLAY_ANIMATION_RUN,
		PLAY_ANIMATION_HURT,
		PLAY_ANIMATION_DIE,
	};

    //需要共享的结构体
    struct AttrData
    {
        UInt    attrId;                     //属性id
        Flt     attrVal;                    //属性值
    };
    struct AttrData_INFO
    {
        static const Int dataSize = sizeof (AttrData);
    };

	struct LineUpSettingInfo
	{
		static const Int line_up_busy_lc_account_login_start_count = 16;				//登录Login排队
		static const Int line_up_busy_fc_account_login_start_count = 8;					//帐号登录FrontServer排队
		static const Int line_up_busy_fc_create_clan_start_count = 32;					//创建家族排队
		static const Int line_up_busy_fc_del_clan_start_count = 32;						//删除家族排队
		static const Int line_up_busy_fc_create_character_start_count = 32;				//创建角色排队
		static const Int line_up_busy_fc_join_game_start_count = 8;						//进入游戏地图排队
	};
    
}


/******************************************************************************/
#endif

