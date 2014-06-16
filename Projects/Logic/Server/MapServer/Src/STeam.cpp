/******************************************************************************/
#include "stdafx.h"
#include "STeam.h"
#include "TroopDB.h"
#include "STroopNetPacketProcesser.h"
/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------------
	STeam::STeam()
	{
		setRegionObject(NULL);
		setID(0);
	}

	//-----------------------------------------------------------------------------
	STeam::STeam(IDType id)
	{
		setRegionObject(NULL);
		setID(id);
	}

	//-----------------------------------------------------------------------------
	STeam::~STeam()
	{

	}
	//-----------------------------------------------------------------------------
	void STeam::reduceHP( UInt num, DAMAGE_TYPE attackType /*= DAMAGE_TYPE_NULL*/ )
	{
		//修改内存值
		Character::reduceHP(num);
		//修改DB值
		//PlayerCharacterDBOp::updatePlayerCharacterHP(*FrontServerMain::getInstance().getDBDriver(), getData()->charID, getData()->charHP);
		//通知客户端和MapServer。
		//STroopNetPacketProcesser::getInstance().sendTroopDamageToClient(this, EFFECT_TYPE_HP, num);
		//STroopNetPacketProcesser::getInstance().sendTroopDamageToFrontServer(this, attackType, EFFECT_TYPE_HP, num);

	}
	//-----------------------------------------------------------------------------
	void STeam::reduceMP( UInt num, DAMAGE_TYPE attackType /*= DAMAGE_TYPE_NULL*/ )
	{
		//修改内存值
		Character::reduceMP(num);
		//修改DB值
		//PlayerCharacterDBOp::updatePlayerCharacterMP(*FrontServerMain::getInstance().getDBDriver(), getData()->charID, getData()->charMP);
		//通知客户端和MapServer。
		//STroopNetPacketProcesser::getInstance().sendTroopDamageToClient(this, EFFECT_TYPE_MP, num);
		//STroopNetPacketProcesser::getInstance().sendTroopDamageToFrontServer(this, attackType, EFFECT_TYPE_MP, num);

	}
	//-----------------------------------------------------------------------------
	void STeam::reduceSP( UInt num, DAMAGE_TYPE attackType /*= DAMAGE_TYPE_NULL*/ )
	{
		//修改内存值
		Character::reduceSP(num);
		//通知客户端和MapServer。
		//STroopNetPacketProcesser::getInstance().sendTroopDamageToClient(this, EFFECT_TYPE_SP, num);
		//STroopNetPacketProcesser::getInstance().sendTroopDamageToFrontServer(this, attackType, EFFECT_TYPE_SP, num);

	}
}
