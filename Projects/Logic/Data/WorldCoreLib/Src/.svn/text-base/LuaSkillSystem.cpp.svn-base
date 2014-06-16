
/******************************************************************************/
#include "stdafx.h"
#include "SkillObject.h"
//#include "LuaSkillObject.h"
#include "LuaSkillSystem.h"
#include "SkillInfoList.h"
#include "ShortRangeGeneralAttackSkillTemplate.h"
#include "LongRangeGeneralAttackSkillTemplate.h"
#include "SingleTargetSkillTemplate.h"
#include "SingleEmitterSkillTemplate.h"
#include "SelfAreaSkillTemplate.h"
#include "TargetPosAreaSkillTemplate.h"
#include "ParabolaAreaSkillTemplate.h"
//#include "LuaSkillObject.h"
//#include "LuaCharacterForSkill.h"
//#include "LuaSkillEffect.h"
//#include "Character.h"
//#include "GameObject.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    LuaSkillSystem::LuaSkillSystem()
        :mLuaMgr(NULL)
    {
        
    }

    //-----------------------------------------------------------------------
    LuaSkillSystem::~LuaSkillSystem()
    {
        uninitialize();
    }

    //-----------------------------------------------------------------------
    Bool LuaSkillSystem::initialize(LuaManager* luaMgr, Str filePath)
    {
		//FUNDETECTION(__MG_FUNC__);
        mLuaMgr = luaMgr;

        if ( loadLuaFile(filePath) == false )
            return false;
        
        registerLua();
        
        loadSkillBaseInfo();

        return true;
    }

    //-----------------------------------------------------------------------
    Bool LuaSkillSystem::uninitialize()
    {
        return true;
    }


    //-----------------------------------------------------------------------
    Bool LuaSkillSystem::loadLuaFile(Str filePath)
    {
        if ( mLuaMgr->dofile(filePath.c_str()) == false ) 
        {
            lua_State* L =  mLuaMgr->getMainLuaState();
            MG_LOG( out_error, ("%s error: lua_load_skill error\n"), lua_tostring(L, -1) );
            return false;
        }
        return true;
    }

    //-----------------------------------------------------------------------
    //void LuaSkillSystem::registerLua()
    //{
    //    lua_State* L = mLuaMgr->getMainLuaState();

    //    #define REGISTER_CLUABINDER(binderClass, luastate) binderClass binderClass##Object; binderClass##Object.LuaRegister(luastate);

    ////            REGISTER_CLUABINDER(LuaSkillObject, L);
    ////            //REGISTER_CLUABINDER(LuaCharacterForSkill, L);
    ////            REGISTER_CLUABINDER(LuaSkillEffect, L);
				////REGISTER_CLUABINDER(LuaPointSkillEffect, L);
				////REGISTER_CLUABINDER(LuaEmitterSkillEffect, L);
				////REGISTER_CLUABINDER(LuaObjectSkillEffect, L);
				////REGISTER_CLUABINDER(LuaInstantSkillEffect, L);
				////REGISTER_CLUABINDER(LuaSprintSkillEffect, L);

    //    #undef REGISTER_CLUABINDER
    //}

    //-----------------------------------------------------------------------
    Bool LuaSkillSystem::loadSkillBaseInfo()
    {
		Bool result = true;
		SkillInfo* skillInfo = NULL;

		for(UInt i = 0; i < SkillInfoList::getInstance().getSkillInfoNum(); ++i)
		{
			skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfoByIndex(i);

			if(skillInfo->skillType == SKT_PASSIVENESS || skillInfo->skillType == SKT_GOUPANDDOWN)
			{
				continue;
			}

			UInt nargs = 0;
			Str8 action;

			mLuaMgr->startAssertStackBalance();
			{
				lua_State* L =  mLuaMgr->getMainLuaState();
				lua_getglobal( L, "Lua_AddSkill" );

				lua_pushinteger(L, (UInt)skillInfo->skillId);
				lua_pushinteger(L, (UInt)skillInfo->skillType);

				lua_newtable(L);	
				nargs++;
				mLuaMgr->setTableFieldByValue(nargs, skillInfo->skillId, -1);
				nargs++;
				mLuaMgr->setTableFieldByValue(nargs, skillInfo->skillInfo->skillTypeGroupId, -1);	
				nargs++;
				mLuaMgr->setTableFieldByValue(nargs, skillInfo->skillInfo->artIconId, -1);		

				for(UInt i = 0; i < 3; ++i)
				{
					MGStrOp::toString(((InitiativeSkillBasicInfo*)skillInfo->skillInfo)->skillExpression[i].action.c_str(), action);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, action, -1);	
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((InitiativeSkillBasicInfo*)skillInfo->skillInfo)->skillExpression[i].artEffectId, -1);	
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((InitiativeSkillBasicInfo*)skillInfo->skillInfo)->skillExpression[i].audioResId, -1);	
				}

				nargs++;
				mLuaMgr->setTableFieldByValue(nargs, ((InitiativeSkillBasicInfo*)skillInfo->skillInfo)->attackFrontTime, -1);	
				nargs++;
				mLuaMgr->setTableFieldByValue(nargs, ((InitiativeSkillBasicInfo*)skillInfo->skillInfo)->attackBehindTime, -1);	
				nargs++;
				mLuaMgr->setTableFieldByValue(nargs, ((InitiativeSkillBasicInfo*)skillInfo->skillInfo)->publicTimepieceId, -1);	
				nargs++;
				mLuaMgr->setTableFieldByValue(nargs, ((InitiativeSkillBasicInfo*)skillInfo->skillInfo)->publicTimepieceDelay, -1);	
				nargs++;
				mLuaMgr->setTableFieldByValue(nargs, ((InitiativeSkillBasicInfo*)skillInfo->skillInfo)->range, -1);	
				nargs++;
				mLuaMgr->setTableFieldByValue(nargs, ((InitiativeSkillBasicInfo*)skillInfo->skillInfo)->maxRange, -1);	
				nargs++;
				mLuaMgr->setTableFieldByValue(nargs, ((InitiativeSkillBasicInfo*)skillInfo->skillInfo)->attackType, -1);
				nargs++;
				mLuaMgr->setTableFieldByValue(nargs, ((InitiativeSkillBasicInfo*)skillInfo->skillInfo)->formulaParameterId, -1);

				if(skillInfo->skillType == SKT_SHORTRANGEGENERAL)
				{
					MGStrOp::toString(((InitiativeSkillBasicInfo*)skillInfo->skillInfo)->skillExpression[3].action.c_str(), action);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, action, -1);	
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((InitiativeSkillBasicInfo*)skillInfo->skillInfo)->skillExpression[3].artEffectId, -1);	
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((InitiativeSkillBasicInfo*)skillInfo->skillInfo)->skillExpression[3].audioResId, -1);	
				}
				else if(skillInfo->skillType == SKT_LONGRANGEGENERAL)
				{
					MGStrOp::toString(((InitiativeSkillBasicInfo*)skillInfo->skillInfo)->skillExpression[3].action.c_str(), action);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, action, -1);	
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((InitiativeSkillBasicInfo*)skillInfo->skillInfo)->skillExpression[3].artEffectId, -1);	
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((InitiativeSkillBasicInfo*)skillInfo->skillInfo)->skillExpression[3].audioResId, -1);	
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((LongRangeGeneralAttackSkillInfo*)skillInfo->skillInfo)->artEffectFlyId, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((LongRangeGeneralAttackSkillInfo*)skillInfo->skillInfo)->artEffectFlySpeed, -1);
				}
				else if(skillInfo->skillType == SKT_SINGLETARGET)
				{
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SingleTargetSkillInfo*)skillInfo->skillInfo)->skillLevel, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SingleTargetSkillInfo*)skillInfo->skillInfo)->artEffectFlyId, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SingleTargetSkillInfo*)skillInfo->skillInfo)->artEffectFlySpeed, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SingleTargetSkillInfo*)skillInfo->skillInfo)->ownerTimepieceId, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SingleTargetSkillInfo*)skillInfo->skillInfo)->ownerTimepieceDelay, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SingleTargetSkillInfo*)skillInfo->skillInfo)->resetTimepieceId, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SingleTargetSkillInfo*)skillInfo->skillInfo)->resetTimepieceGroupId, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SingleTargetSkillInfo*)skillInfo->skillInfo)->characterJudgeId1, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SingleTargetSkillInfo*)skillInfo->skillInfo)->characterJudgeId2, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SingleTargetSkillInfo*)skillInfo->skillInfo)->formulaParameterId2, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SingleTargetSkillInfo*)skillInfo->skillInfo)->stateId, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SingleTargetSkillInfo*)skillInfo->skillInfo)->stateNum, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SingleTargetSkillInfo*)skillInfo->skillInfo)->spendType, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SingleTargetSkillInfo*)skillInfo->skillInfo)->damageType, -1);
				}
				else if(skillInfo->skillType == SKT_SINGLEEMITTER)
				{
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SingleEmitterSkillInfo*)skillInfo->skillInfo)->skillLevel, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SingleEmitterSkillInfo*)skillInfo->skillInfo)->artEffectFlyId, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SingleEmitterSkillInfo*)skillInfo->skillInfo)->artEffectFlySpeed, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SingleEmitterSkillInfo*)skillInfo->skillInfo)->ownerTimepieceId, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SingleEmitterSkillInfo*)skillInfo->skillInfo)->ownerTimepieceDelay, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SingleEmitterSkillInfo*)skillInfo->skillInfo)->resetTimepieceId, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SingleEmitterSkillInfo*)skillInfo->skillInfo)->resetTimepieceGroupId, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SingleEmitterSkillInfo*)skillInfo->skillInfo)->characterJudgeId1, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SingleEmitterSkillInfo*)skillInfo->skillInfo)->characterJudgeId2, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SingleEmitterSkillInfo*)skillInfo->skillInfo)->formulaParameterId2, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SingleEmitterSkillInfo*)skillInfo->skillInfo)->stateId, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SingleEmitterSkillInfo*)skillInfo->skillInfo)->stateNum, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SingleEmitterSkillInfo*)skillInfo->skillInfo)->spendType, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SingleEmitterSkillInfo*)skillInfo->skillInfo)->damageType, -1);
				}
				else if(skillInfo->skillType == SKT_SELFAREA)
				{
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SelfAreaSkillInfo*)skillInfo->skillInfo)->skillLevel, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SelfAreaSkillInfo*)skillInfo->skillInfo)->skillRadius, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SelfAreaSkillInfo*)skillInfo->skillInfo)->attackNum, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SelfAreaSkillInfo*)skillInfo->skillInfo)->ownerTimepieceId, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SelfAreaSkillInfo*)skillInfo->skillInfo)->ownerTimepieceDelay, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SelfAreaSkillInfo*)skillInfo->skillInfo)->resetTimepieceId, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SelfAreaSkillInfo*)skillInfo->skillInfo)->resetTimepieceGroupId, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SelfAreaSkillInfo*)skillInfo->skillInfo)->characterJudgeId1, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SelfAreaSkillInfo*)skillInfo->skillInfo)->characterJudgeId2, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SelfAreaSkillInfo*)skillInfo->skillInfo)->formulaParameterId2, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SelfAreaSkillInfo*)skillInfo->skillInfo)->stateId, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SelfAreaSkillInfo*)skillInfo->skillInfo)->stateNum, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SelfAreaSkillInfo*)skillInfo->skillInfo)->spendType, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((SelfAreaSkillInfo*)skillInfo->skillInfo)->damageType, -1);
				}
				else if(skillInfo->skillType == SKT_TARGETPOSAREA)
				{
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((TargetPosAreaSkillInfo*)skillInfo->skillInfo)->skillLevel, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((TargetPosAreaSkillInfo*)skillInfo->skillInfo)->pointEffectId, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((TargetPosAreaSkillInfo*)skillInfo->skillInfo)->pointSkillEffectId, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((TargetPosAreaSkillInfo*)skillInfo->skillInfo)->pointAudioId, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((TargetPosAreaSkillInfo*)skillInfo->skillInfo)->skillRadius, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((TargetPosAreaSkillInfo*)skillInfo->skillInfo)->attackNum, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((TargetPosAreaSkillInfo*)skillInfo->skillInfo)->skillCastNum, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((TargetPosAreaSkillInfo*)skillInfo->skillInfo)->skillCastInterval, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((TargetPosAreaSkillInfo*)skillInfo->skillInfo)->ownerTimepieceId, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((TargetPosAreaSkillInfo*)skillInfo->skillInfo)->ownerTimepieceDelay, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((TargetPosAreaSkillInfo*)skillInfo->skillInfo)->resetTimepieceId, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((TargetPosAreaSkillInfo*)skillInfo->skillInfo)->resetTimepieceGroupId, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((TargetPosAreaSkillInfo*)skillInfo->skillInfo)->characterJudgeId1, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((TargetPosAreaSkillInfo*)skillInfo->skillInfo)->characterJudgeId2, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((TargetPosAreaSkillInfo*)skillInfo->skillInfo)->formulaParameterId2, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((TargetPosAreaSkillInfo*)skillInfo->skillInfo)->stateId, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((TargetPosAreaSkillInfo*)skillInfo->skillInfo)->stateNum, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((TargetPosAreaSkillInfo*)skillInfo->skillInfo)->spendType, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((TargetPosAreaSkillInfo*)skillInfo->skillInfo)->damageType, -1);
				}
				else if(skillInfo->skillType == SKT_PARABOLAAREA)
				{
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((ParabolaAreaSkillInfo*)skillInfo->skillInfo)->skillLevel, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((ParabolaAreaSkillInfo*)skillInfo->skillInfo)->pointEffectId, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((ParabolaAreaSkillInfo*)skillInfo->skillInfo)->artEffectFlyId, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((ParabolaAreaSkillInfo*)skillInfo->skillInfo)->artEffectFlySpeed, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((ParabolaAreaSkillInfo*)skillInfo->skillInfo)->pointAudioId, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((ParabolaAreaSkillInfo*)skillInfo->skillInfo)->skillRadius, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((ParabolaAreaSkillInfo*)skillInfo->skillInfo)->attackNum, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((ParabolaAreaSkillInfo*)skillInfo->skillInfo)->ownerTimepieceId, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((ParabolaAreaSkillInfo*)skillInfo->skillInfo)->ownerTimepieceDelay, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((ParabolaAreaSkillInfo*)skillInfo->skillInfo)->resetTimepieceId, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((ParabolaAreaSkillInfo*)skillInfo->skillInfo)->resetTimepieceGroupId, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((ParabolaAreaSkillInfo*)skillInfo->skillInfo)->characterJudgeId1, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((ParabolaAreaSkillInfo*)skillInfo->skillInfo)->characterJudgeId2, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((ParabolaAreaSkillInfo*)skillInfo->skillInfo)->formulaParameterId2, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((ParabolaAreaSkillInfo*)skillInfo->skillInfo)->stateId, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((ParabolaAreaSkillInfo*)skillInfo->skillInfo)->stateNum, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((ParabolaAreaSkillInfo*)skillInfo->skillInfo)->spendType, -1);
					nargs++;
					mLuaMgr->setTableFieldByValue(nargs, ((ParabolaAreaSkillInfo*)skillInfo->skillInfo)->damageType, -1);
				}

				if ( mLuaMgr->luaPcall( 3, 1 ) )
					result = (lua_toboolean(L,-1) == 1 ? true : false);
				else
					result = false;

				lua_pop(L, 1);
			}
			mLuaMgr->endAssertStackBalance();

		}

		return result;
    }

	//-----------------------------------------------------------------------
	void LuaSkillSystem::getNumberListFromTable( Int tableIndex, Str name, std::vector<U32>& list )
	{
		lua_State* L =  mLuaMgr->getMainLuaState();

		Str result;
		lua_pushstring(L, name.c_str());

		if (tableIndex < 0)  tableIndex -= 1; 

		lua_gettable(L, tableIndex);  /* get table[key] */
		if (lua_istable(L, -1))
		{
			lua_pushnil(L); 
			// 用一下 'key' （在索引 -2 处） 和 'value' （在索引 -1 处）
			while (lua_next(L, -2) != 0) 
			{
				Int valueIndex	= -1;
				Int keyIndex	= -2;
				
				if ( lua_isnumber(L, valueIndex) )
				{
					U32 id    = (U32)lua_tonumber(L, valueIndex);
					list.push_back( id );
				}
				
				// 移除 'value' ；保留 'key' 做下一次叠代 
				lua_pop(L, 1);
			}
		}
		lua_pop(L, 1);  /* remove table[key] */
	}

	//-----------------------------------------------------------------------
	void LuaSkillSystem::getNumberMapFromTable( Int tableIndex, Str name, std::map<IdType,UInt>& map )
	{
		lua_State* L =  mLuaMgr->getMainLuaState();

		Str result;
		lua_pushstring(L, name.c_str());

		if (tableIndex < 0)  tableIndex -= 1; 

		lua_gettable(L, tableIndex);  /* get table[key] */
		if (lua_istable(L, -1))
		{
			lua_pushnil(L); 
			// 用一下 'key' （在索引 -2 处） 和 'value' （在索引 -1 处）
			while (lua_next(L, -2) != 0) 
			{
				Int valueIndex	= -1;
				Int keyIndex	= -2;

				if ( lua_isnumber(L, keyIndex) && lua_isnumber(L, valueIndex) )
				{
					IdType keyID		= (IdType)lua_tonumber(L, keyIndex);
					UInt valueID		= (UInt)lua_tonumber(L, valueIndex);
					map[keyID] = valueID;
				}

				// 移除 'value' ；保留 'key' 做下一次叠代 
				lua_pop(L, 1);
			}
		}
		lua_pop(L, 1);  /* remove table[key] */
	}

    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------

	////-----------------------------------------------------------------------
	



}