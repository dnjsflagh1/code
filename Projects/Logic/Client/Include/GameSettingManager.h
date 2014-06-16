#ifndef _GAME_SETTING_MANAGER_H
#define _GAME_SETTING_MANAGER_H
/******************************************************************************/
#include "ClientPreqs.h"
#include "IEngineMain.h"
#include "OgreExternalInterface.h"
/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//游戏配置管理器
	/******************************************************************************/

	// 监听器
	class GameSettingManagerListener
	{
	public:

		// 当显示设置发生变化
		virtual		void onApplyDisplayConfig(){};

		// 当声音设置发生变化
		virtual		void onApplyAudioConfig(){};
	};

	class GameSettingManager
	{
	public:

		struct FSAA_MODE
		{
			Str16 FSAA_SAMPLE;
			Str16 FSAA_HINT;
		};
		
		enum post_fx_level
		{
			POST_FX_NONE = 0,
			POST_FX_LOW,
			POST_FX_MID,
			POST_FX_HIGH,
		};

		enum shadow_level
		{
			SHADOW_LEVEL_NONE = 0,
			SHADOW_LEVEL_LOW,
			SHADOW_LEVEL_MID,
			SHADOW_LEVEL_HIGH,
		};

		enum particle_level
		{
			PARTICLE_LEVEL_LOW = 0,
			PARTICLE_LEVEL_MID,
			PARTICLE_LEVEL_HIGH,
		};

		enum material_level
		{
			MATERIAL_LEVEL_LOW = 0,
			MATERIAL_LEVEL_MID,
			MATERIAL_LEVEL_HIGH,
			MATERIAL_LEVEL_MAX,
		};

	public:

		GameSettingManager();
		~GameSettingManager();
		SINGLETON_INSTANCE(GameSettingManager)

		// MG_CN_MODIFY
		Bool initialize(CChar16* configFileName);

        // 初始化调试配置
        Bool configSetting( IEngineMain* engineMain );

	public:

		//获得各系统的初始化配置
		Bool restoreInitConfig();
		//获得初始化完成之后， 各个设备的状态
		Bool resetInitConfig();
		//设置各系统在初始化之后，所需修改的配置
		void restoreRuningConfig();
		//保存所有系统配置到INI文件
		void saveConfig();

		//获得引擎的初始化配置
		EngineInitConfig* getEngineInitConfig() { return mEngineInitConfig; }
	
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//声音设置
		///////////////////////////////////////////////////////////////////////////////////////
		//所有配置生效
		void	applyAllAudioConfig();
        void    applyBGMEnable();
		//是否开启声音
		Bool	getAudioEnable(Bool& enable);
		void	setAudioEnable(Bool	enable);

		Bool	getBGMEnable(Bool& enable);
		void	setBGMEnable(Bool enable);

		///////////////////////////////////////////////////////////////////////////////////////
		//图形显示设置
		///////////////////////////////////////////////////////////////////////////////////////

		// 响应硬件配置
        void	applyHardwareConfig();
        // 响应显示配置
        void	applyDisplayConfig( Bool isImme );


		//分辨率信息, 全屏幕信息
		Bool	getVideoModeList(std::vector<VecI2>& reslist);
		Bool	getVideoMode(Bool& isFullScreen, U32& width, U32& height);
		void	setVideoMode(Bool isFullScreen, U32 width, U32 height);

		//设置抗锯齿倍数
		Bool	getFSAAList(std::vector<FSAA_MODE>& fsaa_list);
		Bool	getFSAA(Str16& szFsaa, Str16& szFsaaHint);
		Bool	getFSAA(U32& fsaa, Str8& fsaaHint );
		void	setFSAA(Str16 szFsaa, Str16 szFsaaHint);
		void	setFSAA(U32 fsaa, Str8 szFsaaHint);

		//后期效果等级
		Bool	getPostFx(post_fx_level& level);
		void	setPostFx(post_fx_level level);

		//阴影等级
		Bool	getShadowLevel(shadow_level& level);
		void	setShadowLevel(shadow_level level);

		//材质品质
		Bool	getMaterialLevel(material_level& level);
		void	setMaterialLevel(material_level level);
		
		//粒子品质
		Bool	getParticleLevel(particle_level& level);
		void	setParticleLevel(particle_level level);

		//是否开启水面倒影
		Bool	getUseWaterReflection(Bool& isWaterReflection);
		void	setUseWaterReflection(Bool isWaterReflection);
		
		//是否使用高模
		Bool	getUseHighLevelModel(Bool& isUseHighLevelModel);
		void	setUseHighLevelModel(Bool isUseHighLevelModel);

		//是否使用高精度贴图
		Bool	getUseHighLevelTexture(Bool& isUseHighLevelTexture);
		void	setUseHighLevelTexture(Bool isUseHighLevelTexture);
		
		//是否显示地形细致物件
		Bool	getUseDetailTerrainObject(Bool& isUseDetailTerrainObject);
		void	setUseDetailTerrainObject(Bool isUseDetailTerrainObject);
		
		//垂直同步
		Bool	getVsync(Bool& isVsync);
		void	setVsync(Bool isVsync);

		//设置游戏字体
		Str8	getTrueFontName();
		void	setTrueFontName(Str8 fontName);

        //得到调试信息
        Bool	isDebugNoTerrain();
        Bool	isDebugNoWater();
        Bool	isDebugNoSpeedTree();
		Bool	isDebugNoSpeedGrass();
        Bool	isDebugNoStaticEntity();
        Bool	isDebugNoStaticEffect();
        Bool	isDebugNoEntity();
        Bool	isDebugNoBuilding();
        Bool	isDebugNoNpc();
        Bool	isDebugNoItem();
        Bool	isDebugShowBlock();

	private:

		//////////////////////////////////////////////////////////////////////////////////////
		//音频设置
		//////////////////////////////////////////////////////////////////////////////////////

		void	applyAudioEnable();

		
		//////////////////////////////////////////////////////////////////////////////////////
		//图形显示设置
		//////////////////////////////////////////////////////////////////////////////////////

        void	applyVideoMode();
        void	applyFullScreen();
        void	applyVsync();
		void	applyFSAA();

		void	applyPostFx();
		void	applyShadowLevel();
		void	applyMaterialLevel();
		void	applyFog();

		void	applyParticleLevel();
		void	applyUseWaterReflection();
		void	applyUseHighLevelModel();
		void	applyUseHighLevelTexture();
		void	applyUseDetailTerrainObject();


	private:

		Bool	restoreEngineInitConfig();

		Str16	toFSAAIniInfo(Str16 fsaa, Str16 fsaaHint);
		void	fromFSAAIniInfo(const Str16& fsaaInfo, Str16 &outFsaa, Str16 &outFsaaHint);

	public:

		//////////////////////////////////////////////////////////////////////////////////////
		// 监听器管理
		//////////////////////////////////////////////////////////////////////////////////////

		void	addListener(Str name, GameSettingManagerListener* listener);

		void	removeListener(Str name);

		void	removeAllListeners();

	private:

		//////////////////////////////////////////////////////////////////////////////////////
		// 监听器事件
		//////////////////////////////////////////////////////////////////////////////////////

		void	notifyApplyDisplayConfig();

		void	notifyApplyAudioConfig();
		
	private:

		Bool	mIsLoad;

		EngineInitConfig* mEngineInitConfig;

		std::map<Str, GameSettingManagerListener*> mListeners;
	};
}

/******************************************************************************/
#endif