//*****************************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//*****************************************************************************************************************
namespace MG
{
	
	class UISystemSetting : public UIObject
	{
		
	public:
		UISystemSetting();
		~UISystemSetting();


		SINGLETON_INSTANCE(UISystemSetting);

		virtual void		setEvent();

		//
		virtual	Bool		openGui(); 
		virtual void        restore();

		//		
				void		restoreVideoSetting();
				void		applyVideoSetting();

				void		restoreAudioSetting();
				void		applyAudioSetting();

		//
				void        setSettingType(SysSettingType sysSetType);


	private:

				void		_setImageVisible(const Str8& name,Bool bVisiable);

	private:
		
		//
		static void			onClickBtnFunction(void* widget);
		static void			onClickBtnVideo(void* widget);
		static void			onClickBtnAudio(void* widget);
		static void			onClickBtnBtnNetWork(void* widget);

		void				_onClickBtnFunction();
		void				_onClickBtnVideo();
		void				_onClickBtnAudio();
		void				_onClickBtnBtnNetWork();
		
		//////////////////////////////////////////////////////////////////////////////////////////

		//video setting
		static void			onClickCheckBtnEnableFullScreen(void* widget);
		static void			onClickCheckBtnEnableVsync(void* widget);
		static void			onClickCheckBtnEnableWaterReflection(void* widget);
		static void			onClickCheckBtnEnableHighLevelModel(void* widget);
		static void			onClickCheckBtnEnableHighLevelTexture(void* widget);
		static void			onClickCheckBtnEnableHighLevelTerrainObject(void* widget);

		static void			onHScrollPostionSetPostFXLevel(void* widget, Int pos);
		static void			onHScrollPostionSetShadowLevel(void* widget, Int pos);
		static void			onHScrollPostionSetParticleLevel(void *widget, Int pos);
		static void			onHScrollPostionSetMaterialLevel(void *widget, Int pos);

		static void			onSelectCommoboxIndex(void* widget, Int index);

		static void			onClickBtnApplyVideo(void* widget);
		void				_onClickBtnApplyVideo();

		//////////////////////////////////////////////////////////////////////////////////////////

        //audio setting
        static void			onClickCheckBtnEnableBgSound(void* widget);
        static void         onClickCheckBtnEnableSilence(void* widget);
		//callback define

		//

		static void			onClickBtnApplyAudio(void* widget);
		void				_onClickBtnApplyAudio();

		//////////////////////////////////////////////////////////////////////////////////////////

	};


}