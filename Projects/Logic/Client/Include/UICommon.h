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
	//���״̬
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
	"",				//��ʧ��
	"RPGNor",		//RPG״̬�µ���ͨ��ͷ
	"RPGTalk",		//RPG״̬�µĽ�̸��ͷ
	"RPGEnter",		//RPG״̬�µĽ����ͷ
	"RPGAttack",	//RPG״̬�µĹ�����ͷ
	"RPGDis",		//RPG״̬�µĲ��ɵ����ͷ
	"RPGSkill",	//RPG״̬�µļ��ܹ�����ͷ
	"RPGGetTask",	//RPG״̬�µĽ������ͷ
	"RPGPayTask",	//RPG״̬�µĽ������ͷ
	"RPGLearn",		//RPG״̬�µ�ѧϰ���ܼ�ͷ
	"RPGRepair",	//RPG״̬�µ������ͷ
	"RPGPick1",		//RPG״̬�µ�ʰȡ��ͷ����ָ�ſ���
	"RPGPick2",		//RPG״̬�µ�ʰȡ��ͷ����ָ��£��
	"RPGSkill2",	//RPG״̬�µļ���׼����ͷ

	"SLGWalk",		//SLG״̬�µ����߼�ͷ
	"SLGNor",		//SLG״̬�µ���ͨ��ͷ
	"SLGTalk",		//SLG״̬�µĽ�̸��ͷ
	"SLGEnter",		//SLG״̬�µĽ����ͷ
	"SLGAttack",	//SLG״̬�µĹ�����ͷ
	"SLGDis",	//SLG״̬�µĲ��ɵ����ͷ
	"SLGDig",	//SLG״̬�µ��ھ�/�޽���ͷ
	"SLGView"	//SLG״̬�µĲ鿴��ͷ
};
    //*************************************************************************************
    typedef void (*PopupMenuFunc)(UInt id);
    //*************************************************************************************
    #define MAIN_WIDGET "_Main"
    #define CHAR_EQUIP_NUM 8
    #define CHAR_ITEM_NUM 4
    #define MG_FLAG_NONE  0
    #define MG_FLAG(num)  (1<<(num))
    #define CLAN_ITEM_BAG_NUM   40                //���屳���ĸ���
    #define ITEM_SHOP_NUM   12                     //�̵�ÿҳ�ɰڷŵ���Ʒ������
    //*************************************************************************************
    //�ؼ���
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
    //��ؼ���Ӧ��skin
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

        ICON_TYPE_ITEM,                 //����
        ICON_TYPE_SKILL,                //����
        ICON_TYPE_STATE,                //buff

        ICON_TYPE_MAX
    };
    //-------------------------------------------------------------------------
    enum  ICON_GROUP
    {
        ICON_GROUP_NULL = 0,

        ICON_GROUP_CLAN_BAG,            //���屳��
        ICON_GROUP_CHARACTER_BAG,       //��ɫ����
        ICON_GROUP_CHARACTER_EQUIP,     //��ɫװ��
        ICON_GROUP_CHARACTER_SKILL,     //��ɫ������
        ICON_GROUP_CHARACTER_LIFESKILL, //��ɫ�����
        ICON_GROUP_ITEMSHOP,            //�����̵�
        ICON_GROUP_SHORTCUT_SKILL,       //���������
		ICON_GROUP_SHORTCUT_ITEM,		//�������Ʒ
        
        ICON_GROUP_MAX
    };
	//-------------------------------------------------------------------------
	//ϵͳ����ѡ��
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
        //���漸���ǿؼ�ICON���������ԣ��趯̬���ġ�
        IdType      dbID;                   //DB ID������ר��
        U32         tempID;                 //ģ��id
        Str8        resouceName;            //icon��������Դ
        Str8        groupName;
        Str8        itemName;

        //���漸���ǿؼ�ICON����ʱ����߱������ԣ��趨�󲻿ɸ���
        ICON_TYPE   type;                   //ͼƬ����
        ICON_GROUP  group;                  //ͼƬ�����ĸ�Ⱥ
        U32         index;                  //icon��������

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