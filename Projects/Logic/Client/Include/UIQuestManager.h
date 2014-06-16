//***************************************************************************************************
#ifndef _UIQUESTMANAGER_H_
#define _UIQUESTMANAGER_H_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//***************************************************************************************************
namespace MG
{
    #define UIREWARD_ITEM_MAX_COUNT	6
	class UIQuestManager  : public UIObject
    {
    public:
        UIQuestManager();
        ~UIQuestManager();
        SINGLETON_INSTANCE(UIQuestManager);

    public:
        virtual void	setEvent();
		static	void	onClickCloseBtn(void* widget);
		static	void	onClickCheckBtn(void* widget);
		static	void	onSelectRow(void* widget,Int index);
		static	void	onClickGiveUpBtn(void* widget);
		static  void	onEventToolTips(void* pWidget, Bool isShow, Int left, Int top);
		virtual Bool	openGui();
		void			InitUI();
		virtual void	restore();
	
	public:
		void			openQuestManager();
		void			addQuest(ClanQuestObject* questObj);
		void			removeQuest(U32 clanQuestInfoId);
		void			adjustUi();

    protected:
		void			_setQuestInfo(U32 questInfoId );
		void			_clearAwardItemsUi();
		void			_setAwardItemsUi(ClanQuestObject* questObj);
		void			_clearQuestInfo();
		void            onHandleTips( Bool isShow, IconInfo* pIconInfo, CoordI coord);
		static void		onSureGiveupQuest(void* arg);

    private:
		U32				mSelectQuestInfoId;		
    };
}
//***************************************************************************************************
#endif
//***************************************************************************************************