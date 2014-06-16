/******************************************************************************/
#ifndef _CTROOPEFFECTENTITYGROUPMANAGER_H_
#define _CTROOPEFFECTENTITYGROUPMANAGER_H_
/******************************************************************************/
#include "ClientPreqs.h"
/******************************************************************************/


namespace MG
{

	/******************************************************************************/
	/// CTroopObject
	/******************************************************************************/

	struct EffectComponentGroup
	{
		std::vector<IEntityGroup*>			effectEntityGroupList;
	};

	class CTroopEffectEntityGroupManager
	{
	public:
		CTroopEffectEntityGroupManager();
		virtual ~CTroopEffectEntityGroupManager();
		SINGLETON_INSTANCE(CTroopEffectEntityGroupManager);

	public:
		// CN_MODIFY
		IEntity*							getEffectComponent(UInt effectID);

		void								destroyEffectComponent(UInt effectID, IEntity* entity);

	protected:
		IEntity*							getInVisibleEffectComponent(UInt effectID);

		IEntityGroup*						createEffectComponentGroup(UInt effectID);

		void								destroyAllEffectComponent();

	private:
		std::map<UInt, EffectComponentGroup*>	mEffectComponentGroupList;
	};
}

#endif
