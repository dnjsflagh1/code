//**********************************************************************************************************
#ifndef _H_DEICON_
#define _H_DEICON_
//**********************************************************************************************************
#include "EnginePreqs.h"
#include "IIcon.h"
#include "DEWidget.h"
//**********************************************************************************************************
class  MyGUI::Widget;
class  MyGUI::Icon;
//**********************************************************************************************************
namespace MG
{
    class  DEIcon : public IIcon, public DEWidget
    {
    public:
                            DEIcon();
        virtual             ~DEIcon();
    public:
        virtual IWidget*    getWidget();
        //设置texture
        virtual void        setTexture(const Str8& name);
        virtual void        setTexture(const Str8& resname, const Str8& groupname, const Str8& itemname);
        virtual bool        setItemResource(const std::string& _name);
        virtual void        setItemGroup(const std::string& _value);
        virtual void        setItemName(const std::string& _value);

    public://事件
        virtual void        setEventStartDrag(PVOIDBOOLREF_CALLBACK pFunc);
        virtual void        setEventRequestDrop(PVOIDPVOIDBOOLREF_CALLBACK pFunc);
        virtual void        setEventDropResult(PVOIDPVOIDBOOL_CALLBACK pFunc);
        virtual void        setEventChangeDDState(PVOIDBYTE_CALLBACK pFunc);
        virtual void        setRequestDragWidgetInfo(PVOIDPVOIDREFRECTREF_CALLBACK pFunc);


    public: 
        //引擎事件
        Bool                setEGIcon(MyGUI::Widget* p);
        MyGUI::Widget*      getEGIcon(){return mpEGIcon;}

    protected:
        void        notifyEventStartDrag(MyGUI::Icon* _sender, const MyGUI::DDIconInfo& _info, bool& _result);
        void        notifyEventRequestDrop(MyGUI::Icon* _sender, const MyGUI::DDIconInfo& _info, bool& _result);
        void        notifyEventDropResult(MyGUI::Icon* _sender, const MyGUI::DDIconInfo& _info, bool _result);
        void        notifyEventChangeDDState(MyGUI::Icon* _sender, MyGUI::DDItemState _state);
        void        notifyRequestDragWidgetInfo(MyGUI::Icon* _sender, MyGUI::Widget*& _item, MyGUI::IntCoord& _dimension);
                
    protected:
        static std::map<MyGUI::Icon*, PVOIDBOOLREF_CALLBACK>               mMapEventStartDrag;
        static std::map<MyGUI::Icon*, PVOIDPVOIDBOOLREF_CALLBACK>          mMapEventRequestDrop;
        static std::map<MyGUI::Icon*, PVOIDPVOIDBOOL_CALLBACK>             mMapEventDropResult;
        static std::map<MyGUI::Icon*, PVOIDBYTE_CALLBACK>                  mMapEventChangeDDState;
        static std::map<MyGUI::Icon*, PVOIDPVOIDREFRECTREF_CALLBACK>       mMapRequestDragWidgetInfo;


    protected:
        typedef void (*ICON_CALLBACK)(MyGUI::Icon* _sender, MyGUI::Widget*& _item, MyGUI::IntCoord& _dimension);

    protected:
    private:
        
        MyGUI::Icon*                                            mpEGIcon;
        DEImage*                                                mDragImage;
        DEText*                                                 mDragText;
        ICON_DRAG_TYPE                                          mIconDragType;

    };   //DEICON
}   //MG

#endif  //_H_DEICON_