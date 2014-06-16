//*************************************************************************************

#ifndef _UI_PVE_SCORE_H_
#define _UI_PVE_SCORE_H_

//*************************************************************************************

#include "ClientPreqs.h"
#include "UIObject.h"

//*************************************************************************************

namespace MG
{
	//-------------------------------------------------------------------------------
	class  UIPveScore : public UIObject
	{
	public:
		UIPveScore();
		~UIPveScore();
		SINGLETON_INSTANCE(UIPveScore);

	public:
		virtual void setEvent();
		virtual Bool openGui();

		void		setCloseTime(Flt seconds = 60);


		static void onClickButtonGetItem(void* widget);
		static void onClickButtonLeave(void* widget);

		static void onCloseTimeCallBack(void* widget);

		//œ‘ æToolTips
		static void onEventToolTips(void* pWidget, Bool isShow, Int left, Int top);

		void		setGroupItemId(U32 groupItemId);
		U32			getGroupItemId() const;

	private:
		void		UIShowGroupItem(U32 groupItemId);
	private:
		U32                     mGroupItemId;
	};
}

#endif	//_UI_PVE_SCORE_H_