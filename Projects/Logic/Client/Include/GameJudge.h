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
		//ֻ�н���Ż���
		Bool checkkGenrealPowerfullType(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 genrealPowerfullType);
		//���˾��ӣ�������Ϊ������֡�
		Bool checkkArmyType(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 armyType);

		Bool checkAttrAppendId(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 attrAppendId);
		Bool checkSkillId(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 skillId);
		Bool checkBuff(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 buffId, U32 addNum);
		Bool checkSpecialStatus(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 stateFlag);
		Bool checkTimepieceID(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 cdId);
	};
	//--------------------------------------------------------------------------------------------
	//Ŀǰ�����жϺͽ�ɫ�ж�ֻ�Ƕ�ȡSCharacter��SClan����û��ȥдSCharacter��SClan
	//���Կ������ɵ�����
	//����Ժ������б䣬���齫�������SCharacter�¡�
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