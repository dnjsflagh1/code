//*************************************************************************************
#ifndef _UIYESNOMSGBOX_H_
#define _UIYESNOMSGBOX_H_
//*************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//*************************************************************************************
namespace MG
{
	class  UIYesNoMsgBox : public UIObject
	{
	public:
		UIYesNoMsgBox();
		virtual ~UIYesNoMsgBox(){;}
		SINGLETON_INSTANCE(UIYesNoMsgBox);

	public:
		virtual void    setEvent();

	public:    //����Ϣ�򣬲�������Ϣ������
		void    showHint(
			std::wstring msgTtSec, std::wstring msgTtKey, std::wstring defaultTt, 
			std::wstring msgConSec, std::wstring msgConKey, std::wstring defaultCon,
			void* userConfirm = NULL, PVOID_CALLBACK funcConfirm = NULL,
			void* userCansel = NULL, PVOID_CALLBACK funcCansel = NULL
			);
		void    showHint(
			Str16 title,Str16 content,
			void* userConfirm = NULL, PVOID_CALLBACK funcConfirm = NULL,
			void* userCansel = NULL, PVOID_CALLBACK funcCansel = NULL
			);

	public:    //����ȷ����ť�������¼�
		static  void    onclickConfirm(void* widget);
		static  void    onclickCansel(void* widget);

	protected: //���ûص�����
		void    callConfirm();
		void    callCansel();

	protected:
		PVOID_CALLBACK      mpFuncConfirm;
		void*               mpUserConfirm; 
		PVOID_CALLBACK      mpFuncCansel;
		void*               mpUserCansel;
	private:
		Int                 getEditBoxWidth();
		Int                 getEditBoxHeight();

	};
}

#endif