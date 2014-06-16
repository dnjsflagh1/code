/******************************************************************************/
#ifndef _CLUACHARACTERFORSKILL_H_
#define _CLUACHARACTERFORSKILL_H_
/******************************************************************************/

#include "CCharacterSceneEntity.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //�ͻ��˼��ܽ�ɫ����ű�����
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

            /** ֹͣ����
            LuaFunc:stopAll()    - return Void
            */
            REGISTER_METHOD(stopAll);

            /** �õ�λ��
            LuaFunc:getPos()    - return {x,y,z}
            */
            REGISTER_METHOD(getPos);

            /** �õ�����
            LuaFunc:getDir()    - return {x,y,z}
            */
            REGISTER_METHOD(getDir);

            /** �õ�����λ��
            LuaFunc:getBonePos()    - return {x,y,z}
            */
            REGISTER_METHOD(getBonePos);

            /** ���Ŷ���
            LuaFunc:playAnimation()    - return Void
            */
            REGISTER_METHOD(playAnimation);

            /** ֹͣ����
            LuaFunc:stopAnimation()    - return Void
            */
			REGISTER_METHOD(stopAnimation);

			///�����˺�
			REGISTER_METHOD(obtainDamage);

			///��������
			REGISTER_METHOD(getElementNum);

			///���ӵ�λ��λ��
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