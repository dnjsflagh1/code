/******************************************************************************/
#ifndef _CLIENTREPREQS_H_
#define _CLIENTREPREQS_H_
/******************************************************************************/

/******************************************************************************/

#include "WorldCorePreqs.h"
#include "CommonGameDefine.h"
#include "ClientDefine.h"

/******************************************************************************/
namespace MG
{
	class CBuffCharacterObject;
	class CBuffManager;
	class CBuffPacketProcesser;
    ///////////////////////////////////////////////////////

    class GameMain;
    class IOpCtrl;

    class LogoScreen;
    class LoginScreen;
    class GameScreen;

    ///////////////////////////////////////////////////////

	class GameJudge;
	class ClanJudge;
	class CharacterJudge;
	class LevelManager;

    ///////////////////////////////////////////////////////

    class LuaManager;
    class GameObjectOpCtrl;

    class CSceneManager;
    
    ///////////////////////////////////////////////////////

    class CSceneObject;
    class CSceneEntity;

    class CCharacterSceneEntity;
    class CNoCharacterSceneEntity;

    class CPlayerCharacterEntity;
    class CThirdPartyCharacterEntity;

    class CNpcEntity;

    class CBuildingEntity;
    class COrdinaryBuildingEntity;

    class CTroopSoldierEntity;
    class CTroopEntity;

    class CMonsterEntity;

    ///////////////////////////////////////////////////////

    class CClan;
    class CPlayer;

    class CCharacter;
 
    class CPlayerTroop;
    class CPlayerCharacter;
    class CBattleBuild;

    ///////////////////////////////////////////////////////

    class CBuffManagerForCharacter;
    class CBuffObject;
    class HeadDamage;
    class HeadDamageManage;
    class HeadDamageResouce;
    class HeadDesManage;
    class HeadDes;


    ///////////////////////////////////////////////////////

	//任务相关
	class CQuestPlayerCharacter;
	class CQuestManager;

    ///////////////////////////////////////////////////////

	//RegionObject 新版本
	class CRegionObject;
	
	//class CMapObject;
	//class CAreaObject;
	

	class CMapDistribution;
	class CPlaceObject;
	class CPveObject;
	class CTiroObject;

	class CRegionManager;

    ///////////////////////////////////////////////////////

    struct SkillData;
    class CSkillUseManager;
	class CSkillOwnManager;
    class CSkillObject;
    class CSkillEffectSystem;
    class CEmitterSkillEffect;
    class CPointSkillEffect;

	class  CPointSkillEffect;
	class  CEmitterSkillEffect;
	class  CObjectSkillEffect;
	class  CInstantSkillEffect;
	class  CSprintSkillEffect;
	class  CGoUpAndDownSkillEffect;

    ///////////////////////////////////////////////////////

    class CAIManager;

    class CCSEntityLineMoveAcion;
    class CCSEntityInjectSkillAcion;

	class ISceneNodePathFindingMoveInAdvanceAction;

	class CAIEntityPathFindingMoveInAdvance;

	struct InitiativeSkillBasicInfo;

    ///////////////////////////////////////////////////////

    class SLGCameraOpCtrl;
    class SLGCameraStretchAction;

	class CAIEntityGroup;

	struct ISceneObjectCollisionCallback;

	///////////////////////////////////////////////////////

	struct SimpleCharacterResInfo;
	struct ArtIconResCsvInfo;

	class FightManager;

	struct FightAIGroup;

	struct FightAIInfo;

	class AIControllerListener;

	struct BaseAIGroup;

	struct SkillRatio;

	class CAI;

	class CAIController;

	struct FightTriggerEvent;

	class CAIEntityFightTrigger;

	struct ItemData;

	class CItemEntity;

	struct CharacterVisionEventInfo;

	class CAISoldierInTroopMove;

	class CAISoldierInTroopAttack;

}

#endif	//_CLIENTREPREQS_H_