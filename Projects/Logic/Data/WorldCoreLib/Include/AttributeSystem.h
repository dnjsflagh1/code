
//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: AttributeSystem.h
//        Author: xkc
//          Date: 2011-10-26
//          Time: 18:34
// Description: 
//			1.属性计算。
//
// modify History:
//      <author>    <time>        <descript>
//         xkc      2011-10-26      add

//////////////////////////////////////////////////////////////
//******************************************************************************************
#ifndef _H_ATTRIBUTESYSTEM_
#define _H_ATTRIBUTESYSTEM_
//******************************************************************************************
#include "WorldCorePreqs.h"
#include "AttributeSet.h"
//******************************************************************************************
namespace MG
{
    //-------------------------------------------------------------------------
    class AttributeSystem
    {
    public:
        AttributeSystem();
        virtual ~AttributeSystem();

    public:
		//打印信息
		void			print();
        //计算最终属性
        void            calFinalAttr(CHAR_FORMULA_TYPE type, CharacterData* pCharacterData);
        //获得属性计算信息。
        AttributeSet*   getCalAttrInfo();
        //获得某一个属性
        Flt             getFanalValue(U32 attrId);
        //设置属性
        void            setFanalValue(U32 attrId, Flt value);  
        //加一个值，返回最终值
        Int             addValue(U32 id, Int num);
		//关联计算（游戏中属性变化之后的计算）
		void			calRelateAttr(U32 attrId, Flt value, CHAR_FORMULA_TYPE type, CharacterData* pCharacterData);

		//设置HpSpMp最大值, 一般用于升级，或刚开始登录游戏时调用一次
		//void			setMax_HpSpMp();

	public:
		//特殊属性，需要单位换算。
		Flt				getMoveSpeed(){return mCalAttrInfo.getFanalValue(ATTR_ID_System01)/10.f;}
		Flt				getRideSpeed(){return mCalAttrInfo.getFanalValue(ATTR_ID_System02)/10.f;}
		Flt				getAttackDistance(){return mCalAttrInfo.getFanalValue(ATTR_ID_System03)/10.f;}
		Flt				getViewRange(){return mCalAttrInfo.getFanalValue(ATTR_ID_System05)/10.f;}
		Flt				getDetectHidingRange(){return mCalAttrInfo.getFanalValue(ATTR_ID_System06)/10.f;}
		UInt			getMaxHp(){return (UInt)(mCalAttrInfo.getFanalValue(ATTR_ID_HpMax));}
		UInt			getMaxMp(){return (UInt)(mCalAttrInfo.getFanalValue(ATTR_ID_MpMax));}
		UInt			getMaxSp(){return (UInt)(mCalAttrInfo.getFanalValue(ATTR_ID_SpMax));}
		//程序自添加属性 (护盾)
		Int				getShieldByType(STATUS_ABSORBTYPE type);
		void			setShieldByType(STATUS_ABSORBTYPE type, Int val);
		void			addShieldByType(STATUS_ABSORBTYPE type, Int val);

	private:
		void			calRelateAttr(std::vector<AttrInfo*>* tempVectorAttrInfo, CHAR_FORMULA_TYPE type, CharacterData* pCharacterData);

    private:
        AttributeSet     mCalAttrInfo;

    };
}


#endif