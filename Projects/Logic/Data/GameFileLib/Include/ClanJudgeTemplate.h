//************************************************************************************************************
#ifndef _H_CLAN_JUDGE_TEMPLATE_
#define _H_CLAN_JUDGE_TEMPLATE_
//************************************************************************************************************
#include "GameFilePreqs.h"
//************************************************************************************************************
namespace MG
{
    //��������                             ˵��
    //ClanJudgeId                          �����ж��ĵ���Id
    //LevelMin                             ����ȼ�����
    //LevelMax                             ����ȼ�����
    //NobilityLevelMin                     �����λ����
    //NobilityLevelMax                     �����λ����
    //QuestId                              ��Ҫ��ɵ������������id
    //DeedId                               ��Ҫ��ɵ�����ɾͣ����id
    //ItemTemplateId                       ������Ҫ���е���Ʒģ�棬���id
    //ItemNum                              ������Ʒģ�������������0��ʾ����Ҫ����
    //TimepieceId                          ���岻�ܾ߱�����ʱ�ļ�ʱ��id�����id
    //NeedStateId                          ������Ҫ�߱���״̬id�����id
    //NoneStateId                          ���岻�ܾ߱���״̬id�����id
    //Script                               ��������������ⲿ�ű���

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