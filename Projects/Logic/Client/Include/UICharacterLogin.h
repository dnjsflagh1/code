//*************************************************************************************
#ifndef _UICHARACTERLOGIN_H_
#define _UICHARACTERLOGIN_H_
//*************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
#include "LoginNetPacket.h"
//*************************************************************************************
namespace MG
{
    class  UICharacterLogin:public UIObject
    {
	public:
		UICharacterLogin(){;}
		virtual ~UICharacterLogin(){;}
		SINGLETON_INSTANCE(UICharacterLogin);
		 virtual void setEvent();
	
		void			setPanelValue(Char16* frontServerName, Char* ip, I32 port);
		static void		onClickLoginFrontServer(void* widget);
		static void		onClickSelectPlayerCharacter(void* widget);
		//void			createPlayerCharacter(PT_ACC_C2F_LOGIN_DATA* data,I32 dataSize);

	private:
		Char16		mName[MAX_SERVER_NAME_LEN];
		Char		mIp[MG_NET_MAX_IP_LEN];
		I32			mPort;
	};
}

#endif