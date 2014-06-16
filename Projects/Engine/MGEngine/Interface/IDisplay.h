#ifndef _IDISPLAY_H_
#define _IDISPLAY_H_

namespace MG
{

    enum TextureFiltering
    {
        TFL_NONE,
        TFL_BILINEAR,
        TFL_TRILINEAR,
        TFL_ANISOTROPIC,
    };

	enum ShadowType
	{
		SCL_NONE,

        SCL_UNIFORM_DEPTH_TEXTURE,
        SCL_UNIFORM_FOCUSED_DEPTH_TEXTURE,
        SCL_LISPSM_DEPTH_TEXTURE,
        SCL_PLANE_OPTIMALDEPTH_TEXTURE,

        SCL_PSSM_DIFFUSE_TEXTURE,
        SCL_PSSM_DEPTH_TEXTURE,
	};
    
    enum FogLevel
    {
        FOL_NONE,
        FOL_EXP,
        FOL_EXP2,
        FOL_LINEAR
    };

	class IDisplay
	{
	public:

        ///////////////////////////////////////////////////////////////////////////////////

        virtual	void	            apply() = 0;

        ///////////////////////////////////////////////////////////////////////////////////

		// 分辨率
		virtual	UInt	            getWidth() = 0;
		virtual	UInt	            getHeight() = 0;

		// 实际分辨率
		virtual UInt	            getActWidth() = 0;
		virtual	UInt	            getActHeight() = 0;

		//设置视频模式
		virtual void				setVideoMode(Bool isFullScreen, U32 width, U32 height, Bool immediately = false) = 0;
		//获取视频模式, 这个实际上和getWidth，getHeight是一样的
		virtual Bool				getVideoMode(Bool& isFullScreen, U32& width, U32& height) = 0;
		//获取可用视屏模式列表
		virtual Bool				getVideoModeList(std::vector<VecI2>& videoModeList) = 0;

		////////////////////////////////////////////////////////////////////////////////////

		//得到全屏
		virtual	Bool	            isFullScreen() = 0;

		//截屏操作
		virtual void				doScreenShot( Str filePath, Str fileName ) = 0; 

		////////////////////////////////////////////////////////////////////////////////////

        // 得到批量处理数量
        virtual	UInt	            getBatchCount() = 0;
        // 得到上次fps
        virtual	Flt	                getLastFPS() = 0;
        // 得到平均fps
        virtual	Flt	                getLastAverageFPS() = 0;
        // 得到三角面
        virtual	UInt                getTriangleCount() = 0;
        
        ///////////////////////////////////////////////////////////////////////////////////

        // 设置阴影
        virtual	void	            setShadowType(ShadowType level) = 0;
        virtual	ShadowType          getShadowType() = 0;

        // 设置阴影参数
        virtual	void	            setShadowParameter( Vec4 parameter ) = 0;
        virtual	Vec4             	getShadowParameter() = 0;

        ///////////////////////////////////////////////////////////////////////////////////

        // 设置雾效
        virtual	void	            setFogLevel(FogLevel level, Color color = ColorSet::white(), Flt expDensity=0.002, Flt linearStart=0, Flt linearEnd=1000) = 0;
        virtual	FogLevel            getFogLevel() = 0;
        virtual	Color               getFogColor() = 0;
        virtual	Flt                 getFogExpDensity() = 0;
        virtual	Flt                 getFogLinearStart() = 0;
        virtual	Flt                 getFogLinearEnd() = 0;

        ///////////////////////////////////////////////////////////////////////////////////

        // 设置位移贴图和高光贴图参数
        virtual	void	            setScaleBiasSpecular(Vec4 sbs) = 0;
        virtual	Vec4                getScaleBiasSpecular() = 0;

        // 设置Gamma
        virtual	void	            setGammaEnabled(Bool enable)= 0;
        virtual	Bool                getGammaEnabled() = 0;

		// 设置FSAA
		virtual	void	            setFSAA(U32 fsaa, Str fsaaHint) = 0;
		virtual	U32					getFSAA() = 0;
		virtual Str					getFSAAHint() = 0;
		virtual Bool				getFSAAList(std::vector<std::pair<U32, Str>>& outFsaaList) = 0;


        // 设置vsync
        virtual	void	            setVsync(Bool enable) = 0;
        virtual	Bool                getVsync() = 0;

        // 设置VSyncInterval
        virtual	void	            setVsyncInterval(UInt interval) = 0;
        virtual	Int                 getVsyncInterval() = 0;

        // 地形线框模式
        virtual	void	            setWireframeMode( Bool enable ) = 0;
        virtual	Bool             	getWireframeMode() = 0;

        ///////////////////////////////////////////////////////////////////////////////////

		// 物件显示
		virtual void				setEntityVisible( Bool visible, Bool immediately = false ) = 0;
		virtual Bool				getEntityVisible() = 0;

        // 设置实体是否使用法线贴图
        virtual	void	            setEntityNormalMapEnable(Bool enable) = 0;
        virtual	Bool                getEntityNormalMapEnable() = 0;

        // 设置实体是否使用高光和AO贴图
        virtual	void	            setEntitySaMapEnable(Bool enable) = 0;
        virtual	Bool                getEntitySaMapEnable() = 0;

        // 设置实体是否使用光照贴图
        virtual	void	            setEntityLightingMapEnable(Bool enable) = 0;
        virtual	Bool                getEntityLightingMapEnable() = 0;

        // 设置是否实体接受动态光照
        virtual	void	            setEntityReceiveDynamicShadowsEnabled(Bool enable) = 0;
        virtual	Bool                getEntityReceiveDynamicShadowsEnabled() = 0;

        ///////////////////////////////////////////////////////////////////////////////////

        // 设置实体组是否使用法线贴图
        virtual	void	            setEntityGroupNormalMapEnable(Bool enable) = 0;
        virtual	Bool                getEntityGroupNormalMapEnable() = 0;

        // 设置实体组是否使用高光和AO贴图
        virtual	void	            setEntityGroupSaMapEnable(Bool enable) = 0;
        virtual	Bool                getEntityGroupSaMapEnable() = 0;

        ///////////////////////////////////////////////////////////////////////////////////

		// 水面显示
		virtual	void				setTerrainWaterVisible( Bool visible, Bool immediately = false ) = 0;
		virtual Bool				getTerrainWaterVisible() = 0;

		///////////////////////////////////////////////////////////////////////////////////

        // 地形网格显示
        virtual	void	            setTerrainGridsVisible( Bool visible ) = 0;
        virtual	Bool             	getTerrainGridsVisible() = 0;

        // 地形Mipmap偏移量
        virtual	void	            setTerrainMipmapBias( Flt bias) = 0;
        virtual	Flt             	getTerrainMipmapBias() = 0;

        // 设置地形参数
        virtual	void	            setTerrainLightingParameter( Vec4 parameter ) = 0;
        virtual	Vec4             	getTerrainLightingParameter() = 0;

        // 地形显示设置
        virtual	void	            setTerrainTextureFiltering( TextureFiltering filter) = 0;
        virtual	TextureFiltering	getTerrainTextureFiltering() = 0;

        virtual	void	            setTerrainColorMappingEnabled( Bool enable) = 0;
        virtual	Bool	            getTerrainColorMappingEnabled() = 0;

        virtual	void	            setTerrainNormalMappingEnabled( Bool enable) = 0;
        virtual	Bool	            getTerrainNormalMappingEnabled() = 0;

        virtual	void	            setTerrainParallaxMappingEnabled( Bool enable) = 0;
        virtual	Bool	            getTerrainParallaxMappingEnabled() = 0;

        virtual	void	            setTerrainSpecularMappingEnabled( Bool enable) = 0;
        virtual	Bool	            getTerrainSpecularMappingEnabled() = 0;

        virtual	void	            setTerrainLightmapEnabled( Bool enable) = 0;
        virtual	Bool	            getTerrainLightmapEnabled() = 0;

        virtual	void	            setTerrainReceiveDynamicShadowsEnabled( Bool enable) = 0;
        virtual	Bool	            getTerrainReceiveDynamicShadowsEnabled() = 0;

        virtual	void	            setTerrainRegionDisplayEnabled( Bool enable) = 0;
        virtual	Bool                getTerrainRegionDisplayEnabled() = 0;

        ///////////////////////////////////////////////////////////////////////////////////

        virtual	void	            setWaterReflectionEnabled( Bool enable) = 0;
        virtual	Bool                getWaterReflectionEnabled() = 0;

		virtual	void	            setWaterRefractionEnabled( Bool enable) = 0;
		virtual	Bool                getWaterRefractionEnabled() = 0;

        virtual	void	            setWaterDepthCheckEnabled( Bool enable) = 0;
        virtual	Bool                getWaterDepthCheckEnabled() = 0;

        ///////////////////////////////////////////////////////////////////////////////////

        virtual void	            setDebugNoTerrain(Bool enable)= 0;
        virtual Bool	            isDebugNoTerrain()= 0;

        virtual void	            setDebugNoWater(Bool enable)= 0;
        virtual Bool	            isDebugNoWater()= 0;

        virtual void	            setDebugNoSpeedTree(Bool enable)= 0;
        virtual Bool	            isDebugNoSpeedTree()= 0;

		virtual void	            setDebugNoSpeedGrass(Bool enable)= 0;
		virtual Bool	            isDebugNoSpeedGrass()= 0;

        virtual void	            setDebugNoStaticEntity(Bool enable)= 0;
        virtual Bool	            isDebugNoStaticEntity()= 0;

        virtual void	            setDebugNoStaticEffect(Bool enable)= 0;
        virtual Bool	            isDebugNoStaticEffect()= 0;

        virtual void	            setDebugNoEntity(Bool enable)= 0;
        virtual Bool	            isDebugNoEntity()= 0;
        
        virtual void	            setDebugShowBlock(Bool enable)= 0;
        virtual Bool	            isDebugShowBlock()= 0;

	};
}

#endif