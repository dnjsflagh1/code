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
	//��Ϸ��ʾ����
	/******************************************************************************/
	class Display : public MGSingleton<Display>, public IDisplay
	{
	public:
        SINGLETON_DECLARE( Display )
        Display();
        virtual ~Display();

        ////////////////////////////////////////////////////////////////////////////////////

        // ����
        virtual	void	            setup();
        virtual	void	            apply();
                void	            getRenderSystemSetting(  Ogre::NameValuePairList& list );

        // ����
        virtual	void	            update();

        ////////////////////////////////////////////////////////////////////////////////////

        // �ֱ���
		virtual	UInt	            getWidth();
		virtual	UInt	            getHeight();

		// ʵ�ʷֱ���
		virtual UInt	            getActWidth();
		virtual	UInt	            getActHeight();

		//������Ƶģʽ
		virtual void				setVideoMode(Bool isFullScreen, U32 width, U32 height, Bool immediately = false);
		//��ȡ��Ƶģʽ, ���ʵ���Ϻ�getWidth��getHeight��һ����
		virtual Bool				getVideoMode(Bool& isFullScreen, U32& width, U32& height);
		//��ȡ��������ģʽ�б�
		virtual Bool				getVideoModeList(std::vector<VecI2>& videoModeList);

        ////////////////////////////////////////////////////////////////////////////////////
        //�õ�ȫ��
		virtual	Bool	            isFullScreen();

		//���н���
		virtual void				doScreenShot( Str filePath, Str fileName );

        ////////////////////////////////////////////////////////////////////////////////////

        // �õ�������������
        virtual	UInt	            getBatchCount();
        // �õ��ϴ�fps
        virtual	Flt	                getLastFPS();
        // �õ�ƽ��fps
        virtual	Flt	                getLastAverageFPS();
        // �õ�������
        virtual	UInt                getTriangleCount();

        ////////////////////////////////////////////////////////////////////////////////////

        // ������Ӱ
        virtual	void	            setShadowType(ShadowType level);
        virtual	ShadowType          getShadowType(){return mShadowType;};

        ////////////////////////////////////////////////////////////////////////////////////

        // ������Ч
        virtual	void	            setFogEnable( Bool enable );
        virtual	void	            setFogLevel(FogLevel level, Color color = ColorSet::white(), Flt expDensity=0.002, Flt linearStart=0, Flt linearEnd=1000);
        virtual	FogLevel            getFogLevel(){return mFogLevel;};
        virtual	Color               getFogColor();
        virtual	Flt                 getFogExpDensity();
        virtual	Flt                 getFogLinearStart();
        virtual	Flt                 getFogLinearEnd();

        ////////////////////////////////////////////////////////////////////////////////////

        // ����λ����ͼ�͸߹���ͼ����
        virtual	void	            setScaleBiasSpecular(Vec4 sbs);
        virtual	Vec4                getScaleBiasSpecular(){return mScaleBiasSpecular;};

        // ����Gamma
        virtual	void	            setGammaEnabled(Bool enable);
        virtual	Bool                getGammaEnabled(){return mGammaEnabled;};

        // ����FSAA
        virtual	void	            setFSAA(U32 fsaa, Str fsaaHint);
        virtual	U32					getFSAA(){return mFSAA;};
		virtual Str					getFSAAHint() { return mFSAAHint; }
		virtual Bool				getFSAAList(std::vector<std::pair<U32, Str>>& outFsaaList);

        // ����vsync
        virtual	void	            setVsync(Bool enable);
        virtual	Bool                getVsync(){return mVsync;};
        

        // ����VSyncInterval
        virtual	void	            setVsyncInterval(UInt interval);
        virtual	Int                 getVsyncInterval(){return mVsyncInterval;};
        
     
        // �����߿�ģʽ
        virtual	void	            setWireframeMode( Bool enable );
        virtual	Bool             	getWireframeMode(){ return mWireframeMode; };

       
        ////////////////////////////////////////////////////////////////////////////////////

		// �Ƿ���ʾ���
		virtual void				setEntityVisible( Bool visible, Bool immediately = false );
		virtual Bool				getEntityVisible() { return mEntityVisible; };

        // ����ʵ���Ƿ�ʹ�÷�����ͼ
        virtual	void	            setEntityNormalMapEnable(Bool enable);
        virtual	Bool                getEntityNormalMapEnable(){return mEntityNormalMapEnable;};

        // ����ʵ���Ƿ�ʹ�ø߹��AO��ͼ
        virtual	void	            setEntitySaMapEnable(Bool enable);
        virtual	Bool                getEntitySaMapEnable(){return mEntitySaMapEnable;};

        // ����ʵ���Ƿ�ʹ�ù�����ͼ
        virtual	void	            setEntityLightingMapEnable(Bool enable);
        virtual	Bool                getEntityLightingMapEnable(){return mEntityLightingMapEnable;};

        // �����Ƿ�ʵ����ܶ�̬����
        virtual	void	            setEntityReceiveDynamicShadowsEnabled(Bool enable);
        virtual	Bool                getEntityReceiveDynamicShadowsEnabled();

        ////////////////////////////////////////////////////////////////////////////////////

        // ����ʵ�����Ƿ�ʹ�÷�����ͼ
        virtual	void	            setEntityGroupNormalMapEnable(Bool enable);
        virtual	Bool                getEntityGroupNormalMapEnable(){return mEntityGroupNormalMapEnable;};

        // ����ʵ�����Ƿ�ʹ�ø߹��AO��ͼ
        virtual	void	            setEntityGroupSaMapEnable(Bool enable);
        virtual	Bool                getEntityGroupSaMapEnable(){return mEntityGroupSaMapEnable;};

        ////////////////////////////////////////////////////////////////////////////////////


        // ��Ӱ����
        /*
            x = shadow base value
            y = 
            z = 
            w = 
        */
        virtual	void	            setShadowParameter( Vec4 parameter );
        virtual	Vec4             	getShadowParameter(){ return mShadowParameter; };



        ////////////////////////////////////////////////////////////////////////////////////

		// �Ƿ���ʾˮ
		virtual	void				setTerrainWaterVisible( Bool visible, Bool immediately = false );
		virtual Bool				getTerrainWaterVisible() { return mTerrainWaterVisible; };

		////////////////////////////////////////////////////////////////////////////////////

        // �Ƿ���ʾ��������
        virtual	void	            setTerrainGridsVisible( Bool visible );
        virtual	Bool             	getTerrainGridsVisible(){ return mTerrainGridsVisible; };


        ////////////////////////////////////////////////////////////////////////////////////

        // ���β���
        /*
            x = ambient nDotl factor
            y = diffuse nDotl factor
            z = 
            w = 
        */
        virtual	void	            setTerrainLightingParameter( Vec4 parameter );
        virtual	Vec4             	getTerrainLightingParameter(){ return mTerrainLightingParameter; };

        // ����mipmapƫ����
        virtual	void	            setTerrainMipmapBias( Flt bias);
        virtual	Flt             	getTerrainMipmapBias(){return mTerrainTextureMipmapBias;};

        // ������ʾ����
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
