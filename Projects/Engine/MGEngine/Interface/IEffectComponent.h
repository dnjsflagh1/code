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
	//��Чʵ��ӿ�
	/******************************************************************************/
	class IEffectComponent : public ISceneObject
	{
	public:

		/// ��ʼһ����Ч
		virtual void start() = NULL;

		virtual void setScale(Vec3 scale) = NULL;

		virtual Bool initialised() = NULL;

		virtual U32	 getEffectResourceID() = NULL;

		/// ����PU��Ч
		virtual IPUEffect*					createPUEffect(CChar* templateName, Str name = "") = NULL;
		/// ����PU��Ч
		virtual IPUEffect*					createPUEffect(U32 effectResID, Str name = "") = NULL;
		/// �������ַ���PU����
		virtual IPUEffect*					getPUEffect(const Str8& puName) = NULL;
		/// ����pu����map
		virtual PUEffectMap					getPUEffectMap() = NULL;
		/// ����PU��Ч
		virtual void						destroyPUEffect(const Str8& puName) = NULL;
		/// ��������PU��Ч
		virtual void						destroyAllPUEffect() = NULL;
		/// ���PU��Component�������
		virtual Str							getEffectName(IPUEffect* effect) = NULL;

		/// ����ģ��
		virtual IEntity*					createModelEffect(U32 resID, Str name = "") = NULL;
		/// �����ⲿģ��		
		virtual IEntity*					createSlotModelEffect(U32 resID) = NULL;
		/// �������ַ���ʵ�����
		virtual IEntity*					getModelEffect(const Str8& entityName) = NULL;
		/// ����ʵ������б�
		virtual EntityMap					getModelEffectMap() = NULL;
		/// �������ַ��ز�λʵ�����
		virtual IEntity*					getSlotModelEffect(const Str8& entityName) = NULL;
		/// ����ģ��
		virtual void						destroyModelEffect(const Str8& entityName) = NULL;
		/// ��������ģ��
		virtual void						destroyAllModelEffect() = NULL;
		/// ���ģ����Component�������
		virtual Str							getModelName(IEntity* entity) = NULL;

		/// ���ð󶨲�λ��ָ��
		virtual void						setBindSlot(U32 slotindex, IEntity* bindEntity) = NULL;

		/// ���ʱ����
		virtual IEffectComponentTimeLine*	getTimeLine() = NULL;
		/// ��ȡ��Ч�ļ�������
		virtual IEffectXmlSerializer*		getEffectXmlSerializer() = NULL;

		/// �����¼�
		virtual IEffectEvent*				createEffectEvent(const Str& eventname, Flt timePoint) = NULL;
		/// ����¼�
		virtual IEffectEvent*				getEffectEvent(const Str& eventname) = NULL;
		/// ��ȡ�¼��б�
		virtual	TimeList					getTimeEventList() = NULL;
		/// �����¼�
		virtual void						destroyEffectEvent(const Str& eventname) = NULL;

	};

}

/******************************************************************************/
#endif