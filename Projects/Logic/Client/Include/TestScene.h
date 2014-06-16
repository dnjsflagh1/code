//**************************************************************************************************
#ifndef _TESTSCENE_H
#define _TESTSCENE_H
//**************************************************************************************************

#include "ClientPreqs.h"
#include <vector>
#include "IEntity.h"
#include "IDecal.h"

//**************************************************************************************************
namespace MG
{
	class  TestScene
	{
	public:
		TestScene();
		~TestScene();
		SINGLETON_INSTANCE(TestScene);
	public:
		Bool init();
		Bool update();

	private:

        Bool mHighConfig;
		CPlayerCharacterEntity* mEntity;
		std::vector<IEntity*> mEntityList;
		std::vector<IEffectEntity*> mEffectEntityList;
		IDecalSet  *highlevelSet;
		Vec3 intersect_pos;
		U64					lastTime;
		U64					currTime;
		std::vector<IEffectComponent*> mEffectComponentList;
	};
}

//**************************************************************************************************
#endif
//**********************************