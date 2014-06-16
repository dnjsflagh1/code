//*****************************************************************************************************
#ifndef _CHARACTERENTITYDATA_H_
#define _CHARACTERENTITYDATA_H_
//*****************************************************************************************************
#include "SceneObjectData.h"
//*****************************************************************************************************
namespace MG
{
	//*****************************************************************************************************
	//ArmyData
	struct CharacterEntityData : public SceneObjectData
	{ 	
		Bool    isDied				;			//�Ƿ�����
		Bool	isFightState		;			//�Ƿ���ս��״̬

		Int     hp					;			//��ǰѪ
		Int     mp					;			//��ǰħ
		Int     sp					;			//��ǰ����
		Int     hpmax				;			//���Ѫ
		Int     mpmax				;			//���ħ
		Int     spmax				;			//�������
		U32		mCharacterTemplateID;			// ��ɫģ��ID
		U32		mLineageNum			;			// ��ɫת������
		U32		mLevel              ;			// ��ɫ��ǰ�ȼ�
		Vec3	mBirthPos			;			// ������λ��
		Vec3	mPos                ;			// �Լ���λ��  ����ǰλ�á�
		Vec3	mDir                ;			// �Լ��ĳ���
		UInt    charArtIcon         ;            //ͷ��ID
		Str16   surName             ;           //��ɫ����
		//------------------------------------------------------------------------
		CharacterEntityData()
			:isDied(false)				
			,isFightState(false)		
			,hp(0)				
			,mp(0)					
			,sp(0)					
			,hpmax(0)				
			,mpmax(0)				
			,spmax(0)				
			,mCharacterTemplateID(0)
			,mLevel(1)    
			,mLineageNum(0)
			,charArtIcon(30015)
			,surName(L"")
		{

		}
		//------------------------------------------------------------------------
		CharacterEntityData& operator=(const CharacterEntityData& A)
		{
			if (this == &A)
			{
				return *this;
			}

			SceneObjectData::operator =(A);

			isDied					=		A.isDied				;
			isFightState			=		A.isFightState			;
											
			hp						=		A.hp					;
			mp						=		A.mp					;
			sp						=		A.sp					;
			hpmax					=		A.hpmax					;
			mpmax					=		A.mpmax					;
			spmax					=		A.spmax					;
			mCharacterTemplateID	=		A.mCharacterTemplateID	;
			mLevel					=		A.mLevel				;
			mBirthPos				=		A.mBirthPos				;
			mPos					=		A.mPos					;
			mDir					=		A.mDir					;
			mLineageNum				=		A.mLineageNum			;
            charArtIcon             =       A.charArtIcon           ;
			surName                 =       A.surName               ;
			return *this;
		}  

	};
}
//*****************************************************************************************************
#endif
//*****************************************************************************************************