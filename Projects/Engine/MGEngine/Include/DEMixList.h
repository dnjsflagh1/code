//*****************************************************************************************************************
#ifndef _H_DEMIXLIST_
#define _H_DEMIXLIST_
//*****************************************************************************************************************
#include "IMixList.h"
#include "DEWidget.h"
//*****************************************************************************************************************
namespace MG
{
    class DEMixList : public IMixList, public DEWidget
    {
    public:
        DEMixList();
        virtual                 ~DEMixList(){;}

    public:
        virtual IWidget*        getWidget();

        virtual IMixListRow*    getMixListRow(int _id);
        virtual IMixListRow*    getMixListRowByIndex(int _index);
        virtual IMixListRow*    getMixListRow(std::wstring _name);
        virtual IMixListRow*    getMixListRow(int _id, std::wstring _name);
        virtual IMixListRow*    addLine(int _id, std::wstring _name);
        virtual void            removeLine(int _id);
        virtual void            removeLine(std::wstring _name);
        virtual void            removeAllLine();
        virtual Int             getMixLixRowCount();
		virtual void			setSelectIndex(int index);
		virtual Int				getSelectIndex();

    public:
        Bool                    setEGMixList(MyGUI::Widget* p);
        MyGUI::MixList*         getEGMixList(){return mpEGMixList;}

    public:
        virtual void            setClickMixListRow(PVOIDINT_CALLBACK func);
        virtual void            setDoubleClickMixListRow(PVOIDINT_CALLBACK func);

    private:
        void                    notifyMouseButtonClick(MyGUI::MixList* p, int index);
        void                    notifyMouseButtonDoubleClick(MyGUI::MixList* p, int index);

    private:
        MyGUI::MixList*         mpEGMixList;
        static std::map<MyGUI::MixList*, PVOIDINT_CALLBACK>                      mMapClickCallBack;
        static std::map<MyGUI::MixList*, PVOIDINT_CALLBACK>                      mMapDoubleClickCallBack;

    };
}
//*****************************************************************************************************************
#endif
//*****************************************************************************************************************