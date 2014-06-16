/******************************************************************************/
#ifndef _EFFECTCOMPONENT_TIMELINE_H_
#define _EFFECTCOMPONENT_TIMELINE_H_
/******************************************************************************/
#include "EnginePreqs.h"
#include "IEffectComponentTimeLine.h"

namespace MG
{
	typedef std::list<IEffectEvent*> TimeList;

	class EffectComponentTimeLine : public IEffectComponentTimeLine
	{
	public:
		EffectComponentTimeLine(EffectComponent* effect, TimeList& timelist, Flt totaltime, BOOL loop = FALSE);
		virtual ~EffectComponentTimeLine();
	public:
		virtual SceneObjectTypes getType() { return EOT_TIMELINE; };

		virtual ISceneNode* getSceneNode();
	public:
		// 设置时间
		virtual void setTime(Flt timing);
		// 开始
		virtual void start();
		// 暂停
		virtual void pause();
		// 结束
		virtual void stop();
		// 更新
		virtual void update(Flt delta);
	public:
		// 总时间
		virtual void setPeriodTime(Flt totaltime);
		virtual Flt	 getPeriodTime();

		// 当前时间
		virtual void setCurrentTime(Flt curtime);
		virtual Flt  getCurrentTime();

		// 是否循环
		virtual void setIsLoop(Bool loop);
		virtual Bool getIsLoop();

		// 是否开始过
		Bool		 isStarted();

		// 运行事件列表里是否为空
		Bool		 isRunTimeListEmpty();
		// 时间轴是否走完.
		Bool		 isTimeLinePassThought();
	private:
		// 是否开始过
		Bool						mIsStarted;
		// 是否时间走完了
		Bool						mIsTimePassThought;
		// 是否开始
		Bool						mIsStart;
		// 累计时间
		Flt							mStartDelta;

		Flt							mTotalTime;
		Flt							mCurrentTime;
		BOOL						mbLoop;

		std::list<IEffectEvent*>	mRunTimeEventlist;
		TimeList					mTimeList;
		EffectComponent*			mComponent;

		// 原始的完整事件列表.用于时间轴停止后做关闭操作的.
		TimeList					mOriginalTimeList;
	};
};

#endif