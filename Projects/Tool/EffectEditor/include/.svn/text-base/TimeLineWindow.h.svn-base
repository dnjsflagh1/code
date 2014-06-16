#ifndef __TIMELINE_WINDOW_H__
#define __TIMELINE_WINDOW_H__

#include <QWidget>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QComboBox;
class QGroupBox;
class QLabel;
class QSpinBox;
class QStackedWidget;
class QPushButton;
QT_END_NAMESPACE
class SlidersGroup;

class TimeLineWindow : public QWidget
{
    Q_OBJECT

public:
    TimeLineWindow(QWidget *parent = 0, Qt::WFlags flags = 0);

	void update(float delta);

	void setMaxTimeNum(float maxtime);

	void setLoopBtnCheck(bool loop);
signals:
	void setSlidersTime(int timing);
private slots:
	void start();
	void pause();
	void stop();
	void addEvent();

	void setLoop(int state);
	void periodTimeValueChanged(int time);
	void currentTimeValueChanged(int time);
private:
    void createControls(const QString &title);

    SlidersGroup*	mHorizontalSliders;
    QStackedWidget*	mStackedWidget;

    QGroupBox*		mControlsGroup;
    QLabel*			mMaximumLabel;
    QLabel*			mSetCurTimeValueLabel;
	QLabel*			mLoopLabel;
    QSpinBox*		mMaximumSpinBox;
    QSpinBox*		mSetCurTimeSpinBox;

	QPushButton*	mBeginBtn;
	QPushButton*	mPauseBtn;
	QPushButton*	mStopBtn;
	QPushButton*	mAddEventBtn;
	
	QCheckBox*		mLoopCheckBox;

	// 是否开始
	bool			mIsStart;
	// 累计时间
	float			mStartDelta;
	// 是否循环
	bool			mbLoop;
	// 总的时间
	float			mTotalTime;
	//
	float			mCurrentTime;
};

#endif
