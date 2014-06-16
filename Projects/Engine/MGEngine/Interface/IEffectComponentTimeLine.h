/******************************************************************************/
#ifndef _IEFFECTCOMPONENT_TIMELINE_H_
#define _IEFFECTCOMPONENT_TIMELINE_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "ISceneObject.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//��Чʱ���߽ӿ�
	/******************************************************************************/
	class IEffectComponentTimeLine : public ISceneObject
	{
	public:
		// ����ʱ��
		virtual void setTime(Flt timing) = NULL;
		// ��ʼ
		virtual void start() = NULL;
		// ��ͣ
		virtual void pause() = NULL;
		// ����
		virtual void stop() = NULL;
		// ����
		virtual void update(Flt delta) = NULL;

		// ��ʱ��
		virtual void setPeriodTime(Flt totaltime) = NULL;
		virtual Flt getPeriodTime() = NULL;

		// ��ǰʱ��
		virtual void setCurrentTime(Flt curtime) = NULL;
		virtual Flt getCurrentTime() = NULL;

		// �Ƿ�ѭ��
		virtual void setIsLoop(Bool loop) = NULL;
		virtual Bool getIsLoop() = NULL;
	};

}

/******************************************************************************/
#endif