//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: TroopTemplate.h
//        Author: xkc
//          Date: 2011-10-27
//          Time: 18:34
// Description: 
//			1.军队模板表。
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
    //数据名称	                中文名	            应用范围	数据类型	    取值范围
    //ArmyTemplateId	        序列Id	            C/S	        unsigned int	1~40亿
    //CharacterTemplateId	    对应的角色模板		C	        char	        角色模板Id
    //ArmyType	                军队类型	        C	        char	        4汉字内
    //OfficialLevel	            带领官位等级	    C	        char	
    //ArmyLevel	                军队等级	    	S	        unsigned int	
    //ArmyNumMax	            人数上限	    	S	        unsigned int	
    //ArmyCharacterNum	        单位人数	        S	        unsigned int	
    //ArmyX	                    角色横间距	    	S	        unsigned int	
    //ArmyY	                    角色纵间距	    	S	        byte	
    //ArmyLoyal	                忠诚度	            S	        byte	
    //ArmyWeapon	            武装度	            S	        unsigned int	0～200
    //State1	                草地附加状态		S	        unsigned int	状态ID
    //State2	                林地附加状态		S	        unsigned int	状态ID
    //State3	                山地附加状态		S	        unsigned int	状态ID
    //State4	                雪地附加状态		S	        unsigned int	状态ID
    //State5	                沙地附加状态		S	        unsigned int	状态ID
    //State6	                水中附加状态		S	        unsigned int	状态ID
  
    //--------------------------------------------------------------------------------
    struct TroopTemplateInfo
    {
        U32                ArmyTemplateId	                      ;             //军队模板id
        U32                CharacterTemplateId                    ;             //军队所使用的角色模板id
        TROOPTEMPLATE_TYPE ArmyType	                              ;             //军队类型，单选
        U32                OfficialLevel	                      ;             //带领官位等级下限
        U32                ArmyLevel	                          ;             //军队等级
        U32                ArmyNumMax	                          ;             //人数上限
		U32				   ArmyObjNum							  ;
        U32                ArmyCharacterNum	                      ;             //单位人数
        U32                ArmyX	                              ;             //角色横间距
        U32                ArmyY	                              ;             //角色纵间距
		U32				   ListNum								  ;				//角色横排数量
        U32                ArmyLoyal	                          ;             //忠诚度	 
        U32                ArmyWeapon	                          ;             //武装度	 
        U32                StateArray[TROOPTEMPLATE_STATE_MAX]    ;             //在不同地形行军中的状态。
    
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