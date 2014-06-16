//*************************************************************************************
#ifndef _H_UICOMMON_75438957_
#define _H_UICOMMON_75438957_
//*************************************************************************************
#include "ClientPreqs.h"
#include "IGuiType.h"
//*************************************************************************************
namespace MG
{
	//*************************************************************************************
	//鼠标状态
enum MGPOINTER_STATUS
{
	MGPOINTER_STATUS_NONE = 0,

	MGPOINTER_STATUS_NORMAL,
	MGPOINTER_STATUS_TALK,
	MGPOINTER_STATUS_ENTER,
	MGPOINTER_STATUS_ATTACK,
	MGPOINTER_STATUS_DIS,
	MGPOINTER_STATUS_SKILL1,
	MGPOINTER_STATUS_GETTASK,
	MGPOINTER_STATUS_PAYTASK,
	MGPOINTER_STATUS_LEARN,
	MGPOINTER_STATUS_REPAIR,
	MGPOINTER_STATUS_RPGPICK1,
	MGPOINTER_STATUS_RPGPICK2,
	MGPOINTER_STATUS_SKILL2,
	MGPOINTER_STATUS_WALK,

	MGPOINTER_STATUS_SLG_NORMAL,
	MGPOINTER_STATUS_SLG_TALK,
	MGPOINTER_STATUS_SLG_ENTER,
	MGPOINTER_STATUS_SLG_ATTACK,
	MGPOINTER_STATUS_SLG_DIS,
	MGPOINTER_STATUS_SLG_DIG,
	MGPOINTER_STATUS_SLG_VIEW,

	MGPOINTER_STATUS_COUNT
};
static Str8 pointerStatusName[MGPOINTER_STATUS_COUNT] = 
{
	"",				//消失。
	"RPGNor",		//RPG状态下的普通箭头
	"RPGTalk",		//RPG状态下的交谈箭头
	"RPGEnter",		//RPG状态下的进入箭头
	"RPGAttack",	//RPG状态下的攻击箭头
	"RPGDis",		//RPG状态下的不可点击箭头
	"RPGSkill",	//RPG状态下的技能攻击箭头
	"RPGGetTask",	//RPG状态下的接任务箭头
	"RPGPayTask",	//RPG状态下的交任务箭头
	"RPGLearn",		//RPG状态下的学习技能箭头
	"RPGRepair",	//RPG状态下的修理箭头
	"RPGPick1",		//RPG状态下的拾取箭头（手指张开）
	"RPGPick2",		//RPG状态下的拾取箭头（手指合拢）
	"RPGSkill2",	//RPG状态下的技能准备箭头

	"SLGWalk",		//SLG状态下的行走箭头
	"SLGNor",		//SLG状态下的普通箭头
	"SLGTalk",		//SLG状态下的交谈箭头
	"SLGEnter",		//SLG状态下的进入箭头
	"SLGAttack",	//SLG状态下的攻击箭头
	"SLGDis",	//SLG状态下的不可点击箭头
	"SLGDig",	//SLG状态下的挖掘/修建箭头
	"SLGView"	//SLG状态下的查看箭头
};
    //*************************************************************************************
    typedef void (*PopupMenuFunc)(UInt id);
    //*************************************************************************************
    #define MAIN_WIDGET "_Main"
    #define CHAR_EQUIP_NUM 8
    #define CHAR_ITEM_NUM 4
    #define MG_FLAG_NONE  0
    #define MG_FLAG(num)  (1<<(num))
    #define CLAN_ITEM_BAG_NUM   40                //氏族背包的格数
    #define ITEM_SHOP_NUM   12                     //商店每页可摆放的物品数量。
    //*************************************************************************************
    //控件名
    #define WIDGET_WIDGET       "Widget"
    #define WIDGET_BUTTON       "Button"
    #define WIDGET_COMBOBOX     "Combobox"
    #define WIDGET_FORM         "Window"
    #define WIDGET_EDIT         "EditBox"
    #define WIDGET_IMAGE        "ImageBox"
    #define WIDGET_LIST         "ListBox"
    #define WIDGET_PROGRESS     "ProgressEx"
    #define WIDGET_ROLLINGTEXT  "RollingText"
    #define WIDGET_TAB          "Tab"
    #define WIDGET_TABITEM      "TabItem"
    #define WIDGET_TEXT         "TextBox"
    #define WIDGET_VIEWSCROLL   "ScrollView"
    #define WIDGET_MIXTREE      "MixTree"
    #define WIDGET_MIXLIST      "MixList"
    //与控件对应的skin
    //button
    //MGButton1001, MGButton1002, MGButton1003, MGButton2001, MGButtonDwon1001, MGButtonDwon1002, MGButtonUp1001, MGButtonUp1002
    //MGButtonLeft1001, MGButtonRight1001, MGButtonX1001, MGButtonH1001, MGButtonImageText, MGCheckBox1001
    //Icon
    //Icon
    //Combobox
    //MGCombobox1001
    //Edit
    //MGEdit2001, MGEdit2002, EditEmpty
    //List
    //MGList1001
    //ProgressEx
    //Progress, MGProgressHP1001,MGProgressMP1001, MGProgressSP1001
    //ScrollView
    //MGViewScroll1001, MGViewScroll1001, MGViewScrollEmpty
    //ImageBox
    //StaticImage
    //StaticText
    //StaticText
    //Tab
    //Tab
    //TabItem
    //TabItem
    //Window
    //MGWindow2001,MGWindow2002
    //MixTree
    //MGMixTree
    //RollingText
    //MGRollingText
    //Widget
    //MGPanel2001, MGPanel2002, MGPanel2003
    //MixList
    //MGMixList
    //*************************************************************************************
    //*************************************************************************************
    const size_t MG_NONE = ~(size_t)0;
    const int MGDEFAULT ((int)-1);
    const float MG_ALPHA_MAX = 1.0f;
    const float MG_ALPHA_MIN = 0.0f;

    
    //*************************************************************************************
    enum ICON_TYPE
    {
        ICON_TYPE_NULL = 0,

        ICON_TYPE_ITEM,                 //道具
        ICON_TYPE_SKILL,                //技能
        ICON_TYPE_STATE,                //buff

        ICON_TYPE_MAX
    };
    //-------------------------------------------------------------------------
    enum  ICON_GROUP
    {
        ICON_GROUP_NULL = 0,

        ICON_GROUP_CLAN_BAG,            //氏族背包
        ICON_GROUP_CHARACTER_BAG,       //角色背包
        ICON_GROUP_CHARACTER_EQUIP,     //角色装备
        ICON_GROUP_CHARACTER_SKILL,     //角色技能栏
        ICON_GROUP_CHARACTER_LIFESKILL, //角色生活技能
        ICON_GROUP_ITEMSHOP,            //道具商店
        ICON_GROUP_SHORTCUT_SKILL,       //快捷栏技能
		ICON_GROUP_SHORTCUT_ITEM,		//快捷栏物品
        
        ICON_GROUP_MAX
    };
	//-------------------------------------------------------------------------
	//系统设置选项
	enum SysSettingType
	{
		SYS_SET_TYPE_FUNCTION = 1,
		SYS_SET_TYPE_VIDEO,
		SYS_SET_TYPE_AUDIO,
		SYS_SET_TYPE_NETWORK
	};

    //*************************************************************************************
    struct IconInfo 
    {
        //下面几项是控件ICON附带的属性，需动态更改。
        IdType      dbID;                   //DB ID，道具专用
        U32         tempID;                 //模板id
        Str8        resouceName;            //icon的三个资源
        Str8        groupName;
        Str8        itemName;

        //下面几项是控件ICON存在时必须具备的属性，设定后不可更改
        ICON_TYPE   type;                   //图片类型
        ICON_GROUP  group;                  //图片属于哪个群
        U32         index;                  //icon的索引号

        IconInfo()
            :tempID(0)
            ,dbID(0)
            ,index(0)
            ,type(ICON_TYPE_NULL)
            ,group(ICON_GROUP_NULL)
        {
            ;
        }
		//--------------------------------------------------------
        IconInfo(const IconInfo& info)
		{
			tempID      = info.tempID;
			dbID        = info.dbID;
			resouceName = info.resouceName;
			groupName   = info.groupName;
			itemName    = info.itemName;

			type        = info.type;
			group       = info.group;
			index       = info.index;
		}
		//--------------------------------------------------------
        void clear()
        {
            tempID      = 0;
            dbID        = 0;
            resouceName.clear();
            groupName.clear();
            itemName.clear();
        }
		//--------------------------------------------------------
        IconInfo& operator=(const IconInfo& info)
        {
            tempID      = info.tempID;
            dbID        = info.dbID;
            resouceName = info.resouceName;
            groupName   = info.groupName;
            itemName    = info.itemName;

            return *this;
        }
		//--------------------------------------------------------
        void  copy(const IconInfo& info)
        {
            tempID      = info.tempID;
            dbID        = info.dbID;
            resouceName = info.resouceName;
            groupName   = info.groupName;
            itemName    = info.itemName;

            type        = info.type;
            group       = info.group;
            index       = info.index;
        }
    };
}
//*************************************************************************************
#endif
//*************************************************************************************