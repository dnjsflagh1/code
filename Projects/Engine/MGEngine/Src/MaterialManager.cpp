/******************************************************************************/
#include "stdafx.h"
#include "MaterialManager.h"
#include "ResourceManager.h"
#include "Display.h"
#include "Scene.h"
/******************************************************************************/

namespace MG
{
    ///******************************************************************************/
    ////MaterialObject
    ///******************************************************************************/
    MaterialDynamicParamsObject::MaterialDynamicParamsObject()
    {

    }
    //-----------------------------------------------------------------------
    MaterialDynamicParamsObject::~MaterialDynamicParamsObject()
    {
        clearDynamicParams();
    }
    //-----------------------------------------------------------------------
    void MaterialDynamicParamsObject::addDynamicParams( MaterialDeclaration* mat_decl, U32 subEntityIndex )
    {
        //////////////////////////////////////////////////////////

        if ( mat_decl->effectGrassID > 0 )
        {
            GrassEffectResourceDeclaration* grass_decl = ResourceManager::getSingleton().getGrassEffectResourceDeclaration( 2 /*mat_decl->effectGrassID*/ );
            if ( grass_decl )
            {

                GrassEffectDynamicParams* grassParams = NULL;
                std::map<U32, GrassEffectDynamicParams*>::iterator iter = grassEffectParamList.find( subEntityIndex );
                if ( iter != grassEffectParamList.end() )
                {
                    grassParams = iter->second;
                }else
                {
                    grassParams = MG_NEW GrassEffectDynamicParams;
                }

                grassParams->avaliable = true;
                grassParams->xinc = grass_decl->grassSwingVelocity.x * Ogre::Math::PI;
                grassParams->zinc = grass_decl->grassSwingVelocity.y * Ogre::Math::PI;
                grassParams->custom.w = grass_decl->grassSwingFactor;
                grassParams->custom.y = params.boundingSize.y;
                grassParams->custom.x = 0.0f;
                grassParams->custom.z = 0.0f;

                grassParams->xpos = Ogre::Math::RangeRandom(-Math::PI, Math::PI);
                grassParams->zpos = Ogre::Math::RangeRandom(-Math::PI, Math::PI);

                grassEffectParamList[subEntityIndex] = grassParams;
            }
        }

        ////////////////////////////////////////////////////////////////////////


        if ( mat_decl->effectWaterID > 0 )
        {
            WaterEffectResourceDeclaration* water_decl = ResourceManager::getSingleton().getWaterEffectResourceDeclaration( mat_decl->effectWaterID );
            if ( water_decl )
            {
                WaterEffectDynamicParams* waterParams = NULL;
                std::map<U32, WaterEffectDynamicParams*>::iterator iter = waterEffectParamList.find( subEntityIndex );
                if ( iter != waterEffectParamList.end() )
                {
                    waterParams = iter->second;
                }else
                {
                    waterParams = MG_NEW WaterEffectDynamicParams;
                }

                ///////////////////////////////////////////////////////////
                //TODO:

                
                ///////////////////////////////////////////////////////////

                waterEffectParamList[subEntityIndex] = waterParams;
            }
        }
    }

    //-----------------------------------------------------------------------
    void MaterialDynamicParamsObject::clearDynamicParams()
    {
        std::map<U32, WaterEffectDynamicParams*>::iterator iter_water = waterEffectParamList.begin();
        for ( ; iter_water != waterEffectParamList.end(); iter_water++ )
        {
            MG_DELETE( iter_water->second );
        }

        std::map<U32, GrassEffectDynamicParams*>::iterator iter_grass = grassEffectParamList.begin();
        for ( ; iter_grass != grassEffectParamList.end(); iter_grass++ )
        {
            MG_DELETE( iter_grass->second );
        }

        waterEffectParamList.clear();
        grassEffectParamList.clear();
    }
    
    /******************************************************************************/
    //MaterialManager
    /******************************************************************************/
	//-----------------------------------------------------------------------
	MaterialManager::MaterialManager()
	{
		mSerializer = MG_NEW MaterialSerializer();
	}
	//-----------------------------------------------------------------------
	MaterialManager::~MaterialManager()
	{
		MG_DELETE(mSerializer);
	}
	//-----------------------------------------------------------------------
	Bool MaterialManager::praseScript(std::vector<std::wstring>& stringVector, MaterialDeclaration* mat_decl)
	{
		if ( !mSerializer )
			return false;

		return mSerializer->parseScript(stringVector, mat_decl);
	}

    //-----------------------------------------------------------------------
    void MaterialManager::updateMaterialGroupDynamicParameter( Flt delta, MaterialDynamicParamsObject& object )
    {   
        updatePlantMaterialGroupDynamicParameter(delta,object);
    }
    //-----------------------------------------------------------------------
    void MaterialManager::updateMaterialElementDynamicParameter( Flt delta, MaterialDynamicParamsObject& object, Vec3 center )
    {   
        updatePlantMaterialElementDynamicParameter(delta,object,center);
    }
    //-----------------------------------------------------------------------
    void MaterialManager::applyMaterialDynamicParameter( MaterialDynamicParamsObject& object, Renderable* renderable, U32 subEntityIndex/* = 0 */)
    {
        applyGrassEffectDynamicParameter(object,renderable, subEntityIndex);
    }
        
    //-----------------------------------------------------------------------
    void MaterialManager::updatePlantMaterialGroupDynamicParameter( Flt delta, MaterialDynamicParamsObject& object )
    {
        //object.xpos += object.xinc * delta;
        //object.zpos += object.zinc * delta;
		std::map<U32, GrassEffectDynamicParams*>::iterator iter = object.grassEffectParamList.begin();
		if ( iter != object.grassEffectParamList.end() )
		{
			GrassEffectDynamicParams* params = iter->second;
			if ( params )
			{
				params->xpos += params->xinc * delta;
				params->zpos += params->zinc * delta;
			}
		}
    }
    //-----------------------------------------------------------------------
    void MaterialManager::updatePlantMaterialElementDynamicParameter( Flt delta, MaterialDynamicParamsObject& object, Vec3 center )
    {
        // a little randomness
		std::map<U32, GrassEffectDynamicParams*>::iterator iter = object.grassEffectParamList.begin();
		if ( iter != object.grassEffectParamList.end() )
		{
			GrassEffectDynamicParams* params = iter->second;
			if ( params )
			{
				params->xpos += center.x * 0.001;
				params->zpos += center.z * 0.001; 
				params->custom.x = Math::Sin(params->xpos) * 0.25;
				params->custom.z = Math::Sin(params->zpos) * 0.25;
			}
		}
    }
    //-----------------------------------------------------------------------
    void MaterialManager::applyGrassEffectDynamicParameter( MaterialDynamicParamsObject& object, Renderable* renderable, U32 subEntityIndex/* = 0 */)
    {
		std::map<U32, GrassEffectDynamicParams*>::iterator iter_grass = object.grassEffectParamList.find( subEntityIndex );
		if ( iter_grass != object.grassEffectParamList.end() )
		{
			GrassEffectDynamicParams* params = iter_grass->second;

			if ( params && params->avaliable )
			{
				renderable->setCustomParameter(999, params->custom);
				return;
			}
		}
    }
	//-----------------------------------------------------------------------
	MaterialDeclaration* MaterialManager::getMaterialDeclaration(Str materialGroup, U32 index)
	{
		return ResourceManager::getSingleton().getMaterialDeclaration(materialGroup, index);
	}
    //-----------------------------------------------------------------------
    Ogre::MaterialPtr MaterialManager::createOrRetriveMaterial(MG::Scene* scene, Str materialGroup, U32 index, MaterialUserParams params)
    {
        MaterialDeclaration* mat_decls = MG::ResourceManager::getSingleton().getMaterialDeclaration(materialGroup, index);

        return createOrRetriveMaterial( scene, mat_decls, params );
    }

    //-----------------------------------------------------------------------
    Ogre::MaterialPtr MaterialManager::createOrRetriveMaterial(MG::Scene* scene, MaterialDeclaration* decl, MaterialUserParams params)
    {
        MaterialPtr instance_mat;

		///////////////////////////////////////////////////////////////////////////////////////////////////////

        if ( !decl	|| 
            decl->materialTemplateName.empty() )
        {
            return instance_mat;
        }

        Str materialResourceGroupName = decl->texturePath;

        if ( !Ogre::ResourceGroupManager::getSingleton().resourceGroupExists( materialResourceGroupName ) )
        {
            return instance_mat;
        }

        ///////////////////////////////////////////////////////////////////////////////////////////////////////

        MaterialRenderParams renderParams;

        // 得到模版材质
        Ogre::MaterialPtr templateMaterial = getTemplateMaterial( decl, params, renderParams );
        if ( templateMaterial.isNull() )
        {
            DYNAMIC_EEXCEPT_LOG("mat is null");
            DYNAMIC_ASSERT(false);
            return instance_mat;
        }

        // 自己的材质名
        Str insMaterialName = decl->materialTemplateName + "_copy_" + params.suffixName;

        // 是否已经初始化了该材质
        instance_mat = Ogre::MaterialManager::getSingleton().getByName( insMaterialName, materialResourceGroupName);

        // 如果没有初始化， 复制材质
        if (instance_mat.isNull() )
        {
            instance_mat = templateMaterial->clone( insMaterialName, true, materialResourceGroupName );
        }else
        {
            templateMaterial->copyDetailsTo( instance_mat );
        }
        
        ///////////////////////////////////////////////////////////////////////////////////////////////////////

        // 应用配置
        applyMaterial( scene, decl, instance_mat, params, renderParams );
        
        ///////////////////////////////////////////////////////////////////////////////////////////////////////

		bindCommonShadowCasterMaterial( scene, instance_mat, decl, params, renderParams );

		///////////////////////////////////////////////////////////////////////////////////////////////////////

        return instance_mat;
    }

    //-----------------------------------------------------------------------
    Ogre::MaterialPtr MaterialManager::createOrRetriveWaterMaterial(MG::Scene* scene, U32 waterMatID, MaterialUserParams params)
    {
        MaterialPtr instance_mat;

        ///////////////////////////////////////////////////////////////////////////////////////////////////////

        MaterialRenderParams renderParams;

        // 得到模版材质
        WaterEffectResourceDeclaration* waterDecl = MG::ResourceManager::getSingleton().getWaterEffectResourceDeclaration(waterMatID);
        Ogre::MaterialPtr templateMaterial = getWaterTemplateMaterial( waterDecl, renderParams );

        // 自己的材质名
        Str insMaterialName = templateMaterial->getName() + "_copy_" + params.suffixName;

        // 是否已经初始化了该材质
        instance_mat = Ogre::MaterialManager::getSingleton().getByName( insMaterialName , Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME );

        // 如果没有初始化， 复制材质
        if (instance_mat.isNull() )
        {
            instance_mat = templateMaterial->clone( insMaterialName, true, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME );
        }else
        {
            templateMaterial->copyDetailsTo( instance_mat );
        }

        ///////////////////////////////////////////////////////////////////////////////////////////////////////

        // 应用配置
        
        Technique*	ins_tech = NULL;
        Pass*		ins_pass = NULL;
        if ( ins_tech = instance_mat->getTechnique(0) )
        {
            ins_pass = instance_mat->getTechnique(0)->getPass(0);
        }

		if ( waterDecl->waterEffectUsage == WATER_EFFECT_USAGE_LAKE )
		{
			applyLakeMaterial( scene, waterDecl, ins_pass, renderParams );
		}else
		if ( waterDecl->waterEffectUsage == WATER_EFFECT_USAGE_WATER )
		{
			applyWaterMaterial( scene, waterDecl, ins_pass, renderParams );
		}else
		if ( waterDecl->waterEffectUsage == WATER_EFFECT_USAGE_SEA )
		{
			applySeaMaterial( scene, waterDecl, ins_pass, renderParams );
		}

        ///////////////////////////////////////////////////////////////////////////////////////////////////////

        return instance_mat;
    }

    //-----------------------------------------------------------------------
    Ogre::MaterialPtr MaterialManager::createOrRetriveWaterMaterial(MG::Scene* scene, WaterEffectResourceDeclaration* decl, MaterialUserParams params)
    {
        MaterialPtr instance_mat;


        return instance_mat;
    }

    //-----------------------------------------------------------------------
    void MaterialManager::bindCommonShadowCasterMaterial( MG::Scene* scene, Ogre::MaterialPtr mat, MaterialDeclaration* decl, MaterialUserParams& params, MaterialRenderParams& renderParams )
    {
        if ( mat.isNull() == false )
        {
            Technique* tec = mat->getTechnique(0);

            Bool isPSSM = scene->getShadowManager()->isUsePSSM();
            ShadowType st = Display::getSingleton().getShadowType();

            if ( tec )
            {
                Pass* pass = tec->getPass(0);

                if ( pass )
                {
					Bool isAlpha = mat->isTransparent();

					if ( pass->getAlphaRejectFunction() != CMPF_ALWAYS_PASS )
						isAlpha = true;

                    if ( params.isBatch )
                    {
                        // 批次物件
                        if ( isPSSM )
                        {
                            if ( renderParams.isSkeleton )
                            {
                                tec->setShadowCasterMaterial( "MG/PSSM/EntityGroup/Skeleton/DepthShadow/Caster" );
                            }else
                            {
                                tec->setShadowCasterMaterial( "MG/PSSM/EntityGroup/DepthShadow/Caster" );
                            }
                        }else
                        {
                            if ( renderParams.isSkeleton )
                            {
                                tec->setShadowCasterMaterial( "MG/USM/EntityGroup/Skeleton/DepthShadow/Caster" );
                            }else
                            {
                                tec->setShadowCasterMaterial( "MG/USM/EntityGroup/DepthShadow/Caster" );
                            }
                        }
                    }else
                    {
                        // 单物件
                        if ( !isAlpha )
                        {
                            // 不带透明材质
                            if ( isPSSM )
                            {
                                tec->setShadowCasterMaterial( "MG/PSSM/Entity/DepthShadow/Caster" );
                            }else
                            {
                                tec->setShadowCasterMaterial( "MG/USM/Entity/DepthShadow/Caster" );
                            }
                        }else
                        {
                            // 带透明材质
                            Ogre::MaterialPtr template_mat;
                            if ( isPSSM )
                            {
                                template_mat = Ogre::MaterialManager::getSingleton().getByName("MG/PSSM/Entity/DepthShadow/Caster/Alpha");
                            }else
                            {
                                template_mat = Ogre::MaterialManager::getSingleton().getByName("MG/USM/Entity/DepthShadow/Caster/Alpha");
                            }

                            // 复制材质
                            Str casterName = mat->getName() + "_ShadowCasterAlpha";
                            Ogre::MaterialPtr bind_mat      = Ogre::MaterialManager::getSingleton().getByName(casterName);
                            if (bind_mat.isNull() )
                            {
                                //bind_mat = template_mat->clone( casterName, true, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME );
								bind_mat = template_mat->clone( casterName, true, mat->getGroup() );

                            }else
                            {
                                template_mat->copyDetailsTo( bind_mat );
                            }

                            Technique* bind_tec = bind_mat->getTechnique(0);

                            if ( bind_tec )
                            {
                                Pass* bind_pass = bind_tec->getPass( 0 );

                                if ( bind_pass )
                                {
                                    // 设置贴图
                                    bind_pass->getTextureUnitState("diffuse")->setTextureName( decl->diffuseTextureName );
									bind_pass->getTextureUnitState("diffuse")->setTextureAddressingMode(TextureUnitState::TAM_WRAP);

                                    ////////////////////////////////////////////////////////////////////////////////////////////

                                    if ( !decl->isIgnoreBlendType )
                                    {
                                        bind_pass->setSceneBlending((SceneBlendType)decl->sceneBlendType);
                                    }
                                    else
                                    {
                                        // set sceneBlending
                                        bind_pass->setSceneBlending((SceneBlendFactor)decl->sceneBlendFactorSrc,(SceneBlendFactor)decl->sceneBlendFactorDest);
                                    }

                                    ////////////////////////////////////////////////////////////////////////////////////////////

                                    // set alphaReject
                                    bind_pass->setAlphaRejectSettings((CompareFunction)decl->alphaRejectionCmpFunc, decl->alphaRejectionValue);

                                    ////////////////////////////////////////////////////////////////////////////////////////////

                                    // set cullingMode
                                    bind_pass->setCullingMode( (CullingMode)decl->cullingHardWare );
                                }
                            }

                            tec->setShadowCasterMaterial( bind_mat );
                        }
                    }
                }
            }
        }
    }

    //-----------------------------------------------------------------------
    Ogre::MaterialPtr MaterialManager::getTemplateMaterial(MaterialDeclaration* decl, MaterialUserParams& params, MaterialRenderParams& renderParams)
    {
        MaterialPtr template_mat;

        //////////////////////////////////////////////////////////////////////////

        renderParams.isBatch    = params.isBatch;
        renderParams.isSkeleton = params.hasSkeleton;
        
        //////////////////////////////////////////////////////////////////////////

        if ( params.isCasterShadow )
            renderParams.shadowCasterType   = Display::getSingleton().getShadowType();
        else
            renderParams.shadowCasterType   = SCL_NONE;

        //////////////////////////////////////////////////////////////////////////

        if ( !decl->normalTextureName.empty() )
        {
            if ( renderParams.isBatch )
            {
                renderParams.isUseNormal        = Display::getSingleton().getEntityGroupNormalMapEnable();
            }else
            {
                renderParams.isUseNormal        = Display::getSingleton().getEntityNormalMapEnable();
            }
        }
        else
            renderParams.isUseNormal    = false;

        //////////////////////////////////////////////////////////////////////////

        if ( !decl->aoTextureName.empty() )
        {
            if ( renderParams.isBatch )
            {
                renderParams.isUseSa    = Display::getSingleton().getEntityGroupSaMapEnable();
            }else
            {
                renderParams.isUseSa    = Display::getSingleton().getEntitySaMapEnable();
            }
        }
        else
            renderParams.isUseSa            = false;

        //////////////////////////////////////////////////////////////////////////

        if ( params.isStaticShadowReceive )
            renderParams.isUseLightingMap   = Display::getSingleton().getEntityLightingMapEnable();
        else
            renderParams.isUseLightingMap   = false;

        //////////////////////////////////////////////////////////////////////////

        if ( params.isDynamiShadowcReceive )
            renderParams.shadowReceiveType  = Display::getSingleton().getShadowType();
        else
            renderParams.shadowReceiveType  = SCL_NONE;

        //////////////////////////////////////////////////////////////////////////

        if ( decl->hasGrassEffect() )
        {
            GrassEffectResourceDeclaration* grassDecl = MG::ResourceManager::getSingleton().getGrassEffectResourceDeclaration(decl->effectGrassID);
            template_mat = getPlantTemplateMaterial(grassDecl,renderParams);
        }else
        if ( decl->hasWaterEffect() )
        {
            WaterEffectResourceDeclaration* waterDecl = MG::ResourceManager::getSingleton().getWaterEffectResourceDeclaration(decl->effectWaterID);
            template_mat = getWaterTemplateMaterial(waterDecl,renderParams);
        }else
        {
            template_mat = getEntityTemplateMaterial(decl,renderParams);
        }
		
        return template_mat;
    }   

    //-----------------------------------------------------------------------
    Ogre::MaterialPtr MaterialManager::getEntityTemplateMaterial(MaterialDeclaration* decl, MaterialRenderParams& params)
    {
        MaterialPtr template_mat;

        //////////////////////////////////////////////////////////////////////////////
        
        // 非批次处理
        if (params.isBatch==false)
        {
            if ( params.isUseNormal && params.isUseSa && (params.shadowReceiveType!=SCL_NONE) )
            {
                template_mat = Ogre::MaterialManager::getSingleton().getByName("MG/CloseRange/Entity/Diffuse/Normal/Specular/AO/Shadow");
            }else
            if ( params.isUseNormal && params.isUseSa )
            {
                template_mat = Ogre::MaterialManager::getSingleton().getByName("MG/CloseRange/Entity/Diffuse/Normal/Specular/AO");
            }else
            if ( params.isUseNormal )
            {
                template_mat = Ogre::MaterialManager::getSingleton().getByName("MG/CloseRange/Entity/Diffuse/Normal");
            }else
            if ( params.shadowReceiveType!=SCL_NONE )    
            {
				if (params.isHasOutline)
				{
					template_mat = Ogre::MaterialManager::getSingleton().getByName("MG/CloseRange/Entity/Diffuse/Shadow/OutLine");
				}
				else
				{
					template_mat = Ogre::MaterialManager::getSingleton().getByName("MG/CloseRange/Entity/Diffuse/Shadow");
				} 
            }else
            {
				if (params.isHasOutline)
				{
					template_mat = Ogre::MaterialManager::getSingleton().getByName("MG/CloseRange/Entity/Diffuse/OutLine");
				}
				else
				{
					template_mat = Ogre::MaterialManager::getSingleton().getByName("MG/CloseRange/Entity/Diffuse");
				}
            }
        }else
        // 批次处理
        {
            //params.isUseNormal = false;
            //params.isUseSa = false;
            params.shadowReceiveType = SCL_NONE;

            // 带骨骼批次处理
            if ( params.isSkeleton )
            {
                //if ( params.isUseNormal && params.isUseSa && params.shadowReceiveType == SCL_PSSM_DEPTH_TEXTURE )
                //{
                //    template_mat = Ogre::MaterialManager::getSingleton().getByName("MG/CloseRange/EntityGroup/Skeleton/Diffuse/Shadow");
                //}else
                //if ( params.isUseNormal && params.isUseSa )
                //{
                //    template_mat = Ogre::MaterialManager::getSingleton().getByName("MG/CloseRange/EntityGroup/Skeleton/Diffuse/Normal/Specular/AO");
                //}else
                //if ( params.isUseNormal )
                //{
                //    template_mat = Ogre::MaterialManager::getSingleton().getByName("MG/CloseRange/EntityGroup/Skeleton/Diffuse/Normal");
                //}else
                {
                    template_mat = Ogre::MaterialManager::getSingleton().getByName("MG/CloseRange/EntityGroup/Skeleton/Diffuse");
                }
            }else
            // 不带骨骼批次处理
            {
                //if ( params.isUseNormal && params.isUseSa && params.shadowReceiveType == SCL_PSSM_DEPTH_TEXTURE )
                //{
                //    template_mat = Ogre::MaterialManager::getSingleton().getByName("MG/EntityGroup/Diffuse/Shadow");
                //}else
                //if ( params.isUseNormal && params.isUseSa )
                //{
                //    template_mat = Ogre::MaterialManager::getSingleton().getByName("MG/CloseRange/EntityGroup/Diffuse/Normal/Specular/AO");
                //}else
                //if ( params.isUseNormal )
                //{
                //    template_mat = Ogre::MaterialManager::getSingleton().getByName("MG/CloseRange/EntityGroup/Diffuse/Normal");
                //}else
                {
                    template_mat = Ogre::MaterialManager::getSingleton().getByName("MG/CloseRange/EntityGroup/Diffuse");
                }
            }
        }

        //////////////////////////////////////////////////////////////////////////////

       
        return template_mat;
    }

    //-----------------------------------------------------------------------
    Ogre::MaterialPtr MaterialManager::getPlantTemplateMaterial(GrassEffectResourceDeclaration* decl, MaterialRenderParams& params)
    {
        MaterialPtr template_mat;

        //////////////////////////////////////////////////////////////////////////////

        template_mat = Ogre::MaterialManager::getSingleton().getByName("MG/Plant/Diffuse");
        
        //////////////////////////////////////////////////////////////////////////////
        
        return template_mat;
    }
    
    //-----------------------------------------------------------------------
    Ogre::MaterialPtr MaterialManager::getWaterTemplateMaterial(WaterEffectResourceDeclaration* decl, MaterialRenderParams& params)
    {
        
        MaterialPtr template_mat;

		Bool sceneShadow = Display::getSingleton().getShadowType() != SCL_NONE ;

        //////////////////////////////////////////////////////////////////////////////

		if ( decl->waterEffectUsage == WATER_EFFECT_USAGE_LAKE )
		{
            if ( Display::getSingleton().getWaterReflectionEnabled() )
            {
                if ( sceneShadow && 
                    Display::getSingleton().getTerrainLightmapEnabled() && 
                    Display::getSingleton().getTerrainReceiveDynamicShadowsEnabled() )
                {
                    if ( Display::getSingleton().getWaterDepthCheckEnabled() )
                    {
                        if ( Display::getSingleton().getWaterRefractionEnabled() )
                        {
                            template_mat = Ogre::MaterialManager::getSingleton().getByName("MG/Reflection/Shadow/AlphaDepthCheck/Refraction/Lake");
                        }else
                        {
                            template_mat = Ogre::MaterialManager::getSingleton().getByName("MG/Reflection/Shadow/AlphaDepthCheck/Lake");
                        }
                    }else
                    {
                        template_mat = Ogre::MaterialManager::getSingleton().getByName("MG/Reflection/Shadow/Lake");
                    }
                }else
                {
                    template_mat = Ogre::MaterialManager::getSingleton().getByName("MG/Reflection/Lake");
                }
            }else
            {
                template_mat = Ogre::MaterialManager::getSingleton().getByName("MG/Lake");
            }
		}else
		if ( decl->waterEffectUsage == WATER_EFFECT_USAGE_WATER )
		{
			template_mat = Ogre::MaterialManager::getSingleton().getByName("MG/Water");
		}else
		if ( decl->waterEffectUsage == WATER_EFFECT_USAGE_SEA )
		{
			if (	sceneShadow && 
				Display::getSingleton().getTerrainLightmapEnabled() && 
				Display::getSingleton().getTerrainReceiveDynamicShadowsEnabled() )
			{
				//if ( Display::getSingleton().getWaterRefractionEnabled() )
				//{
				//	if (decl->waterDynamicNormal == 0)
				//	{
				//		template_mat = Ogre::MaterialManager::getSingleton().getByName("MG/Shadow/Reflection/Refraction/Sea");
				//	}
				//	else
				//	{
				//		template_mat = Ogre::MaterialManager::getSingleton().getByName("MG/Shadow/NormalAnimation/Reflection/Refraction/Sea");
				//	}
				//}else
				//{
				//	if (decl->waterDynamicNormal == 0)
				//	{
				//		template_mat = Ogre::MaterialManager::getSingleton().getByName("MG/Shadow/Reflection/Sea");
				//	}
				//	else
				//	{
				//		template_mat = Ogre::MaterialManager::getSingleton().getByName("MG/Shadow/NormalAnimation/Reflection/Sea");
				//	}
				//}
			}else
			{
				//if (decl->waterDynamicNormal == 0)
				//{
				//	template_mat = Ogre::MaterialManager::getSingleton().getByName("MG/Reflection/Sea");
				//}
				//else
				//{
				//	template_mat = Ogre::MaterialManager::getSingleton().getByName("MG/NormalAnimation/Reflection/Sea");
				//}
			}
		}
     
        //////////////////////////////////////////////////////////////////////////////

        return template_mat;
    }


    //-----------------------------------------------------------------------
    Ogre::MaterialPtr MaterialManager::applyMaterial(MG::Scene* scene, MaterialDeclaration* decl, Ogre::MaterialPtr applyMat, MaterialUserParams& params, MaterialRenderParams& renderParams)
    {
		if ( !applyMat.isNull() )
		{
			Technique*	ins_tech = NULL;
			Pass*		ins_pass = NULL;

			if ( ins_tech = applyMat->getTechnique(0) )
			{
				UInt uPass = applyMat->getTechnique(0)->getNumPasses();
				if (uPass > 1)
				{
					int a = 0;
					a++;
				}
				for (UInt i = 0; i < uPass; ++i)
				{
					ins_pass = applyMat->getTechnique(0)->getPass(i);

					if ( !ins_pass )
						return applyMat;


					////////////////////////////////////////////////////////////////////////////////////////////

					GpuProgramPtr vertexProgram     = ins_pass->getVertexProgram();
					GpuProgramPtr fragmentProgram   = ins_pass->getFragmentProgram();

					////////////////////////////////////////////////////////////////////////////////////////////

					// set diffuse tex
					if ( !decl->diffuseTextureName.empty() )
					{
						TextureUnitState* pTextureUnit = ins_pass->getTextureUnitState("diffuse");
						if (pTextureUnit != NULL)
						{
							pTextureUnit->setTextureName(decl->diffuseTextureName);
						}
						
						//ins_pass->getTextureUnitState("diffuse")->setTextureAddressingMode(TextureUnitState::TAM_MIRROR);
					}

					////////////////////////////////////////////////////////////////////////////////////////////

					// set normal tex
					if ( renderParams.isUseNormal && !decl->normalTextureName.empty() && ins_pass->getTextureUnitState("normal") )
					{
						TextureUnitState* pTextureUnit = ins_pass->getTextureUnitState("normal");
						if (pTextureUnit != NULL)
						{
							pTextureUnit->setTextureName(decl->normalTextureName);
						}
						
						//ins_pass->getTextureUnitState("normal")->setTextureAddressingMode(TextureUnitState::TAM_MIRROR);

						// set sa tex
						if ( renderParams.isUseSa && !decl->aoTextureName.empty() && ins_pass->getTextureUnitState("sa") )
						{
							TextureUnitState* pTextureUnit = ins_pass->getTextureUnitState("sa");
							if (pTextureUnit != NULL)
							{
								pTextureUnit->setTextureName(decl->aoTextureName);
							}
							//ins_pass->getTextureUnitState("sa")->setTextureAddressingMode(TextureUnitState::TAM_MIRROR);
						}
					}

					////////////////////////////////////////////////////////////////////////////////////////////

					if ( !decl->isIgnoreBlendType )
					{
						ins_pass->setSceneBlending((SceneBlendType)decl->sceneBlendType);
					}
					else
					{
						// set sceneBlending
						ins_pass->setSceneBlending((SceneBlendFactor)decl->sceneBlendFactorSrc,(SceneBlendFactor)decl->sceneBlendFactorDest);
					}

					////////////////////////////////////////////////////////////////////////////////////////////

					// set alphaReject
					ins_pass->setAlphaRejectSettings((CompareFunction)decl->alphaRejectionCmpFunc, decl->alphaRejectionValue);

					////////////////////////////////////////////////////////////////////////////////////////////

					// set cullingMode
					ins_pass->setCullingMode( (CullingMode)decl->cullingHardWare );

					////////////////////////////////////////////////////////////////////////////////////////////

					// set shadow
					applyMat->setReceiveShadows( renderParams.shadowReceiveType != SCL_NONE );

					////////////////////////////////////////////////////////////////////////////////////////////

					// set texture UV animation

					////////////////////////////////////////////////////////////////////////////////////////////

					if (params.isOpenGlow)
					{
						applyMat->setShininess( 0.4f );
					}
					else
					{
						applyMat->setShininess( params.shiness );
					}

					ins_pass->setAmbient(ColourValue(0.558,0.558,0.558,1));
					ins_pass->setDiffuse(ColourValue(0.0,0.0,0.0,1));
					applyMat->setSelfIllumination( params.emissive );
					////////////////////////////////////////////////////////////////////////

					

					////////////////////////////////////////////////////////////////////////

					if ( decl->hasGrassEffect() )
					{
						GrassEffectResourceDeclaration* grassDecl = MG::ResourceManager::getSingleton().getGrassEffectResourceDeclaration(decl->effectGrassID);

						applyPlantMaterial( scene, grassDecl, ins_pass, renderParams );
					}else
						if ( decl->hasWaterEffect() )
						{
							WaterEffectResourceDeclaration* waterDecl = MG::ResourceManager::getSingleton().getWaterEffectResourceDeclaration(decl->effectWaterID);

							applyWaterMaterial( scene, waterDecl, ins_pass, renderParams );
						}else
						{
							applyUVMaterial( scene, decl, ins_pass, renderParams );
							applyShadowMaterial( scene ,decl, ins_pass, renderParams );
						}
				}

				//return applyMat;
			}
		}
		return applyMat;
    }

    //-----------------------------------------------------------------------
    void MaterialManager::applyUVMaterial(MG::Scene* scene, MaterialDeclaration* decl, Pass* ins_pass, MaterialRenderParams& renderParams)
    {

        /*if (  decl->textureScale.x != 1.0f || decl->textureScale.y != 1.0f ||
            decl->textureScroll.x != 0.0f || decl->textureScroll.y != 0.0f ||
            decl->textureScrollAnimation.x != 0.0f || decl->textureScrollAnimation.y != 0.0f ||
            decl->textureRotate != 0.0f || decl->textureRotateAnimation != 0.0f 
            )
        {
            Str8 vertex_program_name;
            ins_pass->setVertexProgram(vertex_program_name);

            int countTexUnit = ins_pass->getNumTextureUnitStates();
            for ( int i = 0; i < countTexUnit; i++ )
            {
                TextureUnitState* texUnitPtr = ins_pass->getTextureUnitState(i);

                if ( !texUnitPtr )
                    continue;

                texUnitPtr->setTextureScale( decl->textureScale.x, decl->textureScale.y );

                texUnitPtr->setTextureScroll( decl->textureScroll.x, decl->textureScroll.y );
                texUnitPtr->setScrollAnimation( decl->textureScrollAnimation.x, decl->textureScrollAnimation.y );

                Degree rotate_degree;
                rotate_degree = decl->textureRotate;
                texUnitPtr->setTextureRotate( Radian(rotate_degree.valueRadians()) );

                rotate_degree = decl->textureRotateAnimation;
                texUnitPtr->setRotateAnimation( rotate_degree.valueRadians() );
            }
        }*/
    }

    //-----------------------------------------------------------------------
    void MaterialManager::applyShadowMaterial(MG::Scene* scene, MaterialDeclaration* decl, Pass* ins_pass, MaterialRenderParams& renderParams)
    {
		if ( !renderParams.isUseNormal )
			return;
		if ( !renderParams.isUseSa )
			return;

        if ( renderParams.shadowReceiveType != SCL_NONE )
        {
            //if ( renderParams.shadowReceiveType == SCL_PSSM_DEPTH_TEXTURE )
            //{
            //    PSSMShadowCameraSetup* pssmCam = scene->getShadowManager()->getActiveShadowMaker()->getPSSMShadowCameraSetup();
            //    if ( pssmCam )
            //    {
            //        if ( ins_pass )
            //        {
            //            GpuProgramParametersSharedPtr gp = ins_pass->getFragmentProgramParameters();
            //            if ( gp.isNull() == false )
            //            {
            //                Vector4 splitPoints;
            //                const PSSMShadowCameraSetup::SplitPointList& splitPointList = pssmCam->getSplitPoints();
            //                for (int i = 0; i < 3; ++i)
            //                {
            //                    splitPoints[i] = splitPointList[i];
            //                }
            //                gp->setNamedConstant("pssmSplitPoints", splitPoints);
            //            }
            //        }
            //    }
            //}




        }
    }

    //-----------------------------------------------------------------------
    void MaterialManager::applyPlantMaterial(MG::Scene* scene, GrassEffectResourceDeclaration* decl, Pass* ins_pass, MaterialRenderParams& renderParams)
    {
        
    }

	//-----------------------------------------------------------------------
	void MaterialManager::applyLakeMaterial(MG::Scene* scene, WaterEffectResourceDeclaration* decl, Pass* ins_pass, MaterialRenderParams& renderParams)
	{
        if ( scene )
        {
            ///////////////////////////////////////////////////////////////////////

            UInt gridSize = scene->getTerrainManager()->getConfig().gridSize;
            UInt gridSideNumInChunk = scene->getTerrainManager()->getConfig().gridSideNumInChunk;
            Flt chunkSize =  gridSize * gridSideNumInChunk;

            ///////////////////////////////////////////////////////////////////////

            GpuProgramParametersSharedPtr vpParams = ins_pass->getVertexProgramParameters();
            GpuProgramParametersSharedPtr fpParams = ins_pass->getFragmentProgramParameters();

            if ( decl )
            {
                ///////////////////////////////////////////////////////////////////////
                // Texture
                ///////////////////////////////////////////////////////////////////////

                {
                    // sky cube
                    TextureUnitState* tex = ins_pass->getTextureUnitState("skyCube");
                    if ( tex )
                    {
                        tex->setCubicTextureName( decl->waterSkyCubeTexName, true );
                    }
                }

                {
                    // normal Map
                    TextureUnitState* tex = ins_pass->getTextureUnitState("normal");
                    if ( tex )
                    {
                        tex->setAnimatedTextureName( decl->waterBumpTexName1, decl->waterBumpTexAnim.x, decl->waterBumpTexAnim.y );
                    }
                }

                ///////////////////////////////////////////////////////////////////////
                // VP
                ///////////////////////////////////////////////////////////////////////

                {
                    // gWaterUVWorldSize
                    float uvScale1 = chunkSize / decl->waterBumpTexParams.w;
                    float uvScale2 = chunkSize / decl->waterSpecularScalses.z;

                    vpParams->setNamedConstant( "gWaterUVWorldSize" , Ogre::Vector3(uvScale1,uvScale2,1) );
                }

                ///////////////////////////////////////////////////////////////////////
                // FP
                ///////////////////////////////////////////////////////////////////////

                {
                    // gWaterDeepColor
                    Vector3 param_value;
                    param_value.x = decl->waterDeepColor.x;
                    param_value.y = decl->waterDeepColor.y;
                    param_value.z = decl->waterDeepColor.z;
                    fpParams->setNamedConstant( "gWaterDeepColor" , param_value );
                }


                {
                    // gWaterReflectColor
                    Vector4 param_value;
                    param_value.x = decl->waterReflectColor.x;
                    param_value.y = decl->waterReflectColor.y;
                    param_value.z = decl->waterReflectColor.z;
                    param_value.w = decl->waterReflectColor.w;
                    fpParams->setNamedConstant( "gWaterReflectColor" , param_value );
                }

                {
                    // gWaterReflectScalses
                    Vector4 param_value;
                    param_value.x = decl->waterReflectScalses.x;
                    param_value.y = decl->waterReflectScalses.y;
                    param_value.z = decl->waterReflectScalses.z;
                    param_value.w = decl->waterReflectScalses.w;
                    fpParams->setNamedConstant( "gWaterReflectScalses" , param_value );
                }

                {
                    // gWaterRefractScalses
                    Vector4 param_value;
                    param_value.x = decl->waterRefractScalses.x;
                    param_value.y = decl->waterRefractScalses.y;
                    param_value.z = decl->waterRefractScalses.z;
                    param_value.w = decl->waterRefractScalses.w;
                    fpParams->setNamedConstant( "gWaterRefractScalses" , param_value );
                }

                {
                    // gWaterSpecularColor
                    Vector3 param_value;
                    param_value.x = decl->waterSpecularColor.x;
                    param_value.y = decl->waterSpecularColor.y;
                    param_value.z = decl->waterSpecularColor.z;
                    fpParams->setNamedConstant( "gWaterSpecularColor" , param_value );
                }

                {
                    // gWaterSpecularScalses
                    Vector4 param_value;
                    param_value.x = decl->waterSpecularScalses.x;
                    param_value.y = decl->waterSpecularScalses.y;
                    param_value.z = decl->waterSpecularScalses.z;
                    param_value.w = decl->waterSpecularScalses.w;
                    fpParams->setNamedConstant( "gWaterSpecularScalses" , param_value );
                }

                {
                    // gWaterBumpTexParams
                    Vector4 param_value;
                    param_value.x = decl->waterBumpTexParams.x;
                    param_value.y = decl->waterBumpTexParams.y;
                    param_value.z = decl->waterBumpTexParams.z;
                    param_value.w = decl->waterBumpTexParams.w;
                    fpParams->setNamedConstant( "gWaterBumpTexParams" , param_value );
                }
            }            
        }
	}
		
	//-----------------------------------------------------------------------
	void MaterialManager::applySeaMaterial(MG::Scene* scene, WaterEffectResourceDeclaration* decl, Pass* ins_pass, MaterialRenderParams& renderParams)
	{
        if ( scene )
        {
            ///////////////////////////////////////////////////////////////////////

            UInt gridSize = scene->getTerrainManager()->getConfig().gridSize;
            UInt gridSideNumInChunk = scene->getTerrainManager()->getConfig().gridSideNumInChunk;
            Flt chunkSize =  gridSize * gridSideNumInChunk;

            ///////////////////////////////////////////////////////////////////////

            GpuProgramParametersSharedPtr vpParams = ins_pass->getVertexProgramParameters();
            GpuProgramParametersSharedPtr fpParams = ins_pass->getFragmentProgramParameters();

            if ( decl )
            {
                ///////////////////////////////////////////////////////////////////////
                // VP
                ///////////////////////////////////////////////////////////////////////

                {
                    // gWaterUVWorldSize
                    float uvScale1 = chunkSize / decl->waterBumpTexParams.w;
                    float uvScale2 = chunkSize / decl->waterSpecularScalses.z;

                    vpParams->setNamedConstant( "gWaterUVWorldSize" , Ogre::Vector3(uvScale1,uvScale2,1) );
                }

                ///////////////////////////////////////////////////////////////////////
                // FP
                ///////////////////////////////////////////////////////////////////////

                {
                    // gWaterDeepColor
                    Vector3 param_value;
                    param_value.x = decl->waterDeepColor.x;
                    param_value.y = decl->waterDeepColor.y;
                    param_value.z = decl->waterDeepColor.z;
                    fpParams->setNamedConstant( "gWaterDeepColor" , param_value );
                }


                {
                    // gWaterReflectColor
                    Vector4 param_value;
                    param_value.x = decl->waterReflectColor.x;
                    param_value.y = decl->waterReflectColor.y;
                    param_value.z = decl->waterReflectColor.z;
                    param_value.w = decl->waterReflectColor.w;
                    fpParams->setNamedConstant( "gWaterReflectColor" , param_value );
                }

                {
                    // gWaterReflectScalses
                    Vector4 param_value;
                    param_value.x = decl->waterReflectScalses.x;
                    param_value.y = decl->waterReflectScalses.y;
                    param_value.z = decl->waterReflectScalses.z;
                    param_value.w = decl->waterReflectScalses.w;
                    fpParams->setNamedConstant( "gWaterReflectScalses" , param_value );
                }

                {
                    // gWaterRefractScalses
                    Vector4 param_value;
                    param_value.x = decl->waterRefractScalses.x;
                    param_value.y = decl->waterRefractScalses.y;
                    param_value.z = decl->waterRefractScalses.z;
                    param_value.w = decl->waterRefractScalses.w;
                    fpParams->setNamedConstant( "gWaterRefractScalses" , param_value );
                }

                {
                    // gWaterSpecularColor
                    Vector3 param_value;
                    param_value.x = decl->waterSpecularColor.x;
                    param_value.y = decl->waterSpecularColor.y;
                    param_value.z = decl->waterSpecularColor.z;
                    fpParams->setNamedConstant( "gWaterSpecularColor" , param_value );
                }

                {
                    // gWaterSpecularScalses
                    Vector4 param_value;
                    param_value.x = decl->waterSpecularScalses.x;
                    param_value.y = decl->waterSpecularScalses.y;
                    param_value.z = decl->waterSpecularScalses.z;
                    param_value.w = decl->waterSpecularScalses.w;
                    fpParams->setNamedConstant( "gWaterSpecularScalses" , param_value );
                }

                {
                    // gWaterBumpTexParams
                    Vector4 param_value;
                    param_value.x = decl->waterBumpTexParams.x;
                    param_value.y = decl->waterBumpTexParams.y;
                    param_value.z = decl->waterBumpTexParams.z;
                    param_value.w = decl->waterBumpTexParams.w;
                    fpParams->setNamedConstant( "gWaterBumpTexParams" , param_value );
                }
            }            
        }
	}

    //-----------------------------------------------------------------------
    void MaterialManager::applyWaterMaterial(MG::Scene* scene, WaterEffectResourceDeclaration* decl, Pass* ins_pass, MaterialRenderParams& renderParams)
    {
        if ( scene )
        {
            ///////////////////////////////////////////////////////////////////////

            UInt gridSize = scene->getTerrainManager()->getConfig().gridSize;
            UInt gridSideNumInChunk = scene->getTerrainManager()->getConfig().gridSideNumInChunk;
            Flt chunkSize =  gridSize * gridSideNumInChunk;

            ///////////////////////////////////////////////////////////////////////

            GpuProgramParametersSharedPtr vpParams = ins_pass->getVertexProgramParameters();
            GpuProgramParametersSharedPtr fpParams = ins_pass->getFragmentProgramParameters();

			if ( decl )
			{
                ///////////////////////////////////////////////////////////////////////
				// VP
                ///////////////////////////////////////////////////////////////////////

                {
                    // gWaterUVWorldSize
                    float uvScale1 = chunkSize / decl->waterBumpTexParams.w;
                    float uvScale2 = chunkSize / decl->waterSpecularScalses.z;

                    vpParams->setNamedConstant( "gWaterUVWorldSize" , Ogre::Vector3(uvScale1,uvScale2,1) );
                }

                ///////////////////////////////////////////////////////////////////////
                // FP
                ///////////////////////////////////////////////////////////////////////

                {
				    // gWaterDeepColor
                    Vector3 param_value;
				    param_value.x = decl->waterDeepColor.x;
				    param_value.y = decl->waterDeepColor.y;
				    param_value.z = decl->waterDeepColor.z;
				    fpParams->setNamedConstant( "gWaterDeepColor" , param_value );
                }


                {
                    // gWaterReflectColor
                    Vector4 param_value;
                    param_value.x = decl->waterReflectColor.x;
                    param_value.y = decl->waterReflectColor.y;
                    param_value.z = decl->waterReflectColor.z;
                    param_value.w = decl->waterReflectColor.w;
                    fpParams->setNamedConstant( "gWaterReflectColor" , param_value );
                }

                {
                    // gWaterReflectScalses
                    Vector4 param_value;
                    param_value.x = decl->waterReflectScalses.x;
                    param_value.y = decl->waterReflectScalses.y;
                    param_value.z = decl->waterReflectScalses.z;
                    param_value.w = decl->waterReflectScalses.w;
                    fpParams->setNamedConstant( "gWaterReflectScalses" , param_value );
                }

                {
                    // gWaterRefractScalses
                    Vector4 param_value;
                    param_value.x = decl->waterRefractScalses.x;
                    param_value.y = decl->waterRefractScalses.y;
                    param_value.z = decl->waterRefractScalses.z;
                    param_value.w = decl->waterRefractScalses.w;
                    fpParams->setNamedConstant( "gWaterRefractScalses" , param_value );
                }

                {
                    // gWaterSpecularColor
                    Vector3 param_value;
                    param_value.x = decl->waterSpecularColor.x;
                    param_value.y = decl->waterSpecularColor.y;
                    param_value.z = decl->waterSpecularColor.z;
                    fpParams->setNamedConstant( "gWaterSpecularColor" , param_value );
                }

                {
                    // gWaterSpecularScalses
                    Vector4 param_value;
                    param_value.x = decl->waterSpecularScalses.x;
                    param_value.y = decl->waterSpecularScalses.y;
                    param_value.z = decl->waterSpecularScalses.z;
                    param_value.w = decl->waterSpecularScalses.w;
                    fpParams->setNamedConstant( "gWaterSpecularScalses" , param_value );
                }

                {
                    // gWaterBumpTexParams
                    Vector4 param_value;
                    param_value.x = decl->waterBumpTexParams.x;
                    param_value.y = decl->waterBumpTexParams.y;
                    param_value.z = decl->waterBumpTexParams.z;
                    param_value.w = decl->waterBumpTexParams.w;
                    fpParams->setNamedConstant( "gWaterBumpTexParams" , param_value );
                }
			}            
        }
    }
}