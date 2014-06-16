//*****************************************************************************************************************
#ifndef _H_IMIXLIST_ROW_
#define _H_IMIXLIST_ROW_
//*****************************************************************************************************************
#include "MGEngineInterfacePreqs.h"
//*****************************************************************************************************************
namespace MG
{
    class IMixListRow
    {
    public:
        virtual IWidget*    getWidget() = 0;

        //���ӵ����ԡ�
        virtual void        setId(Int id) = 0;
        virtual void        setMixListRowName(Str16 name) = 0;
        virtual Int         getId() = 0;
        virtual Str16       getMixListRowName() = 0;
		virtual	Int			getIndex() = 0;
        

        //�����Ҫ�������͵Ŀؼ����ɼ�������
        virtual IButton*    getButton(Int index) = 0;
        virtual IImage*     getImage(Int index) = 0;
        virtual IText*      getText(Int index) = 0;
        virtual IWidget*    getChildWidget(Int index) = 0;

    };
}

//*****************************************************************************************************************
#endif
//*****************************************************************************************************************