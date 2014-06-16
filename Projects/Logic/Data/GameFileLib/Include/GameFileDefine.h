/******************************************************************************/
#ifndef _GAME_FILE_DEFINE_H_
#define _GAME_FILE_DEFINE_H_
/******************************************************************************/

/******************************************************************************/
namespace MG
{
	#define TROOP_GROUP_NUM		5	//ͬʱ�����ľ��Ӹ���

	#define SCENE_OBJECT_GROUP_STR_STATIC	"Static"		//��̬������룬����ǿͻ����Զ������������ͷ������޹�
	#define SCENE_OBJECT_GROUP_STR_OBJECT	"Object"		//������룬���ֽ����¼������
	#define SCENE_OBJECT_GROUP_STR_REGION	"Region"		//��Ϸ�����򣬷�����֪ͨ��ͻ������롣
	#define SCENE_OBJECT_GROUP_STR_PLACE	"Place"			//�ݵ㣬������֪ͨ��ͻ�������
	#define SCENE_OBJECT_GROUP_STR_POINT	"Point"			//��ת�㣬������֪ͨ��ͻ������룬������Ϣ����GameFileLib::PointTemplte
	#define SCENE_OBJECT_GROUP_STR_NPC		"NPC"			//NPC��������֪ͨ��ͻ������룬������Ϣ����GameFileLib::CharacterTemplate		
	#define SCENE_OBJECT_GROUP_STR_MONSTER	"Monster"		//��Ϸ�еĵ����֣�������֪ͨ��ͻ������룬������Ϣ����GameFileLib::CharacterTemplate
	#define SCENE_OBJECT_GROUP_STR_TROOP	"Troop"			//��Ϸ�е���Ⱥ�֣�������֪ͨ��ͻ������룬������Ϣ��Դ��GameFileLib::TroopTemplate
	#define SCENE_OBJECT_GROUP_STR_BUILDING	"Building"		//��Ϸ�н�����������֪ͨ��ͻ������롣
	#define SCENE_OBJECT_GROUP_STR_GENERAL	"General"		//��Ϸ�д����佫��
	#define SCENE_OBJECT_GROUP_STR_EFFECT	"Effect"		//��Ϸ�д�����Ч��

	/******************************************************************************/

	#define  NAME_LENGTH      32
	#define  ATTR_PARA_NUM 6
	#define  APPENDATTR_NUM  8
	#define  DISPOSITION_NUM 16
	#define  CHAR_SKILL_NUM  8
	#define  CHAR_ABILITYAPPEND_ID_NUM  4
	#define  CHAR_SKILL_ID_NUM  2
	#define  ITEM_RANDOM_GROUP_NUM 16
	#define	 TIME_HUNDRED_MS	100				//�ٺ���
	#define  PERMILLAGE_VALUE  0.001			//ǧ�ֱ�
	#define  THOUSAND_VALUE  1000			//ǧ�ֱ�

	/******************************************************************************/


	//enum JumpMapType
	//{
	//	JMT_Null,

	//	JMT_Distribution	= 1,		//����ֿ��ͼ
	//	JMT_Place			= 2,		//�ص��ھ���ͼ
	//	JMT_Building		= 3,		//�����ڲ���ͼ
	//	JMT_Direction		= 4,		//ֱ����ת��ͼ
	//	JMT_Instance		= 5,		//������ͼ

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

		CHAR_LVL_USETYPE_CLAN,						//���徭��
		CHAR_LVL_USETYPE_CLAN_POS,					//�����λ����
		CHAR_LVL_USETYPE_CLAN_FEATS,				//���幦������
		CHAR_LVL_USETYPE_CLAN_SPARE,				//���屸�þ���
		CHAR_LVL_USETYPE_CHAR_LVL,					//�佫��������
		CHAR_LVL_USETYPE_CHAR_TRUN,					//�佫ת������
		CHAR_LVL_USETYPE_CHAR_SKILL,				//�佫������������
		CHAR_LVL_USETYPE_CHAR_SPARE,				//�佫���þ���
		CHAR_LVL_USETYPE_AYM_LVL,					//������������
		CHAR_LVL_USETYPE_AYM_SPARE,					//���ӱ��þ���
		CHAR_LVL_USETYPE_BUILD_LVL,					//������������
		CHAR_LVL_USETYPE_BUILD_SPARE,				//�������þ���
		CHAR_LVL_USETYPE_OTHER_SPARE1,				//�������þ���1
		CHAR_LVL_USETYPE_OTHER_SPARE2,				//�������þ���1
		CHAR_LVL_USETYPE_OTHER_SPARE3,				//�������þ���1
		CHAR_LVL_USETYPE_OTHER_SPARE4,				//�������þ���1
		
		CHAR_LVL_USETYPE_MAX
	};
	//--------------------------------------------------------------------------------
	enum  TROOPTEMPLATE_TYPE
	{
		TROOPTEMPLATE_TYPE_NULL = 0,                    //0��������

		TROOPTEMPLATE_TYPE_BROADSWORD   ,           //  1������
		TROOPTEMPLATE_TYPE_SPEAR        ,           //  2��ǹ��
		TROOPTEMPLATE_TYPE_HORSE        ,           //  3�����
		TROOPTEMPLATE_TYPE_BOW          ,           //  4������
		TROOPTEMPLATE_TYPE_WEAPON       ,           //  5������
		TROOPTEMPLATE_TYPE_OTHER        ,           //  6��½�����
		TROOPTEMPLATE_TYPE_SPECIAL		,			//	7����
		TROOPTEMPLATE_TYPE_WATER		,			//	8ˮ��

		TROOPTEMPLATE_TYPE_MAX
	};
	//--------------------------------------------------------------------------------
	enum  
	{
		TROOPTEMPLATE_STATE_GRASSLAND = 0   ,       //�ݵ�
		TROOPTEMPLATE_STATE_WOODLAND        ,       //�ֵ�
		TROOPTEMPLATE_STATE_MOUNTAINLAND    ,       //ɽ��
		TROOPTEMPLATE_STATE_SNOWFIELD       ,       //ѩ��
		TROOPTEMPLATE_STATE_SAND            ,       //ɳ��
		TROOPTEMPLATE_STATE_WATER           ,       //ˮ��

		TROOPTEMPLATE_STATE_MAX
	};
	//-----------------------------------------------------------------------------
	enum CHAR_TYPE
	{
		CHAR_TYPE_NULL = 0,

		CHAR_TYPE_GENREAL,      //�佫
		CHAR_TYPE_ARMY,         //����
		CHAR_TYPE_THING,        //���
		CHAR_TYPE_FUNCTION,     //����

		CHAR_TYPE_Max
	};

	//-----------------------------------------------------------------------------
	enum GENDER_TYPE
	{
		GENDER_TYPE_NULL = 0,

		GENDER_TYPE_MAN,        //����
		GENDER_TYPE_WOMAN,      //Ů��
		GENDER_TYPE_NONE_SEX,   //���Ա�����ӣ��������

		GENDER_TYPE_MAX
	};

	//-----------------------------------------------------------------------------
	enum  FUNCTION_FLAG
	{
		FUNCTION_FLAG_NULL = 0,

		FUNCTION_FLAG_ACTION,    //����
		FUNCTION_FLAG_AUTOWAY,   //Ѱ·

		FUNCTION_FLAG_MAX
	};

	//-----------------------------------------------------------------------------
	enum  POWERFUL_TYPE
	{
		POWERFUL_TYPE_NULL = 0,

		POWERFUL_TYPE_FIRST,           //һ��
		POWERFUL_TYPE_SECOND,          //����
		POWERFUL_TYPE_THIRD,           //����
		POWERFUL_TYPE_NORMAL,          //������

		POWERFUL_TYPE_MAX
	};

	//-----------------------------------------------------------------------------
	enum CHARACTER_OBJ_MUTUALTYPE
	{
		CHARACTER_OBJ_MUTUALTYPE_NULL,

		CHARACTER_OBJ_MUTUALTYPE_Touch,			//��ײ����
		CHARACTER_OBJ_MUTUALTYPE_Action,		//��������

		CHARACTER_OBJ_MUTUALTYPE_MAX,
	};

	//-----------------------------------------------------------------------------
	enum CHARACTER_TYPE
	{
		CHARACTER_TYPE_NULL,

		CHARACTER_TYPE_GENREAL,			//�佫
		CHARACTER_TYPE_ARMY,			//����
		CHARACTER_TYPE_BUILD,			//����
		CHARACTER_TYPE_MONSTER,			//����
		CHARACTER_TYPE_NPC,				//NPC
		CHARACTER_TYPE_OBJ,				//���

		CHARACTER_TYPE_MAX
	};

	//-----------------------------------------------------------------------------
	enum  CHAR_FORMULA_TYPE
	{
		CHAR_FORMULA_TYPE_NULL = 0,

		CHAR_FORMULA_TYPE_POWER,       //�ͽ�
		CHAR_FORMULA_TYPE_QUICK,       //ͳ˧
		CHAR_FORMULA_TYPE_BRAINS,      //ıʿ
		CHAR_FORMULA_TYPE_MANAGER,     //����

		CHAR_FORMULA_TYPE_MAX
	};

	//-----------------------------------------------------------------------------
	/*enum CHAR_RACE_TYPE
	{
		CHAR_RACE_TYPE_NULL,

		CHAR_RACE_TYPE_1,               //���
		CHAR_RACE_TYPE_2,               //���޵�
		CHAR_RACE_TYPE_3,               //�˵�
		CHAR_RACE_TYPE_4,               //������
		CHAR_RACE_TYPE_5,               //���
		CHAR_RACE_TYPE_6,               //������

		CHAR_RACE_TYPE_MAX
	};
    */
	//-----------------------------------------------------------------------------
	enum  CHAR_ATTRRAND_TYPE
	{
		CHAR_ATTRRAND_TYPE_NULL = 0,

		CHAR_ATTRRAND_TYPE_NO,         //�����
		CHAR_ATTRRAND_TYPE_YES,        //���

		CHAR_ATTRRAND_TYPE_MAX
	};
	enum CHAR_BUILD_TYPE
	{
		CHAR_BUILD_TYPE_NULL,
		CHAR_BUILD_TYPE_NOT_FIGHT,			//1~ϵͳ����(���μ�ս��)
		CHAR_BUILD_TYPE_NORMAL,				//2~һ�㽨��(������)
		CHAR_BUILD_TYPE_FIGHT,				//3~ս������(�ṥ��)��
		CHAR_BUILD_TYPE_WALL,				//4~��ǽ֮ǽ
		CHAR_BUILD_TYPE_CORNER,				//5~��ǽ֮ת��
		CHAR_BUILD_TYPE_BAR,				//6~��ǽ֮��¥
		CHAR_BUILD_TYPE_TURRET,				//7~��ǽ֮��¥
		CHAR_BUILD_TYPE_GATE,				//8~��ǽ֮����
		CHAR_BUILD_TYPE_BRIDGE,				//9~��ǽ֮����
		CHAR_BUILD_TYPE_RIVER,				//10~��ǽ֮���Ǻ�
		CHAR_BUILD_TYPE_BARRACKS,			//11~��Ӫ
		CHAR_BUILD_TYPE_HEADQUARTERS,		//12~��Ӫ

		CHAR_BUILD_TYPE_MAX
	};
	//--------------------------------------------------------------------------------------------------
	enum  FORMULA_TYPE
	{
		FORMULA_TYPE_NULL = 0,


		FORMULA_TYPE_Power  = 1,            //�ʺ�������
		FORMULA_TYPE_QUICK  = 2,            //�ʺ�������
		FORMULA_TYPE_BRAINS = 4,            //�ʺ�������
		FORMULA_TYPE_ALL    = 7,            //�ʺ�����

		FORMULA_TYPE_MAX
	};
	//--------------------------------------------------------------------------------------------------
	enum CDTEMP_USETYPE
	{
		CDTEMP_USETYPE_NULL,

		CDTEMP_USETYPE_SERVER,          //������ʹ��
		CDTEMP_USETYPE_CLIENT,          //�ͻ���ʹ��

		CDTEMP_USETYPE_MAX
	};
	//--------------------------------------------------------------------------------------------------
	enum CDTEMP_TIMETYPE
	{
		CDTEMP_TIMETYPE_NULL, 

		CDTEMP_TIMETYPE_REAL,           //��ʵʱ��
		CDTEMP_TIMETYPE_ONLINE,         //����ʱ��

		CDTEMP_TIMETYPE_MAX
	};
	//--------------------------------------------------------------------------------------------------
	enum CDTEMP_SAVETYPE
	{
		CDTEMP_SAVETYPE_NULL,

		CDTEMP_SAVETYPE_NOSAVE,         //������
		CDTEMP_SAVETYPE_SAVE,           //����

		CDTEMP_SAVETYPE_MAX
	};
	//--------------------------------------------------------------------------------------------------
	enum CD_MASTER_TYPE
	{
		CD_MASTER_TYPE_NULL,

		CD_MASTER_TYPE_CLAN,                        //����CD
		CD_MASTER_TYPE_CHARACTER,                   //�����µ��佫CD
		CD_MASTER_TYPE_TROOP,                       //�����µľ���CD
		CD_MASTER_TYPE_BUILD,                       //�����µ�ս��������CD
		CD_MASTER_TYPE_CITY,                        //����CD
		CD_MASTER_TYPE_FROCE,                       //����CD

		CD_MASTER_TYPE_MAX
	};
	//--------------------------------------------------------------------------------------------------
	enum ITEM_IDENTIFY_TYPE
	{
		ITEM_IDENTIFY_TYPE_NULL,

		ITEM_IDENTIFY_TYPE_NO,                   //����Ҫ����
		ITEM_IDENTIFY_TYPE_NEED,                 //��Ҫ����

		ITEM_IDENTIFY_TYPE_MAX
	};
	//--------------------------------------------------------------------------------------------------
	enum  ITEM_DISPPEAR_TYPE  //������
	{
		ITEM_DISPPEAR_TYPE_NULL,

		ITEM_DISPPEAR_TYPE_USE = 1,                 //ʹ�ú���ʧ
		ITEM_DISPPEAR_TYPE_DURABLE = 2,             //�;úľ�
		ITEM_DISPPEAR_TYPE_TIME = 4,                //ʱ��ľ�
		ITEM_DISPPEAR_TYPE_CLAN_OFFLINE = 8,        //��������
		ITEM_DISPPEAR_TYPE_CHARACTER_DEAD = 16,     //��ɫ����
		ITEM_DISPPEAR_TYPE_JUMPMAP = 32,            //����ͼ

		ITEM_DISPPEAR_TYPE_MAX
	};
	//--------------------------------------------------------------------------------------------------
	enum ITEM_FORBID_TYPE
	{
		ITEM_FORBID_TYPE_NULL,

		ITEM_FORBID_TYPE_GIVEUP = 1,                //���ɶ���
		ITEM_FORBID_TYPE_SHOP = 2,                  //���ɻ���
		ITEM_FORBID_TYPE_REPAIR = 4,                //��������
		ITEM_FORBID_TYPE_TRADE = 8,                 //���ɽ���
		ITEM_FORBID_TYPE_CIRCULATE = 16,            //������ͨ
		ITEM_FORBID_TYPE_ARTIFICE = 32,             //��������

		ITEM_FORBID_TYPE_MAX
	};
	//--------------------------------------------------------------------------------------------------
	enum ITEM_TIPS_TYPE
	{
		ITEM_TIPS_TYPE_GENERAL,

		ITEM_TIPS_TYPE_SHOP = 1,                    //�̵���ʾ
		ITEM_TIPS_TYPE_CALLBACK = 2,                //�ع�����ʾ
		ITEM_TIPS_TYPE_MAX
	};
	//--------------------------------------------------------------------------------------------------
	enum  ITEM_EXISTENCE_TIME_TYPE
	{
		ITEM_EXISTENCE_TIME_TYPE_NULL,

		ITEM_EXISTENCE_TIME_TYPE_REAL,          //��ʵʱ��
		ITEM_EXISTENCE_TIME_TYPE_GAME,          //��Ϸʱ��

		ITEM_EXISTENCE_TIME_TYPE_MAX
	};
	//--------------------------------------------------------------------------------------------------
	enum  ITEM_BIND_TYPE
	{
		ITEM_BIND_TYPE_NULL,          //����

		ITEM_BIND_TYPE_GET,          //��ð�
		ITEM_BIND_TYPE_USE,          //ʹ�ð�

		ITEM_BIND_TYPE_MAX
	};
	//--------------------------------------------------------------------------------------------------
	enum  ITEM_SITE_TYPE
	{
		ITEM_SITE_TYPE_NULL,

		ITEM_SITE_TYPE_PLACE,             //�ݵ�
		ITEM_SITE_TYPE_CLAN,              //����ֿ�
		ITEM_SITE_TYPE_CHARACTER_BAG,     //��ɫ����
		ITEM_SITE_TYPE_CHARACTER_EQUIP,   //��ɫװ��
		ITEM_SITE_TYPE_AUTION,            //������
		ITEM_SITE_TYPE_BUYBACK,           //�ع���
		ITEM_SITE_TYPE_MAIL,              //����
		ITEM_SITE_TYPE_DEL,               //��ɾ��

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

		ITEM_REPLACE_TYPE_EQUAL,         //ͬ���滻
		ITEM_REPLACE_TYPE_QUEUE,         //�����滻

		ITEM_REPLACE_TYPE_MAX
	};
	//----------------------------------------------------------------------------------
	enum ITEM_RANDOM_USETYPE
	{
		ITEM_RANDOM_USETYPE_NULL,

		ITEM_RANDOM_USETYPE_DROP,       //����
		ITEM_RANDOM_USETYPE_USEITEM,    //ʹ����Ʒ
		ITEM_RANDOM_USETYPE_SHOP,       //�̵�
		ITEM_RANDOM_USETYPE_COMPOSE,    //�ϳ�
		ITEM_RANDOM_USETYPE_RESOLVE,    //�ֽ�

		ITEM_RANDOM_USETYPE_MAX
	};
	//----------------------------------------------------------------------------------
	enum ITEM_RANDOM_TYPE
	{
		ITEM_RANDOM_TYPE_NULL,

		ITEM_RANDOM_TYPE_ONCE,          //���һ��
		ITEM_RANDOM_TYPE_EVERY,         //�������

		ITEM_RANDOM_TYPE_MAX
	};
	//---------------------------------------------------------------------------------- 
	enum ITEM_USE_RESTORE_TYPE
	{
		ITEM_USE_RESTORE_TYPE_NULL,
		ITEM_USE_RESTORE_TYPE_REAL_VALUE,            //ʵ��ֵ
		ITEM_USE_RESTORE_TYPE_PERMILLAGE_VALUE,      //ǧ�ֱ�
		ITEM_USE_RESTORE_TYPE_MAX
	};
	//----------------------------------------------------------------------------------
	enum IOCN_ART_TYPE
	{
		IOCN_ART_TYPE_NULL,

		IOCN_ART_TYPE_ITEM,					//��Ʒ
		IOCN_ART_TYPE_SKILL,				//����
		IOCN_ART_TYPE_MALEHEAD_LARGE,       //��ͷ�� ��
		IOCN_ART_TYPE_FEMALEHEAD_LARGE,     //Ůͷ�� ��
		IOCN_ART_TYPE_NPC,					//NPC
		IOCN_ART_TYPE_MONSTER,				//����
		IOCN_ART_TYPE_PLACE,                //�ص�
		IOCN_ART_TYPE_FORCE,                //����
		IOCN_ART_TYPE_BUILDING,             //����
		IOCN_ART_TYPE_ARMY,                 //����
        IOCN_ART_TYPE_NPC_TOP_INDENTIFI,    //NPCͷ����ʶ    
		IOCN_ART_TYPE_SMALL,				//Сͼ��
		IOCN_ART_TYPE_SEASON,               //����
		IOCN_ART_TYPE_DayOfTime,			//ʱ��
		ICON_ART_TYPE_CLAN_FLAG,			//����ͼ��
		ICON_ART_TYPE_CLAN_BACK,			//���屳��ͼ��

		IOCN_ART_TYPE_MAX
	};
	//----------------------------------------------------------------------------------
	enum ITEM_GROUP_USETYPE
	{
		ITEM_GROUP_USETYPE_NULL,

		ITEM_GROUP_USETYPE_DROP,        //��Ʒ����
		ITEM_GROUP_USETYPE_USE,         //ʹ����Ʒ���翪���䣩
		ITEM_GROUP_USETYPE_SHOP,        //�̵�
		ITEM_GROUP_USETYPE_COMPOSE,     //�ϳ�
		ITEM_GROUP_USETYPE_RESLOVE,     //�ֽ�

		ITEM_GROUP_USETYPE_MAX
	};
	//----------------------------------------------------------------------------------
	enum ATTR_ID
	{
		ATTR_ID_NULL = 0,

		ATTR_ID_System01Base        ,      //�ƶ��ٶ�
		ATTR_ID_System01Int         ,      //�ƶ��ٶ�
		ATTR_ID_System01Perm        ,      //�ƶ��ٶ�
		ATTR_ID_System01            ,      //�ƶ��ٶ�

		ATTR_ID_System02Base        ,      //����ٶ�
		ATTR_ID_System02Int         ,      //����ٶ�
		ATTR_ID_System02Perm        ,      //����ٶ�
		ATTR_ID_System02            ,      //����ٶ�

		ATTR_ID_System03Base        ,      //��Ұ��Χ
		ATTR_ID_System03Int         ,      //��Ұ��Χ
		ATTR_ID_System03Perm        ,      //��Ұ��Χ
		ATTR_ID_System03            ,      //��Ұ��Χ

		ATTR_ID_System04Base        ,      //̽�ⷶΧ
		ATTR_ID_System04Int         ,      //̽�ⷶΧ
		ATTR_ID_System04Perm        ,      //̽�ⷶΧ
		ATTR_ID_System04            ,      //̽�ⷶΧ

		ATTR_ID_System05Base        ,      //����Ƶ��
		ATTR_ID_System05Int         ,      //����Ƶ��
		ATTR_ID_System05Perm        ,      //����Ƶ��
		ATTR_ID_System05            ,      //����Ƶ��

		ATTR_ID_System06Base        ,      //��������
		ATTR_ID_System06Int         ,      //��������
		ATTR_ID_System06Perm        ,      //��������
		ATTR_ID_System06            ,      //��������

		
		ATTR_ID_Talent1Init         ,      //����
		ATTR_ID_Talent1Up           ,      //����
		ATTR_ID_Talent1Base         ,      //����
		ATTR_ID_Talent1Int          ,      //����
		ATTR_ID_Talent1Perm         ,      //����
		ATTR_ID_Talent1             ,      //����

		ATTR_ID_Talent2Init         ,      //����
		ATTR_ID_Talent2Up           ,      //����
		ATTR_ID_Talent2Base         ,      //����
		ATTR_ID_Talent2Int          ,      //����
		ATTR_ID_Talent2Perm         ,      //����
		ATTR_ID_Talent2             ,      //����

		ATTR_ID_Talent3Init         ,      //����
		ATTR_ID_Talent3Up           ,      //����
		ATTR_ID_Talent3Base         ,      //����
		ATTR_ID_Talent3Int          ,      //����
		ATTR_ID_Talent3Perm         ,      //����
		ATTR_ID_Talent3             ,      //����

		ATTR_ID_Talent4Init         ,      //����
		ATTR_ID_Talent4Up           ,      //����
		ATTR_ID_Talent4Base         ,      //����
		ATTR_ID_Talent4Int          ,      //����
		ATTR_ID_Talent4Perm         ,      //����
		ATTR_ID_Talent4             ,      //����

		ATTR_ID_Talent5Init         ,      //����
		ATTR_ID_Talent5Up           ,      //����
		ATTR_ID_Talent5Base         ,      //����
		ATTR_ID_Talent5Int          ,      //����
		ATTR_ID_Talent5Perm         ,      //����
		ATTR_ID_Talent5             ,      //����

		ATTR_ID_Talent6Init         ,      //����
		ATTR_ID_Talent6Up           ,      //����
		ATTR_ID_Talent6Base         ,      //����
		ATTR_ID_Talent6Int          ,      //����
		ATTR_ID_Talent6Perm         ,      //����
		ATTR_ID_Talent6             ,      //����

		ATTR_ID_HpMaxBase           ,      //�������
		ATTR_ID_HpMaxInt            ,      //�������
		ATTR_ID_HpMaxPerm           ,      //�������
		ATTR_ID_HpMax               ,      //�������

		ATTR_ID_MpMaxBase           ,      //�����
		ATTR_ID_MpMaxInt            ,      //�����
		ATTR_ID_MpMaxPerm           ,      //�����
		ATTR_ID_MpMax               ,      //�����

		ATTR_ID_SpMaxBase           ,      //�������
		ATTR_ID_SpMaxInt            ,      //�������
		ATTR_ID_SpMaxPerm           ,      //�������
		ATTR_ID_SpMax               ,      //�������

		ATTR_ID_Rank1Base           ,      //����
		ATTR_ID_Rank1Int            ,      //����
		ATTR_ID_Rank1PermRate       ,      //������
		ATTR_ID_Rank1Rate           ,      //������

		ATTR_ID_Rank2Base           ,      //���
		ATTR_ID_Rank2Int            ,      //���
		ATTR_ID_Rank2PermRate       ,      //�����
		ATTR_ID_Rank2Rate           ,      //�����

		ATTR_ID_Rank3Base           ,      //�ػ�
		ATTR_ID_Rank3Int            ,      //�ػ�
		ATTR_ID_Rank3PermRate       ,      //�ػ���
		ATTR_ID_Rank3Rate           ,      //�ػ���

		ATTR_ID_Rank4Base           ,      //��
		ATTR_ID_Rank4Int            ,      //��
		ATTR_ID_Rank4PermRate       ,      //��
		ATTR_ID_Rank4Rate           ,      //��

		ATTR_ID_Atk1Base            ,      //ս��Ч��
		ATTR_ID_Atk1Int             ,      //ս��Ч��
		ATTR_ID_Atk1Perm            ,      //ս��Ч��
		ATTR_ID_Atk1                ,      //ս��Ч��

		ATTR_ID_Atk2Base            ,      //�Ʋ�Ч��
		ATTR_ID_Atk2Int             ,      //�Ʋ�Ч��
		ATTR_ID_Atk2Perm            ,      //�Ʋ�Ч��
		ATTR_ID_Atk2                ,      //�Ʋ�Ч��

		ATTR_ID_Def1Base            ,      //ս������
		ATTR_ID_Def1Int             ,      //ս������
		ATTR_ID_Def1Perm            ,      //ս������
		ATTR_ID_Def1                ,      //ս������

		ATTR_ID_Def2Base            ,      //�Ʋ߷���
		ATTR_ID_Def2Int             ,      //�Ʋ߷���
		ATTR_ID_Def2Perm            ,      //�Ʋ߷���
		ATTR_ID_Def2                ,      //�Ʋ߷���

		ATTR_ID_Atk3Change          ,      //����3��ֵ�仯
		ATTR_ID_Atk4Change          ,      //����4��ֵ�仯	
		ATTR_ID_Atk5Change          ,      //����5��ֵ�仯
		ATTR_ID_Atk6Change          ,      //����6��ֵ�仯
		ATTR_ID_Atk7Change          ,      //����7��ֵ�仯
		ATTR_ID_Atk8Change          ,      //����8��ֵ�仯		

		ATTR_ID_Def3Change          ,      //����3��ֵ�仯
		ATTR_ID_Def4Change          ,      //����4��ֵ�仯
		ATTR_ID_Def5Change          ,      //����5��ֵ�仯
		ATTR_ID_Def6Change          ,      //����6��ֵ�仯
		ATTR_ID_Def7Change          ,      //����7��ֵ�仯
		ATTR_ID_Def8Change          ,      //����8��ֵ�仯

		ATTR_ID_MyAtk1DamOther        ,      //�Ҷ����ˡ��˺�1��ֵ�仯
		ATTR_ID_MyAtk2DamOther        ,      //�Ҷ����ˡ��˺�2��ֵ�仯
		ATTR_ID_MyAtk3DamOther        ,      //�Ҷ����ˡ��˺�3��ֵ�仯
		ATTR_ID_MyAtk4DamOther        ,      //�Ҷ����ˡ��˺�4��ֵ�仯
		ATTR_ID_MyAtk5DamOther        ,      //�Ҷ����ˡ��˺�5��ֵ�仯
		ATTR_ID_MyAtk6DamOther        ,      //�Ҷ����ˡ��˺�6��ֵ�仯
		ATTR_ID_MyAtk7DamOther        ,      //�Ҷ����ˡ��˺�7��ֵ�仯
		ATTR_ID_MyAtk8DamOther        ,      //�Ҷ����ˡ��˺�8��ֵ�仯
		ATTR_ID_MyAtk9DamOther        ,      //�Ҷ����ˡ�������ֵ�仯
		ATTR_ID_MyAtk10DamOther       ,      //�Ҷ����ˡ������˺�ǧ�ֱȱ仯
		ATTR_ID_MyAtk11DamOther       ,      //�Ҷ����ˡ������˺�ǧ�ֱȱ仯
		ATTR_ID_MyAtk12DamOther       ,      //�Ҷ����ˡ�����ǧ�ֱȱ仯
		ATTR_ID_MyAtk13DamOther       ,      //�Ҷ����ˡ������ػ������仯
		ATTR_ID_MyAtk14DamOther       ,      //�Ҷ����ˡ������ػ������仯

		ATTR_ID_OtherAtk1DamMe        ,      //���˶��ҡ��˺�1��ֵ�仯
		ATTR_ID_OtherAtk2DamMe        ,      //���˶��ҡ��˺�2��ֵ�仯
		ATTR_ID_OtherAtk3DamMe        ,      //���˶��ҡ��˺�3��ֵ�仯
		ATTR_ID_OtherAtk4DamMe        ,      //���˶��ҡ��˺�4��ֵ�仯
		ATTR_ID_OtherAtk5DamMe        ,      //���˶��ҡ��˺�5��ֵ�仯
		ATTR_ID_OtherAtk6DamMe        ,      //���˶��ҡ��˺�6��ֵ�仯
		ATTR_ID_OtherAtk7DamMe        ,      //���˶��ҡ��˺�7��ֵ�仯
		ATTR_ID_OtherAtk8DamMe        ,      //���˶��ҡ��˺�8��ֵ�仯
		ATTR_ID_OtherAtk9DamMe        ,      //���˶��ҡ�������ֵ�仯
		ATTR_ID_OtherAtk10DamMe       ,      //���˶��ҡ������˺�ǧ�ֱȱ仯
		ATTR_ID_OtherAtk11DamMe       ,      //���˶��ҡ������˺�ǧ�ֱȱ仯
		ATTR_ID_OtherAtk12DamMe       ,      //���˶��ҡ�����ǧ�ֱȱ仯
		ATTR_ID_OtherAtk13DamMe       ,      //���˶��ҡ������ػ������仯
		ATTR_ID_OtherAtk14DamMe       ,      //���˶��ҡ������ػ������仯

		ATTR_ID_MyAtk1DamArmy		  ,		//�ҶԾ��ӹ���ǧ�ֱȱ仯������
		ATTR_ID_MyAtk2DamArmy		  ,		//�ҶԾ��ӹ���ǧ�ֱȱ仯��ǹ��
		ATTR_ID_MyAtk3DamArmy		  ,		//�ҶԾ��ӹ���ǧ�ֱȱ仯�����
		ATTR_ID_MyAtk4DamArmy		  ,		//�ҶԾ��ӹ���ǧ�ֱȱ仯������
		ATTR_ID_MyAtk5DamArmy		  ,		//�ҶԾ��ӹ���ǧ�ֱȱ仯����е
		ATTR_ID_MyAtk6DamArmy		  ,		//�ҶԾ��ӹ���ǧ�ֱȱ仯������

		ATTR_ID_ArmyAtk1DamMe		  ,		//���Ӷ��ҹ���ǧ�ֱȱ仯������
		ATTR_ID_ArmyAtk2DamMe		  ,		//���Ӷ��ҹ���ǧ�ֱȱ仯��ǹ��
		ATTR_ID_ArmyAtk3DamMe		  ,		//���Ӷ��ҹ���ǧ�ֱȱ仯�����
		ATTR_ID_ArmyAtk4DamMe		  ,		//���Ӷ��ҹ���ǧ�ֱȱ仯������
		ATTR_ID_ArmyAtk5DamMe		  ,		//���Ӷ��ҹ���ǧ�ֱȱ仯����е
		ATTR_ID_ArmyAtk6DamMe		  ,		//���Ӷ��ҹ���ǧ�ֱȱ仯������

		ATTR_ID_Buff1resistance		  ,		//״̬����1(��ѣ��ʧ��)
		ATTR_ID_Buff2resistance		  ,		//״̬����2(���ҺͿ־�)
		ATTR_ID_Buff3resistance		  ,		//״̬����3(�⼼�ͽ���)
		ATTR_ID_Buff4resistance		  ,		//״̬����4(����ͼ���)
		ATTR_ID_Buff5resistance		  ,		//״̬����5(������¶�)
		ATTR_ID_Buff6resistance		  ,		//״̬����6(��Ѫ������)

		ATTR_ID_Character1Multiplying ,		//��ɫ����1(������)
		ATTR_ID_Character2Multiplying ,		//��ɫ����2(�һ�����)
		ATTR_ID_Character3Multiplying ,		//��ɫ����3(�һ�����)
		ATTR_ID_Character4Multiplying ,		//��ɫ����4(ս�����)
		ATTR_ID_Character5Multiplying ,		//��ɫ����5(��������)
		ATTR_ID_Character6Multiplying ,		//��ɫ����6(�����ͷ�)

		ATTR_ID_MAX ,
		//�߻���������end

		//�����Զ��廤�ܣ��߻���û�У�
		//���״̬��ʹ�á�
		//����ˣ��쿪��
		Attr_ID_shield_FIGHT			  ,		//ս������			
		Attr_ID_shield_PLAN				  ,		//�Ʋ߻���
		Attr_ID_shield_WATER			  ,		//ˮ����
		Attr_ID_shield_FIRE				  ,		//�𻤶�
		Attr_ID_shield_WIND				  ,		//�绤��
		Attr_ID_shield_THUNDER			  ,		//�׻���
		Attr_ID_shield_SOIL				  ,		//������
		Attr_ID_shield_OTHER			  ,		//���û���
		Attr_ID_shield_ALL				  ,		//ȫ�˺�����
		Attr_ID_shield_MAGIC			  ,		//��������

		ATTR_ID_COUNT_MAX                  
	}; 
	//----------------------------------------------------------------------
	enum ATTR_ADD_TYPE                 
	{                                   
		ATTR_ADD_TYPE_NULL = 0,        

		ATTR_ADD_TYPE_NO,                   //��ʼ��ʱ�ɸı䣬�Ժ��ɹ�ʽ�����á�
		ATTR_ADD_TYPE_YES,					//��ֱ�Ӹı������

		ATTR_SHOW_TYPE_MAX              
	}; 
	//----------------------------------------------------------------------
	enum ATTR_USE_TYPE                  
	{
		ATTR_USE_TYPE_NULL = 0,

		ATTR_USE_TYPE_SYSTEM,                  //ϵͳ����
		ATTR_USE_TYPE_TALENT,                  //�츳����
		ATTR_USE_TYPE_FIGHT,                   //ս������
		ATTR_USE_TYPE_OTHER,                   //������չ����

		ATTR_USE_TYPE_MAX
	};

	enum	ABILITYJUDGE_TYPE
	{
		ABILITYJUDGE_TYPE_NULL,

		ABILITYJUDGE_TYPE_REAL,			//ʵֵ�ж�
		ABILITYJUDGE_TYPE_LVL,			//����Ŀ��ȼ��ж�����ɫ����Ʒ�����ܵȣ�

		ABILITYJUDGE_TYPE_MAX
	};

	//----------------------------------------------------------------------
	enum ITEM_RANK
	{
		ITEM_RANK_NONE,

		ITEM_RANK_WHITE,                        //��װ
		ITEM_RANK_GREEN,                        //��װ
		ITEM_RANK_BLUE,                         //��װ
		ITEM_RANK_PURPLE,                       //��װ

		ITEM_RANK_MAX
	};

	//----------------------------------------------------------------------
	enum ITEM_MONEY_CLASS
	{
		ITEM_MONEY_CLASS_NONE,

		ITEM_MONEY_CLASS_MONEY_RMB_PRESENT,             //���������
		ITEM_MONEY_CLASS_MONEY_GAME,					//��Ϸ��
		ITEM_MONEY_CLASS_MONEY_FOOD,					//��ʳ��
		ITEM_MONEY_CLASS_MONEY_MAN,						//�˿ڱ�
		ITEM_MONEY_CLASS_RENOWN_SPARE1,					//����������1
		ITEM_MONEY_CLASS_RENOWN_SPARE2,					//����������2
		ITEM_MONEY_CLASS_RENOWN_SPARE3,					//����������3
		ITEM_MONEY_CLASS_RENOWN_SPARE4,					//����������4

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

		ITEM_EQUIP_SLOT_TYPE_MAIN,                   //������
		ITEM_EQUIP_SLOT_TYPE_DEPUTY,                 //������
		ITEM_EQUIP_SLOT_TYPE_HEAD,                   //ͷ��
		ITEM_EQUIP_SLOT_TYPE_BODY,                   //����
		ITEM_EQUIP_SLOT_TYPE_FOOT,                   //�㲿
		ITEM_EQUIP_SLOT_TYPE_JEWELRY,                //����
		ITEM_EQUIP_SLOT_TYPE_ADDITION1,              //����1
		ITEM_EQUIP_SLOT_TYPE_HORSE,                  //��

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
		ITEM_SHOP_FUNCTION_TYPE_SHOPPING = 1,			//���ѹ��ܣ�������
		ITEM_SHOP_FUNCTION_TYPE_REPAIR = 2,				//����
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

		ACCESS_TYPE_NORMAL,                     //����ͨ��
		ACCESS_TYPE_ARMY,                       //����ר�õ�
		ACCESS_TYPE_GENREAL,                    //��ɫר�õ�

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
		STATUS_STATUSSYSTYPE_VERDIGO,				//ѣ��
		STATUS_STATUSSYSTYPE_CHAOS,					//����
		STATUS_STATUSSYSTYPE_BLOCKADE,				//�⼼
		STATUS_STATUSSYSTYPE_SLOWDOWN,				//����
		STATUS_STATUSSYSTYPE_POISON,				//�¶�
		STATUS_STATUSSYSTYPE_BLEED,					//��Ѫ
		STATUS_STATUSSYSTYPE_DEAD,					//����
		STATUS_STATUSSYSTYPE_INVISIBILITY,			//����
		STATUS_STATUSSYSTYPE_MAX
	};
	//----------------------------------------------------------------------
	enum STATUS_VITIATEFLAG
	{
		STATUS_VITIATEFLAG_NULL,

		STATUS_VITIATEFLAG_FIGHT = 1,					//ս��
		STATUS_VITIATEFLAG_PLAN = 2,					//����
		STATUS_VITIATEFLAG_WATER = 4,					//ˮ
		STATUS_VITIATEFLAG_FIRE = 8,					//��
		STATUS_VITIATEFLAG_WIND = 16,					//��
		STATUS_VITIATEFLAG_THUNDER = 32,				//��
		STATUS_VITIATEFLAG_SOIL = 64,					//��
		STATUS_VITIATEFLAG_OTHER = 128,					//����

		STATUS_VITIATEFLAG_MAX
	};
	//----------------------------------------------------------------------
	enum STATUS_ABSORBTYPE
	{
		STATUS_ABSORBTYPE_NULL,

		STATUS_ABSORBTYPE_FIGHT,					//ս��
		STATUS_ABSORBTYPE_PLAN,						//����
		STATUS_ABSORBTYPE_WATER,					//ˮ
		STATUS_ABSORBTYPE_FIRE,						//��
		STATUS_ABSORBTYPE_WIND,						//��
		STATUS_ABSORBTYPE_THUNDER,					//��
		STATUS_ABSORBTYPE_SOIL,						//��
		STATUS_ABSORBTYPE_OTHER,					//����
		STATUS_ABSORBTYPE_ALL,						//ȫ�˺�
		STATUS_ABSORBTYPE_MAGIC,					//����

		STATUS_ABSORBTYPE_MAX
	};
	//----------------------------------------------------------------------
	enum STATUS_CYCLETYPE
	{
		STATUS_CYCLETYPE_NULL,

		STATUS_CYCLETYPE_FIXED_DAMAGE,						//��ֵ�˺�
		STATUS_CYCLETYPE_FIXED_ABSORB,						//��ֵ����
		STATUS_CYCLETYPE_PERMILLAGE_DAMAGE,					//ǧ�ֱ��˺�
		STATUS_CYCLETYPE_PERMILLAGE_ABSORB,					//ǧ�ֱ�����
		STATUS_CYCLETYPE_MAX_PERMILLAGE_DAMAGE,				//���ֵǧ�ֱ��˺�
		STATUS_CYCLETYPE_MAX_PERMILLAGE_ABSORB,				//���ֵǧ�ֱ�����

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
		STATUS_SHOWTYPE_IMAGETIME,		//ͼƬ��ʱ��
		STATUS_SHOWTYPE_IMAGE,			//ͼƬ
		STATUS_SHOWTYPE_NOT,			//����ʾ
		STATUS_SHOWTYPE_MAX
	};
	//----------------------------------------------------------------------
	enum STATUS_STYLETYPE
	{
		STATUS_STYLETYPE_NULL,
		STATUS_STYLETYPE_SYS,			//ϵͳ
		STATUS_STYLETYPE_EQUIP,			//װ��
		STATUS_STYLETYPE_GOOD,			//����
		STATUS_STYLETYPE_BAD,			//����
		STATUS_STYLETYPE_MAX
	};
	//----------------------------------------------------------------------
	enum STATUS_TIMETYPE
	{
		STATUS_TIMETYPE_NULL,
		STATUS_TIMETYPE_FOREVER,		//���ã���ʱ�����
		STATUS_TIMETYPE_GAME,			//��Ϸʱ��
		STATUS_TIMETYPE_REAL,			//��ʵʱ��
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

		STATUS_TYPE_CHARACTER,			//��ɫ
		STATUS_TYPE_CLAN,				//����
		STATUS_TYPE_PLACE,				//�ݵ�
		STATUS_TYPE_FORCE,				//����

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