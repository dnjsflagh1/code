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
	//MG����ϵͳ
	/******************************************************************************/
	class MaterialManager
	{
	public:

		MaterialManager();
		virtual ~MaterialManager();
		SINGLETON_INSTANCE(MaterialManager)

	public:

		//���ⲿʹ�õĽ�ڣ� ��һ�����������л���MaterialDeclaration
		Bool					praseScript(std::vector<std::wstring>& stringVector, MaterialDeclaration* mat_decls);

	public:

        // ������ȡ�ز���
        Ogre::MaterialPtr       createOrRetriveMaterial(MG::Scene* scene, Str materialGroup, U32 index, MaterialUserParams params);
        Ogre::MaterialPtr       createOrRetriveMaterial(MG::Scene* scene, MaterialDeclaration* decl, MaterialUserParams params);

        // ������ȡ��ˮ����
        Ogre::MaterialPtr       createOrRetriveWaterMaterial(MG::Scene* scene, U32 waterMatID, MaterialUserParams params);
        Ogre::MaterialPtr       createOrRetriveWaterMaterial(MG::Scene* scene, WaterEffectResourceDeclaration* decl, MaterialUserParams params);

		//��ò���ģ������
		MaterialDeclaration*	getMaterialDeclaration(Str materialGroup, U32 index);
        
	private:
		

        // �õ�ģ�����
        Ogre::MaterialPtr       getTemplateMaterial(MaterialDeclaration* decl, MaterialUserParams& params, MaterialRenderParams& renderParams);

        // �õ�ʵ��ģ�����`
        Ogre::MaterialPtr       getEntityTemplateMaterial(MaterialDeclaration* decl, MaterialRenderParams& params);
        // �õ�ʵ��ģ�����
        Ogre::MaterialPtr       getPlantTemplateMaterial(GrassEffectResourceDeclaration* decl, MaterialRenderParams& params);
        // �õ�ʵ��ģ�����
        Ogre::MaterialPtr       getWaterTemplateMaterial(WaterEffectResourceDeclaration* decl, MaterialRenderParams& params);


        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

    private:

        // ����ӰͶ�����
        void                    bindCommonShadowCasterMaterial( MG::Scene* scene, Ogre::MaterialPtr mat, 
                                    MaterialDeclaration* decl, MaterialUserParams& params, MaterialRenderParams& renderParams );


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:

        // �����ܲ��ʲ���
        void                    updateMaterialGroupDynamicParameter( Flt delta, MaterialDynamicParamsObject& object );
        // �����Ӳ��ʲ���
        void                    updateMaterialElementDynamicParameter( Flt delta, MaterialDynamicParamsObject& object, Vec3 center );

        // ������Ӧ���ʲ�������Ⱦʵ��
        void                    applyMaterialDynamicParameter( MaterialDynamicParamsObject& object, Renderable* renderable, U32 subEntityIndex = 0 );

    private:

        // ����ֲ�����ƫ����
        void                    updatePlantMaterialGroupDynamicParameter( Flt delta, MaterialDynamicParamsObject& object );
        // ����ֲ�����ƫ����
        void                    updatePlantMaterialElementDynamicParameter( Flt delta, MaterialDynamicParamsObject& object, Vec3 center );
        // ��Ӧֲ�����ʲ���
        void                    applyGrassEffectDynamicParameter( MaterialDynamicParamsObject& object, Renderable* renderable, U32 subEntityIndex = 0 );

	public:

        // ͨ��ģ�͵����ͣ� ���в���װ��
        Ogre::MaterialPtr		applyMaterial(MG::Scene* scene, MaterialDeclaration* decl, Ogre::MaterialPtr applyMat, MaterialUserParams& params, MaterialRenderParams& renderParams);

        // Ӧ����Ӱ����
        void            		applyShadowMaterial(MG::Scene* scene, MaterialDeclaration* decl, Pass* ins_pass, MaterialRenderParams& renderParams);
        // Ӧ��ʵ�����
		void		            applyUVMaterial(MG::Scene* scene, MaterialDeclaration* decl, Pass* ins_pass, MaterialRenderParams& renderParams);
        
        // Ӧ��ֲ�����
        void 	            	applyPlantMaterial(MG::Scene* scene, GrassEffectResourceDeclaration* decl, Pass* ins_pass, MaterialRenderParams& renderParams);
        // Ӧ��water����
        void 		            applyWaterMaterial(MG::Scene* scene, WaterEffectResourceDeclaration* decl, Pass* ins_pass, MaterialRenderParams& renderParams);
		// Ӧ��lake����
		void 		            applyLakeMaterial(MG::Scene* scene, WaterEffectResourceDeclaration* decl, Pass* ins_pass, MaterialRenderParams& renderParams);
		// Ӧ��sea����
		void 		            applySeaMaterial(MG::Scene* scene, WaterEffectResourceDeclaration* decl, Pass* ins_pass, MaterialRenderParams& renderParams);



	private:

		MG::MaterialSerializer*		mSerializer;
	};
}

/******************************************************************************/

#endif
