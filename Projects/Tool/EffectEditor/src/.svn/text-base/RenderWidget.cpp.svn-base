#include "RenderWidget.h"
#include "RenderWindow.h"

RenderWidget::RenderWidget( const QString &title, QWidget *parent /*= 0*/, Qt::WindowFlags flags /*= 0*/ )
	: QDockWidget(title, parent, flags)
{
	mRenderWindow = new RenderWindow(this);
	//mRenderWindow->setWindowFlags(Qt::Window);
	mRenderWindow->setWindowTitle("Render");
	mRenderWindow->sizeHint();
	mRenderWindow->show();

	this->setWidget(mRenderWindow);
}

RenderWidget::~RenderWidget()
{

}

RenderWindow* RenderWidget::getRenderWindow()
{
	return mRenderWindow;
}