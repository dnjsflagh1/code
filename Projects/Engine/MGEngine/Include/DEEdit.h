//**********************************************************************************************************
#ifndef _H_DEEDIT_57893247587439_
#define _H_DEEDIT_57893247587439_
//**********************************************************************************************************
#include "IEdit.h"
#include "DEWidget.h"
//**********************************************************************************************************
class  MyGUI::Widget;
//**********************************************************************************************************
namespace MG
{
    class DEEdit : public IEdit, public DEWidget  
    {
    public:
                                DEEdit();
        virtual                 ~DEEdit();

    public:
        virtual IWidget*        getWidget();
        virtual void            setEditPassword(bool _value);
        virtual bool            getEditPassword();
        virtual void            setEditMultiLine(bool _value);
        virtual bool            getEditMultiLine();
        virtual void            setEditStatic(bool _value);
        virtual bool            getEditStatic();
        virtual void            addText(const std::wstring& text);
        virtual void            setTextColour(const Color& value);
        virtual const Color     getTextColour();
        virtual void            setTextAlign(MGAlign _value);
        virtual void            setFontName(const std::string& _value);
        virtual const std::string& getFontName();
        virtual void            setFontHeight(int _value);
        virtual int             getFontHeight();
		virtual void            setTextIntervalColour(Int _start, Int _count, const Color& value);
		virtual void            setTextSelection(U32 _start, U32 _end);
		virtual void            setTextSelectionColour(const Color& _value);
		virtual U32             getTextLength() const;
		virtual U32				getMaxTextLength() const;
		virtual const std::wstring& getCaption()const;
		virtual void			setCaption(std::wstring caption);
		virtual bool			clearEditText(bool _history);

    public:
        virtual void            setSelectAcceptEvent(PVOID_CALLBACK); 
        virtual void            setTextChangeEvent(PVOID_CALLBACK);
		virtual void			setEditAddFaceEvent(PVOIDPVOIDINT_CALLBACK);
		virtual void        	setShowLinkInfoEvent(PVOIDVECI2U64INTBOOL_CALLBACK); 
		virtual void        	setClickLinkEvent(PVOIDU64INT_CALLBACK);

    public: 
        //引擎事件
                Bool            setEGEdit(MyGUI::Widget* p);
                MyGUI::Widget*  getEGEdit(){return mpEGEdit;}
    
    protected:
        //引擎事件
                void            notifySelectAccept(MyGUI::Edit* p);
                void            notifyTextChange(MyGUI::Edit* p);
				void			notifyAddFace(MyGUI::Edit* _p, MyGUI::ImageBox* _pImage, Int _id);
				void			notifyShowLinkInfo(MyGUI::Edit* _p, MyGUI::IntPoint _point, __int64 _id, Int _type, Bool _isShow);
				void			notifyClickLink(MyGUI::Edit* _p, __int64 _id, Int _type);
        
    protected:
        //记录引擎对象和对应的回调函数，当引擎的回调响应时可找到client的回调函数
        static std::map<MyGUI::Edit*, PVOID_CALLBACK>                  mMapSelectAcceptCallBack;
        static std::map<MyGUI::Edit*, PVOID_CALLBACK>                  mMapTextChangeCallBack;
		static std::map<MyGUI::Edit*, PVOIDPVOIDINT_CALLBACK>		   mMapAddFaceCallBack;
		static std::map<MyGUI::Edit*, PVOIDVECI2U64INTBOOL_CALLBACK>   mMapShowLinkInfoCallBack;
		static std::map<MyGUI::Edit*, PVOIDU64INT_CALLBACK>			   mMapClickLinkCallBack;
        
    private:
        //引擎对象指针
        MyGUI::Edit*                                            mpEGEdit;
    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************