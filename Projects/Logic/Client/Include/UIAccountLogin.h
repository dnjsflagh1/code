//*************************************************************************************
#ifndef _UIAccountLogin_H_584jf_
#define _UIAccountLogin_H_584jf_
//*************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//*************************************************************************************
namespace MG
{
    class  UIAccountLogin:public UIObject
    {
    public:
		UIAccountLogin():mIsAgreeUserPro(true),mIsSaveAccount(false){}
        virtual ~UIAccountLogin(){;}
        SINGLETON_INSTANCE(UIAccountLogin);
    public:
        virtual void setEvent();
        virtual Bool openGui();
		virtual void restore();
		virtual void update(Flt delta);

    protected:
        static void onSelectAcceptEvent(void* widget);
		static void onLogin(void* widget);
		static void onClickGoBack(void* widget);
        static void onClickMsgBoxRuleError(void* user);
        static void onReset(void* widget);
		static void onRegister(void* widget);
		static void onReCharge(void* widget);
		static void onFindPwd(void* widget);
		static void onExitGame(void* widget);
        static void onViewHomePage(void* widget);
		static void onUserProtocol(void* widget);

		static void onCboxAgreeClick(void* widget);
		static void onReturnSelectServerConfirm(void* arg);
		static void onConfirmExitGame(void* arg);

    protected:
        void		checkCanSend();
		void        setCboxAgree();
		//返回选择服务器界面
		void        goBack();           
	private:
		Bool        mIsAgreeUserPro;
		Bool        mIsSaveAccount;

    };
}

#endif