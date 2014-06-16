
/******************************************************************************/

#include "stdafx.h"
#include "SBuilding.h"
#include "SSkillOwnManager.h"
#include "SCDManager.h"
#include "SWorldManager.h"
#include "SSkillOwnManager.h"
#include "SBuffManager.h"
/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------------
	SBuilding::SBuilding(GameObjectIndexIdInSceneType indexId)
		:SCharacter(GOT_BUILDING, MG_NEW BuildingData())
	{
		//��ü���
		getSkillOwnManager()->getDefultSkill();
		setSCDManager(CD_MASTER_TYPE_BUILD, this);
	}

	//-----------------------------------------------------------------------------
	SBuilding::~SBuilding()
	{

	}

	//-----------------------------------------------------------------------------
	BuildingData* SBuilding::getBuildingData()
	{
		return (BuildingData*)(getGameObjectData());
	}

	//-----------------------------------------------------------------------------
	SPlayerIdentifyInfo* SBuilding::getParentPlayerIdentifyInfo()
	{
		return &mPlayerIndentifyInfo;
	}

	//-----------------------------------------------------------------------------
	void SBuilding::init()
	{
		//����ģ����Ϣ
		setCharacterTempInfo();
		//��������
		calAttr();

		//SCharacter::init();
	}

	//-----------------------------------------------------------------------------
	CHAR_BUILD_TYPE SBuilding::getBuildingType()
	{
		return getCharacterTempInfo()->getBuildType();
	}
	//-----------------------------------------------------------------------------
	void SBuilding::calAttrOther()
	{
		//���㼼�ܡ�
		getSkillOwnManager()->calAttrAllBase();
		//����״̬��
		getSBuffManager()->calAttrAllBase();
	}
}