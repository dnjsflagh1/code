//*****************************************************************************************************************
#ifndef _BASEAIGROUPTEMPLATE_H_
#define _BASEAIGROUPTEMPLATE_H_
//*****************************************************************************************************************
#include "GameFilePreqs.h"
#include "BaseAITemplate.h"
//*****************************************************************************************************************
namespace MG
{
	//-------------------------------------------------------------------------------

	struct BaseAIGroup 
	{
		UInt													aiBaseGroupId;
		std::map<BaseAIHead, std::map<BaseAIType, BaseAIInfo*>>	aiBaseAIInfoList;
	};

	//-------------------------------------------------------------------------------
	class BaseAIGroupTemplate
	{
	public:
		BaseAIGroupTemplate();
		~BaseAIGroupTemplate();
		SINGLETON_INSTANCE(BaseAIGroupTemplate);

	public:
		// MG_CN_MODIFY
		Bool									load( Str16 fileName, IMGExternalPackManager* packManager = NULL );
		const BaseAIGroup*						getBaseAIGroup( UInt groupId );

	private:
		void									clear();

	private:
		std::map<UInt, BaseAIGroup*>			mBaseAIGroupList;
	};

}
//*****************************************************************************************************************
#endif
//*****************************************************************************************************************