//**********************************************************************************************************************
#ifndef _H_CHARACTERNPCLIST_
#define _H_CHARACTERNPCLIST_
//**********************************************************************************************************************
#include "GameFilePreqs.h"
//**********************************************************************************************************************
namespace MG
{
	struct CharacterNpcInfo
	{
		U32				CharacterNpcId			;
		Str16			ListName				;
		Str16			SurName					;
		Str16			Name					;
		Str16			Title					;
		Str16			Tips					;
		GENDER_TYPE		GenderType				;
		U32				Level					;
		U32				CharacterAppellationId	;
		U32				CharacterDialogId		;
		U32				AIId					;
		U32				InfluenceId				;
		U32				ArtIconId				;
		U32				ArtMashId				;
		U32				ArtEffectId				;  //Õ∑∂•±Í ∂ID
		U32				CharacterVisionEventListId;
		UInt			AIBaseGroupId			;
		UInt			AIFightGroupId			;

		U32				FunctionListId1			;
		U32				FunctionListId2			;
		U32				FunctionListId3			;
		U32				FunctionListId4			;
		U32				FunctionListId5			;
		U32				FunctionListId6			;
		U32				FunctionListId7			;
		U32				FunctionListId8			;
		//-----------------------------------------------------------------------------
        CharacterNpcInfo()
		{
			CharacterNpcId			= 0;
			ListName				= L"";
			SurName					= L"";
			Name				    = L"";	
			Title					= L"";
			Tips					= L"";
			GenderType				= GENDER_TYPE_NULL;
			Level					= 0;
			CharacterAppellationId	= 0;
			CharacterDialogId	= 0;	
			AIId				= 0;	
			InfluenceId			= 0;	
			ArtIconId			= 0;	
			ArtMashId			= 0;	
			ArtEffectId			= 0;
			CharacterVisionEventListId	        = 0;
			
			AIBaseGroupId       = 0;
			AIFightGroupId		= 0;	

			FunctionListId1		= 0;
			FunctionListId2		= 0;
			FunctionListId3		= 0;
			FunctionListId4		= 0;
			FunctionListId5		= 0;
			FunctionListId6		= 0;
			FunctionListId7		= 0;
			FunctionListId8		= 0;

		}

		U32					getNpcFunctionListId(int index)const
		{
			switch (index)
			{
			case 0:
				return FunctionListId1;
				break;
			case 1:
				return FunctionListId2;
				break;
			case 2:
				return FunctionListId3;
				break;
			case 3:
				return FunctionListId4;
				break;
			case 4:
				return FunctionListId5;
				break;
			case 5:
				return FunctionListId6;
				break;
			case 6:
				return FunctionListId7;
				break;
			case 7:
				return FunctionListId8;
				break;
			default:
				DYNAMIC_ASSERT(0);
				break;
			}
			return 0;
		}

	};

	//=-------------------------------------------------------------------------------------------------
	class CharacterNpcList
	{
	public:
		CharacterNpcList(){;}
		~CharacterNpcList();
		SINGLETON_INSTANCE(CharacterNpcList);

	public:
		// MG_CN_MODIFY
		Bool						loadFile(Str16 filename, IMGExternalPackManager* packManager = NULL);
		const CharacterNpcInfo*		getCharacterNpcInfo(U32 id);

	private:
		void						clear();

	private:
		std::map<U32, CharacterNpcInfo*>			mMapCharacterNpcInfo;

	};

}
//**********************************************************************************************************************
#endif
//**********************************************************************************************************************