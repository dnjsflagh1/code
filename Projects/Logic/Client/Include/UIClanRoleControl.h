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
        //当收到武将消息， 更新武将显示消息
        void updateGenrealInfo(CPlayerCharacter* pCharacter);
        //加角色list。
        void addCharacterList();
        //加角色
        void addCharacter(CPlayerCharacter* pCharacter);
        //删除角色
        void deleteCharacer(CPlayerCharacter* pCharacter);

    protected:  //事件
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