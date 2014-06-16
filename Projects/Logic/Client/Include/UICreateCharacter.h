//*************************************************************************************
#ifndef _UICREATECHARACTER_H_
#define _UICREATECHARACTER_H_
//*************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
#include "SimplePlayerCharacter.h"
//*************************************************************************************
namespace MG
{
    class  UICreateCharacter:public UIObject
    {
    public:
		UICreateCharacter():mSelectCharResourceID(-1),mCurPicCount(1),mMaxPicCount(1){;}
        virtual ~UICreateCharacter();
        SINGLETON_INSTANCE(UICreateCharacter);

		enum Direction
		{
			DIR_LEFT  = 1,
			DIR_RIGHT
		};

    public:
        virtual void setEvent();
		virtual void restore();
		virtual bool openGui();
		virtual void update(Flt delta);
		
		//messboxyesorno »Øµ÷
		static void onNotificateOK(void* arg);
		static void onNotificateCancle(void* arg);

    protected:

        static void OnClickConfirm(void* widget);
		static void OnRest(void* widget);
		static void OnRandom(void* widget);

		static void OnClickLeft(void* widget);
		static void OnClickRight(void* widget);

	public:

		void		OnClickCharacter(CCharacterSceneEntity* entity);
		void		OnMouseOverCharacter(CCharacterSceneEntity* entity);

   
	public:
        void		sendCharacterData();

	protected:

		void        initCharacter();
		void        setHeadPicList();
		void        mouseSetFocus(const Str8 highlight);
		void        mouseLostFocus(const Str8 highlight);
		void        checkCharacter(I32 index);
		void        setAttribute();
		void        changeHeadPic(Direction dir);

	private:

	   I32								 mSelectCharResourceID;
	   std::vector<SimpleCharacterResInfo>	mCharTemplates;	

       IOCN_ART_TYPE                     mIconArtType;
	   U32								 mCurPicCount;
	   U32								 mMaxPicCount;
	   std::map<U32, ArtIconResCsvInfo*>	 mIconResInfoList;
	   GENDER_TYPE						 mCheckSex;

	   

    };
}

#endif