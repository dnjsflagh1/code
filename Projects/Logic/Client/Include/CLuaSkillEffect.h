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
    //技能特效
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

            /** 开始
            LuaFunc:start( )    - return Nil
            */
            REGISTER_METHOD(start);

            /** 结束
            LuaFunc:end( )    - return Nil
            */
            REGISTER_METHOD(finish);


#undef REGISTER_METHOD
        }
    };

    /******************************************************************************/
    //点技能特效
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

            /** 开始
            LuaFunc:start( )    - return Nil
            */
            REGISTER_METHOD(start);

            /** 结束
            LuaFunc:end( )    - return Nil
            */
            REGISTER_METHOD(finish);

            /** 设置特效
            LuaFunc:setEffect( name )    - return Nil
            */
            REGISTER_METHOD(setEffect);

            /** 设置位置
            LuaFunc:setPos( pos )    - return Nil
            */
            REGISTER_METHOD(setPos);

			/** 设置高度
			LuaFunc:setHight( hight )    - return Nil
			*/
			//REGISTER_METHOD(setHight);

			REGISTER_METHOD(setAttackNum);
			//设置特效播放时间
			REGISTER_METHOD(setAffectNum);
			//设置特效半径
			REGISTER_METHOD(setRadius);

			REGISTER_METHOD(setAffectIntervalTime);

			REGISTER_METHOD(setStartPos);

			REGISTER_METHOD(setFlyEffectId);

			REGISTER_METHOD(setMoveSpeed);

#undef REGISTER_METHOD
        }
    };

    
    /******************************************************************************/
    //飞行技能特效
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

            /** 开始
            LuaFunc:start( )    - return Nil
            */
            REGISTER_METHOD(start);

            /** 结束
            LuaFunc:end( )    - return Nil
            */
            REGISTER_METHOD(finish);


            /** 设置特效
            LuaFunc:setEffect( name )    - return Nil
            */
            REGISTER_METHOD(setEffect);

            /** 设置位置
            LuaFunc:setStartPos( pos )    - return Nil
            */
            REGISTER_METHOD(setStartPos);

            /** 设置方向
            LuaFunc:setStartDir( dir )    - return Nil
            */
            REGISTER_METHOD(setStartDir);

            /** 设置距离
            LuaFunc:setDistance( dis )    - return Nil
            */
            REGISTER_METHOD(setDistance);

			//设置发射体数量
			REGISTER_METHOD(setEmitterNum);

			//设置目标位置
			REGISTER_METHOD(setTargetPos);

			//设置发射类型
			REGISTER_METHOD(setEmitType);

			//设置飞行轨迹
			REGISTER_METHOD(setFlyTrackType);

			//设置是否穿刺
			REGISTER_METHOD(setIsPuncture);

			REGISTER_METHOD(setIsParabola);

			REGISTER_METHOD(setMoveSpeed);

			REGISTER_METHOD(setScatterAngle);

#undef REGISTER_METHOD
        }
    };

	/******************************************************************************/
	//目标技能特效
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

			/** 开始
			LuaFunc:start( )    - return Nil
			*/
			REGISTER_METHOD(start);

			/** 结束
			LuaFunc:end( )    - return Nil
			*/
			REGISTER_METHOD(finish);


			/** 设置特效
			LuaFunc:setEffect( name )    - return Nil
			*/
			REGISTER_METHOD(setEffect);

			/** 设置位置
			LuaFunc:setStartPos( pos )    - return Nil
			*/
			REGISTER_METHOD(setStartPos);

			/** 设置方向
			LuaFunc:setStartDir( dir )    - return Nil
			*/
			REGISTER_METHOD(setDistance);

			REGISTER_METHOD(setTargetIndex);

			///设置目标
			REGISTER_METHOD(setTargetId);

			///设置目标类型
			REGISTER_METHOD(setTargetType);

			REGISTER_METHOD(setIsParabola);

			REGISTER_METHOD(setMoveSpeed);


#undef REGISTER_METHOD
		}
	};

	/******************************************************************************/
	//瞬间技能特效
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

			/** 开始
			LuaFunc:start( )    - return Nil
			*/
			REGISTER_METHOD(start);

			/** 结束
			LuaFunc:end( )    - return Nil
			*/
			REGISTER_METHOD(finish);


			/** 设置特效
			LuaFunc:setEffect( name )    - return Nil
			*/
			REGISTER_METHOD(setEffect);

			/** 设置位置
			LuaFunc:setStartPos( pos )    - return Nil
			*/
			REGISTER_METHOD(setPos);

			///特效播放时间
			REGISTER_METHOD(setPlayTotalTime);

			REGISTER_METHOD(setTargetIndex);
			///设置目标
			REGISTER_METHOD(setTargetId);

			///设置目标类型
			REGISTER_METHOD(setTargetType);



#undef REGISTER_METHOD
		}
	};

	/******************************************************************************/
	//冲刺技能特效
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

			/** 开始
			LuaFunc:start( )    - return Nil
			*/
			REGISTER_METHOD(start);

			/** 结束
			LuaFunc:end( )    - return Nil
			*/
			REGISTER_METHOD(finish);


			/** 设置特效
			LuaFunc:setEffect( name )    - return Nil
			*/
			REGISTER_METHOD(setEffect);

			/** 设置位置
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

