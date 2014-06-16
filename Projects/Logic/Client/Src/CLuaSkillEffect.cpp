
/******************************************************************************/
#include "stdafx.h"
#include "CLuaSkillEffect.h"
//#include "Character.h"
#include "CSkillObject.h"
#include "CLuaSkillSystem.h"
#include "CLuaCharacterForSkill.h"
#include "CPointSkillEffect.h"
#include "CEmitterSkillEffect.h"
#include "CObjectSkillEffect.h"
#include "CInstantSkillEffect.h"
#include "CSprintSkillEffect.h"
/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //技能特效
    /******************************************************************************/
    Str CLuaSkillEffect::LUA_TYPE_NAME = "CLuaSkillEffect"; 

    //-----------------------------------------------------------------------

    const Str& CLuaSkillEffect::getLuaTypeName() const 
    {
        return CLuaSkillEffect::LUA_TYPE_NAME;
    }

    //-----------------------------------------------------------------------
    int CLuaSkillEffect::start(lua_State *L)
    {
        CSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CSkillEffect,CLuaSkillEffect,L); 
        if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

        effectObject->start();

        return 0;
    }

    //-----------------------------------------------------------------------
    int CLuaSkillEffect::finish(lua_State *L)
    {
        CSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CSkillEffect,CLuaSkillEffect,L); 
        if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

        effectObject->end();

        return 0;
    }

    /******************************************************************************/
    //点技能特效
    /******************************************************************************/
    //-----------------------------------------------------------------------

    Str CLuaPointSkillEffect::LUA_TYPE_NAME = "CLuaPointSkillEffect"; 

    //-----------------------------------------------------------------------

    const Str& CLuaPointSkillEffect::getLuaTypeName() const 
    {
        return CLuaPointSkillEffect::LUA_TYPE_NAME;
    }

    //-----------------------------------------------------------------------
    int CLuaPointSkillEffect::start(lua_State *L)
    {
         CPointSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT( CPointSkillEffect,CLuaPointSkillEffect,L); 
        if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

        effectObject->start();

        return 0;
    }

    //-----------------------------------------------------------------------
    int CLuaPointSkillEffect::finish(lua_State *L)
    {
         CPointSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT( CPointSkillEffect,CLuaPointSkillEffect,L); 
        if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

        effectObject->end();

        return 0;
    }

    //-----------------------------------------------------------------------
    int CLuaPointSkillEffect::setEffect(lua_State *L)
    {
         CPointSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT( CPointSkillEffect,CLuaPointSkillEffect,L); 
        if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

        UInt id    = CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
        effectObject->setEffect( id );

        return 0;
    }

    //-----------------------------------------------------------------------
    int CLuaPointSkillEffect::setPos(lua_State *L)
    {
         CPointSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT( CPointSkillEffect,CLuaPointSkillEffect,L); 
        if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

        Vec3 pos    = CLuaSkillSystem::getInstance().getLuaManager()->getVector3FromTable(2);
        effectObject->setPos( pos );

        return 0;
    }
	//-----------------------------------------------------------------------
	//int CLuaPointSkillEffect::setHight(lua_State *L)
	//{
	//	 CPointSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT( CPointSkillEffect,CLuaPointSkillEffect,L); 
	//	if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

	//	UInt hight    = CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
	//	effectObject->setHight( hight );

	//	return 0;
	//}
	//-----------------------------------------------------------------------
	int CLuaPointSkillEffect::setAffectNum(lua_State *L)
	{
		 CPointSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT( CPointSkillEffect,CLuaPointSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		UInt num = (Flt)CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
		effectObject->setAffectNum( num );

		return 0;
	}
	//-----------------------------------------------------------------------
	int CLuaPointSkillEffect::setRadius(lua_State *L)
	{
		 CPointSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT( CPointSkillEffect,CLuaPointSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		UInt radius = CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
		effectObject->setRadius( radius );

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaPointSkillEffect::setAttackNum(lua_State *L)
	{
		CPointSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT( CPointSkillEffect,CLuaPointSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		UInt radius = CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
		effectObject->setAttackNum( radius );

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaPointSkillEffect::setAffectIntervalTime(lua_State *L)
	{
		 CPointSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT( CPointSkillEffect,CLuaPointSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		Flt intervalTime = CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
		effectObject->setAffectIntervalTime( intervalTime );

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaPointSkillEffect::setStartPos(lua_State *L)
	{
		CPointSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT( CPointSkillEffect,CLuaPointSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		Vec3 pos    = CLuaSkillSystem::getInstance().getLuaManager()->getVector3FromTable(2);
		effectObject->setStartPos( pos );

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaPointSkillEffect::setFlyEffectId(lua_State *L)
	{
		CPointSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT( CPointSkillEffect,CLuaPointSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		UInt flyEffectID = CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
		effectObject->setFlyEffectId( flyEffectID );

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaPointSkillEffect::setMoveSpeed(lua_State *L)
	{
		CPointSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT( CPointSkillEffect,CLuaPointSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		Flt moveSpeed = CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
		effectObject->setMoveSpeed( moveSpeed );

		return 0;
	}

    /******************************************************************************/
    //直线飞行技能特效
    /******************************************************************************/
    Str CLuaEmitterSkillEffect::LUA_TYPE_NAME = "CLuaEmitterSkillEffect"; 

    //-----------------------------------------------------------------------

    const Str& CLuaEmitterSkillEffect::getLuaTypeName() const 
    {
        return CLuaEmitterSkillEffect::LUA_TYPE_NAME;
    }

    //-----------------------------------------------------------------------
    int CLuaEmitterSkillEffect::start(lua_State *L)
    {
        CEmitterSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CEmitterSkillEffect,CLuaEmitterSkillEffect,L); 
        if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

        effectObject->start();

        return 0;
    }

    //-----------------------------------------------------------------------
    int CLuaEmitterSkillEffect::finish(lua_State *L)
    {
        CEmitterSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CEmitterSkillEffect,CLuaEmitterSkillEffect,L); 
        if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

        effectObject->end();

        return 0;
    }

    //-----------------------------------------------------------------------
    int CLuaEmitterSkillEffect::setEffect(lua_State *L)
    {
        CEmitterSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CEmitterSkillEffect,CLuaEmitterSkillEffect,L); 
        if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		UInt id    = CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
		effectObject->setEffect( id );

        return 0;
    }

    //-----------------------------------------------------------------------
    int CLuaEmitterSkillEffect::setStartPos(lua_State *L)
    {
        CEmitterSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CEmitterSkillEffect,CLuaEmitterSkillEffect,L); 
        if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

        Vec3 pos    = CLuaSkillSystem::getInstance().getLuaManager()->getVector3FromTable(2);
        effectObject->setStartPos( pos );

		MG_LOG( out_error, MG_STR("jjj_hero shoot at (%f,%f,%f)\n"), pos.x, pos.y, pos.z);

        return 0;
    }

    //-----------------------------------------------------------------------
    int CLuaEmitterSkillEffect::setStartDir(lua_State *L)
    {
        CEmitterSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CEmitterSkillEffect,CLuaEmitterSkillEffect,L); 
        if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

        Vec3 dir    = CLuaSkillSystem::getInstance().getLuaManager()->getVector3FromTable(2);
        effectObject->setStartDir( dir );

        return 0;
    }

    //-----------------------------------------------------------------------
    int CLuaEmitterSkillEffect::setDistance(lua_State *L)
    {
        CEmitterSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CEmitterSkillEffect,CLuaEmitterSkillEffect,L); 
        if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

        Int dis    = CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
        effectObject->setDistance( Flt(dis) );

        return 0;
    }
	//-----------------------------------------------------------------------
	int CLuaEmitterSkillEffect::setEmitterNum(lua_State *L)
	{
		CEmitterSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CEmitterSkillEffect,CLuaEmitterSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		Int num    = CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
		effectObject->setEmitterNum( num );

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaEmitterSkillEffect::setTargetPos(lua_State *L)
	{
		CEmitterSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CEmitterSkillEffect,CLuaEmitterSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }
		Vec3 targetPos = CLuaSkillSystem::getInstance().getLuaManager()->getVector3FromTable(2);
		effectObject->setTargetPos( targetPos );

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaEmitterSkillEffect::setEmitType(lua_State *L)
	{
		CEmitterSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CEmitterSkillEffect,CLuaEmitterSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }
		Int type = CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
		effectObject->setEmitType( (CEmitterSkillEffect::EmitType)type );

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaEmitterSkillEffect::setFlyTrackType(lua_State *L)
	{
		CEmitterSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CEmitterSkillEffect,CLuaEmitterSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }
		Int type = CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
		effectObject->setFlyTrackType( (CEmitterSkillEffect::FlyTrackType)type );

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaEmitterSkillEffect::setIsPuncture(lua_State *L)
	{
		CEmitterSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CEmitterSkillEffect,CLuaEmitterSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }
		Bool isPuncture = CLuaSkillSystem::getInstance().getLuaManager()->getBoolean(2);
		effectObject->setIsPuncture( isPuncture );

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaEmitterSkillEffect::setIsParabola(lua_State *L)
	{
		CEmitterSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CEmitterSkillEffect,CLuaEmitterSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }
		Bool isParabola = CLuaSkillSystem::getInstance().getLuaManager()->getBoolean(2);
		effectObject->setIsParabola(isParabola);

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaEmitterSkillEffect::setMoveSpeed(lua_State *L)
	{
		CEmitterSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CEmitterSkillEffect,CLuaEmitterSkillEffect,L); 
		Flt speed = CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
		effectObject->setMoveSpeed(speed);

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaEmitterSkillEffect::setScatterAngle(lua_State *L)
	{
		CEmitterSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CEmitterSkillEffect,CLuaEmitterSkillEffect,L); 
		Flt angle = CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
		effectObject->setScatterAngle(angle);

		return 0;
	}

	/******************************************************************************/
	//目标技能特效
	/******************************************************************************/
	Str CLuaObjectSkillEffect::LUA_TYPE_NAME = "CLuaObjectSkillEffect"; 

	//-----------------------------------------------------------------------

	const Str& CLuaObjectSkillEffect::getLuaTypeName() const 
	{
		return CLuaObjectSkillEffect::LUA_TYPE_NAME;
	}

	//-----------------------------------------------------------------------
	int CLuaObjectSkillEffect::start(lua_State *L)
	{
		CObjectSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CObjectSkillEffect,CLuaObjectSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		effectObject->start();

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaObjectSkillEffect::finish(lua_State *L)
	{
		CObjectSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CObjectSkillEffect,CLuaObjectSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		effectObject->end();

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaObjectSkillEffect::setEffect(lua_State *L)
	{
		CObjectSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CObjectSkillEffect,CLuaObjectSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		UInt id    = CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
		effectObject->setEffect( id );

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaObjectSkillEffect::setStartPos(lua_State *L)
	{
		CObjectSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CObjectSkillEffect,CLuaObjectSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		Vec3 pos    = CLuaSkillSystem::getInstance().getLuaManager()->getVector3FromTable(2);
		effectObject->setStartPos( pos );

		//MG_LOG( out_error, MG_STR("jjj_hero shoot at (%f,%f,%f)\n"), pos.x, pos.y, pos.z);

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaObjectSkillEffect::setDistance(lua_State *L)
	{
		CObjectSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CObjectSkillEffect,CLuaObjectSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		Int dis = CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
		effectObject->setDistance( Flt(dis) );

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaObjectSkillEffect::setTargetIndex(lua_State *L)
	{
		CObjectSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CObjectSkillEffect,CLuaObjectSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		UInt index = CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
		effectObject->setTargetIndex(index);

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaObjectSkillEffect::setTargetId(lua_State *L)
	{
		CObjectSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CObjectSkillEffect,CLuaObjectSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		IdType id = CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
		effectObject->setTargetID(id);

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaObjectSkillEffect::setTargetType(lua_State *L)
	{
		CObjectSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CObjectSkillEffect,CLuaObjectSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		GAMEOBJ_TYPE type = (GAMEOBJ_TYPE)CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
		effectObject->setTargetType(type);

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaObjectSkillEffect::setIsParabola(lua_State *L)
	{
		CObjectSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CObjectSkillEffect,CLuaObjectSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		Bool isParabola = CLuaSkillSystem::getInstance().getLuaManager()->getBoolean(2);
		//effectObject->setIsParabola(isParabola);

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaObjectSkillEffect::setMoveSpeed(lua_State *L)
	{
		CObjectSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CObjectSkillEffect,CLuaObjectSkillEffect,L); 
		Flt speed = CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
		effectObject->setMoveSpeed(speed);

		return 0;
	}

	//-----------------------------------------------------------------------


	/******************************************************************************/
	//瞬间技能特效
	/******************************************************************************/
	Str CLuaInstantSkillEffect::LUA_TYPE_NAME = "CLuaInstantSkillEffect"; 

	//-----------------------------------------------------------------------

	const Str& CLuaInstantSkillEffect::getLuaTypeName() const 
	{
		return CLuaInstantSkillEffect::LUA_TYPE_NAME;
	}

	//-----------------------------------------------------------------------
	int CLuaInstantSkillEffect::start(lua_State *L)
	{
		CInstantSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CInstantSkillEffect,CLuaInstantSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		effectObject->start();

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaInstantSkillEffect::finish(lua_State *L)
	{
		CInstantSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CInstantSkillEffect,CLuaInstantSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		effectObject->end();

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaInstantSkillEffect::setEffect(lua_State *L)
	{
		CInstantSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CInstantSkillEffect,CLuaInstantSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		UInt id    = CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
		effectObject->setEffect( id );

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaInstantSkillEffect::setPos(lua_State *L)
	{
		CInstantSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CInstantSkillEffect,CLuaInstantSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		Vec3 pos    = CLuaSkillSystem::getInstance().getLuaManager()->getVector3FromTable(2);
		effectObject->setPos( pos );

		MG_LOG( out_error, MG_STR("jjj_hero shoot at (%f,%f,%f)\n"), pos.x, pos.y, pos.z);

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaInstantSkillEffect::setPlayTotalTime(lua_State *L)
	{
		CInstantSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CInstantSkillEffect,CLuaInstantSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		Flt time= CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
		//effectObject->setPlayTotalTime( time );

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaInstantSkillEffect::setTargetIndex(lua_State *L)
	{
		CInstantSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CInstantSkillEffect,CLuaInstantSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		UInt index = CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
		effectObject->setTargetIndex(index);

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaInstantSkillEffect::setTargetId(lua_State *L)
	{
		CInstantSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CInstantSkillEffect,CLuaInstantSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		IdType id = CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
		effectObject->setTargetID(id);

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaInstantSkillEffect::setTargetType(lua_State *L)
	{
		CInstantSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CInstantSkillEffect,CLuaInstantSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		GAMEOBJ_TYPE type = (GAMEOBJ_TYPE)CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
		effectObject->setTargetType(type);

		return 0;
	}

	/******************************************************************************/
	//冲刺技能特效
	/******************************************************************************/
	Str CLuaSprintSkillEffect::LUA_TYPE_NAME = "CLuaSprintSkillEffect"; 

	//-----------------------------------------------------------------------

	const Str& CLuaSprintSkillEffect::getLuaTypeName() const 
	{
		return CLuaSprintSkillEffect::LUA_TYPE_NAME;
	}

	//-----------------------------------------------------------------------
	int CLuaSprintSkillEffect::start(lua_State *L)
	{
		CSprintSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CSprintSkillEffect,CLuaSprintSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		effectObject->start();

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaSprintSkillEffect::finish(lua_State *L)
	{
		CSprintSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CSprintSkillEffect,CLuaSprintSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		effectObject->end();

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaSprintSkillEffect::setEffect(lua_State *L)
	{
		CSprintSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CSprintSkillEffect,CLuaSprintSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		UInt id    = CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
		effectObject->setEffect( id );

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaSprintSkillEffect::setPos(lua_State *L)
	{
		CSprintSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CSprintSkillEffect,CLuaSprintSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		Vec3 pos    = CLuaSkillSystem::getInstance().getLuaManager()->getVector3FromTable(2);
		effectObject->setPos( pos );

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaSprintSkillEffect::setDistance(lua_State *L)
	{
		CSprintSkillEffect* effectObject  = LUA_RETRIEVE_OBJECT(CSprintSkillEffect,CLuaSprintSkillEffect,L); 
		if (NULL == effectObject) { DYNAMIC_ASSERT(0); return 0; }

		UInt dis = CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
		effectObject->setDis( dis );

		return 0;
	}
}