/******************************************************************************/
#ifndef _CLUASKILLOBJECT_H_
#define _CLUASKILLOBJECT_H_
/******************************************************************************/


/******************************************************************************/


namespace MG
{
	/******************************************************************************/
	//�ͻ��˼��ܶ���ű�����
	/******************************************************************************/
	class CLuaSkillObject : public CLuaBinder<CSkillObject>
	{ 
	public:

		CLuaSkillObject(){};
		virtual ~CLuaSkillObject(){};

		static Str LUA_TYPE_NAME;

		static int getOwner(lua_State *L);
		static int getTargetPos(lua_State *L);
		static int getTargetIndex(lua_State *L);
		static int getTargetId(lua_State *L);
		static int getTargetType(lua_State *L);
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

#define REGISTER_METHOD(methodname) mMethod.push_back(make_luaL_reg(#methodname,&CLuaSkillObject::methodname));

            /** �õ�ӵ����
            LuaFunc:getOwner()    - return Character
            */
            REGISTER_METHOD(getOwner);

            /** ���ӵ���Ч
            LuaFunc:addPointEffect()    - return PointSkillEffect
            */
            REGISTER_METHOD(addPointEffect);

            /** ����ֱ�߷�����Ч
            LuaFunc:addEmitterSkillEffectt()    - return LineFlySkillEffect
            */
            REGISTER_METHOD(addEmitterSkillEffect);

			/** ����Ŀ�������Ч
			LuaFunc:addObjectSkillEffect()    - return ObjectSkillEffect
			*/
			REGISTER_METHOD(addObjectSkillEffect);

			/** ����˲����Ч
			LuaFunc:addInstantSkillEffect()    - return InstantSkillEffect
			*/
			REGISTER_METHOD(addInstantSkillEffect);

			/** ���˲����Ч
			LuaFunc:addSprintSkillEffect()    - return SprintSkillEffect
			*/
			REGISTER_METHOD(addSprintSkillEffect);

			///��ü���Ŀ������
			REGISTER_METHOD(getTargetPos);

			REGISTER_METHOD(getTargetIndex);
			///��ü���Ŀ��
			REGISTER_METHOD(getTargetId);

			///��ü���Ŀ������
			REGISTER_METHOD(getTargetType);

			REGISTER_METHOD(skillEnded);

			REGISTER_METHOD(getSkillId);


#undef REGISTER_METHOD
		}

	};

}

/******************************************************************************/
#endif

