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

		// ��ʱ��Ϊ0��ʱ��,�����¼�startһ��.�������¼��Լ�����
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
		// ֹͣ�����������¼�
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

			// ��������ʱ����Event����.Ȼ�����
			std::list<IEffectEvent*>::iterator eventIter = mRunTimeEventlist.begin();
			for ( ; eventIter != mRunTimeEventlist.end(); eventIter++)
			{
				(*eventIter)->update(delta);
			}

		}

	}

	// ����ʱ���¼�map.�������ʱ���,��event�ŵ���ǰ���м��������.
	// Ȼ���ʱ���¼�map��ɾ��.
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