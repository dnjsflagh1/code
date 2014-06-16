//*******************************************************************************************************
#ifndef _H_CDTIMERFORCHARACTER_
#define _H_CDTIMERFORCHARACTER_
//*******************************************************************************************************
#include "WorldCorePreqs.h"
#include "WorldCoreDefine.h"
#include "CDTimer.h"
//*******************************************************************************************************
namespace MG
{
    class CDTimerForCharacter : public CDTimer
    {
    public:
        CDTimerForCharacter(GameObject* pParent);
        virtual ~CDTimerForCharacter();

    public:
        Bool    addSkillCD( SkillBaseInfo* pSkillInfo );
        Bool    checkSkillCD( SkillBaseInfo* pSkillInfo );

    protected:
    private:
       GameObject* mParent;
    };
    
}
//*******************************************************************************************************
#endif
//*******************************************************************************************************