/******************************************************************************/
#ifndef _PU_EFFECT_H_
#define _PU_EFFECT_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IPUEffect.h"
#include "ParticleUniverseSystemManager.h"
/******************************************************************************/
namespace MG
{

	/******************************************************************************/
	//特效实体对象
	/******************************************************************************/
	class PUEffect : public IPUEffect
	{
		friend class Scene;

	public:

		PUEffect(CChar* PUName, CChar* effectTemplateName, Scene* scene,Bool isAutoDestroy = true, Bool isAutoStart = true);
		PUEffect(CChar* PUName, U32 effectResID, Scene* scene,Bool isAutoDestroy = true, Bool isAutoStart = true);
		virtual ~PUEffect();

		/// 得到类型
		virtual SceneObjectTypes        getType();
		/// 得到空间节点
		virtual MGSceneNode*            getSceneNode();
		/// 绑定到模型
		virtual Bool					bind(IEntity* entity, Bool attachToParent = false);
		/// 是否创建成功
		virtual Bool					initialised();


		/// 开始一个特效
		virtual void                    start();
		/// 停止一个特效
		virtual void					stop();

		/// 设置下大小
		virtual void					setScale( Vec3 scale );

		virtual U32						getEffectResourceID() { return mEffectResID; }

		virtual void					setTrailLength(U32 length);

		virtual void					setTrailWidth(U32 width);

		virtual void					setTrailLiveTime(Flt time);

		Scene*							getScene() { return mScene; }

		CChar*							getEffectTemplateName() { return mEffectTemplateName; }
	protected:
		/// 创建PU特效
		void                            createPUEffect(CChar* effectTemplateName, Bool isAutoStart);
		/// 创建PU特效
		void                            createPUEffect(U32 effectResID, Bool isAutoStart);
		/// 销毁PU特效
		void                            destroyPUEffect();

		/// 更新
		virtual Bool                    update( Flt delta );

	protected:

		///节点对象
		MGSceneNode* mSceneNode;
		/// 所属场景对象
		Scene* mScene;
		/// PU粒子对象
		ParticleUniverse::ParticleSystem* mPUParticleSystem;
		/// 是否自动销毁
		Bool mIsAutoDestroy;
		/// PU模板名字
		CChar* mEffectTemplateName;
		/// 特效资源模版号
		U32  mEffectResID;
		// 是否开始
		Bool mIsStart;
		// 累计时间
		Flt mStartDelta;
	};

}

/******************************************************************************/

#endif
