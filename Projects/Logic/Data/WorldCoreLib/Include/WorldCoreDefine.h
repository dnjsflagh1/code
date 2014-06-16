/******************************************************************************/
#ifndef _WORLDCOREDEFINE_H_
#define _WORLDCOREDEFINE_H_
/******************************************************************************/



/******************************************************************************/
namespace MG
{
	//------------------------------------------------------------------------------------------
	#define FORTUNATE_MAX 10000  //计算福源的基数
	#define ROUND_TABLE_MAX 10000
	
	/******************************************************************************/
	//平时建筑类型
	/******************************************************************************/
	enum ORDINARY_BUILDING_TYPE
	{
		OBLT_UNKNOWN         = 0,

		OBLT_SHOP,          // 商店

		OBLT_PLACE,         // 据点
	};
	//------------------------------------------------------------------------------------------
	//战斗房间的位置 
	enum POSITION
	{
		POSITION_INIT	= -1,

		POSITION_1		= 0,
		POSITION_2,
		POSITION_3,
		POSITION_4,
		POSITION_5,

		//POSITION_6,
		//POSITION_7,
		//POSITION_8,
		//POSITION_9,

		POSITION_MAX,		//暂订5个位置
	};

	//PVE房间的位置 
	enum Pve_Position
	{
		Pve_Position_Init	= -1,

		Pve_Position_1		= 0,
		Pve_Position_2,
		Pve_Position_3,
		Pve_Position_4,
		Pve_Position_5,

		Pve_Position_Max,		//5个位置
	};

	//------------------------------------------------------------------------------------------
	enum OPENTYPE
	{
		OT_NULL,
		OT_OPEN,
		OT_CLOSE,
	};

	//------------------------------------------------------------------------------------------
	enum FORCE		//战场
	{
		FORCE_INIT,
		FORCE_ATTACK,		//攻击方
		FORCE_DEFENSE,		//防守方
		FORCE_MONSTER,
		FORCE_MAX,
	};

    //------------------------------------------------------------------------------------------
	enum REGION_OBJ_TYPE
	{
		ROT_UNKNOWN	= 0,

		ROT_MAP_DISTRIBUTION	= 1,			//大地图
		ROT_PLACE				= 2,			//主城
		ROT_TIRO				= 3,			//新手副本
		ROT_PVE					= 4,			//pve副本
		ROT_HOME				= 5,			//家园副本
		ROT_PVP,
		ROT_GROWUP,
		ROT_HISTORY,
		ROT_SPORT,
		ROT_FIGHT,
		ROT_TRAIN,

		
		ROT_MAX,
	};

	enum GameType
	{
		GameType_Null,

		GameType_Rpg,
		GameType_Slg,

		GameType_Max
	};

    //------------------------------------------------------------------------------------------
	enum GAMEOBJ_TYPE
	{
		GOT_UNKNOWN					= 0,

		GOT_PLAYERCHARACTER			,	// 玩家角色

		GOT_TROOP_GROUP				,	// 军队小队组
		GOT_TROOP					,	// 军队小队
		GOT_SOLDIER					,	// 军队小组内的士兵

		GOT_MONSTER					,	// 怪物
		GOT_NPC						,	// NPC
        GOT_BUILDING				,	// 战斗中的建筑
		GOT_ITEM					,	// 物品

		GOT_ORDINARY_BUILDING		,	// 平时的建筑
		GOT_THIRDPARTYCHARACTER		,	// 第三方角色 
		// TODO: 注意网络包的类型大小
	};

	//------------------------------------------------------------------------------------------
	enum GAMEOBJ_QUERY_TYPE
	{
		GQT_UNKNOWN					= 0,

		GQT_PLAYERCHARACTER			= BIT(0),	// 玩家角色
		GQT_TROOP					= BIT(1),	// 军队小组
		GQT_SOLDIER					= BIT(2),	// 军队小组内的士兵
		GQT_MONSTER					= BIT(3),	// 怪物

		GQT_NPC						= BIT(4),	// NPC
		GQT_BUILDING				= BIT(5),	// 战斗中的建筑

		GQT_ITEM					= BIT(6),	// 物品
		GQT_ORDINARY_BUILDING		= BIT(7),	// 平时的建筑
		GQT_THIRDPARTYCHARACTER		= BIT(8),	// 第三方角色 
	};
	
    //------------------------------------------------------------------------------------------
	enum JUMP_TYPE
	{
		JUMP_NORMAL,			    //客户端的 【普通跳转】 MapObject -> PlaceObject 或 PlaceObject -> MapObject
		//JUMP_OUT,					//Place -> 大地图
		JUMP_BORN,				    //NPC, 怪物，。。。 等出生点
		JUMP_ATTACK,			    //战斗开始时 攻击方的出生点
		JUMP_DEFENSE,			    //战斗开始时 防守方的出生点

		JUMP_MAX,
	};

    //------------------------------------------------------------------------------------------
	enum LOADFILE_TYPE
	{
        LFT_NULL,
		LFT_GAME,
		LFT_EDIT,
	};

    /******************************************************************************/
    //角色
    enum CHAR_STATE
    {
        CHAR_STATE_Null = 0,

        CHAR_STATE_Working,                      //上阵
        CHAR_STATE_Freetime,                     //待机
        CHAR_STATE_Close,                        //封闭
        CHAR_STATE_Outdoors,                     //在野

        CHAR_STATE_Max
    };

    //------------------------------------------------------------------------------------------
    enum CHAR_LIFE_STATE
    {
        CHAR_LIFE_STATE_Null = 0,

        CHAR_LIFE_STATE_Living,                   //活的
        CHAR_LIFE_STATE_Dead,                     //非寿命耗尽死亡
        CHAR_LIFE_STATE_LifeEnd,                  //寿命耗尽死亡

        CHAR_LIFE_STATE_Max
    };

    //------------------------------------------------------------------------------------------
    //enum AttackType
    //{
    //   DAMAGE_TYPE_NULL,

    //   //穿刺攻击
    //   DAMAGE_TYPE_1,
    //   DAMAGE_TYPE_2,
    //   DAMAGE_TYPE_3,
    //   DAMAGE_TYPE_4,
    //   DAMAGE_TYPE_5,
    //   DAMAGE_TYPE_6,
    //   DAMAGE_TYPE_7,
    //   DAMAGE_TYPE_8,

    //   DAMAGE_TYPE_MAX
    //};

    //------------------------------------------------------------------------------------------
    enum ATTACK_POS
    {
        ATTACK_POS_NULL,

        ATTACK_POS_FRONT,    //前面
        ATTACK_POS_BACK,     //背面

        ATTACK_POS_MAX
    };

    //------------------------------------------------------------------------------------------
    //enum DamageType       //治疗/伤害类型
    //{
    //    EFFECT_TYPE_NULL,

    //    EFFECT_TYPE_HP = 1,    //HP治疗/伤害
    //    EFFECT_TYPE_MP = 2,    //MP治疗/伤害
    //    EFFECT_TYPE_SP = 4,    //SP治疗/伤害
    //    EFFECT_TYPE_ALL = EFFECT_TYPE_HP|EFFECT_TYPE_MP|EFFECT_TYPE_SP,   //治疗/伤害所有
    //    EFFECT_TYPE_HPMP = EFFECT_TYPE_HP|EFFECT_TYPE_MP,  //治疗/伤害HP和MP
    //};

    //------------------------------------------------------------------------------------------
    enum SKILL_OWNER_TYPE
    {
        SKILL_OWNER_TYPE_NULL,

        SKILL_OWNER_TYPE_SELF,
        SKILL_OWNER_TYPE_OTHER,

        SKILL_OWNER_TYPE_MAX
    };

    //------------------------------------------------------------------------------------------
	enum FormationType
	{
		FT_ROUND,
		FT_RECTANGLE,
	};

    //----------------------------------------------------------------------------------
    enum TROOP_MASTER_TYPE
    {
        TROOP_MASTER_TYPE_NULL = 0,

        TROOP_MASTER_TYPE_PLACEOBJ,                 //据点对象
        TROOP_MASTER_TYPE_CLANOBJ,                  //氏族对象

        TROOP_MASTER_TYPE_MAX
    };

    //----------------------------------------------------------------------------------
    enum TROOP_LIFE_TYPE
    {
        TROOP_LIFE_TYPE_NULL = 0,

        TROOP_LIFE_TYPE_ACTIVE,                     //活的，多余一个人存活
        TROOP_LIFE_TYPE_FIGHT,                      //出征
        TROOP_LIFE_TYPE_DEAD,                       //全部阵亡
        TROOP_LIFE_TYPE_NONE,                       //被遣散，玩家实际不拥有这只部队。

        TROOP_LIFE_TYPE_MAX
    };

    //----------------------------------------------------------------------------------
    enum BUFF_TIME_TYPE
    {
        BUFF_TIME_TYPE_NULL,

        BUFF_TIME_TYPE_NONE,                        //无时间概念
        BUFF_TIME_TYPE_GAME,                        //游戏时间
        BUFF_TIME_TYPE_REAL,                        //现实时间

        BUFF_TIME_TYPE_MAX
    };

    //----------------------------------------------------------------------------------
    enum BUFF_EFFECT_GROUP
    {
        BUFF_EFFECT_GROUP_NULL,

        BUFF_EFFECT_GROUP_SYSTEM,                  //系统
        BUFF_EFFECT_GROUP_NORMAL,                  //一般
        BUFF_EFFECT_GROUP_GOOD,                    //有利
        BUFF_EFFECT_GROUP_BAD,                     //有害

        BUFF_EFFECT_GROUP_MAX
    };

    //----------------------------------------------------------------------------------
    enum BUFF_DISAPPEAR_TYPE
    {
        BUFF_DISAPPEAR_TYPE_NULL,

        //BUFF_DISAPPEAR_TYPE_TIME            = BIT(0),                   //时间到消失
        BUFF_DISAPPEAR_TYPE_CLICK           = BIT(1),                   //点击图标
        BUFF_DISAPPEAR_TYPE_DEAD            = BIT(2),                   //死亡消失
        BUFF_DISAPPEAR_TYPE_HURT            = BIT(3),                   //受到伤害
        BUFF_DISAPPEAR_TYPE_JOINFIGHT       = BIT(4),                   //进入战斗
        BUFF_DISAPPEAR_TYPE_EXITFIGHT       = BIT(5),                   //离开战斗
        BUFF_DISAPPEAR_TYPE_ACTIVECHANGE    = BIT(6),                   //动作变化
        BUFF_DISAPPEAR_TYPE_SKILL           = BIT(7),                   //释放技能
        BUFF_DISAPPEAR_TYPE_SHIELDS         = BIT(8),                   //护盾值耗尽

        BUFF_DISAPPEAR_TYPE_AND             = ( 
                    BUFF_DISAPPEAR_TYPE_CLICK | BUFF_DISAPPEAR_TYPE_DEAD | BUFF_DISAPPEAR_TYPE_HURT
                    | BUFF_DISAPPEAR_TYPE_JOINFIGHT | BUFF_DISAPPEAR_TYPE_EXITFIGHT | 
                    BUFF_DISAPPEAR_TYPE_ACTIVECHANGE | BUFF_DISAPPEAR_TYPE_SKILL | BUFF_DISAPPEAR_TYPE_SHIELDS 
                    ),

        BUFF_DISAPPEAR_TYPE_MAX
    };

    //----------------------------------------------------------------------------------
    enum BUFF_SAVE_TYPE
    {
        BUFF_SAVE_TYPE_NULL,

        BUFF_SAVE_TYPE_NO,          //不保存DB
        BUFF_SAVE_TYPE_YES,         //保存DB

        BUFF_SAVE_TYPE_MAX
    };

    //----------------------------------------------------------------------------------
    enum BUFF_SHOW_TYPE
    {
        BUFF_SHOW_TYPE_NULL,

        BUFF_SHOW_TYPE_TIMEICON,    //显示时间和图标
        BUFF_SHOW_TYPE_ICON,        //只显示图标
        BUFF_SHOW_TYPE_NOSHOW,      //不显示

        BUFF_SHOW_TYPE_MAX
    };

    //----------------------------------------------------------------------------------
    enum  ITEM_BELONG_TYPE
    {
        ITEM_BELONG_TYPE_NULL,

        ITEM_BELONG_TYPE_CLAN,              //氏族仓库
        ITEM_BELONG_TYPE_PLACE,             //据点

        ITEM_BELONG_TYPE_MAX
    };

    //----------------------------------------------------------------------------------
    enum  ATTACK_RESULT_TYPE
    {
        ATTACK_RESULT_TYPE_NULL,

        ATTACK_RESULT_TYPE_INVALID,                 //无效
        ATTACK_RESULT_TYPE_DODGE,                   //躲避
        ATTACK_RESULT_TYPE_ABSORB,                  //吸收
        ATTACK_RESULT_TYPE_DEAD,                    //死亡
        ATTACK_RESULT_TYPE_HURT,                    //受伤
		ATTACK_RESULT_TYPE_HURT_CHANGE_RECOVER,     //伤害转治疗。

        ATTACK_RESULT_TYPE_RECOVER = 10,            //治疗回复
		ATTACK_RESULT_TYPE_RECOVER_INVALID,         //治疗无效。
		

        ATTACK_RESULT_TYPE_MAX
    };
    //----------------------------------------------------------------------------------
    enum ITEM_DELETE_ERROR
    {
        ITEM_DELETE_ERROR_SUCCEED,
        ITEM_DELETE_ERROR_NONE,                               //没有道具。
        ITEM_DELETE_ERROR_CANNOT,                             //不能删除
        ITEM_DELETE_ERROR_UI,                                 //此界面没有删除功能
		ITEM_DELETE_ERROR_NOT_ENOUGH_NUM
    };
    //----------------------------------------------------------------------------------
	enum FIGHT_TYPE
	{
		FIGHT_TYPE_NULL,
	};

	//复活方式
	enum AliveType
	{
		AliveType_TimeOut,			//复活时间到 【复活点复活】
		AliveType_User_CurPos,		//玩家 【原地复活】
		AliveType_User_AlivePos,	//玩家 【复活点复活】

	};
    //////////////////////////////////////////////////////////////////////////
	enum GAMEJUDGE_TYPE
	{    

		 //类型继续添加
         GAMEJUDGE_TYPE_NULL,
		 GAMEJUDGE_TYPE_SUCCESS,
		 GAMEJUDGE_TYPE_CLAN_COMPLETE_QUEST_ERROR,			//需要完成特定任务
		 GAMEJUDGE_TYPE_CLAN_LEVEL_ERROR,
		 ///////////////////////////////////////
		 GAMEJUDGE_TYPE_CHARACTER_LEVEL_ERROR,				//等级
		 GAMEJUDGE_TYPE_CHARACTER_TYPE_ERROR,				//角色类型
		 GAMEJUDGE_TYPE_CHARACTER_GENDER_TYPE_ERROR,		//性别
         GAMEJUDGE_TYPE_CHARACTER_POWERFULL_TYPE_ERROR,		//职业
		 GAMEJUDGE_TYPE_UNKNOWN_ERROR                        //未知

	};
	//////////////////////////////////////////////////////////////////////////
	enum CLAN_STATUS_TYPE
	{
		CLAN_STATUS_TYPE_NULL = 0,

		CLAN_STATUS_TYPE_NOMAL,				//正常
		CLAN_STATUS_TYPE_DEL,				//删除
		CLAN_STATUS_TYPE_CLOSED,			//封闭
		CLAN_STATUS_TYPE_TURNNING,			//转服中
		CLAN_STATUS_TYPE_WAIT_DEL,			//等待删除

		CLAN_STATUS_TYPE_MAX
	};


}

#endif