//**************************************************************************************************
#ifndef _TESTEFFECT_H_
#define _TESTEFFECT_H_
//**************************************************************************************************

#include "ClientPreqs.h"

//**************************************************************************************************
namespace MG
{
    class  TestEffect
    {
    public:
        TestEffect();
        ~TestEffect();
        SINGLETON_INSTANCE(TestEffect);
    public:
        Bool init();
        Bool update();

    private:

        IEffectEntity* mEntity;
		IEffectEntity* mEntity2;
    };
}

//**************************************************************************************************
#endif
//**********************************