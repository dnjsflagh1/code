//**********************************************************************************************************
#ifndef _H_GAMEJUDGE_
#define _H_GAMEJUDGE_
//**********************************************************************************************************
#include "MapServerPreqs.h"
//**********************************************************************************************************

namespace MG
{
	//--------------------------------------------------------------------------------------------
	class CharacterJudge
	{
		friend GameJudge;
	public:
	protected:
		Bool checkCharacterJudge(SCharacter* pSCharacter, U32 characterJudgeId);

	private:
		Bool checkAttrAppendId(SCharacter* pSCharacter, U32 attrAppendId);
		Bool checkSkillId(SCharacter* pSCharacter, U32 skillId);
		Bool checkBuff(SCharacter* pSCharacter, U32 buffId, U32 addNum);
		Bool checkSpecialStatus(SCharacter* pSCharacter, U32 stateFlag);
		Bool checkTimepieceID(SCharacter* pSCharacter, U32 cdId);
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
		Bool checkGameJudge(SCharacter* pSCharacter, U32 characterJudgeId);

	protected:
	private:
		CharacterJudge		mCharacterJudge;
	};
}

//**********************************************************************************************************
#endif
//**********************************************************************************************************