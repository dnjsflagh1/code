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
	//��Ϸ���ù�����
	/******************************************************************************/

	// ������
	class GameSettingManagerListener
	{
	public:

		// ����ʾ���÷����仯
		virtual		void onApplyDisplayConfig(){};

		// ���������÷����仯
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

        // ��ʼ����������
        Bool configSetting( IEngineMain* engineMain );

	public:

		//��ø�ϵͳ�ĳ�ʼ������
		Bool restoreInitConfig();
		//��ó�ʼ�����֮�� �����豸��״̬
		Bool resetInitConfig();
		//���ø�ϵͳ�ڳ�ʼ��֮�������޸ĵ�����
		void restoreRuningConfig();
		//��������ϵͳ���õ�INI�ļ�
		void saveConfig();

		//�������ĳ�ʼ������
		EngineInitConfig* getEngineInitConfig() { return mEngineInitConfig; }
	
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//��������
		///////////////////////////////////////////////////////////////////////////////////////
		//����������Ч
		void	applyAllAudioConfig();
        void    applyBGMEnable();
		//�Ƿ�������
		Bool	getAudioEnable(Bool& enable);
		void	setAudioEnable(Bool	enable);

		Bool	getBGMEnable(Bool& enable);
		void	setBGMEnable(Bool enable);

		///////////////////////////////////////////////////////////////////////////////////////
		//ͼ����ʾ����
		///////////////////////////////////////////////////////////////////////////////////////

		// ��ӦӲ������
        void	applyHardwareConfig();
        // ��Ӧ��ʾ����
        void	applyDisplayConfig( Bool isImme );


		//�ֱ�����Ϣ, ȫ��Ļ��Ϣ
		Bool	getVideoModeList(std::vector<VecI2>& reslist);
		Bool	getVideoMode(Bool& isFullScreen, U32& width, U32& height);
		void	setVideoMode(Bool isFullScreen, U32 width, U32 height);

		//���ÿ���ݱ���
		Bool	getFSAAList(std::vector<FSAA_MODE>& fsaa_list);
		Bool	getFSAA(Str16& szFsaa, Str16& szFsaaHint);
		Bool	getFSAA(U32& fsaa, Str8& fsaaHint );
		void	setFSAA(Str16 szFsaa, Str16 szFsaaHint);
		void	setFSAA(U32 fsaa, Str8 szFsaaHint);

		//����Ч���ȼ�
		Bool	getPostFx(post_fx_level& level);
		void	setPostFx(post_fx_level level);

		//��Ӱ�ȼ�
		Bool	getShadowLevel(shadow_level& level);
		void	setShadowLevel(shadow_level level);

		//����Ʒ��
		Bool	getMaterialLevel(material_level& level);
		void	setMaterialLevel(material_level level);
		
		//����Ʒ��
		Bool	getParticleLevel(particle_level& level);
		void	setParticleLevel(particle_level level);

		//�Ƿ���ˮ�浹Ӱ
		Bool	getUseWaterReflection(Bool& isWaterReflection);
		void	setUseWaterReflection(Bool isWaterReflection);
		
		//�Ƿ�ʹ�ø�ģ
		Bool	getUseHighLevelModel(Bool& isUseHighLevelModel);
		void	setUseHighLevelModel(Bool isUseHighLevelModel);

		//�Ƿ�ʹ�ø߾�����ͼ
		Bool	getUseHighLevelTexture(Bool& isUseHighLevelTexture);
		void	setUseHighLevelTexture(Bool isUseHighLevelTexture);
		
		//�Ƿ���ʾ����ϸ�����
		Bool	getUseDetailTerrainObject(Bool& isUseDetailTerrainObject);
		void	setUseDetailTerrainObject(Bool isUseDetailTerrainObject);
		
		//��ֱͬ��
		Bool	getVsync(Bool& isVsync);
		void	setVsync(Bool isVsync);

		//������Ϸ����
		Str8	getTrueFontName();
		void	setTrueFontName(Str8 fontName);

        //�õ�������Ϣ
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
		//��Ƶ����
		//////////////////////////////////////////////////////////////////////////////////////

		void	applyAudioEnable();

		
		//////////////////////////////////////////////////////////////////////////////////////
		//ͼ����ʾ����
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
		// ����������
		//////////////////////////////////////////////////////////////////////////////////////

		void	addListener(Str name, GameSettingManagerListener* listener);

		void	removeListener(Str name);

		void	removeAllListeners();

	private:

		//////////////////////////////////////////////////////////////////////////////////////
		// �������¼�
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