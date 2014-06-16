/******************************************************************************/
#include "stdafx.h"
#include "TerrainWaterMaterial.h"
#include "TerrainWaterBatch.h"
#include "TerrainBatch.h"
#include "TerrainChunk.h"
#include "EngineMain.h"
#include "Scene.h"
#include "TerrainTiles.h"
#include "MGSceneNode.h"
#include "MGEngineUtility.h"
#include "Display.h"
#include "MaterialManager.h"
#include "Display.h"
/******************************************************************************/

namespace MG
{

    //------------------------------------------------------------------------
    TerrainWaterMaterial::TerrainWaterMaterial( Scene* scene, TerrainSurfaceManager* surfaceMgr )
        :mScene(scene)
        ,mIsRenderWater(false)
        ,mTerrainSurfaceManager(surfaceMgr)
    {

    }

    //------------------------------------------------------------------------
    TerrainWaterMaterial::~TerrainWaterMaterial()
    {
		for ( std::map<UInt, WaterMaterialWrapper>::iterator iter = mMaterialList.begin(); 
			iter != mMaterialList.end(); iter++ )
		{
			WaterMaterialWrapper& wmw = iter->second;
			if (wmw.refractionTarget != NULL)
			{
				wmw.refractionTarget->removeAllListeners();
			}
			if (wmw.reflectionTarget != NULL)
			{
				wmw.reflectionTarget->removeAllListeners();
			}
		}
    }

    //------------------------------------------------------------------------
    void TerrainWaterMaterial::update( Flt delta )
    {
        Bool active = mScene->getActiveCamera()->getPositionDirty() || mScene->getActiveCamera()->getOrientationDirty();

        Bool reflectionActive = active;
        Bool refractionActive = active;

        if ( Display::getSingleton().getWaterReflectionEnabled() == false )
        {
            reflectionActive = false;
        }

        if ( Display::getSingleton().getWaterRefractionEnabled() == false )
        {
            refractionActive = false;
        }

        std::map<UInt, WaterMaterialWrapper>::iterator iter = mMaterialList.begin();
        for ( ;iter!=mMaterialList.end();iter++)
        {
            if ( iter->second.renderFirst == false )
            {
                if ( iter->second.reflectionTarget )
                {
                    if ( reflectionActive )
                    {
                        Viewport* viewPort = iter->second.reflectionTarget->getViewport(0);
                        if ( viewPort )
                        {
                            viewPort->setVisibilityMask( SOV_REFLECT );
                        }
                    }

                    iter->second.reflectionTarget->setActive( reflectionActive );
                }

                if ( iter->second.refractionTarget )
                {
                    if ( refractionActive )
                    {
                        Viewport* viewPort = iter->second.refractionTarget->getViewport(0);
                        if ( viewPort )
                        {
                            viewPort->setVisibilityMask( SOV_REFRACT );
                        }
                    }

                    iter->second.refractionTarget->setActive( refractionActive );
                }

            }else
            {
                iter->second.renderFirst = false;

                if ( iter->second.reflectionTarget )
                {
                    iter->second.reflectionTarget->setActive( true );
                }
                if ( iter->second.refractionTarget )
                {
                    iter->second.refractionTarget->setActive( true );
                }
            }
        }
    }

    //------------------------------------------------------------------------
    void TerrainWaterMaterial::reset()
    {
        std::map<UInt, WaterMaterialWrapper>::iterator iter = mMaterialList.begin();
        if ( iter!=mMaterialList.end() )
        {
            iter->second.renderFirst = true ;
            if ( iter->second.reflectionTarget )
            {
                iter->second.reflectionTarget->setActive( true );
            }
            if ( iter->second.refractionTarget )
            {
                iter->second.refractionTarget->setActive( true );
            }
        }
    }

    //------------------------------------------------------------------------
    void TerrainWaterMaterial::applyRenderConfig()
    {
        freeAllMaterialPtr();
    }

	//------------------------------------------------------------------------
	TerrainWaterMaterial::WaterMaterialWrapper* TerrainWaterMaterial::getWaterMaterialWrapper( UInt groupID )
	{
		std::map<UInt, WaterMaterialWrapper>::iterator iter = mMaterialList.find( groupID );
		if ( iter!=mMaterialList.end() )
		{
			return &iter->second;
		}

        WaterMaterialWrapper wrapper;
        wrapper.groupID = groupID;
		wrapper.mgr = this;
        mMaterialList[groupID] = wrapper;
     
		return &mMaterialList[groupID];
	}

    //------------------------------------------------------------------------
    MaterialPtr& TerrainWaterMaterial::getOrGenerateMaterialPtr( UInt groupID, TerrainChunk* chunk )
    {
        Str chunName = chunk->getName();

		WaterMaterialWrapper* wrapper = getWaterMaterialWrapper(groupID);
		if ( wrapper )
		{
			MaterialPtr& mat = wrapper->matList[ chunName ];

            wrapper->renderFirst = true;
		
            if ( mat.isNull() == true )
	        {
		        TerrainWaterGroupDeclaration* decl =  mTerrainSurfaceManager->getGlobleWaterGroup( groupID );
		        U32 waterMatID = 1;
		        if ( decl )
		        {
			        waterMatID = decl->wMatID;
		        }

		        //////////////////////////////////////////////////////////////////////////////////////////////

		        MaterialUserParams params;
		        params.suffixName = getWaterMaterialSuffixName( groupID, chunk );
		        wrapper->matList[ chunName ]  = MaterialManager::getInstance().createOrRetriveWaterMaterial(mScene,waterMatID,params);

		        //////////////////////////////////////////////////////////////////////////////////////////////

                if ( Display::getSingleton().getWaterReflectionEnabled() )
                {
                    createReflectionTexture( wrapper, chunk );
                }

                if ( Display::getSingleton().getWaterRefractionEnabled() || Display::getSingleton().getWaterDepthCheckEnabled() )
                {
                    createReflectionTexture( wrapper, chunk );
                }

                if ( Display::getSingleton().getTerrainLightmapEnabled() && 
                    Display::getSingleton().getTerrainReceiveDynamicShadowsEnabled() )
                {
                    setLightingMap(wrapper,chunk);
                }

                //////////////////////////////////////////////////////////////////////////////////////////////
            }

            return mat;
		}

        return mNullMaterialPtr;
    }

    //------------------------------------------------------------------------
    void TerrainWaterMaterial::setLightingMap( WaterMaterialWrapper* wrapper, TerrainChunk* chunk )
    {
        if ( Display::getSingleton().getTerrainLightmapEnabled() )
        {
            MaterialPtr mat = wrapper->matList[chunk->getName()];

            if (mat.isNull() == false)
            {
                Technique*	ins_tech = NULL;
                Pass*		ins_pass = NULL;

                if ( ins_tech = mat->getTechnique(0) )
                {
                    ins_pass = ins_tech->getPass(0);
                }

                TextureUnitState* us = ins_pass->getTextureUnitState("lightingMap");

                if ( us )
                {
                    Str lmName = chunk->getTerrainGroundSurface()->getLightmap()->getName();
                    us->setTextureName( lmName );
                }
            }
        }
    }

	//------------------------------------------------------------------------
	Str TerrainWaterMaterial::getWaterMaterialSuffixName( UInt groupID, TerrainChunk* chunk )
	{
		std::ostringstream s;
		s << "_TerrainWaterMaterial_" << groupID << "_" << chunk->getName();

		return s.str();
	}
 
	//------------------------------------------------------------------------
	Str TerrainWaterMaterial::getWaterReflectionTextureName( UInt groupID )
	{
		std::ostringstream s;
		s << "_TerrainReflectionTexture_" << groupID << "_";

		return s.str();
	}

	//------------------------------------------------------------------------
	Str TerrainWaterMaterial::getWaterRefractionTextureName( UInt groupID )
	{
		std::ostringstream s;
		s << "_TerrainRefractionTexture_" << groupID << "_";

		return s.str();
	}

	//------------------------------------------------------------------------
	void TerrainWaterMaterial::createReflectionTexture( WaterMaterialWrapper* wrapper, TerrainChunk* chunk )
	{
		Str name = getWaterReflectionTextureName( wrapper->groupID );

		if ( wrapper->reflectionTarget == NULL )
		{
			TexturePtr tex = TextureManager::getSingleton().getByName(name);
			if (tex.isNull()==true)
			{
				//tex = TextureManager::getSingleton().createManual(name,
				//	ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, TEX_TYPE_2D, 512, 512, 0, PF_R8G8B8, TU_RENDERTARGET);
                tex = TextureManager::getSingleton().createManual(name,
                    ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, TEX_TYPE_2D, 512, 512, 0, PF_R8G8B8A8, TU_RENDERTARGET);
			}

            ////////////////////////////////////////////////////
            // 多个Chunk公用

			if (tex.isNull()==false)
			{
				wrapper->reflectionTarget = tex->getBuffer()->getRenderTarget();

				if (wrapper->reflectionTarget->getNumViewports()==0)
				{
					Viewport* viewport = wrapper->reflectionTarget->addViewport(mScene->getActiveCamera()->getOgreCamera());
					viewport->setOverlaysEnabled( false );
					viewport->setShadowsEnabled( false );
					viewport->setSkiesEnabled( false );
					viewport->setOverlaysEnabled( false );
  
                    viewport->setBackgroundColour(Ogre::ColourValue(0.5,0.5,0.5,0));
					
					viewport->setUsage(1);
                    //viewport->setClearEveryFrame( false );

					wrapper->reflectionTarget->setAutoUpdated(true);
					wrapper->reflectionTarget->addListener(wrapper);

                    if ( Display::getSingleton().getWaterReflectionEnabled() )
                    {
                        viewport->setVisibilityMask(  SOV_REFLECT );
                    }else
                    {
                        viewport->setVisibilityMask(  SOV_NULL );
                    }
				}
			}

			////////////////////////////////////////////////////

			Technique*	ins_tech = NULL;
			Pass*		ins_pass = NULL;

            MaterialPtr mat = wrapper->matList[chunk->getName()];

            if (mat.isNull() == false)
            {
                if ( ins_tech = mat->getTechnique(0) )
                {
                    ins_pass = ins_tech->getPass(0);
                }

                ins_pass->getTextureUnitState("reflection")->setTextureName(name);
            }
		}
	}

	//------------------------------------------------------------------------
	void TerrainWaterMaterial::destroyReflectionTexture( WaterMaterialWrapper* wrapper )
	{
		if ( wrapper->reflectionTarget )
		{
			////////////////////////////////////////////////////

			wrapper->reflectionTarget->removeAllViewports();
			wrapper->reflectionTarget->removeAllListeners();
			wrapper->reflectionTarget = NULL;

			////////////////////////////////////////////////////

			Str name = getWaterReflectionTextureName( wrapper->groupID );
			TexturePtr tex = TextureManager::getSingleton().getByName(name);

			if (tex.isNull()==false)
			{
				TextureManager::getSingleton().remove( tex->getHandle() );
			}
		}
	}

	//------------------------------------------------------------------------
	void TerrainWaterMaterial::createRefractionTexture( WaterMaterialWrapper* wrapper, TerrainChunk* chunk )
	{
		Str name = getWaterRefractionTextureName( wrapper->groupID );

		if ( wrapper->refractionTarget == NULL )
		{
			TexturePtr tex = TextureManager::getSingleton().getByName(name);
			if (tex.isNull()==true)
			{
				tex = TextureManager::getSingleton().createManual(name,
					ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, TEX_TYPE_2D, 512, 512, 0, PF_R8G8B8A8/*PF_R8G8B8*/, TU_RENDERTARGET);
			}

			////////////////////////////////////////////////////
			// 多个Chunk公用

			if (tex.isNull()==false)
			{
				wrapper->refractionTarget = tex->getBuffer()->getRenderTarget();

				if (wrapper->refractionTarget->getNumViewports()==0)
				{
					Viewport* viewport = wrapper->refractionTarget->addViewport(mScene->getActiveCamera()->getOgreCamera());
					viewport->setOverlaysEnabled( false );
					viewport->setShadowsEnabled( false );
					viewport->setSkiesEnabled( false );
					viewport->setOverlaysEnabled( false );

					viewport->setBackgroundColour(Ogre::ColourValue(0.5,0.5,0.5,0));

					//viewport->setClearEveryFrame( false );
					viewport->setUsage(2);

					wrapper->refractionTarget->setAutoUpdated(true);
					wrapper->refractionTarget->addListener(wrapper);

					if ( Display::getSingleton().getWaterRefractionEnabled() )
					{
						viewport->setVisibilityMask( SOV_REFRACT );
					}else
					{
						viewport->setVisibilityMask( SOV_NULL );
					}
				}
			}

			////////////////////////////////////////////////////

			Technique*	ins_tech = NULL;
			Pass*		ins_pass = NULL;

			MaterialPtr mat = wrapper->matList[chunk->getName()];

			if (mat.isNull() == false)
			{
				if ( ins_tech = mat->getTechnique(0) )
				{
					ins_pass = ins_tech->getPass(0);
				}

				ins_pass->getTextureUnitState("refraction")->setTextureName(name);
			}
		}
	}

	//------------------------------------------------------------------------
	void TerrainWaterMaterial::destroyRefractionTexture( WaterMaterialWrapper* wrapper )
	{
		if ( wrapper->refractionTarget )
		{
			////////////////////////////////////////////////////

			wrapper->refractionTarget->removeAllViewports();
			wrapper->refractionTarget->removeAllListeners();
			wrapper->refractionTarget = NULL;

			////////////////////////////////////////////////////

			Str name = getWaterRefractionTextureName( wrapper->groupID );
			TexturePtr tex = TextureManager::getSingleton().getByName(name);

			if (tex.isNull()==false)
			{
				TextureManager::getSingleton().remove( tex->getHandle() );
			}
		}
	}

	//------------------------------------------------------------------------
	void TerrainWaterMaterial::freeMaterial( WaterMaterialWrapper* wrapper )
	{
        destroyReflectionTexture( wrapper );
        destroyRefractionTexture( wrapper );
            
        std::map<Str,MaterialPtr>::iterator iter = wrapper->matList.begin();
        for ( ; iter!=wrapper->matList.end(); iter++ )
        {
            MaterialPtr& mat = iter->second;
            if ( mat.isNull() == false )
            {
                Ogre::MaterialManager::getSingleton().remove( mat->getHandle() );
            }
        }
        wrapper->matList.clear();
	}


	//------------------------------------------------------------------------
	void TerrainWaterMaterial::freeAllMaterialPtr( )
	{
		std::map<UInt, WaterMaterialWrapper>::iterator iter = mMaterialList.begin();
		for ( ;iter!=mMaterialList.end();iter++)
		{
			freeMaterial( &iter->second );
		}
		mMaterialList.clear();
	}

    //-----------------------------------------------------------------------
    void TerrainWaterMaterial::setReflectionPlane( RenderTarget* rt, Plane& plane )
    {
        TerrainWaterGroupDeclaration* groupDecl = NULL;
        std::map<UInt, WaterMaterialWrapper>::iterator iter = mMaterialList.begin();
        for ( ;iter!=mMaterialList.end();iter++)
        {
            if ( iter->second.reflectionTarget == rt )
            {
                groupDecl = mTerrainSurfaceManager->getGlobleWaterGroup( iter->second.groupID );
                break;
            }
        }

        if ( groupDecl )
        {
            Vec3& rp = groupDecl->reflectPostion;
            Vec3& rd = groupDecl->reflectDirection;
            plane = Plane( Vector3(rd.x,rd.y,rd.z), Vector3(rp.x,rp.y,rp.z) );
        }else
        {
            plane = Plane(Vector3::UNIT_Y, 0);
        }
    }

	//-----------------------------------------------------------------------
	void TerrainWaterMaterial::WaterMaterialWrapper::preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
	{
        RenderTarget* renderTarget = evt.source;
        //Viewport* viewPort = renderTarget->getViewport(0);

		if ( renderTarget == this->reflectionTarget )
		{
			Plane plane;
			mgr->setReflectionPlane( renderTarget, plane );

			mgr->mScene->getActiveCamera()->getOgreCamera()->enableReflection(plane);
			mgr->mScene->getActiveCamera()->getOgreCamera()->enableCustomNearClipPlane(plane);
		}

        mgr->mScene->getOgreSceneManager()->setSkyBoxEnabled( false );
        mgr->mScene->getOgreSceneManager()->setSkyDomeEnabled( false );
        mgr->mScene->getOgreSceneManager()->setSkyPlaneEnabled( false );

        mgr->mIsRenderWater = true;
	}
	//-----------------------------------------------------------------------
	void TerrainWaterMaterial::WaterMaterialWrapper::postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
	{
		RenderTarget* renderTarget = evt.source;
		//Viewport* viewPort = renderTarget->getViewport(0);

		if ( renderTarget == this->reflectionTarget )
		{
			mgr->mScene->getActiveCamera()->getOgreCamera()->disableReflection();
			mgr->mScene->getActiveCamera()->getOgreCamera()->disableCustomNearClipPlane();
		}

        mgr->mScene->getOgreSceneManager()->setSkyBoxEnabled( true );
        mgr->mScene->getOgreSceneManager()->setSkyDomeEnabled( true );
        mgr->mScene->getOgreSceneManager()->setSkyPlaneEnabled( true );
		
		mgr->mIsRenderWater = false;
	}

}