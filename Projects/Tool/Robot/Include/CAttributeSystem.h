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
        friend class CCharacter;
    public:
        CAttributeSystem(){;}
        virtual ~CAttributeSystem(){;}

    protected:
        //�������Լ���
        void                        calBaseAttr(CCharacter* pCharacter);
    private:
    };
}
/***********************************************************************************************************/
#endif
/***********************************************************************************************************/