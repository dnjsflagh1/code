//******************************************************************************************
#ifndef _NPCFUCTIONINFO_H_
#define _NPCFUCTIONINFO_H_
//******************************************************************************************
namespace MG
{
#define NPC_FUCTION_INFO_IOCNRES_MAX_LEN	64
#define NPC_FUCTION_INFO_DESC_MAX_LEN		64
#define NPC_FUCTION_INFO_PARAM4_MAX_LEN		64

    enum  NPC_FUCTION_TYPE
    {
		NPC_FUCTION_TYPE_NULL					= 0,
        NPC_FUCTION_TYPE_CLAN_QUEST				= 1,
		NPC_FUCTION_TYPE_JUMPMAP				= 2, 
		NPC_FUCTION_TYPE_ITEMSHOP				= 3,
		NPC_FUCTION_TYPE_CLAN_STORAGE			= 4,
		NPC_FUCTION_TYPE_GENERAL_RECRUIRED		= 5,
		NPC_FUCTION_TYPE_CHANGE_FIGHTED_GENERAL = 6,
		NPC_FUCTION_TYPE_PVP_BATTLE				= 7,
		NPC_FUCTION_TYPE_PVE_BATTLE				= 8,
    };
	enum
	{
		npcfunctioninfoid,
		npcfunctioninfoartiocnres = 2,  //过滤掉Note字段
		npcfunctioninfodesc,
		npcfunctioninfotype,
		npcfunctioninfoparam1,
		npcfunctioninfoparam2,
		npcfunctioninfoparam3,
		npcfunctioninfoparam4,
	};
    //-----------------------------------------------------------------------
	//对应策划文档DialogueFunctionList一条记录
    struct NpcFunctionInfo
    {
		U32					id;
		U32					artIocnResId;
		Str16				desc;	
		NPC_FUCTION_TYPE	type;
		Int					param1;
		Int					param2;
		Int					param3;
		Str16				param4;
		NpcFunctionInfo():id(0)
			,artIocnResId(0)
			,type(NPC_FUCTION_TYPE_NULL)
			,param1(0)
			,param2(0)
			,param3(0)
		{
			desc.resize(NPC_FUCTION_INFO_DESC_MAX_LEN);
			param4.resize(NPC_FUCTION_INFO_PARAM4_MAX_LEN);
		}
    };
    //-----------------------------------------------------------------------
	//对应策划文档DialogueFunctionList表
    class NpcFunctionInfos                       
    {
    public:
        NpcFunctionInfos();
        ~NpcFunctionInfos();
        SINGLETON_INSTANCE(NpcFunctionInfos);

    public:
        ///加载 DialogueFunctionList.csv 
		// MG_CN_MODIFY
        Bool                            load(Str16 fileName, IMGExternalPackManager* packManager = NULL);

        //根据ID获得  NpcFuctionInfo
        NpcFunctionInfo*					getNpcFuctionInfo(U32 id);

    protected:
        void                            clear();

    private:
        std::map<U32, NpcFunctionInfo*> mNpcFuctionInfoMap;

    };
}
//******************************************************************************************
#endif  // _H_JOBTEMPLATE_
//******************************************************************************************