/******************************************************************************/
#ifndef _LUASKILLOBJECT_H_
#define _LUASKILLOBJECT_H_
/******************************************************************************/

#include "WorldCorePreqs.h"

/******************************************************************************/


namespace MG
{
	/******************************************************************************/
	//客户端技能对象脚本对象
	/******************************************************************************/
	class LuaSkillObject : public CLuaBinder<SkillObject>
	{ 
	public:

		LuaSkillObject(){};
		virtual ~LuaSkillObject(){};

		static Str LUA_TYPE_NAME;

		static int getOwner(lua_State *L);
		static int getTargetPos(lua_State *L);
		static int getTargetId(lua_State *L);
		static int getTargetType(lua_State *L);
		static int getSkillLevel(lua_State *L);
        static int addPointEffect(lua_State *L);
        static int addEmitterSkillEffect(lua_State *L);
		static int addObjectSkillEffect(lua_State *L);
		static int addInstantSkillEffect(lua_State *L);
		static int addSprintSkillEffect(lua_State *L);
		static int skillEnded(lua_State *L);
		static int getSkillId(lua_State *L);

		const Str& getLuaTypeName() const;

	protected:
		
		virtual void RegisterMethods()
		{

#define REGISTER_METHOD(methodname) mMethod.push_back(make_luaL_reg(#methodname,&LuaSkillObject::methodname));

            /** 得到拥有者
            LuaFunc:getOwner()    - return Character
            */
            REGISTER_METHOD(getOwner);

            /** 增加点特效
            LuaFunc:addPointEffect()    - return PointSkillEffect
            */
            REGISTER_METHOD(addPointEffect);

            /** 增加直线飞行特效
            LuaFunc:addEmitterSkillEffectt()    - return LineFlySkillEffect
            */
            REGISTER_METHOD(addEmitterSkillEffect);

			/** 增加目标飞行特效
			LuaFunc:addObjectSkillEffect()    - return ObjectSkillEffect
			*/
			REGISTER_METHOD(addObjectSkillEffect);

			/** 增加瞬间特效
			LuaFunc:addInstantSkillEffect()    - return InstantSkillEffect
			*/
			REGISTER_METHOD(addInstantSkillEffect);

			/** 冲刺瞬间特效
			LuaFunc:addSprintSkillEffect()    - return SprintSkillEffect
			*/
			REGISTER_METHOD(addSprintSkillEffect);

			///获得技能目标坐标
			REGISTER_METHOD(getTargetPos);

			///获得技能目标
			REGISTER_METHOD(getTargetId);

			///获得技能目标类型
			REGISTER_METHOD(getTargetType);
			
			///获得技能等级
			REGISTER_METHOD(getSkillLevel);

			REGISTER_METHOD(skillEnded);

			REGISTER_METHOD(getSkillId);


#undef REGISTER_METHOD
		}




	};

}

/******************************************************************************/
#endif

