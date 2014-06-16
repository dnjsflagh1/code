//***************************************************************************************
#ifndef _H_STATUSCHARACTERLIST_
#define _H_STATUSCHARACTERLIST_
//***************************************************************************************
#include "GameFilePreqs.h"
#include "StatusBaseInfo.h"
//***************************************************************************************
namespace MG
{
	enum
	{
		Status_Character_StatusCharacterId			,
		Status_Character_Notes						,	
		Status_Character_GroupId					,
		Status_Character_GroupLevel					,
		Status_Character_TargetLevel				,
		Status_Character_Name						,
		Status_Character_Text						,
		Status_Character_KindName					,
		Status_Character_ArtIconId					,
		Status_Character_ShowType					,
		Status_Character_StyleType					,
		Status_Character_SlotNum					,
		Status_Character_SlotPriority				,
		Status_Character_TimeType					,
		Status_Character_HoldTime					,
		Status_Character_DisappearType				,
		Status_Character_MaxAddNum					,
		Status_Character_AbilityAppendId			,
		Status_Character_StatusSysType				,
		Status_Character_VitiateFlag				,
		Status_Character_AbsorbType					,
		Status_Character_AbsorbNum					,
		Status_Character_VisionEventId				,
		Status_Character_ModelResId					,
		Status_Character_CycleNum					,
		Status_Character_CycleType					,
		Status_Character_CycleParameter1			,
		Status_Character_CycleParameter2			,
		Status_Character_CycleParameter3			,
		Status_Character_CycleParameter4			,
		Status_Character_EventCondition				,
		Status_Character_ConditionParameter1		,
		Status_Character_ConditionParameter2		,
		Status_Character_ConditionParameter3		,
		Status_Character_ConditionParameter4		,
		Status_Character_EventResult				,
		Status_Character_ResultParameter1			,
		Status_Character_ResultParameter2			,
		Status_Character_ResultParameter3			,
		Status_Character_ResultParameter4			,

		Status_Character_Max,
	};
	//----------------------------------------------------------------------
	struct StatusCharacterData : public StatusBaseInfo 
	{
		STATUS_STATUSSYSTYPE	StatusSysType		;
		UInt					VitiateFlag			;
		STATUS_ABSORBTYPE		AbsorbType			;
		UInt					AbsorbNum			;
		UInt					VisionEventId		;
		UInt					ModelResId			;
		UInt					CycleNum			;
		STATUS_CYCLETYPE		CycleType			;
		UInt					CycleParameter1		;
		UInt					CycleParameter2		;
		UInt					CycleParameter3		;
		UInt					CycleParameter4		;
		STATUS_EVENTCONDITION	EventCondition		;
		UInt					ConditionParameter1	;
		UInt					ConditionParameter2	;
		UInt					ConditionParameter3	;
		UInt					ConditionParameter4	;
		STATUS_EVENTRESULT		EventResult			;
		UInt					ResultParameter1	;
		UInt					ResultParameter2	;
		UInt					ResultParameter3	;
		UInt					ResultParameter4	;

	};

	//---------------------------------------------------------------------------

	class StatusCharacterList
	{
	public:
		StatusCharacterList(){;}
		~StatusCharacterList();
		SINGLETON_INSTANCE(StatusCharacterList);

	public:
		Bool					load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
		const StatusBaseInfo*	getStatusBaseInfo(UInt id);
		const StatusBaseInfo*	getmStatusBaseInfoByIdLvl(UInt groupId, UInt lvl);
		const StatusBaseInfo*	getmStatusBaseInfoByIdLvl(UInt groupId, UInt lvl, UInt objLvl);

	private:
		void					clear();
		void					setIdLvlMapStatusBaseInfo(StatusCharacterData* pData);

	private:
		std::map<UInt, StatusBaseInfo*> mMapStatusCharacterData;
		std::map<UInt, std::map<UInt, StatusBaseInfo*>> mIdLvlMapStatusBaseInfo;

	};

}

//***************************************************************************************
#endif
//***************************************************************************************