/******************************************************************************/
#ifndef _EFFECTEVENT_FACTORY_H_
#define _EFFECTEVENT_FACTORY_H_
/******************************************************************************/
#include "IEffectEvent.h"
#include "ModelEffectEvent.h"
#include "PUEffectEvent.h"
#include "WeaponLightEvent.h"
#include "EffectFadeEvent.h"

namespace MG
{
	static NameGenerator mModel_VisibleGenerator("Model_Visible");
	static NameGenerator mModel_AnimationGenerator("Model_Animation");
	static NameGenerator mModel_BindGenerator("Model_Bind");
	static NameGenerator mPU_StartGenerator("PU_Start");
	static NameGenerator mPU_StopGenerator("PU_Stop");
	static NameGenerator mPU_BindGenerator("PU_Bind");
	static NameGenerator mWeapon_LightGenerator("Weapon_Light");
	static NameGenerator mEffect_FadeGenerator("Effect_Fade");
	static Int nCount = 0;
	/***************************************************************/
	// 特效事件工厂
	/***************************************************************/
	class EffectEventFactory
	{
	public:
		SINGLETON_INSTANCE(EffectEventFactory)
		EffectEventFactory(){}
		virtual ~EffectEventFactory() {}
	
		IEffectEvent *createInstance( const Str8& eventname, Flt timepoint, EffectComponent* controller) 
		{
			while( nCount++<1000 )
			{
				if (eventname == "Model_Visible")
				{
					name = mModel_VisibleGenerator.generate();
					return MG_NEW ModelVisibleEffectEvent(name, eventname, timepoint, controller);
				}
				else if (eventname == "Model_Animation")
				{
					name = mModel_AnimationGenerator.generate();
					return MG_NEW ModelAnimationEffectEvent(name, eventname, timepoint, controller);
				}
				else if (eventname == "Model_Bind")
				{
					name = mModel_BindGenerator.generate();
					return MG_NEW ModelBindEffectEvent(name, eventname, timepoint, controller);
				}
				else if (eventname == "PU_Start")
				{
					name = mPU_StartGenerator.generate();
					return MG_NEW PUStartEffectEvent(name, eventname, timepoint, controller);
				}
				else if (eventname == "PU_Stop")
				{
					name = mPU_StopGenerator.generate();
					return MG_NEW PUStopEffectEvent(name, eventname, timepoint, controller);
				}
				else if (eventname == "PU_Bind")
				{
					name = mPU_BindGenerator.generate();
					return MG_NEW PUBindEffectEvent(name, eventname, timepoint, controller);
				}
				else if (eventname == "Weapon_Light")
				{
					name = mWeapon_LightGenerator.generate();
					return MG_NEW WeaponLightEvent(name, eventname, timepoint, controller);
				}
				else if (eventname == "Effect_Fade")
				{
					name = mEffect_FadeGenerator.generate();
					return MG_NEW EffectFadeEvent(name, eventname, timepoint, controller);
				}

			}
			
			return NULL;
		}
		void destroyInstance( IEffectEvent* arch) { MG_DELETE(arch); }
	
	private:

		String		name;
	};


}

#endif