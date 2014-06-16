//***************************************************************************************************
#ifndef _H_UICLANROLE_INFO_
#define _H_UICLANROLE_INFO_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//***************************************************************************************************
namespace MG
{
    //--------------------------------------------------------------------------
    enum UI_CLAN_INFO_TYPE
    {
        UI_CLAN_INFO_TYPE_NULL,

        UI_CLAN_INFO_TYPE_INFO,          //信息
        UI_CLAN_INFO_TYPE_GOODS,         //物资
        UI_CLAN_INFO_TYPE_EQUIP,         //装备
        UI_CLAN_INFO_TYPE_ARMY,          //军队

        UI_CLAN_INFO_TYPE_MAX
    };
	enum UI_CLAN_DRAG_OPREATE
	{
		OPERATE_DRAG_NILL,				//无拖动操作
		OPREATE__ITEM_CHANGEPOS,		//更换物品位置拖动
		OPERATE_ITEM_SPLIT,				//拆分物品拖动
		OPREATE_ITEM_MAX
	};
    //--------------------------------------------------------------------------
    class UIClanInfo  : public UIObject
    {
    public:
        UIClanInfo();
        ~UIClanInfo();
        SINGLETON_INSTANCE(UIClanInfo);

    public:
        virtual void    setEvent();
        virtual Bool    openGui();
        virtual void    restore();

    //道具
    //-------------------------------------------------------------------------------------------
    public: //外部接口
        void            addItem(PlayerItem* pItem, ITEM_SITE_TYPE type, bool addKeyboard = false);
        void            deleteItem(U32 index, ITEM_SITE_TYPE type,bool delKeyboard = false );
        void            updateItem(U32 index, U32 num, ITEM_SITE_TYPE type,bool updateKeyboard = false);
        IdType          getCurGenrealId(){return mSelectGeneralId;}

		//通知UI加CD了。
		void			notifyUIAddCD( U32 cdId, U32 cdtime, U32 totalTime, PlayerCharacterIdType characterId = 0 );
		//通知UI删除CD了。
		void			notifyUIDeleteCD( U32 cdid, PlayerCharacterIdType characterId = 0 );
		//换页或者删除CDGroup时调用
		void			updateItemCD();

		void			updateBasicAttr();
		void		    updateMoney();
		void			updateLevel();
		void			updateExp();
		void			addCharSkillList(CPlayerCharacter* pCPlayerCharacter=NULL);
		void            onHandleSelectGenreal(PlayerCharacterIdType charid);
	
		


    private:
        void            addClanBagItem(PlayerItem* pItem);
        void            deleteClanBagItem(U32 index);
        void            updateClanBagItem(U32 index, U32 num);
        void            clearClanBagItemList();

        void            addUICharItem(PlayerItem* pItem);
        void            deleteUICharItem(U32 index);
        void            updateUICharItem(U32 index, U32 num);
        void            clearCharItemList();

        void            addCharEquip(PlayerItem* pItem);
        void            deleteCharEquip(U32 index);
        void            clearCharEquipList();

		void			addCharSkill(const SkillInfo* skillinfo, Bool isInitiative, U32 num);

		


    private://回调事件
        static void     onClickClanInfoBtn(void* pWidget);
        static void     onClickGenrelLeftBtn(void* pWidget);
        static void     onClickGenrelRightBtn(void* pWidget);
		static void     onRightClickImgItem(void* pWidget);
        static void     onClickGenrealList(void* pWidget, Int index);
        static void     onEventToolTips(void* pWidget, Bool isShow, Int left, Int top);
        static void     onEventDrag(void* pWidget, int left, int top);
        static void     onClickItemIcon(void* pWidget);
        static void     onClickClanBagBtn(void* pWidget);
        static void     onDoubleClickGenrealItem(void* pWidget);
		static void		onGetMouseFocusEvent(void* pGetWidget, void* pLostWidget);
		static void		onLostMouseFocusEvent(void* pLostWidget, void* pGetWidget);
		static void     onSureSplitItem(void* arg, Int splitCount, Int maxCount);
		static void		onCancelSplitItem(void* arg);

    private:
		void			onHandleDrag(IWidget* pWidget);
        void            onHandleCutUI(UI_CLAN_INFO_TYPE type);
        void            onHandleRefreshEquipList(Bool isAdd);
        
        void            onHandleTips(Bool isShow, IconInfo* pIconInfo, CoordI coord);
        void            onHandleGetIconInfo(IconInfo* pSendInfo, void*& widget2, CoordI rect);
        void            onHandleDrop(IconInfo* pSend, IconInfo* pRece);
        void            onHandleClickGenrealItemIcon(IconInfo* pIconInfo, CoordI screenCoord);
        void            onHandleCutClanBag(Int index);
        void            onHandleDoubleClickGenrealItem(IconInfo* pIconInfo);
		//选择蒙板
		void			setHighVisble( ICON_GROUP type, Int Index, Bool isVisble );
		void			setSelectGeneralUI();

    //-----------------------------------------------------------------------------------------------
    private://窗口的切换
        void            updateBgByClanInfoType(UI_CLAN_INFO_TYPE type);
        void            openClanGoodsBg();
        void            openClanInfoBg();
        void            openClanEquipBg();
        void            openClanArmyBg();
   
    private://刷新氏族信息
        void            clearClanInfo();
    
    private://icon的拖曳
        void            onHandleClanBag( IconInfo* pSend, IconInfo* pRece );
        void            onHandleCharBag( IconInfo* pSend, IconInfo* pRece );
        void            onHandleCharEquip( IconInfo* pSend, IconInfo* pRece  );
        //氏族背包
        void            clanBagDropItem(IdType itemdbid);
        void            clanBagChangePos(IconInfo* pSendInfo, IconInfo* pReceInfo);
        void            checkSpecialOperate(IconInfo* pSendInfo);
        //角色背包和装备
        void            characterBagDropItem(IdType itemdbid);
        void            characterEquipDropItem(IdType itemdbid);
        void            characterBagChangePos(IconInfo* pSendInfo, IconInfo* pReceInfo);
        void            characterEquipChangePos(IconInfo* pSendInfo, IconInfo* pReceInfo);
		void            onSplitItem(IconInfo* pSendInfo, IconInfo* pReceInfo);

    private://发送消息
        void            sendDropItem(ITEM_SITE_TYPE type, IdType ID, PlayerCharacterIdType charid);
        void            sendBagChangePos(U32 sendIndex, U32 recvIndex,ITEM_SITE_TYPE sendType,ITEM_SITE_TYPE recvType, PlayerCharacterIdType charid);
    
    //-----------------------------------------------------------------------------------------------
    //角色list
    public: //外部接口
        void            addPlayerCharacter(CPlayerCharacter* pChar);
        void            delPlayerCharacter(CPlayerCharacter* pChar);
        void            updatePlayerCharacter(CPlayerCharacter* pChar);

    public:
        void            initPlayerCharacterList();
        void            updatePlayerCharacterInfo();
        void            clearGenrealInfo();
		void			clearAllGenrealList();

    //-----------------------------------------------------------------------------------------------
    //武将UI
    private://刷新武将信息。
        void            clearSkillList();
		void			updateItemCDByCDTimer(const CDTimer* cdtimer);

    private:
        UI_CLAN_INFO_TYPE               mSelectClanInfoType;
        PlayerCharacterIdType           mSelectGeneralId;
        U32                             mTotalGenralPage;
        U32                             mCurGenrealPage;
        U32                             mCurClanBagPage;
		IconInfo*						mSplitItemInfo;
		U32								mSplitCount;
		UI_CLAN_DRAG_OPREATE			mDragOperate;
		IdType							mOnTipsItemDBId;  //用来物品卖出，或删除时，tips的清除
		IdType							mOnHighSelectItemDBId;
    };
}
//***************************************************************************************************
#endif
//***************************************************************************************************