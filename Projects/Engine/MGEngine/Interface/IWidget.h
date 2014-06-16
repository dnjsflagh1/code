//**********************************************************************************************************
#ifndef _H_IWIDGET_574893578_
#define _H_IWIDGET_574893578_
//**********************************************************************************************************
#include "MGEngineInterfacePreqs.h"
#include "IAny.h"
//**********************************************************************************************************
//��ť�ӿ�
namespace MG
{
    class IWidget
    {
    public:
        //ת��
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

        //�ֿؼ������ؼ�
        //createһ���ӿؼ�
        virtual IWidget*        createWidget(const std::string& _type, const std::string& _skin, const CoordI& _coord, const Int& _align, const std::string& _name) = 0;   
        //����ӿؼ�����
        virtual Int             getChildCount() = 0;
        //����index����ӿؼ�
        virtual IWidget*        getChildAt(Int index) = 0;
        //��ø��ؼ������ظ��ؼ�������
        virtual IWidget&        getParent() = 0;
        //����Ƥ��
        virtual void            changeWidgetSkin(const std::string& _skinname) = 0;
		//�����ӿؼ�
		virtual IWidget*		findWidget(const std::string& _name) = 0;

        //��������
        //��ÿؼ��Ĵ�С����ߣ������ؿؼ���С��
        virtual Vec2            getSize() = 0;
        //��ÿؼ�����Ը��ؼ���λ�ã����ص�ǰ�õ�λ�á�
        virtual Vec2            getPosition() = 0;
        //���ÿؼ��Ĵ�С
        virtual void            setSize(const Vec2& mgSize) = 0;
        //���ÿؼ�����Ը��ؼ���λ��
        virtual void            setPosition(const Vec2& mgPos) = 0;
        // Set widget ��Alphaֵ   0 -- 1
        virtual void            setAlpha(float _value) = 0;
        // Get widget ��Alphaֵ
        virtual float           getAlpha() = 0;
        // �����Ƿ�̳и��ؼ� ��Alphaֵ  
        virtual void            setInheritsAlpha(bool _value) = 0;
        // ����Ƿ�̳и��ؼ� ��Alphaֵ
        virtual bool            isInheritsAlpha() = 0;
        // �����Ƿ���Ҫ���key focus��
        virtual void            setNeedKeyFocus(bool _value) = 0;
        // ����Ƿ���Ҫ���key focus��
        virtual bool            isNeedKeyFocus() = 0;
        // �����Ƿ���Ҫ���Mouse focus��
        virtual void            setNeedMouseFocus(bool _value) = 0;
        // ����Ƿ���Ҫ���Mouse focus��
        virtual bool            isNeedMouseFocus() = 0;
        // �����Ƿ�̳и��ؼ� ��Mouse focus����
        virtual void            setInheritsPick(bool _value) = 0;
        // ����Ƿ�̳и��ؼ� ��Mouse focus����
        virtual bool            isInheritsPick() = 0;
        // �����Ƿ����
        virtual void            setEnabled(bool _value) = 0;
        // ����Ƿ����
        virtual bool            isEnabled() = 0;
        // ��ÿͻ������С��λ�á�
        virtual CoordI          getClientCoord() = 0;
        //�����Ƿ���ҪTips��
        virtual void            setNeedToolTip(bool _value) = 0;
        //����Ƿ���ҪTips��
        virtual bool            getNeedToolTip() = 0;
        /** Set coordinates (position and size) */
        virtual void            setCoord(const CoordI& _value) = 0;
        /** Get coordinates (position and size) */
        virtual CoordI          getCoord() = 0;
        /** Get coordinate in screen coordinates */
        virtual CoordI          getAbsoluteCoord() = 0;
        //�����Լ�Ϊ��갴���Ľ���
        virtual void            setKeyFocus(Bool focus) = 0;
        //��õ�ǰ����갴�������Ƿ����Լ���
        virtual Bool            isKeyFocus() = 0 ;
        //! Get name of widget
        virtual const std::string& 
                                getName() = 0;
        //�Ƿ�ɼ���
        virtual Bool            isVisible() = 0;
        //���ÿؼ��Ƿ�ɼ���
        virtual Bool            setVisible(Bool bVisible) = 0;
        //���ÿؼ� caption
        virtual void            setCaption(const std::wstring& caption) = 0;
        //��ÿؼ� caption
        virtual std::wstring    getCaption() = 0;

		//���ÿؼ�����ʱ���ر�
		virtual void			setCloseTime(Flt lastTime) = 0;

		//��Ӱ�������ڰ������ֵĿؼ��������Ǽ̳���TextBox������ᱨ��
		//������Ӱ
		virtual void			setTextShadow(Bool _value) = 0;
		//������Ӱ��ɫ
		virtual void			setTextShadowColour(const Color& _value) = 0;
		//���ؼ�������ɫ
		virtual void			setColour(const Color& _value) = 0;
		
		//���ö���
		virtual void			setAction( WIDGET_ACTION _type, Flt _actionTime, Bool _isClose ) = 0;

    public: //usedata
        //����usestring
        virtual void                setUserString(const std::string& _key, const std::string& _value) = 0;
        //���usestring
        virtual const std::string&  getUserString(const std::string& _key) = 0;
        //ɾ��usestring
        virtual bool                clearUserString(const std::string& _key) = 0;
        //ɾ�����е�usestring
        virtual void                clearUserStrings() = 0; 
        //key�Ƿ����ҵ�usestring
        virtual bool                isUserString(const std::string& _key) = 0;
        //����anydata
        virtual void                setUserData(IAny _data) = 0;
        //���anydata
        virtual IAny*               getUserData(bool _throw = true) = 0;
        

    public://�¼�(��Щ���ǹ��õ��¼�����)
		//���ÿؼ��رյ��õĺ�����lastTime��ʾ����ʱ���ر�
		virtual void			setCloseEvent(Flt lastTime, PVOID_CALLBACK func) = 0;
        //�ؼ���Tips��Ϣ��
        //����ԭ�ͣ�void (__cdecl *PVOIDBOOLINTINTINT_CALLBACK)(void*, Bool, Int, Int, Int)��
        //@param1 _sender�ص�PVOIDBOOLINTINTINT_CALLBACK��@param2 �Ƿ���ʾTips��true��ʾ��false����ʾ��@param3&4 ���λ�ã�@param5����ؼ���һ�飬��ʾ����һ���е�Index��
        virtual void            setToolTipsEvent(PVOIDBOOLINTINT_CALLBACK) = 0;
        virtual void            setMouseButtonClickEvent(PVOID_CALLBACK) = 0;
		virtual void            setMouseButtonRightClickEvent(PVOID_CALLBACK) = 0;
        virtual void            setMouseButtonDoubleClickEvent(PVOID_CALLBACK) = 0;
        virtual void            setMouseButtonPressedEvent(PVOIDINTINTMOUSECODE_CALLBACK) = 0;
        virtual void            setMouseButtonReleasedEvent(PVOIDINTINTMOUSECODE_CALLBACK) = 0;
        //�ؼ�ʧȥ���̽��㣬
        //����ԭ�ͣ�void PVOIDPVOID_CALLBACK��IWidget* sender��IWidget* older����
        //@param1 _sender�ص�PVOIDPVOID_CALLBACK��@param2 ��ý���Ŀؼ���nullPtr
        virtual void       setKeyLostFocusEvent(PVOIDPVOID_CALLBACK) = 0;
        //�ؼ���ü��̽��㣬
        //����ԭ�ͣ�void PVOIDPVOID_CALLBACK��IWidget* sender��IWidget* older����
        //@param1 _sender�ص�PVOIDPVOID_CALLBACK��@param2 ��ý���Ŀؼ���nullPtr
        //virtual void       setKeySetFocusEvent(PVOIDPVOID_CALLBACK) = 0;
        //�ؼ�ʧȥ��꽹�㣬
        //����ԭ�ͣ�void PVOIDPVOID_CALLBACK��IWidget* sender��IWidget* older����
        //@param1 _sender�ص�PVOIDPVOID_CALLBACK��@param2 ��ý���Ŀؼ���nullPtr
        virtual void       setMouseLostFocusEvent(PVOIDPVOID_CALLBACK) = 0;
        //�ؼ������꽹�㣬
        //����ԭ�ͣ�void PVOIDPVOID_CALLBACK��IWidget* sender��IWidget* older����
        //@param1 _sender�ص�PVOIDPVOID_CALLBACK��@param2 ʧȥ����Ŀؼ�
        virtual void       setMouseSetFocusEvent(PVOIDPVOID_CALLBACK) = 0;
        //�ؼ��������ҷ��
        //����ԭ�ͣ�void PVOIDINTINT_CALLBACK��IWidget* sender��int offsetX�� int offsetX����
        //@param1 _sender�ص�PVOIDINTINT_CALLBACK��@param2 �� @param3 ��������ƫ�ơ�
        virtual void       setMouseDragEvent(PVOIDINTINT_CALLBACK) = 0;
        //����ڿؼ����ƶ���
        //����ԭ�ͣ�void PVOIDINTINT_CALLBACK��IWidget* sender��int posX�� int posY����
        //@param1 _sender�ص�PVOIDINTINT_CALLBACK��@param2 �� @param3 ��������λ��
        //virtual void       setMouseMoveEvent(PVOIDINTINT_CALLBACK) = 0;
        //������ؼ���
        //����ԭ�ͣ�void PVOID_CALLBACK��IWidget* sender����
        //@param1 _sender�ص�PVOID_CALLBACK��
        //virtual void       setMouseButtonClickEvent(PVOID_CALLBACK) = 0;
        //���˫���ؼ���
        //����ԭ�ͣ�void PVOID_CALLBACK��IWidget* sender����
        //@param1 _sender�ص�PVOID_CALLBACK��
        //virtual void       setMouseButtonDoubleClickEvent(PVOID_CALLBACK) = 0;
        //�ؼ�����꽹��仯��
        //����ԭ�ͣ�void PVOIDBOOL_CALLBACK��IWidget* sender��bool isFocus����
        //@param1 _sender�ص�PVOIDBOOL_CALLBACK��@param2 �Ƿ�����꽹�㡣
        virtual void       setMouseChangeRootFocusEvent(PVOIDBOOL_CALLBACK) = 0;
        //�ؼ��ļ��̽���仯��
        //����ԭ�ͣ�void PVOIDBOOL_CALLBACK��IWidget* sender��bool isFocus����
        //@param1 _sender�ص�PVOIDBOOL_CALLBACK��@param2 �Ƿ����̱꽹�㡣
        virtual void       setKeyChangeRootFocusEvent(PVOIDBOOL_CALLBACK) = 0;
        //���̰����ɿ��ؼ���
        //����ԭ�ͣ�void PVOIDBYTE_CALLBACK��IWidget* sender��keycode key����
        //@param1 _sender�ص�PVOIDBYTE_CALLBACK��@param2 ���̰���ֵ��
        //virtual void       setKeyButtonReleasedEvent(PVOIDBYTE_CALLBACK) = 0;
        //����м��ڿؼ��Ϲ�����
        //����ԭ�ͣ�void PVOIDINTINT_CALLBACK��IWidget* sender��int rel����
        //@param1 _sender�ص�PVOIDINTINT_CALLBACK��@param2 relative wheel position��
        //virtual void       setMouseWheelEvent(PVOIDINT_CALLBACK) = 0;
        //��갴�����¿ؼ���
        //����ԭ�ͣ�void PVOIDINTINTMOUSECODE_CALLBACK��IWidget* sender��int posX��int posY�� mousecode id����
        //@param1 _sender�ص�PVOIDINTINTMOUSECODE_CALLBACK��@param2 �� @param3 ��������λ�ã�@param4 ��갴����id��
        //virtual void       setMouseButtonPressedEvent(PVOIDINTINTMOUSECODE_CALLBACK) = 0;
        //��갴���ɿ��ؼ���
        //����ԭ�ͣ�void PVOIDINTINTMOUSECODE_CALLBACK��IWidget* sender��int posX��int posY�� mousecode id����
        //@param1 _sender�ص�PVOIDINTINTMOUSECODE_CALLBACK��@param2 �� @param3 ��������λ�ã�@param4 ��갴����id��
        //virtual void       setMouseButtonReleasedEvent(PVOIDINTINTMOUSECODE_CALLBACK) = 0;
        //���̰������¿ؼ���
        //����ԭ�ͣ�void PVOIDKEYCODECHAR_CALLBACK��IWidget* sender��keycode key��char _char����
        //@param1 _sender�ص�PVOIDKEYCODECHAR_CALLBACK��@param2 ���̰���ֵ��@param3 _char of pressed symbol (for multilanguage applications)��
        //virtual void       setKeyButtonPressedEvent(PVOIDKEYCODECHAR_CALLBACK) = 0;
    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************