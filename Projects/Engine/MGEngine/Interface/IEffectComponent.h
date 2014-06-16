/******************************************************************************/
#ifndef _IEFFECTCOMPONENT_H_
#define _IEFFECTCOMPONENT_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "ISceneObject.h"

/******************************************************************************/

namespace MG
{
	typedef std::list<IEffectEvent*> TimeList;
	typedef std::map<Str8, IPUEffect*> PUEffectMap;
	typedef std::map<Str8, IEntity*> EntityMap;
	/******************************************************************************/
	//特效实体接口
	/******************************************************************************/
	class IEffectComponent : public ISceneObject
	{
	public:

		/// 开始一个特效
		virtual void start() = NULL;

		virtual void setScale(Vec3 scale) = NULL;

		virtual Bool initialised() = NULL;

		virtual U32	 getEffectResourceID() = NULL;

		/// 创建PU特效
		virtual IPUEffect*					createPUEffect(CChar* templateName, Str name = "") = NULL;
		/// 创建PU特效
		virtual IPUEffect*					createPUEffect(U32 effectResID, Str name = "") = NULL;
		/// 根据名字返回PU对象
		virtual IPUEffect*					getPUEffect(const Str8& puName) = NULL;
		/// 返回pu对象map
		virtual PUEffectMap					getPUEffectMap() = NULL;
		/// 销毁PU特效
		virtual void						destroyPUEffect(const Str8& puName) = NULL;
		/// 销毁所有PU特效
		virtual void						destroyAllPUEffect() = NULL;
		/// 获得PU在Component里的名字
		virtual Str							getEffectName(IPUEffect* effect) = NULL;

		/// 创建模型
		virtual IEntity*					createModelEffect(U32 resID, Str name = "") = NULL;
		/// 创建外部模型		
		virtual IEntity*					createSlotModelEffect(U32 resID) = NULL;
		/// 根据名字返回实体对象
		virtual IEntity*					getModelEffect(const Str8& entityName) = NULL;
		/// 返回实体对象列表
		virtual EntityMap					getModelEffectMap() = NULL;
		/// 根据名字返回槽位实体对象
		virtual IEntity*					getSlotModelEffect(const Str8& entityName) = NULL;
		/// 销毁模型
		virtual void						destroyModelEffect(const Str8& entityName) = NULL;
		/// 销毁所有模型
		virtual void						destroyAllModelEffect() = NULL;
		/// 获得模型在Component里的名字
		virtual Str							getModelName(IEntity* entity) = NULL;

		/// 设置绑定槽位和指针
		virtual void						setBindSlot(U32 slotindex, IEntity* bindEntity) = NULL;

		/// 获得时间轴
		virtual IEffectComponentTimeLine*	getTimeLine() = NULL;
		/// 获取特效文件解析器
		virtual IEffectXmlSerializer*		getEffectXmlSerializer() = NULL;

		/// 创建事件
		virtual IEffectEvent*				createEffectEvent(const Str& eventname, Flt timePoint) = NULL;
		/// 获得事件
		virtual IEffectEvent*				getEffectEvent(const Str& eventname) = NULL;
		/// 获取事件列表
		virtual	TimeList					getTimeEventList() = NULL;
		/// 销毁事件
		virtual void						destroyEffectEvent(const Str& eventname) = NULL;

	};

}

/******************************************************************************/
#endif