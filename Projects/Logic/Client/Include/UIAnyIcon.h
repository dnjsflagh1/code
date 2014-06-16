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
		//���ر����еĵ���
		//sitetype��Ҫ�����ĵ��ߵ�λ�ã� 
		//index����λ�õ�������
		//������ߵ���Ļ���ꡣ
		void			loadItem(ITEM_SITE_TYPE sitetype, UInt index, CoordI screenCoord, Bool isAddButton);

	private://�¼�����
		//���icon����iconinfo
		static void		onClickIcon(void* pWidget);

		//���ж�ذ�ť
		static void		onClickUninstall(void* pWidget);

		//ʧȥ����ص�UI
		static  void    notifyKeyLostFocusEvent(void* widget, void* newWidget);
		static  void	onEventToolTips(void* pWidget, Bool isShow, Int left, Int top);

		void  onHandleTips( Bool isShow, IconInfo* pIconInfo, CoordI coord);

	private:
		//������װ
		void			onHandleUninstall();
		//���ͽ������ߵ���Ϣ
		void			sendChangeItem(ITEM_SITE_TYPE sitetype, UInt index, Bool isUninstall);
		//���ص���
		void			loadItem();
		//����λ��
		void			adjustUIPos();
		//����ͼƬ
        void            addItemIcon(IconInfo* pIconInfo, U32 index);
		//��õ���list
		void			getItemList(std::vector<IconInfo>& iconlist );
		//��жװ��ť
		void			addUninstallButton();
		//�����Ե��ӿؼ��ر�
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