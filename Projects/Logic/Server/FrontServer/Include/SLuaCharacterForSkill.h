/******************************************************************************/
#ifndef _SLUACHARACTERFORSKILL_H_
#define _SLUACHARACTERFORSKILL_H_
/******************************************************************************/

#include "SCharacter.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //客户端技能角色对象脚本对象
    /******************************************************************************/
    class SLuaCharacterForSkill : public CLuaBinder<SCharacter>
    { 
    public:

        SLuaCharacterForSkill(){};
        virtual ~SLuaCharacterForSkill(){};

        static Str LUA_TYPE_NAME;
		
        const Str& getLuaTypeName() const;

		static int getPos(lua_State *L);
		static int getDir(lua_State *L);
		static int obtainDamage(lua_State *L);
		//static int getElementNum(lua_State *L);
		static int summonBuilding(lua_State *L);


    protected:

        virtual void RegisterMethods()
        {

#define REGISTER_METHOD(methodname) mMethod.push_back(make_luaL_reg(#methodname,&SLuaCharacterForSkill::methodname));

            /** 得到位置
            LuaFunc:getPos()    - return {x,y,z}
            */
            REGISTER_METHOD(getPos);

            /** 得到方向
            LuaFunc:getDir()    - return {x,y,z}
            */
			REGISTER_METHOD(getDir);

			///计算伤害
			REGISTER_METHOD(obtainDamage);

			///军队人数
			//REGISTER_METHOD(getElementNum);

			//REGISTER_METHOD(setIsCtrl);

			REGISTER_METHOD(summonBuilding);


#undef REGISTER_METHOD
        }

    };

}

/******************************************************************************/

#endif