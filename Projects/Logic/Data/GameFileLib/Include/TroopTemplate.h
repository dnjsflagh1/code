//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: TroopTemplate.h
//        Author: xkc
//          Date: 2011-10-27
//          Time: 18:34
// Description: 
//			1.����ģ���
//
// modify History:
//      <author>    <time>        <descript>
//         xkc      2011-10-27      add

//////////////////////////////////////////////////////////////
//******************************************************************************************
#ifndef _H_TROOPTEMPLATE_
#define _H_TROOPTEMPLATE_
//******************************************************************************************
#include "GameFilePreqs.h"
//******************************************************************************************
namespace MG
{
    //��������	                ������	            Ӧ�÷�Χ	��������	    ȡֵ��Χ
    //ArmyTemplateId	        ����Id	            C/S	        unsigned int	1~40��
    //CharacterTemplateId	    ��Ӧ�Ľ�ɫģ��		C	        char	        ��ɫģ��Id
    //ArmyType	                ��������	        C	        char	        4������
    //OfficialLevel	            �����λ�ȼ�	    C	        char	
    //ArmyLevel	                ���ӵȼ�	    	S	        unsigned int	
    //ArmyNumMax	            ��������	    	S	        unsigned int	
    //ArmyCharacterNum	        ��λ����	        S	        unsigned int	
    //ArmyX	                    ��ɫ����	    	S	        unsigned int	
    //ArmyY	                    ��ɫ�ݼ��	    	S	        byte	
    //ArmyLoyal	                �ҳ϶�	            S	        byte	
    //ArmyWeapon	            ��װ��	            S	        unsigned int	0��200
    //State1	                �ݵظ���״̬		S	        unsigned int	״̬ID
    //State2	                �ֵظ���״̬		S	        unsigned int	״̬ID
    //State3	                ɽ�ظ���״̬		S	        unsigned int	״̬ID
    //State4	                ѩ�ظ���״̬		S	        unsigned int	״̬ID
    //State5	                ɳ�ظ���״̬		S	        unsigned int	״̬ID
    //State6	                ˮ�и���״̬		S	        unsigned int	״̬ID
  
    //--------------------------------------------------------------------------------
    struct TroopTemplateInfo
    {
        U32                ArmyTemplateId	                      ;             //����ģ��id
        U32                CharacterTemplateId                    ;             //������ʹ�õĽ�ɫģ��id
        TROOPTEMPLATE_TYPE ArmyType	                              ;             //�������ͣ���ѡ
        U32                OfficialLevel	                      ;             //�����λ�ȼ�����
        U32                ArmyLevel	                          ;             //���ӵȼ�
        U32                ArmyNumMax	                          ;             //��������
		U32				   ArmyObjNum							  ;
        U32                ArmyCharacterNum	                      ;             //��λ����
        U32                ArmyX	                              ;             //��ɫ����
        U32                ArmyY	                              ;             //��ɫ�ݼ��
		U32				   ListNum								  ;				//��ɫ��������
        U32                ArmyLoyal	                          ;             //�ҳ϶�	 
        U32                ArmyWeapon	                          ;             //��װ��	 
        U32                StateArray[TROOPTEMPLATE_STATE_MAX]    ;             //�ڲ�ͬ�����о��е�״̬��
    
     }; 
    //--------------------------------------------------------------------------------
    class  TroopTemplate            
    {                     	         
    public:
        TroopTemplate();
        ~TroopTemplate();
        SINGLETON_INSTANCE(TroopTemplate);

    public:
        Bool                        load(Str16 fileName);
        Bool                        getTroopTemplateInfo(U32 id, const TroopTemplateInfo*& info);
        const TroopTemplateInfo*    getTroopTemplateInfo(U32 id);
		const TroopTemplateInfo*	getTroopTemplateInfoByIndex(Int index);
		U32							getNumsTroopTemplateInfo() { return mTroopTemplateInfoMap.size(); }

    protected:
        void                        clear();

    public:
        typedef std::map<U32, TroopTemplateInfo*>       TroopTemplateInfoMap;
        typedef TroopTemplateInfoMap::iterator          TroopTemplateInfoMapIter; 

    private:
        TroopTemplateInfoMap                            mTroopTemplateInfoMap;

    };
}
//******************************************************************************************
#endif  //_H_TROOPTEMPLATE_
//******************************************************************************************