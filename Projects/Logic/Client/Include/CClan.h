/******************************************************************************/
#ifndef _CCLAN_H_
#define _CCLAN_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "Singleton.h"
#include "Clan.h"
#include "CPlayerCharacter.h"
#include "GeneralRecruitNetPacket.h"

/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //�������
    //��Ҫ��������µĽ�ɫ
    /******************************************************************************/
    class CClan : public Clan
    {
    public:
        CClan();
        virtual	~CClan();

    public:

        void                    init(ClanData* pData);

        void                    setOtherInfo();
        CCharacter*             getCharacter(IdType id, GAMEOBJ_TYPE type);
        
    public:

        //����һ����ҽ�ɫ
        CPlayerCharacter*		addPlayerCharacter( PlayerCharacterData* pData, Bool& isFirst );
		//�ж��Ƿ����һ����ҽ�ɫ
		Bool					hasPlayerCharacter( U64 id );
        //�õ�һ����ҽ�ɫ
        CPlayerCharacter*		getPlayerCharacter( U64 id );
        //�Ƴ�һ����ҽ�ɫ
        void					removePlayerCharacter( U64 id );
        //�Ƴ�������ҽ�ɫ
        void					removeAllPlayerCharacter();
        //��Ľ�ɫ������
        U32                     getPlayerCharacterNum(){return mPlayerCharacterList.size();}
        ////����Index��ý�ɫ
        //CPlayerCharacter*       getPlayerCharacterByIndex(U32 index);
		
		CPlayerCharacter*		getMainGenreal();
		void					setMainPlayerCharacter(CPlayerCharacter* playerCharacter);
		std::map<U64, CPlayerCharacter*>*	getPlayerCharacterList()  { return &mPlayerCharacterList; }		

#if 0
	public:	//��ļ���佫
		void								clearRecruitGeneralList();
		void								loadRecruitGeneralInfo(NetRecuitGeneralInfo* generalInfo);
        std::map<U64, CPlayerCharacter*>*	getRecruitGeneralList();
#endif
    private:

        //��ҽ�ɫ�б�
        std::map<U64, CPlayerCharacter*>	mPlayerCharacterList;

		CPlayerCharacter*					mMainPlayerCharacter;
#if 0
		//����ļ���佫�б�
		std::map<U64, CPlayerCharacter*>	mRecruitGeneralList;
#endif

    };
}
#endif
