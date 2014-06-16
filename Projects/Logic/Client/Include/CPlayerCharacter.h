/******************************************************************************/
#ifndef _CCHARACTER_H_
#define _CCHARACTER_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "CCharacter.h"

/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //��ҿ��ƵĽ�ɫ
    //ֻ���߼���أ�����ʾ�޹�
    /******************************************************************************/
    class CPlayerCharacter : public CCharacter
	{
	public:
		CPlayerCharacter();
		virtual ~CPlayerCharacter();

    public:
        PlayerCharacterData*            getData();
		Str16							getNormalName();		//��+��

    ///----------------------------------------------------------------------------------------------
    /// ���Լ������
    public:
        //���Լ���ʱ����á�
        virtual void                        setHp(Int val);
        virtual void                        setMp(Int val);
        virtual void                        setSp(Int val);

    protected:
        //���Լ���ʱ����á�
        virtual Flt                         getDBAttrInit(UInt index);
        virtual Flt                         getDBAttrLvlAdd(UInt index);
        // ������������
        virtual void                        calOtherAttr();
		virtual UInt						getDBAttrInitID();
		virtual UInt						getDBAttrLvlAddID();

    /// ���Լ������ -- end
    ///----------------------------------------------------------------------------------------------

    public:
        void                                init(PlayerCharacterData* pData);
		void								unInit();

		U32				getExp();

	};
}

#endif