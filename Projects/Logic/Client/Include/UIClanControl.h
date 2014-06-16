//*************************************************************************************
#ifndef _UICLANCONTROL_H_
#define _UICLANCONTROL_H_
//*************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//*************************************************************************************
namespace MG
{
    class  UIClanControl:public UIObject
    {
    public:
        UIClanControl();
        virtual ~UIClanControl();
        SINGLETON_INSTANCE(UIClanControl);
    public:
        virtual Bool openGui();
        virtual void setEvent();
        virtual void update(Flt delta);
		virtual void restore();

    public:
		void    initInfo();
        void    selectClan();
		void    refreshClanInfo(const Str16 zhuZhang,const Str16 jueWei,const Str16 zhuDi,const Str16 level);  //刷新氏族面板显示信息

    private:
		static  void onClickReLogin(void* widget);
        static  void onClickReadyJoinGame(void* widget);
        static  void onClickDeleteClan(void* widget);

		//messgebox回调
		static void onNotificateDeleteOk(void* arg);
		static void onNotificateDeleteCancle(void* arg);
		static void	onReturnAccount(void* arg);
		static void	onReallyJoinGame(void* arg);

	public:

		void		joinGame();

    private:
        void _joinGame();
        void _deleteClan();;
    private:

    };
}

#endif