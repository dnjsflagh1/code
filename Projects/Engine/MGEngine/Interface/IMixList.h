//*****************************************************************************************************************
#ifndef _H_IMIXLIST_
#define _H_IMIXLIST_
//*****************************************************************************************************************
#include "MGEngineInterfacePreqs.h"
#include "IWidget.h"
//*****************************************************************************************************************
namespace MG
{
    class IMixList
    {
    public:
        virtual IWidget*        getWidget() = 0;

        virtual IMixListRow*    getMixListRow(int _id) = 0;
        virtual IMixListRow*    getMixListRowByIndex(int _index) = 0;
        virtual IMixListRow*    getMixListRow(std::wstring _name) = 0;
        virtual IMixListRow*    getMixListRow(int _id, std::wstring _name) = 0;
        virtual IMixListRow*    addLine(int _id, std::wstring _name) = 0;
        virtual void            removeLine(int _id) = 0;
        virtual void            removeLine(std::wstring _name) =0 ;
        virtual void            removeAllLine() = 0;
        virtual Int             getMixLixRowCount() = 0;
		virtual void			setSelectIndex(int index) = 0;
		virtual Int				getSelectIndex() = 0;

        virtual void            setClickMixListRow(PVOIDINT_CALLBACK func) = 0;
        virtual void            setDoubleClickMixListRow(PVOIDINT_CALLBACK func) = 0;

    };
}
//*****************************************************************************************************************
#endif
//*****************************************************************************************************************