	//************************************************************************************************************
#ifndef _H_MGPOINTER_
#define _H_MGPOINTER_
//************************************************************************************************************
#include "IPointer.h"
#include "IAny.h"
//************************************************************************************************************
namespace MG
{
    class MGPointer : public IPointer
    {
    public:
        MGPointer(){;}
        virtual ~MGPointer(){;}
        SINGLETON_INSTANCE(MGPointer);

    public:
		//根据状态设置鼠标
		virtual void					setPointer(Str8 name, MGPOINTER_LEVEL level = MGPOINTER_LEVEL_LOW);
		virtual void					setVisible( bool visible );
        virtual void                    resetToDefaultPointer();
		virtual void                    setImage(Str8 resName, Str8 groupName, Str8 itemName, IAny any, int num = 1);
        virtual IAny*                   getAnyData();

    public:
        virtual void					setDropEvent(PVOID_CALLBACK func);

    protected:
        //引擎事件
        void                    notifyDropEvent(MyGUI::PointerManager* pPointerManager);

    private:
        static      PVOID_CALLBACK              mDropEvent;


    };
}
//************************************************************************************************************
#endif
//************************************************************************************************************