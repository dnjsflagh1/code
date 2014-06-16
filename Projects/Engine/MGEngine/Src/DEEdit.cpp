//**********************************************************************************************************
#include "stdafx.h"
#include "DEEdit.h"
#include "GuiDelegateElementPool.h"
//**********************************************************************************************************
//**********************************************************************************************************
namespace MG
{ 
    std::map<MyGUI::Edit*, PVOID_CALLBACK>                  DEEdit::mMapSelectAcceptCallBack;
    std::map<MyGUI::Edit*, PVOID_CALLBACK>                  DEEdit::mMapTextChangeCallBack;
	std::map<MyGUI::Edit*, PVOIDPVOIDINT_CALLBACK>			DEEdit::mMapAddFaceCallBack;
	std::map<MyGUI::Edit*, PVOIDVECI2U64INTBOOL_CALLBACK>   DEEdit::mMapShowLinkInfoCallBack;
	std::map<MyGUI::Edit*, PVOIDU64INT_CALLBACK>			DEEdit::mMapClickLinkCallBack;


    DEEdit::DEEdit()
        :mpEGEdit(nullptr)
    {

    }
    //-----------------------------------------------------------------------------
    DEEdit::~DEEdit()
    {

    }
    //-----------------------------------------------------------------------------
    Bool DEEdit::setEGEdit( MyGUI::Widget* p )
    {
        assert( p );
        mpEGEdit = p->castType<MyGUI::Edit>();
        assert( mpEGEdit );
        setEGWidget(p);
        return true;
    }
    //-----------------------------------------------------------------------------
    IWidget* DEEdit::getWidget()
    {
        assert( mpEGEdit );
        setEGWidget(mpEGEdit);
        return this;
    }
    //-----------------------------------------------------------------------------
    void DEEdit::setSelectAcceptEvent( PVOID_CALLBACK pfunc )
    {
        assert ( mpEGEdit );  
        mMapSelectAcceptCallBack[mpEGEdit] = pfunc;
        mpEGEdit->eventEditSelectAccept = MyGUI::newDelegate(this, &DEEdit::notifySelectAccept);
    }
    //-----------------------------------------------------------------------------
    void DEEdit::setTextChangeEvent( PVOID_CALLBACK pfunc )
    {
        assert ( mpEGEdit );  
        mMapTextChangeCallBack[mpEGEdit] = pfunc;
        mpEGEdit->eventEditTextChange = MyGUI::newDelegate(this, &DEEdit::notifyTextChange);
    }
    //-----------------------------------------------------------------------------
    void DEEdit::notifySelectAccept( MyGUI::Edit* p )
    {
        mpEGEdit = p;
        assert ( mpEGEdit );
        setEGWidget(p);
        (mMapSelectAcceptCallBack[mpEGEdit])(this);
    }
    //-----------------------------------------------------------------------------
    void DEEdit::notifyTextChange( MyGUI::Edit* p )
    {
        mpEGEdit = p;
        assert ( mpEGEdit );
        setEGWidget(p);
        (mMapTextChangeCallBack[mpEGEdit])(this);
    }
    //-----------------------------------------------------------------------------
    void DEEdit::setEditPassword( bool _value )
    {
        assert(mpEGEdit);
        mpEGEdit->setEditPassword(_value);
    }
    //-----------------------------------------------------------------------------
    bool DEEdit::getEditPassword()
    {
        assert(mpEGEdit);
        return mpEGEdit->getEditPassword();
    }
    //-----------------------------------------------------------------------------
    void DEEdit::setEditMultiLine( bool _value )
    {
        assert(mpEGEdit);
        mpEGEdit->setEditMultiLine(_value);
    }
    //-----------------------------------------------------------------------------
    bool DEEdit::getEditMultiLine()
    {
        assert(mpEGEdit);
        return mpEGEdit->getEditMultiLine();
    }
    //-----------------------------------------------------------------------------
    void DEEdit::setEditStatic( bool _value )
    {
         assert(mpEGEdit);
         mpEGEdit->setEditStatic(_value);
    }
    //-----------------------------------------------------------------------------
    bool DEEdit::getEditStatic()
    {
         assert(mpEGEdit);
         return mpEGEdit->getEditStatic();
    }
    //-----------------------------------------------------------------------------
    void DEEdit::addText( const std::wstring& text )
    {
         assert(mpEGEdit);
         mpEGEdit->addText(text);
    }
    //-----------------------------------------------------------------------------
    void DEEdit::setTextColour( const Color& value )
    {
        assert(mpEGEdit);
        mpEGEdit->setTextColour(MyGUI::Colour(value.r, value.g, value.b, value.a));
    }
    //-----------------------------------------------------------------------------
    const Color DEEdit::getTextColour()
    {
        assert(mpEGEdit);
        MyGUI::Colour tempColor = mpEGEdit->getTextColour();
        return Color(tempColor.red, tempColor.green, tempColor.blue, tempColor.alpha);
    }
    //-----------------------------------------------------------------------------
    void DEEdit::setTextAlign( MGAlign _value )
    {
        assert(mpEGEdit);
        MyGUI::Align temp((MyGUI::Align::Enum)(int)_value);
        mpEGEdit->setTextAlign(temp);
    }
    //-----------------------------------------------------------------------------
    void DEEdit::setFontName( const std::string& _value )
    {
        assert(mpEGEdit);
        mpEGEdit->setFontName(_value);
    }
    //-----------------------------------------------------------------------------
    const std::string& DEEdit::getFontName()
    {
        assert(mpEGEdit);
        return mpEGEdit->getFontName();
    }
    //-----------------------------------------------------------------------------
    void DEEdit::setFontHeight( int _value )
    {
        assert(mpEGEdit);
        mpEGEdit->setFontHeight(_value);
    }
    //-----------------------------------------------------------------------------
    int DEEdit::getFontHeight()
    {
        assert(mpEGEdit);
        return mpEGEdit->getFontHeight();
    }
	//-----------------------------------------------------------------------------
	void DEEdit::setTextIntervalColour( Int _start, Int _count, const Color& value )
	{
        assert(mpEGEdit);
        mpEGEdit->setTextIntervalColour(_start,_count,MyGUI::Colour(value.r/255.0f, value.g/255.0f, value.b/255.0f, value.a));
		
	}
	//-----------------------------------------------------------------------------
	void DEEdit::setTextSelection( U32 _start, U32 _end )
	{
         assert(mpEGEdit);
         mpEGEdit->setTextSelection(_start,_end);

	}
	//-----------------------------------------------------------------------------
	void DEEdit::setTextSelectionColour( const Color& _value )
	{
		assert(mpEGEdit);
        mpEGEdit->setTextSelectionColour(MyGUI::Colour(_value.r/255.0f, _value.g/255.0f, _value.b/255.0f, _value.a));

	}
	//-----------------------------------------------------------------------------
	MG::U32 DEEdit::getTextLength() const
	{
		assert(mpEGEdit);
        return mpEGEdit->getTextLength();

	}
	//-----------------------------------------------------------------------------
	MG::U32 DEEdit::getMaxTextLength() const
	{
		assert(mpEGEdit);
		return mpEGEdit->getMaxTextLength();

	}
	//-----------------------------------------------------------------------------
	bool DEEdit::clearEditText(bool _history) 
	{
		assert(mpEGEdit);
		return mpEGEdit->clearEditText(_history);

	}
	//-----------------------------------------------------------------------------
	const std::wstring& DEEdit::getCaption() const
	{
		assert(mpEGEdit);
		return mpEGEdit->getCaption().asWStr();
	}
	//-----------------------------------------------------------------------------
	void DEEdit::setEditAddFaceEvent( PVOIDPVOIDINT_CALLBACK pfunc )
	{
		assert ( mpEGEdit );  
		mMapAddFaceCallBack[mpEGEdit] = pfunc;
		mpEGEdit->mEventEditAddFace = MyGUI::newDelegate(this, &DEEdit::notifyAddFace);
	}
	//-----------------------------------------------------------------------------
	void DEEdit::setShowLinkInfoEvent( PVOIDVECI2U64INTBOOL_CALLBACK pfunc )
	{
		assert ( mpEGEdit );  
		mMapShowLinkInfoCallBack[mpEGEdit] = pfunc;
		mpEGEdit->mEventShowLinkInfo = MyGUI::newDelegate(this, &DEEdit::notifyShowLinkInfo);
	}
	//-----------------------------------------------------------------------------
	void DEEdit::setClickLinkEvent( PVOIDU64INT_CALLBACK pfunc )
	{
		assert ( mpEGEdit );  
		mMapClickLinkCallBack[mpEGEdit] = pfunc;
		mpEGEdit->mEventClickLink = MyGUI::newDelegate(this, &DEEdit::notifyClickLink);
	}
	//-----------------------------------------------------------------------------
	void DEEdit::notifyAddFace( MyGUI::Edit* _p, MyGUI::ImageBox* _pImage, Int _id )
	{
		mpEGEdit = _p;
		assert ( mpEGEdit );
		setEGWidget(_p);
		(mMapAddFaceCallBack[mpEGEdit])(this, GuiDgElmPool::getInstance().getDEImage(_pImage), _id);
	}
	//-----------------------------------------------------------------------------
	void DEEdit::notifyShowLinkInfo( MyGUI::Edit* _p, MyGUI::IntPoint _point, __int64 _id, Int _type, Bool _isShow )
	{
		mpEGEdit = _p;
		assert ( mpEGEdit );
		setEGWidget(_p);

		VecI2 tempVecI2(_point.left, _point.top);

		(mMapShowLinkInfoCallBack[mpEGEdit])(this, tempVecI2, _id, _type, _isShow);
	}
	//-----------------------------------------------------------------------------
	void DEEdit::notifyClickLink( MyGUI::Edit* _p, __int64 _id, Int _type )
	{
		mpEGEdit = _p;
		assert ( mpEGEdit );
		setEGWidget(_p);

		(mMapClickLinkCallBack[mpEGEdit])(this, _id, _type);
	}
	//-----------------------------------------------------------------------------
	void DEEdit::setCaption(std::wstring caption)
	{
		assert(mpEGEdit);
		mpEGEdit->setCaption(caption);
	}
}