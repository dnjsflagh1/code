//************************************************************************************************
#ifndef _H_IPOINTER_
#define _H_IPOINTER_
//************************************************************************************************
#include "MGEngineInterfacePreqs.h"
//************************************************************************************************
namespace MG
{
    class IPointer
    {
    public:
		//根据状态设置鼠标
		virtual void					setPointer(Str8 name, MGPOINTER_LEVEL level = MGPOINTER_LEVEL_LOW) = 0;
        /** Reset to default pointer */
        virtual void                    resetToDefaultPointer() = 0;
        //将技能图片，道具图片设为鼠标图片
        virtual void                    setImage(Str8 resName, Str8 groupName, Str8 itemName, IAny any, int num = 1) = 0;
        //获得附加信息。
        virtual IAny*                   getAnyData() = 0;
        //添加一个丢弃的事件函数
        virtual void                    setDropEvent(PVOID_CALLBACK func) = 0;
		//鼠标的显示丢弃
		virtual void					setVisible( bool visible ) = 0;

    };
}

//************************************************************************************************
#endif
//************************************************************************************************