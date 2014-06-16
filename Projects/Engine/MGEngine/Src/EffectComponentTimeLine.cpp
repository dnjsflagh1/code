#include "stdafx.h"
#include "EffectComponentTimeLine.h"
#include "EffectXmlSerializer.h"
#include "EffectComponent.h"
#include "IEffectEvent.h"

namespace MG
{
	EffectComponentTimeLine::EffectComponentTimeLine( EffectComponent* effect, TimeList& timelist, Flt totaltime, BOOL loop)
		: mComponent(effect)
		, mTimeList(timelist)
		, mTotalTime(totaltime)
		, mbLoop(loop)
		, mStartDelta(0)
		, mIsStart(false)
		, mIsStarted(false)
		, mIsTimePassThought(false)
	{

	}

	EffectComponentTimeLine::~EffectComponentTimeLine()
	{
		
	}

	void EffectComponentTimeLine::start()
	{
		mStartDelta = 0;
		mIsStart = true;
		mIsStarted = true;
		mTimeList = mComponent->getTimeEventMap();

		// 总时间为0的时候,所有事件start一次.销毁由事件自己控制
		if (mTotalTime == 0)
		{
			TimeList::iterator iter = mTimeList.begin();
			for ( ; iter != mTimeList.end(); iter++)
			{
				(*iter)->start();
				mRunTimeEventlist.push_back(*iter);
			}
		}
	}

	void EffectComponentTimeLine::pause()
	{

	}

	void EffectComponentTimeLine::stop()
	{
		mStartDelta = 0;
		mIsStart = false;

		mOriginalTimeList = mComponent->getTimeEventMap();
		// 停止发生的所有事件
		std::list<IEffectEvent*>::iterator eventIter = mOriginalTimeList.begin();
		for ( ; eventIter != mOriginalTimeList.end(); eventIter++)
		{
			(*eventIter)->stop();
		}
	}

	void EffectComponentTimeLine::update( Flt delta )
	{
		if ( mIsStart )
		{
			mStartDelta += delta;
			setTime(mStartDelta);

			if (mbLoop)
			{
				if ( mStartDelta >= mTotalTime )
				{
					mStartDelta = 0;
					mTimeList = mComponent->getTimeEventMap();
				}
			}
			else
			{
				if ((mStartDelta > mTotalTime) && (mTotalTime != 0))
				{
					mIsTimePassThought = true;
					stop();
				}
			}

			// 遍历运行时激活Event队列.然后更新
			std::list<IEffectEvent*>::iterator eventIter = mRunTimeEventlist.begin();
			for ( ; eventIter != mRunTimeEventlist.end(); eventIter++)
			{
				(*eventIter)->update(delta);
			}

		}

	}

	// 遍历时间事件map.如果到了时间点,把event放到当前运行激活队列里.
	// 然后从时间事件map里删除.
	void EffectComponentTimeLine::setTime(Flt timing)
	{
		if (mTimeList.size() > 0)
		{
			TimeList::iterator iter = mTimeList.begin();
			for ( ; iter != mTimeList.end(); iter++)
			{
				if (timing >= (*iter)->getEventTimePoint())
				{
					IEffectEvent* event = *iter;
					event->start();
					mRunTimeEventlist.push_back(event);
			
					mTimeList.erase(iter);
					if (mTimeList.size() > 0)
					{
						iter = mTimeList.begin();
					}
					else
						break;
				}

			}
		}

	}

	ISceneNode* EffectComponentTimeLine::getSceneNode()
	{
		if (mComponent)
			return mComponent->getSceneNode();
		else
			return NULL;
	}

	void EffectComponentTimeLine::setPeriodTime( Flt totaltime )
	{
		mTotalTime = totaltime;
	}

	MG::Flt EffectComponentTimeLine::getPeriodTime()
	{
		return mTotalTime;
	}

	void EffectComponentTimeLine::setCurrentTime( Flt curtime )
	{
		mCurrentTime = curtime;
	}

	MG::Flt EffectComponentTimeLine::getCurrentTime()
	{
		return mCurrentTime;
	}

	void EffectComponentTimeLine::setIsLoop( Bool loop )
	{
		mbLoop = loop;
	}

	MG::Bool EffectComponentTimeLine::getIsLoop()
	{
		return mbLoop;
	}

	Bool EffectComponentTimeLine::isStarted()
	{
		return mIsStarted;
	}

	Bool EffectComponentTimeLine::isRunTimeListEmpty()
	{
		return mRunTimeEventlist.size()==0 ? true:false;
	}

	Bool EffectComponentTimeLine::isTimeLinePassThought()
	{
		return mIsTimePassThought;
	}
}