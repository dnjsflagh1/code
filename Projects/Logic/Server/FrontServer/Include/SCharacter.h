//*************************************************************************************************
#ifndef _H_SCHARACTER_URIOEWURIO_
#define _H_SCHARACTER_URIOEWURIO_
//*************************************************************************************************

#include "FrontServerPreqs.h"
#include "GameObject.h"
#include "CharacterData.h"
#include "SAttributeSystem.h"
#include "CharacterSceneObj.h"
#include "LevelManager.h"

//*************************************************************************************************
namespace MG
{
    class SCharacter : public GameObject, public CharacterSceneObj
    {
        friend SAttributeSystem;

    public:

        SCharacter(GAMEOBJ_TYPE type, GameObjectData* data);
        virtual ~SCharacter();

    public:

        //-----------------------------------------------------------------------------------
        // Main
        //-----------------------------------------------------------------------------------

        virtual Bool                initialize();
        virtual Bool                unInitialize();

        virtual void                update(Flt delta);
        virtual void                clear();



        //-----------------------------------------------------------------------------------
        // Debug
        //-----------------------------------------------------------------------------------

        void                        print();

        //-----------------------------------------------------------------------------------
        // Player
        //-----------------------------------------------------------------------------------

        // get Player Info

        //-----------------------------------------------------------------------------------
        // Clan
        //-----------------------------------------------------------------------------------

        // get Clan Info
        
        //-----------------------------------------------------------------------------------
        // Skill
        //-----------------------------------------------------------------------------------


        SSkillUseManager*			getSkillUseManager() const;
		SSkillOwnManager*			getSkillOwnManager() const;


        //-----------------------------------------------------------------------------------
        // Base Info
        //-----------------------------------------------------------------------------------

        CharacterData*              getData();

        U32                         getCharacterTemplateID();
        void                        setCharacterTemplateID(U32 id);

        //���úͻ�õȼ�
        U32                         getLevel();
        void                        setLevel(U32 level);
        LevelManager*				getLevelManager(){return &mLevelManager;}

        //�õ��ͻ�ý�ɫģ��ָ��
        void                        setCharacterTempInfo();
        const CharacterTempInfo*    getCharacterTempInfo();

		//���Լ���ʱ����á�
		Int							getHp();
		Int							getMp();
		Int							getSp();
		Int							getMaxHp();
		Int							getMaxMp();
		Int							getMaxSp();
		virtual UInt                getLineageNum();
		virtual void                setHp(Int hp);
		virtual void                setMp(Int mp);
		virtual void                setSp(Int sp);

		// �����˺���ָ�
		void                        setHurtOrRecove(DamageType type, ATTACK_RESULT_TYPE resType, U32 value);
		void						setMax_HpSpMp();

		//��ɫ��������ԡ�
		virtual void                setDBAttrInit(UInt index, Flt value){;}
		virtual Flt                 getDBAttrInit(UInt index){return 0.f;}
		virtual void                setDBAttrLvlAdd(UInt index, Flt value){;}
		virtual Flt                 getDBAttrLvlAdd(UInt index){return 0.f;}


		virtual UInt				getDBAttrInitID(){return 0;}
		virtual UInt				getDBAttrLvlAddID(){return 0;}
		virtual void				setDBAttrInitID(UInt id){}
		virtual void				setDBAttrLvlAddID(UInt id){}
        //-----------------------------------------------------------------------------------
        // Region Info
        //-----------------------------------------------------------------------------------

        //�õ�����������
		SRegionObjectBase*			getCurrentRegionObject();
        void			            setRegion(REGION_OBJ_TYPE regionType, RegionIdType regionId, InstanceUIdType instanceUId);
        REGION_OBJ_TYPE	            getRegionType() ;
        U32			                getRegionId() ;
		InstanceIdType				getInstanceUId();
		
		RegionIdType				getLastRegionId();
		REGION_OBJ_TYPE				getLastRegionType();
		InstanceUIdType				getLastInstanceUId();


        //-----------------------------------------------------------------------------------
        // Alive
        //-----------------------------------------------------------------------------------

        virtual void                dead();
        Bool						isDead();

        //-----------------------------------------------------------------------------------
        // Attr Info
        //-----------------------------------------------------------------------------------

        AttributeSet*               getAttributeSet(){return mSAttributeSystem.getCalAttrInfo();}
        SAttributeSystem*           getSAttributeSystem(){return &mSAttributeSystem;}

        void                        calAttr(Bool isFirst);

		// ������������
		virtual void                calOtherAttr(){}

        //-----------------------------------------------------------------------------------
        // World Info
        //-----------------------------------------------------------------------------------
		Vec3						getPos(){return Vec3(0,0,0);};
		Vec3						getDir(){return Vec3(0,0,0);};


	private:
	public:
		SSkillUseManager*				mSkillUseManager;
		SSkillOwnManager*				mSkillOwnManager;
        SAttributeSystem                mSAttributeSystem;
        const CharacterTempInfo*        mCharacterTempInfo;
        SClan*						    mParentClan;
		LevelManager					mLevelManager;

		
		InstanceUIdType					mLastInstanceUId;
		RegionIdType					mLastRegionId;
		REGION_OBJ_TYPE					mLastRegionType;
         
    };

}
//*************************************************************************************************
#endif
//*************************************************************************************************