//**********************************************************************************************************
#ifndef _H_IWIDGET_574893578_
#define _H_IWIDGET_574893578_
//**********************************************************************************************************
#include "MGEngineInterfacePreqs.h"
#include "IAny.h"
//**********************************************************************************************************
//按钮接口
namespace MG
{
    class IWidget
    {
    public:
        //转换
        virtual IButton*        getButton() = 0;
        virtual IEdit*          getEdit() = 0;
        virtual IForm*          getForm() = 0;
        virtual IImage*         getImage() = 0;
        virtual IProgress*      getProgress() = 0;
        virtual IText*          getText() = 0;
        virtual IViewScroll*    getViewScroll() = 0;
        virtual IList*          getList() = 0;
        virtual ITab*           getTab() = 0;
        virtual ITabItem*       getTabItem() = 0;
        virtual IComboBox*      getComboBox() = 0;
        virtual IMixTree*       getMixTree() = 0;
        virtual IRollingText*   getRollingText( ) = 0;
        virtual IMixList*       getMixList() = 0;
        virtual IMixListRow*    getMixListRow() = 0;
		virtual ITimeText*		getTimeText() = 0;

        //字控件，父控件
        //create一个子控件
        virtual IWidget*        createWidget(const std::string& _type, const std::string& _skin, const CoordI& _coord, const Int& _align, const std::string& _name) = 0;   
        //获得子控件数量
        virtual Int             getChildCount() = 0;
        //根据index获得子控件
        virtual IWidget*        getChildAt(Int index) = 0;
        //获得父控件，返回父控件的引用
        virtual IWidget&        getParent() = 0;
        //更换皮肤
        virtual void            changeWidgetSkin(const std::string& _skinname) = 0;
		//查找子控件
		virtual IWidget*		findWidget(const std::string& _name) = 0;

        //基本属性
        //获得控件的大小（宽高），返回控件大小。
        virtual Vec2            getSize() = 0;
        //获得控件的相对父控件的位置，返回当前得到位置。
        virtual Vec2            getPosition() = 0;
        //设置控件的大小
        virtual void            setSize(const Vec2& mgSize) = 0;
        //设置控件的相对父控件的位置
        virtual void            setPosition(const Vec2& mgPos) = 0;
        // Set widget 的Alpha值   0 -- 1
        virtual void            setAlpha(float _value) = 0;
        // Get widget 的Alpha值
        virtual float           getAlpha() = 0;
        // 设置是否继承父控件 的Alpha值  
        virtual void            setInheritsAlpha(bool _value) = 0;
        // 获得是否继承父控件 的Alpha值
        virtual bool            isInheritsAlpha() = 0;
        // 设置是否需要获得key focus。
        virtual void            setNeedKeyFocus(bool _value) = 0;
        // 获得是否需要获得key focus。
        virtual bool            isNeedKeyFocus() = 0;
        // 设置是否需要获得Mouse focus。
        virtual void            setNeedMouseFocus(bool _value) = 0;
        // 获得是否需要获得Mouse focus。
        virtual bool            isNeedMouseFocus() = 0;
        // 设置是否继承父控件 的Mouse focus属性
        virtual void            setInheritsPick(bool _value) = 0;
        // 获得是否继承父控件 的Mouse focus属性
        virtual bool            isInheritsPick() = 0;
        // 设置是否可用
        virtual void            setEnabled(bool _value) = 0;
        // 获得是否可用
        virtual bool            isEnabled() = 0;
        // 获得客户区域大小和位置。
        virtual CoordI          getClientCoord() = 0;
        //设置是否需要Tips。
        virtual void            setNeedToolTip(bool _value) = 0;
        //获得是否需要Tips。
        virtual bool            getNeedToolTip() = 0;
        /** Set coordinates (position and size) */
        virtual void            setCoord(const CoordI& _value) = 0;
        /** Get coordinates (position and size) */
        virtual CoordI          getCoord() = 0;
        /** Get coordinate in screen coordinates */
        virtual CoordI          getAbsoluteCoord() = 0;
        //设置自己为鼠标按键的焦点
        virtual void            setKeyFocus(Bool focus) = 0;
        //获得当前的鼠标按键焦点是否是自己。
        virtual Bool            isKeyFocus() = 0 ;
        //! Get name of widget
        virtual const std::string& 
                                getName() = 0;
        //是否可见。
        virtual Bool            isVisible() = 0;
        //设置控件是否可见。
        virtual Bool            setVisible(Bool bVisible) = 0;
        //设置控件 caption
        virtual void            setCaption(const std::wstring& caption) = 0;
        //获得控件 caption
        virtual std::wstring    getCaption() = 0;

		//设置控件多少时间后关闭
		virtual void			setCloseTime(Flt lastTime) = 0;

		//阴影（仅限于包含文字的控件，并且是继承于TextBox，否则会报错）
		//设置阴影
		virtual void			setTextShadow(Bool _value) = 0;
		//设置阴影颜色
		virtual void			setTextShadowColour(const Color& _value) = 0;
		//给控件设置颜色
		virtual void			setColour(const Color& _value) = 0;
		
		//设置动画
		virtual void			setAction( WIDGET_ACTION _type, Flt _actionTime, Bool _isClose ) = 0;

    public: //usedata
        //设置usestring
        virtual void                setUserString(const std::string& _key, const std::string& _value) = 0;
        //获得usestring
        virtual const std::string&  getUserString(const std::string& _key) = 0;
        //删除usestring
        virtual bool                clearUserString(const std::string& _key) = 0;
        //删除所有的usestring
        virtual void                clearUserStrings() = 0; 
        //key是否能找到usestring
        virtual bool                isUserString(const std::string& _key) = 0;
        //设置anydata
        virtual void                setUserData(IAny _data) = 0;
        //获得anydata
        virtual IAny*               getUserData(bool _throw = true) = 0;
        

    public://事件(这些都是共用的事件函数)
		//设置控件关闭调用的函数。lastTime表示多少时间后关闭
		virtual void			setCloseEvent(Flt lastTime, PVOID_CALLBACK func) = 0;
        //控件的Tips消息，
        //函数原型：void (__cdecl *PVOIDBOOLINTINTINT_CALLBACK)(void*, Bool, Int, Int, Int)；
        //@param1 _sender回调PVOIDBOOLINTINTINT_CALLBACK，@param2 是否显示Tips，true显示，false不显示，@param3&4 鼠标位置，@param5如果控件是一组，表示在这一组中的Index。
        virtual void            setToolTipsEvent(PVOIDBOOLINTINT_CALLBACK) = 0;
        virtual void            setMouseButtonClickEvent(PVOID_CALLBACK) = 0;
		virtual void            setMouseButtonRightClickEvent(PVOID_CALLBACK) = 0;
        virtual void            setMouseButtonDoubleClickEvent(PVOID_CALLBACK) = 0;
        virtual void            setMouseButtonPressedEvent(PVOIDINTINTMOUSECODE_CALLBACK) = 0;
        virtual void            setMouseButtonReleasedEvent(PVOIDINTINTMOUSECODE_CALLBACK) = 0;
        //控件失去键盘焦点，
        //函数原型：void PVOIDPVOID_CALLBACK（IWidget* sender，IWidget* older）；
        //@param1 _sender回调PVOIDPVOID_CALLBACK，@param2 获得焦点的控件或nullPtr
        virtual void       setKeyLostFocusEvent(PVOIDPVOID_CALLBACK) = 0;
        //控件获得键盘焦点，
        //函数原型：void PVOIDPVOID_CALLBACK（IWidget* sender，IWidget* older）；
        //@param1 _sender回调PVOIDPVOID_CALLBACK，@param2 获得焦点的控件或nullPtr
        //virtual void       setKeySetFocusEvent(PVOIDPVOID_CALLBACK) = 0;
        //控件失去鼠标焦点，
        //函数原型：void PVOIDPVOID_CALLBACK（IWidget* sender，IWidget* older）；
        //@param1 _sender回调PVOIDPVOID_CALLBACK，@param2 获得焦点的控件或nullPtr
        virtual void       setMouseLostFocusEvent(PVOIDPVOID_CALLBACK) = 0;
        //控件获得鼠标焦点，
        //函数原型：void PVOIDPVOID_CALLBACK（IWidget* sender，IWidget* older）；
        //@param1 _sender回调PVOIDPVOID_CALLBACK，@param2 失去焦点的控件
        virtual void       setMouseSetFocusEvent(PVOIDPVOID_CALLBACK) = 0;
        //控件被鼠标拖曳，
        //函数原型：void PVOIDINTINT_CALLBACK（IWidget* sender，int offsetX， int offsetX）；
        //@param1 _sender回调PVOIDINTINT_CALLBACK，@param2 和 @param3 代表鼠标的偏移。
        virtual void       setMouseDragEvent(PVOIDINTINT_CALLBACK) = 0;
        //鼠标在控件上移动，
        //函数原型：void PVOIDINTINT_CALLBACK（IWidget* sender，int posX， int posY）；
        //@param1 _sender回调PVOIDINTINT_CALLBACK，@param2 和 @param3 代表鼠标的位置
        //virtual void       setMouseMoveEvent(PVOIDINTINT_CALLBACK) = 0;
        //鼠标点击控件，
        //函数原型：void PVOID_CALLBACK（IWidget* sender）；
        //@param1 _sender回调PVOID_CALLBACK。
        //virtual void       setMouseButtonClickEvent(PVOID_CALLBACK) = 0;
        //鼠标双击控件，
        //函数原型：void PVOID_CALLBACK（IWidget* sender）；
        //@param1 _sender回调PVOID_CALLBACK。
        //virtual void       setMouseButtonDoubleClickEvent(PVOID_CALLBACK) = 0;
        //控件的鼠标焦点变化，
        //函数原型：void PVOIDBOOL_CALLBACK（IWidget* sender，bool isFocus）；
        //@param1 _sender回调PVOIDBOOL_CALLBACK，@param2 是否获得鼠标焦点。
        virtual void       setMouseChangeRootFocusEvent(PVOIDBOOL_CALLBACK) = 0;
        //控件的键盘焦点变化，
        //函数原型：void PVOIDBOOL_CALLBACK（IWidget* sender，bool isFocus）；
        //@param1 _sender回调PVOIDBOOL_CALLBACK，@param2 是否获键盘标焦点。
        virtual void       setKeyChangeRootFocusEvent(PVOIDBOOL_CALLBACK) = 0;
        //键盘按键松开控件，
        //函数原型：void PVOIDBYTE_CALLBACK（IWidget* sender，keycode key）；
        //@param1 _sender回调PVOIDBYTE_CALLBACK，@param2 键盘按键值。
        //virtual void       setKeyButtonReleasedEvent(PVOIDBYTE_CALLBACK) = 0;
        //鼠标中键在控件上滚动，
        //函数原型：void PVOIDINTINT_CALLBACK（IWidget* sender，int rel）；
        //@param1 _sender回调PVOIDINTINT_CALLBACK，@param2 relative wheel position。
        //virtual void       setMouseWheelEvent(PVOIDINT_CALLBACK) = 0;
        //鼠标按键按下控件，
        //函数原型：void PVOIDINTINTMOUSECODE_CALLBACK（IWidget* sender，int posX，int posY， mousecode id）；
        //@param1 _sender回调PVOIDINTINTMOUSECODE_CALLBACK，@param2 和 @param3 代表鼠标的位置，@param4 鼠标按键的id。
        //virtual void       setMouseButtonPressedEvent(PVOIDINTINTMOUSECODE_CALLBACK) = 0;
        //鼠标按键松开控件，
        //函数原型：void PVOIDINTINTMOUSECODE_CALLBACK（IWidget* sender，int posX，int posY， mousecode id）；
        //@param1 _sender回调PVOIDINTINTMOUSECODE_CALLBACK，@param2 和 @param3 代表鼠标的位置，@param4 鼠标按键的id。
        //virtual void       setMouseButtonReleasedEvent(PVOIDINTINTMOUSECODE_CALLBACK) = 0;
        //键盘按键按下控件，
        //函数原型：void PVOIDKEYCODECHAR_CALLBACK（IWidget* sender，keycode key，char _char）；
        //@param1 _sender回调PVOIDKEYCODECHAR_CALLBACK，@param2 键盘按键值，@param3 _char of pressed symbol (for multilanguage applications)。
        //virtual void       setKeyButtonPressedEvent(PVOIDKEYCODECHAR_CALLBACK) = 0;
    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************