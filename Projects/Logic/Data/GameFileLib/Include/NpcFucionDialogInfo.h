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
	
	///��Ӧ�߻��ĵ�CharacterDialogueһ����¼
	struct NpcFuncionDialogInfo
	{
		U32					id;				//id
		U32					characterTempId;//��ɫģ��id
		U32					npcFuctionId[NPC_DIALOG_FUNCTION_ID_COUNT];

		NpcFuncionDialogInfo():id(0)
		{
			for (Int i = 0; i < NPC_DIALOG_FUNCTION_ID_COUNT; i++)
			{
				npcFuctionId[i] = 0;
			}
		}
	};
	
	///��Ӧ�߻��ĵ�CharacterDialogue��
	class NpcFuncionDialogInfos                       
	{
	public:
		NpcFuncionDialogInfos();
		~NpcFuncionDialogInfos();
		 SINGLETON_INSTANCE(NpcFuncionDialogInfos);

	public:
		// MG_CN_MODIFY
		///���� CharacterDialogue.csv 
		Bool                            load(Str16 fileName, IMGExternalPackManager* packManager = NULL);

		///����ID���  NpcFucionDialogInfo
		NpcFuncionDialogInfo*			getNpcFucionDialogInfo(U32 id);
		NpcFuncionDialogInfo*			getNpcFucionDialogInfobyCharacterTempId(U32 id);

	protected:
		void                            clear();

	private:
		std::map<U32, NpcFuncionDialogInfo*> mNpcFuctionDialogInfoMap;
	};

}
#endif //_NPCFUCIONDIALOGINFO_H_