/******************************************************************************/
#ifndef _CCHARACTER_H_
#define _CCHARACTER_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "CCharacter.h"

/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //玩家控制的角色
    //只和逻辑相关，和显示无关
    /******************************************************************************/
    class CPlayerCharacter : public CCharacter
	{
	public:
		CPlayerCharacter();
		virtual ~CPlayerCharacter();

    public:
        PlayerCharacterData*            getData();
		Str16							getNormalName();		//姓+名

    ///----------------------------------------------------------------------------------------------
    /// 属性计算相关
    public:
        //属性计算时需调用。
        virtual void                        setHp(Int val);
        virtual void                        setMp(Int val);
        virtual void                        setSp(Int val);

    protected:
        //属性计算时需调用。
        virtual Flt                         getDBAttrInit(UInt index);
        virtual Flt                         getDBAttrLvlAdd(UInt index);
        // 计算其他属性
        virtual void                        calOtherAttr();
		virtual UInt						getDBAttrInitID();
		virtual UInt						getDBAttrLvlAddID();

    /// 属性计算相关 -- end
    ///----------------------------------------------------------------------------------------------

    public:
        void                                init(PlayerCharacterData* pData);
		void								unInit();

		U32				getExp();

	};
}

#endif