//***********************************************************************************************************
#include "stdafx.h"
#include "HeadDamage.h"
#include "ClientMain.h"
//***********************************************************************************************************
namespace MG
{
    HeadDamage::HeadDamage( CoordI pos, Str8 Resouse, Str8 group, Str8 item )
        :mSpeed(12.f)
        ,mOffsetY(0.f)
        ,mAlpha(0.8f)
        ,mMaxMoveHeight(40.f)
    {
        mImage = ClientMain::getInstance().getGui()->getImage(pos, Resouse, group, item);
        mImage->getWidget()->setAlpha(mAlpha);

        mPos.x = (Flt)pos.left, mPos.y = (Flt)pos.top;
        mIsDead = false;
        mState = HEADDAMAGE_STATE_NORMAL;
    }
    //---------------------------------------------------------------------------------------
    HeadDamage::~HeadDamage()
    {

    }
    //---------------------------------------------------------------------------------------
    void HeadDamage::resetHeadDamage( CoordI pos, Str8 Resouse, Str8 group, Str8 item )
    {
        mPos.x = (Flt)pos.left, mPos.y = (Flt)pos.top;
        mIsDead = false;
        mState = HEADDAMAGE_STATE_NORMAL;
        mOffsetY = 0.f;
        mAlpha = 0.8f;
        mSpeed = 10.f;

        mImage->getWidget()->setCoord(pos);
        mImage->setTexture(Resouse, group, item);
        mImage->getWidget()->setVisible(true);
        mImage->getWidget()->setAlpha(mAlpha);
    }
    //---------------------------------------------------------------------------------------
    void HeadDamage::close()
    {
        mImage->getWidget()->setVisible(false);
    }
    //---------------------------------------------------------------------------------------
    void HeadDamage::update( Flt delta )
    {
        switch (mState)
        {
        case HEADDAMAGE_STATE_NORMAL:
            {
                Flt deltaY = mSpeed * (delta+0.2f);
                mOffsetY += deltaY;
                if ( mSpeed > 6.f )
                    mSpeed -= 0.1f;
                else
                    mSpeed = 6.f;
                if (mOffsetY > mMaxMoveHeight)
                {
                    mPos.y -= mOffsetY - mMaxMoveHeight;
                    mState = HEADDAMAGE_STATE_FADEOUT;
                }
                else
                {
                    mPos.y -= deltaY;
                }
                mImage->getWidget()->setPosition(mPos);
            }
        	break;
        case HEADDAMAGE_STATE_FADEOUT:
            {
                mAlpha -= 0.02f;
                if (mAlpha <= 0.f)
                {
                    mIsDead = true;
                }
                else
                    mImage->getWidget()->setAlpha(mAlpha);
            }
            break;
        }
    }
}