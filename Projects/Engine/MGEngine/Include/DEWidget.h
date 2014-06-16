//**********************************************************************************************************
#ifndef _H_DEWIDGET_75743897589_
#define _H_DEWIDGET_75743897589_
//**********************************************************************************************************
#include "IWidget.h"
//**********************************************************************************************************
class  MyGUI::Widget;
struct MyGUI::ToolTipInfo;
struct MyGUI::Align;
//**********************************************************************************************************
namespace MG
{
    class DEWidget : public IWidget 
    {
    public:
        DEWidget();
        virtual ~DEWidget();

    public:
        virtual IButton*            getButton();
        virtual IEdit*              getEdit();
        virtual IForm*              getForm();
        virtual IImage*             getImage();
        virtual IProgress*          getProgress();
        virtual IText*              getText();
        virtual IViewScroll*        getViewScroll();
        virtual IList*              getList();
        virtual ITab*               getTab();
        virtual ITabItem*           getTabItem();
        virtual IComboBox*          getComboBox();
        virtual IMixTree*           getMixTree();
        virtual IRollingText*       getRollingText( );
        virtual IMixList*           getMixList();
        virtual IMixListRow*        getMixListRow();
		virtual ITimeText*			getTimeText();

        virtual IWidget&            getParent();
        virtual Int                 getChildCount();
        virtual IWidget*            getChildAt(Int index);
        virtual IWidget*            createWidget(const std::string& _type, const std::string& _skin, const CoordI& _coord, const Int& _align, const std::string& _name);   
		virtual IWidget*			findWidget(const std::string& _name);

        virtual Vec2                getSize();
        virtual Vec2                getPosition();
        virtual void                setSize(const Vec2& mgSize);
        virtual void                setPosition(const Vec2& mgPos);
        virtual Bool                isVisible();
        virtual Bool                setVisible(Bool bVisible);
        virtual void                setCaption(const std::wstring& caption);
        virtual std::wstring        getCaption();
        virtual void                setAlpha(float _value);
        virtual float               getAlpha();
        virtual void                setInheritsAlpha(bool _value);
        virtual bool                isInheritsAlpha();
        virtual void                setNeedKeyFocus(bool _value);
        virtual bool                isNeedKeyFocus();
        virtual void                setNeedMouseFocus(bool _value);
        virtual bool                isNeedMouseFocus();
        virtual void                setInheritsPick(bool _value);
        virtual bool                isInheritsPick();
        virtual void                setEnabled(bool _value);
        virtual bool                isEnabled();
        virtual CoordI              getClientCoord();
        virtual void                setNeedToolTip(bool _value);
        virtual bool                getNeedToolTip();
        virtual void                setCoord(const CoordI& _value);
        virtual CoordI              getCoord();
        virtual CoordI              getAbsoluteCoord();
        virtual void                changeWidgetSkin(const std::string& _skinname);
        virtual void                setKeyFocus(Bool focus);
        virtual Bool                isKeyFocus();
        virtual const std::string&  getName();

        virtual void                setUserString(const std::string& _key, const std::string& _value);
        virtual const std::string&  getUserString(const std::string& _key);
        virtual bool                clearUserString(const std::string& _key);
        virtual void                clearUserStrings(); 
        virtual bool                isUserString(const std::string& _key);
        virtual void                setUserData(IAny _data);
        virtual IAny*               getUserData(bool _throw = true);

		virtual void				setCloseTime(Flt lastTime);
		virtual void				setTextShadow(bool _value);
		virtual void				setTextShadowColour(const Color& _value);

		virtual void				setAction( WIDGET_ACTION _type, Flt _actionTime, Bool _isClose );
		virtual void				setColour(const Color& _value);

    public:
                void    setEGWidget(MyGUI::Widget* widget);

    public:
        virtual void    setToolTipsEvent(PVOIDBOOLINTINT_CALLBACK);
        virtual void    setMouseButtonClickEvent(PVOID_CALLBACK pFunc);
		virtual void    setMouseButtonRightClickEvent(PVOID_CALLBACK pFunc);
        virtual void    setMouseButtonDoubleClickEvent(PVOID_CALLBACK pFunc);
        virtual void    setMouseButtonPressedEvent(PVOIDINTINTMOUSECODE_CALLBACK pFunc);
        virtual void    setMouseButtonReleasedEvent(PVOIDINTINTMOUSECODE_CALLBACK pFunc);
        virtual void    setMouseChangeRootFocusEvent(PVOIDBOOL_CALLBACK pFunc);
        virtual void    setKeyChangeRootFocusEvent(PVOIDBOOL_CALLBACK pFunc);
        virtual void    setKeyLostFocusEvent(PVOIDPVOID_CALLBACK pFunc);
        virtual void    setMouseLostFocusEvent(PVOIDPVOID_CALLBACK pFunc);
        virtual void    setMouseSetFocusEvent(PVOIDPVOID_CALLBACK pFunc);
        virtual void    setMouseDragEvent(PVOIDINTINT_CALLBACK pFunc);
		virtual void	setCloseEvent(Flt lastTime, PVOID_CALLBACK func);


    protected:
        //引擎事件
        void            notifyTooltip(MyGUI::Widget* p, const MyGUI::ToolTipInfo& _info);
        void            notifyMouseButtonClick(MyGUI::Widget* p);
		void            notifyMouseButtonRightClick(MyGUI::Widget* p);
        void            notifyMouseButtonDoubleClick(MyGUI::Widget* p);
        void            notifyMouseButtonPressed(MyGUI::Widget* p, Int msposX, Int msposY, MyGUI::MouseButton id);
        void            notifyMouseButtonReleased(MyGUI::Widget* p, Int msposX, Int msposY, MyGUI::MouseButton id);
        void            notifyMouseChangeRootFocusEvent(MyGUI::Widget* p, Bool focus);
        void            notifyKeyChangeRootFocusEvent(MyGUI::Widget* p, Bool focus);
        void            notifyKeyLostFocusEvent(MyGUI::Widget* _sender, MyGUI::Widget* _new);
        void            notifyMouseLostFocusEvent(MyGUI::Widget* _sender, MyGUI::Widget* _new);
        void            notifyMouseSetFocusEvent(MyGUI::Widget* _sender, MyGUI::Widget* _new);
        void            notifyMouseDragEvent(MyGUI::Widget* p, Int msposX, Int msposY);       

    protected:
        MyGUI::Align    getAlign(const Int& _value) const ;
        Str             getTypeAndSkin(const Str& _name, const Str& _skin, Str& name, Str& skin) ;
        MyGUI::Widget*  createWidgetT(const std::string& _type, const std::string& _skin, const CoordI& _coord, const Int& _align, const std::string& _name);   


    protected:
        //记录引擎对象和对应的回调函数，当引擎的回调响应时可找到client的回调函数
        static std::map<MyGUI::Widget*, PVOIDBOOLINTINT_CALLBACK>            mMapTooltipCallBack;
        static std::map<MyGUI::Widget*, PVOID_CALLBACK>                      mMapClickCallBack;
		static std::map<MyGUI::Widget*, PVOID_CALLBACK>                      mMapRightClickCallBack;
        static std::map<MyGUI::Widget*, PVOID_CALLBACK>                      mMapDoubleClickCallBack;
        static std::map<MyGUI::Widget*, PVOIDINTINTMOUSECODE_CALLBACK>       mMapMsPressedCallBack;
        static std::map<MyGUI::Widget*, PVOIDINTINTMOUSECODE_CALLBACK>       mMapMsReleasedCallBack;
        static std::map<MyGUI::Widget*, PVOIDBOOL_CALLBACK>                  mMapMsChangeRootFocusCallBack;
        static std::map<MyGUI::Widget*, PVOIDBOOL_CALLBACK>                  mMapKeyChangeRootFocusCallBack;
        static std::map<MyGUI::Widget*, PVOIDPVOID_CALLBACK>                 mMapKeyLostFocusCallBack;
        static std::map<MyGUI::Widget*, PVOIDPVOID_CALLBACK>                 mMapMouseLostFocusCallBack;
        static std::map<MyGUI::Widget*, PVOIDPVOID_CALLBACK>                 mMapMouseSetFocusCallBack;
        static std::map<MyGUI::Widget*, PVOIDINTINT_CALLBACK>                mMapMouseDragEventCallBack;

    protected:
        //引擎对象指针
        MyGUI::Widget* mpEGWidget;

    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************