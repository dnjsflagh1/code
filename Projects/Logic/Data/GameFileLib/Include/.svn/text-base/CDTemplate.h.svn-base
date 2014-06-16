
//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: CDTemplate.h
//        Author: xkc
//          Date: 2011-12-6
//          Time: 18:34
// Description: 
//			1.计时器模板表。
//
// modify History:
//      <author>    <time>        <descript>
//         xkc      2011-12-6      add

//////////////////////////////////////////////////////////////
//****************************************************************************************************
#ifndef _H_CDTTEMPLATE_
#define _H_CDTTEMPLATE_
//****************************************************************************************************
#include "GameFilePreqs.h"
//****************************************************************************************************
namespace MG
{
    //-------------------------------------------------------------------------------
    //序号	英文名	                中文名	        用途简述			                特殊取值	默认值	
    //1	    TimepieceId	            计时器id	    计时器的id，		                无	        无	
    //2	    TimepieceGroupId	    计时器分组id	计时器的分组id，相同表示为同一分组	无	        无
    //3	    UseType	                时间单位	    CD是否需要在服务端处理,单选	        "0～无意义,1服务器CD,2客户端CD"
    //4	    TimeType	            时间类型	    计时器的时间类型		            "0～无意义, 1～真实时间,2～在线时间"  2	
    //5	    SaveType	            存储类型	    计时器具体时间的存储类型	        "0～无意义,1～不存储,2～存储"无	
    //6	    SaveEntityType	        存储位置	    计时器具体时间的保存位置		    "0～无意义,1～角色和建筑,2～氏族,3～同盟,4～政区5～副本6后陆续添加"	无	
    //-------------------------------------------------------------------------------

    struct CDTempInfo
    {
        U32                     TimepieceId	                ;
        U32                     TimepieceGroupId            ;
        CDTEMP_USETYPE          UseType	                    ;
        CDTEMP_TIMETYPE         TimeType	                ;
        CDTEMP_SAVETYPE         SaveType	                ;
        CD_MASTER_TYPE          SaveEntityType	            ;             
    };

    //-------------------------------------------------------------------------------
    class  CDTemplate
    {
    public:
        CDTemplate(){;}
        ~CDTemplate();
        SINGLETON_INSTANCE(CDTemplate);

    public:
		// MG_CN_MODIFY
        //加载血脉模板表
        Bool                        load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
        //获得属性附加ID
        const CDTempInfo*           getCDTempInfo( U32 cdTempId );
        //获得属性附加ID
        Bool                        getCDTempInfo( U32 cdTempId, const CDTempInfo*& info );

    protected:
        void                        clear();

    protected:
        std::map<U32, CDTempInfo*> mCDTempInfoMap;

    };

}
//****************************************************************************************************
#endif  //_H_CDTTEMPLATE_

//****************************************************************************************************