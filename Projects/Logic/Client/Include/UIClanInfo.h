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

        UI_CLAN_INFO_TYPE_INFO,          //��Ϣ
        UI_CLAN_INFO_TYPE_GOODS,         //����
        UI_CLAN_INFO_TYPE_EQUIP,         //װ��
        UI_CLAN_INFO_TYPE_ARMY,          //����

        UI_CLAN_INFO_TYPE_MAX
    };
	enum UI_CLAN_DRAG_OPREATE
	{
		OPERATE_DRAG_NILL,				//���϶�����
		OPREATE__ITEM_CHANGEPOS,		//������Ʒλ���϶�
		OPERATE_ITEM_SPLIT,				//�����Ʒ�϶�
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

    //����
    //-------------------------------------------------------------------------------------------
    public: //�ⲿ�ӿ�
        void            addItem(PlayerItem* pItem, ITEM_SITE_TYPE type, bool addKeyboard = false);
        void            deleteItem(U32 index, ITEM_SITE_TYPE type,bool delKeyboard = false );
        void            updateItem(U32 index, U32 num, ITEM_SITE_TYPE type,bool updateKeyboard = false);
        IdType          getCurGenrealId(){return mSelectGeneralId;}

		//֪ͨUI��CD�ˡ�
		void			notifyUIAddCD( U32 cdId, U32 cdtime, U32 totalTime, PlayerCharacterIdType characterId = 0 );
		//֪ͨUIɾ��CD�ˡ�
		void			notifyUIDeleteCD( U32 cdid, PlayerCharacterIdType characterId = 0 );
		//��ҳ����ɾ��CDGroupʱ����
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

		


    private://�ص��¼�
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
		//ѡ���ɰ�
		void			setHighVisble( ICON_GROUP type, Int Index, Bool isVisble );
		void			setSelectGeneralUI();

    //-----------------------------------------------------------------------------------------------
    private://���ڵ��л�
        void            updateBgByClanInfoType(UI_CLAN_INFO_TYPE type);
        void            openClanGoodsBg();
        void            openClanInfoBg();
        void            openClanEquipBg();
        void            openClanArmyBg();
   
    private://ˢ��������Ϣ
        void            clearClanInfo();
    
    private://icon����ҷ
        void            onHandleClanBag( IconInfo* pSend, IconInfo* pRece );
        void            onHandleCharBag( IconInfo* pSend, IconInfo* pRece );
        void            onHandleCharEquip( IconInfo* pSend, IconInfo* pRece  );
        //���屳��
        void            clanBagDropItem(IdType itemdbid);
        void            clanBagChangePos(IconInfo* pSendInfo, IconInfo* pReceInfo);
        void            checkSpecialOperate(IconInfo* pSendInfo);
        //��ɫ������װ��
        void            characterBagDropItem(IdType itemdbid);
        void            characterEquipDropItem(IdType itemdbid);
        void            characterBagChangePos(IconInfo* pSendInfo, IconInfo* pReceInfo);
        void            characterEquipChangePos(IconInfo* pSendInfo, IconInfo* pReceInfo);
		void            onSplitItem(IconInfo* pSendInfo, IconInfo* pReceInfo);

    private://������Ϣ
        void            sendDropItem(ITEM_SITE_TYPE type, IdType ID, PlayerCharacterIdType charid);
        void            sendBagChangePos(U32 sendIndex, U32 recvIndex,ITEM_SITE_TYPE sendType,ITEM_SITE_TYPE recvType, PlayerCharacterIdType charid);
    
    //-----------------------------------------------------------------------------------------------
    //��ɫlist
    public: //�ⲿ�ӿ�
        void            addPlayerCharacter(CPlayerCharacter* pChar);
        void            delPlayerCharacter(CPlayerCharacter* pChar);
        void            updatePlayerCharacter(CPlayerCharacter* pChar);

    public:
        void            initPlayerCharacterList();
        void            updatePlayerCharacterInfo();
        void            clearGenrealInfo();
		void			clearAllGenrealList();

    //-----------------------------------------------------------------------------------------------
    //�佫UI
    private://ˢ���佫��Ϣ��
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
		IdType							mOnTipsItemDBId;  //������Ʒ��������ɾ��ʱ��tips�����
		IdType							mOnHighSelectItemDBId;
    };
}
//***************************************************************************************************
#endif
//***************************************************************************************************