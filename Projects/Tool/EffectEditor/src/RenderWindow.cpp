#include "RenderWindow.h"
#include "mainwindow.h"
#include "qevent.h"

#include "Define.h"
#include "DllLoader.h"
#include "CoreManager.h"

using namespace EffectEditor;

RenderWindow::RenderWindow(QWidget *parent, Qt::WFlags flags):QWidget(parent, flags)
{ 
	//setFocusPolicy(Qt::StrongFocus);//
	//setMouseTracking(true);
}
RenderWindow::~RenderWindow()
{

}

void RenderWindow::resizeEvent(QResizeEvent * event)
{
	QSize size = event->size();
	//CoreManager::getInstance().setDisplayMode(size.width(), size.height());
}