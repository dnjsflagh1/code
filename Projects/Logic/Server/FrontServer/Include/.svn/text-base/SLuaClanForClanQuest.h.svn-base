/******************************************************************************/
#ifndef _SLUACLANFORCLANQUEST_H_
#define _SLUACLANFORCLANQUEST_H_
/******************************************************************************/
#include "SClan.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //服务器家族任务 家族脚本对象
    /******************************************************************************/
    class SLuaClanForClanQuest : public CLuaBinder<SClan>
    { 
    public:
        SLuaClanForClanQuest(){};
        virtual ~SLuaClanForClanQuest(){};

        static Str LUA_TYPE_NAME;
        const Str& getLuaTypeName() const;


    protected:

        virtual void RegisterMethods()
        {
#define REGISTER_METHOD(methodname) mMethod.push_back(make_luaL_reg(#methodname,&SLuaClanForClanQuest::methodname));

#undef REGISTER_METHOD
        }

    };

}

/******************************************************************************/

#endif