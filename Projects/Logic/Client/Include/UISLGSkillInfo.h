//***************************************************************************************************
#ifndef _H_UISLGSKILLINFO_
#define _H_UISLGSKILLINFO_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
#include "PlayerItem.h"
//***************************************************************************************************
namespace MG
{
	class UISLGSkillInfo  : public UIObject
	{
	public:
		UISLGSkillInfo();
		~UISLGSkillInfo();
		SINGLETON_INSTANCE(UISLGSkillInfo);

	public:
		virtual void	setEvent();
	
		virtual	void	restore();
		virtual void	update(Flt delta);
		static  void	onEventToolTips(void* pWidget, Bool isShow, Int left, Int top);
		static  void	onMouseSetFocus(void* widget,void* param);
		static  void	onMouseLostFocus(void* widget,void* param);
		static  void	onClickKeyNum(void* widget);
		static  void    onClickItemIcon(void* widget);
		

	public:
		void			UIRefresh(bool isMe,Int index);
		bool			opreatorIsMe(){return mIsMe;};
		//通知UI加CD了。
		void			notifyUIAddCD( U32 cdId, U32 cdtime, U32 totalTime, PlayerCharacterIdType characterId = 0 );
		//通知UI删除CD了。
		void			notifyUIDeleteCD( U32 cdid, PlayerCharacterIdType characterId = 0 );
	public:
		void			addSkillIcon( IdType characterID = 0);
		void			getCharacterSkillList(IdType characterID, std::vector<UInt>& skillList);
		void            addCharItems();
		void			addItemIcon(PlayerItem* item);
		void            deleteCharItem(U32 index);
		void			updateCharItem( U32 index, U32 num );

		void            clearSkillList();
		void            clearItemList();
	private:
		void			updateKeyInput();
		IconInfo*		getSkillIconInfo(Int index);
		IconInfo*		getItemIconInfo(Int index);
	private:
		void			onHandleTips( Bool isShow, IconInfo* pIconInfo, CoordI coord);
		void			onHandleMouseSetFocus(IconInfo* pIcon);
		void			onHandleMouseLostFocus(IconInfo* pIcon);
		void			onHandleClickSkillKeyNum(IconInfo* pIcon);
		void			onHandleClickItem(IconInfo* pIconInfo);
		Int				mSelectCharId;
		bool			mIsMe;

	};
}
//***************************************************************************************************
#endif
//***************************************************************************************************