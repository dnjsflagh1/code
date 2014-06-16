#include "TimeLineWidget.h"

#include <QtGui>
#include "SlidersGroup.h"
#include "TimeLineWindow.h"

TimeLineWidget::TimeLineWidget( const QString &title, QWidget *parent /*= 0*/, Qt::WindowFlags flags /*= 0*/ )
	: QDockWidget(title, parent, flags)
{
	mWindow = new TimeLineWindow;
	this->setWidget(mWindow);
}

void TimeLineWidget::update( float delta )
{
	mWindow->update(delta);
}

TimeLineWindow* TimeLineWidget::getTimeLineWindow()
{
	return mWindow;
}