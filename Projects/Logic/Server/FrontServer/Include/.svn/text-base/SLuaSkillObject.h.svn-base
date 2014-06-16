/******************************************************************************/
#ifndef _SLUASKILLOBJECT_H_
#define _SLUASKILLOBJECT_H_
/******************************************************************************/

#include "SkillObject.h"

/******************************************************************************/


namespace MG
{
	/******************************************************************************/
	//客户端技能对象脚本对象
	/******************************************************************************/
	class SLuaSkillObject : public CLuaBinder<SkillObject>
	{ 
	public:

		SLuaSkillObject(){};
		virtual ~SLuaSkillObject(){};

		static Str LUA_TYPE_NAME;

		static int getOwner(lua_State *L);
		static int getTargetPos(lua_State *L);
		static int getTargetId(lua_State *L);
		static int getTargetType(lua_State *L);
		static int skillEnded(lua_State *L);
		static int getSkillId(lua_State *L);

		const Str& getLuaTypeName() const;

	protected:
		
		virtual void RegisterMethods()
		{

#define REGISTER_METHOD(methodname) mMethod.push_back(make_luaL_reg(#methodname,&SLuaSkillObject::methodname));

            /** 得到拥有者
            LuaFunc:getOwner()    - return Character
            */
            REGISTER_METHOD(getOwner);

			///获得技能目标坐标
			REGISTER_METHOD(getTargetPos);

			///获得技能目标
			REGISTER_METHOD(getTargetId);

			///获得技能目标类型
			REGISTER_METHOD(getTargetType);

			REGISTER_METHOD(skillEnded);

			REGISTER_METHOD(getSkillId);


#undef REGISTER_METHOD
		}




	};

}

/******************************************************************************/
#endif

