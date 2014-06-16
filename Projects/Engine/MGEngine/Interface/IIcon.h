//**********************************************************************************************************
#ifndef _H_IICON_
#define _H_IICON_
//**********************************************************************************************************
#include "MGEngineInterfacePreqs.h"
#include "IWidget.h"
#include "IAny.h"
//**********************************************************************************************************
//Icon�ӿ�
namespace MG
{
    enum  ICON_DRAG_TYPE
    {
        ICON_DRAG_TYPE_NULL,

        ICON_DRAG_TYPE_IMAGE,
        ICON_DRAG_TYPE_TEXT,

        ICON_DRAG_TYPE_MAX
    };

    class IIcon
    {
    public:
        //��ÿؼ��Ĺ�ͬ���Բ��֡�
        virtual IWidget*    getWidget() = 0;

        //����texture
        virtual void  setTexture(const Str8& name) = 0;
        //����texture
        virtual void  setTexture(const Str8& resname, const Str8& groupname, const Str8& itemname) = 0;
        //����texture����Դ��
        virtual bool setItemResource(const std::string& _name) = 0;
        //����ȡ�Ǹ�Ⱥ����Դ
        virtual void setItemGroup(const std::string& _value) = 0;
        //����ȡ�������Դ
        virtual void setItemName(const std::string& _value) =0;

    public://�¼�
        /*event:*/
        /** Event : request for start drag
        signature : void method(MyGUI::Icon* _sender, const MyGUI::DDIconInfo& _info, bool& _result)
        @param _sender widget that called this event
        @param _info information about DDContainers
        @param _result write here true if container can be draggedor false if it can't
        */
        virtual void setEventStartDrag(PVOIDBOOLREF_CALLBACK) = 0;
        
        /** Event : request for start drag (moving mouse over container, but not dropped yet)
        signature : void method(MyGUI::Icon* _sender, const MyGUI::DDIconInfo& _info, bool& _result)
        @param _sender widget that called this event
        @param _info information about DDContainers
        @param _result write here true if container accept dragged widget or false if it isn't
        */
        virtual void  setEventRequestDrop(PVOIDPVOIDBOOLREF_CALLBACK) = 0;

        /** Event : end drag (drop)
        signature : void method(MyGUI::Icon* _sender, const MyGUI::DDIconInfo& _info, bool _result)
        @param _sender widget that called this event
        @param _info information about DDContainers
        @param _result if true then drop was successfull
        */
        virtual void setEventDropResult(PVOIDPVOIDBOOL_CALLBACK) = 0;

        /** Event : drag'n'drop state changed
        signature : void method(MyGUI::Icon* _sender, MyGUI::DDItemState _state)
        @param _sender widget that called this event
        @param _state new state
        */
        virtual void setEventChangeDDState(PVOIDBYTE_CALLBACK) = 0;

        /** Event : [not used] request widget for dragging
        signature : void method(MyGUI::Icon* _sender, MyGUI::Widget*& _item, MyGUI::IntCoord& _dimension)
        @param _sender widget that called this event
        @param _item write widget pointer here
        @param _dimension write widget coordinate here
        */
        virtual void setRequestDragWidgetInfo(PVOIDPVOIDREFRECTREF_CALLBACK) = 0;
        
    protected:
    private:
    };
}

//**********************************************************************************************************
#endif
//**********************************************************************************************************