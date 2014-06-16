/******************************************************************************/
#ifndef _TERRAINGROUNDTILES_H_
#define _TERRAINGROUNDTILES_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "TerrainNode.h"
#include "TerrainTiles.h"
#include "TerrainTilesLayerBlendMap.h"
#include "TerrainTilesMaterial.h"
#include "TerrainTilesGpu.h"


/******************************************************************************/
namespace MG
{
    //��������������������������������������������������������������������������������������������������
    //��������������������������������������������������������������������������������������������������

    /******************************************************************************/
    //�ؿ��еĵ�����Ⱦ����
    /******************************************************************************/
    class TerrainGroundTileRender : public TerrainTileRender
    {
    public:
		enum
		{
			MTL_NORMAL,
			MTL_REFRACT,

			MTL_NR,
		};

        TerrainGroundTileRender( TerrainManager* mgr, TerrainChunk* chunk, TerrainNode* node, TerrainTile* tile, UInt index );
        virtual ~TerrainGroundTileRender();

    public:

        //**********************************************************************************************************************
        //**********************************************************************************************************************

        virtual void                    update( Flt delta ) ;

        virtual void                    load( ) ;
        virtual void                    unload( ) ;

        /*########################################
        //      ����ͼ�����          
        #########################################*/
    public:

        // ��ͼ������
        struct TextureLayerInstance
        {
            // �������
            Int     layerIndex;
            // ȫ����ͼ����
            Int     globleIndex;
            // The world size of the texture to be applied in this layer Real worldSize;
            Flt     worldSize;

            Bool    hasDiffuseSpecular;
            Int     diffuseSpecularTextureIndex;
            Vec2    diffuseSpecularUVPos;
            Vec2    diffuseSpecularUVSize;

            Bool    hasNormalHeight;
            Int     normalHeightTextureIndex;
            Vec2    normalHeightUVPos;
            Vec2    normalHeightUVSize;

            TextureLayerInstance()
                : worldSize(100),hasDiffuseSpecular(false),hasNormalHeight(false)
                ,globleIndex(-1),layerIndex(-1),diffuseSpecularTextureIndex(-1),normalHeightTextureIndex(-1){}
        };

        typedef std::list<TextureLayerInstance> TextureLayerInstanceList;

        /// �����ͼ��
        void                            clearTextureLayer();

        /// �õ�������ͼ������
        virtual UInt                    getMaxTextureLayerCount() = 0;

        /// ������ͼ��,�Զ�������������������
        Int                             createOrRetriveTextureLayer( Int globleIndex, Bool isAutoGenerate=false );

        // �õ���ͼ������
        UInt                            getTextureLayerCount() const;
        /// �õ���ͼ��
        TextureLayerInstance*           getTextureLayer(Int layerIndex);

        /// ��ղ��õĲ��ʲ�
        void                            cleanNoUsedTextureLayer();

        ///////////////////////////////////////////////////////////////////////////////////////////////////

        /// ������ͼ��Դ
        virtual void                    generateTextureLayerResource() = 0;
        /// ������ͼ��Դ
        virtual void                    generateTextureLayerResource(Int layerIndex) = 0;
        /// ж����ͼ��Դ
        virtual void                    unLoadTextureLayerResource() = 0;

        /*########################################
        //      �����ͼ����          
        #########################################*/

    public:

        /// ���ɻ����ͼ�����б�
        void                            generateBlendTextureNameList();

        /// ���ɻ����ͼ�б�
        void                            generateBlendTextureList();

        /// �õ������ͼ, ���2��
        TexturePtr                      getBlendTexture(Int selfIndex);
        //  ɾ�������ͼ
        void                            destroyAllBlendTexture();
        /// �õ������ͼ�����б�
        const StringVector&             getValidBlendTextureNameList();

        // �õ������ͼ��С
        UInt                            getBlendTexturSize(){ return mLayerBlendMapSizeActual; };

        // �õ���ʽ
        static PixelFormat              getBlendTexturFormat();

        //**********************************************************************************************************************
        //**********************************************************************************************************************

        void                            generateTextureBlendLayerList();


		void							setMtlType(Int mtlType) { mMaterialType = mtlType; }

		Int								getMtlType() const { return mMaterialType; }
        /*########################################
        //      ��ͼ��ϲ���          
        #########################################*/

    public:
        // �õ���ͼ��ϲ�
        /** Retrieve the layer blending map for a given layer, which may
        be used to edit the blending information for that layer.
        @note
        You can only do this after the terrain has been loaded. You may 
        edit the content of the blend layer in another thread, but you
        may only upload it in the main render thread.
        @param layerIndex The layer index, which should be 1 or higher (since 
        the bottom layer has no blending).
        @returns Pointer to the TerrainLayerBlendMap requested. The caller must
        not delete this instance, use freeTemporaryResources if you want
        to save the memory after completing your editing.
        */
        TerrainLayerBlendMap*           createOrRetriveTextureBlendLayer(uint8 layerIndex);
        // ɾ��������ͼ��ϲ�
        void                            destroyAllTextureBlendLayer();
        /// ��ȡ��ͼ��ϲ�����
        uint8                           getTextureBlendLayerCount() const ;

        // �滻2����ͼ��
        void                            replaceTextureBlendLayer( uint8 layerIndex1, uint8 layerIndex2 );

        // ���»��Ͳ�
        void                            updateTextureBlendLayer();

        /*########################################
        //      UV�������ֱ���
        #########################################*/

    public:

        // ����UV������
        void                            generateUVMultipliers();
        /** Get the layer UV multiplier. 
        @remarks
        This is derived from the texture world size. The base UVs in the 
        terrain vary from 0 to 1 and this multiplier is used (in a fixed-function 
        texture coord scaling or a shader parameter) to translate it to the
        final value.
        @param index The layer index.
        */
        Real                            getLayerUVMultiplier(uint8 index) const;


        /*########################################
        //      ���ʹ���
        #########################################*/

    public:

		struct GroundMaterialGenerator
		{
			mutable unsigned long long int mMaterialGenerationCount;
			mutable bool mMaterialDirty;
			mutable bool mMaterialParamsDirty;

			String mMaterialName;

			mutable MaterialPtr mMaterial;

			GroundMaterialGenerator()
				:mMaterialGenerationCount(0)
				,mMaterialDirty(false)
				,mMaterialParamsDirty(false)
			{

			}
		};
		GroundMaterialGenerator&		getGroundMaterialGenerator();

        /// Ӧ����ʾ�����޸�
        virtual void                    applyRenderConfig();

        // ���ɲ�������
        void                            generateMaterialName() ;

		// �Ƿ�򵥵Ĳ���
		Bool							isSimpleMaterial();

        /// Get the material being used for the terrain
        MaterialPtr&                    getOrGenerateMaterialPtr() ;

        /// Internal getting of material 
        MaterialPtr&                    getMaterialPtr();

        /// Get the name of the material being used for the terrain
        const String&                   getMaterialName();

        void                            freeMaterial();

    protected:

        typedef std::vector<TexturePtr> TexturePtrList;

        ///////////////////////////////////////////////////////////////////////////////

    protected:

        ///////////////////////////////////////////////////////////////////////////////

        // ��ɫ����������
        TextureLayerInstanceList mColorTextureDeclLayers;

        ///////////////////////////////////////////////////////////////////////////////

        // ��������б�
        uint16 mLayerBlendMapSize;
        uint16 mLayerBlendMapSizeActual;
        StringVector mBlendTextureNameList;
        StringVector mValidBlendTextureNameList;
        TexturePtrList mBlendTextureList;

        ///////////////////////////////////////////////////////////////////////////////

        // ��ϲ�Ĳ����������б�
        TerrainLayerBlendMapList mBlendMapLayerList;

        ///////////////////////////////////////////////////////////////////////////////

        // �������б�
        typedef std::vector<Real> RealVector;
        RealVector mLayerUVMultiplier;

        ///////////////////////////////////////////////////////////////////////////////

        // ����
        mutable TerrainMaterialGeneratorPtr mBaseMaterialGenerator;

		GroundMaterialGenerator mMaterialGenerator;
		GroundMaterialGenerator mSimpleMaterialGenerator;
		GroundMaterialGenerator	mRefractMaterialGenerator;

		Int	mMaterialType;
        ///////////////////////////////////////////////////////////////////////////////

    };



}

/******************************************************************************/

#endif
