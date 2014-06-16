//************************************************************************************************************
#ifndef _H_CLAN_JUDGE_TEMPLATE_
#define _H_CLAN_JUDGE_TEMPLATE_
//************************************************************************************************************
#include "GameFilePreqs.h"
//************************************************************************************************************
namespace MG
{
    //数据名称                             说明
    //ClanJudgeId                          氏族判定的调用Id
    //LevelMin                             氏族等级下限
    //LevelMax                             氏族等级上限
    //NobilityLevelMin                     氏族爵位下限
    //NobilityLevelMax                     氏族爵位上限
    //QuestId                              需要完成的氏族任务，外表id
    //DeedId                               需要完成的氏族成就，外表id
    //ItemTemplateId                       氏族需要持有的物品模版，外表id
    //ItemNum                              以上物品模版的消耗数量，0表示仅需要持有
    //TimepieceId                          氏族不能具备倒计时的计时器id，外表id
    //NeedStateId                          氏族需要具备的状态id，外表id
    //NoneStateId                          氏族不能具备的状态id，外表id
    //Script                               氏族其他需求的外部脚本名

    struct ClanJudgeInfo
    {
        U32         ClanJudgeId          ;
        U32         Level				 ;
        U32         NobilityLevel	     ;
        U32         QuestId              ;
        U32         DeedId               ;
        U32         ItemTemplateId       ;
        U32         ItemNum              ;
        U32         TimepieceId          ;
        U32         NeedStateId          ;
        U32         NoneStateId          ;
        Str16       Script               ;
    };

    //---------------------------------------------------------------------------------------------
    class ClanJudgeTemplate
    {
    public:
        ClanJudgeTemplate(){;}
        ~ClanJudgeTemplate();
        SINGLETON_INSTANCE(ClanJudgeTemplate);
    
    public:
		// MG_CN_MODIFY
        Bool                                    load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
        const ClanJudgeInfo*                    getClanJudgeInfo(U32 ClanJudgeId);

    private:
        void                                    clear();

    private:
        std::map<U32, ClanJudgeInfo*>           mMapClanJudgeInfo;

    };
}
//************************************************************************************************************
#endif
//************************************************************************************************************