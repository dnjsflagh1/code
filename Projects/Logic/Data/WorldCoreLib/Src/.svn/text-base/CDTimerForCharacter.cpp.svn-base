//*******************************************************************************************************
#include "stdafx.h"
#include "CDTimerForCharacter.h"
//#include "Character.h"
#include "SkillObject.h"
//*******************************************************************************************************
namespace MG
{
    CDTimerForCharacter::CDTimerForCharacter(GameObject* pParent)
        :mParent(pParent)
    {

    }
    //---------------------------------------------------------------------------------------
    CDTimerForCharacter::~CDTimerForCharacter()
    {

    }
    //---------------------------------------------------------------------------------------
    Bool CDTimerForCharacter::addSkillCD( SkillBaseInfo* pSkillInfo )
    {
        //加组和自己的id
        if ( pSkillInfo->ownerTimepieceId )
            addTimer(pSkillInfo->ownerTimepieceId, pSkillInfo->ownerTimepieceDelay);
        if ( pSkillInfo->publicTimepieceId )
            addTimer(pSkillInfo->publicTimepieceId, pSkillInfo->publicTimepieceDelay);
        //删除自己影响的组和个别ID
        if ( pSkillInfo->resetTimepieceGroupId )
            removeGroupTimer(pSkillInfo->resetTimepieceGroupId);
        if ( pSkillInfo->resetTimepieceId )
            removeTimer(pSkillInfo->resetTimepieceId);

        return true;
    }
    //---------------------------------------------------------------------------------------
    MG::Bool CDTimerForCharacter::checkSkillCD( SkillBaseInfo* pSkillInfo )
    {
        //检查自己的id和组id是否正在运行
        if ( pSkillInfo->ownerTimepieceId  &&  ifGoing(pSkillInfo->ownerTimepieceId) )
            return false;
        if ( pSkillInfo->publicTimepieceId  &&  ifGoing(pSkillInfo->publicTimepieceId) )
            return false;

        return true;
    }
}