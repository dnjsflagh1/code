/******************************************************************************/
#include "stdafx.h"
#include "BrushSystem.h"
#include "BrushShape.h"
#include "BrushStyle.h"
#include "TerrainChunk.h"
#include "EngineMain.h"
#include "Scene.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    const Str BrushSystem::FACADE_NAME = "BRUSHSYSTEM_FACADE_NAME";

    //-----------------------------------------------------------------------
    BrushSystem::BrushSystem()
        :mSize(100)
        ,mSpeed(1.0)
		,mActiveTextureLayerIndex(0)
        ,mActiveBatchEntityLayerIndex(0)
    {
        mActiveBrushShape = getBrushCircleShape();
        mActiveBrushStyle = getBrushPaintStyle();
    }

    //-----------------------------------------------------------------------
    BrushSystem::~BrushSystem()
    {
        
    }

    //-----------------------------------------------------------------------
    void BrushSystem::setStartPos(Vec3 pos)
    {
        mStartPos = pos;

        //////////////////////////////////////////////////////////////

        Scene* scene = EngineMain::getInstance().getFirstScene();
        if ( scene )
        {
			if (mActiveBrushShape == getBrushCircleShape())
			{
				ITerrainCircleDecorator* decorator = scene->getWireframeManager()->createTerrainCircleDecorator( BrushSystem::FACADE_NAME );
				decorator->setCenter( mStartPos );
			}
			else if (mActiveBrushShape == getBrushRectShape())
			{
				ITerrainSquareDecorator* decorator = scene->getWireframeManager()->createTerrainSquareDecorator( BrushSystem::FACADE_NAME );
				decorator->setCenter( mStartPos );
			}
			else if (mActiveBrushShape == getBrushRhombusShape())
			{
				ITerrainDiamondDecorator* decorator = scene->getWireframeManager()->createTerrainDiamondDecorator( BrushSystem::FACADE_NAME );
				decorator->setCenter( mStartPos );
			}            
        }
    }

    //-----------------------------------------------------------------------
    Vec3 BrushSystem::getStartPos()
    {
        return mStartPos;
    }

    //-----------------------------------------------------------------------
    void BrushSystem::setEndPos(Vec3 pos)
    {
        mEndPos = pos;
    }

    //-----------------------------------------------------------------------
    Vec3 BrushSystem::getEndPos()
    {
        return mEndPos ;
    }

    //-----------------------------------------------------------------------
    Flt BrushSystem::getSize()
    {
        return mSize;
    }

    //-----------------------------------------------------------------------
    void BrushSystem::setSize( Flt size ) 
    {
        mSize = size;

        //////////////////////////////////////////////////////////////

        Scene* scene = EngineMain::getInstance().getFirstScene();
        if ( scene )
        {
			if (mActiveBrushShape == getBrushCircleShape())
			{
				ITerrainCircleDecorator* decorator = scene->getWireframeManager()->createTerrainCircleDecorator( BrushSystem::FACADE_NAME );
				decorator->setRadius( mSize );
			}
			else if (mActiveBrushShape == getBrushRectShape())
			{
				ITerrainSquareDecorator* decorator = scene->getWireframeManager()->createTerrainSquareDecorator( BrushSystem::FACADE_NAME ); 
				decorator->setSideLength( 2*mSize );
			}
			else if (mActiveBrushShape == getBrushRhombusShape())
			{
				ITerrainDiamondDecorator* decorator = scene->getWireframeManager()->createTerrainDiamondDecorator( BrushSystem::FACADE_NAME );
				decorator->setSideLength( 2*mSize );
			}
        }
    }

    //-----------------------------------------------------------------------
    void BrushSystem::setFacadeVisible(Bool visible)
    {
        Scene* scene = EngineMain::getInstance().getFirstScene();
        if ( scene )
        {
			IWireframeDecorator* decorator = NULL;
			if (mActiveBrushShape == getBrushCircleShape())
			{
				decorator = scene->getWireframeManager()->createTerrainCircleDecorator( BrushSystem::FACADE_NAME );
			}
			else if (mActiveBrushShape == getBrushRectShape())
			{
				decorator = scene->getWireframeManager()->createTerrainSquareDecorator( BrushSystem::FACADE_NAME );
			}
			else if (mActiveBrushShape == getBrushRhombusShape())
			{
				decorator = scene->getWireframeManager()->createTerrainDiamondDecorator( BrushSystem::FACADE_NAME );
			}
            decorator->setVisible( visible );
        }
    }

    //-----------------------------------------------------------------------
    Flt BrushSystem::getSpeed() 
    {
        return mSpeed;
    }

    //-----------------------------------------------------------------------
    void BrushSystem::setSpeed( Flt speed ) 
    {
        mSpeed = speed;
    }

	//-----------------------------------------------------------------------
	Int BrushSystem::getActiveTextureLayerIndex( )
	{
		return mActiveTextureLayerIndex;
	}

	//-----------------------------------------------------------------------
	void BrushSystem::setActiveTextureLayerIndex( Int index )
	{
		mActiveTextureLayerIndex = index;
	}

    //-----------------------------------------------------------------------
    Int BrushSystem::getActiveBatchEntityLayerIndex( )
    {
        return  mActiveBatchEntityLayerIndex;
    }

    //-----------------------------------------------------------------------
    void BrushSystem::setActiveBatchEntityLayerIndex( Int index )
    {
        mActiveBatchEntityLayerIndex = index;
    }

    //-----------------------------------------------------------------------
    IBrushCircleShape* BrushSystem::getBrushCircleShape()
    {
        return &BrushCircleShape::getInstance();
    }

    //-----------------------------------------------------------------------
    IBrushRectShape* BrushSystem::getBrushRectShape()
    {
        return &BrushRectShape::getInstance();
    }

    //-----------------------------------------------------------------------
    IBrushRhombusShape* BrushSystem::getBrushRhombusShape()
    {
         return &BrushRhombusShape::getInstance();
    }

    //-----------------------------------------------------------------------
    void BrushSystem::setActiveShape(IBrushShape* shape)
    {
		Scene* scene = EngineMain::getInstance().getFirstScene();
		if ( scene )
		{
			IWireframeDecorator* decorator = NULL;
			if (mActiveBrushShape == getBrushCircleShape())
			{
				decorator = scene->getWireframeManager()->createTerrainCircleDecorator( BrushSystem::FACADE_NAME );
			}
			else if (mActiveBrushShape == getBrushRectShape())
			{
				decorator = scene->getWireframeManager()->createTerrainSquareDecorator( BrushSystem::FACADE_NAME );
			}
			else if (mActiveBrushShape == getBrushRhombusShape())
			{
				decorator = scene->getWireframeManager()->createTerrainDiamondDecorator( BrushSystem::FACADE_NAME );
			}
			decorator->setVisible( false );

			if (shape == getBrushCircleShape())
			{
				decorator = scene->getWireframeManager()->createTerrainCircleDecorator( BrushSystem::FACADE_NAME );
			}
			else if (shape == getBrushRectShape())
			{
				decorator = scene->getWireframeManager()->createTerrainSquareDecorator( BrushSystem::FACADE_NAME );
			}
			else if (shape == getBrushRhombusShape())
			{
				decorator = scene->getWireframeManager()->createTerrainDiamondDecorator( BrushSystem::FACADE_NAME );
			}
			decorator->setVisible( true );
		}
        mActiveBrushShape = shape;
    }

    //-----------------------------------------------------------------------
    IBrushShape* BrushSystem::getActiveShape()
    {
        return mActiveBrushShape;
    }

    //-----------------------------------------------------------------------
    IBrushAirStyle* BrushSystem::getBrushAirStyle()
    {
        return &BrushAirStyle::getInstance();
    }

    //-----------------------------------------------------------------------
    IBrushPaintStyle* BrushSystem::getBrushPaintStyle()
    {
        return &BrushPaintStyle::getInstance();
    }

    //-----------------------------------------------------------------------
    IBrushNoiseStyle* BrushSystem::getBrushNoiseStyle()
    {
        return &BrushNoiseStyle::getInstance();
    }

    //-----------------------------------------------------------------------
    IBrushFractalStyle* BrushSystem::getBrushFractalStyle()
    {
        return &BrushFractalStyle::getInstance();
    }

    //-----------------------------------------------------------------------
    void BrushSystem::setActiveStyle(IBrushStyle* style)
    {
        mActiveBrushStyle = style;
    }

    //-----------------------------------------------------------------------
    IBrushStyle* BrushSystem::getActiveStyle()
    {
        return mActiveBrushStyle;
    }

    //-----------------------------------------------------------------------
    Ogre::Rect BrushSystem::getActiveRect()
    {
        //	-z
        //	|
        //	|
        //	w0---------w1
        //	|          |
        //	| [brush]  |
        //	|          |
        //	w2---------w3----+x
        //	*/


        Ogre::Rect rect;

        rect.left       = mStartPos.x - mSize;
        rect.right      = mStartPos.x + mSize;
        rect.top        = mStartPos.z - mSize;
        rect.bottom     = mStartPos.z + mSize;
        
        return rect;
    }

}


