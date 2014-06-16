//**********************************************************************************************************
#ifndef _H_IEDIT_578941320_
#define _H_IEDIT_578941320_
//**********************************************************************************************************
#include "MGEngineInterfacePreqs.h"
#include "IWidget.h"
//**********************************************************************************************************
//编辑文字接口
namespace MG
{
    class IEdit
    {
    public:
        //获得控件的共同属性部分。
        virtual IWidget*    getWidget() = 0;
        //设置为密码模式
        virtual void        setEditPassword(bool _value) = 0;
        //或得是否为密码模式
        virtual bool        getEditPassword() = 0;
        //设置为多行模式
        virtual void        setEditMultiLine(bool _value) = 0;
        //获得是否为多行模式
        virtual bool        getEditMultiLine() = 0;
        //设置为静态模式，相当于Text，但是可以多行显示。
        virtual void        setEditStatic(bool _value) = 0;
        //获得是否为静态模式。
        virtual bool        getEditStatic() = 0;
        //加text。
        virtual void        addText(const std::wstring& text) = 0;
        //
        virtual void            setTextColour(const Color& value) = 0;
        //
        virtual const Color     getTextColour() = 0;
        /** Set widget text align */
        virtual void            setTextAlign(MGAlign _value) = 0;
        /** Set widget text font */
        virtual void            setFontName(const std::string& _value) = 0;
        /** Get widget text font name */
        virtual const std::string& getFontName() = 0;
        /** Set widget text font height */
        virtual void            setFontHeight(int _value) = 0;
        /** Get widget text font height */
        virtual int             getFontHeight() = 0 ;
		/** Colour interval */
		virtual void setTextIntervalColour(Int _start, Int _count, const Color& value) = 0;
		/** set selected text */
		virtual void setTextSelection(U32 _start, U32 _end) = 0;
		/** Colour selected text */
		virtual void setTextSelectionColour(const Color& _value) = 0;
		virtual U32 getTextLength() const = 0;
		virtual U32 getMaxTextLength() const = 0;
		virtual const std::wstring& getCaption()const = 0;
		virtual void setCaption(std::wstring caption) = 0;
		virtual bool clearEditText(bool _history) = 0;

     public://事件
        virtual void        setSelectAcceptEvent(PVOID_CALLBACK) = 0;
        virtual void        setTextChangeEvent(PVOID_CALLBACK) = 0;

		//PVOIDPVOIDINT_CALLBACK回调函数的三个参数详解
		//第一个参数pvoid 为IEdit自己的指针
		//第二个参数pvoid 为IImage指针，他是IEdit控件内的图片
		//第三个参数int 为图片的ID。
		//PVOIDPVOIDINT_CALLBACK的功能是设置IImage图片的内容
		virtual void		setEditAddFaceEvent(PVOIDPVOIDINT_CALLBACK) = 0;

		//PVOIDVECI2U64INTBOOL_CALLBACK的五个参数详解
		//第一个参数pvoid 为IEdit自己的指针
		//第二个参数vecI2为鼠标的位置
		//第三个参数u64 为超链接的id号，
		//第四个参数int 为超链接的类型。
		//第五个参数bool 为是否显示超链接。
		//PVOIDVECI2U64INTBOOL_CALLBACK 是是否显示tips。
		virtual void        setShowLinkInfoEvent(PVOIDVECI2U64INTBOOL_CALLBACK) = 0; 

		//PVOIDU64INT_CALLBACK的三个参数详解
		//第一个参数pvoid 为IEdit自己的指针
		//第三个参数u64 为超链接的id号，
		//第四个参数int 为超链接的类型。
		//PVOIDU64INT_CALLBACK的功能是点击超链接的事件。
		virtual void        setClickLinkEvent(PVOIDU64INT_CALLBACK) = 0;
    protected:
    private:
    };
}

//**********************************************************************************************************
#endif
//**********************************************************************************************************