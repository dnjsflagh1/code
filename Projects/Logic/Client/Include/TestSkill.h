//**************************************************************************************************
#ifndef _TESSKILL_H
#define _TESSKILL_H
//**************************************************************************************************

#include "ClientPreqs.h"

//**************************************************************************************************
namespace MG
{
    class  TestSkill
    {
    public:
        TestSkill();
        ~TestSkill();
        SINGLETON_INSTANCE(TestSkill);
    public:
        Bool init();
        Bool update();

    private:

        CPlayerCharacterEntity* mEntity;
		CPlayerCharacterEntity* mEntityCampare;
		MG::IEntity*			mEngineEntity;
    };
}

//**************************************************************************************************
#endif
//**********************************