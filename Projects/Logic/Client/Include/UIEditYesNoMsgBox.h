//*************************************************************************************
#ifndef _UIEDITYESNOMSGBOX_H_
#define _UIEDITYESNOMSGBOX_H_
//*************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//*************************************************************************************
namespace MG
{
	class  UIEditYesNoMsgBox : public UIObject
	{
	public:
		UIEditYesNoMsgBox();
		virtual ~UIEditYesNoMsgBox(){;}
		SINGLETON_INSTANCE(UIEditYesNoMsgBox);

	public:
		virtual void    setEvent();

	public:    //����Ϣ�򣬲�������Ϣ������
		void    showHint(
			std::wstring msgTtSec, std::wstring msgTtKey, std::wstring defaultTt, 
			std::wstring msgConSec, std::wstring msgConKey, std::wstring defaultCon,Int maxCount,
			void* userConfirm = NULL, PVOIDINTINT_CALLBACK funcConfirm = NULL,
			void* userCancel = NULL, PVOID_CALLBACK funcCancel = NULL
			);
		void    showHint(
			Str16 title,Str16 content,Int maxCount,
			void* userConfirm = NULL, PVOIDINTINT_CALLBACK funcConfirm = NULL,
			void* userCancel = NULL, PVOID_CALLBACK funcCancel = NULL
			);

	public:    //����ȷ����ť�������¼�
		static  void    onclickConfirm(void* widget);
		static  void    onclickCancel(void* widget);

	protected: //���ûص�����
		void    callConfirm();
		void    callCancel();

	protected:
		PVOIDINTINT_CALLBACK      mpFuncConfirm;
		void*               mpUserConfirm; 
		PVOID_CALLBACK      mpFuncCancel;
		void*               mpUserCancel;
		Int					mInputCount;
		Int					mMaxCount;

	};
}

#endif