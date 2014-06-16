//*****************************************************************************************************************
#ifndef _H_DEMIXLIST_ROW_
#define _H_DEMIXLIST_ROW_
//*****************************************************************************************************************
#include "IMixListRow.h"
#include "DEWidget.h"
//*****************************************************************************************************************
namespace MG
{
    class DEMixListRow : public IMixListRow, public DEWidget
    {
    public:
        DEMixListRow();
        virtual     ~DEMixListRow(){;}

    public:
        virtual IWidget*    getWidget();

        //���ӵ����ԡ�
        virtual void        setId(Int id);
        virtual void        setMixListRowName(Str16 name);
        virtual Int         getId();
        virtual Str16       getMixListRowName();
		virtual	Int			getIndex();

        //�����Ҫ�������͵Ŀؼ����ɼ�������
        virtual IButton*    getButton(Int index);
        virtual IImage*     getImage(Int index);
        virtual IText*      getText(Int index);
        virtual IWidget*    getChildWidget(Int index);

    public:
        Bool                        setEGMixListRow(MyGUI::Widget* p);
        MyGUI::MixListRow*          getEGMixListRow(){return mpEGMixListRow;}

    private:
        MyGUI::MixListRow*      mpEGMixListRow;

    };

}
//*****************************************************************************************************************
#endif
//*****************************************************************************************************************