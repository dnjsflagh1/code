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
        TROOP_MASTER_TYPE  MasterType	      ;      //"军队主人的类型，
        U64                MasterId	          ;      //根据以上主人类型，记录的Id( 或regionID或clanID )
        TROOP_LIFE_TYPE    ArmyLiveType	      ;      //军队存活类型，
        U32                ArmyExp	          ;      //军队当前经验	
        U32                ArmyNum	          ;      //军队当前数量	
        U32                ArmyLoyal	      ;      //军队当前忠诚度，最大为1000
        U32                ArmyWeapon         ;      //军队当前武装度，最大为1000
        U32                ArmyWound	      ;      //军队当前伤兵率，最大为1000

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