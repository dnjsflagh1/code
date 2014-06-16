//*************************************************************************************************//
#include "stdafx.h"
#include "BattleConfig.h"
#include "Ini.h"
#include "CharacterList.h"
//*************************************************************************************************//
namespace MG
{
	BattleConfig::BattleConfig()
	{
	}

	//--------------------------------------------------------------------------
	BattleConfig::~BattleConfig()
	{
	}

	//--------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool BattleConfig::loadFile( std::wstring fileName, IMGExternalPackManager* packManager/* = NULL*/ )
	{
		assert(fileName.length() > 4);

		//读取Ini文件
		UINI ini;
		// MG_CN_MODIFY
		if ( ini.create( fileName, packManager ) )
		{
			//根据Index取出ini内容

			BattleConfigInfo newBattleInfo;

			//if (false == ini.hasGroup(L"battle"))
			//{
			//	DEBUG_ASSERT_LOG(false, "load BattleConfig File error");
			//	return false;
			//}

			ini.setGroup(L"battle");
			//MGStrOp::toI32( ini.getValue(L"BattleTimeSecond", L"0" ).c_str(), newBattleInfo.battleSecond );
			//MGStrOp::toI32( ini.getValue(L"PrepareTimeSecond", L"0" ).c_str(), newBattleInfo.prepareSecond );

			//newBattleInfo.prepareSecond = newBattleInfo.prepareSecond/10;
			for(Int troopIndex = 0; troopIndex < MAX_TROOP_NUM; ++troopIndex)
			{
				wchar_t tempStr[60] = { 0 };

				swprintf_s(tempStr,60, L"AttackCamp_%d", troopIndex + 1);
				loadSingleCampInfo(&ini, tempStr, &(newBattleInfo.attackCampInfo[troopIndex]));

				swprintf_s(tempStr,60, L"DefenseCamp_%d", troopIndex + 1);
				loadSingleCampInfo(&ini, tempStr, &(newBattleInfo.defenseCampInfo[troopIndex]));
			}

			mBattleConfigList.push_back( newBattleInfo );
		
			return true;
		}
		return false;
	}

	//--------------------------------------------------------------------------
	void BattleConfig::loadSingleCampInfo(UINI* ini, wchar_t* campName, CampConfigInfo* campInfo)
	{
		if (false == ini->hasGroup(campName))
		{
			return;
		}

		ini->setGroup(campName);
		MGStrOp::toI32(ini->getValue(L"ArmyNum", L"0" ).c_str(), campInfo->armyNum);
		//campInfo->armyNum = 1;	//默认设置为1 for test

		MGStrOp::toI32(ini->getValue(L"TroopGroupNum", L"0" ).c_str(), campInfo->troopGroupNum);

		wchar_t tempStr[60] = { 0 };
		for (Int i=0; i<campInfo->troopGroupNum; ++i)
		{
			swprintf_s(tempStr,60, L"TroopTemplate_%d", i + 1);
			MGStrOp::toI32( ini->getValue(tempStr, L"0" ).c_str(), campInfo->troopGroupInfo[i].troopTemplateId);

#if 1
			Int troopTemplateId = campInfo->troopGroupInfo[i].troopTemplateId;
			const CharacterTempInfo* charTempInfo = CharacterTemplate::getInstance().getCharacterTempInfo(troopTemplateId);
			DYNAMIC_ASSERT(NULL != charTempInfo);
			campInfo->troopGroupInfo[i].troopNum = charTempInfo->getFormationNumMax();
			campInfo->troopGroupInfo[i].troopSolierNum = charTempInfo->getFormationCharacterNum();
#endif
#if 0
			swprintf_s(tempStr,60, L"TroopNum_%d", i + 1);
			MGStrOp::toI32( ini->getValue(tempStr, L"0" ).c_str(), campInfo->troopGroupInfo[i].troopNum);
			
			swprintf_s(tempStr,60, L"TroopSolierNum_%d", i + 1);
			MGStrOp::toI32( ini->getValue(tempStr, L"0" ).c_str(), campInfo->troopGroupInfo[i].troopSolierNum);
#endif
		}
		
		int ii =0;
	}

	//--------------------------------------------------------------------------
	Int BattleConfig::getBattleConfigNum()
	{
		return mBattleConfigList.size();
	}

	//--------------------------------------------------------------------------
	BattleConfigInfo* BattleConfig::getBattleConfigByIndex( Int index )
	{
		assert(index >= 0  &&  index < (Int)mBattleConfigList.size());

		return &(mBattleConfigList.at(index));
	}

	//--------------------------------------------------------------------------
}