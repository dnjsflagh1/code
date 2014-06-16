//***************************************************************************************************
#ifndef _H_UINPC_
#define _H_UINPC_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"

//***************************************************************************************************
namespace MG
{
#define UINPC_FUNCTION_MAX_COUNT 8
#define UINPC_ITEM_MAX_COUNT	6
	struct NpcFunctionInfo;
	class NpcFuctionObject;
	struct CharacterTempInfo;
	enum NPC_DIALOG_TYPE
	{
		NPC_DIALOG_TYPE_NULL,
		NPC_DIALOG_TYPE_GENERAL,
		NPC_DIALOG_TYPE_QUEST,
		NPC_DIALOG_TYPE_PLACE,
		NPC_DIALOG_TYPE_TALK,		//�Ի�����Ի���
	};
	enum NPC_QUEST_STATE
	{
		NPC_QUEST_STATE_NULL,
		NPC_QUEST_STATE_ACCEPT,
		NPC_QUEST_STATE_UNACCEPT,
		NPC_QUEST_STATE_COMMIT,
		NPC_QUEST_STATE_UNCOMMIT,
		NPC_QUEST_STATE_TALK,
	};
	class UINpc: public UIObject
    {
    public:
        UINpc();
        ~UINpc();
        SINGLETON_INSTANCE(UINpc);

    public:
        virtual void		setEvent();
		virtual void        restore()
		{
			//;TODO ��տؼ�����������  ���µ�¼��Ϸ����
		}
		///����ڴ�
		void				clearGeneralTalkData();
		void				clearQuestData();
		void				clearPlaceData();

		void				openGeneralTalkDialog(U32 npcCharTempId,PlayerCharacterIdType characterId);
		void				openNpcQuestDialog(QuestIdType npcQuestId,NPC_QUEST_STATE state);
		void				openNpcPlaceDialog(PlaceIdType placeId,PlayerCharacterIdType characterId);
		void				returnTalkDialog();

		/// �����¼�
		static	void		onClickCloseBtn(void* widget);		// �رհ�ť
		static	void		onClickFunBtn(void* widget);		// ���ܰ�ť
		
		static void			onClickQuestCmdBtn(void* widget);	//��������
		
		static	void		onClickQuestBackBtn(void* widget);	// ���񷵻�

		static	void		onClickPlaceEneter(void* widget);	// ����ݵ�

		void				destoryFunctionObj(Int index = -1);		// index == -1 ɾ����ǰ���ܶ���

		//reward item tips
		static  void	onEventToolTips(void* pWidget, Bool isShow, Int left, Int top);
		static  void	onMouseSetFocus(void* widget,void* param);
		static  void	onMouseLostFocus(void* widget,void* param);
		//
		virtual Bool		openGui();
		virtual Bool		closeGui(Bool isForceClose =false);
	private:
		
		//�򿪲�ͬ�Ĺ��ܶԻ������
		void				_openFunctionGui(NPC_DIALOG_TYPE dialogType);
		/// ����ui
		Bool				_adjustGeneralTalkUi();
		Bool				_adjustQuestUi();
		Bool				_adjustPlaceUi();

		void				_handleQuestBtnCmd();
	
		void				_setType(NPC_DIALOG_TYPE type);
		void				_setName(Char16* name);
		void				_setTitle(Char16* title);
		void				_setTaskDescTitle(Char16* title,NPC_DIALOG_TYPE type);
		void				_setNpcIocn(UInt id);
		
		void				_setFunctionIocn(Int index = -1,Int id = -1);// id == -1���ͼ��,index = -1���õ�ǰ����ͼ��
		void				_setCurrSelectFunctionObj(Int index);
		void				_addFunction(NpcFunctionInfo* funInfo);	
		NpcFuctionObject*	_getFunctionObj(Int index = -1);			// index == -1 ��õ�ǰ���ܶ���


		/// ��ӽ�����Ʒ
		void                restoreRewardItemUi();
		void				_addRewardItem();
        void                onHandleTips( Bool isShow, IconInfo* pIconInfo, CoordI coord);
		PlaceIdType			getPlaceId() const;
		

    private:
		std::vector<NpcFuctionObject*>	mFunctionObjs;
		//std::vector<IdType>				mRewardItems;
		std::vector<ItemNum>            mRewardItems;
		//std::vector<ItemInfo*>          mRewardItemsInfo;
		
		U32								mNpcCharTempId;
		PlayerCharacterIdType			mCharacterId;
		
		PlaceIdType						mPlaceId;
		

		Int								mCurrSelectFunObjIndex;
		NPC_DIALOG_TYPE					mType;

		NPC_QUEST_STATE					mQuestState;
		QuestIdType						mQuestId;
	protected:
		U32                 getWidthStrAddBreak(Str16& src, Int width, Str8 fontName = "");   //���������ӻ��з�

	private:
		Int                 getEditBoxWidth(Int index);
		Int                 getEditBoxHeight(Int index);

    };
}
//***************************************************************************************************
#endif
//***************************************************************************************************