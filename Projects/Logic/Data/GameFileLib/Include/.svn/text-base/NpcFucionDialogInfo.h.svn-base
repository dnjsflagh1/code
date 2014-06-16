//******************************************************************************************
#ifndef _NPCFUCIONDIALOGINFO_H_
#define _NPCFUCIONDIALOGINFO_H_
//******************************************************************************************
namespace MG
{
#define NPC_DIALOG_FUNCTION_ID_COUNT 8
	enum
	{
		npcfuctiondialoginfoid,
		npcfuctiondialoginfocharacterid,
		npcfuctiondialoginfofuction1,
		npcfuctiondialoginfofuction2,
		npcfuctiondialoginfofuction3,
		npcfuctiondialoginfofuction4,
		npcfuctiondialoginfofuction5,
		npcfuctiondialoginfofuction6,
		npcfuctiondialoginfofuction7,
		npcfuctiondialoginfofuction8,

	};
	
	///对应策划文档CharacterDialogue一条记录
	struct NpcFuncionDialogInfo
	{
		U32					id;				//id
		U32					characterTempId;//角色模板id
		U32					npcFuctionId[NPC_DIALOG_FUNCTION_ID_COUNT];

		NpcFuncionDialogInfo():id(0)
		{
			for (Int i = 0; i < NPC_DIALOG_FUNCTION_ID_COUNT; i++)
			{
				npcFuctionId[i] = 0;
			}
		}
	};
	
	///对应策划文档CharacterDialogue表
	class NpcFuncionDialogInfos                       
	{
	public:
		NpcFuncionDialogInfos();
		~NpcFuncionDialogInfos();
		 SINGLETON_INSTANCE(NpcFuncionDialogInfos);

	public:
		// MG_CN_MODIFY
		///加载 CharacterDialogue.csv 
		Bool                            load(Str16 fileName, IMGExternalPackManager* packManager = NULL);

		///根据ID获得  NpcFucionDialogInfo
		NpcFuncionDialogInfo*			getNpcFucionDialogInfo(U32 id);
		NpcFuncionDialogInfo*			getNpcFucionDialogInfobyCharacterTempId(U32 id);

	protected:
		void                            clear();

	private:
		std::map<U32, NpcFuncionDialogInfo*> mNpcFuctionDialogInfoMap;
	};

}
#endif //_NPCFUCIONDIALOGINFO_H_