/******************************************************************************/
#ifndef _DISPLAY_H_
#define _DISPLAY_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "Singleton.h"
#include "IDisplay.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//游戏显示处理
	/******************************************************************************/
	class Display : public MGSingleton<Display>, public IDisplay
	{
	public:
        SINGLETON_DECLARE( Display )
        Display();
        virtual ~Display();

        ////////////////////////////////////////////////////////////////////////////////////

        // 配置
        virtual	void	            setup();
        virtual	void	            apply();
                void	            getRenderSystemSetting(  Ogre::NameValuePairList& list );

        // 更新
        virtual	void	            update();

        ////////////////////////////////////////////////////////////////////////////////////

        // 分辨率
		virtual	UInt	            getWidth();
		virtual	UInt	            getHeight();

		// 实际分辨率
		virtual UInt	            getActWidth();
		virtual	UInt	            getActHeight();

		//设置视频模式
		virtual void				setVideoMode(Bool isFullScreen, U32 width, U32 height, Bool immediately = false);
		//获取视频模式, 这个实际上和getWidth，getHeight是一样的
		virtual Bool				getVideoMode(Bool& isFullScreen, U32& width, U32& height);
		//获取可用视屏模式列表
		virtual Bool				getVideoModeList(std::vector<VecI2>& videoModeList);

        ////////////////////////////////////////////////////////////////////////////////////
        //得到全屏
		virtual	Bool	            isFullScreen();

		//进行截屏
		virtual void				doScreenShot( Str filePath, Str fileName );

        ////////////////////////////////////////////////////////////////////////////////////

        // 得到批量处理数量
        virtual	UInt	            getBatchCount();
        // 得到上次fps
        virtual	Flt	                getLastFPS();
        // 得到平均fps
        virtual	Flt	                getLastAverageFPS();
        // 得到三角面
        virtual	UInt                getTriangleCount();

        ////////////////////////////////////////////////////////////////////////////////////

        // 设置阴影
        virtual	void	            setShadowType(ShadowType level);
        virtual	ShadowType          getShadowType(){return mShadowType;};

        ////////////////////////////////////////////////////////////////////////////////////

        // 设置雾效
        virtual	void	            setFogEnable( Bool enable );
        virtual	void	            setFogLevel(FogLevel level, Color color = ColorSet::white(), Flt expDensity=0.002, Flt linearStart=0, Flt linearEnd=1000);
        virtual	FogLevel            getFogLevel(){return mFogLevel;};
        virtual	Color               getFogColor();
        virtual	Flt                 getFogExpDensity();
        virtual	Flt                 getFogLinearStart();
        virtual	Flt                 getFogLinearEnd();

        ////////////////////////////////////////////////////////////////////////////////////

        // 设置位移贴图和高光贴图参数
        virtual	void	            setScaleBiasSpecular(Vec4 sbs);
        virtual	Vec4                getScaleBiasSpecular(){return mScaleBiasSpecular;};

        // 设置Gamma
        virtual	void	            setGammaEnabled(Bool enable);
        virtual	Bool                getGammaEnabled(){return mGammaEnabled;};

        // 设置FSAA
        virtual	void	            setFSAA(U32 fsaa, Str fsaaHint);
        virtual	U32					getFSAA(){return mFSAA;};
		virtual Str					getFSAAHint() { return mFSAAHint; }
		virtual Bool				getFSAAList(std::vector<std::pair<U32, Str>>& outFsaaList);

        // 设置vsync
        virtual	void	            setVsync(Bool enable);
        virtual	Bool                getVsync(){return mVsync;};
        

        // 设置VSyncInterval
        virtual	void	            setVsyncInterval(UInt interval);
        virtual	Int                 getVsyncInterval(){return mVsyncInterval;};
        
     
        // 地形线框模式
        virtual	void	            setWireframeMode( Bool enable );
        virtual	Bool             	getWireframeMode(){ return mWireframeMode; };

       
        ////////////////////////////////////////////////////////////////////////////////////

		// 是否显示物件
		virtual void				setEntityVisible( Bool visible, Bool immediately = false );
		virtual Bool				getEntityVisible() { return mEntityVisible; };

        // 设置实体是否使用法线贴图
        virtual	void	            setEntityNormalMapEnable(Bool enable);
        virtual	Bool                getEntityNormalMapEnable(){return mEntityNormalMapEnable;};

        // 设置实体是否使用高光和AO贴图
        virtual	void	            setEntitySaMapEnable(Bool enable);
        virtual	Bool                getEntitySaMapEnable(){return mEntitySaMapEnable;};

        // 设置实体是否使用光照贴图
        virtual	void	            setEntityLightingMapEnable(Bool enable);
        virtual	Bool                getEntityLightingMapEnable(){return mEntityLightingMapEnable;};

        // 设置是否实体接受动态光照
        virtual	void	            setEntityReceiveDynamicShadowsEnabled(Bool enable);
        virtual	Bool                getEntityReceiveDynamicShadowsEnabled();

        ////////////////////////////////////////////////////////////////////////////////////

        // 设置实体组是否使用法线贴图
        virtual	void	            setEntityGroupNormalMapEnable(Bool enable);
        virtual	Bool                getEntityGroupNormalMapEnable(){return mEntityGroupNormalMapEnable;};

        // 设置实体组是否使用高光和AO贴图
        virtual	void	            setEntityGroupSaMapEnable(Bool enable);
        virtual	Bool                getEntityGroupSaMapEnable(){return mEntityGroupSaMapEnable;};

        ////////////////////////////////////////////////////////////////////////////////////


        // 阴影参数
        /*
            x = shadow base value
            y = 
            z = 
            w = 
        */
        virtual	void	            setShadowParameter( Vec4 parameter );
        virtual	Vec4             	getShadowParameter(){ return mShadowParameter; };



        ////////////////////////////////////////////////////////////////////////////////////

		// 是否显示水
		virtual	void				setTerrainWaterVisible( Bool visible, Bool immediately = false );
		virtual Bool				getTerrainWaterVisible() { return mTerrainWaterVisible; };

		////////////////////////////////////////////////////////////////////////////////////

        // 是否显示地形网格
        virtual	void	            setTerrainGridsVisible( Bool visible );
        virtual	Bool             	getTerrainGridsVisible(){ return mTerrainGridsVisible; };


        ////////////////////////////////////////////////////////////////////////////////////

        // 地形参数
        /*
            x = ambient nDotl factor
            y = diffuse nDotl factor
            z = 
            w = 
        */
        virtual	void	            setTerrainLightingParameter( Vec4 parameter );
        virtual	Vec4             	getTerrainLightingParameter(){ return mTerrainLightingParameter; };

        // 设置mipmap偏移量
        virtual	void	            setTerrainMipmapBias( Flt bias);
        virtual	Flt             	getTerrainMipmapBias(){return mTerrainTextureMipmapBias;};

        // 地形显示设置
        virtual	void	            setTerrainTextureFiltering( TextureFiltering filter);
        virtual	TextureFiltering	getTerrainTextureFiltering(){return mTerrainTextureFiltering;};

        virtual	void	            setTerrainColorMappingEnabled( Bool enable);
        virtual	Bool	            getTerrainColorMappingEnabled(){ return mTerrainColorMappingEnabled;};

        virtual	void	            setTerrainNormalMappingEnabled( Bool enable);
        virtual	Bool	            getTerrainNormalMappingEnabled(){return mTerrainNormalMappingEnabled;};

        virtual	void	            setTerrainParallaxMappingEnabled( Bool enable);
        virtual	Bool	            getTerrainParallaxMappingEnabled(){return mTerrainParallaxMappingEnabled;};

        virtual	void	            setTerrainSpecularMappingEnabled( Bool enable);
        virtual	Bool	            getTerrainSpecularMappingEnabled(){return mTerrainSpecularMappingEnabled;};

        virtual	void	            setTerrainLightmapEnabled( Bool enable);
        virtual	Bool	            getTerrainLightmapEnabled(){return mTerrainLightmapEnabled;};

        virtual	void	            setTerrainReceiveDynamicShadowsEnabled( Bool enable);
        virtual	Bool                getTerrainReceiveDynamicShadowsEnabled();

        virtual	void	            setTerrainRegionDisplayEnabled( Bool enable);
        virtual	Bool                getTerrainRegionDisplayEnabled(){return mTerrainRegionDisplayEnabledEnabled;};

        ////////////////////////////////////////////////////////////////////////////////////

        virtual	void	            setWaterReflectionEnabled( Bool enable);
        virtual	Bool                getWaterReflectionEnabled(){return mWaterReflectionEnabled;};

		virtual	void	            setWaterRefractionEnabled( Bool enable);
		virtual	Bool                getWaterRefractionEnabled(){return mWaterRefractionEnabled;};

        virtual	void	            setWaterDepthCheckEnabled( Bool enable);
        virtual	Bool                getWaterDepthCheckEnabled(){return mWaterDepthCheckEnabled;};

        ////////////////////////////////////////////////////////////////////////////////////

        //Debug
        virtual void	            setDebugNoTerrain(Bool enable){mIsDebugNoTerrain=enable;};
        virtual Bool	            isDebugNoTerrain(){return mIsDebugNoTerrain;};

        virtual void	            setDebugNoWater(Bool enable){mIsDebugNoWater=enable;};
        virtual Bool	            isDebugNoWater(){return mIsDebugNoWater;};

        virtual void	            setDebugNoSpeedTree(Bool enable){mIsDebugNoSpeedTree=enable;};
        virtual Bool	            isDebugNoSpeedTree(){return mIsDebugNoSpeedTree;};

		virtual void	            setDebugNoSpeedGrass(Bool enable){mIsDebugNoSpeedGrass=enable;};
		virtual Bool	            isDebugNoSpeedGrass(){return mIsDebugNoSpeedGrass;};

        virtual void	            setDebugNoStaticEntity(Bool enable){mIsDebugNoStaticEntity=enable;};
        virtual Bool	            isDebugNoStaticEntity(){return mIsDebugNoStaticEntity;};

        virtual void	            setDebugNoStaticEffect(Bool enable){mIsDebugNoStaticEffect=enable;};
        virtual Bool	            isDebugNoStaticEffect(){return mIsDebugNoStaticEffect;};

        virtual void	            setDebugNoEntity(Bool enable){mIsDebugNoEntity=enable;};
        virtual Bool	            isDebugNoEntity(){return mIsDebugNoEntity;};

        virtual void	            setDebugShowBlock(Bool enable){mIsDebugShowBlock=enable;};
        virtual Bool	            isDebugShowBlock(){return mIsDebugShowBlock;};

        ////////////////////////////////////////////////////////////////////////////////////

    private:

		Bool mEntityVisible;
        Bool mEntityNormalMapEnable;
        Bool mEntitySaMapEnable;
        Bool mEntityLightingMapEnable;
        Bool mEntityReceiveDynamicShadowsEnabled;

        Bool mEntityGroupNormalMapEnable;
        Bool mEntityGroupSaMapEnable;

		ShadowType mShadowType;

        FogLevel    mFogLevel;

        Bool mTerrainNormalMappingEnabled;
        Bool mTerrainParallaxMappingEnabled;
        Bool mTerrainSpecularMappingEnabled;
        Bool mTerrainLightmapEnabled;
        Bool mTerrainReceiveDynamicShadowsEnabled;
        Bool mTerrainRegionDisplayEnabledEnabled;
        Bool mTerrainColorMappingEnabled;
        Bool mWaterReflectionEnabled;
		Bool mWaterRefractionEnabled;
        Bool mWaterDepthCheckEnabled;

        Flt mTerrainTextureMipmapBias;
        TextureFiltering mTerrainTextureFiltering;
        Bool mIsFullScreen;
        VecI2 mDefaultWindowSize;
        VecI2 mCurWindowSize;
		U32	mDefaultColorDepths;
        Vec4 mScaleBiasSpecular;
        Bool mGammaEnabled;
        Int mFSAA;
		Str mFSAAHint;
        Bool mVsync;
        UInt mVsyncInterval;
        Bool mWireframeMode;
        Bool mTerrainGridsVisible;
		Bool mTerrainWaterVisible;

        Vec4 mTerrainLightingParameter;
        Vec4 mShadowParameter;

        // Fog
        FogLevel mFogMode;
        ColourValue mFogColour;
        Real mFogStart;
        Real mFogEnd;
        Real mFogDensity;

        //Debug
        Bool    mIsDebugNoTerrain;
        Bool    mIsDebugNoWater;
        Bool    mIsDebugNoSpeedTree;
		Bool	mIsDebugNoSpeedGrass;
        Bool    mIsDebugNoStaticEntity;
        Bool    mIsDebugNoStaticEffect;
        Bool    mIsDebugNoEntity;
        Bool    mIsDebugShowBlock;

	};
	
}

/******************************************************************************/

#endif
