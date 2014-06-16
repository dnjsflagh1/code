//***************************************************************************************************
#ifndef _H_UICLANROLECONTROL_
#define _H_UICLANROLECONTROL_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//***************************************************************************************************
namespace MG
{
    //--------------------------------------------------------------------------
    class CPlayerCharacter;
    //--------------------------------------------------------------------------
    class UIClanRoleControl  : public UIObject
    {
    public:
        UIClanRoleControl();
        ~UIClanRoleControl();
        SINGLETON_INSTANCE(UIClanRoleControl);

    public:
        virtual void setEvent();

    public:
        //���յ��佫��Ϣ�� �����佫��ʾ��Ϣ
        void updateGenrealInfo(CPlayerCharacter* pCharacter);
        //�ӽ�ɫlist��
        void addCharacterList();
        //�ӽ�ɫ
        void addCharacter(CPlayerCharacter* pCharacter);
        //ɾ����ɫ
        void deleteCharacer(CPlayerCharacter* pCharacter);

    protected:  //�¼�
        static void onClickGenreal(void* widget, Int index);
        static void onClickGenrealEquip(void* widget);
        static void onClickGenrealSkill(void* widget);
        static void onClickGenrealFeats(void* widget);
        static void onSelectComboboxItem(void* widget, Int index);

    protected:
        void setGenrealInfo(Int index);
    private:
        U32 mCurSelectIndex;
    };
}
//***************************************************************************************************
#endif
//***************************************************************************************************