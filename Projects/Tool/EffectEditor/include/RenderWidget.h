#ifndef __RENDER_WIDGET_H__
#define __RENDER_WIDGET_H__

#include <qdockwidget.h>

class QWidget;
class RenderWindow;

class RenderWidget : public QDockWidget
{
	//Q_OBJECT
public:
	RenderWidget(const QString &title, QWidget *parent = 0, Qt::WindowFlags flags = 0);
	virtual ~RenderWidget();

public:
	RenderWindow* getRenderWindow();

private:
	RenderWindow *mRenderWindow;
};

#endif