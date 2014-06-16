/******************************************************************************/
#ifndef _CBATTLEBUILD_H_
#define _CBATTLEBUILD_H_
/******************************************************************************/
#include "ClientPreqs.h"
#include "CCharacter.h"
/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    class CBattleBuild : public CCharacter
    {
    public:
        CBattleBuild();
        virtual ~CBattleBuild();

    public:
        void                                init(BuildingData* pData);
        
    public:
        virtual BuildingData*     getData();

    ///----------------------------------------------------------------------------------------------
    /// ���Լ������
    public:
        //���Լ���ʱ����á�
        virtual UInt                        getHp();
        virtual UInt                        getMp();
        virtual void                        setHp(UInt val);
        virtual void                        setMp(UInt val);

    protected:
        
        // ������������
        virtual void                        calOtherAttr();

    /// ���Լ������ -- end
    ///----------------------------------------------------------------------------------------------


    };
}

#endif