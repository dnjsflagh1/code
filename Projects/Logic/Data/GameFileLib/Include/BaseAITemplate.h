//*****************************************************************************************************************
#ifndef _BASEAITEMPLATE_H_
#define _BASEAITEMPLATE_H_
//*****************************************************************************************************************
#include "GameFilePreqs.h"
//*****************************************************************************************************************
namespace MG
{
	//-------------------------------------------------------------------------------

	struct BaseAIInfo 
	{
		UInt								aiBaseId;
		BaseAIType							aiBaseType;
		std::vector<Flt>					paramList;
	};

	//-------------------------------------------------------------------------------
	class BaseAITemplate
	{
	public:
		BaseAITemplate();
		~BaseAITemplate();
		SINGLETON_INSTANCE(BaseAITemplate);

	public:
		// MG_CN_MODIFY
		Bool									load( Str16 fileName, IMGExternalPackManager* packManager = NULL );
		const BaseAIInfo*						getBaseAIInfo( UInt id );

	private:
		void									clear();

	private:
		std::map<UInt, BaseAIInfo*>				mBaseAIInfoList;
	};

}
//*****************************************************************************************************************
#endif
//*****************************************************************************************************************