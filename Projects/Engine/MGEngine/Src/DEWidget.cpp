//**********************************************************************************************************
#include "stdafx.h"
#include "DEWidget.h"
#include "GuiDelegateElementPool.h"
#include <typeinfo>
#include "newFuction.h"
//**********************************************************************************************************
//**********************************************************************************************************
namespace MG
{ 
    std::map<MyGUI::Widget*, PVOIDBOOLINTINT_CALLBACK>            DEWidget::mMapTooltipCallBack;
    std::map<MyGUI::Widget*, PVOID_CALLBACK>                      DEWidget::mMapClickCallBack;
	std::map<MyGUI::Widget*, PVOID_CALLBACK>                      DEWidget::mMapRightClickCallBack;
    std::map<MyGUI::Widget*, PVOID_CALLBACK>                      DEWidget::mMapDoubleClickCallBack;
    std::map<MyGUI::Widget*, PVOIDINTINTMOUSECODE_CALLBACK>       DEWidget::mMapMsPressedCallBack;
    std::map<MyGUI::Widget*, PVOIDINTINTMOUSECODE_CALLBACK>       DEWidget::mMapMsReleasedCallBack;
    std::map<MyGUI::Widget*, PVOIDBOOL_CALLBACK>                  DEWidget::mMapMsChangeRootFocusCallBack;
    std::map<MyGUI::Widget*, PVOIDBOOL_CALLBACK>                  DEWidget::mMapKeyChangeRootFocusCallBack;
    std::map<MyGUI::Widget*, PVOIDPVOID_CALLBACK>                 DEWidget::mMapKeyLostFocusCallBack;
    std::map<MyGUI::Widget*, PVOIDPVOID_CALLBACK>                 DEWidget::mMapMouseLostFocusCallBack;
    std::map<MyGUI::Widget*, PVOIDPVOID_CALLBACK>                 DEWidget::mMapMouseSetFocusCallBack;
    std::map<MyGUI::Widget*, PVOIDINTINT_CALLBACK>                DEWidget::mMapMouseDragEventCallBack;

    DEWidget::DEWidget()
        :mpEGWidget(nullptr)
    {

    }
    //-----------------------------------------------------------------------------
    DEWidget::~DEWidget()
    {

    }
    //-----------------------------------------------------------------------------
    IWidget& DEWidget::getParent()
    {
        return *this;
    }
    //-----------------------------------------------------------------------------
    Vec2 DEWidget::getSize()
    {     
        assert (mpEGWidget);

        Vec2 selfSize;
        MyGUI::IntSize size = mpEGWidget->getSize();
        selfSize.x = size.width;
        selfSize.y = size.height;
        return selfSize;
    }
    //-----------------------------------------------------------------------------
    Vec2 DEWidget::getPosition()
    {      
        assert (mpEGWidget);

        Vec2 selfPos;
        MyGUI::IntPoint pos = mpEGWidget->getPosition();
        selfPos.x = pos.left;
        selfPos.y = pos.top;
        return selfPos;
    }
    //-----------------------------------------------------------------------------
    void DEWidget::setSize( const Vec2& mgSize )
    {        
        assert (mpEGWidget);

        MyGUI::IntSize size;
        size.width = mgSize.x;
        size.height = mgSize.y;
        mpEGWidget->setSize(size);
    }
    //-----------------------------------------------------------------------------
    void DEWidget::setPosition( const Vec2& mgPos )
    {       
        assert (mpEGWidget);

        MyGUI::IntPoint pos;
        pos.left = mgPos.x;
        pos.top = mgPos.y;
        mpEGWidget->setPosition(pos);
    }
    //-----------------------------------------------------------------------------
    Bool DEWidget::isVisible()
    {
        assert (mpEGWidget);

        return mpEGWidget->isVisible();
    }
    //-----------------------------------------------------------------------------
    Bool DEWidget::setVisible( Bool bVisible )
    {
        assert (mpEGWidget);

        mpEGWidget->setVisible(bVisible);
        return true;
    }
    //-----------------------------------------------------------------------------
    void DEWidget::setEGWidget( MyGUI::Widget* widget )
    {
        assert(widget);

        mpEGWidget = widget;
    }
    //-----------------------------------------------------------------------------
    void DEWidget::setToolTipsEvent( PVOIDBOOLINTINT_CALLBACK pfunc )
    {
        assert ( mpEGWidget );
          
        mMapTooltipCallBack[mpEGWidget] = pfunc;
        mpEGWidget->eventToolTip = MyGUI::newDelegate(this, &DEWidget::notifyTooltip);
    }
    //-----------------------------------------------------------------------------
    void DEWidget::notifyTooltip( MyGUI::Widget* p, const MyGUI::ToolTipInfo& _info )
    {
        mpEGWidget = p;
        if (mpEGWidget)
        {
            (mMapTooltipCallBack[mpEGWidget])(this, _info.type!=0, _info.point.left, _info.point.top);
        }
    }
    //-----------------------------------------------------------------------------
    void DEWidget::setCaption( const std::wstring& caption )
    {
        assert(mpEGWidget);
		MyGUI::ISubWidgetText* pTempText = mpEGWidget->getSubWidgetText();
		if ( pTempText )
			pTempText->setCaption( caption );
    }
    //-----------------------------------------------------------------------------
    std::wstring DEWidget::getCaption()
    {
        assert(mpEGWidget);
		MyGUI::ISubWidgetText* pTempText = mpEGWidget->getSubWidgetText();
		if ( pTempText )
			return pTempText->getCaption();

		return L"";
    }
    //-----------------------------------------------------------------------------
    IWidget* DEWidget::createWidget( const std::string& _type, const std::string& _skin, const CoordI& _coord, const Int& _align, const std::string& _name )
    {   
        MyGUI::Widget* tempWidget = createWidgetT(_type, _skin, _coord, _align, _name);
        return GuiDgElmPool::getInstance().getDEWidget(tempWidget);
    }
    //-----------------------------------------------------------------------------
    MyGUI::Widget* DEWidget::createWidgetT( const std::string& _type, const std::string& _skin, const CoordI& _coord, const Int& _align, const std::string& _name )
    {
        assert(mpEGWidget);
        MyGUI::Align tempAlign = getAlign(_align);
        return mpEGWidget->createWidgetT(_type, _skin, MyGUI::IntCoord(_coord.left, _coord.top, _coord.width, _coord.height), tempAlign, _name);
    }
    //-----------------------------------------------------------------------------
    MyGUI::Align DEWidget::getAlign( const Int& _value ) const
    {
        switch (_value)
        {
        case 0:
			return MyGUI::Align(MyGUI::Align::Enum::HCenter);
            break;              
        case 1:
            return MyGUI::Align(MyGUI::Align::VCenter);
            break;
        case 2:
            return MyGUI::Align(MyGUI::Align::Center);
            break;
        case 3:
            return MyGUI::Align(MyGUI::Align::Left);
            break;
        case 4:
            return MyGUI::Align(MyGUI::Align::Right);
            break;
        case 5:
            return MyGUI::Align(MyGUI::Align::HStretch);
            break;
        case 6:
            return MyGUI::Align(MyGUI::Align::Top);
            break;
        case 7:
            return MyGUI::Align(MyGUI::Align::Bottom);
            break;
        case 8:
            return MyGUI::Align(MyGUI::Align::VStretch);
            break;
        case 9:
            return MyGUI::Align(MyGUI::Align::Stretch);
            break;
        case 10:
            return MyGUI::Align(MyGUI::Align::Default);
            break;
        }
        assert(0);

		return MyGUI::Align(MyGUI::Align::Default);
    }  
    //-----------------------------------------------------------------------------
    void DEWidget::setUserString( const std::string& _key, const std::string& _value )
    {
        assert(mpEGWidget);
        mpEGWidget->setUserString(_key, _value);
    }
    //-----------------------------------------------------------------------------
    const std::string& DEWidget::getUserString( const std::string& _key )
    {
        assert(mpEGWidget);
        return mpEGWidget->getUserString(_key);
    }
    //-----------------------------------------------------------------------------
    bool DEWidget::clearUserString( const std::string& _key )
    {
        assert(mpEGWidget);
        return mpEGWidget->clearUserString(_key);
    }
    //-----------------------------------------------------------------------------
    void DEWidget::clearUserStrings()
    {
        assert(mpEGWidget);
        mpEGWidget->clearUserStrings();
    }
    //-----------------------------------------------------------------------------
    bool DEWidget::isUserString( const std::string& _key )
    {
         assert(mpEGWidget);
         return mpEGWidget->isUserString(_key);
    }
    //-----------------------------------------------------------------------------
    void DEWidget::setUserData( IAny _data )
    {
         assert(mpEGWidget);
         mpEGWidget->setUserData(_data);
    }
    //-----------------------------------------------------------------------------
    IAny* DEWidget::getUserData( bool _throw /*= true*/ )
    {
        assert(mpEGWidget);
        return mpEGWidget->getUserData<IAny>(_throw);
    }
    //-----------------------------------------------------------------------------
    void DEWidget::setAlpha( float _value )
    {
        assert(mpEGWidget);
        mpEGWidget->setAlpha(_value);
    }
    //-----------------------------------------------------------------------------
    float DEWidget::getAlpha()
    {
        assert(mpEGWidget);
        return mpEGWidget->getAlpha();
    }
    //-----------------------------------------------------------------------------
    void DEWidget::setInheritsAlpha( bool _value )
    {
        assert(mpEGWidget);
        mpEGWidget->setInheritsAlpha(_value);
    }
    //-----------------------------------------------------------------------------
    bool DEWidget::isInheritsAlpha()
    {
        assert(mpEGWidget);
        return mpEGWidget->isInheritsAlpha();
    }
    //-----------------------------------------------------------------------------
    void DEWidget::setNeedKeyFocus( bool _value )
    {
        assert(mpEGWidget);
        mpEGWidget->setNeedKeyFocus(_value);
    }
    //-----------------------------------------------------------------------------
    bool DEWidget::isNeedKeyFocus()
    {
        assert(mpEGWidget);
        return mpEGWidget->isNeedKeyFocus();
    }
    //-----------------------------------------------------------------------------
    void DEWidget::setNeedMouseFocus( bool _value )
    {
        assert(mpEGWidget);
        mpEGWidget->setNeedMouseFocus(_value);
    }
    //-----------------------------------------------------------------------------
    bool DEWidget::isNeedMouseFocus()
    {
        assert(mpEGWidget);
        return mpEGWidget->isNeedMouseFocus();
    }
    //-----------------------------------------------------------------------------
    void DEWidget::setInheritsPick( bool _value )
    {
        assert(mpEGWidget);
        mpEGWidget->setInheritsPick(_value);
    }
    //-----------------------------------------------------------------------------
    bool DEWidget::isInheritsPick()
    {
        assert(mpEGWidget);
        return mpEGWidget->isInheritsPick();
    }
    //-----------------------------------------------------------------------------
    void DEWidget::setEnabled( bool _value )
    {
        assert(mpEGWidget);
        mpEGWidget->setEnabled(_value);
    }
    //-----------------------------------------------------------------------------
    bool DEWidget::isEnabled()
    {
        assert(mpEGWidget);
        return mpEGWidget->isEnabled();
    }                                                                           
    //-----------------------------------------------------------------------------
    MG::CoordI DEWidget::getClientCoord()
    {
        assert(mpEGWidget);
        MyGUI::IntCoord temp = mpEGWidget->getClientCoord();
        return CoordI(temp.left, temp.top, temp.width, temp.height);
    }
    //-----------------------------------------------------------------------------
    void DEWidget::setNeedToolTip( bool _value )
    {
        assert(mpEGWidget);
        mpEGWidget->setNeedToolTip(_value);
    }
    //-----------------------------------------------------------------------------
    bool DEWidget::getNeedToolTip()
    {
        assert(mpEGWidget);
        return mpEGWidget->getNeedToolTip();
    }
    //-----------------------------------------------------------------------------
    void DEWidget::setCoord( const CoordI& _value )
    {
        assert(mpEGWidget);
        mpEGWidget->setCoord(MyGUI::IntCoord(_value.left, _value.top, _value.width, _value.height));
    }
    //-----------------------------------------------------------------------------
    CoordI DEWidget::getCoord()
    {
        assert(mpEGWidget);
        MyGUI::IntCoord temp = mpEGWidget->getCoord();
        return CoordI(temp.left, temp.top, temp.width, temp.height);
    }
    //-----------------------------------------------------------------------------
    void DEWidget::setMouseButtonClickEvent( PVOID_CALLBACK pfunc )
    {
        assert ( mpEGWidget );  
        mMapClickCallBack[mpEGWidget] = pfunc;
        mpEGWidget->eventMouseButtonClick = MyGUI::newDelegate(this, &DEWidget::notifyMouseButtonClick);
    }
	//-----------------------------------------------------------------------------
	void DEWidget::setMouseButtonRightClickEvent( PVOID_CALLBACK pfunc )
	{
		assert ( mpEGWidget );  
		mMapRightClickCallBack[mpEGWidget] = pfunc;
		mpEGWidget->eventMouseButtonRightClick = MyGUI::newDelegate(this, &DEWidget::notifyMouseButtonRightClick);
	}
    //-----------------------------------------------------------------------------
    void DEWidget::setMouseButtonDoubleClickEvent( PVOID_CALLBACK pfunc )
    {
        assert ( mpEGWidget );  
        mMapDoubleClickCallBack[mpEGWidget] = pfunc;
        mpEGWidget->eventMouseButtonDoubleClick = MyGUI::newDelegate(this, &DEWidget::notifyMouseButtonDoubleClick);
    }
    //-----------------------------------------------------------------------------
    void DEWidget::setMouseButtonPressedEvent( PVOIDINTINTMOUSECODE_CALLBACK pfunc )
    {
        assert ( mpEGWidget );  
        mMapMsPressedCallBack[mpEGWidget] = pfunc;
        mpEGWidget->eventMouseButtonPressed = MyGUI::newDelegate(this, &DEWidget::notifyMouseButtonPressed);
    }
    //-----------------------------------------------------------------------------
    void DEWidget::setMouseButtonReleasedEvent( PVOIDINTINTMOUSECODE_CALLBACK pfunc )
    {
        assert ( mpEGWidget );  
        mMapMsReleasedCallBack[mpEGWidget] = pfunc;
        mpEGWidget->eventMouseButtonReleased = MyGUI::newDelegate(this, &DEWidget::notifyMouseButtonReleased);
    }
    //-----------------------------------------------------------------------------
    void DEWidget::notifyMouseButtonClick( MyGUI::Widget* p )
    {
        assert(p);
        mpEGWidget = p;
        (mMapClickCallBack[mpEGWidget])(this);
        
    }
	//-----------------------------------------------------------------------------
	void DEWidget::notifyMouseButtonRightClick( MyGUI::Widget* p )
	{
		assert(p);
		mpEGWidget = p;
		(mMapRightClickCallBack[mpEGWidget])(this);

	}
    //-----------------------------------------------------------------------------
    void DEWidget::notifyMouseButtonDoubleClick( MyGUI::Widget* p )
    {
        assert(p);
        mpEGWidget = p;
        (mMapDoubleClickCallBack[mpEGWidget])(this);
    }
    //-----------------------------------------------------------------------------
    void DEWidget::notifyMouseButtonPressed( MyGUI::Widget* p, Int msposX, Int msposY, MyGUI::MouseButton id )
    {
        assert(p);
        mpEGWidget = p;
        (mMapMsPressedCallBack[mpEGWidget])(this, msposX, msposY, MouseCode( id.toValue() ) );
    }
    //-----------------------------------------------------------------------------
    void DEWidget::notifyMouseButtonReleased( MyGUI::Widget* p, Int msposX, Int msposY, MyGUI::MouseButton id )
    {
        assert(p);
        mpEGWidget = p;
        (mMapMsReleasedCallBack[mpEGWidget])(this, msposX, msposY, MouseCode( id.toValue() ) );
    }
    //-----------------------------------------------------------------------------
    void DEWidget::changeWidgetSkin( const std::string& _skinname )
    {
        assert(mpEGWidget);

        mpEGWidget->changeWidgetSkin(_skinname);
    }
    //-----------------------------------------------------------------------------
    void DEWidget::setMouseChangeRootFocusEvent( PVOIDBOOL_CALLBACK pFunc )
    {
        assert ( mpEGWidget );  
        mMapMsChangeRootFocusCallBack[mpEGWidget] = pFunc;
        mpEGWidget->eventRootMouseChangeFocus = MyGUI::newDelegate(this, &DEWidget::notifyMouseChangeRootFocusEvent);
    }
    //-----------------------------------------------------------------------------
    void DEWidget::setKeyChangeRootFocusEvent( PVOIDBOOL_CALLBACK pFunc )
    {
        assert ( mpEGWidget );  
        mMapKeyChangeRootFocusCallBack[mpEGWidget] = pFunc;
        mpEGWidget->eventRootKeyChangeFocus = MyGUI::newDelegate(this, &DEWidget::notifyKeyChangeRootFocusEvent);
    }
    //-----------------------------------------------------------------------------
    void DEWidget::notifyMouseChangeRootFocusEvent( MyGUI::Widget* p, Bool focus )
    {
        assert(p);
        mpEGWidget = p;
        (mMapMsChangeRootFocusCallBack[mpEGWidget])(this, focus);
    }
    //-----------------------------------------------------------------------------
    void DEWidget::notifyKeyChangeRootFocusEvent( MyGUI::Widget* p, Bool focus )
    {
        assert(p);
        mpEGWidget = p;
        (mMapKeyChangeRootFocusCallBack[mpEGWidget])(this, focus);
    }
    //-----------------------------------------------------------------------------
    void DEWidget::setKeyLostFocusEvent( PVOIDPVOID_CALLBACK pFunc )
    {
        assert ( mpEGWidget );  
        mMapKeyLostFocusCallBack[mpEGWidget] = pFunc;
        mpEGWidget->eventKeyLostFocus = MyGUI::newDelegate(this, &DEWidget::notifyKeyLostFocusEvent);

    }
    //-----------------------------------------------------------------------------
    void DEWidget::notifyKeyLostFocusEvent( MyGUI::Widget* _sender, MyGUI::Widget* _new )
    {
        assert(_sender);
        mpEGWidget = _sender;
        (mMapKeyLostFocusCallBack[mpEGWidget])(this, NULL);
    }
    //-----------------------------------------------------------------------------
    void DEWidget::setKeyFocus(Bool focus)
    {
        assert(mpEGWidget);
        if ( focus )
            MyGUI::InputManager::getInstance().setKeyFocusWidget(mpEGWidget);
        else
            MyGUI::InputManager::getInstance().setKeyFocusWidget(NULL);
    }
    //-----------------------------------------------------------------------------
    void DEWidget::setMouseLostFocusEvent( PVOIDPVOID_CALLBACK pFunc )
    {
        assert ( mpEGWidget );  
        mMapMouseLostFocusCallBack[mpEGWidget] = pFunc;
        mpEGWidget->eventMouseLostFocus = MyGUI::newDelegate(this, &DEWidget::notifyMouseLostFocusEvent);
    }
    //-----------------------------------------------------------------------------
    void DEWidget::setMouseSetFocusEvent( PVOIDPVOID_CALLBACK pFunc )
    {
        assert ( mpEGWidget );  
        mMapMouseSetFocusCallBack[mpEGWidget] = pFunc;
        mpEGWidget->eventMouseSetFocus = MyGUI::newDelegate(this, &DEWidget::notifyMouseSetFocusEvent);
    }
    //-----------------------------------------------------------------------------
    void DEWidget::notifyMouseLostFocusEvent( MyGUI::Widget* _sender, MyGUI::Widget* _new )
    {
        assert(_sender);
		mpEGWidget = _sender;
		IWidget* pWidget = GuiDgElmPool::getInstance().getDEWidget(_new);
		//因为回调函数记住的DEWidget的地址是初始化时的地址。
		//pWidget是游戏运行中取的值。
		//this与pWidget并不是同时取的值
		//所以this与pWidget可能指向同一块内存
		if ( mpEGWidget != _sender )
		{	
			mpEGWidget = _sender;
			pWidget = GuiDgElmPool::getInstance().getDEWidget(_new);
		}
        (mMapMouseLostFocusCallBack[mpEGWidget])(this, pWidget);
    }
    //-----------------------------------------------------------------------------
    void DEWidget::notifyMouseSetFocusEvent( MyGUI::Widget* _sender, MyGUI::Widget* _new )
    {
        assert(_sender);
        mpEGWidget = _sender;
		IWidget* pWidget = GuiDgElmPool::getInstance().getDEWidget(_new);
		if ( mpEGWidget != _sender )
		{	
			mpEGWidget = _sender;
			pWidget = GuiDgElmPool::getInstance().getDEWidget(_new);
		}
        (mMapMouseSetFocusCallBack[mpEGWidget])(this, pWidget);
    }
    //-----------------------------------------------------------------------------
    const std::string& DEWidget::getName()
    {
        assert(mpEGWidget); 
        return mpEGWidget->getName();
    }
    //-----------------------------------------------------------------------------
    IButton* DEWidget::getButton()
    {
        assert(mpEGWidget);
        return GuiDgElmPool::getInstance().getDEButton(mpEGWidget);
    }
    //-----------------------------------------------------------------------------
    IEdit* DEWidget::getEdit()
    {
        assert(mpEGWidget);
        return GuiDgElmPool::getInstance().getDEEdit(mpEGWidget);
    }
    //-----------------------------------------------------------------------------
    IForm* DEWidget::getForm()
    {
        assert(mpEGWidget);
        return GuiDgElmPool::getInstance().getDEForm(mpEGWidget);
    }
    //-----------------------------------------------------------------------------
    IImage* DEWidget::getImage()
    {
        assert(mpEGWidget);
        return GuiDgElmPool::getInstance().getDEImage(mpEGWidget);
    }
    //-----------------------------------------------------------------------------
    IProgress* DEWidget::getProgress()
    {
        assert(mpEGWidget);
        return GuiDgElmPool::getInstance().getDEProgress(mpEGWidget);
    }
    //-----------------------------------------------------------------------------
    IText* DEWidget::getText()
    {
        assert(mpEGWidget);
        return GuiDgElmPool::getInstance().getDEText(mpEGWidget);
    }
    //-----------------------------------------------------------------------------
    IViewScroll* DEWidget::getViewScroll()
    {
        assert(mpEGWidget);
        return GuiDgElmPool::getInstance().getDEViewScroll(mpEGWidget);
    }
    //-----------------------------------------------------------------------------
    IList* DEWidget::getList()
    {
        assert(mpEGWidget);
        return GuiDgElmPool::getInstance().getDEList(mpEGWidget);
    }
    //-----------------------------------------------------------------------------
    ITab* DEWidget::getTab()
    {
        assert(mpEGWidget);
        return GuiDgElmPool::getInstance().getDETab(mpEGWidget);
    }
    //-----------------------------------------------------------------------------
    ITabItem* DEWidget::getTabItem()
    {
        assert(mpEGWidget);
        return GuiDgElmPool::getInstance().getDETabItem(mpEGWidget);
    }
    //-----------------------------------------------------------------------------
    IComboBox* DEWidget::getComboBox()
    {
        assert(mpEGWidget);
        return GuiDgElmPool::getInstance().getDEComboBox(mpEGWidget);
    }
    //-----------------------------------------------------------------------------
    IMixTree* DEWidget::getMixTree()
    {
        assert(mpEGWidget);
        return GuiDgElmPool::getInstance().getDEMixTree(mpEGWidget);
    }
    //-----------------------------------------------------------------------------
    IRollingText* DEWidget::getRollingText()
    {
        assert(mpEGWidget);
        return GuiDgElmPool::getInstance().getDERollingText(mpEGWidget);
    }
    //-----------------------------------------------------------------------------
    IMixList* DEWidget::getMixList()
    {
        assert(mpEGWidget);
        return GuiDgElmPool::getInstance().getDEMixList(mpEGWidget);
    }
    //-----------------------------------------------------------------------------
    IMixListRow* DEWidget::getMixListRow()
    {
        assert(mpEGWidget);
        return GuiDgElmPool::getInstance().getDEMixListRow(mpEGWidget);
    }
    //-----------------------------------------------------------------------------
    MG::Int DEWidget::getChildCount()
    {
        assert(mpEGWidget);
        return mpEGWidget->getChildCount();
    }
    //-----------------------------------------------------------------------------
    IWidget* DEWidget::getChildAt( Int index )
    {
        assert(mpEGWidget);
        MyGUI::Widget* pWidget = mpEGWidget->getChildAt(index);
        assert(pWidget);

        return GuiDgElmPool::getInstance().getDEWidget(pWidget);
    }
    //-----------------------------------------------------------------------------
    MG::CoordI DEWidget::getAbsoluteCoord()
    {
        assert(mpEGWidget);
        MyGUI::IntCoord tempCoord = mpEGWidget->getAbsoluteCoord();

        return CoordI(tempCoord.left, tempCoord.top, tempCoord.width, tempCoord.height);
    }
    //-----------------------------------------------------------------------------
    void DEWidget::setMouseDragEvent( PVOIDINTINT_CALLBACK pFunc )
    {
        assert(mpEGWidget);

        mMapMouseDragEventCallBack[mpEGWidget] = pFunc;
        mpEGWidget->eventMouseDrag = MyGUI::newDelegate(this, &DEWidget::notifyMouseDragEvent);
    }
    //-----------------------------------------------------------------------------
    void DEWidget::notifyMouseDragEvent( MyGUI::Widget* p, Int msposX, Int msposY )
    {
        assert(p);

        mpEGWidget = p;
        (mMapMouseDragEventCallBack[mpEGWidget])(this, msposX, msposY);
    }
    //-----------------------------------------------------------------------------
    MG::Bool DEWidget::isKeyFocus()
    {
        assert(mpEGWidget);
        if ( mpEGWidget == MyGUI::InputManager::getInstance().getKeyFocusWidget() )
            return true;
        else
            return false;
    }
	//-----------------------------------------------------------------------------
	IWidget* DEWidget::findWidget( const std::string& _name )
	{
		assert(mpEGWidget);
		MyGUI::Widget* pWidget = mpEGWidget->findWidget(_name);
		assert(pWidget);

		return GuiDgElmPool::getInstance().getDEWidget(pWidget);
	}
	//-----------------------------------------------------------------------------
	ITimeText* DEWidget::getTimeText()
	{
		assert(mpEGWidget);
		return GuiDgElmPool::getInstance().getDETimeText(mpEGWidget);
	}
	//-----------------------------------------------------------------------------
	void DEWidget::setCloseTime( Flt lastTime )
	{
		assert(mpEGWidget);
		GuiFuction::getInstance().setCloseTime(mpEGWidget, lastTime);
	}
	//-----------------------------------------------------------------------------
	void DEWidget::setCloseEvent( Flt lastTime, PVOID_CALLBACK func )
	{
		assert(mpEGWidget);
		GuiFuction::getInstance().setCloseEvent(mpEGWidget, lastTime, func);
	}
	//-----------------------------------------------------------------------------
	void DEWidget::setTextShadow( bool _value )
	{
		assert(mpEGWidget);
		if (NULL != mpEGWidget->getSubWidgetText())
			mpEGWidget->getSubWidgetText()->setShadow(_value);
	}
	//-----------------------------------------------------------------------------
	void DEWidget::setTextShadowColour( const Color& _value )
	{
		assert(mpEGWidget);
		if (NULL != mpEGWidget->getSubWidgetText())
		{
			MyGUI::Colour guiColour = MyGUI::Colour(_value.r,_value.g,_value.b,_value.a);
			mpEGWidget->getSubWidgetText()->setShadowColour(guiColour);
		}
	}
	//-----------------------------------------------------------------------------
	void DEWidget::setAction( WIDGET_ACTION _type, Flt _actionTime, Bool _isClose )
	{
		assert(mpEGWidget);

		mpEGWidget->setVisible(true);

		MyGUI::ControllerManager* pControllerManager = MyGUI::ControllerManager::getInstancePtr();

		MyGUI::ControllerItem* item = pControllerManager->createItem(MyGUI::ControllerForm::getClassTypeName());
		MyGUI::ControllerForm* controller = item->castType<MyGUI::ControllerForm>();

		controller->setFunction(widgetAction[(Int)_type]);
		controller->setTime(_actionTime);
		controller->setCloseFlag(_isClose);

		pControllerManager->addItem(mpEGWidget, controller);
	}
	//-----------------------------------------------------------------------------
	void DEWidget::setColour( const Color& _value )
	{
		assert(mpEGWidget);
		
		MyGUI::Colour guiColour = MyGUI::Colour(_value.r,_value.g,_value.b,_value.a);
		mpEGWidget->setColour(guiColour);
	}
}