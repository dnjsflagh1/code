/******************************************************************************/
#ifndef _CLUACHARACTERFORSKILL_H_
#define _CLUACHARACTERFORSKILL_H_
/******************************************************************************/

#include "CCharacterSceneEntity.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //客户端技能角色对象脚本对象
    /******************************************************************************/
    class CLuaCharacterForSkill : public CLuaBinder<CCharacterSceneEntity>
    { 
    public:

        CLuaCharacterForSkill(){};
        virtual ~CLuaCharacterForSkill(){};

        static Str LUA_TYPE_NAME;
		
        const Str& getLuaTypeName() const;

        static int stopAll(lua_State *L);
        static int playAnimation(lua_State *L);
        static int stopAnimation(lua_State *L);
		static int getPos(lua_State *L);
		static int getDir(lua_State *L);
		static int getBonePos(lua_State *L);
		static int obtainDamage(lua_State *L);
		static int getElementNum(lua_State *L);
		static int getElementPos(lua_State *L);
		static int getElementDir(lua_State *L);
		static int setIsCtrl(lua_State *L);
		static int addEffect(lua_State *L);
		static int endEffect(lua_State *L);
		static int summonBuilding(lua_State *L);


    protected:

        virtual void RegisterMethods()
        {

#define REGISTER_METHOD(methodname) mMethod.push_back(make_luaL_reg(#methodname,&CLuaCharacterForSkill::methodname));

            /** 停止所有
            LuaFunc:stopAll()    - return Void
            */
            REGISTER_METHOD(stopAll);

            /** 得到位置
            LuaFunc:getPos()    - return {x,y,z}
            */
            REGISTER_METHOD(getPos);

            /** 得到方向
            LuaFunc:getDir()    - return {x,y,z}
            */
            REGISTER_METHOD(getDir);

            /** 得到骨骼位置
            LuaFunc:getBonePos()    - return {x,y,z}
            */
            REGISTER_METHOD(getBonePos);

            /** 播放动画
            LuaFunc:playAnimation()    - return Void
            */
            REGISTER_METHOD(playAnimation);

            /** 停止动画
            LuaFunc:stopAnimation()    - return Void
            */
			REGISTER_METHOD(stopAnimation);

			///计算伤害
			REGISTER_METHOD(obtainDamage);

			///军队人数
			REGISTER_METHOD(getElementNum);

			///军队单位的位置
			REGISTER_METHOD(getElementPos);

			REGISTER_METHOD(getElementDir);

			REGISTER_METHOD(setIsCtrl);

			REGISTER_METHOD(addEffect);

			REGISTER_METHOD(endEffect);

			REGISTER_METHOD(summonBuilding);


#undef REGISTER_METHOD
        }

    };

}

/******************************************************************************/

#endif