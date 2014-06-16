//**********************************************************************************************************
#include "stdafx.h"
#include "DEIcon.h"
#include "GuiDelegateElementPool.h"
#include "DEImage.h"
#include "DEText.h"
#include "GuiElempoolEx.h"
//**********************************************************************************************************
namespace MG
{
    std::map<MyGUI::Icon*, PVOIDBOOLREF_CALLBACK>  DEIcon::mMapEventStartDrag;
    std::map<MyGUI::Icon*, PVOIDPVOIDBOOLREF_CALLBACK> DEIcon::mMapEventRequestDrop;
    std::map<MyGUI::Icon*, PVOIDPVOIDBOOL_CALLBACK>  DEIcon::mMapEventDropResult;
    std::map<MyGUI::Icon*, PVOIDBYTE_CALLBACK>  DEIcon::mMapEventChangeDDState;
    std::map<MyGUI::Icon*, PVOIDPVOIDREFRECTREF_CALLBACK> DEIcon::mMapRequestDragWidgetInfo;

    DEIcon::DEIcon()
        :mpEGIcon(nullptr)
        ,mDragImage(NULL)
        ,mDragText(NULL)
        ,mIconDragType(ICON_DRAG_TYPE_NULL)
    {

    }
    //-------------------------------------------------------------------------------------
    DEIcon::~DEIcon()
    {

    }
    //-------------------------------------------------------------------------------------
    IWidget* DEIcon::getWidget()
    {
       assert(mpEGIcon);
       setEGWidget(mpEGIcon);
       return this;
    }
    //-------------------------------------------------------------------------------------
    void DEIcon::setEventStartDrag( PVOIDBOOLREF_CALLBACK pFunc )
    {
        assert(mpEGIcon);
        assert(pFunc);
        mMapEventStartDrag[mpEGIcon] = pFunc;
        mpEGIcon->eventStartDrag = MyGUI::newDelegate(this, &DEIcon::notifyEventStartDrag);
    }
    //-------------------------------------------------------------------------------------
    void DEIcon::setEventRequestDrop( PVOIDPVOIDBOOLREF_CALLBACK pFunc )
    {
        assert(mpEGIcon);
        assert(pFunc);
        mMapEventRequestDrop[mpEGIcon] = pFunc;
        mpEGIcon->eventRequestDrop = MyGUI::newDelegate(this, &DEIcon::notifyEventRequestDrop);
    }
    //-------------------------------------------------------------------------------------
    void DEIcon::setEventDropResult( PVOIDPVOIDBOOL_CALLBACK pFunc )
    {
        assert(mpEGIcon);
        assert(pFunc);
        mMapEventDropResult[mpEGIcon] = pFunc;
        mpEGIcon->eventDropResult = MyGUI::newDelegate(this, &DEIcon::notifyEventDropResult);
    }
    //-------------------------------------------------------------------------------------
    void DEIcon::setEventChangeDDState( PVOIDBYTE_CALLBACK pFunc )
    {
        assert(mpEGIcon);
        assert(pFunc);
        mMapEventChangeDDState[mpEGIcon] = pFunc;
        mpEGIcon->eventChangeDDState = MyGUI::newDelegate(this, &DEIcon::notifyEventChangeDDState);
    }
    //-------------------------------------------------------------------------------------
    void DEIcon::setRequestDragWidgetInfo(PVOIDPVOIDREFRECTREF_CALLBACK pFunc)
    {
        assert(mpEGIcon);
        assert(pFunc);
        mMapRequestDragWidgetInfo[mpEGIcon] = pFunc;
        mpEGIcon->requestDragWidgetInfo = MyGUI::newDelegate(this, &DEIcon::notifyRequestDragWidgetInfo);
    }
    //-------------------------------------------------------------------------------------
    Bool DEIcon::setEGIcon( MyGUI::Widget* p )
    {
        assert(p);
        mpEGIcon = p->castType<MyGUI::Icon>();
        assert(mpEGIcon);
        setEGWidget(p);

        return true;
    }
    //-------------------------------------------------------------------------------------
    void DEIcon::notifyEventStartDrag( MyGUI::Icon* _sender, const MyGUI::DDIconInfo& _info, bool& _result )
    {
        assert(_sender);
        mpEGIcon = _sender;
        setEGWidget(_sender);
        (mMapEventStartDrag[mpEGIcon])(this, _result);
    }
    //-------------------------------------------------------------------------------------
    void DEIcon::notifyEventRequestDrop( MyGUI::Icon* _sender, const MyGUI::DDIconInfo& _info, bool& _result )
    {
        assert(_sender);
        mpEGIcon = _sender;
        setEGWidget(_sender);
        MyGUI::Icon* tempIcon = _info.receiver;
        if ( tempIcon == NULL )
            (mMapEventRequestDrop[mpEGIcon])(this, NULL, _result);
        else
            (mMapEventRequestDrop[mpEGIcon])(this, GuiDgElmPool::getInstance().getDEIcon( tempIcon ), _result);

    }
    //-------------------------------------------------------------------------------------
    void DEIcon::notifyEventDropResult( MyGUI::Icon* _sender, const MyGUI::DDIconInfo& _info, bool _result )
    {
        assert(_sender);
        mpEGIcon = _sender;
        setEGWidget(_sender);
        MyGUI::Icon* tempIcon = _info.receiver;
        if ( tempIcon == NULL )
            (mMapEventDropResult[mpEGIcon])(this, NULL, _result);
        else
            (mMapEventDropResult[mpEGIcon])(this, GuiDgElmPool::getInstance().getDEIcon( tempIcon ), _result);

        //Ïú»ÙÍÏÒ·µÄ¿Ø¼þ¡£
        if ( mIconDragType == ICON_DRAG_TYPE_IMAGE )
            GuiDgElmPoolEx::getInstance().removeImage(mDragImage);
        else if ( mIconDragType == ICON_DRAG_TYPE_TEXT )
            GuiDgElmPoolEx::getInstance().removeText(mDragText);
        mIconDragType = ICON_DRAG_TYPE_NULL;
    }
    //-------------------------------------------------------------------------------------
    void DEIcon::notifyEventChangeDDState( MyGUI::Icon* _sender, MyGUI::DDItemState _state )
    {
        assert(_sender);
        mpEGIcon = _sender;
        setEGWidget(_sender);
        (mMapEventChangeDDState[mpEGIcon])(this, _state.getState());
    }
    //-------------------------------------------------------------------------------------
    void DEIcon::notifyRequestDragWidgetInfo( MyGUI::Icon* _sender, MyGUI::Widget*& _item, MyGUI::IntCoord& _dimension )
    {
        assert(_sender);
        mpEGIcon = _sender;
        setEGWidget(_sender);
        CoordI tempCoord;
        void* tempItem;

        (mMapRequestDragWidgetInfo[mpEGIcon])(this, (void*&)tempItem, tempCoord, (Byte&)mIconDragType);
        _dimension.left = 0;
        _dimension.top = 0;
        _dimension.width = tempCoord.width;
        _dimension.height = tempCoord.height;
        if ( mIconDragType == ICON_DRAG_TYPE_IMAGE )
        {  
            mDragImage =  (DEImage*)(tempItem);
            _item = mDragImage->getEGImage();
        }
        else if ( mIconDragType == ICON_DRAG_TYPE_TEXT )
        {    
            mDragText = (DEText*)(tempItem);
            _item = mDragText->getEGText(); 
        }
    }
    //-------------------------------------------------------------------------------------
    void DEIcon::setTexture( const Str8& name )
    {
        assert(mpEGIcon);
        mpEGIcon->setImageTexture(name);
    }
    //-------------------------------------------------------------------------------------
    void DEIcon::setTexture( const Str8& resname, const Str8& groupname, const Str8& itemname )
    {
        assert(mpEGIcon);
        mpEGIcon->setItemResource(resname);
        mpEGIcon->setItemGroup(groupname);
        mpEGIcon->setItemName(itemname);
    }
    //-------------------------------------------------------------------------------------
    bool DEIcon::setItemResource( const std::string& _name )
    {
        assert(mpEGIcon);
        return mpEGIcon->setItemResource(_name);
    }
    //-------------------------------------------------------------------------------------
    void DEIcon::setItemGroup( const std::string& _value )
    {
        assert(mpEGIcon);
        mpEGIcon->setItemGroup(_value);
    }
    //-------------------------------------------------------------------------------------
    void DEIcon::setItemName( const std::string& _value )
    {
        assert(mpEGIcon);
        mpEGIcon->setItemName(_value);
    }
    
}