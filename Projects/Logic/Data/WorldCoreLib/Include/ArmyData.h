//*****************************************************************************************************
#ifndef _ARMYDATA_H
#define _ARMYDATA_H
//*****************************************************************************************************
#include "CharacterData.h"
//*****************************************************************************************************
namespace MG
{
    //*****************************************************************************************************
    //ArmyData
    struct ArmyData
    { 	
        TROOP_MASTER_TYPE  MasterType	      ;      //"�������˵����ͣ�
        U64                MasterId	          ;      //���������������ͣ���¼��Id( ��regionID��clanID )
        TROOP_LIFE_TYPE    ArmyLiveType	      ;      //���Ӵ�����ͣ�
        U32                ArmyExp	          ;      //���ӵ�ǰ����	
        U32                ArmyNum	          ;      //���ӵ�ǰ����	
        U32                ArmyLoyal	      ;      //���ӵ�ǰ�ҳ϶ȣ����Ϊ1000
        U32                ArmyWeapon         ;      //���ӵ�ǰ��װ�ȣ����Ϊ1000
        U32                ArmyWound	      ;      //���ӵ�ǰ�˱��ʣ����Ϊ1000

        //------------------------------------------------------------------------
        ArmyData()
            :MasterType(TROOP_MASTER_TYPE_NULL)	 
            ,MasterId(0)	     
            ,ArmyLiveType(TROOP_LIFE_TYPE_NULL)	 
            ,ArmyExp(0)	     
            ,ArmyNum(0)	     
            ,ArmyLoyal(0)	 
            ,ArmyWeapon(0)    
            ,ArmyWound(0)
        {

        }

        //------------------------------------------------------------------------
        ArmyData& operator=(const ArmyData& A)
        {
            if (this == &A)
            {
                return *this;
            }

            MasterType	           =          A.MasterType	    ;
            MasterId	           =          A.MasterId	    ;  
            ArmyLiveType	       =          A.ArmyLiveType	;  
            ArmyExp	               =          A.ArmyExp	        ;
            ArmyNum	               =          A.ArmyNum	        ;
            ArmyLoyal	           =          A.ArmyLoyal	    ;
            ArmyWeapon             =          A.ArmyWeapon      ;
            ArmyWound	           =          A.ArmyWound	    ;

            return *this;
        }  

    };
}
//*****************************************************************************************************
#endif
//*****************************************************************************************************