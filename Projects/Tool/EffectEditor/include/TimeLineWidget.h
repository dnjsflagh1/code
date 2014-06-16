#ifndef __TIMELINE_WIDGET_H__
#define __TIMELINE_WIDGET_H__

#include <qdockwidget.h>

class QString;
class QWidget;
class TimeLineWindow;

class TimeLineWidget : public QDockWidget
{
	Q_OBJECT
public:
	TimeLineWidget(const QString &title, QWidget *parent = 0, Qt::WindowFlags flags = 0);

	void update(float delta);

	TimeLineWindow*		getTimeLineWindow();
private:
	TimeLineWindow*		mWindow;
};

#endif