/******************************************************************************/
#ifndef _IGUI_H_
#define _IGUI_H_
/******************************************************************************/
#include "MGEngineInterfacePreqs.h"
#include "IWidget.h"
/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //用户排版对象接口
    /******************************************************************************/
    class ILayout
    {
    public:
        virtual Bool            isVisible() = 0;
        virtual void            setVisible(Bool bVisible) = 0;
        virtual IButton*        getButton( const Str8 name ) = 0;
        virtual IEdit*          getEdit( const Str8 name ) = 0;
        virtual IForm*          getForm( const Str8 name ) = 0;
        virtual IImage*         getImage( const Str8 name ) = 0;
        virtual IProgress*      getProgress( const Str8 name ) = 0;
        virtual IText*          getText( const Str8 name ) = 0;
        virtual IViewScroll*    getViewScroll( const Str8 name ) = 0;
        virtual IWidget*        getWidget( const Str8 name ) = 0; 
        virtual IList*          getList( const Str8 name ) = 0;
        virtual ITab*           getTab( const Str8 name ) = 0;
        virtual ITabItem*       getTabItem( const Str8 name ) = 0;
        virtual IComboBox*      getComboBox( const Str8 name ) = 0;
        virtual IMixTree*       getMixTree( const Str8 name ) = 0;
        virtual IRollingText*   getRollingText( const Str8 name ) = 0;
        virtual IMixList*       getMixList( const Str8 name ) = 0;
        virtual IMixListRow*    getMixListRow( const Str8 name ) = 0;
		virtual	IHScroll*		getHScroll( const Str8 name ) = 0;
		virtual	IVScroll*		getVScroll( const Str8 name ) = 0;
		virtual ITimeText*		getTimeText( const Str8 name ) = 0;
        //---------------------------------------------------------------------
        virtual Bool            isMouseInUI() = 0;    //鼠标点的控件是否在自己身上。
    };

    /******************************************************************************/
	//用户界面接口
	/******************************************************************************/
    class IGui
	{
	public:
        //加载layout资源，并返回layout资源。
        virtual ILayout*        loadLayOut(const Str fileName)=0;
        //获得layout资源
        virtual ILayout*        getLayOut(const Str fileName)=0;

		virtual void			resizeWindow() = 0;

        //可获得不变的指针，即可保存指针，由自己管理，由引擎销毁
        virtual     IText*              getText(const MGTextDs* pTds, CoordI coord, std::wstring caption, Bool isTop = false) = 0;
        virtual     IText*              getText(const MGTextDs* pTds, VecI2 pos, VecI2 size, std::wstring caption, Bool isTop = false) = 0;
        virtual     IText*              getText(const MGTextDs* pTds, Int left, Int top, Int width, Int height, std::wstring caption, Bool isTop = false) = 0;

        virtual     IEdit*              getEdit(const MGTextDs* pTds, CoordI coord, std::wstring caption, Bool isTop = false) = 0;
        virtual     IEdit*              getEdit(const MGTextDs* pTds, VecI2 pos, VecI2 size, std::wstring caption, Bool isTop = false) = 0;
        virtual     IEdit*              getEdit(const MGTextDs* pTds, Int left, Int top, Int width, Int height, std::wstring caption, Bool isTop = false) = 0;

        virtual     IProgress*          getProgress(CoordI coord, U32 range, U32 position, Bool isTop = false) = 0;
        virtual     IProgress*          getProgress(VecI2 pos, VecI2 size, U32 range, U32 position, Bool isTop = false) = 0;
        virtual     IProgress*          getProgress(Int left, Int top, Int width, Int height, U32 range, U32 position, Bool isTop = false) = 0;

        virtual     IImage*             getImage(CoordI coord, std::string imagename, Bool isTop = false) = 0;
        virtual     IImage*             getImage(VecI2 pos, VecI2 size, std::string imagename, Bool isTop = false) = 0;
        virtual     IImage*             getImage(Int left, Int top, Int width, Int height, std::string imagename, Bool isTop = false) = 0;

        virtual     IImage*             getImage(CoordI coord, std::string imagenrecouse, std::string group, std::string item, Bool isTop = false) = 0;
        virtual     IImage*             getImage(VecI2 pos, VecI2 size, std::string imagenrecouse, std::string group, std::string item, Bool isTop = false) = 0;
        virtual     IImage*             getImage(Int left, Int top, Int width, Int height, std::string imagenrecouse, std::string group, std::string item, Bool isTop = false) = 0;
        
        virtual     void                destroyImage(IImage*& pImage) = 0;
        virtual     void                destroyText(IText*& pText) = 0;
        virtual     void                destroyEdit(IEdit*& pImage) = 0;
        virtual     void                destroyProgress(IProgress*& pText) = 0;

        //直接描绘，不返回，由引擎管理，由引擎销毁
        virtual     void                MGText(const MGTextDs*& pTds, CoordI coord, std::wstring caption, Bool isTop = false) = 0;
        virtual     void                MGText(const MGTextDs*& pTds, VecI2 pos, VecI2 size, std::wstring caption, Bool isTop = false) = 0;
        virtual     void                MGText(const MGTextDs*& pTds, Int left, Int top, Int width, Int height, std::wstring caption, Bool isTop = false) = 0;

        virtual     void                MGEdit(const MGTextDs* pTds, CoordI coord, std::wstring caption, Bool isTop = false) = 0;
        virtual     void                MGEdit(const MGTextDs* pTds, VecI2 pos, VecI2 size, std::wstring caption, Bool isTop = false) = 0;
        virtual     void                MGEdit(const MGTextDs* pTds, Int left, Int top, Int width, Int height, std::wstring caption, Bool isTop = false) = 0;

        virtual     void                MGProgress(CoordI coord, U32 range, U32 position, Bool isTop = false) = 0;
        virtual     void                MGProgress(VecI2 pos, VecI2 size, U32 range, U32 position, Bool isTop = false) = 0;
        virtual     void                MGProgress(Int left, Int top, Int width, Int height, U32 range, U32 position, Bool isTop = false) = 0;

        virtual     void                MGImage(CoordI coord, std::string imagename, Bool isTop = false) = 0;
        virtual     void                MGImage(VecI2 pos, VecI2 size, std::string imagename, Bool isTop = false) = 0;
        virtual     void                MGImage(Int left, Int top, Int width, Int height, std::string imagename, Bool isTop = false) = 0;

        virtual     void                MGImage(CoordI coord, std::string imagenrecouse, std::string group, std::string item, Bool isTop = false) = 0;
        virtual     void                MGImage(VecI2 pos, VecI2 size, std::string imagenrecouse, std::string group, std::string item, Bool isTop = false) = 0;
        virtual     void                MGImage(Int left, Int top, Int width, Int height, std::string imagenrecouse, std::string group, std::string item, Bool isTop = false) = 0;
        
        //计算字符串的长度,高度。
        virtual     U32                 getLengthStr(Str16 src, Str8 fontName = "") = 0;
        virtual     U32                 getLengthStr(Str8 src, Str8 fontName = "") = 0;
        //添加\n
        virtual     U32                 getHeightStrAddBreak(Str16& src, Int width, Str8 fontName = "") = 0;
        virtual     U32                 getHeightStrAddBreak(Str8& src, Int width, Str8 fontName = "") = 0;
        //不添加\n
        virtual     U32                 getHeightStr(Str16 src, Int width, Str8 fontName = "") = 0;
        virtual     U32                 getHeightStr(Str8 src, Int width, Str8 fontName = "") = 0;
        virtual     U32                 getHeightChar(Str8 fontName = "") = 0;
        //根据给定宽度获得字符串在这一行的最后一个字符的索引值。（从1开始计算）
        virtual     U32                 getIndexByWidth(Str16 src, U32 width, Str8 fontName = "") = 0;
        virtual     U32                 getIndexByWidth(Str8 src, U32 width, Str8 fontName = "") = 0;
        //获得图片的长和宽。
        virtual     VecI2               getImageSize(Str8 textureName) = 0;
        virtual     VecI2               getImageSize(Str8 imageRecouse, Str8 group, Str8 item) = 0;

        //获取鼠标的焦点是否在UI上。
        virtual     Bool                isMouseCanHoldUI() = 0; 
		//获取键盘的焦点是否在UI上。
		virtual     Bool                isKeyCanHoldUI() = 0;  
    };

}

/******************************************************************************/
#endif
