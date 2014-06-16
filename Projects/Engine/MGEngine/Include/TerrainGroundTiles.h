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
    //×××××××××××××××××××××××××××××××××××××××××××××××××
    //×××××××××××××××××××××××××××××××××××××××××××××××××

    /******************************************************************************/
    //地块中的单次渲染区域
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
        //      总贴图层操作          
        #########################################*/
    public:

        // 贴图层声明
        struct TextureLayerInstance
        {
            // 层的索引
            Int     layerIndex;
            // 全局贴图索引
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

        /// 清除贴图层
        void                            clearTextureLayer();

        /// 得到最大的贴图层数量
        virtual UInt                    getMaxTextureLayerCount() = 0;

        /// 增加贴图层,自动计算自身索引并返回
        Int                             createOrRetriveTextureLayer( Int globleIndex, Bool isAutoGenerate=false );

        // 得到贴图层数量
        UInt                            getTextureLayerCount() const;
        /// 得到贴图层
        TextureLayerInstance*           getTextureLayer(Int layerIndex);

        /// 清空不用的材质层
        void                            cleanNoUsedTextureLayer();

        ///////////////////////////////////////////////////////////////////////////////////////////////////

        /// 生成贴图资源
        virtual void                    generateTextureLayerResource() = 0;
        /// 生成贴图资源
        virtual void                    generateTextureLayerResource(Int layerIndex) = 0;
        /// 卸载贴图资源
        virtual void                    unLoadTextureLayerResource() = 0;

        /*########################################
        //      混合贴图操作          
        #########################################*/

    public:

        /// 生成混合贴图名字列表。
        void                            generateBlendTextureNameList();

        /// 生成混合贴图列表。
        void                            generateBlendTextureList();

        /// 得到混合贴图, 最多2张
        TexturePtr                      getBlendTexture(Int selfIndex);
        //  删除混合贴图
        void                            destroyAllBlendTexture();
        /// 得到混合贴图名字列表
        const StringVector&             getValidBlendTextureNameList();

        // 得到混合贴图大小
        UInt                            getBlendTexturSize(){ return mLayerBlendMapSizeActual; };

        // 得到格式
        static PixelFormat              getBlendTexturFormat();

        //**********************************************************************************************************************
        //**********************************************************************************************************************

        void                            generateTextureBlendLayerList();


		void							setMtlType(Int mtlType) { mMaterialType = mtlType; }

		Int								getMtlType() const { return mMaterialType; }
        /*########################################
        //      贴图混合操作          
        #########################################*/

    public:
        // 得到贴图混合层
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
        // 删除所有贴图混合层
        void                            destroyAllTextureBlendLayer();
        /// 获取贴图混合层数量
        uint8                           getTextureBlendLayerCount() const ;

        // 替换2个贴图层
        void                            replaceTextureBlendLayer( uint8 layerIndex1, uint8 layerIndex2 );

        // 更新缓和层
        void                            updateTextureBlendLayer();

        /*########################################
        //      UV采样器分辨率
        #########################################*/

    public:

        // 分配UV采样器
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
        //      材质管理
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

        /// 应用显示参数修改
        virtual void                    applyRenderConfig();

        // 生成材质名字
        void                            generateMaterialName() ;

		// 是否简单的材质
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

        // 颜色纹理描述层
        TextureLayerInstanceList mColorTextureDeclLayers;

        ///////////////////////////////////////////////////////////////////////////////

        // 混合纹理集列表
        uint16 mLayerBlendMapSize;
        uint16 mLayerBlendMapSizeActual;
        StringVector mBlendTextureNameList;
        StringVector mValidBlendTextureNameList;
        TexturePtrList mBlendTextureList;

        ///////////////////////////////////////////////////////////////////////////////

        // 混合层的操作管理器列表
        TerrainLayerBlendMapList mBlendMapLayerList;

        ///////////////////////////////////////////////////////////////////////////////

        // 采样器列表
        typedef std::vector<Real> RealVector;
        RealVector mLayerUVMultiplier;

        ///////////////////////////////////////////////////////////////////////////////

        // 材质
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
