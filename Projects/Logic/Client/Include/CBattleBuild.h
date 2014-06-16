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
    /// 属性计算相关
    public:
        //属性计算时需调用。
        virtual UInt                        getHp();
        virtual UInt                        getMp();
        virtual void                        setHp(UInt val);
        virtual void                        setMp(UInt val);

    protected:
        
        // 计算其他属性
        virtual void                        calOtherAttr();

    /// 属性计算相关 -- end
    ///----------------------------------------------------------------------------------------------


    };
}

#endif