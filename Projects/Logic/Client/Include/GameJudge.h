//**********************************************************************************************************
#ifndef _H_GAMEJUDGE_
#define _H_GAMEJUDGE_
//**********************************************************************************************************
#include "ClientPreqs.h"
//**********************************************************************************************************

namespace MG
{
	class ClanJudge
	{
		friend GameJudge;
	public:
	protected:
		GAMEJUDGE_TYPE checkClanJudge(CClan* pSClan, U32 clanJudgeId);

	private:
		Bool checkClanLevel(CClan* pSClan, U32 level);
		Bool checkClanQuest(CClan* pSClan, U32 questId);
		Bool checkClanItemAndNum(CClan* pSClan, U32 itemTemplateId, U32 num);
	};
	//--------------------------------------------------------------------------------------------
	class CharacterJudge
	{
		friend GameJudge;
	public:
	protected:
		GAMEJUDGE_TYPE checkCharacterJudge(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 characterJudgeId);

	private:
		Bool checkkCharacterType(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 characterType);
		Bool checkkCharacterLevel(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 characterLevel);
		Bool checkkCharacterLineageLevel(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 characterLineageLevel);
		Bool checkkCharacterGenderType(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 characterGenderType);
		//只有将领才会检查
		Bool checkkGenrealPowerfullType(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 genrealPowerfullType);
		//除了军队，其它都为特殊兵种。
		Bool checkkArmyType(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 armyType);

		Bool checkAttrAppendId(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 attrAppendId);
		Bool checkSkillId(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 skillId);
		Bool checkBuff(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 buffId, U32 addNum);
		Bool checkSpecialStatus(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 stateFlag);
		Bool checkTimepieceID(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 cdId);
	};
	//--------------------------------------------------------------------------------------------
	//目前氏族判断和角色判断只是读取SCharacter和SClan，而没有去写SCharacter和SClan
	//所以可以做成单键。
	//如果以后需求有变，建议将此类放在SCharacter下。
	class GameJudge
	{
	public:
		SINGLETON_INSTANCE(GameJudge);

	public:
		GAMEJUDGE_TYPE checkGameJudge(CClan* pSClan, CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, 
			U32 clanJudgeId, U32 characterJudgeId);
		GAMEJUDGE_TYPE checkClanJudge(CClan* pSClan, U32 clanJudgeId);
		GAMEJUDGE_TYPE checkCharacterJudge(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 characterJudgeId);

	protected:
	private:
		ClanJudge			mClanJudge;
		CharacterJudge		mCharacterJudge;
	};
}

//**********************************************************************************************************
#endif
//**********************************************************************************************************