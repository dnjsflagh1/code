/******************************************************************************/
#include "stdafx.h"
#include "WireframeManager.h"
#include "Scene.h"
#include "EngineMain.h"
#include "MGEngineUtility.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    WireframeManager::WireframeManager(Scene* scene)
        :mScene(scene)
        ,mPolylineWireframeDecoratorNameGenerator("PolylineWireframeDecorator")
        ,mScreenRectWireframeDecoratorNameGenerator("ScreenRectWireframeDecorator")
        ,mTerrainCircleDecoratorNameGenerator("TerrainCircleDecorator")
		,mTerrainSquareDecoratorNameGenerator("TerrainSquareDecorator")
		,mTerrainDiamondDecoratorNameGenerator("TerrainDiamondDecorator")
        ,mTerrainGridsDecoratorNameGenerator("TerrainGridsDecorator")
		,mEffectGridsDecoratorNameGenerator("EffeectGridsDecorator")
    {
    }

    //-----------------------------------------------------------------------
    WireframeManager::~WireframeManager()
    {
        clear();
    }

    //-----------------------------------------------------------------------
    void WireframeManager::update( Real delta )
    {
        std::map<String, ScreenRectWireframeDecorator*>::iterator iter = mScreenRectWireframeDecorators.begin();
        for ( ;iter!=mScreenRectWireframeDecorators.end();iter++ )
        {
            iter->second->update();
        }
    }

    //-----------------------------------------------------------------------
    void WireframeManager::postFindVisibleObjects(Ogre::SceneManager* source, 
        Ogre::SceneManager::IlluminationRenderStage irs, Ogre::Viewport* v)
    {
        std::map<String, ScreenRectWireframeDecorator*>::iterator iter = mScreenRectWireframeDecorators.begin();
        for ( ;iter!=mScreenRectWireframeDecorators.end();iter++ )
        {
            iter->second->postFindVisibleObjects( source, irs, v );
        }
    }
   
    //-----------------------------------------------------------------------
    void WireframeManager::clear( )
    {
         destroyAllScreenRectWireframeDecorator();
         destroyAllPolylineWireframeDecorator();
         destroyAllTerrainCircleDecorator();
		 destroyAllTerrainSquareDecorator();
		 destroyAllTerrainDiamondDecorator();
         destroyAllTerrainGridsDecorator();
    }

    //-----------------------------------------------------------------------
    IScreenRectWireframeDecorator* WireframeManager::createScreenRectWireframeDecorator( Str name )
    {
        IScreenRectWireframeDecorator* result = getScreenRectWireframeDecorator( name );
        if ( !result )
        {
            //String name = mScreenRectWireframeDecoratorNameGenerator.generate();
            ScreenRectWireframeDecorator* decorator = MG_NEW ScreenRectWireframeDecorator(name,mScene);
            mScreenRectWireframeDecorators[name] = decorator;
            result = decorator;
        }

        return result;
    }

    //-----------------------------------------------------------------------
    IScreenRectWireframeDecorator* WireframeManager::getScreenRectWireframeDecorator( Str name )
    {
        std::map<String, ScreenRectWireframeDecorator*>::iterator iter = mScreenRectWireframeDecorators.find( name );

        if ( iter != mScreenRectWireframeDecorators.end() )
        {
            return iter->second;
        }
        
        return NULL;
    }

    //-----------------------------------------------------------------------
    void WireframeManager::destroyScreenRectWireframeDecorator(IScreenRectWireframeDecorator* decorator)
    {
        std::map<String, ScreenRectWireframeDecorator*>::iterator iter = mScreenRectWireframeDecorators.begin();
        for ( ;iter!=mScreenRectWireframeDecorators.end();iter++ )
        {
            if (iter->second == decorator)
            {
                mScreenRectWireframeDecorators.erase( iter );
                break;
            }
        }
        MG_SAFE_DELETE(decorator);
    }

    //-----------------------------------------------------------------------
    void WireframeManager::destroyAllScreenRectWireframeDecorator()
    {
        mScreenRectWireframeDecoratorNameGenerator.reset();

        std::map<String, ScreenRectWireframeDecorator*>::iterator iter = mScreenRectWireframeDecorators.begin();
        for ( ;iter!=mScreenRectWireframeDecorators.end();iter++ )
        {
            MG_SAFE_DELETE(iter->second);
        }
        mScreenRectWireframeDecorators.clear();
    }

    //-----------------------------------------------------------------------
    IPolylineWireframeDecorator* WireframeManager::createPolylineWireframeDecorator( Str name )
    {
        IPolylineWireframeDecorator* result = getPolylineWireframeDecorator( name );
        if ( !result )
        {
            //String name = mPolylineWireframeDecoratorNameGenerator.generate();
            PolylineWireframeDecorator* decorator = MG_NEW PolylineWireframeDecorator(name,mScene);
            mPolylineWireframeDecorators[name] = decorator;
            result = decorator;
        }

        return result;
    }

    //-----------------------------------------------------------------------
    IPolylineWireframeDecorator* WireframeManager::getPolylineWireframeDecorator( Str name )
    {
        std::map<String, PolylineWireframeDecorator*>::iterator iter = mPolylineWireframeDecorators.find( name );

        if ( iter != mPolylineWireframeDecorators.end() )
        {
            return iter->second;
        }

        return NULL;
    }

    //-----------------------------------------------------------------------
    void WireframeManager::destroyPolylineWireframeDecorator(IPolylineWireframeDecorator* decorator)
    {
        std::map<String, PolylineWireframeDecorator*>::iterator iter = mPolylineWireframeDecorators.begin();
        for ( ;iter!=mPolylineWireframeDecorators.end();iter++ )
        {
            if (iter->second == decorator)
            {
                mPolylineWireframeDecorators.erase( iter );
                break;
            }
        }
        MG_SAFE_DELETE(decorator);
    }

    //-----------------------------------------------------------------------
    void WireframeManager::destroyAllPolylineWireframeDecorator()
    {
        mPolylineWireframeDecoratorNameGenerator.reset();

        std::map<String, PolylineWireframeDecorator*>::iterator iter = mPolylineWireframeDecorators.begin();
        for ( ;iter!=mPolylineWireframeDecorators.end();iter++ )
        {
            MG_SAFE_DELETE(iter->second);
        }
        mPolylineWireframeDecorators.clear();
    }

    //-----------------------------------------------------------------------
    ITerrainCircleDecorator* WireframeManager::createTerrainCircleDecorator( Str name ) 
    {
        ITerrainCircleDecorator* result = getTerrainCircleDecorator( name );
        if ( !result )
        {
            //String name = mTerrainCircleDecoratorNameGenerator.generate();
            TerrainCircleDecorator* decorator = MG_NEW TerrainCircleDecorator(name,mScene);
            mTerrainCircleDecorator[name] = decorator;
            result = decorator;
        }

        return result;
    }

    //-----------------------------------------------------------------------
    ITerrainCircleDecorator* WireframeManager::getTerrainCircleDecorator( Str name )
    {
        std::map<String, TerrainCircleDecorator*>::iterator iter = mTerrainCircleDecorator.find( name );

        if ( iter != mTerrainCircleDecorator.end() )
        {
            return iter->second;
        }

        return NULL;
    }

    //-----------------------------------------------------------------------
    void WireframeManager::destroyTerrainCircleDecorator(ITerrainCircleDecorator* decorator)
    {
        std::map<String, TerrainCircleDecorator*>::iterator iter = mTerrainCircleDecorator.begin();
        for ( ;iter!=mTerrainCircleDecorator.end();iter++ )
        {
            if (iter->second == decorator)
            {
                mTerrainCircleDecorator.erase( iter );
                break;
            }
        }
        MG_SAFE_DELETE(decorator);
    }

    //-----------------------------------------------------------------------
    void WireframeManager::destroyAllTerrainCircleDecorator()
    {
        mTerrainCircleDecoratorNameGenerator.reset();

        std::map<String, TerrainCircleDecorator*>::iterator iter = mTerrainCircleDecorator.begin();
        for ( ;iter!=mTerrainCircleDecorator.end();iter++ )
        {
            MG_SAFE_DELETE(iter->second);
        }
        mTerrainCircleDecorator.clear();
    }

	//-----------------------------------------------------------------------
	ITerrainSquareDecorator* WireframeManager::createTerrainSquareDecorator( Str name ) 
	{
		ITerrainSquareDecorator* result = getTerrainSquareDecorator( name );
		if ( !result )
		{
			//String name = mTerrainCircleDecoratorNameGenerator.generate();
			TerrainSquareDecorator* decorator = MG_NEW TerrainSquareDecorator(name,mScene);
			mTerrainSquareDecorator[name] = decorator;
			result = decorator;
		}

		return result;
	}

	//-----------------------------------------------------------------------
	ITerrainSquareDecorator* WireframeManager::getTerrainSquareDecorator( Str name )
	{
		std::map<String, TerrainSquareDecorator*>::iterator iter = mTerrainSquareDecorator.find( name );

		if ( iter != mTerrainSquareDecorator.end() )
		{
			return iter->second;
		}

		return NULL;
	}

	//-----------------------------------------------------------------------
	void WireframeManager::destroyTerrainSquareDecorator(ITerrainSquareDecorator* decorator)
	{
		std::map<String, TerrainSquareDecorator*>::iterator iter = mTerrainSquareDecorator.begin();
		for ( ;iter!=mTerrainSquareDecorator.end();iter++ )
		{
			if (iter->second == decorator)
			{
				mTerrainSquareDecorator.erase( iter );
				break;
			}
		}
		MG_SAFE_DELETE(decorator);
	}

	//-----------------------------------------------------------------------
	void WireframeManager::destroyAllTerrainSquareDecorator()
	{
		mTerrainSquareDecoratorNameGenerator.reset();

		std::map<String, TerrainSquareDecorator*>::iterator iter = mTerrainSquareDecorator.begin();
		for ( ;iter!=mTerrainSquareDecorator.end();iter++ )
		{
			MG_SAFE_DELETE(iter->second);
		}
		mTerrainSquareDecorator.clear();
	}

	//-----------------------------------------------------------------------
	ITerrainDiamondDecorator* WireframeManager::createTerrainDiamondDecorator( Str name ) 
	{
		ITerrainDiamondDecorator* result = getTerrainDiamondDecorator( name );
		if ( !result )
		{
			//String name = mTerrainCircleDecoratorNameGenerator.generate();
			TerrainDiamondDecorator* decorator = MG_NEW TerrainDiamondDecorator(name,mScene);
			mTerrainDiamondDecorator[name] = decorator;
			result = decorator;
		}

		return result;
	}

	//-----------------------------------------------------------------------
	ITerrainDiamondDecorator* WireframeManager::getTerrainDiamondDecorator( Str name )
	{
		std::map<String, TerrainDiamondDecorator*>::iterator iter = mTerrainDiamondDecorator.find( name );

		if ( iter != mTerrainDiamondDecorator.end() )
		{
			return iter->second;
		}

		return NULL;
	}

	//-----------------------------------------------------------------------
	void WireframeManager::destroyTerrainDiamondDecorator(ITerrainDiamondDecorator* decorator)
	{
		std::map<String, TerrainDiamondDecorator*>::iterator iter = mTerrainDiamondDecorator.begin();
		for ( ;iter!=mTerrainDiamondDecorator.end();iter++ )
		{
			if (iter->second == decorator)
			{
				mTerrainDiamondDecorator.erase( iter );
				break;
			}
		}
		MG_SAFE_DELETE(decorator);
	}

	//-----------------------------------------------------------------------
	void WireframeManager::destroyAllTerrainDiamondDecorator()
	{
		mTerrainDiamondDecoratorNameGenerator.reset();

		std::map<String, TerrainDiamondDecorator*>::iterator iter = mTerrainDiamondDecorator.begin();
		for ( ;iter!=mTerrainDiamondDecorator.end();iter++ )
		{
			MG_SAFE_DELETE(iter->second);
		}
		mTerrainDiamondDecorator.clear();
	}

    //-----------------------------------------------------------------------
    ITerrainGridsDecorator* WireframeManager::createTerrainGridsDecorator( Str name )
    {
        ITerrainGridsDecorator* result = getTerrainGridsDecorator( name );
        if ( !result )
        {
            //String name = mTerrainGridsDecoratorNameGenerator.generate();
            TerrainGridsDecorator* decorator = MG_NEW TerrainGridsDecorator(name,mScene);
            mTerrainGridsDecorator[name] = decorator;
            result = decorator;
        }

        return result;
    }

    //-----------------------------------------------------------------------
    ITerrainGridsDecorator* WireframeManager::getTerrainGridsDecorator( Str name )
    {
        std::map<String, TerrainGridsDecorator*>::iterator iter = mTerrainGridsDecorator.find( name );

        if ( iter != mTerrainGridsDecorator.end() )
        {
            return iter->second;
        }

        return NULL;
    }

    //-----------------------------------------------------------------------
    void WireframeManager::destroyTerrainGridsDecorator(ITerrainGridsDecorator* decorator) 
    {
        std::map<String, TerrainGridsDecorator*>::iterator iter = mTerrainGridsDecorator.begin();
        for ( ;iter!=mTerrainGridsDecorator.end();iter++ )
        {
            if (iter->second == decorator)
            {
                mTerrainGridsDecorator.erase( iter );
                break;
            }
        }
        MG_SAFE_DELETE(decorator);
    }

    //-----------------------------------------------------------------------
    void WireframeManager::destroyAllTerrainGridsDecorator()
    {
        mTerrainGridsDecoratorNameGenerator.reset();

        std::map<String, TerrainGridsDecorator*>::iterator iter = mTerrainGridsDecorator.begin();
        for ( ;iter!=mTerrainGridsDecorator.end();iter++ )
        {
            MG_SAFE_DELETE(iter->second);
        }
        mTerrainGridsDecorator.clear();
    }

	IEffectGridsDecorator* WireframeManager::createEffectGridsDecorator( Str name )
	{
		IEffectGridsDecorator* result = getEffectGridsDecorator( name );
		if ( !result )
		{
			EffectGridDecorator* decorator = MG_NEW EffectGridDecorator(name,mScene);
			mEffectGridsDecorator[name] = decorator;
			result = decorator;
		}

		return result;
	}

	IEffectGridsDecorator* WireframeManager::getEffectGridsDecorator( Str name )
	{
		std::map<String, EffectGridDecorator*>::iterator iter = mEffectGridsDecorator.find( name );

		if ( iter != mEffectGridsDecorator.end() )
		{
			return iter->second;
		}

		return NULL;
	}

	void WireframeManager::destroyEffectGridsDecorator( IEffectGridsDecorator* decorator )
	{
		std::map<String, EffectGridDecorator*>::iterator iter = mEffectGridsDecorator.begin();
		for ( ;iter!=mEffectGridsDecorator.end();iter++ )
		{
			if (iter->second == decorator)
			{
				mEffectGridsDecorator.erase( iter );
				break;
			}
		}
		MG_SAFE_DELETE(decorator);
	}

	void WireframeManager::destroyAllEffectGridsDecorator()
	{
		mEffectGridsDecoratorNameGenerator.reset();

		std::map<String, EffectGridDecorator*>::iterator iter = mEffectGridsDecorator.begin();
		for ( ;iter!=mEffectGridsDecorator.end();iter++ )
		{
			MG_SAFE_DELETE(iter->second);
		}
		mEffectGridsDecorator.clear();
	}
}