//***********************************************************************************************
#ifndef _H_CHARACTER_RESOURCE_CONFIG
#define _H_CHARACTER_RESOURCE_CONFIG
//***********************************************************************************************
#include "GameFilePreqs.h"
#include "MapListCsv.h"
//***********************************************************************************************

namespace MG
{
    
	enum
	{
       CHARACTER_ID = 0,
       CHARACTER_NAME = 2,   //���˵�Note�ֶ�
	   CHARACTER_TEMPLATEID,
       CHARACTER_MAPLISTID,
	   CHARACTER_MAPLISTTYPE,
       CHARACTER_POINTRESId
	};

	//--------------------------------------------------------------------------
	//id				��ɫID;
	//templateid		��ɫģ��ID;
	//maplistid		    ��ͼID
	//maplisttype		��ͼ����
	//pointresid		����λ��
	//name              ��ɫ��������
	//--------------------------------------------------------------------------
    struct CharacterResInfo
    {
		U32					id;
        U32					templateid;
		U32					maplistid;
		MapType				maplisttype;
		U32   pointresid;
		Str16 name;
		CharacterResInfo():id(0),templateid(0),maplistid(0),maplisttype(MT_Null),
		pointresid(0),name(L"")
		{;}

    };
    
	class CharacterResourceConfig
	{
	public:
		CharacterResourceConfig(){;}
        ~CharacterResourceConfig();
		SINGLETON_INSTANCE(CharacterResourceConfig);
		// MG_CN_MODIFY
		Bool                                    load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
		const CharacterResInfo*		            getCharacterResourceInfo(U32 id);

        const std::map<U32, CharacterResInfo*>  getCharacterResourceInfoList() const;
        const Bool                              verifyResourceCorrectness(U32 resID, U32 templateid, U32 maplistid, Int maplisttype);

	private:
		void                          clear();

	private:
		std::map<U32, CharacterResInfo*>  mCharacterResourceList;
	};

}

#endif