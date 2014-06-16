#include <QComboBox>
#include <QProgressBar>
#include <QtGui>

#include "Define.h"
#include "DllLoader.h"
#include "CoreManager.h"
#include "OperationManager.h"

#include "mainwindow.h"
#include "RenderWindow.h"

#include "TimeLineWidget.h"
#include "RenderWidget.h"
#include "ExModelWidget.h"
#include "EntityWidget.h"
#include "EffectWidget.h"
#include "EventWidget.h"
#include "ExComponentWidget.h"
#include "AddObjectTabDialog.h"

#include "IWireframeManager.h"
#include "IEffectXmlSerializer.h"

using namespace EffectEditor;

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags): QMainWindow(parent, flags)
	, mFpsLabel(NULL)
	, mCameraPosLabel(NULL)
	, mProjectNameLabel(NULL)

	, mFileMenu(NULL)
	, mToolMenu(NULL)
	, mViewMenu(NULL)
	, mAboutMenu(NULL)

	, mSeparatorAction(NULL)
	, mFileNewAction(NULL)
	, mFileOpenAction(NULL)
	, mFileAddObject(NULL)
	, mFileSaveAction(NULL)
	, mExitAction(NULL)

	, mToolChooseAction(NULL)
	, mToolTranslateAction(NULL)
	, mToolZoomAction(NULL)
	, mToolRotateAction(NULL)
	, mToolGridAction(NULL)
	, mToolRecoverCamAction(NULL)

	, mViewRenderAction(NULL)
	, mViewPropertyAction(NULL)
	, mViewTimeLineAction(NULL)
	, mAboutEditAction(NULL)

	, mToolBar(NULL)
	, mTranslateComboBox(NULL)

	, mRenderWidget(NULL)
	, mPropertyTabDockWidget(NULL)
	, mPropertyTabWidget(NULL)
	, mExModelWidget(NULL)
	, mExComponentWidget(NULL)
	, mTimeLineWidget(NULL)
	
{
	setFocusPolicy(Qt::StrongFocus);//
	setMouseTracking(true);

	create();
	init();

	setWindowIcon(QIcon(":/images/qtOgitor.png"));
	setWindowTitle("Effect Editor");
	setMinimumSize(QSize(1000,700));
	resize(1000,700);

	//startTimer(2);
}

MainWindow::~MainWindow()
{
	MG_SAFE_DELETE(mFpsLabel);
	MG_SAFE_DELETE(mCameraPosLabel);
	MG_SAFE_DELETE(mProjectNameLabel);

	MG_SAFE_DELETE(mSeparatorAction);
	MG_SAFE_DELETE(mFileMenu);
	MG_SAFE_DELETE(mToolMenu);
	MG_SAFE_DELETE(mViewMenu);
	MG_SAFE_DELETE(mAboutMenu);

	MG_SAFE_DELETE(mFileNewAction);
	MG_SAFE_DELETE(mFileOpenAction);
	MG_SAFE_DELETE(mFileAddObject);
	MG_SAFE_DELETE(mFileSaveAction);
	MG_SAFE_DELETE(mExitAction);

	MG_SAFE_DELETE(mToolChooseAction);
	MG_SAFE_DELETE(mToolTranslateAction);
	MG_SAFE_DELETE(mToolZoomAction);
	MG_SAFE_DELETE(mToolRotateAction);
	MG_SAFE_DELETE(mToolGridAction);
	MG_SAFE_DELETE(mToolRecoverCamAction);

	MG_SAFE_DELETE(mViewRenderAction);
	MG_SAFE_DELETE(mViewPropertyAction);
	MG_SAFE_DELETE(mViewTimeLineAction);
	MG_SAFE_DELETE(mAboutEditAction);
	MG_SAFE_DELETE(mTranslateComboBox);
	MG_SAFE_DELETE(mToolBar);

	MG_SAFE_DELETE(mRenderWidget);
	MG_SAFE_DELETE(mExModelWidget);
	MG_SAFE_DELETE(mExComponentWidget);
	MG_SAFE_DELETE(mPropertyTabWidget);
	MG_SAFE_DELETE(mPropertyTabDockWidget);
	MG_SAFE_DELETE(mTimeLineWidget);
}

void MainWindow::create()
{
	createActions();
	createMenus();
	createToolBars();
	createStatusBar();

	createwidget();
	createTabWidget();
}

void MainWindow::init()
{
	mToolChooseAction->setCheckable(true);
	mToolTranslateAction->setCheckable(true);
	mToolZoomAction->setCheckable(true);
	mToolRotateAction->setCheckable(true);
	mToolGridAction->setCheckable(true);

	mViewPropertyAction->setCheckable(true);
	mViewRenderAction->setCheckable(true);
	mViewTimeLineAction->setCheckable(true);

	mAboutEditAction->setCheckable(true);

	
	//////////////////////////////////////////////////////////////////////////
	mViewRenderAction->setChecked(true);
	mViewPropertyAction->setChecked(true);
	mViewTimeLineAction->setChecked(true);

	mToolChooseAction->setChecked(true);
	mToolGridAction->setChecked(true);

	mCurrentTabIndex = 0;
}

void MainWindow::createActions()
{
	//file
    mFileNewAction = new QAction(tr("&New"), this);
    mFileNewAction->setIcon(QIcon(":/images/ogscene.png"));
    mFileNewAction->setShortcut(QKeySequence::New);
    connect(mFileNewAction, SIGNAL(triggered()), this, SLOT(newFile()));

	mFileOpenAction = new QAction(tr("&Open"), this);
	mFileOpenAction->setIcon(QIcon(":/images/fileopen.png"));
	mFileOpenAction->setShortcut(QKeySequence::Open);
	connect(mFileOpenAction, SIGNAL(triggered()), this, SLOT(open()));

	mFileAddObject = new QAction(tr("&AddObject"), this);
	mFileAddObject->setIcon(QIcon(":/images/entity.png"));
	connect(mFileAddObject, SIGNAL(triggered()), this, SLOT(addObject()));

	mFileSaveAction = new QAction(tr("&Save"), this);
	mFileSaveAction->setIcon(QIcon(":/images/filesave.png"));
	mFileSaveAction->setShortcut(QKeySequence::Save);
	connect(mFileSaveAction, SIGNAL(triggered()), this, SLOT(saveAs()));

	mExitAction = new QAction(tr("Exit"), this);
	mExitAction->setIcon(QIcon(":/images/exit.png"));
	connect(mExitAction, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

	//tool
	mToolChooseAction = new QAction(tr("Choose"), this);
	mToolChooseAction->setIcon(QIcon(":/images/select.png"));

	mToolTranslateAction = new QAction(tr("Translate"), this);
	mToolTranslateAction->setIcon(QIcon(":/images/move.png"));

	mToolZoomAction = new QAction(tr("Zoom"), this);
	mToolZoomAction->setIcon(QIcon(":/images/scale.png"));

	mToolRotateAction = new QAction(tr("Rotate"), this);
	mToolRotateAction->setIcon(QIcon(":/images/rotate.png"));

	mToolGridAction = new QAction(tr("Grid"), this);
	mToolGridAction->setIcon(QIcon(":/images/grid.png"));
	connect(mToolGridAction, SIGNAL(triggered()), this, SLOT(showGrid()));

	mToolRecoverCamAction = new QAction(tr("Recover Camera"), this);
	mToolRecoverCamAction->setIcon(QIcon(":/images/project.png"));
	connect(mToolRecoverCamAction, SIGNAL(triggered()), this, SLOT(recoverCameraPos()));
	
	mViewPropertyAction = new QAction(tr("Property"), this);
	mViewPropertyAction->setIcon(QIcon(":/images/properties.png"));
	connect(mViewPropertyAction, SIGNAL(triggered(bool)), this, SLOT(showPropertyDockWidget(bool)));

	mViewRenderAction = new QAction(tr("Render"), this);
	mViewRenderAction->setIcon(QIcon(":/images/param.png"));
	connect(mViewRenderAction, SIGNAL(triggered(bool)), this, SLOT(showRenderDockWidget(bool)));

	mViewTimeLineAction = new QAction(tr("Time Line"), this);
	mViewTimeLineAction->setIcon(QIcon(":/images/info.png"));
	mViewTimeLineAction->setCheckable(true);
	connect(mViewTimeLineAction, SIGNAL(triggered(bool)), this, SLOT(showTimeLineDockWidget(bool)));
	
	//about
	mAboutEditAction = new QAction(tr("EffectEditor"), this);
	mAboutEditAction->setIcon(QIcon(":/images/about.png"));
	connect(mAboutEditAction, SIGNAL(triggered()), this, SLOT(about()));

	mTranslateComboBox = new QComboBox();
	mTranslateComboBox->addItem("Free");
	mTranslateComboBox->addItem("Center");
	mTranslateComboBox->addItem("Quarter");
}

void MainWindow::createMenus()
{
	//file
    mFileMenu = menuBar()->addMenu(tr("&File"));
    mFileMenu->addAction(mFileNewAction);
	mSeparatorAction = mFileMenu->addSeparator();
	mFileMenu->addAction(mFileOpenAction);
	mFileMenu->addAction(mFileAddObject);
	mFileMenu->addAction(mFileSaveAction);
	mSeparatorAction = mFileMenu->addSeparator();
	mFileMenu->addAction(mExitAction);

	//tool
	mToolMenu = menuBar()->addMenu(tr("&Tool"));
	mToolMenu->addAction(mToolChooseAction);
	mToolMenu->addAction(mToolTranslateAction);
	mToolMenu->addAction(mToolZoomAction);
	mToolMenu->addAction(mToolRotateAction);
	mSeparatorAction = mToolMenu->addSeparator();
	mToolMenu->addAction(mToolGridAction);
	mSeparatorAction = mToolMenu->addSeparator();
	mToolMenu->addAction(mToolRecoverCamAction);

	//view
	mViewMenu = menuBar()->addMenu(tr("&View"));
	mSeparatorAction = mViewMenu->addSeparator();
	mViewMenu->addAction(mViewRenderAction);
	mViewMenu->addAction(mViewPropertyAction);
	mSeparatorAction = mViewMenu->addSeparator();
	mViewMenu->addAction(mViewTimeLineAction);

	//about
	mAboutMenu = menuBar()->addMenu(tr("&About"));
	mAboutMenu->addAction(mAboutEditAction);
}

void MainWindow::createToolBars()
{
	mToolBar = addToolBar(tr("&File"));
	mToolBar->addAction(mFileNewAction);
	mToolBar->addAction(mFileOpenAction);
	mToolBar->addAction(mFileAddObject);
	mToolBar->addAction(mFileSaveAction);

	mToolBar->addSeparator();
	mToolBar->addAction(mToolChooseAction);
	mToolBar->addAction(mToolTranslateAction);
	mToolBar->addWidget(mTranslateComboBox);
	mToolBar->addAction(mToolZoomAction);
	mToolBar->addAction(mToolRotateAction);

	mToolBar->addSeparator();
	mToolBar->addAction(mToolGridAction);

	mToolBar->addSeparator();
	mToolBar->addAction(mViewRenderAction);
	mToolBar->addAction(mViewPropertyAction);

	mToolBar->addSeparator();
	mToolBar->addAction(mViewTimeLineAction);
}

void MainWindow::createStatusBar()
{
	mProjectNameLabel = new QLabel("Effect Editor[Sirius]");
	mProjectNameLabel->setAlignment(Qt::AlignLeft);
	mProjectNameLabel->setMinimumSize(QSize(170,10));

	mFpsLabel = new QLabel("FPS:100.0");
	mFpsLabel->setMinimumSize(mFpsLabel->sizeHint());

	mCameraPosLabel = new QLabel("Camera pos:X:0, Y:0, Z:0");
	mCameraPosLabel->setAlignment(Qt::AlignHCenter);
	mCameraPosLabel->setMinimumSize(QSize(300,10));

	statusBar()->addWidget(mProjectNameLabel);
	statusBar()->addWidget(mFpsLabel);
	statusBar()->addWidget(mCameraPosLabel);

}

void MainWindow::update( float delta )
{
	mTimeLineWidget->update(delta);
}

void MainWindow::updateStatusBar(float fps)
{
	char cfps[1024];
	sprintf(cfps, "FPS:%.2f", fps);

	QString sFps(cfps);
	mFpsLabel->setText(sFps);
}

void MainWindow::updateCameraPos( float x, float y, float z )
{
	char cCameraPos[1024];
	sprintf(cCameraPos, "Camera pos: X:%.2f Y:%.2f Z:%.2f", x, y, z);

	QString sCamera(cCameraPos);
	mCameraPosLabel->setText(sCamera);
}

void MainWindow::addEntitytoList(const std::string& name )
{
	if (mCurrentTabIndex == 0)
	{
		if (mExModelWidget)
			mExModelWidget->addNameToList(name);
	}
	else
	{
		if (mExComponentWidget->getEntityWidget() && mExComponentWidget)
			mExComponentWidget->getEntityWidget()->addNameToList(name);
	}
}

void MainWindow::addEffecttoList(const std::string& name )
{
	if (mExComponentWidget->getEffectWidget() && mExComponentWidget)
		mExComponentWidget->getEffectWidget()->addNameToList(name);
}

void MainWindow::addEventName(const std::string& name, const std::string& typeName)
{
	if (mExComponentWidget->getEventWidget() && mExComponentWidget)
		mExComponentWidget->getEventWidget()->addNameToList(name, typeName);
}

int MainWindow::getCurrentTabIndex()
{
	return mCurrentTabIndex;
}

ExComponentWidget* MainWindow::getExComponentWidget()
{
	return mExComponentWidget;
}

ExModelWidget* MainWindow::getExModelWidget()
{
	return mExModelWidget;
}

RenderWindow* MainWindow::getRenderWindow()
{
	return mRenderWidget->getRenderWindow();
}

TimeLineWidget* MainWindow::getTimeLineWidget()
{
	return mTimeLineWidget;
}

void MainWindow::clear()
{
	mExComponentWidget->clear();
	mExModelWidget->clear();
}

void MainWindow::createwidget()
{
	/*-------------------------------------------------------------*/
	/*	创建dock  */
	/*-------------------------------------------------------------*/
	mRenderWidget = new RenderWidget(tr("Render"), this);
	mTimeLineWidget = new TimeLineWidget(tr("Time Line"),this);

	mPropertyTabDockWidget = new QDockWidget(tr("Property"), this);

	mRenderWidget->setMinimumWidth(this->width()*3/4);
	//mRenderWidget->setMinimumWidth(512);
	//mRenderWidget->setMaximumWidth(1024);
	//mRenderWidget->setMinimumHeight(384);
	//mRenderWidget->setMaximumHeight(768);

	//
	///*-------------------------------------------------------------*/
	///*	控件布局  */
	///*-------------------------------------------------------------*/
	addDockWidget(Qt::RightDockWidgetArea, mPropertyTabDockWidget);
	addDockWidget(Qt::BottomDockWidgetArea, mTimeLineWidget);

	setCentralWidget(mRenderWidget);
}

void MainWindow::createTabWidget()
{
	mPropertyTabWidget = new QTabWidget();
	mPropertyTabWidget->setElideMode(Qt::ElideRight);
	mPropertyTabWidget->setTabsClosable(true);
	mPropertyTabWidget->setMovable(false);
	mPropertyTabWidget->setDocumentMode(1);

	mPropertyTabDockWidget->setWidget(mPropertyTabWidget);

	mExModelWidget = new ExModelWidget();
	mExModelWidget->setWindowTitle("ExModel");
	mExModelWidget->sizeHint();
	mPropertyTabWidget->addTab(mExModelWidget, QString("Model"));

	mExComponentWidget = new ExComponentWidget();
	mExComponentWidget->setWindowTitle("ExComponent");
	mExComponentWidget->sizeHint();
	mPropertyTabWidget->addTab(mExComponentWidget, QString("Component"));

	connect(mPropertyTabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));
}

bool MainWindow::okToContinue()
{
	/*if (isWindowModified())*/ {
		int r = QMessageBox::warning(this, tr("EffectEditor"),
			tr("The scene has been modified.\n"
			"Do you want to save your changes?"),
			QMessageBox::Yes | QMessageBox::No
			| QMessageBox::Cancel);
		if (r == QMessageBox::Yes) {
			return save();
		} else if (r == QMessageBox::Cancel) {
			return false;
		}
	}
	return true;
}


bool MainWindow::saveFile( const QString &fileName )
{
	IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
	if (!component)
		return false;

	IEffectXmlSerializer* effectxmlSer = component->getEffectXmlSerializer();
	if (!effectxmlSer)
		return false;

	if (!effectxmlSer->saveEffectFile(fileName.toStdString().c_str()))
	{
		QMessageBox::information(this, "Error", "Save File Fail!");
		return false;
	}
	else
		QMessageBox::information(this, "Success", "Save File Success!");

	//setCurrentFile(fileName);

	statusBar()->showMessage(tr("File saved"), 2000);
	return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
	mCurFileName = fileName;
	setWindowModified(false);

	QString shownName = tr("Untitled");
	if (!mCurFileName.isEmpty()) {
		shownName = strippedName(mCurFileName);
	}

	setWindowTitle(tr("%1[*] - %2").arg(shownName)
		.arg(tr("EffectEditor")));
}

bool MainWindow::loadFile(const QString &fileName)
{
	Str fullname = fileName.toStdString();
	Str basename, path, name, nametype;
	MGStrOp::splitFilename(fullname, basename, path);
	MGStrOp::splitTypename(basename, name, nametype);

	if (!OperationManager::getInstance().loadEffectComponentFile(fileName.toStdString().c_str(), name))
	{
		QMessageBox::information(this, "Error", "Open File Fail!");
		return false;
	}
	else
		QMessageBox::information(this, "Success", "Open File Success!");

	//setCurrentFile(fileName);

	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("QXmlStream Bookmarks"),
			tr("Cannot read file %1:\n%2.")
			.arg(fileName)
			.arg(file.errorString()));
		return false;
	}
	
	statusBar()->showMessage(tr("File loaded"), 2000);

	return true;
}

QString MainWindow::strippedName(const QString &fullFileName)
{
	return QFileInfo(fullFileName).fileName();
}


//-----------------------------------------------------------------------------------
//slots
void MainWindow::showGrid()
{
	IEffectGridsDecorator* effectGrid = 
		CoreManager::getInstance().getScene()->getWireframeManager()->getEffectGridsDecorator("EffectGrid");
	if (effectGrid)
		effectGrid->setVisible(!effectGrid->getVisible());
}

void MainWindow::recoverCameraPos()
{
	OperationManager::getInstance().revertCamera();
}

void MainWindow::showRenderDockWidget(bool checked)
{
	if (checked)
		mRenderWidget->show();
	else
		mRenderWidget->hide();
}

void MainWindow::showTimeLineDockWidget(bool checked)
{
	if (checked)
		mTimeLineWidget->show();
	else
		mTimeLineWidget->hide();
}

void MainWindow::showPropertyDockWidget(bool checked)
{
	if (checked)
		mPropertyTabDockWidget->show();
	else
		mPropertyTabDockWidget->hide();
}

void MainWindow::newFile()
{
	if (!OperationManager::getInstance().newEffectComponentFile())
	{
		QMessageBox::information(this, "Error", "create a effectComponent false!");
	}
	else
		QMessageBox::information(this, "Success", "create a effectComponent Success!");
	//if (okToContinue()) {
	//	OperationManager::getInstance().newEffectComponentFile();
	//	//mExComponentWidget->addNameToList("_new_effect");
	//}
}

void MainWindow::open()
{
	/*if (okToContinue()) {*/
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Effect"), ".",
		tr("Effect files (*.effect)"));

	if (!fileName.isEmpty())
	{
		if (!loadFile(fileName))
		{
			QMessageBox::warning(this, tr("QXmlStream Bookmarks"),
				tr("Cannot read file %1:\n%2.")
				.arg(fileName)
				.arg("load effect error!"));
		}
		else
			mImportfilename = fileName;
	}
			
	//}
}

void MainWindow::addObject()
{
	AddObjectTabDialog dlg;
	dlg.initList();
	dlg.exec();
}


bool MainWindow::save()
{
	if (mCurFileName.isEmpty()) {
		return saveAs();
	} else {
		return saveFile(mCurFileName);
	}
}

void MainWindow::about()
{
	QMessageBox::about(this, tr("EffectEditor"),
		tr("<b>EffectEditor<br />Author:X.Sirius</b>"));
}


bool MainWindow::saveAs()
{
	if (!CoreManager::getInstance().getCurEffectComponent())
	{
		QMessageBox::information(this, "Warning!", 
			"has no Component in the Scene right now!");

		return false;
	}

	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Save Effect"), ".",
		tr("Effect files (*.effect)"));
	if (fileName.isEmpty())
		return false;

	return saveFile(fileName);
}

void MainWindow::tabChanged( int index)
{
	mCurrentTabIndex = index;
}

void MainWindow::resizeEvent( QResizeEvent * event )
{
//	int extraWidth = width() - minimumWidth();
////	int extraHeight = height() - minimumHeight();
//
//	mRenderWidget->getRenderWindow()->setMinimumWidth(200+extraWidth);
}

//---------------------------------------------------------------------------------------
HWND MainWindow::getHandle()
{
	return (HWND)mRenderWidget->getRenderWindow()->winId();
}

HWND MainWindow::getInputHandle()
{
	return (HWND)this->winId();
}

size_t MainWindow::getWidth()
{
	//return static_cast<size_t>(mRenderWidget->getRenderWindow()->width());
	return static_cast<size_t>(this->width());
}

size_t MainWindow::getHeight()
{
	//return static_cast<size_t>(mRenderWidget->getRenderWindow()->height());
	return static_cast<size_t>(this->height());
}

void MainWindow::renderWindowResizeEvent( void )
{
	
}

//消息响应
void MainWindow::keyPressEvent( QKeyEvent* evt )
{
	
}

void MainWindow::keyReleaseEvent( QKeyEvent* evt )
{
	
}

void MainWindow::paintEvent( QPaintEvent *evt )
{
	Q_UNUSED(evt);
	//CoreManager::getInstance().update(0.0f);
}

void MainWindow::timerEvent( QTimerEvent* evt )
{
	Q_UNUSED(evt);
	//CoreManager::getInstance().update(0.004f);
}

