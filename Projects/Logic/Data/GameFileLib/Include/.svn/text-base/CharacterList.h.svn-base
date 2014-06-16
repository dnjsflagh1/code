//**********************************************************************************************************************
#ifndef _H_CHARACTERLIST_
#define _H_CHARACTERLIST_
//**********************************************************************************************************************
#include "GameFilePreqs.h"
//**********************************************************************************************************************
namespace MG
{
	struct CharacterTempInfo
	{
	friend CharacterTemplate;
	public:
		CharacterTempInfo();

	public:
		U32				CharacterId			;
		CHARACTER_TYPE	CharacterType		;
		U32				CharacterListId		;

	protected:
		const CharacterGenrealInfo*	mCharacterGenrealInfo	;
		const CharacterArmyInfo*	mCharacterArmyInfo		;
		const CharacterBuildInfo*	mCharacterBuildInfo		;
		const CharacterMonsterInfo*	mCharacterMonsterInfo	;
		const CharacterNpcInfo*		mCharacterNpcInfo		;
		const CharacterObjectInfo*	mCharacterObjectInfo	;

	public:
		//base
		U32					getCharacterTempId()const{return CharacterId;}
		CHARACTER_TYPE		getCharacterType()const{return CharacterType;}
		//
		U32					getCharacterArtIconId()const;
		U32					getCharacterArtMashId(int index = 0)const;
		Str16				getCharacterTitle()const;
		Str16				getCharacterTips()const;
		Str16				getCharacterSurName()const;
		Str16				getCharacterListName()const;
		U32					getCharacterLevel()const;
		U32					getCharacterAbilityAppendId(int index)const;
		U32					getCharacterCharacterSkillId(int index)const;
		U32					getCharacterLineageLevel()const;
		CHAR_FORMULA_TYPE	getCharacterFormulaType()const;
		U32					getCharacterInfluenceId()const;
		Bool				isValid() const;

		UInt				getAIBaseGroupId() const;
		UInt				getAIFightGroupId() const;

		U32					getCharacterVisionEventListId() const; 
		GENDER_TYPE			getCharacterGenderType()const;
		TROOPTEMPLATE_TYPE	getCharacterArmyType()const;

		//武将
		Str16				getGenrealName()const;
		GENDER_TYPE			getGenrealGenderType()const;
		POWERFUL_TYPE		getGenrealPowerfulType()const;	
		U32					getGenrealAge()const;
		U32					getGenrealMinLifeSpan()const;
		//U32					getGenrealMaxLifeSpan()const;
		U32					getGenrealNatureId()const;
		U32					getGenrealCharacterAppellationId()const;
		U32					getGenrealCharacterDialogId()const;
		U32					getGenrealWeaponAcction()const;
		U32					getGenrealAudioResId()const;

		//军队
		TROOPTEMPLATE_TYPE	getArmyArmyType()const;
		U32					getFormationNumMax()const;
		U32					getArmyArmyNumMax()const;
		U32					getFormationListNum()const;
		U32					getFormationCharacterNum()const;
		U32					getArmyArmyX()const;
		U32					getArmyArmyY()const;
		U32					getArmyListNum()const;
		U32					getArmyArmyLoyal()const;
		U32					getArmyArmyWeapon()const;
		U32					getArmyState(int index)const;
		U32					getArmyCollisionMeshId()const;

		//建筑
		U32					getBuildAudioResId()const;
		U32					getBuildArtMashId2()const;
		U32					getBuildMapListId()const;
		Str16				getBuildDestroyScript()const;
		CHAR_BUILD_TYPE		getBuildType()const;

		//怪物
		Str16				getMonsterSuiName()const;
		Str16				getMonsterName()const;
		GENDER_TYPE			getMonsterGenderType()const;
		POWERFUL_TYPE		getMonsterPowerfulType()const;	
		U32					getMonsterCharacterAppellationId()const;
		U32					getMonsterCharacterDialogId()const;
		U32					getMonsterAudioResId()const;
		U32					getMonsterItemGroupId()const;
        Byte                getMonsterNameColorType() const;
       
		//NPC
		Str16				getNpcSuiName()const;
		Str16				getNpcName()const;
		//Str16				getNpcZhiName()const;
		GENDER_TYPE			getNpcGenderType()const;
		U32					getNpcCharacterAppellationId()const;
		U32					getNpcCharacterDialogId()const;
		U32					getNpcArtEffectId()const;
		U32					getNpcAudioResId()const;
		U32					getNpcFunctionListId(int index)const;
		
		//物件
		U32					getObjectAudioResId()const;
		CHARACTER_OBJ_MUTUALTYPE					
							getObjectMutualType()const;
		Str16				getObjectMutualAction()const;
		U32					getObjectMutualTime()const;
		U32					getObjectMutualItemGroup()const;
		U32					getObjectMutualEffectId()const;
		Str16				getObjectMutualScript()const;

	};

	//--------------------------------------------------------------------------------
	class CharacterTemplate
	{
	public:
		CharacterTemplate(){;}
		~CharacterTemplate();
		SINGLETON_INSTANCE(CharacterTemplate);

	public:
		// MG_CN_MODIFY
		Bool										loadFile(Str16 filename, IMGExternalPackManager* packManager = NULL);
		CharacterTempInfo*							getCharacterTempInfo(U32 id);
		std::map<U32, CharacterTempInfo*>&	        getCharacterTempInfoList();
	private:
		void						clear();
		void						setTempInfo(CharacterTempInfo* info);

	public:
		std::map<U32, CharacterTempInfo*> mMapCharacterTempInfoNew;

	};
}
//**********************************************************************************************************************
#endif
//**********************************************************************************************************************