
//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: AttributeList.h
//        Author: xkc
//          Date: 2011-10-25
//          Time: 18:34
// Description: 
//			1.血脉模板表。
//
// modify History:
//      <author>    <time>        <descript>
//         xkc      2011-10-25      add

//////////////////////////////////////////////////////////////
//******************************************************************************************
#ifndef _H_LINEAGETEMPLATE_
#define _H_LINEAGETEMPLATE_
//******************************************************************************************

//-------------------------------------------------------------------------------
namespace MG
{
	struct LineageInfo
	{
		UInt        lineageID;                       // 血脉id

		Str16       lineageName;                     // 血脉名，6汉字内，如：轩辕。
		Str16       lineageText;                     // 血脉的介绍文字，64汉字内，不允许为空。
		Str8        artIconRes;                      // 血脉的图标，从图标资源表获得.

		UInt        abilityGroupAppendId;            // 提供的属性加成，从属性分组附加表获得
	};

    class  LineageTemplate
    {
    public:
        LineageTemplate();
        ~LineageTemplate();
        SINGLETON_INSTANCE(LineageTemplate);

    public:
		// MG_CN_MODIFY
        //加载血脉模板表
        Bool                        load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
        //获得属性附加ID
        const LineageInfo*          getLineageInfo( U32 lineageId );
        //获得属性附加ID
        Bool                        getLineageInfo( U32 lineageId, const LineageInfo*& info );

    protected:
        void                        clear();

    protected:
        std::map<U32, LineageInfo*> mLineageInfoMap;

    };
}
#endif