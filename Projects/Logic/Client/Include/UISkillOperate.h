//***************************************************************************************************
#ifndef _H_UISKILLOPERATE_
#define _H_UISKILLOPERATE_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//***************************************************************************************************
namespace MG
{
	struct SkillIconIndex
	{
		Int index;
	};

	class UISkillOperate  : public UIObject
	{
	public:
		UISkillOperate();
		~UISkillOperate();
		SINGLETON_INSTANCE(UISkillOperate);

	public:
		virtual void	setEvent();
		virtual void    update(Flt delta);
		static  void	onClickKeyNum(void* widget);
		static  void    onClickItemIcon(void* widget);
        static  void	onEventToolTips(void* pWidget, Bool isShow, Int left, Int top);
		static  void	onMouseSetFocus(void* widget,void* param);
		static  void	onMouseLostFocus(void* widget,void* param);
		virtual	void	restore();

	public:
		//通知UI加CD了。
		void			notifyUIAddCD( U32 cdId, U32 cdtime, U32 totalTime, PlayerCharacterIdType characterId = 0 );
		//通知UI删除CD了。
		void			notifyUIDeleteCD( U32 cdid, PlayerCharacterIdType characterId = 0 );

	public:
		void			addSkillIcon(GAMEOBJ_TYPE characterType, IdType characterID, Int characterIndex = 0);
		void			addCharItemIcon(GAMEOBJ_TYPE characterType, IdType characterID, Int characterIndex = 0);
		void            addCharItem(PlayerItem* pItem);
		void            deleteCharItem(U32 index);
		void			updateCharItem( U32 index, U32 num );

		void            clearSkillList();
		void            clearItemList();
		static			CCharacter* getCurrCharacter();
         
	private:
		static CCharacter*              mCurrCharacter;
		static GAMEOBJ_TYPE				mCurrCharacterType;
		static IdType					mCurrCharacterID;
		static Int						mCurrCharacterIndex;

    private:
         void       updateKeyInput();
		 IconInfo*  getSkillIconInfo(Int index);
		 IconInfo*  getItemIconInfo(Int index);

	private:
		void  onHandleTips( Bool isShow, IconInfo* pIconInfo, CoordI coord);
		void  onHandleMouseSetFocus(IconInfo* pIcon);
		void  onHandleMouseLostFocus(IconInfo* pIcon);
		void  onHandleClickSkillKeyNum(IconInfo* pIcon);
		void  onHandleClickItem(IconInfo* pIconInfo);

		static void  getCharacterSkillList( GAMEOBJ_TYPE characterType, IdType characterID, std::vector<UInt>& skillList );

	};
}
//***************************************************************************************************
#endif
//***************************************************************************************************