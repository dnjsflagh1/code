
//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: AttributePara.h
//        Author: xkc
//          Date: 2011-10-26
//          Time: 18:34
// Description: 
//			1.属性参数表。
//
// modify History:
//      <author>    <time>        <descript>
//         xkc      2011-10-26      add

//////////////////////////////////////////////////////////////
//******************************************************************************************
#ifndef _H_ATTRIBUTEPARA_
#define _H_ATTRIBUTEPARA_
//******************************************************************************************
#include "GameFilePreqs.h"
//******************************************************************************************
namespace MG
{
    //--------------------------------------------------------------------------------------------------
    struct AttrParaInfo
    {
        U32                     FormulaParameterId;         //参数ID
        U32                     FormulaId;                  //公式ID
        U32                     AbilityId;                  //结果对应的ID
        Flt                     para[ATTR_PARA_NUM];        //参数表
        U32                     attrID[ATTR_PARA_NUM];      //属性ID表
    };
    //--------------------------------------------------------------------------------------------------
    class  AttributePara
    {
    public:
        AttributePara();
        ~AttributePara();
        SINGLETON_INSTANCE(AttributePara);

    public:
		// MG_CN_MODIFY
        Bool load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
        Bool getAttrParaInfo(U32 id, const AttrParaInfo*& info);
        const AttrParaInfo* getAttrParaInfo(U32 id);

    protected:
        void clear();

    public:
        typedef std::map<U32, AttrParaInfo*> AttrParaInfoMap;
        typedef AttrParaInfoMap::iterator   AttrParaInfoMapIter;

    protected:
        AttrParaInfoMap mAttrParaInfoMap;

    };
}
//******************************************************************************************
#endif
//******************************************************************************************