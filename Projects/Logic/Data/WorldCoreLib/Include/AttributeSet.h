
//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: AttributeSet.h
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
#ifndef _H_ATTRIBUTESET_
#define _H_ATTRIBUTESET_
//******************************************************************************************
#include "WorldCorePreqs.h"
#include "AttributeList.h"
//******************************************************************************************
namespace MG
{
    //-------------------------------------------------------------------------
    class AttributeSet
    {
        friend AttributeFormula;
        friend AttributeSystem;
    public:
        AttributeSet();
        ~AttributeSet();

    public:
        Flt     getFanalValue(U32 id) const;                        //获得id对应的最终表属性值
        void    setFanalValue(U32 id, Flt value);                   //设置ID对应的最终表属性值
        
        Flt     addValue(U32 id, Flt value);                        //加一个值，返回最终值

		void	resetAllValue();

		void	print();

    protected:
        void    calFanalAttr( CHAR_FORMULA_TYPE type, CharacterData* pCharacterData );    

    private:
        Flt     mAttrfinalList[ATTR_ID_COUNT_MAX];                        //最终属性
    };
    
}

#endif  // _H_ATTRIBUTESET_
//******************************************************************************************