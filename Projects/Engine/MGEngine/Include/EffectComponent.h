/******************************************************************************/
#ifndef _EFFECTCOMPONENT_H_
#define _EFFECTCOMPONENT_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "EnginePreqs.h"
#include "IEffectComponent.h"
#include "ILogicBinder.h"
#include "OgreEntity.h"
#include "ParticleUniverseSystemManager.h"
#include "MGSceneNode.h"
#include "PUEffect.h"
#include "Entity.h"
#include "EffectComponentTimeLine.h"
/******************************************************************************/
namespace MG
{
	typedef std::map<U32, IEntity*> SlotEntityMap;
	/******************************************************************************/
	//特效实体对象
	/******************************************************************************/
	class EffectComponent : public IEffectComponent
	{
		friend class Scene;

	public:
		EffectComponent(CChar* name, Scene* scene);
		EffectComponent(CChar* entityName, U32 effectResID, Scene* scene, Bool isAutoDestroy,Bool isAutoStart);
		EffectComponent(CChar* entityName, CChar* fullfilename, Scene* scene, Bool isAutoDestroy,Bool isAutoStart);
		virtual ~EffectComponent();

		///// 得到类型
		virtual SceneObjectTypes			getType();
		///// 得到空间节点
		virtual ISceneNode*					getSceneNode();
		/// 是否创建成功
		virtual Bool						initialised();


		/// 开始一个特效
		virtual void						start();

		/// 设置下大小
		virtual void						setScale( Vec3 scale );

		virtual U32							getEffectResourceID() { return mEffectResID; }

	public:
		/// 创建PU特效
		virtual PUEffect*					createPUEffect(CChar* templateName, Str name = "");
		/// 创建PU特效
		virtual PUEffect*					createPUEffect(U32 effectResID, Str name = "");
		/// 根据名字返回PU对象
		virtual PUEffect*					getPUEffect(const Str8& puName);
		/// 返回pu对象map
		virtual PUEffectMap					getPUEffectMap();
		/// 销毁PU特效
		virtual void						destroyPUEffect(const Str8& puName);
		/// 销毁所有PU特效
		virtual void						destroyAllPUEffect();
		/// 获得PU在Component里的名字
		virtual Str							getEffectName(IPUEffect* effect);

		/// 创建模型
		virtual Entity*						createModelEffect(U32 resID, Str name = "");
		/// 创建外部模型(编辑器使用)
		virtual Entity*						createSlotModelEffect(U32 resID);
		/// 根据名字返回实体对象
		virtual Entity*						getModelEffect(const Str8& entityName);
		/// 返回实体对象列表
		virtual EntityMap					getModelEffectMap();
		/// 根据名字返回槽位实体对象(编辑器使用)
		virtual Entity*						getSlotModelEffect(const Str8& entityName);
		/// 销毁模型
		virtual void						destroyModelEffect(const Str8& entityName);
		/// 销毁所有模型
		virtual void						destroyAllModelEffect();
		/// 获得模型在Component里的名字
		virtual Str							getModelName(IEntity* entity);

		/// 设置绑定槽位和指针(客户端使用)
		virtual void						setBindSlot(U32 slotindex, IEntity* bindEntity);

		/// 获得时间轴
		virtual EffectComponentTimeLine*	getTimeLine();

		/// 创建事件
		virtual IEffectEvent*				createEffectEvent(const Str& eventname, Flt timePoint);
		/// 获得事件
		virtual IEffectEvent*				getEffectEvent(const Str& eventname);
		/// 获取事件列表
		virtual	TimeList					getTimeEventList();
		/// 销毁事件
		virtual void						destroyEffectEvent(const Str& eventname);

		virtual Scene*						getScene() { return mScene; }

		virtual IEffectXmlSerializer*		getEffectXmlSerializer();
	public:
		/// 返回时间事件列表
		TimeList&							getTimeEventMap(){ return mTimeList; }

		/// 获取槽位实体(客户端里使用)
		IEntity*								getSlotEntity(U32 index);
	protected:

		/// 加载Effect文件
		void								loadEffectFile(U32 effectResID);
		
		void								loadEffectFile(CChar* fullfilename);

		/// 更新
		virtual Bool						update( Flt delta );

	protected:
		///节点对象
		MGSceneNode*						mSceneNode;
		/// 所属场景对象
		Scene*								mScene;
		/// 是否自动开始
		Bool								mIsAutoStart;
		/// 是否自动销毁
		Bool								mIsAutoDestroy;
		/// 特效资源模版号
		U32									mEffectResID;
		/// 特效文件完整路径
		Str									mEffectFullPath;

		//////////////////////////////////////////////////////////////////////////

		/// 用map存,Event要用名字来找对象
		/// PU粒子对象
		PUEffectMap							mPUEffectList;
		/// 内部模型对象
		EntityMap							mEntityList;
		/// 时间事件表
		TimeList							mTimeList;
		/// 特效解析类
		EffectXmlSerializer*				mEffectSerialzer;
		//EffectComponentSerialization*		mEffectSerialzer;
		/// 时间类
		EffectComponentTimeLine*			mEffectComponentTimeLine;

		/// 绑定的槽位和对象map
		SlotEntityMap						mSlotEntityMap;
	private:
		/// 实体名字
		NameGenerator						mEntityNameGenerator;
		/// 实体名字
		NameGenerator						mPUNameGenerator;
	};

}

/******************************************************************************/

#endif
