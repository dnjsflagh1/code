/******************************************************************************/
#ifndef _TERRAINTILESMATERIALA2_H_
#define _TERRAINTILESMATERIALA2_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "TerrainTilesMaterial.h"
#include "OgreGpuProgramParams.h"
/******************************************************************************/
namespace MG
{
    /** \addtogroup Optional Components
    *  @{
    */
    /** \addtogroup Terrain
    *  Some details on the terrain component
    *  @{
    */


    /** A TerrainMaterialGenerator which can cope with normal mapped, specular mapped
    terrain. 
    @note Requires the Cg plugin to render correctly
    */
    class TerrainMaterialGeneratorA2 : public TerrainMaterialGenerator
    {
    public:
        TerrainMaterialGeneratorA2();
        ~TerrainMaterialGeneratorA2();

        /** Shader model 2 profile target. 
        */
        class SM2Profile : public TerrainMaterialGenerator::Profile
        {
        public:
            SM2Profile(TerrainMaterialGenerator* parent, const String& name, const String& desc);
            ~SM2Profile();

            virtual MaterialPtr generate(TerrainGroundTileRender* tileRender);
            virtual uint8       getMaxLayers(TerrainGroundTileRender* tileRender) const;
            virtual void        updateParams(const MaterialPtr& mat, TerrainGroundTileRender* tileRender);
            virtual void        requestOptions(TerrainGroundTileRender* tileRender);
            virtual void        respondOptions(Bool immediately, Bool isSimple);

            ///////////////////////////////////////////////////////////////////////////////////////////////////

            bool isLayerColorMappingEnabled() const  { return mLayerColorMappingEnabled; }

            /** Whether to support normal mapping per layer in the shader (default true). 
            */
            bool isLayerNormalMappingEnabled() const  { return mLayerNormalMappingEnabled; }
            /** Whether to support normal mapping per layer in the shader (default true). 
            */
            void setLayerNormalMappingEnabled(bool enabled);
            /** Whether to support parallax mapping per layer in the shader (default true). 
            */
            bool isLayerParallaxMappingEnabled() const  { return mLayerParallaxMappingEnabled; }
            /** Whether to support parallax mapping per layer in the shader (default true). 
            */
            void setLayerParallaxMappingEnabled(bool enabled);
            /** Whether to support specular mapping per layer in the shader (default true). 
            */
            bool isLayerSpecularMappingEnabled() const  { return mLayerSpecularMappingEnabled; }
            /** Whether to support specular mapping per layer in the shader (default true). 
            */
            void setLayerSpecularMappingEnabled(bool enabled);
            /** Whether to support a global colour map over the terrain in the shader,
            if it's present (default true). 
            */
            bool isGlobalColourMapEnabled() const  { return mGlobalColourMapEnabled; }
            /** Whether to support a global colour map over the terrain in the shader,
            if it's present (default true). 
            */
            void setGlobalColourMapEnabled(bool enabled);
            /** Whether to support a light map over the terrain in the shader,
            if it's present (default true). 
            */
            bool isLightmapEnabled() const  { return mLightmapEnabled; }
            /** Whether to support a light map over the terrain in the shader,
            if it's present (default true). 
            */
            void setLightmapEnabled(bool enabled);

            bool isRegionMapEnabled() const  { return mRegionMapEnable; }

            /** Whether to support dynamic texture shadows received from other 
            objects, on the terrain (default true). 
            */
            bool getReceiveDynamicShadowsEnabled() const  { return mReceiveDynamicShadows; }
            /** Whether to support dynamic texture shadows received from other 
            objects, on the terrain (default true). 
            */
            void setReceiveDynamicShadowsEnabled(bool enabled);

            /** Whether to use depth shadows (default false). 
            */
            void setReceiveDynamicShadowsDepth(bool enabled);
            /** Whether to use depth shadows (default false). 
            */
            bool getReceiveDynamicShadowsDepth() const { return mDepthShadows; }
            /** Whether to use shadows on low LOD material rendering (when using composite map) (default false). 
            */
            void setReceiveDynamicShadowsLowLod(bool enabled);
            /** Whether to use shadows on low LOD material rendering (when using composite map) (default false). 
            */
            bool getReceiveDynamicShadowsLowLod() const { return mLowLodShadows; }

            /// Internal
            bool _isSM3Available() const { return mSM3Available; }

        protected:

            enum TechniqueType
            {
                HIGH_LOD, 
                LOW_LOD
            };

            void addNormalTechnique(const MaterialPtr& mat, TerrainBBGroundTileRender* tileRender, TechniqueType tt);
            void addWireFrameTechnique(const MaterialPtr& mat, TerrainBBGroundTileRender* tileRender, TechniqueType tt);

            void addFixedTechnique(const MaterialPtr& mat, TerrainBBGroundTileRender* tileRender, TechniqueType tt);

            void setTextureilter(TextureUnitState* tu);

            /// Interface definition for helper class to generate shaders
            class ShaderHelper : public GeneralAllocatedObject
            {
            public:
                ShaderHelper() {}
                virtual ~ShaderHelper() {}
                virtual HighLevelGpuProgramPtr generateVertexProgram(const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt);
                virtual HighLevelGpuProgramPtr generateFragmentProgram(const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt);
                virtual void updateParams(const SM2Profile* prof, const MaterialPtr& mat, TerrainBBGroundTileRender* tileRender);
            protected:
                virtual String getVertexProgramName(const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt);
                virtual String getFragmentProgramName(const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt);
                virtual HighLevelGpuProgramPtr createVertexProgram(const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt) = 0;
                virtual HighLevelGpuProgramPtr createFragmentProgram(const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt) = 0;
                virtual void generateVertexProgramSource(const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt, StringUtil::StrStreamType& outStream);
                virtual void generateFragmentProgramSource(const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt, StringUtil::StrStreamType& outStream);
                virtual void generateVpHeader(const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt, StringUtil::StrStreamType& outStream) = 0;
                virtual void generateFpHeader(const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt, StringUtil::StrStreamType& outStream) = 0;
                virtual void generateVpLayer(const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt, uint layer, StringUtil::StrStreamType& outStream) = 0;
                virtual void generateFpLayer(const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt, uint layer, StringUtil::StrStreamType& outStream) = 0;
                virtual void generateVpFooter(const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt, StringUtil::StrStreamType& outStream) = 0;
                virtual void generateFpFooter(const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt, StringUtil::StrStreamType& outStream) = 0;
                virtual void defaultVpParams(const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt, const HighLevelGpuProgramPtr& prog);
                virtual void defaultFpParams(const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt, const HighLevelGpuProgramPtr& prog);
                virtual void updateVpParams(const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt, const GpuProgramParametersSharedPtr& params);
                virtual void updateFpParams(const SM2Profile* prof, TerrainBBGroundTileRender* tileRender, TechniqueType tt, const GpuProgramParametersSharedPtr& params);
                static String getRGBAChannel(uint idx);
                static String getXYZWChannel(uint idx);
                size_t mShadowSamplerStartHi;
                size_t mShadowSamplerStartLo;

            };

            /// Utility class to help with generating shaders for Cg / HLSL.
            class ShaderHelperCg : public ShaderHelper
            {
            protected:
                HighLevelGpuProgramPtr createVertexProgram(const SM2Profile* prof, TerrainBBGroundTileRender* terrain, TechniqueType tt);
                HighLevelGpuProgramPtr createFragmentProgram(const SM2Profile* prof, TerrainBBGroundTileRender* terrain, TechniqueType tt);
                void generateVpHeader(const SM2Profile* prof, TerrainBBGroundTileRender* terrain, TechniqueType tt, StringUtil::StrStreamType& outStream);
                void generateFpHeader(const SM2Profile* prof, TerrainBBGroundTileRender* terrain, TechniqueType tt, StringUtil::StrStreamType& outStream);
                void generateVpLayer(const SM2Profile* prof, TerrainBBGroundTileRender* terrain, TechniqueType tt, uint layer, StringUtil::StrStreamType& outStream);
                void generateFpLayer(const SM2Profile* prof, TerrainBBGroundTileRender* terrain, TechniqueType tt, uint layer, StringUtil::StrStreamType& outStream);
                void generateVpFooter(const SM2Profile* prof, TerrainBBGroundTileRender* terrain, TechniqueType tt, StringUtil::StrStreamType& outStream);
                void generateFpFooter(const SM2Profile* prof, TerrainBBGroundTileRender* terrain, TechniqueType tt, StringUtil::StrStreamType& outStream);
                uint generateVpDynamicShadowsParams(uint texCoordStart, const SM2Profile* prof, TerrainBBGroundTileRender* terrain, TechniqueType tt, StringUtil::StrStreamType& outStream);
                void generateVpDynamicShadows(const SM2Profile* prof, TerrainBBGroundTileRender* terrain, TechniqueType tt, StringUtil::StrStreamType& outStream);
                void generateFpDynamicShadowsHelpers(const SM2Profile* prof, TerrainBBGroundTileRender* terrain, TechniqueType tt, StringUtil::StrStreamType& outStream);
                void generateFpDynamicShadowsParams(uint* texCoord, uint* sampler, const SM2Profile* prof, TerrainBBGroundTileRender* terrain, TechniqueType tt, StringUtil::StrStreamType& outStream);
                void generateFpDynamicShadows(const SM2Profile* prof, TerrainBBGroundTileRender* terrain, TechniqueType tt, StringUtil::StrStreamType& outStream);
            };

            class ShaderHelperHLSL : public ShaderHelperCg
            {
            protected:
                HighLevelGpuProgramPtr createVertexProgram(const SM2Profile* prof, TerrainBBGroundTileRender* terrain, TechniqueType tt);
                HighLevelGpuProgramPtr createFragmentProgram(const SM2Profile* prof, TerrainBBGroundTileRender* terrain, TechniqueType tt);
            };

            /// Utility class to help with generating shaders for GLSL.
            class ShaderHelperGLSL : public ShaderHelper
            {
            protected:
                HighLevelGpuProgramPtr createVertexProgram(const SM2Profile* prof, TerrainBBGroundTileRender* terrain, TechniqueType tt);
                HighLevelGpuProgramPtr createFragmentProgram(const SM2Profile* prof, TerrainBBGroundTileRender* terrain, TechniqueType tt);
                void generateVpHeader(const SM2Profile* prof, TerrainBBGroundTileRender* terrain, TechniqueType tt, StringUtil::StrStreamType& outStream) {}
                void generateFpHeader(const SM2Profile* prof, TerrainBBGroundTileRender* terrain, TechniqueType tt, StringUtil::StrStreamType& outStream) {}
                void generateVpLayer(const SM2Profile* prof, TerrainBBGroundTileRender* terrain, TechniqueType tt, uint layer, StringUtil::StrStreamType& outStream) {}
                void generateFpLayer(const SM2Profile* prof, TerrainBBGroundTileRender* terrain, TechniqueType tt, uint layer, StringUtil::StrStreamType& outStream) {}
                void generateVpFooter(const SM2Profile* prof, TerrainBBGroundTileRender* terrain, TechniqueType tt, StringUtil::StrStreamType& outStream) {}
                void generateFpFooter(const SM2Profile* prof, TerrainBBGroundTileRender* terrain, TechniqueType tt, StringUtil::StrStreamType& outStream) {}
            };

            ShaderHelper* mShaderGen;
            bool mLayerColorMappingEnabled;
            bool mLayerNormalMappingEnabled;
            bool mLayerParallaxMappingEnabled;
            bool mLayerSpecularMappingEnabled;

            bool mGlobalColourMapEnabled;
            bool mLightmapEnabled;
            bool mRegionMapEnable;

            bool mReceiveDynamicShadows;
            bool mDepthShadows;
            bool mLowLodShadows;
            bool mSM3Available;

            bool isShadowingEnabled(TechniqueType tt, TerrainBBGroundTileRender* terrain) const;

        };




    };



    /** @} */
    /** @} */


}

/******************************************************************************/

#endif
