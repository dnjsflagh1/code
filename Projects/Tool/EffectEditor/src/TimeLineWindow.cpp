#include <QtGui>

#include "SlidersGroup.h"
#include "TimeLineWindow.h"
#include "AddEventDlg.h"

#include "Define.h"
#include "IEffectComponentTimeLine.h"
#include "CoreManager.h"

using namespace EffectEditor;

TimeLineWindow::TimeLineWindow(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent)
	, mHorizontalSliders(NULL)
	, mStackedWidget(NULL)
	, mControlsGroup(NULL)
	, mMaximumLabel(NULL)
	, mSetCurTimeValueLabel(NULL)
	, mLoopLabel(NULL)
	, mMaximumSpinBox(NULL)
	, mSetCurTimeSpinBox(NULL)
	, mBeginBtn(NULL)
	, mPauseBtn(NULL)
	, mStopBtn(NULL)
	, mAddEventBtn(NULL)
	, mLoopCheckBox(NULL)
	, mIsStart(false)
	, mbLoop(false)
	, mStartDelta(0.0f)
	, mCurrentTime(0.0f)
	, mTotalTime(10.0f)
{
    mHorizontalSliders = new SlidersGroup(Qt::Horizontal, tr("Horizontal"));

    mStackedWidget = new QStackedWidget;
    mStackedWidget->addWidget(mHorizontalSliders);

    createControls(tr("Controls"));

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(mControlsGroup);
    layout->addWidget(mStackedWidget);
    setLayout(layout);

    setWindowTitle(tr("Time Sliders"));
}

void TimeLineWindow::createControls(const QString &title)
{
    mControlsGroup = new QGroupBox(title);

    mMaximumLabel = new QLabel(tr("Max Time:"));
    mSetCurTimeValueLabel = new QLabel(tr("Set CurrentTime:"));

	mLoopLabel = new QLabel(tr("Loop:"));

	mBeginBtn = new QPushButton(tr("Start:"));
	mPauseBtn = new QPushButton(tr("Pause:"));
	mStopBtn = new QPushButton(tr("Stop:"));
	mAddEventBtn = new QPushButton(tr("AddEvent:"));

	mBeginBtn->setEnabled(true);
	mPauseBtn->setEnabled(false);
	mStopBtn->setEnabled(false);

	mLoopCheckBox = new QCheckBox(this);

    mMaximumSpinBox = new QSpinBox;
    mMaximumSpinBox->setRange(-100, 100);
    mMaximumSpinBox->setSingleStep(1);

    mSetCurTimeSpinBox = new QSpinBox;
    mSetCurTimeSpinBox->setRange(-100, 100);
    mSetCurTimeSpinBox->setSingleStep(1);

	// 最大时间 修改数值
	connect(mMaximumSpinBox, SIGNAL(valueChanged(int)),
		mHorizontalSliders, SLOT(setMaximum(int)));
	connect(mMaximumSpinBox, SIGNAL(valueChanged(int)),
		this, SLOT(periodTimeValueChanged(int)));

	// 当前时间 修改数值
	connect(mSetCurTimeSpinBox, SIGNAL(valueChanged(int)),
            mHorizontalSliders, SLOT(setValue(int)));
	connect(mSetCurTimeSpinBox, SIGNAL(valueChanged(int)),
			this, SLOT(currentTimeValueChanged(int)));

	// 当前时间 拉动时间轴
	connect(mHorizontalSliders, SIGNAL(valueChanged(int)),
		mSetCurTimeSpinBox, SLOT(setValue(int)));

	// update驱动,更新时间轴和当前时间点控件值
	connect(this, SIGNAL(setSlidersTime(int)),
		mSetCurTimeSpinBox, SLOT(setValue(int)));


	connect(mBeginBtn, SIGNAL(clicked()), this, SLOT(start()));
	connect(mPauseBtn, SIGNAL(clicked()), this, SLOT(pause()));
	connect(mStopBtn, SIGNAL(clicked()), this, SLOT(stop()));
	connect(mAddEventBtn, SIGNAL(clicked()), this, SLOT(addEvent()));
	connect(mLoopCheckBox, SIGNAL(stateChanged(int)), this, SLOT(setLoop(int)));

    QGridLayout *controlsLayout = new QGridLayout;
    controlsLayout->addWidget(mMaximumLabel, 0, 1);
    controlsLayout->addWidget(mSetCurTimeValueLabel, 1, 1);
	controlsLayout->addWidget(mLoopLabel, 2, 1);

    controlsLayout->addWidget(mMaximumSpinBox, 0, 2);
    controlsLayout->addWidget(mSetCurTimeSpinBox, 1, 2);
	controlsLayout->addWidget(mLoopCheckBox, 2, 2);

	controlsLayout->addWidget(mBeginBtn, 0, 0);
	controlsLayout->addWidget(mPauseBtn, 1, 0);
	controlsLayout->addWidget(mStopBtn, 2, 0);
	controlsLayout->addWidget(mAddEventBtn, 3, 0);
    mControlsGroup->setLayout(controlsLayout);

	mMaximumSpinBox->setValue(mTotalTime);
	mSetCurTimeSpinBox->setValue(mCurrentTime);
}

void TimeLineWindow::setMaxTimeNum( float maxtime )
{
	mMaximumSpinBox->setValue(maxtime);
}

void TimeLineWindow::setLoopBtnCheck( bool loop )
{
	mLoopCheckBox->setChecked(loop);
}

void TimeLineWindow::update( float delta )
{
	IScene* scene = CoreManager::getInstance().getScene();
	if (!scene)
		return;

	IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
	if (!component)
		return;

	IEffectComponentTimeLine *timeline =	
		component->getTimeLine();

	if (!timeline)
		return;

	if ( mIsStart )
	{
		if (timeline->getPeriodTime() != 0)
		{
			mStartDelta += delta;
			mCurrentTime = mStartDelta;
			setSlidersTime(mStartDelta);

			if (mbLoop)
			{
				if ( mStartDelta >= mTotalTime )
					mStartDelta = 0;
			}
			else
			{
				if ( mStartDelta > mTotalTime )
					stop();
			}
		}

	}
}

void TimeLineWindow::start()
{
	mStartDelta = 0;
	mIsStart = true;

	mBeginBtn->setEnabled(false);
	mStopBtn->setEnabled(true);

	IScene* scene = CoreManager::getInstance().getScene();
	if (!scene)
		return;

	IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
	if (!component)
		return;

	IEffectComponentTimeLine *timeline =	
		component->getTimeLine();

	if (!timeline)
		return;

	timeline->start();
}

void TimeLineWindow::pause()
{
	IScene* scene = CoreManager::getInstance().getScene();
	if (!scene)
		return;

	IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
	if (!component)
		return;

	IEffectComponentTimeLine *timeline =	
		component->getTimeLine();

	if (!timeline)
		return;

	// todo
}

void TimeLineWindow::stop()
{
	mStartDelta = 0;
	mIsStart = false;

	setSlidersTime(mStartDelta);

	mBeginBtn->setEnabled(true);
	mStopBtn->setEnabled(false);

	IScene* scene = CoreManager::getInstance().getScene();
	if (!scene)
		return;

	IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
	if (!component)
		return;

	IEffectComponentTimeLine *timeline =	
		component->getTimeLine();

	if (!timeline)
		return;

	timeline->stop();
}

void TimeLineWindow::addEvent()
{
	AddEventDlg dlg;
	dlg.setEventTime(mCurrentTime);
	dlg.exec();
}

void TimeLineWindow::setLoop( int state )
{
	mbLoop = (state == 2);

	IScene* scene = CoreManager::getInstance().getScene();
	if (!scene)
		return;

	IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
	if (!component)
		return;

	IEffectComponentTimeLine *timeline =	
		component->getTimeLine();

	if (!timeline)
		return;

	IEffectXmlSerializer* effectxmlSer = component->getEffectXmlSerializer();
	if (!effectxmlSer)
		return;

	timeline->setIsLoop(mbLoop);

	XMLElement* elm = effectxmlSer->getTimeLineXMLEle();

	Int loop = mbLoop;
	XmlHelper::setAttribute(elm, loop, "Loop");
}

void TimeLineWindow::periodTimeValueChanged( int time )
{
	mTotalTime = time;

	IScene* scene = CoreManager::getInstance().getScene();
	if (!scene)
		return;

	IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
	if (!component)
		return;

	IEffectComponentTimeLine *timeline =	
		component->getTimeLine();

	if (!timeline)
		return;

	IEffectXmlSerializer* effectxmlSer = component->getEffectXmlSerializer();
	if (!effectxmlSer)
		return;

	timeline->setPeriodTime(mTotalTime);

	XMLElement* elm = effectxmlSer->getTimeLineXMLEle();
	XmlHelper::setAttribute(elm, mTotalTime, "Period");
}

void TimeLineWindow::currentTimeValueChanged( int time )
{
	mCurrentTime = time;

	if (!mIsStart)
		return;

	IScene* scene = CoreManager::getInstance().getScene();
	if (!scene)
		return;

	IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
	if (!component)
		return;

	IEffectComponentTimeLine *timeline =	
		component->getTimeLine();

	if (!timeline)
		return;

	timeline->setCurrentTime(time);
}
