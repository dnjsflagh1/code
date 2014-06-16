/******************************************************************************/
#ifndef _MATERIAL_MANAGER_H_
#define _MATERIAL_MANAGER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IResourceManager.h"
#include "IModelObject.h"
#include "MaterialSerializer.h"
#include "IDisplay.h"

/******************************************************************************/
namespace MG
{

    ///////////////////////////////////////////////////////////////////////////////////////

    struct MaterialUserParams
    {
        Bool				isBatch;
        Bool                isCasterShadow;
        Bool				isDynamiShadowcReceive;
        Bool				isStaticShadowReceive;
        Bool                hasSkeleton;
        Str					suffixName;
        Flt                 shiness;
		Vec3				boundingSize;
        Ogre::ColourValue   emissive;
		Bool				isOpenGlow;

        MaterialUserParams()
            :isBatch(false)
            ,hasSkeleton(false)
            ,suffixName("")
            ,shiness(1)
            ,emissive(0,0,0)
            ,isCasterShadow(false)
            ,isDynamiShadowcReceive(false)
            ,isStaticShadowReceive(false)
			,isOpenGlow(false)
        {

        }
    };

    ///////////////////////////////////////////////////////////////////////////////////////

    struct MaterialRenderParams
    {
        ShadowType          shadowCasterType;
        ShadowType          shadowReceiveType;

        Bool                isUseLightingMap;
        Bool                isUseNormal;
        Bool                isUseSa;
        Bool                isBatch;
        Bool                isSkeleton;
		Bool				isHasOutline;

        MaterialRenderParams()
            :shadowCasterType(SCL_NONE)
            ,shadowReceiveType(SCL_NONE)
            ,isUseLightingMap(false)
            ,isUseNormal(false)
            ,isUseSa(false)
            ,isBatch(false)
            ,isSkeleton(false)
			,isHasOutline(false)
        {

        }
    };

    ///////////////////////////////////////////////////////////////////////////////////////

	struct GrassEffectDynamicParams
	{
		Bool avaliable;

		Real xinc;
		Real zinc;
		Real xpos;
		Real zpos;

		/* 
		param custom.x: offset in x axis direction;
		param custom.z: offset in z axis direction;
		param custom.y: height of entity;
		param custom.z: a reference value, final offset = offsetVelocity * timeElapsed * ( custom.y / custom.z )
		*/
		Vector4 custom;
	};

    ///////////////////////////////////////////////////////////////////////////////////////

	struct WaterEffectDynamicParams
	{

	};

    ///////////////////////////////////////////////////////////////////////////////////////

    struct MaterialDynamicParamsObject
    {
        ////////////////////////////////////////
        MaterialUserParams params;

		std::map<U32, GrassEffectDynamicParams*> grassEffectParamList;
		std::map<U32, WaterEffectDynamicParams*> waterEffectParamList;

        ////////////////////////////////////////

        MaterialDynamicParamsObject();
        virtual ~MaterialDynamicParamsObject();

        ////////////////////////////////////////

        void addDynamicParams( MaterialDeclaration* mat_decl, U32 subEntityIndex );
        void clearDynamicParams();

        ////////////////////////////////////////
    };

	/******************************************************************************/
	//MG材质系统
	/******************************************************************************/
	class MaterialManager
	{
	public:

		MaterialManager();
		virtual ~MaterialManager();
		SINGLETON_INSTANCE(MaterialManager)

	public:

		//给外部使用的借口， 从一段数据中序列化出MaterialDeclaration
		Bool					praseScript(std::vector<std::wstring>& stringVector, MaterialDeclaration* mat_decls);

	public:

        // 创建或取回材质
        Ogre::MaterialPtr       createOrRetriveMaterial(MG::Scene* scene, Str materialGroup, U32 index, MaterialUserParams params);
        Ogre::MaterialPtr       createOrRetriveMaterial(MG::Scene* scene, MaterialDeclaration* decl, MaterialUserParams params);

        // 创建或取回水材质
        Ogre::MaterialPtr       createOrRetriveWaterMaterial(MG::Scene* scene, U32 waterMatID, MaterialUserParams params);
        Ogre::MaterialPtr       createOrRetriveWaterMaterial(MG::Scene* scene, WaterEffectResourceDeclaration* decl, MaterialUserParams params);

		//获得材质模版描述
		MaterialDeclaration*	getMaterialDeclaration(Str materialGroup, U32 index);
        
	private:
		

        // 得到模板材质
        Ogre::MaterialPtr       getTemplateMaterial(MaterialDeclaration* decl, MaterialUserParams& params, MaterialRenderParams& renderParams);

        // 得到实体模板材质`
        Ogre::MaterialPtr       getEntityTemplateMaterial(MaterialDeclaration* decl, MaterialRenderParams& params);
        // 得到实体模板材质
        Ogre::MaterialPtr       getPlantTemplateMaterial(GrassEffectResourceDeclaration* decl, MaterialRenderParams& params);
        // 得到实体模板材质
        Ogre::MaterialPtr       getWaterTemplateMaterial(WaterEffectResourceDeclaration* decl, MaterialRenderParams& params);


        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

    private:

        // 绑定阴影投射材质
        void                    bindCommonShadowCasterMaterial( MG::Scene* scene, Ogre::MaterialPtr mat, 
                                    MaterialDeclaration* decl, MaterialUserParams& params, MaterialRenderParams& renderParams );


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:

        // 更新总材质参数
        void                    updateMaterialGroupDynamicParameter( Flt delta, MaterialDynamicParamsObject& object );
        // 更新子材质参数
        void                    updateMaterialElementDynamicParameter( Flt delta, MaterialDynamicParamsObject& object, Vec3 center );

        // 配置相应材质参数到渲染实体
        void                    applyMaterialDynamicParameter( MaterialDynamicParamsObject& object, Renderable* renderable, U32 subEntityIndex = 0 );

    private:

        // 更新植被随机偏移量
        void                    updatePlantMaterialGroupDynamicParameter( Flt delta, MaterialDynamicParamsObject& object );
        // 更新植被随机偏移量
        void                    updatePlantMaterialElementDynamicParameter( Flt delta, MaterialDynamicParamsObject& object, Vec3 center );
        // 相应植被材质参数
        void                    applyGrassEffectDynamicParameter( MaterialDynamicParamsObject& object, Renderable* renderable, U32 subEntityIndex = 0 );

	public:

        // 通过模型的类型， 进行材质装配
        Ogre::MaterialPtr		applyMaterial(MG::Scene* scene, MaterialDeclaration* decl, Ogre::MaterialPtr applyMat, MaterialUserParams& params, MaterialRenderParams& renderParams);

        // 应用阴影材质
        void            		applyShadowMaterial(MG::Scene* scene, MaterialDeclaration* decl, Pass* ins_pass, MaterialRenderParams& renderParams);
        // 应用实体材质
		void		            applyUVMaterial(MG::Scene* scene, MaterialDeclaration* decl, Pass* ins_pass, MaterialRenderParams& renderParams);
        
        // 应用植物材质
        void 	            	applyPlantMaterial(MG::Scene* scene, GrassEffectResourceDeclaration* decl, Pass* ins_pass, MaterialRenderParams& renderParams);
        // 应用water材质
        void 		            applyWaterMaterial(MG::Scene* scene, WaterEffectResourceDeclaration* decl, Pass* ins_pass, MaterialRenderParams& renderParams);
		// 应用lake材质
		void 		            applyLakeMaterial(MG::Scene* scene, WaterEffectResourceDeclaration* decl, Pass* ins_pass, MaterialRenderParams& renderParams);
		// 应用sea材质
		void 		            applySeaMaterial(MG::Scene* scene, WaterEffectResourceDeclaration* decl, Pass* ins_pass, MaterialRenderParams& renderParams);



	private:

		MG::MaterialSerializer*		mSerializer;
	};
}

/******************************************************************************/

#endif
