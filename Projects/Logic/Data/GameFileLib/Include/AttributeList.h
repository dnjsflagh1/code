
//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: AttributeList.h
//        Author: xkc
//          Date: 2011-10-24
//          Time: 18:34
// Description: 
//			1.所有属性穷举表。
//
// modify History:
//      <author>    <time>        <descript>
//         xkc      2011-10-24      add

//////////////////////////////////////////////////////////////
//******************************************************************************************
#ifndef _H_ATTRIBUTELIST_
#define _H_ATTRIBUTELIST_
//******************************************************************************************
#include "GameFilePreqs.h"
//******************************************************************************************
namespace MG
{
    //----------------------------------------------------------------------
    struct AttrInfo
    {
        ATTR_ID                     attrId;        //属性ID
		UInt						attrInitId;
		UInt						attrAddId;
		UInt						groupId;
        Str16                       attrChName;    //中文名
        ATTR_USE_TYPE               useType;       //属性使用类型
        Int                         defaultValue;  //默认值
        Int                         minValue;      //最小值
        Int                         maxValue;      //最大值
        U32                         formulaParaID[CHAR_FORMULA_TYPE_MAX];//公式参数id

        AttrInfo()
            :attrId(ATTR_ID_NULL)
			,attrAddId(0)
			,attrInitId(0)
            ,groupId(0)
            ,useType(ATTR_USE_TYPE_NULL)
            ,defaultValue(0)
            ,minValue(0)
            ,maxValue(0)
        {
            memset( formulaParaID, 0, sizeof(formulaParaID) );
        }
    };
    //----------------------------------------------------------------------
    class AttributeList
    {
		friend AttributeInit;
		friend AttributeAppend;
    public:
        AttributeList(){;}
        ~AttributeList();
        SINGLETON_INSTANCE(AttributeList);

    public:
		// MG_CN_MODIFY
        //加载 AttributeList.csv 表。
        Bool                load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
        const AttrInfo*     getAttrInfo(ATTR_ID id);
        Bool                getAttrInfo(ATTR_ID id, const AttrInfo* info);
		std::vector<AttrInfo*>*
							getVectorAttrInfoByUseType(ATTR_USE_TYPE useType);
		std::vector<AttrInfo*>*
							getVectorAttrInfoByGroupId(UInt groupId);

	protected:
		const AttrInfo*		getAttrInfoByInitId(UInt initId);
		const AttrInfo*		getAttrInfoByAddId(UInt addId);

    private:
		void				setUseTypeAttrInfo(AttrInfo* info);
		void				setGroupIdAttrInfo(AttrInfo* info);
        void				clear();
		void				setInitAttrInfo(AttrInfo* info);
		void				setAddAttrInfo(AttrInfo* info);

    protected:
        std::map<ATTR_ID, AttrInfo*>							mMapAttrInfo;
		std::map<UInt, AttrInfo*>								mMapInitAttrInfo;
		std::map<UInt, AttrInfo*>								mMapAddAttrInfo;

		std::map<ATTR_USE_TYPE, std::vector<AttrInfo*>*>		mMapUseTypeAttrInfo;
		std::map<UInt, std::vector<AttrInfo*>*>					mMapGroupAttrInfo;

    };

}
//******************************************************************************************

#endif   //_H_ATTRIBUTELIST_