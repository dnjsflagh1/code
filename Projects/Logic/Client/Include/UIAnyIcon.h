//*************************************************************************************************************
#ifndef _H_UI_ANYICON_
#define _H_UI_ANYICON_
//*************************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//*************************************************************************************************************
namespace MG
{
    class UIAnyIcon : public UIObject
    {
    public:
        UIAnyIcon();
        ~UIAnyIcon();
        SINGLETON_INSTANCE(UIAnyIcon);

	public:
		virtual void    setEvent();
		
	public:
		//加载背包中的道具
		//sitetype需要交换的道具的位置， 
		//index所在位置的索引号
		//这个道具的屏幕坐标。
		void			loadItem(ITEM_SITE_TYPE sitetype, UInt index, CoordI screenCoord, Bool isAddButton);

	private://事件函数
		//点击icon交换iconinfo
		static void		onClickIcon(void* pWidget);

		//点击卸载按钮
		static void		onClickUninstall(void* pWidget);

		//失去焦点关掉UI
		static  void    notifyKeyLostFocusEvent(void* widget, void* newWidget);
		static  void	onEventToolTips(void* pWidget, Bool isShow, Int left, Int top);

		void  onHandleTips( Bool isShow, IconInfo* pIconInfo, CoordI coord);

	private:
		//处理脱装
		void			onHandleUninstall();
		//发送交换道具的信息
		void			sendChangeItem(ITEM_SITE_TYPE sitetype, UInt index, Bool isUninstall);
		//加载道具
		void			loadItem();
		//调整位置
		void			adjustUIPos();
		//加载图片
        void            addItemIcon(IconInfo* pIconInfo, U32 index);
		//获得道具list
		void			getItemList(std::vector<IconInfo>& iconlist );
		//加卸装按钮
		void			addUninstallButton();
		//将所以的子控件关闭
		void			closeAllChild();

    private:
        ITEM_SITE_TYPE	mOldItemSiteType;
		U32				mOldItemIndex;
		Bool			mIsAddButton;
		U32				mIconNum;

		CoordI			mWidgetCoord;

    };
}
//*************************************************************************************************************
#endif
//*************************************************************************************************************