//***********************************************************************************************
#ifndef _H_CREATE_CLAN_RES_CONFIG
#define _H_CREATE_CLAN_RES_CONFIG
//***********************************************************************************************
#include "GameFilePreqs.h"
//***********************************************************************************************


namespace MG
{
    
	enum
	{
		CHARACTER_ID = 0,
		CHARACTER_NAME,
		CHARACTER_TEMPLATEID

	};

	//--------------------------------------------------------------------------
	//id		   ÊÏ×åÑªÂöID;
	//templateid   ÊÏ×åÑªÂöÄ£°æID;
	//name		   ÊÏ×åÑªÂöÃû³Æ;
	//--------------------------------------------------------------------------
	struct CreateClanResInfo
	{
		U32   id;
		U32   templateid;
		Str16 name;
		CreateClanResInfo():id(0),templateid(0),name(L""){;}

	};

	class CreateClanResConfig
	{
	public:
         ~CreateClanResConfig();
		 SINGLETON_INSTANCE(CreateClanResConfig);
		 // MG_CN_MODIFY
		 Bool                                    load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
		 const CreateClanResInfo*		         getCreateResInfo(U32 id);
		 const std::map<U32, CreateClanResInfo*> getCreateResInfoList() const;

	private:
		void                          clear();

	private:
		std::map<U32, CreateClanResInfo*>  mCreateClanResList;
	};



}


#endif