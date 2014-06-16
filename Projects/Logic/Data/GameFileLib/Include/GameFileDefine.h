/******************************************************************************/
#ifndef _GAME_FILE_DEFINE_H_
#define _GAME_FILE_DEFINE_H_
/******************************************************************************/

/******************************************************************************/
namespace MG
{
	#define TROOP_GROUP_NUM		5	//同时创建的军队个数

	#define SCENE_OBJECT_GROUP_STR_STATIC	"Static"		//静态物件载入，这个是客户端自动载入的物件，和服务器无关
	#define SCENE_OBJECT_GROUP_STR_OBJECT	"Object"		//物件载入，各种交互事件的物件
	#define SCENE_OBJECT_GROUP_STR_REGION	"Region"		//游戏中区域，服务器通知后客户端载入。
	#define SCENE_OBJECT_GROUP_STR_PLACE	"Place"			//据点，服务器通知后客户端载入
	#define SCENE_OBJECT_GROUP_STR_POINT	"Point"			//跳转点，服务器通知后客户端载入，具体信息来自GameFileLib::PointTemplte
	#define SCENE_OBJECT_GROUP_STR_NPC		"NPC"			//NPC，服务器通知后客户端载入，具体信息来自GameFileLib::CharacterTemplate		
	#define SCENE_OBJECT_GROUP_STR_MONSTER	"Monster"		//游戏中的单个怪，服务器通知后客户端载入，具体信息来自GameFileLib::CharacterTemplate
	#define SCENE_OBJECT_GROUP_STR_TROOP	"Troop"			//游戏中的组群怪，服务器通知后客户端载入，具体信息来源于GameFileLib::TroopTemplate
	#define SCENE_OBJECT_GROUP_STR_BUILDING	"Building"		//游戏中建筑，服务器通知后客户端载入。
	#define SCENE_OBJECT_GROUP_STR_GENERAL	"General"		//游戏中创建武将。
	#define SCENE_OBJECT_GROUP_STR_EFFECT	"Effect"		//游戏中创建特效。

	/******************************************************************************/

	#define  NAME_LENGTH      32
	#define  ATTR_PARA_NUM 6
	#define  APPENDATTR_NUM  8
	#define  DISPOSITION_NUM 16
	#define  CHAR_SKILL_NUM  8
	#define  CHAR_ABILITYAPPEND_ID_NUM  4
	#define  CHAR_SKILL_ID_NUM  2
	#define  ITEM_RANDOM_GROUP_NUM 16
	#define	 TIME_HUNDRED_MS	100				//百毫秒
	#define  PERMILLAGE_VALUE  0.001			//千分比
	#define  THOUSAND_VALUE  1000			//千分比

	/******************************************************************************/


	//enum JumpMapType
	//{
	//	JMT_Null,

	//	JMT_Distribution	= 1,		//世界分块地图
	//	JMT_Place			= 2,		//地点内景地图
	//	JMT_Building		= 3,		//建筑内部地图
	//	JMT_Direction		= 4,		//直接跳转地图
	//	JMT_Instance		= 5,		//副本地图

	//	JMT_Max,
	//};

	//-------------------------------------------------------------------------------------------
	enum RECRUIT_POSITION
	{
		RECRUIT_POSITION_1,
		RECRUIT_POSITION_2,
		RECRUIT_POSITION_3,
		RECRUIT_POSITION_4,
		RECRUIT_POSITION_5,

		RECRUIT_POSITION_MAX
	};

	//-------------------------------------------------------------------------------------------
	enum CHAR_LVL_USETYPE
	{
		CHAR_LVL_USETYPE_NULL,

		CHAR_LVL_USETYPE_CLAN,						//氏族经验
		CHAR_LVL_USETYPE_CLAN_POS,					//氏族官位经验
		CHAR_LVL_USETYPE_CLAN_FEATS,				//氏族功绩经验
		CHAR_LVL_USETYPE_CLAN_SPARE,				//氏族备用经验
		CHAR_LVL_USETYPE_CHAR_LVL,					//武将升级经验
		CHAR_LVL_USETYPE_CHAR_TRUN,					//武将转生经验
		CHAR_LVL_USETYPE_CHAR_SKILL,				//武将技能升级经验
		CHAR_LVL_USETYPE_CHAR_SPARE,				//武将备用经验
		CHAR_LVL_USETYPE_AYM_LVL,					//军队升级经验
		CHAR_LVL_USETYPE_AYM_SPARE,					//军队备用经验
		CHAR_LVL_USETYPE_BUILD_LVL,					//建筑升级经验
		CHAR_LVL_USETYPE_BUILD_SPARE,				//建筑备用经验
		CHAR_LVL_USETYPE_OTHER_SPARE1,				//其它备用经验1
		CHAR_LVL_USETYPE_OTHER_SPARE2,				//其它备用经验1
		CHAR_LVL_USETYPE_OTHER_SPARE3,				//其它备用经验1
		CHAR_LVL_USETYPE_OTHER_SPARE4,				//其它备用经验1
		
		CHAR_LVL_USETYPE_MAX
	};
	//--------------------------------------------------------------------------------
	enum  TROOPTEMPLATE_TYPE
	{
		TROOPTEMPLATE_TYPE_NULL = 0,                    //0～无意义

		TROOPTEMPLATE_TYPE_BROADSWORD   ,           //  1～刀兵
		TROOPTEMPLATE_TYPE_SPEAR        ,           //  2～枪兵
		TROOPTEMPLATE_TYPE_HORSE        ,           //  3～骑兵
		TROOPTEMPLATE_TYPE_BOW          ,           //  4～弓兵
		TROOPTEMPLATE_TYPE_WEAPON       ,           //  5～兵器
		TROOPTEMPLATE_TYPE_OTHER        ,           //  6后陆续添加
		TROOPTEMPLATE_TYPE_SPECIAL		,			//	7特殊
		TROOPTEMPLATE_TYPE_WATER		,			//	8水军

		TROOPTEMPLATE_TYPE_MAX
	};
	//--------------------------------------------------------------------------------
	enum  
	{
		TROOPTEMPLATE_STATE_GRASSLAND = 0   ,       //草地
		TROOPTEMPLATE_STATE_WOODLAND        ,       //林地
		TROOPTEMPLATE_STATE_MOUNTAINLAND    ,       //山地
		TROOPTEMPLATE_STATE_SNOWFIELD       ,       //雪地
		TROOPTEMPLATE_STATE_SAND            ,       //沙地
		TROOPTEMPLATE_STATE_WATER           ,       //水中

		TROOPTEMPLATE_STATE_MAX
	};
	//-----------------------------------------------------------------------------
	enum CHAR_TYPE
	{
		CHAR_TYPE_NULL = 0,

		CHAR_TYPE_GENREAL,      //武将
		CHAR_TYPE_ARMY,         //军队
		CHAR_TYPE_THING,        //物件
		CHAR_TYPE_FUNCTION,     //功能

		CHAR_TYPE_Max
	};

	//-----------------------------------------------------------------------------
	enum GENDER_TYPE
	{
		GENDER_TYPE_NULL = 0,

		GENDER_TYPE_MAN,        //男人
		GENDER_TYPE_WOMAN,      //女人
		GENDER_TYPE_NONE_SEX,   //无性别：如军队，建筑物等

		GENDER_TYPE_MAX
	};

	//-----------------------------------------------------------------------------
	enum  FUNCTION_FLAG
	{
		FUNCTION_FLAG_NULL = 0,

		FUNCTION_FLAG_ACTION,    //激活
		FUNCTION_FLAG_AUTOWAY,   //寻路

		FUNCTION_FLAG_MAX
	};

	//-----------------------------------------------------------------------------
	enum  POWERFUL_TYPE
	{
		POWERFUL_TYPE_NULL = 0,

		POWERFUL_TYPE_FIRST,           //一流
		POWERFUL_TYPE_SECOND,          //二流
		POWERFUL_TYPE_THIRD,           //三流
		POWERFUL_TYPE_NORMAL,          //不入流

		POWERFUL_TYPE_MAX
	};

	//-----------------------------------------------------------------------------
	enum CHARACTER_OBJ_MUTUALTYPE
	{
		CHARACTER_OBJ_MUTUALTYPE_NULL,

		CHARACTER_OBJ_MUTUALTYPE_Touch,			//碰撞交互
		CHARACTER_OBJ_MUTUALTYPE_Action,		//动作交互

		CHARACTER_OBJ_MUTUALTYPE_MAX,
	};

	//-----------------------------------------------------------------------------
	enum CHARACTER_TYPE
	{
		CHARACTER_TYPE_NULL,

		CHARACTER_TYPE_GENREAL,			//武将
		CHARACTER_TYPE_ARMY,			//军队
		CHARACTER_TYPE_BUILD,			//建筑
		CHARACTER_TYPE_MONSTER,			//怪物
		CHARACTER_TYPE_NPC,				//NPC
		CHARACTER_TYPE_OBJ,				//物件

		CHARACTER_TYPE_MAX
	};

	//-----------------------------------------------------------------------------
	enum  CHAR_FORMULA_TYPE
	{
		CHAR_FORMULA_TYPE_NULL = 0,

		CHAR_FORMULA_TYPE_POWER,       //猛将
		CHAR_FORMULA_TYPE_QUICK,       //统帅
		CHAR_FORMULA_TYPE_BRAINS,      //谋士
		CHAR_FORMULA_TYPE_MANAGER,     //能吏

		CHAR_FORMULA_TYPE_MAX
	};

	//-----------------------------------------------------------------------------
	/*enum CHAR_RACE_TYPE
	{
		CHAR_RACE_TYPE_NULL,

		CHAR_RACE_TYPE_1,               //天道
		CHAR_RACE_TYPE_2,               //修罗道
		CHAR_RACE_TYPE_3,               //人道
		CHAR_RACE_TYPE_4,               //畜生道
		CHAR_RACE_TYPE_5,               //鬼道
		CHAR_RACE_TYPE_6,               //地狱道

		CHAR_RACE_TYPE_MAX
	};
    */
	//-----------------------------------------------------------------------------
	enum  CHAR_ATTRRAND_TYPE
	{
		CHAR_ATTRRAND_TYPE_NULL = 0,

		CHAR_ATTRRAND_TYPE_NO,         //不随机
		CHAR_ATTRRAND_TYPE_YES,        //随机

		CHAR_ATTRRAND_TYPE_MAX
	};
	enum CHAR_BUILD_TYPE
	{
		CHAR_BUILD_TYPE_NULL,
		CHAR_BUILD_TYPE_NOT_FIGHT,			//1~系统建筑(不参加战斗)
		CHAR_BUILD_TYPE_NORMAL,				//2~一般建筑(不攻击)
		CHAR_BUILD_TYPE_FIGHT,				//3~战斗建筑(会攻击)、
		CHAR_BUILD_TYPE_WALL,				//4~城墙之墙
		CHAR_BUILD_TYPE_CORNER,				//5~城墙之转角
		CHAR_BUILD_TYPE_BAR,				//6~城墙之门楼
		CHAR_BUILD_TYPE_TURRET,				//7~城墙之角楼
		CHAR_BUILD_TYPE_GATE,				//8~城墙之城门
		CHAR_BUILD_TYPE_BRIDGE,				//9~城墙之吊桥
		CHAR_BUILD_TYPE_RIVER,				//10~城墙之护城河
		CHAR_BUILD_TYPE_BARRACKS,			//11~兵营
		CHAR_BUILD_TYPE_HEADQUARTERS,		//12~大本营

		CHAR_BUILD_TYPE_MAX
	};
	//--------------------------------------------------------------------------------------------------
	enum  FORMULA_TYPE
	{
		FORMULA_TYPE_NULL = 0,


		FORMULA_TYPE_Power  = 1,            //适合力量型
		FORMULA_TYPE_QUICK  = 2,            //适合敏捷型
		FORMULA_TYPE_BRAINS = 4,            //适合智力型
		FORMULA_TYPE_ALL    = 7,            //适合所有

		FORMULA_TYPE_MAX
	};
	//--------------------------------------------------------------------------------------------------
	enum CDTEMP_USETYPE
	{
		CDTEMP_USETYPE_NULL,

		CDTEMP_USETYPE_SERVER,          //服务器使用
		CDTEMP_USETYPE_CLIENT,          //客户端使用

		CDTEMP_USETYPE_MAX
	};
	//--------------------------------------------------------------------------------------------------
	enum CDTEMP_TIMETYPE
	{
		CDTEMP_TIMETYPE_NULL, 

		CDTEMP_TIMETYPE_REAL,           //真实时间
		CDTEMP_TIMETYPE_ONLINE,         //在线时间

		CDTEMP_TIMETYPE_MAX
	};
	//--------------------------------------------------------------------------------------------------
	enum CDTEMP_SAVETYPE
	{
		CDTEMP_SAVETYPE_NULL,

		CDTEMP_SAVETYPE_NOSAVE,         //不储存
		CDTEMP_SAVETYPE_SAVE,           //储存

		CDTEMP_SAVETYPE_MAX
	};
	//--------------------------------------------------------------------------------------------------
	enum CD_MASTER_TYPE
	{
		CD_MASTER_TYPE_NULL,

		CD_MASTER_TYPE_CLAN,                        //氏族CD
		CD_MASTER_TYPE_CHARACTER,                   //氏族下的武将CD
		CD_MASTER_TYPE_TROOP,                       //氏族下的军队CD
		CD_MASTER_TYPE_BUILD,                       //氏族下的战斗建筑物CD
		CD_MASTER_TYPE_CITY,                        //城市CD
		CD_MASTER_TYPE_FROCE,                       //势力CD

		CD_MASTER_TYPE_MAX
	};
	//--------------------------------------------------------------------------------------------------
	enum ITEM_IDENTIFY_TYPE
	{
		ITEM_IDENTIFY_TYPE_NULL,

		ITEM_IDENTIFY_TYPE_NO,                   //不需要鉴定
		ITEM_IDENTIFY_TYPE_NEED,                 //需要鉴定

		ITEM_IDENTIFY_TYPE_MAX
	};
	//--------------------------------------------------------------------------------------------------
	enum  ITEM_DISPPEAR_TYPE  //二进制
	{
		ITEM_DISPPEAR_TYPE_NULL,

		ITEM_DISPPEAR_TYPE_USE = 1,                 //使用后消失
		ITEM_DISPPEAR_TYPE_DURABLE = 2,             //耐久耗尽
		ITEM_DISPPEAR_TYPE_TIME = 4,                //时间耗尽
		ITEM_DISPPEAR_TYPE_CLAN_OFFLINE = 8,        //氏族下线
		ITEM_DISPPEAR_TYPE_CHARACTER_DEAD = 16,     //角色死亡
		ITEM_DISPPEAR_TYPE_JUMPMAP = 32,            //跳地图

		ITEM_DISPPEAR_TYPE_MAX
	};
	//--------------------------------------------------------------------------------------------------
	enum ITEM_FORBID_TYPE
	{
		ITEM_FORBID_TYPE_NULL,

		ITEM_FORBID_TYPE_GIVEUP = 1,                //不可丢弃
		ITEM_FORBID_TYPE_SHOP = 2,                  //不可回收
		ITEM_FORBID_TYPE_REPAIR = 4,                //不可修理
		ITEM_FORBID_TYPE_TRADE = 8,                 //不可交易
		ITEM_FORBID_TYPE_CIRCULATE = 16,            //不可流通
		ITEM_FORBID_TYPE_ARTIFICE = 32,             //不可炼化

		ITEM_FORBID_TYPE_MAX
	};
	//--------------------------------------------------------------------------------------------------
	enum ITEM_TIPS_TYPE
	{
		ITEM_TIPS_TYPE_GENERAL,

		ITEM_TIPS_TYPE_SHOP = 1,                    //商店显示
		ITEM_TIPS_TYPE_CALLBACK = 2,                //回购栏显示
		ITEM_TIPS_TYPE_MAX
	};
	//--------------------------------------------------------------------------------------------------
	enum  ITEM_EXISTENCE_TIME_TYPE
	{
		ITEM_EXISTENCE_TIME_TYPE_NULL,

		ITEM_EXISTENCE_TIME_TYPE_REAL,          //现实时间
		ITEM_EXISTENCE_TIME_TYPE_GAME,          //游戏时间

		ITEM_EXISTENCE_TIME_TYPE_MAX
	};
	//--------------------------------------------------------------------------------------------------
	enum  ITEM_BIND_TYPE
	{
		ITEM_BIND_TYPE_NULL,          //不绑定

		ITEM_BIND_TYPE_GET,          //获得绑定
		ITEM_BIND_TYPE_USE,          //使用绑定

		ITEM_BIND_TYPE_MAX
	};
	//--------------------------------------------------------------------------------------------------
	enum  ITEM_SITE_TYPE
	{
		ITEM_SITE_TYPE_NULL,

		ITEM_SITE_TYPE_PLACE,             //据点
		ITEM_SITE_TYPE_CLAN,              //氏族仓库
		ITEM_SITE_TYPE_CHARACTER_BAG,     //角色背包
		ITEM_SITE_TYPE_CHARACTER_EQUIP,   //角色装备
		ITEM_SITE_TYPE_AUTION,            //拍卖栏
		ITEM_SITE_TYPE_BUYBACK,           //回购栏
		ITEM_SITE_TYPE_MAIL,              //邮箱
		ITEM_SITE_TYPE_DEL,               //已删除

		ITEM_SITE_TYPE_MAX
	};
	//----------------------------------------------------------------------------------
	enum ITEM_USER_DEFINED_ID_TYPE
	{
         ITEM_USER_DEFINED_ID_TYPE_NULL,
         
		 ITEM_USER_DEFINED_ID_TYPE_CLAN,
		 ITEM_USER_DEFINED_ID_TYPE_PLAYER_CHARACTER,
         
	};
	//----------------------------------------------------------------------------------
	enum ITEM_REPLACE_TYPE
	{
		ITEM_REPLACE_TYPE_NULL,

		ITEM_REPLACE_TYPE_EQUAL,         //同格替换
		ITEM_REPLACE_TYPE_QUEUE,         //队列替换

		ITEM_REPLACE_TYPE_MAX
	};
	//----------------------------------------------------------------------------------
	enum ITEM_RANDOM_USETYPE
	{
		ITEM_RANDOM_USETYPE_NULL,

		ITEM_RANDOM_USETYPE_DROP,       //掉落
		ITEM_RANDOM_USETYPE_USEITEM,    //使用物品
		ITEM_RANDOM_USETYPE_SHOP,       //商店
		ITEM_RANDOM_USETYPE_COMPOSE,    //合成
		ITEM_RANDOM_USETYPE_RESOLVE,    //分解

		ITEM_RANDOM_USETYPE_MAX
	};
	//----------------------------------------------------------------------------------
	enum ITEM_RANDOM_TYPE
	{
		ITEM_RANDOM_TYPE_NULL,

		ITEM_RANDOM_TYPE_ONCE,          //随机一次
		ITEM_RANDOM_TYPE_EVERY,         //依次随机

		ITEM_RANDOM_TYPE_MAX
	};
	//---------------------------------------------------------------------------------- 
	enum ITEM_USE_RESTORE_TYPE
	{
		ITEM_USE_RESTORE_TYPE_NULL,
		ITEM_USE_RESTORE_TYPE_REAL_VALUE,            //实数值
		ITEM_USE_RESTORE_TYPE_PERMILLAGE_VALUE,      //千分比
		ITEM_USE_RESTORE_TYPE_MAX
	};
	//----------------------------------------------------------------------------------
	enum IOCN_ART_TYPE
	{
		IOCN_ART_TYPE_NULL,

		IOCN_ART_TYPE_ITEM,					//物品
		IOCN_ART_TYPE_SKILL,				//技能
		IOCN_ART_TYPE_MALEHEAD_LARGE,       //男头像 大
		IOCN_ART_TYPE_FEMALEHEAD_LARGE,     //女头像 大
		IOCN_ART_TYPE_NPC,					//NPC
		IOCN_ART_TYPE_MONSTER,				//怪物
		IOCN_ART_TYPE_PLACE,                //地点
		IOCN_ART_TYPE_FORCE,                //势力
		IOCN_ART_TYPE_BUILDING,             //建筑
		IOCN_ART_TYPE_ARMY,                 //军队
        IOCN_ART_TYPE_NPC_TOP_INDENTIFI,    //NPC头顶标识    
		IOCN_ART_TYPE_SMALL,				//小图标
		IOCN_ART_TYPE_SEASON,               //季节
		IOCN_ART_TYPE_DayOfTime,			//时辰
		ICON_ART_TYPE_CLAN_FLAG,			//氏族图案
		ICON_ART_TYPE_CLAN_BACK,			//氏族背景图案

		IOCN_ART_TYPE_MAX
	};
	//----------------------------------------------------------------------------------
	enum ITEM_GROUP_USETYPE
	{
		ITEM_GROUP_USETYPE_NULL,

		ITEM_GROUP_USETYPE_DROP,        //物品掉落
		ITEM_GROUP_USETYPE_USE,         //使用物品（如开宝箱）
		ITEM_GROUP_USETYPE_SHOP,        //商店
		ITEM_GROUP_USETYPE_COMPOSE,     //合成
		ITEM_GROUP_USETYPE_RESLOVE,     //分解

		ITEM_GROUP_USETYPE_MAX
	};
	//----------------------------------------------------------------------------------
	enum ATTR_ID
	{
		ATTR_ID_NULL = 0,

		ATTR_ID_System01Base        ,      //移动速度
		ATTR_ID_System01Int         ,      //移动速度
		ATTR_ID_System01Perm        ,      //移动速度
		ATTR_ID_System01            ,      //移动速度

		ATTR_ID_System02Base        ,      //骑乘速度
		ATTR_ID_System02Int         ,      //骑乘速度
		ATTR_ID_System02Perm        ,      //骑乘速度
		ATTR_ID_System02            ,      //骑乘速度

		ATTR_ID_System03Base        ,      //视野范围
		ATTR_ID_System03Int         ,      //视野范围
		ATTR_ID_System03Perm        ,      //视野范围
		ATTR_ID_System03            ,      //视野范围

		ATTR_ID_System04Base        ,      //探测范围
		ATTR_ID_System04Int         ,      //探测范围
		ATTR_ID_System04Perm        ,      //探测范围
		ATTR_ID_System04            ,      //探测范围

		ATTR_ID_System05Base        ,      //攻击频率
		ATTR_ID_System05Int         ,      //攻击频率
		ATTR_ID_System05Perm        ,      //攻击频率
		ATTR_ID_System05            ,      //攻击频率

		ATTR_ID_System06Base        ,      //攻击距离
		ATTR_ID_System06Int         ,      //攻击距离
		ATTR_ID_System06Perm        ,      //攻击距离
		ATTR_ID_System06            ,      //攻击距离

		
		ATTR_ID_Talent1Init         ,      //力量
		ATTR_ID_Talent1Up           ,      //力量
		ATTR_ID_Talent1Base         ,      //力量
		ATTR_ID_Talent1Int          ,      //力量
		ATTR_ID_Talent1Perm         ,      //力量
		ATTR_ID_Talent1             ,      //力量

		ATTR_ID_Talent2Init         ,      //敏捷
		ATTR_ID_Talent2Up           ,      //敏捷
		ATTR_ID_Talent2Base         ,      //敏捷
		ATTR_ID_Talent2Int          ,      //敏捷
		ATTR_ID_Talent2Perm         ,      //敏捷
		ATTR_ID_Talent2             ,      //敏捷

		ATTR_ID_Talent3Init         ,      //智力
		ATTR_ID_Talent3Up           ,      //智力
		ATTR_ID_Talent3Base         ,      //智力
		ATTR_ID_Talent3Int          ,      //智力
		ATTR_ID_Talent3Perm         ,      //智力
		ATTR_ID_Talent3             ,      //智力

		ATTR_ID_Talent4Init         ,      //悟性
		ATTR_ID_Talent4Up           ,      //悟性
		ATTR_ID_Talent4Base         ,      //悟性
		ATTR_ID_Talent4Int          ,      //悟性
		ATTR_ID_Talent4Perm         ,      //悟性
		ATTR_ID_Talent4             ,      //悟性

		ATTR_ID_Talent5Init         ,      //体质
		ATTR_ID_Talent5Up           ,      //体质
		ATTR_ID_Talent5Base         ,      //体质
		ATTR_ID_Talent5Int          ,      //体质
		ATTR_ID_Talent5Perm         ,      //体质
		ATTR_ID_Talent5             ,      //体质

		ATTR_ID_Talent6Init         ,      //心神
		ATTR_ID_Talent6Up           ,      //心神
		ATTR_ID_Talent6Base         ,      //心神
		ATTR_ID_Talent6Int          ,      //心神
		ATTR_ID_Talent6Perm         ,      //心神
		ATTR_ID_Talent6             ,      //心神

		ATTR_ID_HpMaxBase           ,      //最大生命
		ATTR_ID_HpMaxInt            ,      //最大生命
		ATTR_ID_HpMaxPerm           ,      //最大生命
		ATTR_ID_HpMax               ,      //最大生命

		ATTR_ID_MpMaxBase           ,      //最大法力
		ATTR_ID_MpMaxInt            ,      //最大法力
		ATTR_ID_MpMaxPerm           ,      //最大法力
		ATTR_ID_MpMax               ,      //最大法力

		ATTR_ID_SpMaxBase           ,      //最大气力
		ATTR_ID_SpMaxInt            ,      //最大气力
		ATTR_ID_SpMaxPerm           ,      //最大气力
		ATTR_ID_SpMax               ,      //最大气力

		ATTR_ID_Rank1Base           ,      //命中
		ATTR_ID_Rank1Int            ,      //命中
		ATTR_ID_Rank1PermRate       ,      //命中率
		ATTR_ID_Rank1Rate           ,      //命中率

		ATTR_ID_Rank2Base           ,      //躲避
		ATTR_ID_Rank2Int            ,      //躲避
		ATTR_ID_Rank2PermRate       ,      //躲避率
		ATTR_ID_Rank2Rate           ,      //躲避率

		ATTR_ID_Rank3Base           ,      //重击
		ATTR_ID_Rank3Int            ,      //重击
		ATTR_ID_Rank3PermRate       ,      //重击率
		ATTR_ID_Rank3Rate           ,      //重击率

		ATTR_ID_Rank4Base           ,      //格挡
		ATTR_ID_Rank4Int            ,      //格挡
		ATTR_ID_Rank4PermRate       ,      //格挡
		ATTR_ID_Rank4Rate           ,      //格挡

		ATTR_ID_Atk1Base            ,      //战法效果
		ATTR_ID_Atk1Int             ,      //战法效果
		ATTR_ID_Atk1Perm            ,      //战法效果
		ATTR_ID_Atk1                ,      //战法效果

		ATTR_ID_Atk2Base            ,      //计策效果
		ATTR_ID_Atk2Int             ,      //计策效果
		ATTR_ID_Atk2Perm            ,      //计策效果
		ATTR_ID_Atk2                ,      //计策效果

		ATTR_ID_Def1Base            ,      //战法防御
		ATTR_ID_Def1Int             ,      //战法防御
		ATTR_ID_Def1Perm            ,      //战法防御
		ATTR_ID_Def1                ,      //战法防御

		ATTR_ID_Def2Base            ,      //计策防御
		ATTR_ID_Def2Int             ,      //计策防御
		ATTR_ID_Def2Perm            ,      //计策防御
		ATTR_ID_Def2                ,      //计策防御

		ATTR_ID_Atk3Change          ,      //攻击3数值变化
		ATTR_ID_Atk4Change          ,      //攻击4数值变化	
		ATTR_ID_Atk5Change          ,      //攻击5数值变化
		ATTR_ID_Atk6Change          ,      //攻击6数值变化
		ATTR_ID_Atk7Change          ,      //攻击7数值变化
		ATTR_ID_Atk8Change          ,      //攻击8数值变化		

		ATTR_ID_Def3Change          ,      //防御3数值变化
		ATTR_ID_Def4Change          ,      //防御4数值变化
		ATTR_ID_Def5Change          ,      //防御5数值变化
		ATTR_ID_Def6Change          ,      //防御6数值变化
		ATTR_ID_Def7Change          ,      //防御7数值变化
		ATTR_ID_Def8Change          ,      //防御8数值变化

		ATTR_ID_MyAtk1DamOther        ,      //我对他人～伤害1数值变化
		ATTR_ID_MyAtk2DamOther        ,      //我对他人～伤害2数值变化
		ATTR_ID_MyAtk3DamOther        ,      //我对他人～伤害3数值变化
		ATTR_ID_MyAtk4DamOther        ,      //我对他人～伤害4数值变化
		ATTR_ID_MyAtk5DamOther        ,      //我对他人～伤害5数值变化
		ATTR_ID_MyAtk6DamOther        ,      //我对他人～伤害6数值变化
		ATTR_ID_MyAtk7DamOther        ,      //我对他人～伤害7数值变化
		ATTR_ID_MyAtk8DamOther        ,      //我对他人～伤害8数值变化
		ATTR_ID_MyAtk9DamOther        ,      //我对他人～治疗数值变化
		ATTR_ID_MyAtk10DamOther       ,      //我对他人～正面伤害千分比变化
		ATTR_ID_MyAtk11DamOther       ,      //我对他人～背面伤害千分比变化
		ATTR_ID_MyAtk12DamOther       ,      //我对他人～治疗千分比变化
		ATTR_ID_MyAtk13DamOther       ,      //我对他人～攻击重击倍数变化
		ATTR_ID_MyAtk14DamOther       ,      //我对他人～治疗重击倍数变化

		ATTR_ID_OtherAtk1DamMe        ,      //他人对我～伤害1数值变化
		ATTR_ID_OtherAtk2DamMe        ,      //他人对我～伤害2数值变化
		ATTR_ID_OtherAtk3DamMe        ,      //他人对我～伤害3数值变化
		ATTR_ID_OtherAtk4DamMe        ,      //他人对我～伤害4数值变化
		ATTR_ID_OtherAtk5DamMe        ,      //他人对我～伤害5数值变化
		ATTR_ID_OtherAtk6DamMe        ,      //他人对我～伤害6数值变化
		ATTR_ID_OtherAtk7DamMe        ,      //他人对我～伤害7数值变化
		ATTR_ID_OtherAtk8DamMe        ,      //他人对我～伤害8数值变化
		ATTR_ID_OtherAtk9DamMe        ,      //他人对我～治疗数值变化
		ATTR_ID_OtherAtk10DamMe       ,      //他人对我～正面伤害千分比变化
		ATTR_ID_OtherAtk11DamMe       ,      //他人对我～背面伤害千分比变化
		ATTR_ID_OtherAtk12DamMe       ,      //他人对我～治疗千分比变化
		ATTR_ID_OtherAtk13DamMe       ,      //他人对我～攻击重击倍数变化
		ATTR_ID_OtherAtk14DamMe       ,      //他人对我～治疗重击倍数变化

		ATTR_ID_MyAtk1DamArmy		  ,		//我对军队攻击千分比变化～刀兵
		ATTR_ID_MyAtk2DamArmy		  ,		//我对军队攻击千分比变化～枪兵
		ATTR_ID_MyAtk3DamArmy		  ,		//我对军队攻击千分比变化～骑兵
		ATTR_ID_MyAtk4DamArmy		  ,		//我对军队攻击千分比变化～弓兵
		ATTR_ID_MyAtk5DamArmy		  ,		//我对军队攻击千分比变化～器械
		ATTR_ID_MyAtk6DamArmy		  ,		//我对军队攻击千分比变化～其他

		ATTR_ID_ArmyAtk1DamMe		  ,		//军队对我攻击千分比变化～刀兵
		ATTR_ID_ArmyAtk2DamMe		  ,		//军队对我攻击千分比变化～枪兵
		ATTR_ID_ArmyAtk3DamMe		  ,		//军队对我攻击千分比变化～骑兵
		ATTR_ID_ArmyAtk4DamMe		  ,		//军队对我攻击千分比变化～弓兵
		ATTR_ID_ArmyAtk5DamMe		  ,		//军队对我攻击千分比变化～器械
		ATTR_ID_ArmyAtk6DamMe		  ,		//军队对我攻击千分比变化～其他

		ATTR_ID_Buff1resistance		  ,		//状态抗性1(晕眩和失控)
		ATTR_ID_Buff2resistance		  ,		//状态抗性2(混乱和恐惧)
		ATTR_ID_Buff3resistance		  ,		//状态抗性3(封技和禁具)
		ATTR_ID_Buff4resistance		  ,		//状态抗性4(定身和减速)
		ATTR_ID_Buff5resistance		  ,		//状态抗性5(诅咒和下毒)
		ATTR_ID_Buff6resistance		  ,		//状态抗性6(流血和致命)

		ATTR_ID_Character1Multiplying ,		//角色倍率1(经验获得)
		ATTR_ID_Character2Multiplying ,		//角色倍率2(挂机练功)
		ATTR_ID_Character3Multiplying ,		//角色倍率3(挂机工作)
		ATTR_ID_Character4Multiplying ,		//角色倍率4(战斗仇恨)
		ATTR_ID_Character5Multiplying ,		//角色倍率5(技能消耗)
		ATTR_ID_Character6Multiplying ,		//角色倍率6(死亡惩罚)

		ATTR_ID_MAX ,
		//策划表加载完毕end

		//程序自定义护盾，策划表没有，
		//配合状态表使用。
		//添加人：徐开超
		Attr_ID_shield_FIGHT			  ,		//战法护盾			
		Attr_ID_shield_PLAN				  ,		//计策护盾
		Attr_ID_shield_WATER			  ,		//水护盾
		Attr_ID_shield_FIRE				  ,		//火护盾
		Attr_ID_shield_WIND				  ,		//风护盾
		Attr_ID_shield_THUNDER			  ,		//雷护盾
		Attr_ID_shield_SOIL				  ,		//土护盾
		Attr_ID_shield_OTHER			  ,		//备用护盾
		Attr_ID_shield_ALL				  ,		//全伤害护盾
		Attr_ID_shield_MAGIC			  ,		//法力护盾

		ATTR_ID_COUNT_MAX                  
	}; 
	//----------------------------------------------------------------------
	enum ATTR_ADD_TYPE                 
	{                                   
		ATTR_ADD_TYPE_NULL = 0,        

		ATTR_ADD_TYPE_NO,                   //初始化时可改变，以后都由公式计算获得。
		ATTR_ADD_TYPE_YES,					//可直接改变的属性

		ATTR_SHOW_TYPE_MAX              
	}; 
	//----------------------------------------------------------------------
	enum ATTR_USE_TYPE                  
	{
		ATTR_USE_TYPE_NULL = 0,

		ATTR_USE_TYPE_SYSTEM,                  //系统属性
		ATTR_USE_TYPE_TALENT,                  //天赋属性
		ATTR_USE_TYPE_FIGHT,                   //战斗属性
		ATTR_USE_TYPE_OTHER,                   //后续扩展属性

		ATTR_USE_TYPE_MAX
	};

	enum	ABILITYJUDGE_TYPE
	{
		ABILITYJUDGE_TYPE_NULL,

		ABILITYJUDGE_TYPE_REAL,			//实值判定
		ABILITYJUDGE_TYPE_LVL,			//根据目标等级判定（角色，物品，技能等）

		ABILITYJUDGE_TYPE_MAX
	};

	//----------------------------------------------------------------------
	enum ITEM_RANK
	{
		ITEM_RANK_NONE,

		ITEM_RANK_WHITE,                        //白装
		ITEM_RANK_GREEN,                        //绿装
		ITEM_RANK_BLUE,                         //蓝装
		ITEM_RANK_PURPLE,                       //紫装

		ITEM_RANK_MAX
	};

	//----------------------------------------------------------------------
	enum ITEM_MONEY_CLASS
	{
		ITEM_MONEY_CLASS_NONE,

		ITEM_MONEY_CLASS_MONEY_RMB_PRESENT,             //人民币赠币
		ITEM_MONEY_CLASS_MONEY_GAME,					//游戏币
		ITEM_MONEY_CLASS_MONEY_FOOD,					//粮食币
		ITEM_MONEY_CLASS_MONEY_MAN,						//人口币
		ITEM_MONEY_CLASS_RENOWN_SPARE1,					//备用声望币1
		ITEM_MONEY_CLASS_RENOWN_SPARE2,					//备用声望币2
		ITEM_MONEY_CLASS_RENOWN_SPARE3,					//备用声望币3
		ITEM_MONEY_CLASS_RENOWN_SPARE4,					//备用声望币4

		ITEM_MONEY_CLASS_MAX
	};

	//----------------------------------------------------------------------
	enum ITEM_EQUIP_CLASS
	{
		ITEM_EQUIP_CLASS_NONE,
		ITEM_EQUIP_CLASS_MAX
	};
	//----------------------------------------------------------------------
	enum ITEM_EQUIP_SLOT_TYPE
	{
		ITEM_EQUIP_SLOT_TYPE_NONE,

		ITEM_EQUIP_SLOT_TYPE_MAIN,                   //主武器
		ITEM_EQUIP_SLOT_TYPE_DEPUTY,                 //副武器
		ITEM_EQUIP_SLOT_TYPE_HEAD,                   //头部
		ITEM_EQUIP_SLOT_TYPE_BODY,                   //身体
		ITEM_EQUIP_SLOT_TYPE_FOOT,                   //足部
		ITEM_EQUIP_SLOT_TYPE_JEWELRY,                //饰物
		ITEM_EQUIP_SLOT_TYPE_ADDITION1,              //附加1
		ITEM_EQUIP_SLOT_TYPE_HORSE,                  //马

		ITEM_EQUIP_SLOT_TYPE_MAX
	};
	//----------------------------------------------------------------------
	enum ITEM_USE_CLASS
	{
		ITEM_USE_CLASS_NONE,
		ITEM_USE_CLASS_MAX
	};
	//----------------------------------------------------------------------
	enum ITEM_OTHER_CLASS
	{
		ITEM_OTHER_CLASS_NONE,
		ITEM_OTHER_CLASS_MAX
	};
	//----------------------------------------------------------------------
	enum ITEM_SHOP_FUNCTION_TYPE
	{
		ITEM_SHOP_FUNCTION_TYPE_SHOPPING = 1,			//消费功能（买卖）
		ITEM_SHOP_FUNCTION_TYPE_REPAIR = 2,				//修理
	};
	//----------------------------------------------------------------------

	enum AttackType
	{
		AT_NULL,
		AT_SLASH,
		AT_PUNCTURE,
		AT_BLUNT,
		AT_DASH,
		AT_FIRE,
		AT_WATER,
		AT_WIND,
		AT_THUNDER,

		AT_MAX
	};

	//-----------------------------------------------------------------------
	enum DamageType
	{
		DT_NULL,
		DT_HP,
		DT_MP,
		DT_HPMP,
		DT_SP,
		DT_PROMILLE_HP, 
		DT_PROMILLE_MP,
		DT_PROMILLE_HPMP,
		DT_PROMILLE_SP,	

		DT_MAX
	};

	//-----------------------------------------------------------------------
	enum ShareType
	{
		SHT_NULL,
		SHT_DIRECT,
		SHT_AVERAGE,

		SHT_MAX
	};
	//-----------------------------------------------------------------------
	enum  ACCESS_TYPE
	{
		ACCESS_TYPE_NULL,

		ACCESS_TYPE_NORMAL,                     //常规通道
		ACCESS_TYPE_ARMY,                       //军队专用道
		ACCESS_TYPE_GENREAL,                    //角色专用道

		ACCESS_TYPE_MAX
	};
	//-----------------------------------------------------------------------

	enum ContactType
	{
		CT_NULL,
		CT_ContactType1,
		CT_ContactType2,
		CT_ContactType3,
		CT_ContactType4,
		CT_ContactType5,
		CT_ContactType6,
		CT_ContactType7,
		CT_ContactType8,
	};

	//-----------------------------------------------------------------------
	enum ContactCharacterType
	{
		CCT_NULL,
		CCT_CCT1,
		CCT_CCT2,
		CCT_CCT3,
		CCT_CCT4,
	};

	//-----------------------------------------------------------------------
	enum EventType
	{
		ET_NULL,
		ET_EventType1,
		ET_EventType2,
	};

	//-----------------------------------------------------------------------
	enum EventCharacterType
	{
		ETT_NULL,
		ETT_EET1,
		ETT_EET2,
		ETT_EET3,
		ETT_EET4,
		ETT_EET5,
		ETT_EET6,
	};

	//-----------------------------------------------------------------------
	enum BaseAIType
	{
		BAT_NULL,
		BAT_REBIRTH,
		BAT_DISAPPEAR,
		BAT_EFFECT,
		BAT_RANDOMMOVE,
		BAT_GUARD,
		BAT_SEEKHELP,
		BAT_ESCAPE,
		BAT_HATEDETECT,
		BAT_PURSUE,
		BAT_KEEPDISTANCE,
		BAT_SELECTSKILL,
		BAT_RETURN,
	};

	//-----------------------------------------------------------------------
	enum BaseAIHead
	{
		BAH_NULL,
		BAH_ANY,
		BAH_PEACE,
		BAH_STARTFIGHT,
		BAH_FIGHT,
		BAH_ENDFIGHT,
	};
	
   //-----------------------------------------------------------------------

	enum CharAppearType
	{
		CAT_ANY_SCENE,
		CAT_RPG_SCENE_ONLY,
		CAT_SLG_SCENE_ONLY,

		CAT_SLG_SCENE_MAX
	};
	enum STATUS_STATUSSYSTYPE
	{
		STATUS_STATUSSYSTYPE_NULL,
		STATUS_STATUSSYSTYPE_VERDIGO,				//眩晕
		STATUS_STATUSSYSTYPE_CHAOS,					//混乱
		STATUS_STATUSSYSTYPE_BLOCKADE,				//封技
		STATUS_STATUSSYSTYPE_SLOWDOWN,				//减速
		STATUS_STATUSSYSTYPE_POISON,				//下毒
		STATUS_STATUSSYSTYPE_BLEED,					//流血
		STATUS_STATUSSYSTYPE_DEAD,					//死亡
		STATUS_STATUSSYSTYPE_INVISIBILITY,			//隐身
		STATUS_STATUSSYSTYPE_MAX
	};
	//----------------------------------------------------------------------
	enum STATUS_VITIATEFLAG
	{
		STATUS_VITIATEFLAG_NULL,

		STATUS_VITIATEFLAG_FIGHT = 1,					//战斗
		STATUS_VITIATEFLAG_PLAN = 2,					//策术
		STATUS_VITIATEFLAG_WATER = 4,					//水
		STATUS_VITIATEFLAG_FIRE = 8,					//火
		STATUS_VITIATEFLAG_WIND = 16,					//风
		STATUS_VITIATEFLAG_THUNDER = 32,				//雷
		STATUS_VITIATEFLAG_SOIL = 64,					//土
		STATUS_VITIATEFLAG_OTHER = 128,					//其它

		STATUS_VITIATEFLAG_MAX
	};
	//----------------------------------------------------------------------
	enum STATUS_ABSORBTYPE
	{
		STATUS_ABSORBTYPE_NULL,

		STATUS_ABSORBTYPE_FIGHT,					//战斗
		STATUS_ABSORBTYPE_PLAN,						//策术
		STATUS_ABSORBTYPE_WATER,					//水
		STATUS_ABSORBTYPE_FIRE,						//火
		STATUS_ABSORBTYPE_WIND,						//风
		STATUS_ABSORBTYPE_THUNDER,					//雷
		STATUS_ABSORBTYPE_SOIL,						//土
		STATUS_ABSORBTYPE_OTHER,					//其它
		STATUS_ABSORBTYPE_ALL,						//全伤害
		STATUS_ABSORBTYPE_MAGIC,					//法力

		STATUS_ABSORBTYPE_MAX
	};
	//----------------------------------------------------------------------
	enum STATUS_CYCLETYPE
	{
		STATUS_CYCLETYPE_NULL,

		STATUS_CYCLETYPE_FIXED_DAMAGE,						//定值伤害
		STATUS_CYCLETYPE_FIXED_ABSORB,						//定值治疗
		STATUS_CYCLETYPE_PERMILLAGE_DAMAGE,					//千分比伤害
		STATUS_CYCLETYPE_PERMILLAGE_ABSORB,					//千分比治疗
		STATUS_CYCLETYPE_MAX_PERMILLAGE_DAMAGE,				//最大值千分比伤害
		STATUS_CYCLETYPE_MAX_PERMILLAGE_ABSORB,				//最大值千分比治疗

		STATUS_CYCLETYPE_MAX
	};
	enum	STATUS_EVENTCONDITION
	{
		STATUS_EVENTCONDITION_NULL,
		STATUS_EVENTCONDITION_MAX
	};
	enum STATUS_EVENTRESULT
	{
		STATUS_EVENTRESULT_NULL,
		STATUS_EVENTRESULT_MAX
	};	
	//----------------------------------------------------------------------
	enum STATUS_SHOWTYPE
	{
		STATUS_SHOWTYPE_NULL,
		STATUS_SHOWTYPE_IMAGETIME,		//图片和时间
		STATUS_SHOWTYPE_IMAGE,			//图片
		STATUS_SHOWTYPE_NOT,			//不显示
		STATUS_SHOWTYPE_MAX
	};
	//----------------------------------------------------------------------
	enum STATUS_STYLETYPE
	{
		STATUS_STYLETYPE_NULL,
		STATUS_STYLETYPE_SYS,			//系统
		STATUS_STYLETYPE_EQUIP,			//装备
		STATUS_STYLETYPE_GOOD,			//有益
		STATUS_STYLETYPE_BAD,			//不利
		STATUS_STYLETYPE_MAX
	};
	//----------------------------------------------------------------------
	enum STATUS_TIMETYPE
	{
		STATUS_TIMETYPE_NULL,
		STATUS_TIMETYPE_FOREVER,		//永久，无时间概念
		STATUS_TIMETYPE_GAME,			//游戏时间
		STATUS_TIMETYPE_REAL,			//真实时间
		STATUS_TIMETYPE_MAX
	};
	//----------------------------------------------------------------------
	enum STATUS_DISAPPEARTYPE
	{
		STATUS_DISAPPEARTYPE_NULL,
		STATUS_DISAPPEARTYPE_OFFLINE = 1,
		STATUS_DISAPPEARTYPE_DEAD = 2,
		STATUS_DISAPPEARTYPE_MOVE = 4,
		STATUS_DISAPPEARTYPE_FIGHT = 8,
		STATUS_DISAPPEARTYPE_OFFFIGHT = 16,
		STATUS_DISAPPEARTYPE_TANSMIT = 32,
		STATUS_DISAPPEARTYPE_SAFE = 64,
		STATUS_DISAPPEARTYPE_CLICKIMAGE = 128,
		STATUS_DISAPPEARTYPE_MAX
	};
	//----------------------------------------------------------------------
	enum STATUS_TYPE
	{
		STATUS_TYPE_NULL,

		STATUS_TYPE_CHARACTER,			//角色
		STATUS_TYPE_CLAN,				//氏族
		STATUS_TYPE_PLACE,				//据点
		STATUS_TYPE_FORCE,				//势力

		STATUS_TYPE_MAX
	};

#define CALENDARINFO_HOUR_MAX_COUNT		12
#define CALENDARINFO_DIZHI_MAX_COUNT		10
#define CALENDARINFO_SEASON_MAX_COUNT		4
#define CALENDARINFO_YEAR_MAX_COUNT	12
#define CALENDARINFO_MONTH_MAX_COUNT		12
#define CALENDARINFO_DAY_MAX_COUNT			30
}


#endif	//_GAME_FILE_DEFINE_H_