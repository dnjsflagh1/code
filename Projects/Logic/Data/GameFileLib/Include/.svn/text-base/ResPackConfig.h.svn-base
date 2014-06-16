//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: ResPackConfig.h
//        Author: xvyadong
//          Date: 2012-2-9
//          Time: 15:15
// Description: 
//			1.读取资源表分包配置
//
// modify History:
//      <author>    <time>        <descript>
//      xvyadong    2012-2-9      add
//////////////////////////////////////////////////////////////
//***********************************************************************************************
#ifndef _H_RES_PACK_CONFIG
#define _H_RES_PACK_CONFIG
//***********************************************************************************************
#include "GameFilePreqs.h"
//***********************************************************************************************
namespace MG
{
	//----------------------------------------------------------------------
	enum                  
	{
		RES_PACK_BASE = 0,					   //基础包

		RES_PACK_SECTION,					   //阶段包
		RES_PACK_DLC,						   //资料包
		RES_PACK_PATCH,						   //补丁包

		RES_PACK_MAX
	};
	//----------------------------------------------------------------------

	//ResPack_Id	序列id
	//Notes	        策划备注
	//Name	        分包名
	//Pack_Type	    分包类型
	//Path			分包路径

	//--------------------------------------------------------------------------
	struct ResPackInfo
	{
		U32             ResPackId			;
		U8				ResPackType			;
		Str8			ResPackDescription	;
		Str8            ResPackName		    ;
		Str8            ResPackPath			;
	};
	//--------------------------------------------------------------------------
	class ResPackConfig
	{
	public:
		ResPackConfig(){;}
		~ResPackConfig();
		SINGLETON_INSTANCE(ResPackConfig);

	public:

		Bool                    load(Str16 fileName);
		const ResPackInfo*		getResPackInfo(U32 pack_id);

	private:

		void                    clear();

	private:

		std::map<U32, ResPackInfo*>  mResPackInfoList;

	};
}
//***********************************************************************************************
#endif
//***********************************************************************************************