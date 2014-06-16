/******************************************************************************/
#include "stdafx.h"
#include "TerrainChunk.h"
#include "EngineMain.h"
#include "Scene.h"
#include "TerrainTilesGpu.h"
#include "TerrainTiles.h"
#include "TerrainTilesMaterialA2.h"
#include "Display.h"

#include "TerrainGroundSurface.h"
#include "TerrainGroundBatch.h"
#include "TerrainGroundTiles.h"
#include "TerrainBBGroundTiles.h"
#include "TerrainBBGroundSurface.h"

#include "OgreMaterialManager.h"
#include "OgreTechnique.h"
#include "OgrePass.h"
#include "OgreTextureUnitState.h"
#include "OgreGpuProgramManager.h"
#include "OgreHighLevelGpuProgramManager.h"
#include "OgreHardwarePixelBuffer.h"
#include "OgreShadowCameraSetupPSSM.h"
/******************************************************************************/

namespace MG
{
    //---------------------------------------------------------------------
    TerrainMaterialGeneratorA2::TerrainMaterialGeneratorA2()
    {
        mProfiles.push_back(OGRE_NEW SM2Profile(this, "SM2", "Profile for rendering on Shader Model 2 capable cards"));
        // TODO - check hardware capabilities & use fallbacks if required (more profiles needed)
        setActiveProfile("SM2");

    }
    //---------------------------------------------------------------------
    TerrainMaterialGeneratorA2::~TerrainMaterialGeneratorA2()
    {

    }
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    TerrainMaterialGeneratorA2::SM2Profile::SM2Profile(TerrainMaterialGenerator* parent, const String& name, const String& desc)
        : Profile(parent, name, desc)
        , mShaderGen(0)
        , mLayerColorMappingEnabled(true)
        , mLayerNormalMappingEnabled(false)
        , mLayerParallaxMappingEnabled(false)
        , mLayerSpecularMappingEnabled(false)
        , mGlobalColourMapEnabled(false)
        , mRegionMapEnable(false)
        , mLightmapEnabled(true)
        , mReceiveDynamicShadows(false)
        , mDepthShadows(false)
        , mLowLodShadows(false)
    {
    }
    //---------------------------------------------------------------------
    TerrainMaterialGeneratorA2::SM2Profile::~SM2Profile()
    {
        OGRE_DELETE mShaderGen;
    }	


    //**********************************************************************************************************************
    //**********************************************************************************************************************



    //---------------------------------------------------------------------
    void TerrainMaterialGeneratorA2::SM2Profile::respondOptions(Bool immediately, Bool isSimple)
    {
        IDisplay* display = EngineMain::getInstance().display();

        mLayerColorMappingEnabled       = !isSimple && display->getTerrainColorMappingEnabled();
        mLayerNormalMappingEnabled      = !isSimple &&display->getTerrainNormalMappingEnabled();
        mLayerParallaxMappingEnabled    = !isSimple &&display->getTerrainParallaxMappingEnabled();
        mLayerSpecularMappingEnabled    = !isSimple &&display->getTerrainSpecularMappingEnabled();
        mLightmapEnabled                = !isSimple &&display->getTerrainLightmapEnabled();
        mRegionMapEnable                = !isSimple &&display->getTerrainRegionDisplayEnabled();

        mReceiveDynamicShadows          = !isSimple &&display->getTerrainReceiveDynamicShadowsEnabled();
        mDepthShadows                   = !isSimple &&display->getShadowType() == SCL_PSSM_DEPTH_TEXTURE;

        if ( immediately )
            mParent->_markChanged();
    }
    //---------------------------------------------------------------------
    void TerrainMaterialGeneratorA2::SM2Profile::requestOptions(TerrainGroundTileRender* tileRender)
    {
        //terrain->_setMorphRequired(true);
        //terrain->_setNormalMapRequired(true);
        //terrain->_setLightMapRequired(mLightmapEnabled, true);
        //terrain->_setCompositeMapRequired(mCompositeMapEnabled);
    }


    //---------------------------------------------------------------------
    uint8 TerrainMaterialGeneratorA2::SM2Profile::getMaxLayers(TerrainGroundTileRender* tileRender) const
    {
        //// count the texture units free
        //uint8 freeTextureUnits = TERRAIN_MAX_TEXTURE;
        //// lightmap
        //--freeTextureUnits;
        //// normalmap
        //--freeTextureUnits;
        //// colourmap
        //if (terrain->getGlobalColourMapEnabled())
        //    --freeTextureUnits;
        //if (isShadowingEnabled(HIGH_LOD, terrain))
        //{
        //    uint numShadowTextures = 1;
        //    if (getReceiveDynamicShadowsPSSM())
        //    {
        //        numShadowTextures = getReceiveDynamicShadowsPSSM()->getSplitCount();
        //    }
        //    freeTextureUnits -= numShadowTextures;
        //}

        //// each layer needs 2.25 units (1xdiffusespec, 1xnormalheight, 0.25xblend)
        //return static_cast<uint8>(freeTextureUnits / 2.25f);

        return tileRender->getMaxTextureLayerCount();
    }
    //---------------------------------------------------------------------
    MaterialPtr TerrainMaterialGeneratorA2::SM2Profile::generate(TerrainGroundTileRender* tileRender)
    {

        TerrainBBGroundTileRender* bbTile = (TerrainBBGroundTileRender*)tileRender;

        ///////////////////////////////////////////////////////////////////////////////

        respondOptions( true, tileRender->isSimpleMaterial() );

        ///////////////////////////////////////////////////////////////////////////////

        // re-use old material if exists
        MaterialPtr mat = tileRender->getMaterialPtr();
        if (mat.isNull())
        {
            Ogre::MaterialManager& matMgr = Ogre::MaterialManager::getSingleton();

            // it's important that the names are deterministic for a given terrain, so
            // use the terrain pointer as an ID
            const String& matName = tileRender->getMaterialName();
            mat = matMgr.getByName(matName);
            if (mat.isNull())
            {
                mat = matMgr.create(matName, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
            }
        }
        // clear everything
        mat->removeAllTechniques();

        // Automatically disable normal & parallax mapping if card cannot handle it
        // We do this rather than having a specific technique for it since it's simpler
        GpuProgramManager& gmgr = GpuProgramManager::getSingleton();
        if (!gmgr.isSyntaxSupported("ps_3_0") && !gmgr.isSyntaxSupported("ps_2_x")
            && !gmgr.isSyntaxSupported("fp40") && !gmgr.isSyntaxSupported("arbfp1"))
        {
            setLayerNormalMappingEnabled(false);
            setLayerParallaxMappingEnabled(false);
            setReceiveDynamicShadowsEnabled(false);
        }

        //TODO:
        //IDisplay* display                   = EngineMain::getInstance().display();
        //if ( display->getWireframeMode() == true )
        //{
        //    addWireFrameTechnique(mat, tileRender, HIGH_LOD);
        //}else
        {
            addNormalTechnique(mat, bbTile, HIGH_LOD);

            updateParams(mat, tileRender);
        }

        mat->setReceiveShadows( mReceiveDynamicShadows );

        //addFixedTechnique(mat, terrain, HIGH_LOD);

        return mat;

    }

    //---------------------------------------------------------------------
    void TerrainMaterialGeneratorA2::SM2Profile::updateParams(const MaterialPtr& mat, TerrainGroundTileRender* tileRender)
    {
        TerrainBBGroundTileRender* bbTile = (TerrainBBGroundTileRender*)tileRender;

        mShaderGen->updateParams(this, mat, bbTile);
    }

    //**********************************************************************************************************************
    //**********************************************************************************************************************

    //---------------------------------------------------------------------
    void TerrainMaterialGeneratorA2::SM2Profile::setLayerNormalMappingEnabled(bool enabled)
    {
        if (enabled != mLayerNormalMappingEnabled)
        {
            mLayerNormalMappingEnabled = enabled;
            mParent->_markChanged();
        }
    }
    //---------------------------------------------------------------------
    void TerrainMaterialGeneratorA2::SM2Profile::setLayerParallaxMappingEnabled(bool enabled)
    {
        if (enabled != mLayerParallaxMappingEnabled)
        {
            mLayerParallaxMappingEnabled = enabled;
            mParent->_markChanged();
        }
    }
    //---------------------------------------------------------------------
    void TerrainMaterialGeneratorA2::SM2Profile::setLayerSpecularMappingEnabled(bool enabled)
    {
        if (enabled != mLayerSpecularMappingEnabled)
        {
            mLayerSpecularMappingEnabled = enabled;
            mParent->_markChanged();
        }
    }
    //---------------------------------------------------------------------
    void  TerrainMaterialGeneratorA2::SM2Profile::setGlobalColourMapEnabled(bool enabled)
    {
        if (enabled != mGlobalColourMapEnabled)
        {
            mGlobalColourMapEnabled = enabled;
            mParent->_markChanged();
        }
    }
    //---------------------------------------------------------------------
    void  TerrainMaterialGeneratorA2::SM2Profile::setLightmapEnabled(bool enabled)
    {
        if (enabled != mLightmapEnabled)
        {
            mLightmapEnabled = enabled;
            mParent->_markChanged();
        }
    }
    //---------------------------------------------------------------------
    void  TerrainMaterialGeneratorA2::SM2Profile::setReceiveDynamicShadowsEnabled(bool enabled)
    {
        if (enabled != mReceiveDynamicShadows)
        {
            mReceiveDynamicShadows = enabled;
            mParent->_markChanged();
        }
    }
    //---------------------------------------------------------------------
    void TerrainMaterialGeneratorA2::SM2Profile::setReceiveDynamicShadowsDepth(bool enabled)
    {
        if (enabled != mDepthShadows)
        {
            mDepthShadows = enabled;
            mParent->_markChanged();
        }

    }
    //---------------------------------------------------------------------
    void TerrainMaterialGeneratorA2::SM2Profile::setReceiveDynamicShadowsLowLod(bool enabled)
    {
        if (enabled != mLowLodShadows)
        {
            mLowLodShadows = enabled;
            mParent->_markChanged();
        }
    }

    //---------------------------------------------------------------------
    void TerrainMaterialGeneratorA2::SM2Profile::addFixedTechnique(const MaterialPtr& mat, TerrainBBGroundTileRender* tileRender, TechniqueType tt)
    {
        Technique* tech = mat->createTechnique();

        // Only supporting one pass
        Pass* pass = tech->createPass();

        TextureUnitState* tu = NULL;

        // global normal map
        //tu = pass->createTextureUnitState(terrain->getLayerTextureName(0, 0));
    }

    //---------------------------------------------------------------------
    void TerrainMaterialGeneratorA2::SM2Profile::setTextureilter(TextureUnitState* tu)
    {
        IDisplay* display = EngineMain::getInstance().display();

        Flt bias = display->getTerrainMipmapBias();
        tu->setTextureMipmapBias(bias);

        if ( display->getTerrainTextureFiltering() == TFL_NONE )
        {
            tu->setTextureFiltering(FO_POINT, FO_POINT, FO_NONE);
        }else
            if ( display->getTerrainTextureFiltering() == TFL_BILINEAR )
            {
                tu->setTextureFiltering(FO_LINEAR, FO_LINEAR, FO_POINT);
            }else
                if ( display->getTerrainTextureFiltering() == TFL_TRILINEAR )
                {
                    tu->setTextureFiltering(FO_LINEAR, FO_LINEAR, FO_LINEAR);
                }else
                    if ( display->getTerrainTextureFiltering() == TFL_ANISOTROPIC )
                    {
                        tu->setTextureFiltering(FO_ANISOTROPIC, FO_ANISOTROPIC, FO_LINEAR);
                    }
    }
    //---------------------------------------------------------------------
    void TerrainMaterialGeneratorA2::SM2Profile::addWireFrameTechnique(
        const MaterialPtr& mat, TerrainBBGroundTileRender* tileRender, TechniqueType tt)
    {

        Technique* tech = mat->createTechnique();

        // Only supporting one pass
        Pass* pass = tech->createPass();

        pass->setLightingEnabled(false);
        pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
        pass->setCullingMode(Ogre::CULL_NONE);
        pass->setDepthCheckEnabled( false );

    }
    //---------------------------------------------------------------------
    void TerrainMaterialGeneratorA2::SM2Profile::addNormalTechnique(
        const MaterialPtr& mat, TerrainBBGroundTileRender* tileRender, TechniqueType tt)
    {
        const TerrainGroundSurface* surfaceMgr  = tileRender->getTerrainChunk()->getTerrainGroundSurface();
        IDisplay* display                   = EngineMain::getInstance().display();
        GpuProgramManager& gmgr             = GpuProgramManager::getSingleton();
        HighLevelGpuProgramManager& hmgr    = HighLevelGpuProgramManager::getSingleton();

        /////////////////////////////////////////////////////////////////////////////////

        Technique* tech = mat->createTechnique();

        // Only supporting one pass
        Pass* pass = tech->createPass();

        ShadowType st = display->getShadowType();
        if ( (st == SCL_PSSM_DIFFUSE_TEXTURE) || (st == SCL_PSSM_DEPTH_TEXTURE) )
        {
            tech->setShadowCasterMaterial("MG/Terrain/PSSM/DepthShadow/Caster");
        }else
        {
            tech->setShadowCasterMaterial("MG/Terrain/USM/DepthShadow/Caster");
        }

        /////////////////////////////////////////////////////////////////////////////////
        if (!mShaderGen)
        {
            bool check2x = mLayerNormalMappingEnabled || mLayerParallaxMappingEnabled;
            if (hmgr.isLanguageSupported("cg"))
                mShaderGen = OGRE_NEW ShaderHelperCg();
            else if (hmgr.isLanguageSupported("hlsl") &&
                ((check2x && gmgr.isSyntaxSupported("ps_2_x")) ||
                (!check2x && gmgr.isSyntaxSupported("ps_2_0"))))
                mShaderGen = OGRE_NEW ShaderHelperHLSL();
            else if (hmgr.isLanguageSupported("glsl"))
                mShaderGen = OGRE_NEW ShaderHelperGLSL();
            else
            {
                // todo
            }

            // check SM3 features
            mSM3Available = GpuProgramManager::getSingleton().isSyntaxSupported("ps_3_0");

        }

        /////////////////////////////////////////////////////////////////////////////////

        HighLevelGpuProgramPtr vprog = mShaderGen->generateVertexProgram(this, tileRender, tt);
        HighLevelGpuProgramPtr fprog = mShaderGen->generateFragmentProgram(this, tileRender, tt);

        pass->setVertexProgram(vprog->getName());
        pass->setFragmentProgram(fprog->getName());

        /////////////////////////////////////////////////////////////////////////////////

        if (tt == HIGH_LOD )
        {
            TextureUnitState* tu = NULL;

            /////////////////////////////////////////////////////////////////////////////////

            // global normal map
            //{
            //    tu = pass->createTextureUnitState();
            //    tu->setTextureName(surfaceMgr->getTerrainNormalMap()->getName());
            //    tu->setTextureAddressingMode(TextureUnitState::TAM_MIRROR);

            //    setTextureilter( tu );
            //}

            /////////////////////////////////////////////////////////////////////////////////

            // light map
            if (isLightmapEnabled())
            {
                tu = pass->createTextureUnitState(surfaceMgr->getLightmap()->getName());
                tu->setTextureAddressingMode(TextureUnitState::TAM_MIRROR);

                setTextureilter( tu );
            }

            /////////////////////////////////////////////////////////////////////////////////

            // region map
            if (isRegionMapEnabled())
            {
                tu = pass->createTextureUnitState(surfaceMgr->getRegionDisplayTexture()->getName());
                tu->setTextureAddressingMode(TextureUnitState::TAM_CLAMP);
                tu->setTextureFiltering(FO_POINT, FO_POINT, FO_NONE);
            }

            /////////////////////////////////////////////////////////////////////////////////

            // blend maps
            {
                const StringVector& bdList = tileRender->getValidBlendTextureNameList();
                for (uint i = 0; i < bdList.size(); ++i)
                {
                    tu = pass->createTextureUnitState(bdList[i]);
                    tu->setTextureAddressingMode(TextureUnitState::TAM_MIRROR);
                    setTextureilter( tu );
                }
            }

            /////////////////////////////////////////////////////////////////////////////////

            // diffuseSpecularTexture atlas textures
            {
                const StringVector& dsList = tileRender->getValidDiffuseSpecularTextureAtlasNameList();
                for (uint i = 0; i < dsList.size(); ++i)
                {
                    // diffuse / specular
                    tu = pass->createTextureUnitState(dsList[i]);
                    tu->setTextureAddressingMode(TextureUnitState::TAM_MIRROR);
                    setTextureilter( tu );
                    tu->setHardwareGammaEnabled( display->getGammaEnabled() );
                }
            }

            /////////////////////////////////////////////////////////////////////////////////

            // normalHeightTexture atlas textures
            if (isLayerNormalMappingEnabled())
            {
                const StringVector& nhList = tileRender->getValidNormalHeightTextureAtlasNameList();
                for (uint i = 0; i < nhList.size(); ++i)
                {
                    // normal / height
                    tu = pass->createTextureUnitState(nhList[i]);
                    tu->setTextureAddressingMode(TextureUnitState::TAM_MIRROR);
                    setTextureilter( tu );
                }
            }
        }
        else
        {
            // LOW_LOD textures
            // composite map

            // That's it!
        }

        // Add shadow textures (always at the end)
        if (isShadowingEnabled(tt, tileRender))
        {
            uint numTextures = 1;

            for (uint i = 0; i < numTextures; ++i)
            {
                TextureUnitState* tu = pass->createTextureUnitState();
                tu->setContentType(TextureUnitState::CONTENT_SHADOW);
                tu->setTextureAddressingMode(TextureUnitState::TAM_BORDER);
                tu->setTextureBorderColour(ColourValue(1,1,1,1));
            }
        }

    }
    //---------------------------------------------------------------------
    bool TerrainMaterialGeneratorA2::SM2Profile::isShadowingEnabled(TechniqueType tt, TerrainBBGroundTileRender* tileRender) const
    {
        return getReceiveDynamicShadowsEnabled() && tileRender->getTerrainManager()->getScene()->getOgreSceneManager()->isShadowTechniqueTextureBased();
    }
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    HighLevelGpuProgramPtr 
        TerrainMaterialGeneratorA2::SM2Profile::ShaderHelper::generateVertexProgram(
        const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt)
    {
        HighLevelGpuProgramPtr ret = createVertexProgram(prof, tileRender, tt);

        StringUtil::StrStreamType sourceStr;
        generateVertexProgramSource(prof, tileRender, tt, sourceStr);
        ret->setSource(sourceStr.str());
        ret->load();
        defaultVpParams(prof, tileRender, tt, ret);
#if OGRE_DEBUG_MODE
        LogManager::getSingleton().stream(LML_TRIVIAL) << "*** Terrain Vertex Program: " 
            << ret->getName() << " ***\n" << ret->getSource() << "\n***   ***";
#endif

        return ret;

    }
    //---------------------------------------------------------------------
    HighLevelGpuProgramPtr 
        TerrainMaterialGeneratorA2::SM2Profile::ShaderHelper::generateFragmentProgram(
        const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt)
    {
        HighLevelGpuProgramPtr ret = createFragmentProgram(prof, tileRender, tt);

        StringUtil::StrStreamType sourceStr;
        generateFragmentProgramSource(prof, tileRender, tt, sourceStr);
        ret->setSource(sourceStr.str());
        ret->load();
        defaultFpParams(prof, tileRender, tt, ret);

#if OGRE_DEBUG_MODE
        LogManager::getSingleton().stream(LML_TRIVIAL) << "*** Terrain Fragment Program: " 
            << ret->getName() << " ***\n" << ret->getSource() << "\n***   ***";
#endif

        return ret;
    }
    //---------------------------------------------------------------------
    void TerrainMaterialGeneratorA2::SM2Profile::ShaderHelper::generateVertexProgramSource(
        const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt, StringUtil::StrStreamType& outStream)
    {
        generateVpHeader(prof, tileRender, tt, outStream);

        if (tt != LOW_LOD && tileRender->getMtlType() != TerrainGroundTileRender::MTL_REFRACT)
        {
            uint maxLayers = prof->getMaxLayers(tileRender);
            uint numLayers = min(maxLayers, static_cast<uint>(tileRender->getTextureLayerCount()));

            for (uint i = 0; i < numLayers; ++i)
                generateVpLayer(prof, tileRender, tt, i, outStream);
        }

        generateVpFooter(prof, tileRender, tt, outStream);

    }
    //---------------------------------------------------------------------
    void TerrainMaterialGeneratorA2::SM2Profile::ShaderHelper::generateFragmentProgramSource(
        const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt, StringUtil::StrStreamType& outStream)
    {
        generateFpHeader(prof, tileRender, tt, outStream);

		if (tt != LOW_LOD && tileRender->getMtlType() != TerrainGroundTileRender::MTL_REFRACT)
        {
            uint maxLayers = prof->getMaxLayers(tileRender);
            uint numLayers = min(maxLayers, static_cast<uint>(tileRender->getTextureLayerCount()));

            for (uint i = 0; i < numLayers; ++i)
            {
                generateFpLayer(prof, tileRender, tt, i, outStream);
            }
        }

        generateFpFooter(prof, tileRender, tt, outStream);
    }
    //---------------------------------------------------------------------
    void TerrainMaterialGeneratorA2::SM2Profile::ShaderHelper::defaultVpParams(
        const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt, const HighLevelGpuProgramPtr& prog)
    {
        GpuProgramParametersSharedPtr params = prog->getDefaultParameters();
        params->setIgnoreMissingParams(true);

		if (tileRender->getMtlType() == TerrainGroundTileRender::MTL_REFRACT)
		{
			params->setNamedAutoConstant("worldViewProjMatrix", GpuProgramParameters::ACT_WORLDVIEWPROJ_MATRIX);
			params->setNamedAutoConstant("scene_depth_range", GpuProgramParameters::ACT_SCENE_DEPTH_RANGE);
		}
		else
		{
			///////////////////////////////////////////////////////////////////////////////////////////////////////////

			//params->setNamedAutoConstant("worldMatrix", GpuProgramParameters::ACT_WORLD_MATRIX);
			//params->setNamedAutoConstant("viewProjMatrix", GpuProgramParameters::ACT_VIEWPROJ_MATRIX);

			///////////////////////////////////////////////////////////////////////////////////////////////////////////

			params->setNamedAutoConstant("worldMatrix", GpuProgramParameters::ACT_WORLD_MATRIX);
			params->setNamedAutoConstant("worldViewProjMatrix", GpuProgramParameters::ACT_WORLDVIEWPROJ_MATRIX);
			params->setNamedAutoConstant("lightDirectionObjSpace", GpuProgramParameters::ACT_LIGHT_DIRECTION_OBJECT_SPACE, 0);
			params->setNamedAutoConstant("eyePosObjSpace", GpuProgramParameters::ACT_CAMERA_POSITION_OBJECT_SPACE);
			params->setNamedAutoConstant("eyeWorldDir", GpuProgramParameters::ACT_VIEW_DIRECTION);

			///////////////////////////////////////////////////////////////////////////////////////////////////////////

			params->setNamedAutoConstant("fogParams", GpuProgramParameters::ACT_FOG_PARAMS);

			///////////////////////////////////////////////////////////////////////////////////////////////////////////

			if (prof->isShadowingEnabled(tt, tileRender))
			{
				uint numTextures = 1;
				params->setNamedAutoConstant("texViewProj", GpuProgramParameters::ACT_TEXTURE_VIEWPROJ_MATRIX);
			}
		}
    }
    //---------------------------------------------------------------------
    void TerrainMaterialGeneratorA2::SM2Profile::ShaderHelper::defaultFpParams(
        const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt, const HighLevelGpuProgramPtr& prog)
	{
		GpuProgramParametersSharedPtr params = prog->getDefaultParameters();
		params->setIgnoreMissingParams(true);

		if (tileRender->getMtlType() != TerrainGroundTileRender::MTL_REFRACT)
		{
			params->setNamedAutoConstant("ambient", GpuProgramParameters::ACT_AMBIENT_LIGHT_COLOUR);
			params->setNamedAutoConstant("lightDiffuseColour", GpuProgramParameters::ACT_LIGHT_DIFFUSE_COLOUR, 0);
			params->setNamedAutoConstant("lightSpecularColour", GpuProgramParameters::ACT_LIGHT_SPECULAR_COLOUR, 0);
			params->setNamedAutoConstant("fogColour", GpuProgramParameters::ACT_FOG_COLOUR);

			if (prof->isShadowingEnabled(tt, tileRender))
			{
				uint numTextures = 1;
				//params->setNamedConstant("inverseShadowmapSize", Real(0.0009765625));
				//params->setNamedConstant("fixedDepthBias", Real(0.0005));
				//params->setNamedConstant("gradientClamp", Real(0.0098));
				//params->setNamedConstant("gradientScaleBias", Real(0));

				params->setNamedConstant("inverseShadowmapSize", Real(0.0009765625));
				params->setNamedConstant("fixedDepthBias", Real(0.009));
				params->setNamedConstant("gradientClamp", Real(1.9596));
				params->setNamedConstant("gradientScaleBias", Real(0.04));
			}
		}
		else
		{
			params->setNamedAutoConstant("scene_depth_range", GpuProgramParameters::ACT_SCENE_DEPTH_RANGE);
		}
    }
    //---------------------------------------------------------------------
    void TerrainMaterialGeneratorA2::SM2Profile::ShaderHelper::updateParams(
        const SM2Profile* prof, const MaterialPtr& mat, TerrainBBGroundTileRender* tileRender)
    {
        Pass* p = mat->getTechnique(0)->getPass(0);
        {
            // high lod
            updateVpParams(prof, tileRender, HIGH_LOD, p->getVertexProgramParameters());
            updateFpParams(prof, tileRender, HIGH_LOD, p->getFragmentProgramParameters());

        }
    }
    //---------------------------------------------------------------------
    void TerrainMaterialGeneratorA2::SM2Profile::ShaderHelper::updateVpParams(
        const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt, const GpuProgramParametersSharedPtr& params)
    {
        params->setIgnoreMissingParams(true);

        Vec4 scaleBiasSpecular = EngineMain::getInstance().display()->getScaleBiasSpecular();
        params->setNamedConstant("scaleBiasSpecular", Vector4(scaleBiasSpecular.x,scaleBiasSpecular.y,scaleBiasSpecular.z,scaleBiasSpecular.w));
    }
    //---------------------------------------------------------------------
    void TerrainMaterialGeneratorA2::SM2Profile::ShaderHelper::updateFpParams(
        const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt, const GpuProgramParametersSharedPtr& params)
    {
        params->setIgnoreMissingParams(true);

        // TODO - parameterise this?
        Vec4 scaleBiasSpecular = EngineMain::getInstance().display()->getScaleBiasSpecular();
        params->setNamedConstant("scaleBiasSpecular", Vector4(scaleBiasSpecular.x,scaleBiasSpecular.y,scaleBiasSpecular.z,scaleBiasSpecular.w));

        uint maxLayers = prof->getMaxLayers( tileRender );
        uint numLayers = min(maxLayers, static_cast<uint>( tileRender->getTextureLayerCount()));
        uint numUVMul = numLayers / 4;
        if (numLayers % 4)
            ++numUVMul;
        for (uint i = 0; i < numUVMul; ++i)
        {
            Vector4 uvMul(
                tileRender->getLayerUVMultiplier(i * 4), 
                tileRender->getLayerUVMultiplier(i * 4 + 1), 
                tileRender->getLayerUVMultiplier(i * 4 + 2), 
                tileRender->getLayerUVMultiplier(i * 4 + 3) 
                );
            params->setNamedConstant("uvMul" + StringConverter::toString(i), uvMul);
        }

    }
    //---------------------------------------------------------------------
    String TerrainMaterialGeneratorA2::SM2Profile::ShaderHelper::getRGBAChannel(uint idx)
    {
        uint rem = idx % 4;
        switch(rem)
        {
        case 0:
        default:
            return "r";
        case 1:
            return "g";
        case 2:
            return "b";
        case 3:
            return "a";
        };
    }

    //---------------------------------------------------------------------
    String TerrainMaterialGeneratorA2::SM2Profile::ShaderHelper::getXYZWChannel(uint idx)
    {
        uint rem = idx % 4;
        switch(rem)
        {
        case 0:
        default:
            return "x";
        case 1:
            return "y";
        case 2:
            return "z";
        case 3:
            return "w";
        };
    }

    //---------------------------------------------------------------------
    String TerrainMaterialGeneratorA2::SM2Profile::ShaderHelper::getVertexProgramName(
        const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt)
    {
        String progName = tileRender->getMaterialName() + "/sm2/vp";

        switch(tt)
        {
        case HIGH_LOD:
            progName += "/hlod";
            break;
        case LOW_LOD:
            progName += "/llod";
            break;
        }

        return progName;

    }
    //---------------------------------------------------------------------
    String TerrainMaterialGeneratorA2::SM2Profile::ShaderHelper::getFragmentProgramName(
        const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt)
    {

        String progName = tileRender->getMaterialName() + "/sm2/fp";

        switch(tt)
        {
        case HIGH_LOD:
            progName += "/hlod";
            break;
        case LOW_LOD:
            progName += "/llod";
            break;
        }

        return progName;
    }
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    HighLevelGpuProgramPtr
        TerrainMaterialGeneratorA2::SM2Profile::ShaderHelperCg::createVertexProgram(
        const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt)
    {
        HighLevelGpuProgramManager& mgr = HighLevelGpuProgramManager::getSingleton();
        String progName = getVertexProgramName(prof, tileRender, tt);
        HighLevelGpuProgramPtr ret = mgr.getByName(progName);
        if (ret.isNull())
        {
            ret = mgr.createProgram(progName, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
                "cg", GPT_VERTEX_PROGRAM);
        }
        else
        {
            ret->unload();
        }

        ret->setParameter("profiles", "vs_3_0 vs_2_0 arbvp1");
        ret->setParameter("entry_point", "main_vp");

        return ret;

    }
    //---------------------------------------------------------------------
    HighLevelGpuProgramPtr
        TerrainMaterialGeneratorA2::SM2Profile::ShaderHelperCg::createFragmentProgram(
        const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt)
    {
        HighLevelGpuProgramManager& mgr = HighLevelGpuProgramManager::getSingleton();
        String progName = getFragmentProgramName(prof, tileRender, tt);

        HighLevelGpuProgramPtr ret = mgr.getByName(progName);
        if (ret.isNull())
        {
            ret = mgr.createProgram(progName, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
                "cg", GPT_FRAGMENT_PROGRAM);
        }
        else
        {
            ret->unload();
        }

        if(prof->isLayerNormalMappingEnabled() || prof->isLayerParallaxMappingEnabled() || prof->isShadowingEnabled(tt,tileRender) )
            ret->setParameter("profiles", "ps_3_0 ps_2_x fp40 arbfp1");
        else
            ret->setParameter("profiles", "ps_3_0 ps_2_0 fp30 arbfp1");
        ret->setParameter("entry_point", "main_fp");

        return ret;

    }
    //---------------------------------------------------------------------
    void TerrainMaterialGeneratorA2::SM2Profile::ShaderHelperCg::generateVpHeader(
        const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt, StringUtil::StrStreamType& outStream)
    {
		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		//input
		if (tileRender->getMtlType() == TerrainGroundTileRender::MTL_REFRACT)
		{
			outStream << 
				"void main_vp(\n"
				" float4 pos : POSITION\n"
				",uniform float4x4 worldViewProjMatrix\n"
				",uniform float4 depthRange\n"
				",out float4 oPos : POSITION\n"
				",out float2 odepth : TEXCOORD0" << "\n";

			//////////////////////////////////////////////////////////////////////////////////////////////////////////

			outStream <<
				")\n"
				"{\n";

			//////////////////////////////////////////////////////////////////////////////////////////////////////////

			outStream <<
				"oPos = mul(worldViewProjMatrix, pos);\n";

			outStream << 
				"odepth.x = (oPos.z - depthRange.x) * depthRange.w;\n"
				"odepth.y = oPos.w;\n";

			//outStream << 
			//	"odepth.xy = oPos.zw;\n";

		}
		else
		{
			outStream << 
				"void main_vp(\n"
				" float4 pos : POSITION\n"
				",float3 normal : NORMAL\n"
				",float2 uv0  : TEXCOORD0\n"
				",float2 uv1  : TEXCOORD1\n"
				",float4 diffuse : COLOR\n";

			//outStream << 
			//",float3 tangent : TANGENT0\n";

			//////////////////////////////////////////////////////////////////////////////////////////////////////////
			//uniform

			outStream << 
				",uniform float4x4 worldMatrix\n"
				",uniform float4x4 worldViewProjMatrix\n"
				//",uniform float4x4 worldMatrix\n"
				//",uniform float4x4 viewProjMatrix\n";
				",uniform float4 lightDirectionObjSpace\n"
				",uniform float3 eyePosObjSpace\n"
				",uniform float3 eyeWorldDir\n"
				",uniform float4 scaleBiasSpecular\n";

			//////////////////////////////////////////////////////////////////////////////////////////////////////////
			//output

			//position
			outStream <<
				",out float4 oPos : POSITION\n";
			//",out float4 oPosObj : TEXCOORD0\n";

			//////////////////////////////////////////////////////////////////////////////////////////////////////////

			//diffuse
			//outStream <<
			//    "out float3 oDiffuse : COLOR,\n";

			//////////////////////////////////////////////////////////////////////////////////////////////////////////

			// UV
			uint texCoordSet = 0;

			outStream <<
				",out float2 oUVMisc0 : TEXCOORD" << texCoordSet++ <<"\n";
			outStream <<
				",out float2 oUVMisc1 : TEXCOORD" << texCoordSet++ <<"\n";   

			//////////////////////////////////////////////////////////////////////////////////////////////////////////

			// TBN Space Light params
			if (prof->isLayerNormalMappingEnabled())
			{
				outStream <<
					",out float3 oTSLightDir : TEXCOORD" << texCoordSet++ <<"\n";

				outStream <<
					",out float3 oTSeyeDir : TEXCOORD" << texCoordSet++ <<"\n";

				//outStream <<
				//    ",out float3 oTSHalfVector : TEXCOORD" << texCoordSet++ <<"\n";

				//outStream <<
				//    ",out float oLitRes : TEXCOORD" << texCoordSet++ <<"\n";

			}else
			{
				outStream <<
					",out float3 oLitRes : TEXCOORD" << texCoordSet++ <<"\n";
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////

			//fog
			if ( Display::getSingletonPtr()->getFogLevel() != FOL_NONE )
			{
				outStream <<
					",uniform float4 fogParams\n"
					",out float fogVal : COLOR\n";
			}

			if (tileRender->getMtlType() == TerrainGroundTileRender::MTL_REFRACT)
			{
				outStream <<
					",out float2 depth : TEXCOORD" << texCoordSet++ <<"\n";
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////
			//set

			if (prof->isShadowingEnabled(tt, tileRender))
			{
				texCoordSet = generateVpDynamicShadowsParams(texCoordSet, prof, tileRender, tt, outStream);
			}

			// check we haven't exceeded texture coordinates
			if (texCoordSet > 8)
			{
				OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, 
					"Requested options require too many texture coordinate sets! Try reducing the number of layers.",
					__FUNCTION__);
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////

			outStream <<
				")\n"
				"{\n";

			//////////////////////////////////////////////////////////////////////////////////////////////////////////

			outStream <<
				"oPos = mul(worldViewProjMatrix, pos);\n";
			//"oPosObj = pos;\n";


			//////////////////////////////////////////////////////////////////////////////////////////////////////////

			//outStream <<
			//    "	};\n";
			//return;

			/////////////////////////////////////////////////////////////////////////////

			outStream << 
				"	normal = normalize(normal);\n";

			/////////////////////////////////////////////////////////////////////////////

			outStream <<
				"	float3 lightDir = \n"
				//"		lightPosObjSpace.xyz -  (iPosition.xyz * lightPosObjSpace.w);\n"
				"		- lightDirectionObjSpace.xyz;\n"
				"	float3 eyeDir = eyePosObjSpace - pos.xyz;\n";

			outStream << "	lightDir = normalize(lightDir);\n";


			/////////////////////////////////////////////////////////////////////////////

			if (prof->isLayerNormalMappingEnabled())
			{
				// derive the tangent space basis
				// we do this in the pixel shader because we don't have per-vertex normals
				// because of the LOD, we use a normal map
				// tangent is always +x or -z in object space depending on alignment

				//ALIGN_X_Z:
				outStream << "  float3 tangent = float3(1, 0, 0);\n";
				outStream << "	float3 binormal = normalize(cross(tangent, normal));\n";
				// note, now we need to re-cross to derive tangent again because it wasn't orthonormal
				outStream << "	tangent = normalize(cross(normal, binormal));\n";

				// derive final matrix
				outStream << "	float3x3 TBN = float3x3(tangent, binormal, normal);\n";


				// light dir
				{
					//outStream << "	oTSLightDir			= normalize(float3(1,1,1));\n";

					/////////////////////////////////////////////////////////////////////////////////////////////

					outStream << "	oTSLightDir     = normalize(mul(TBN, lightDir));\n";

					/////////////////////////////////////////////////////////////////////////////////////////////

					//outStream << "	oTSLightDir     = float3(-eyeWorldDir.x,eyeWorldDir.y,-eyeWorldDir.z);\n";

					/////////////////////////////////////////////////////////////////////////////////////////////

					//outStream << "	oTSLightDir     = normalize(mul(TBN, -eyeWorldDir));\n";

					/////////////////////////////////////////////////////////////////////////////////////////////

					//outStream << "	oTSLightDir		= float3( lightDir.x, lightDir.z, lightDir.y) ;\n";

					/////////////////////////////////////////////////////////////////////////////////////////////


					// 不传递光线方向
					/*
					outStream << "	oTSLightDir     = normalize(mul(TBN, eyeDir));\n";
					*/

				}


				// half vector
				{
					outStream << "	oTSeyeDir       = normalize(mul(TBN, eyeDir));\n";


					// 不传递半角方向
					//outStream << "	oTSHalfVector   = normalize(oTSLightDir + oTSeyeDir);\n";
					//outStream << "	oTSHalfVector   = oTSLightDir;\n";

					//////////////////////////////////////////////////////////////////////////

					//outStream << "	oTSHalfVector   = -eyeWorldDir + eyeDir;\n";
					//outStream << "	oTSHalfVector   = normalize(mul(TBN, oTSHalfVector));\n";
				}

				// n dot l
				{

					//outStream << "	oLitRes = dot(lightDir, normal);\n";
					//            outStream << "	oLitRes = oLitRes * 0.5 + 0.5;\n";

					//outStream << "	oLitRes = sign(oLitRes);\n";
					//outStream << "	oTSLightDir = oTSLightDir * oLitRes;\n";
					//outStream << "	oLitRes =  clamp( oLitRes, 0, 1 ) + clamp( oLitRes, -1, 0 ) * 0.5 ;\n";
				}


			}
			else
			{
				// simple per-pixel lighting with no normal mapping
				outStream << "	eyeDir = normalize(eyeDir);\n";
				outStream << "	float3 halfAngle = normalize(lightDir + eyeDir);\n";

				/////////////////////////////////////////////////////////////////////////////

				outStream << "	oLitRes.x = 1;\n";

				//outStream << "	oLitRes.y = dot(lightDir, normal);\n";
				outStream << "	float3 ln1 = dot(lightDir, normal);\n";
				outStream << "	float3 ln2 = -ln1 * 0.5;\n";
				outStream << "	oLitRes.y = clamp(ln1,0,1) + clamp(ln2,0,1);\n";

				outStream << "	oLitRes.z = pow(saturate(dot(normal, halfAngle)), scaleBiasSpecular.z);\n";

				///////////////////////////////////////////////////////////////////////////////

			}

			if (tileRender->getMtlType() == TerrainGroundTileRender::MTL_REFRACT)
			{
				outStream << "depth.xy = oPos.zw;\n";
			}
		}
    }
    //---------------------------------------------------------------------
    void TerrainMaterialGeneratorA2::SM2Profile::ShaderHelperCg::generateFpHeader(
        const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt, StringUtil::StrStreamType& outStream)
    {
		// Main header
		outStream << 
			// helpers
			"float4 expand(float4 v)\n"
			"{ \n"
			"	return v * 2 - 1;\n"
			"}\n\n\n";

		if (tileRender->getMtlType() == TerrainGroundTileRender::MTL_REFRACT)
		{
			////////////////////////////////////////////////////////////////////////////////////////////////////
			outStream << 
				"float4 main_fp(\n";

			////////////////////////////////////////////////////////////////////////////////////////////////////

			outStream <<
				"float2 depth			 : TEXCOORD0\n";

			outStream << 
				") : COLOR\n"
				"{\n"
				"	float4 outputCol;\n";
		}
		else
		{
			if (prof->isShadowingEnabled(tt, tileRender))
				generateFpDynamicShadowsHelpers(prof, tileRender, tt, outStream);


			////////////////////////////////////////////////////////////////////////////////////////////////////
			outStream << 
				"float4 main_fp(\n";

			////////////////////////////////////////////////////////////////////////////////////////////////////

			//input
			uint texCoordSet = 0;

			////////////////////////////////////////////////////////////////////////////////////////////////////

			//uv
			outStream <<
				" float2 uvMisc0 : TEXCOORD" << texCoordSet++ << "\n";

			outStream <<
				",float2 uvMisc1 : TEXCOORD" << texCoordSet++ << "\n";

			/////////////////////////////////////////////////////////////////////////////////////////////////////

			// TBN Space Light params
			if (prof->isLayerNormalMappingEnabled())
			{
				outStream <<
					",float3 iTSLightDir     : TEXCOORD" << texCoordSet++ << "\n";

				outStream <<
					",float3 iTSeyeDir       : TEXCOORD" << texCoordSet++ << "\n";

				//outStream <<
				//    ",float3 iTSHalfVector   : TEXCOORD" << texCoordSet++ << "\n";

				//outStream <<
				//    ",float iLitRes         : TEXCOORD" << texCoordSet++ << "\n";
			}else
			{
				outStream <<
					",float3 iLitRes         : TEXCOORD" << texCoordSet++ << "\n";
			}

			if (tileRender->getMtlType() == TerrainGroundTileRender::MTL_REFRACT)
			{
				outStream <<
					",float2 depth			 : TEXCOORD" << texCoordSet++ << "\n";
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////

			// UV's premultiplied, packed as xy/zw
			uint maxLayers = prof->getMaxLayers(tileRender);
			uint numBlendTextures = tileRender->getValidBlendTextureNameList().size();
			uint numLayers = min(maxLayers, static_cast<uint>(tileRender->getTextureLayerCount()));


			/////////////////////////////////////////////////////////////////////////////////////////////////////

			// uv multipliers
			uint numUVMultipliers = (numLayers / 4);
			if (numLayers % 4)
				++numUVMultipliers;
			for (uint i = 0; i < numUVMultipliers; ++i)
				outStream << ",uniform float4 uvMul" << i << " \n";

			/////////////////////////////////////////////////////////////////////////////////////////////////////

			//fog
			if ( Display::getSingletonPtr()->getFogLevel() != FOL_NONE )
			{
				outStream <<
					",uniform float3 fogColour\n"
					",float fogVal : COLOR\n";
			}


			/////////////////////////////////////////////////////////////////////////////////////////////////////
			// uniform
			outStream <<
				// Only 1 light supported in this version
				// deferred shading profile / generator later, ok? :)
				",uniform float3 ambient\n"
				",uniform float3 lightDiffuseColour\n"
				",uniform float3 lightSpecularColour\n"
				// pack scale, bias and specular
				",uniform float4 scaleBiasSpecular\n";

			/////////////////////////////////////////////////////////////////////////////////////////////////////
			// sampler2D
			uint currentSamplerIdx = 0;
			{
				/////////////////////////////////////////////////////////////////////////////////////////////////////

				//currentSamplerIdx++;

				/////////////////////////////////////////////////////////////////////////////////////////////////////

				if (prof->isLightmapEnabled())
				{
					outStream << ", uniform sampler2D lightMap : register(s" 
						<< currentSamplerIdx++ << ")\n";
				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////

				if ( prof->isRegionMapEnabled() )
				{
					outStream << ", uniform sampler2D regionMap : register(s" 
						<< currentSamplerIdx++ << ")\n";
				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////

				// Blend textures - sampler definitions
				for (uint i = 0; i < numBlendTextures; ++i)
				{
					outStream << ", uniform sampler2D blendTex" << i 
						<< " : register(s" << currentSamplerIdx++ << ")\n";
				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////

				// Layer textures - sampler definitions & UV multipliers
				{
					const StringVector& dsList = tileRender->getValidDiffuseSpecularTextureAtlasNameList();

					for (uint i = 0; i < dsList.size(); ++i)
					{
						outStream << ", uniform sampler2D difftex" << i 
							<< " : register(s" << currentSamplerIdx++ << ")\n";
					}
				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////

				if (prof->isLayerNormalMappingEnabled())
				{
					const StringVector& nhList = tileRender->getValidNormalHeightTextureAtlasNameList();

					for (uint i = 0; i < nhList.size(); ++i)
					{
						outStream << ", uniform sampler2D normtex" << i 
							<< " : register(s" << currentSamplerIdx++ << ")\n";
					}
				}
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////

			if (prof->isShadowingEnabled(tt, tileRender))
			{
				generateFpDynamicShadowsParams(&texCoordSet, &currentSamplerIdx, prof, tileRender, tt, outStream);
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////

			// check we haven't exceeded samplers
			if (currentSamplerIdx > TERRAIN_MAX_TEXTURE)
			{
				OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, 
					"Requested options require too many texture samplers! Try reducing the number of layers.",
					__FUNCTION__);
			}

			outStream << 
				") : COLOR\n"
				"{\n"
				"	float4 outputCol;\n";


			//////////////////////////////////////////////////////////////////////////////////////////////////////////

			//outStream <<
			//    "	return outputCol; };\n";
			//return;

			//////////////////////////////////////////////////////////////////////////////////////////////////////////

			outStream << 
				"	float shadow = 1.0;\n"
				"	float2 uv0 = uvMisc0.xy;\n"
				"	float2 uv1 = uvMisc1.xy;\n"
				// base colour
				"	outputCol = float4(0,0,0,1);\n";

			///////////////////////////////////////////////////////////

			outStream <<
				// set up accumulation areas
				"	float3 diffuse = float3(0.5,0.5,0.5);\n";

			///////////////////////////////////////////////////////////

			outStream <<
				// set up accumulation areas
				"	float3 smooth = float3(0.5,0.5,1.0f);\n";

			///////////////////////////////////////////////////////////

			if (prof->isLayerSpecularMappingEnabled())
			{
				outStream <<
					"	float specular = 0;\n";
			}

			///////////////////////////////////////////////////////////

			outStream <<
				//"	float2 dWorldX = ddx(uv0*10);\n"
				//"	float2 dWorldY = ddy(uv0*10);\n";
				"	float2 dWorldX;\n"
				"	float2 dWorldY;\n";

			//outStream << "	dWorldX = ddx(uv0.xy * 8 );\n";
			//outStream << "	dWorldY = ddy(uv0.xy * 8 );\n";

			///////////////////////////////////////////////////////////

			{
				// set up the blend values
				for (uint i = 0; i < numBlendTextures; ++i)
				{
					outStream << "	float4 blendTexVal" << i << " = tex2D(blendTex" << i << ", uv1);\n";
				}

				if (prof->isLayerNormalMappingEnabled())
				{
					outStream <<  "	float4 litRes       = float4(1,1,1,1);\n" ;
					outStream <<  "	float4 litResLayer  = float4(1,1,1,1);\n" ;
					outStream <<  "	float3 TSnormal;\n" ;
					outStream <<  "	float3 TSnormalDot1;\n" ;
					outStream <<  "	float3 TSnormalDot2;\n" ;

					if (prof->isLayerParallaxMappingEnabled())
						outStream << "	float disPlaceEntityment;\n";
				}
				else
				{
					// simple per-pixel lighting with no normal mapping
					outStream << "	float4 litRes = float4(iLitRes,1);\n";
				}
			}
		}
    }
    //---------------------------------------------------------------------
    void TerrainMaterialGeneratorA2::SM2Profile::ShaderHelperCg::generateVpLayer(
        const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt, uint layer, StringUtil::StrStreamType& outStream)
    {
        // nothing to do
    }
    //---------------------------------------------------------------------
    void TerrainMaterialGeneratorA2::SM2Profile::ShaderHelperCg::generateFpLayer(
        const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt, uint layer, StringUtil::StrStreamType& outStream)
    {
        uint uvIdx = layer / 2;
        String uvChannels = layer % 2 ? ".zw" : ".xy";
        uint blendIdx = (layer-1) / 4;
        String blendChannel = getRGBAChannel(layer-1);
        String blendWeightStr = String("blendTexVal") + StringConverter::toString(blendIdx) + 
            "." + blendChannel;

        // generate early-out conditional
        /* Disable - causing some issues even when trying to force the use of texldd
        if (layer && prof->_isSM3Available())
        outStream << "  if (" << blendWeightStr << " > 0.0003)\n  { \n";
        */

        const TerrainBBGroundTileRender::TextureLayerInstance* TextureLayerInstance = tileRender->getTextureLayer( layer );
        if ( TextureLayerInstance == false )
        {
            return;
        }

        outStream << "	\n";
        outStream << "	////////////////////////////////////////////////;\n";
        outStream << "	\n";

        // 计算全局uv
        // generate UV
        //outStream << "	float2 originalUV" << layer << " = layerUV" << uvIdx << uvChannels << ";\n";
        uint uvMulIdx = layer / 4;
        outStream << "	float2 originalUV" << layer << " = " << " uv0.xy * uvMul" << uvMulIdx << "." << getXYZWChannel(layer) << ";\n";
        //outStream << "	float2 originalUV" << layer << " = " << " uv0.xy * 8 ;\n";



        //现在暂时统一使用diffuseSpecular相关参数作为贴图集参考
        Vec2 uvPos  = TextureLayerInstance->diffuseSpecularUVPos;
        Vec2 uvSize = TextureLayerInstance->diffuseSpecularUVSize;

        outStream << "	float2 atlasUV" << layer 
            << " = float2(" << uvPos.x << "," << uvPos.y << " ) " 
            << " + float2( frac( originalUV" << layer << ".x ) * " << uvSize.x 
            << ", frac( originalUV" << layer << ".y ) * " << uvSize.y << " ) ;\n" ;

        // DDX DDY
        //outStream << "	dWorldX = ddx( " << " uv1.xy * uvMul" << uvMulIdx << "." << getXYZWChannel(layer) <<  ");\n";
        //outStream << "	dWorldY = ddy( " << " uv1.xy * uvMul" << uvMulIdx << "." << getXYZWChannel(layer) <<  ");\n";
        outStream << "	dWorldX = ddx( " << " originalUV" << layer <<  ");\n";
        outStream << "	dWorldY = ddy( " << " originalUV" << layer <<  ");\n";
        //outStream << "	dWorldX = uv0.xy * 8;\n";
        //outStream << "	dWorldY = uv1.xy * 8;\n";


        // calculate lighting here if normal mapping
        if (prof->isLayerNormalMappingEnabled())
        {
            if (prof->isLayerParallaxMappingEnabled())
            {
                // modify UV - note we have to sample an extra time
                outStream << 
                    "	disPlaceEntityment = tex2D(normtex" 
                    << TextureLayerInstance->normalHeightTextureIndex 
                    <<  ", atlasUV" << layer 
                    //<<  ",ddx( " << "originalUV" << layer << ")"
                    //<<  ",ddy( " << "originalUV" << layer << ")"
                    //<<  ",dWorldX,dWorldY" 
                    <<  ").a "
                    " * scaleBiasSpecular.x + scaleBiasSpecular.y;\n";

                outStream << "	originalUV" << layer << " += iTSeyeDir.xy * disPlaceEntityment;\n";

                outStream << "	atlasUV" << layer 
                    << " = float2(" << uvPos.x << "," << uvPos.y << " ) " 
                    << " + float2(  frac( originalUV" << layer << ".x ) * " << uvSize.x 
                    << ",  frac( originalUV" << layer << ".y ) * " << uvSize.y << " ) ;\n" ;
            }

            // access TS normal map
            outStream << "	TSnormal = tex2D(normtex" << TextureLayerInstance->normalHeightTextureIndex 
                <<  ", atlasUV" << layer 
                //<<  ",ddx( " << "originalUV" << layer << ")"
                //<<  ",ddy( " << "originalUV" << layer << ")"
                <<  ",dWorldX,dWorldY"
                <<  ").rgb;\n";

            {
                // Calculate normal
                //outStream << "	TSnormal = lerp( smooth, TSnormal, scaleBiasSpecular.w );\n";
                outStream << "	TSnormal = normalize( ( TSnormal * 2.0f ) - 1.0f );\n";
                //outStream << "	litResLayer.y = dot(TSnormal, iTSLightDir);\n";
                //outStream << "	litResLayer.y = dot(TSnormal, iTSeyeDir);\n";

                outStream << "	TSnormalDot1 = dot(TSnormal, iTSLightDir);\n";
                outStream << "	TSnormalDot2 = -TSnormalDot1 * 0.5;\n";
                outStream << "	litResLayer.y = clamp( TSnormalDot1, 0, 1 ) + clamp( TSnormalDot2, 0, 1 );\n";
            }

            if (prof->isLayerSpecularMappingEnabled())
            {
                //outStream << "	litResLayer.z = pow(saturate(dot(TSnormal, iTSHalfVector)), scaleBiasSpecular.z);\n";
                outStream << "	litResLayer.z = pow(saturate(dot(TSnormal, iTSeyeDir)), scaleBiasSpecular.z);\n";
            }

            if (!layer)
            {
                outStream << "	litRes = litResLayer;\n";
            }else
            {
                outStream << "	litRes = lerp(litRes, litResLayer, " << blendWeightStr << ");\n";
            }
        }

        // sample diffuse texture
        {
            //outStream << "	float4 diffuseSpecTex" << layer 
            //    << " = tex2D(difftex" << TextureLayerInstance->diffuseSpecularTextureIndex << ", atlasUV" << layer << ");\n";

            outStream << "	float4 diffuseSpecTex" << layer 
                << " = tex2D(difftex" << TextureLayerInstance->diffuseSpecularTextureIndex 
                <<  ", atlasUV" << layer 
                //<<  ",ddx( " << "originalUV" << layer << ")"
                //<<  ",ddy( " << "originalUV" << layer << ")"
                <<  ",dWorldX,dWorldY"
                <<  ");\n";

            DYNAMIC_ASSERT( TextureLayerInstance->diffuseSpecularTextureIndex >= 0 );
        }

        // apply to common
        if (!layer)
        {
            if (prof->isLayerColorMappingEnabled()) 
            {
                outStream << "	diffuse = diffuseSpecTex0.rgb;\n";
            }

            if (prof->isLayerSpecularMappingEnabled())
            {
                outStream << "	specular = diffuseSpecTex0.a;\n";
            }
        }
        else
        {
            //if (prof->isLayerColorMappingEnabled()) 
            {
                outStream << "	diffuse = lerp(diffuse, diffuseSpecTex" << layer 
                    << ".rgb, " << blendWeightStr << ");\n";
            }

            if (prof->isLayerSpecularMappingEnabled())
                outStream << "	specular = lerp(specular, diffuseSpecTex" << layer 
                << ".a, " << blendWeightStr << ");\n";
        }

        // End early-out
        /* Disable - causing some issues even when trying to force the use of texldd
        if (layer && prof->_isSM3Available())
        outStream << "  } // early-out blend value\n";
        */
    }
    //---------------------------------------------------------------------
    void TerrainMaterialGeneratorA2::SM2Profile::ShaderHelperCg::generateVpFooter(
        const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt, StringUtil::StrStreamType& outStream)
    {

        //outStream << 
        //    "	oPos = mul(viewProjMatrix, worldPos);\n";

        //outStream << 
        //    "	oDiffuse = diffuse;\n";

		if (tileRender->getMtlType() != TerrainGroundTileRender::MTL_REFRACT)
		{
			outStream << 
				"	oUVMisc0.xy = uv0.xy;\n"
				"	oUVMisc1.xy = uv1.xy;\n";


			///////////////////////////////////////////////////////////////////////

			if ( Display::getSingletonPtr()->getFogLevel() != FOL_NONE )
			{
				if ( Display::getSingletonPtr()->getFogLevel() == FOL_LINEAR )
				{
					outStream <<
						"	fogVal = saturate((oPos.z - fogParams.y) * fogParams.w);\n";
				}
				else
				{
					outStream <<
						//"	fogVal = saturate(1 / (exp(oPos.z * fogParams.x)));\n";
						"	fogVal = saturate(1 - exp(oPos.z * -fogParams.x));\n";
				}
			}

			///////////////////////////////////////////////////////////////////////

			if (prof->isShadowingEnabled(tt, tileRender))
				generateVpDynamicShadows(prof, tileRender, tt, outStream);
		}

        outStream << 
            "}\n";


    }
    //---------------------------------------------------------------------
    void TerrainMaterialGeneratorA2::SM2Profile::ShaderHelperCg::generateFpFooter(
        const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt, StringUtil::StrStreamType& outStream)
    {

        outStream << "////////////////////////////////////////;\n";

        ///////////////////////////////////////////////////////////////////////////

		if (tileRender->getMtlType() != TerrainGroundTileRender::MTL_REFRACT)
		{
			if (tt == LOW_LOD)
			{
				if (prof->isShadowingEnabled(tt, tileRender))
				{
					generateFpDynamicShadows(prof, tileRender, tt, outStream);
					outStream << 
						"	outputCol.rgb = diffuse * rtshadow;\n";
				}
				else
				{
					outStream << 
						"	outputCol.rgb = diffuse;\n";
				}
			}
			else
			{
				///////////////////////////////////////////////////////////////////////////

				if (prof->isLightmapEnabled())
				{
					// sample lightmap
					outStream << "	shadow = tex2D(lightMap, uv0).r;\n";
				}

				///////////////////////////////////////////////////////////////////////////

				if (prof->isShadowingEnabled(tt, tileRender))
				{
					generateFpDynamicShadows(prof, tileRender, tt, outStream);
				}

				///////////////////////////////////////////////////////////////////////////

				{
					Vec4 sp = Display::getSingleton().getShadowParameter();

					if ( prof->isLightmapEnabled() || prof->isShadowingEnabled(tt, tileRender) )
					{
						outStream << "	shadow =  shadow * " <<  (1-sp.x)  << " + " << sp.x << "  ;\n";
					}
				}

				///////////////////////////////////////////////////////////////////////////
				// clamp normal

				if (prof->isLayerNormalMappingEnabled())
				{

					{
						// float iLitRes 三角面法线和光线点积
						// float litRes.y 法线贴图法线和光线点积
					}


					Vec4 sbsl = Display::getSingletonPtr()->getScaleBiasSpecular();


					{
						//outStream << "	float clampNormal =  litRes.y ;\n";
					}

					{
						// 截断背面光照
						outStream << "	float clampNormal = clamp( litRes.y, 0, 1 ) ;\n";
					}


					{
						// 截断z背面光照
						//outStream << "	float w = 1 - scaleBiasSpecular.w ;\n";

						//outStream << "	float clampFrontHalfNormal	= clamp( litRes.y - w, 0 , 1 - w );\n";
						//outStream << "	float clampBackHalfNormal	= clamp( litRes.y - w, 0 - w, 0 );\n";

						//outStream << "	float clampNormal = clampFrontHalfNormal + clampBackHalfNormal * clampBackHalfNormal + w ;\n";
					}

					{
						//outStream << "	float clampNormal = litRes.y ;\n";

						//outStream << "	iLitRes =  sign(iLitRes) ;\n";
						//outStream << "	iLitRes =  clamp( litRes.y, 0, 1 ) + clamp( iLitRes, -1, 0 ) * 0.5 ;\n";

						//outStream << "	clampNormal =  clampNormal * iLitRes ;\n";
					}

					{
						// 正方2个方向光照
						//               outStream << "	float clampNormal = clamp( litRes.y, 0, 1 );\n";
						//               outStream << "	clampNormal += -clamp( litRes.y, -1, 0 ) * 0.5;\n";
						//outStream << "	clampNormal += -clamp( litRes.y, -1, 0 );\n";
					}

					{
						// 凹凸感会减弱
						//outStream << "	float clampNormal =  litRes.y * 0.5 + 0.5 ;\n";
					}

					////////////////////////////////////////////////////////////////////////////////

					{
						// 整体变暗
						//outStream << "	clampNormal = pow(clampNormal, scaleBiasSpecular.w) ;\n";
					}

					{
						// 整体变化
						//outStream << "	clampNormal = clampNormal * scaleBiasSpecular.w ;\n";
					}

					////////////////////////////////////////////////////////////////////////////////

					{
						//outStream << "	float clampNormal = clamp( litRes.y, 0, 1 );\n";
						//outStream << "	clampNormal += -clamp( litRes.y, -1, 0 ) * 0.5;\n";

						////////////////////////////////////////////////////////////////////////////////

						//outStream << "	float globalNormal =  iLitRes * 0.5 + 0.5 ;\n";

						////////////////////////////////////////////////////////////////////////////////

						//outStream << "	globalNormal = clampNormal * globalNormal ;\n";
						//outStream << "	globalNormal = clampNormal ;\n";

					}

					////////////////////////////////////////////////////////////////////////////////

					{
						//outStream << "	iLitRes         =  ( iLitRes - 0.5 ) * 2 ;\n";
						//outStream << "	float isBack    =  -sign( iLitRes ) ;\n";
						//outStream << "	isBack          =  clamp( isBack, 0, 1 ) ;\n";

						//outStream << "	iLitRes         =  - clamp( iLitRes, -1, 0 ) ;\n";
						//outStream << "	iLitRes         =  1 - iLitRes ;\n";
					}

					////////////////////////////////////////////////////////////////////////////////
					////////////////////////////////////////////////////////////////////////////////
					////////////////////////////////////////////////////////////////////////////////

					{
						Vec4 tl = Display::getSingleton().getTerrainLightingParameter();

						//outStream << "	float ambientNormal =  clampNormal * 0.5 + 0.5 ;\n";
						outStream << "	float ambientNormal =  clampNormal * " <<  (1-tl.x)  << " + " << tl.x << "  ;\n";

						//outStream << "	iLitRes = iLitRes * 0.5 + 0.5 ;\n";    
						//outStream << "	iLitRes = iLitRes * isBack ;\n";  
						//outStream << "	ambientNormal = ambientNormal * ( 1 - iLitRes ) + iLitRes ;\n";

						//outStream << "	ambientNormal += 0.2 * isBack ;\n"; 
					}

					////////////////////////////////////////////////////////////////////////////////

					{
						// diffuse lighting
						outStream << "	outputCol.rgb += ambient * diffuse * ambientNormal + lightDiffuseColour * diffuse  * clampNormal * shadow;\n";
					}

					///////////////////////////////////////////////////////////////////////////

					// specular default
					if (prof->isLayerSpecularMappingEnabled())
					{
						//outStream << "	specular = 1.0;\n";
						// Apply specular
						outStream << "	outputCol.rgb += lightSpecularColour * specular * shadow * litRes.z ;\n";
					}

					///////////////////////////////////////////////////////////////////////////

				}else
				{
					outStream << "	float clampNormal = clamp( litRes.y, 0, 1 );\n";
					outStream << "	clampNormal += -clamp( litRes.y, -1, 0 ) * 0.5;\n";


					///////////////////////////////////////////////////////////////////////////

					// diffuse lighting
					outStream << "	outputCol.rgb += ambient * diffuse  + lightDiffuseColour * diffuse * shadow * clampNormal;\n";

					///////////////////////////////////////////////////////////////////////////
				}



				///////////////////////////////////////////////////////////////////////////

				if (prof->getParent()->getDebugLevel())
				{
					outStream << "	outputCol.rg += lodInfo.xy;\n";
				}
			}

			/////////////////////////////////////////////////////////////////////////

			if ( Display::getSingletonPtr()->getFogLevel() != FOL_NONE )
			{
				outStream << "	outputCol.rgb = lerp(outputCol.rgb, fogColour, fogVal);\n";
			}

			/////////////////////////////////////////////////////////////////////////

			if ( prof->isRegionMapEnabled() )
			{
				// 区域显示
				outStream << 
					"   float regionVisible = tex2D(regionMap, uv0).b; \n"
					"   outputCol.rgb = lerp(outputCol.rgb, float3(1,0,0), regionVisible*0.2); \n";
			}

			/////////////////////////////////////////////////////////////////////////

			//outStream << "	return litRes;\n";

			if (tileRender->getMtlType() == TerrainGroundTileRender::MTL_REFRACT)
			{
				outStream << "float da = depth.x / depth.y; \n";
				outStream << "outputCol.r = da; \n";
				outStream << "outputCol.g = da; \n";
				outStream << "outputCol.b = da; \n";
				outStream << "outputCol.a = da; \n";
			}
		}
		else
		{
			outStream << "float da = depth.x / depth.y; \n";
			outStream << "outputCol.r = da; \n";
			outStream << "outputCol.g = da; \n";
			outStream << "outputCol.b = da; \n";
			outStream << "outputCol.a = da; \n";
		}
        // Final return
        outStream << "	return outputCol;\n"
            << "}\n";

    }
    //---------------------------------------------------------------------
    void TerrainMaterialGeneratorA2::SM2Profile::ShaderHelperCg::generateFpDynamicShadowsHelpers(
        const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt, StringUtil::StrStreamType& outStream)
    {
        // TODO make filtering configurable
        outStream <<
            "// Simple PCF \n"
            "// Number of samples in one dimension (square for total samples) \n"
            "#define NUM_SHADOW_SAMPLES_1D 2.0 \n"
            "#define SHADOW_FILTER_SCALE 1 \n"

            "#define SHADOW_SAMPLES NUM_SHADOW_SAMPLES_1D*NUM_SHADOW_SAMPLES_1D \n"

            "float4 offsetSample(float4 uv, float2 offset, float invMapSize) \n"
            "{ \n"
            "	return float4(uv.xy + offset * invMapSize * uv.w, uv.z, uv.w); \n"
            "} \n";

        Bool depthShadow = true;

        
        if ( depthShadow )
        {
            /*outStream << 
                "float calcDepthShadow(sampler2D shadowMap, float4 shadowUV, float inverseShadowmapSize,float fixedDepthBias, float gradientClamp, float gradientScaleBias) \n"
                "{ \n"
                "	float shadow = 1; \n"
                "	shadowUV.xy = shadowUV.xy / shadowUV.w; \n"
                "	float centerdepth = tex2D(shadowMap, shadowUV.xy).x; \n"
                "	float pixeloffset = inverseShadowmapSize; \n"
                "	float4 depths = float4( \n"
                "	    tex2D(shadowMap, shadowUV.xy + float2(-pixeloffset, 0)).x, \n"
                "	    tex2D(shadowMap, shadowUV.xy + float2(+pixeloffset, 0)).x, \n"
                "	    tex2D(shadowMap, shadowUV.xy + float2(0, -pixeloffset)).x, \n"
                "	    tex2D(shadowMap, shadowUV.xy + float2(0, +pixeloffset)).x); \n"
                "   float2 differences = abs( depths.yw - depths.xz ); \n"
                "   float gradient = min(gradientClamp, max(differences.x, differences.y)); \n"
                "   float gradientFactor = gradient * gradientScaleBias; \n"
                "   float depthAdjust = gradientFactor + (fixedDepthBias * centerdepth); \n"
                "   float finalCenterDepth = centerdepth + depthAdjust; \n"
                "   shadow = (finalCenterDepth > shadowUV.z) ? 1 : 0; \n"
                "	return shadow; \n"
                "} \n";*/

            outStream << 
                "float calcDepthShadow(sampler2D shadowMap, float4 shadowUV, float inverseShadowmapSize,float fixedDepthBias, float gradientClamp, float gradientScaleBias) \n"
                "{ \n"
                "	// 4-sample PCF \n"

                "	float shadow = 0.0; \n"
                "	float offset = (NUM_SHADOW_SAMPLES_1D/2 - 0.5) * SHADOW_FILTER_SCALE; \n"
                "	for (float y = -offset; y <= offset; y += SHADOW_FILTER_SCALE) \n"
                "		for (float x = -offset; x <= offset; x += SHADOW_FILTER_SCALE) \n"
                "		{ \n"
                "			float4 newUV = offsetSample(shadowUV, float2(x, y), inverseShadowmapSize);\n"
                "			// manually project and assign derivatives \n"
                "			// to avoid gradient issues inside loops \n"
                "			newUV = newUV / newUV.w; \n"
                "			float depth = tex2Dlod(shadowMap, newUV).x; \n"
                "			if (depth >= 1 || depth >= shadowUV.z)\n"
                "				shadow += 1.0;\n"
                "		} \n"

                "	shadow /= SHADOW_SAMPLES; \n"

                "	return shadow; \n"
                "} \n";
        }
        else
        {
            outStream <<
                "float calcSimpleShadow(sampler2D shadowMap, float4 shadowMapPos) \n"
                "{ \n"
                "	return tex2Dproj(shadowMap, shadowMapPos).x; \n"
                "} \n";

        }
    }
    //---------------------------------------------------------------------
    uint TerrainMaterialGeneratorA2::SM2Profile::ShaderHelperCg::generateVpDynamicShadowsParams(
        uint texCoord, const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt, StringUtil::StrStreamType& outStream)
    {
        // out semantics & params
        uint numTextures = 1;

        outStream <<
            ",out float4 shadowUV : TEXCOORD" << texCoord++ <<"\n";

        outStream <<
            ",uniform float4x4 texViewProj \n";

        //outStream <<
        //    ",uniform float4 shadowDepthRange \n";

        return texCoord;

    }
    //---------------------------------------------------------------------
    void TerrainMaterialGeneratorA2::SM2Profile::ShaderHelperCg::generateVpDynamicShadows(
        const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt, StringUtil::StrStreamType& outStream)
    {
        uint numTextures = 1;

        outStream <<
            " float4 worldPos = mul(worldMatrix, pos); \n";

        // Calculate the position of vertex in light space
        outStream <<
            " shadowUV = mul(texViewProj, worldPos); \n";
        
    }
    //---------------------------------------------------------------------
    void TerrainMaterialGeneratorA2::SM2Profile::ShaderHelperCg::generateFpDynamicShadowsParams(
        uint* texCoord, uint* sampler, const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt, StringUtil::StrStreamType& outStream)
    {
        if (tt == HIGH_LOD)
            mShadowSamplerStartHi = *sampler;
        else if (tt == LOW_LOD)
            mShadowSamplerStartLo = *sampler;

        // in semantics & params
        uint numTextures = 1;
       
        outStream <<
            ", float4 shadowUV : TEXCOORD" << *texCoord << " \n" <<
            ", uniform sampler2D shadowMap : register(s" << *sampler << ") \n";

        outStream <<
            ", uniform float inverseShadowmapSize\n";
        outStream <<
            ", uniform float fixedDepthBias\n";
        outStream <<
            ", uniform float gradientClamp\n";
        outStream <<
            ", uniform float gradientScaleBias\n";
        //outStream <<
        //    ", uniform float shadowFuzzyWidth  \n";
    }
    //---------------------------------------------------------------------
    void TerrainMaterialGeneratorA2::SM2Profile::ShaderHelperCg::generateFpDynamicShadows(
        const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt, StringUtil::StrStreamType& outStream)
    {
        outStream <<
            "	float rtshadow = calcDepthShadow( shadowMap, shadowUV, inverseShadowmapSize, fixedDepthBias, gradientClamp, gradientScaleBias );";

        outStream << 
            "	shadow = min(shadow, rtshadow);\n";

    }
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    HighLevelGpuProgramPtr
        TerrainMaterialGeneratorA2::SM2Profile::ShaderHelperHLSL::createVertexProgram(
        const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt)
    {
        HighLevelGpuProgramManager& mgr = HighLevelGpuProgramManager::getSingleton();
        String progName = getVertexProgramName(prof, tileRender, tt);

        HighLevelGpuProgramPtr ret = mgr.getByName(progName);
        if (ret.isNull())
        {
            ret = mgr.createProgram(progName, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
                "hlsl", GPT_VERTEX_PROGRAM);
        }
        else
        {
            ret->unload();
        }

        if (prof->_isSM3Available())
            ret->setParameter("target", "vs_3_0");
        else
            ret->setParameter("target", "vs_2_0");
        ret->setParameter("entry_point", "main_vp");

        return ret;

    }
    //---------------------------------------------------------------------
    HighLevelGpuProgramPtr
        TerrainMaterialGeneratorA2::SM2Profile::ShaderHelperHLSL::createFragmentProgram(
        const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt)
    {
        HighLevelGpuProgramManager& mgr = HighLevelGpuProgramManager::getSingleton();
        String progName = getFragmentProgramName(prof, tileRender, tt);


        HighLevelGpuProgramPtr ret = mgr.getByName(progName);
        if (ret.isNull())
        {
            ret = mgr.createProgram(progName, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
                "hlsl", GPT_FRAGMENT_PROGRAM);
        }
        else
        {
            ret->unload();
        }

        if (prof->_isSM3Available())
            ret->setParameter("target", "ps_3_0");
        else
            ret->setParameter("target", "ps_2_x");
        ret->setParameter("entry_point", "main_fp");

        return ret;

    }
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    HighLevelGpuProgramPtr
        TerrainMaterialGeneratorA2::SM2Profile::ShaderHelperGLSL::createVertexProgram(
        const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt)
    {
        HighLevelGpuProgramManager& mgr = HighLevelGpuProgramManager::getSingleton();
        String progName = getVertexProgramName(prof, tileRender, tt);

        switch(tt)
        {
        case HIGH_LOD:
            progName += "/hlod";
            break;
        case LOW_LOD:
            progName += "/llod";
            break;
        }

        HighLevelGpuProgramPtr ret = mgr.getByName(progName);
        if (ret.isNull())
        {
            ret = mgr.createProgram(progName, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
                "glsl", GPT_VERTEX_PROGRAM);
        }
        else
        {
            ret->unload();
        }

        return ret;

    }
    //---------------------------------------------------------------------
    HighLevelGpuProgramPtr
        TerrainMaterialGeneratorA2::SM2Profile::ShaderHelperGLSL::createFragmentProgram(
        const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt)
    {
        HighLevelGpuProgramManager& mgr = HighLevelGpuProgramManager::getSingleton();
        String progName = getFragmentProgramName(prof, tileRender, tt);

        HighLevelGpuProgramPtr ret = mgr.getByName(progName);
        if (ret.isNull())
        {
            ret = mgr.createProgram(progName, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
                "glsl", GPT_FRAGMENT_PROGRAM);
        }
        else
        {
            ret->unload();
        }

        return ret;

    }

}