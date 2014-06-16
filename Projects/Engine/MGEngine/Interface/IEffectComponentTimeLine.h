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
	//特效时间线接口
	/******************************************************************************/
	class IEffectComponentTimeLine : public ISceneObject
	{
	public:
		// 设置时间
		virtual void setTime(Flt timing) = NULL;
		// 开始
		virtual void start() = NULL;
		// 暂停
		virtual void pause() = NULL;
		// 结束
		virtual void stop() = NULL;
		// 更新
		virtual void update(Flt delta) = NULL;

		// 总时间
		virtual void setPeriodTime(Flt totaltime) = NULL;
		virtual Flt getPeriodTime() = NULL;

		// 当前时间
		virtual void setCurrentTime(Flt curtime) = NULL;
		virtual Flt getCurrentTime() = NULL;

		// 是否循环
		virtual void setIsLoop(Bool loop) = NULL;
		virtual Bool getIsLoop() = NULL;
	};

}

/******************************************************************************/
#endif