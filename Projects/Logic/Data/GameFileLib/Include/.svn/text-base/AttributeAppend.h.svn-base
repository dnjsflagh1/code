
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
#ifndef _H_ATTRIBUTEAPPEND_
#define _H_ATTRIBUTEAPPEND_
//******************************************************************************************
#include "GameFilePreqs.h"
//******************************************************************************************

//******************************************************************************************
namespace MG
{
        //数据名称	        类型	长度	应用	说明
        //AbilityAppendId	u int	32	    客/服	通用非战斗属性附加的id
        //Notes	            string	32	    None	策划备注，16个汉字以内
        //GroupAppendId	    u int	32	    客/服	附加抽取分组，用于在一组属性内随机抽取
        //GroupAppendName	string	16	    客	    附加后追加的名字，8汉字以内
        //AppendType	     int	4	    客/服	"属性附加类型，只有两种。
        //AbilityListId1	u int	32	    客/服	附加的属性1
        //Num1	            int	    32	    客/服	属性1附加的数值，可为负
        //AbilityListId2	u int	32	    客/服	附加的属性2
        //Num2	            int	    32	    客/服	属性2附加的数值，可为负
        //AbilityListId3	u int	32	    客/服	附加的属性3
        //Num3	            int	    32	    客/服	属性3附加的数值，可为负
        //AbilityListId4	u int	32	    客/服	附加的属性4
        //Num4	            int 	32	    客/服	属性4附加的数值，可为负
        //AbilityListId5	u int	32	    客/服	附加的属性5
        //Num5	            int	    32	    客/服	属性5附加的数值，可为负
        //AbilityListId6	u int	32	    客/服	附加的属性6
        //Num6	            int	    32	    客/服	属性6附加的数值，可为负
        //AbilityListId7	u int	32	    客/服	附加的属性7
        //Num7	            int	    32	    客/服	属性7附加的数值，可为负
        //AbilityListId8	u int	32	    客/服	附加的属性8
        //Num8	            int	    32	    客/服	属性8附加的数值，可为负
        //AbilityListId9	u int	32	    客/服	附加的属性9
        //Num9	            int	    32	    客/服	属性9附加的数值，可为负
        //AbilityListId10	u int	32	    客/服	附加的属性10
        //Num10	            int	    32	    客/服	属性10附加的数值，可为负


    //-----------------------------------------------------------------------------
    enum APPEND_TYPE
    {
        APPEND_TYPE_NULL,

        APPEND_TYPE_REAL,                //实数附加
        APPEND_TYPE_LEVEL,               //等级附加

        APPEND_TYPE_MAX
    };
    //-----------------------------------------------------------------------------
    struct AttributeAppendInfo
    {
        U32             AbilityAppendId                                 ; //通用非战斗属性附加的id
        U32             GroupAppendId	                                ; //附加抽取分组，用于在一组属性内随机抽取

        Str16           GroupAppendName                                 ; //附加后追加的名字，8汉字以内

        APPEND_TYPE     AppendType	                                    ; //附加类型
        AppendAttr      AppendAttrList[APPENDATTR_NUM]                  ; //附加属性表
    };

    //-----------------------------------------------------------------------------
    class  AttributeAppend;
    //-----------------------------------------------------------------------------
    struct  AttributeGroupInfo
    {
        friend AttributeAppend;
        std::map<U32, AttributeAppendInfo*> mAttrAppendInfoMap; //群Id对应的属性附加表
    public:
        //根据群ID获得一个随机的附加属性表
        Bool                        getRandAttributeAppendInfo(const AttributeAppendInfo*& info);
        const AttributeAppendInfo*   getRandAttributeAppendInfo();
    protected:
        //添加附加属性表
        void                        addAttributeAppendInfo(AttributeAppendInfo* info);
    };

    //-----------------------------------------------------------------------------
    class AttributeAppend
    {
        friend AttributeGroupInfo;
    public:
        AttributeAppend();
        ~AttributeAppend();
        SINGLETON_INSTANCE(AttributeAppend);

    public:
		// MG_CN_MODIFY
        //加载AttributeAppend.csv表
        Bool                        load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
        //根据ID获得附加属性表
        Bool                        getAttributeAppendInfo(U32, const AttributeAppendInfo*& info);
        const AttributeAppendInfo*  getAttributeAppendInfo(U32);
        //根据群ID获得一个随机的附加属性表
        Bool                        getRandAttributeAppendInfo(U32 id, const AttributeAppendInfo*& info);
        const AttributeAppendInfo*  getRandAttributeAppendInfo(U32 id);
         
    protected:
        void clear();
        //加附加属性表到群组中
        void                        addAttributeAppendInfoToGroup( AttributeAppendInfo* info );
		void						setAttributeId(AttributeAppendInfo* pInfo);

    public:
        typedef std::map<U32, AttributeGroupInfo*>       AttributeGroupInfoMap;
        typedef AttributeGroupInfoMap::iterator          AttributeGroupInfoMapIter;  
        typedef std::map<U32, AttributeAppendInfo*>      AttributeAppendInfoMap;
        typedef AttributeAppendInfoMap::iterator         AttributeAppendInfoMapIter;

    private:
        AttributeAppendInfoMap                           mAttributeAppendInfoMap;
        AttributeGroupInfoMap                            mAttributeGroupInfoMap;

    };

}
//******************************************************************************************
#endif
//******************************************************************************************