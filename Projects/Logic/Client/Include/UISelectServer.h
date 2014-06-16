//*************************************************************************************
#ifndef _UISELECTSERVER_H_584JF_
#define _UISELECTSERVER_H_584JF_
//*************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//*************************************************************************************
namespace MG
{


	struct SelectServerData 
	{
		Str8    mSelectServerIp;
		I32     mSelectServerPort;
		SelectServerData()
			:mSelectServerIp(""),mSelectServerPort(0)
		{
			
		}

	};
    class  UISelectServer : public UIObject
    {
    public:
		UISelectServer():mSelectServerIp(""),mSelectServerPort(0),
			mSelectMainZoneName(L""),mSelectSubZoneName(L"") 
		{

		}
		virtual ~UISelectServer() {;}
        SINGLETON_INSTANCE(UISelectServer);

    public:

		void setEvent();

        void addServer();
		Str16 getSelectMainZoneName() const;
		Str16 getSelectSubZoneName() const;
		void setSelectMainZoneName(Str16 mainZoneName);
		void setSelectSubZoneName(Str16 subZoneName);

    public:
        
		//
		static void onClickMainZone(void* widget,Int index);
		static void onClickSubZone(void* widget,Int index);
		static void onDobuleClikSubZone(void* widget,Int index);
		static void onClickLogin(void* widget);

    protected:      
		void handlClickLogin();


	private:
		void init();
		void setSelectServerData(Str8 selectServerIp,I32 selectServerPort);

		//Int  mSelectMainZoneIndex;
		//Int
		Str8    mSelectServerIp;
		I32     mSelectServerPort;

		//
		Str16   mSelectMainZoneName;
		Str16   mSelectSubZoneName;

    };
}

#endif