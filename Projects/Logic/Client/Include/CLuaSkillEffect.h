/******************************************************************************/
#ifndef _CLUASKILLEFFECT_H_
#define _CLUASKILLEFFECT_H_
/******************************************************************************/

#include "CSkillEffectSystem.h"
#include "CPointSkillEffect.h"
#include "CObjectSkillEffect.h"
#include "CInstantSkillEffect.h"
#include "CEmitterSkillEffect.h"
#include "CSprintSkillEffect.h"

/******************************************************************************/


namespace MG
{
    /******************************************************************************/
    //������Ч
    /******************************************************************************/
    class CLuaSkillEffect : public CLuaBinder<CSkillEffect>
    { 
    public:
        CLuaSkillEffect(){};
        virtual ~CLuaSkillEffect(){};

        static Str LUA_TYPE_NAME;
        const Str& getLuaTypeName() const;

        static int start(lua_State *L);
        static int finish(lua_State *L);

    protected:

        virtual void RegisterMethods()
        {

#define REGISTER_METHOD(methodname) mMethod.push_back(make_luaL_reg(#methodname,&CLuaSkillEffect::methodname));

            /** ��ʼ
            LuaFunc:start( )    - return Nil
            */
            REGISTER_METHOD(start);

            /** ����
            LuaFunc:end( )    - return Nil
            */
            REGISTER_METHOD(finish);


#undef REGISTER_METHOD
        }
    };

    /******************************************************************************/
    //�㼼����Ч
    /******************************************************************************/
    class CLuaPointSkillEffect : public CLuaBinder< CPointSkillEffect>
    { 
    public:
        CLuaPointSkillEffect(){};
        virtual ~CLuaPointSkillEffect(){};

        static Str LUA_TYPE_NAME;
        const Str& getLuaTypeName() const;

        static int start(lua_State *L);
        static int finish(lua_State *L);
        static int setEffect(lua_State *L);
        static int setPos(lua_State *L);
		//static int setHight(lua_State *L);
		static int setAffectNum(lua_State *L);
		static int setAttackNum(lua_State *L);
		static int setRadius(lua_State *L);
		static int setAffectIntervalTime(lua_State *L);
		static int setStartPos(lua_State *L);
		static int setFlyEffectId(lua_State *L);
		static int setMoveSpeed(lua_State *L);

    protected:

        virtual void RegisterMethods()
        {

#define REGISTER_METHOD(methodname) mMethod.push_back(make_luaL_reg(#methodname,&CLuaPointSkillEffect::methodname));

            /** ��ʼ
            LuaFunc:start( )    - return Nil
            */
            REGISTER_METHOD(start);

            /** ����
            LuaFunc:end( )    - return Nil
            */
            REGISTER_METHOD(finish);

            /** ������Ч
            LuaFunc:setEffect( name )    - return Nil
            */
            REGISTER_METHOD(setEffect);

            /** ����λ��
            LuaFunc:setPos( pos )    - return Nil
            */
            REGISTER_METHOD(setPos);

			/** ���ø߶�
			LuaFunc:setHight( hight )    - return Nil
			*/
			//REGISTER_METHOD(setHight);

			REGISTER_METHOD(setAttackNum);
			//������Ч����ʱ��
			REGISTER_METHOD(setAffectNum);
			//������Ч�뾶
			REGISTER_METHOD(setRadius);

			REGISTER_METHOD(setAffectIntervalTime);

			REGISTER_METHOD(setStartPos);

			REGISTER_METHOD(setFlyEffectId);

			REGISTER_METHOD(setMoveSpeed);

#undef REGISTER_METHOD
        }
    };

    
    /******************************************************************************/
    //���м�����Ч
    /******************************************************************************/
    class CLuaEmitterSkillEffect : public CLuaBinder<CEmitterSkillEffect>
    { 
    public:
        CLuaEmitterSkillEffect(){};
        virtual ~CLuaEmitterSkillEffect(){};

        static Str LUA_TYPE_NAME;
        const Str& getLuaTypeName() const;

        static int start(lua_State *L);
        static int finish(lua_State *L);
        static int setEffect(lua_State *L);
        static int setStartPos(lua_State *L);
        static int setStartDir(lua_State *L);
        static int setDistance(lua_State *L);
		static int setEmitterNum(lua_State *L);
		static int setTargetPos(lua_State *L);
		static int setEmitType(lua_State *L);
		static int setFlyTrackType(lua_State *L);
		static int setIsPuncture(lua_State *L);
		static int setIsParabola(lua_State *L);
		static int setMoveSpeed(lua_State *L); 
		static int setScatterAngle(lua_State *L);

    protected:

        virtual void RegisterMethods()
        {

#define REGISTER_METHOD(methodname) mMethod.push_back(make_luaL_reg(#methodname,&CLuaEmitterSkillEffect::methodname));

            /** ��ʼ
            LuaFunc:start( )    - return Nil
            */
            REGISTER_METHOD(start);

            /** ����
            LuaFunc:end( )    - return Nil
            */
            REGISTER_METHOD(finish);


            /** ������Ч
            LuaFunc:setEffect( name )    - return Nil
            */
            REGISTER_METHOD(setEffect);

            /** ����λ��
            LuaFunc:setStartPos( pos )    - return Nil
            */
            REGISTER_METHOD(setStartPos);

            /** ���÷���
            LuaFunc:setStartDir( dir )    - return Nil
            */
            REGISTER_METHOD(setStartDir);

            /** ���þ���
            LuaFunc:setDistance( dis )    - return Nil
            */
            REGISTER_METHOD(setDistance);

			//���÷���������
			REGISTER_METHOD(setEmitterNum);

			//����Ŀ��λ��
			REGISTER_METHOD(setTargetPos);

			//���÷�������
			REGISTER_METHOD(setEmitType);

			//���÷��й켣
			REGISTER_METHOD(setFlyTrackType);

			//�����Ƿ񴩴�
			REGISTER_METHOD(setIsPuncture);

			REGISTER_METHOD(setIsParabola);

			REGISTER_METHOD(setMoveSpeed);

			REGISTER_METHOD(setScatterAngle);

#undef REGISTER_METHOD
        }
    };

	/******************************************************************************/
	//Ŀ�꼼����Ч
	/******************************************************************************/
	class CLuaObjectSkillEffect : public CLuaBinder<CObjectSkillEffect>
	{ 
	public:
		CLuaObjectSkillEffect(){};
		virtual ~CLuaObjectSkillEffect(){};

		static Str LUA_TYPE_NAME;
		const Str& getLuaTypeName() const;

		static int start(lua_State *L);
		static int finish(lua_State *L);
		static int setEffect(lua_State *L);
		static int setStartPos(lua_State *L);
		static int setDistance(lua_State *L);
		static int setTargetIndex(lua_State *L);
		static int setTargetId(lua_State *L);
		static int setTargetType(lua_State *L);
		static int setIsParabola(lua_State *L);
		static int setMoveSpeed(lua_State *L); 

	protected:

		virtual void RegisterMethods()
		{

#define REGISTER_METHOD(methodname) mMethod.push_back(make_luaL_reg(#methodname,&CLuaObjectSkillEffect::methodname));

			/** ��ʼ
			LuaFunc:start( )    - return Nil
			*/
			REGISTER_METHOD(start);

			/** ����
			LuaFunc:end( )    - return Nil
			*/
			REGISTER_METHOD(finish);


			/** ������Ч
			LuaFunc:setEffect( name )    - return Nil
			*/
			REGISTER_METHOD(setEffect);

			/** ����λ��
			LuaFunc:setStartPos( pos )    - return Nil
			*/
			REGISTER_METHOD(setStartPos);

			/** ���÷���
			LuaFunc:setStartDir( dir )    - return Nil
			*/
			REGISTER_METHOD(setDistance);

			REGISTER_METHOD(setTargetIndex);

			///����Ŀ��
			REGISTER_METHOD(setTargetId);

			///����Ŀ������
			REGISTER_METHOD(setTargetType);

			REGISTER_METHOD(setIsParabola);

			REGISTER_METHOD(setMoveSpeed);


#undef REGISTER_METHOD
		}
	};

	/******************************************************************************/
	//˲�似����Ч
	/******************************************************************************/
	class CLuaInstantSkillEffect : public CLuaBinder<CInstantSkillEffect>
	{ 
	public:
		CLuaInstantSkillEffect(){};
		virtual ~CLuaInstantSkillEffect(){};

		static Str LUA_TYPE_NAME;
		const Str& getLuaTypeName() const;

		static int start(lua_State *L);
		static int finish(lua_State *L);
		static int setEffect(lua_State *L);
		static int setPos(lua_State *L);
		static int setPlayTotalTime(lua_State *L);
		static int setTargetIndex(lua_State *L);
		static int setTargetId(lua_State *L);
		static int setTargetType(lua_State *L);

	protected:

		virtual void RegisterMethods()
		{

#define REGISTER_METHOD(methodname) mMethod.push_back(make_luaL_reg(#methodname,&CLuaInstantSkillEffect::methodname));

			/** ��ʼ
			LuaFunc:start( )    - return Nil
			*/
			REGISTER_METHOD(start);

			/** ����
			LuaFunc:end( )    - return Nil
			*/
			REGISTER_METHOD(finish);


			/** ������Ч
			LuaFunc:setEffect( name )    - return Nil
			*/
			REGISTER_METHOD(setEffect);

			/** ����λ��
			LuaFunc:setStartPos( pos )    - return Nil
			*/
			REGISTER_METHOD(setPos);

			///��Ч����ʱ��
			REGISTER_METHOD(setPlayTotalTime);

			REGISTER_METHOD(setTargetIndex);
			///����Ŀ��
			REGISTER_METHOD(setTargetId);

			///����Ŀ������
			REGISTER_METHOD(setTargetType);



#undef REGISTER_METHOD
		}
	};

	/******************************************************************************/
	//��̼�����Ч
	/******************************************************************************/
	class CLuaSprintSkillEffect : public CLuaBinder<CSprintSkillEffect>
	{ 
	public:
		CLuaSprintSkillEffect(){};
		virtual ~CLuaSprintSkillEffect(){};

		static Str LUA_TYPE_NAME;
		const Str& getLuaTypeName() const;

		static int start(lua_State *L);
		static int finish(lua_State *L);
		static int setEffect(lua_State *L);
		static int setPos(lua_State *L);
		static int setDistance(lua_State *L);

	protected:

		virtual void RegisterMethods()
		{

#define REGISTER_METHOD(methodname) mMethod.push_back(make_luaL_reg(#methodname,&CLuaSprintSkillEffect::methodname));

			/** ��ʼ
			LuaFunc:start( )    - return Nil
			*/
			REGISTER_METHOD(start);

			/** ����
			LuaFunc:end( )    - return Nil
			*/
			REGISTER_METHOD(finish);


			/** ������Ч
			LuaFunc:setEffect( name )    - return Nil
			*/
			REGISTER_METHOD(setEffect);

			/** ����λ��
			LuaFunc:setStartPos( pos )    - return Nil
			*/
			REGISTER_METHOD(setPos);

			REGISTER_METHOD(setDistance);



#undef REGISTER_METHOD
		}
	};

}

/******************************************************************************/
#endif

