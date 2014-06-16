//**********************************************************************************************************
#include "stdafx.h"
#include "DEProgress.h"
//**********************************************************************************************************
//**********************************************************************************************************
namespace MG
{ 
    DEProgress::DEProgress()
        :mpEGProgress(nullptr)
    {

    }
    //-----------------------------------------------------------------------------
    DEProgress::~DEProgress()
    {

    }
    //-----------------------------------------------------------------------------
    Bool DEProgress::setEGProgress( MyGUI::Widget* p )
    {
        assert( p );
        mpEGProgress = p->castType<MyGUI::ProgressEx>();
        assert( mpEGProgress );
        setEGWidget(p);
        return true;
    }
    //-----------------------------------------------------------------------------
    IWidget* DEProgress::getWidget()
    {
        setEGWidget(mpEGProgress);
        return this;
    }

    //-----------------------------------------------------------------------------
    void DEProgress::setProgressPosition( Flt _value )
    {
        assert(mpEGProgress);
        mpEGProgress->setProgressPosition(_value);
    }
    //-----------------------------------------------------------------------------
    Flt DEProgress::getProgressPosition(  )
    {
        assert(mpEGProgress);
        return mpEGProgress->getProgressPosition();
    }
	//-----------------------------------------------------------------------------
    void DEProgress::setTopTexture( const Str8 resName, const Str8 groupName, const Str8 itemName )
    {
        assert(mpEGProgress);
        mpEGProgress->setTopItemResource("");

        mpEGProgress->setTopItemResource(resName);
        mpEGProgress->setTopItemGroup(groupName);
        mpEGProgress->setTopItemName(itemName);
    }
    //-----------------------------------------------------------------------------
    void DEProgress::setBottomTexture( const Str8 resName, const Str8 groupName, const Str8 itemName )
    {
        assert(mpEGProgress);
        mpEGProgress->setItemResource("");

        mpEGProgress->setItemResource(resName);
        mpEGProgress->setItemGroup(groupName);
        mpEGProgress->setItemName(itemName);
    }
    //-----------------------------------------------------------------------------
    void DEProgress::setTexture( const Str8 resName, const Str8 groupName, const Str8 itemName )
    {
        assert(mpEGProgress);
        mpEGProgress->setProgressItemResource("");

        mpEGProgress->setProgressItemResource(resName);
        mpEGProgress->setProgressItemGroup(groupName);
        mpEGProgress->setProgressItemName(itemName);
    }
}