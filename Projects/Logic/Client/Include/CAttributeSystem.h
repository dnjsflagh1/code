/***********************************************************************************************************/
#ifndef _H_CATTRIBUTESYSTEM_
#define _H_CATTRIBUTESYSTEM_
/***********************************************************************************************************/
#include "ClientPreqs.h"
#include "AttributeSystem.h"
/***********************************************************************************************************/
namespace MG
{
    class CAttributeSystem : public AttributeSystem
    {
        friend CCharacter;
    public:
        CAttributeSystem(){;}
        virtual ~CAttributeSystem(){;}

    public:
        //基本属性计算
        void                        calBaseAttr(CCharacter* pCharacter);
        void                        calBaseAttr(const CharacterTempInfo* pInfo);
    private:
    };
}
/***********************************************************************************************************/
#endif
/***********************************************************************************************************/