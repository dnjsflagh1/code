//**********************************************************************************************************
#ifndef _H_GAMEJUDGE_
#define _H_GAMEJUDGE_
//**********************************************************************************************************
#include "FrontServerPreqs.h"
//**********************************************************************************************************

namespace MG
{
	class ClanJudge
	{
		friend GameJudge;
	public:
	protected:
		GAMEJUDGE_TYPE checkClanJudge(SClan* pSClan, U32 clanJudgeId);

	private:
		Bool checkClanLevel(SClan* pSClan, U32 level);
		Bool checkClanQuest(SClan* pSClan, U32 questId);
		Bool checkClanItemAndNum(SClan* pSClan, U32 itemTemplateId, U32 num);
	};
	//--------------------------------------------------------------------------------------------
	class CharacterJudge
	{
		friend GameJudge;
	public:
	protected:
		GAMEJUDGE_TYPE checkCharacterJudge(SCharacter* pSCharacter, U32 characterJudgeId);

	private:
		Bool checkkCharacterType(SCharacter* pSCharacter, U32 characterType);
		Bool checkkCharacterLevel(SCharacter* pSCharacter, U32 characterLevel);
		Bool checkkCharacterLineageLevel(SCharacter* pSCharacter, U32 characterLineageLevel);
		Bool checkkCharacterGenderType(SCharacter* pSCharacter, U32 characterGenderType);
		//ֻ�н���Ż���
		Bool checkkGenrealPowerfullType(SCharacter* pSCharacter, U32 genrealPowerfullType);
		//���˾��ӣ�������Ϊ������֡�
		Bool checkkArmyType(SCharacter* pSCharacter, U32 armyType);
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
		GAMEJUDGE_TYPE checkGameJudge(SClan* pSClan, SCharacter* pSCharacter, U32 clanJudgeId, U32 characterJudgeId);
		GAMEJUDGE_TYPE checkClanJudge(SClan* pSClan, U32 clanJudgeId);
		GAMEJUDGE_TYPE checkCharacterJudge(SCharacter* pSCharacter, U32 characterJudgeId);

	protected:
	private:
		ClanJudge			mClanJudge;
		CharacterJudge		mCharacterJudge;
	};
}

//**********************************************************************************************************
#endif
//**********************************************************************************************************