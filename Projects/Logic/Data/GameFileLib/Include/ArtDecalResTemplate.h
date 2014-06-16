//************************************************************************************************************
#ifndef _ARTDECALRESTEMPLATE_H_
#define _ARTDECALRESTEMPLATE_H_
//************************************************************************************************************
#include "GameFilePreqs.h"
#include "SkillBaseInfo.h"
//************************************************************************************************************
namespace MG
{

	enum DecalAdvanceType
	{
		DAT_NULL,
	};

	enum DecalUseType
	{
		DUT_NULL,
		DUT_SKILL,
	};

	struct ArtDecalResInfo
	{
		UInt						Id				;
		DecalAdvanceType			advanceType		;
		DecalUseType				useType         ;
		UInt						resPackId		;
		Str16						filePath		;
		Str16						fileName        ;
		UInt						replaceResId	;
	};

	//---------------------------------------------------------------------------------------------
	class ArtDecalResTemplate
	{
	public:
		ArtDecalResTemplate();
		~ArtDecalResTemplate();
		SINGLETON_INSTANCE(ArtDecalResTemplate);

	public:
		// MG_CN_MODIFY
		Bool														load( Str16 fileName, IMGExternalPackManager* packManager = NULL );
		const ArtDecalResInfo*										getArtDecalResInfo( UInt id );

	private:
		void														clear();

	private:
		std::map<U32, ArtDecalResInfo*>								mArtDecalResInfoList;

	};
}
//************************************************************************************************************
#endif
//************************************************************************************************************