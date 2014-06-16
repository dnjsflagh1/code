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
		// ����ʱ��
		virtual void setTime(Flt timing);
		// ��ʼ
		virtual void start();
		// ��ͣ
		virtual void pause();
		// ����
		virtual void stop();
		// ����
		virtual void update(Flt delta);
	public:
		// ��ʱ��
		virtual void setPeriodTime(Flt totaltime);
		virtual Flt	 getPeriodTime();

		// ��ǰʱ��
		virtual void setCurrentTime(Flt curtime);
		virtual Flt  getCurrentTime();

		// �Ƿ�ѭ��
		virtual void setIsLoop(Bool loop);
		virtual Bool getIsLoop();

		// �Ƿ�ʼ��
		Bool		 isStarted();

		// �����¼��б����Ƿ�Ϊ��
		Bool		 isRunTimeListEmpty();
		// ʱ�����Ƿ�����.
		Bool		 isTimeLinePassThought();
	private:
		// �Ƿ�ʼ��
		Bool						mIsStarted;
		// �Ƿ�ʱ��������
		Bool						mIsTimePassThought;
		// �Ƿ�ʼ
		Bool						mIsStart;
		// �ۼ�ʱ��
		Flt							mStartDelta;

		Flt							mTotalTime;
		Flt							mCurrentTime;
		BOOL						mbLoop;

		std::list<IEffectEvent*>	mRunTimeEventlist;
		TimeList					mTimeList;
		EffectComponent*			mComponent;

		// ԭʼ�������¼��б�.����ʱ����ֹͣ�����رղ�����.
		TimeList					mOriginalTimeList;
	};
};

#endif