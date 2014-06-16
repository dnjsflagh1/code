/******************************************************************************/
#ifndef _H_CCHARACTER_
#define _H_CCHARACTER_
/******************************************************************************/
#include "ClientPreqs.h"
#include "CharacterData.h"
#include "GameObject.h"
#include "CAttributeSystem.h"
/******************************************************************************/
namespace MG
{
    class CCharacter : public GameObject
    {
        friend CAttributeSystem;
    public:
        CCharacter(GAMEOBJ_TYPE type, GameObjectData* data, PlayerCharacterIdType id = 0);
        virtual ~CCharacter();

    public:
        CharacterData*				getCharacterData();

    public: // ���������ԡ�
        // ���úͻ�ý�ɫģ��
        U32                         getCharacterTemplateID();
        void                        setCharacterTemplateID(U32 id);

        //�õ�����������
        void			            setRegion(REGION_OBJ_TYPE type, U32 id,InstanceIdType instanceId,  Bool isCalBelongMapID=false) ;
        REGION_OBJ_TYPE	            getRegionType() ;
        U32			                getRegionID() ;
		InstanceIdType              getInstanceUId();

        //�õ��ͻ�ý�ɫģ��ָ��
        void                        setCharacterTempInfo();
        const CharacterTempInfo*    getCharacterTempInfo();

        AttributeSet*               getAttributeSet(){return mCAttributeSystem.getCalAttrInfo();}
        CAttributeSystem*           getAttributeSystem(){return &mCAttributeSystem;}

    ///----------------------------------------------------------------------------------------------
    /// ���Լ������
    public: // ��ս�����Լ��㡿
        //���Լ���ʱ����á�
        virtual UInt                getHp();
        virtual UInt                getMp();
        virtual UInt                getSp();
		virtual UInt				getMaxHp();
		virtual UInt				getMaxMp();
		virtual UInt				getMaxSp();
        virtual UInt                getLineageNum();
        virtual void                setHp(Int val);
        virtual void                setMp(Int val);
		virtual void                setSp(Int val);
		void						setMax_HpSpMp();
		//���úͻ�õȼ�
		U32                         getLevel();
		void                        setLevel(U32 level);

        // ����id ���ս������
        Int                         getFanalValue(U32 id);
        // ����id����ս������
        void                        setFanalValue(U32 id, Flt val);
        /// �ı�Ѫ �� �� �� ŭ��ֵ
        void                        setHpMpSp(Flt num, DamageType type, ATTACK_RESULT_TYPE resType);
        
    public:
        // ������������
        void                        calAttr();

	protected:
        //���Լ���ʱ����á�
        virtual Flt                 getDBAttrInit(UInt index){return 0.f;}
        virtual Flt                 getDBAttrLvlAdd(UInt index){return 0.f;}
		virtual UInt				getDBAttrInitID(){return 0;}
		virtual UInt				getDBAttrLvlAddID(){return 0;}
        // ������������
        virtual void                calOtherAttr(){}

    /// ���Լ������ -- end
    ///----------------------------------------------------------------------------------------------

    public:  /// �õ����ܹ�����, �˹�����ֻ�������߼����ݱ���
        CSkillOwnManager*				getSkillOwnManager(); 

    private:

		CSkillOwnManager*				mSkillOwnManager;
        CAttributeSystem                mCAttributeSystem;
        const CharacterTempInfo*        mCharacterTempInfo;
		

    };

}
/******************************************************************************/
#endif
/******************************************************************************/