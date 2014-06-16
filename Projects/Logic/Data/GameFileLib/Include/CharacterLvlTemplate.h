
//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: CharacterLvlTemplate.h
//        Author: xkc
//          Date: 2011-10-25
//          Time: 18:34
// Description: 
//			1.�ȼ�ģ���
//
// modify History:
//      <author>    <time>        <descript>
//         xkc      2011-10-25      add

//////////////////////////////////////////////////////////////
//******************************************************************************************
#ifndef _H_CHARACTERLVLBTEMPLATE_
#define _H_CHARACTERLVLBTEMPLATE_
//******************************************************************************************
#include "GameFilePreqs.h"
//******************************************************************************************
namespace MG
{
        //��������	        ����	    ����	Ӧ��	 ˵��
        //LevelId	        u int	    32	    ��/��	�ȼ�������id
        //LevelName	        string	    32	    ��	    �ȼ���������16�����ڣ����ڹ�λ��
        //UseType	        u int	    32	    ��/��	"�ȼ������÷��࣬ͳһ�����ʾ����һ����������"
        //UpToLvl	        u int	    32	    ��/��	Ҫ�����ĵȼ�
        //SpendExp	        u int	    32	    ��/��	���������ϵȼ���Ҫ���ѵľ���
        //OpenType	        int	        4	    ��/��	�������ϵȼ��Ƿ񿪷�
        //NeedLevel	        u int	    32	    ��/��	���������ϵȼ���Ҫ��Ŀ��ȼ�
        //QuestId	        u int	    32	    ��/��	�������˵ȼ���ɵ�����Id
        //ExploitId	        u int	    32	    ��/��	�������˵ȼ���Ҫ��ɵĳɾ�Id
    
    //-------------------------------------------------------------------------------------------
    struct CharLvlInfo
    {
        U32                LevelId			;                 //�ȼ�������id

        Str16              LevelName		;                 //�ȼ���������16�����ڣ����ڹ�λ��

        CHAR_LVL_USETYPE   UseType			;                 //"�ȼ������÷��࣬ͳһ�����ʾ����һ����������"
        U32                UpToLvl			;                 //Ҫ�����ĵȼ�
        U32                SpendExp			;                 //���������ϵȼ���Ҫ���ѵľ���
        U32                ClanJudgeid	    ;                 //�������˵ȼ���ɵ�����Id
        U32                CharacterJudgeid	;                 //�������˵ȼ���Ҫ��ɵĳɾ�Id
    };
    //-------------------------------------------------------------------------------------------
    class   CharacterLvlTemplate
    {
    public:
        CharacterLvlTemplate();
        ~CharacterLvlTemplate();
        SINGLETON_INSTANCE(CharacterLvlTemplate);

    public:
		// MG_CN_MODIFY
        //����CharacterLvlTemplate��csv
        Bool load(Str16 filename, IMGExternalPackManager* packManager = NULL);
        
		const CharLvlInfo* getCharLvlInfo(CHAR_LVL_USETYPE type,  U32 lvl);

    private:
        void clear();
		void setCharLvlInfo(CharLvlInfo* pInfo);
		

    private:
        std::map<U32, CharLvlInfo*> mMapCharLvlInfo;
		std::map<U32, std::map<U32, CharLvlInfo*>> mMapTypeLvlCharLvlInfo;
    };
}
//******************************************************************************************
#endif  // _H_CHARACTERLVLBTEMPLATE_
//******************************************************************************************