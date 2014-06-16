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

		// �ֱ���
		virtual	UInt	            getWidth() = 0;
		virtual	UInt	            getHeight() = 0;

		// ʵ�ʷֱ���
		virtual UInt	            getActWidth() = 0;
		virtual	UInt	            getActHeight() = 0;

		//������Ƶģʽ
		virtual void				setVideoMode(Bool isFullScreen, U32 width, U32 height, Bool immediately = false) = 0;
		//��ȡ��Ƶģʽ, ���ʵ���Ϻ�getWidth��getHeight��һ����
		virtual Bool				getVideoMode(Bool& isFullScreen, U32& width, U32& height) = 0;
		//��ȡ��������ģʽ�б�
		virtual Bool				getVideoModeList(std::vector<VecI2>& videoModeList) = 0;

		////////////////////////////////////////////////////////////////////////////////////

		//�õ�ȫ��
		virtual	Bool	            isFullScreen() = 0;

		//��������
		virtual void				doScreenShot( Str filePath, Str fileName ) = 0; 

		////////////////////////////////////////////////////////////////////////////////////

        // �õ�������������
        virtual	UInt	            getBatchCount() = 0;
        // �õ��ϴ�fps
        virtual	Flt	                getLastFPS() = 0;
        // �õ�ƽ��fps
        virtual	Flt	                getLastAverageFPS() = 0;
        // �õ�������
        virtual	UInt                getTriangleCount() = 0;
        
        ///////////////////////////////////////////////////////////////////////////////////

        // ������Ӱ
        virtual	void	            setShadowType(ShadowType level) = 0;
        virtual	ShadowType          getShadowType() = 0;

        // ������Ӱ����
        virtual	void	            setShadowParameter( Vec4 parameter ) = 0;
        virtual	Vec4             	getShadowParameter() = 0;

        ///////////////////////////////////////////////////////////////////////////////////

        // ������Ч
        virtual	void	            setFogLevel(FogLevel level, Color color = ColorSet::white(), Flt expDensity=0.002, Flt linearStart=0, Flt linearEnd=1000) = 0;
        virtual	FogLevel            getFogLevel() = 0;
        virtual	Color               getFogColor() = 0;
        virtual	Flt                 getFogExpDensity() = 0;
        virtual	Flt                 getFogLinearStart() = 0;
        virtual	Flt                 getFogLinearEnd() = 0;

        ///////////////////////////////////////////////////////////////////////////////////

        // ����λ����ͼ�͸߹���ͼ����
        virtual	void	            setScaleBiasSpecular(Vec4 sbs) = 0;
        virtual	Vec4                getScaleBiasSpecular() = 0;

        // ����Gamma
        virtual	void	            setGammaEnabled(Bool enable)= 0;
        virtual	Bool                getGammaEnabled() = 0;

		// ����FSAA
		virtual	void	            setFSAA(U32 fsaa, Str fsaaHint) = 0;
		virtual	U32					getFSAA() = 0;
		virtual Str					getFSAAHint() = 0;
		virtual Bool				getFSAAList(std::vector<std::pair<U32, Str>>& outFsaaList) = 0;


        // ����vsync
        virtual	void	            setVsync(Bool enable) = 0;
        virtual	Bool                getVsync() = 0;

        // ����VSyncInterval
        virtual	void	            setVsyncInterval(UInt interval) = 0;
        virtual	Int                 getVsyncInterval() = 0;

        // �����߿�ģʽ
        virtual	void	            setWireframeMode( Bool enable ) = 0;
        virtual	Bool             	getWireframeMode() = 0;

        ///////////////////////////////////////////////////////////////////////////////////

		// �����ʾ
		virtual void				setEntityVisible( Bool visible, Bool immediately = false ) = 0;
		virtual Bool				getEntityVisible() = 0;

        // ����ʵ���Ƿ�ʹ�÷�����ͼ
        virtual	void	            setEntityNormalMapEnable(Bool enable) = 0;
        virtual	Bool                getEntityNormalMapEnable() = 0;

        // ����ʵ���Ƿ�ʹ�ø߹��AO��ͼ
        virtual	void	            setEntitySaMapEnable(Bool enable) = 0;
        virtual	Bool                getEntitySaMapEnable() = 0;

        // ����ʵ���Ƿ�ʹ�ù�����ͼ
        virtual	void	            setEntityLightingMapEnable(Bool enable) = 0;
        virtual	Bool                getEntityLightingMapEnable() = 0;

        // �����Ƿ�ʵ����ܶ�̬����
        virtual	void	            setEntityReceiveDynamicShadowsEnabled(Bool enable) = 0;
        virtual	Bool                getEntityReceiveDynamicShadowsEnabled() = 0;

        ///////////////////////////////////////////////////////////////////////////////////

        // ����ʵ�����Ƿ�ʹ�÷�����ͼ
        virtual	void	            setEntityGroupNormalMapEnable(Bool enable) = 0;
        virtual	Bool                getEntityGroupNormalMapEnable() = 0;

        // ����ʵ�����Ƿ�ʹ�ø߹��AO��ͼ
        virtual	void	            setEntityGroupSaMapEnable(Bool enable) = 0;
        virtual	Bool                getEntityGroupSaMapEnable() = 0;

        ///////////////////////////////////////////////////////////////////////////////////

		// ˮ����ʾ
		virtual	void				setTerrainWaterVisible( Bool visible, Bool immediately = false ) = 0;
		virtual Bool				getTerrainWaterVisible() = 0;

		///////////////////////////////////////////////////////////////////////////////////

        // ����������ʾ
        virtual	void	            setTerrainGridsVisible( Bool visible ) = 0;
        virtual	Bool             	getTerrainGridsVisible() = 0;

        // ����Mipmapƫ����
        virtual	void	            setTerrainMipmapBias( Flt bias) = 0;
        virtual	Flt             	getTerrainMipmapBias() = 0;

        // ���õ��β���
        virtual	void	            setTerrainLightingParameter( Vec4 parameter ) = 0;
        virtual	Vec4             	getTerrainLightingParameter() = 0;

        // ������ʾ����
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