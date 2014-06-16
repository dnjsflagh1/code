#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QLabel;
class QComboBox;

class TimeLineWidget;
class RenderWindow;
class RenderWidget;
class ExModelWidget;
class ExComponentWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	virtual ~MainWindow();

	void renderWindowResizeEvent(void);
	//��Ϣ��Ӧ
	void keyPressEvent(QKeyEvent* evt);
	void keyReleaseEvent(QKeyEvent* evt);

	void paintEvent(QPaintEvent *evt);

	void timerEvent(QTimerEvent* evt);

	HWND getHandle();
	HWND getInputHandle();
	size_t getWidth();
	size_t getHeight();

	void update(float delta);

	void updateStatusBar(float fps);
	void updateCameraPos(float x, float y, float z);

	void addEntitytoList(const std::string& name);
	void addEffecttoList(const std::string& name);
	void addEventName(const std::string& name, const std::string& typeName);

	int	 getCurrentTabIndex();
	void clear();

	ExComponentWidget*  getExComponentWidget();

	ExModelWidget*		getExModelWidget();

	RenderWindow*		getRenderWindow();

	TimeLineWidget*		getTimeLineWidget();
private:
	// �����ؼ����
	void init();
	void create();
    void createActions();
    void createMenus();
	void createToolBars();
	void createStatusBar();

	void createwidget();
	void createTabWidget();
//slots
private slots:
	void	newFile();
	void	open();
	void	addObject();
	bool	save();
	bool	saveAs();
	void	about();
	void	recoverCameraPos();
	void	showRenderDockWidget(bool checked);
	void	showTimeLineDockWidget(bool checked);
	void	showPropertyDockWidget(bool checked);
	void	showGrid();
	
	void	resizeEvent(QResizeEvent * event);

	void	tabChanged(int);
private:
	bool	okToContinue();
	bool	saveFile(const QString &fileName);
	bool	loadFile(const QString &fileName);
	void	setCurrentFile(const QString &fileName);
	QString strippedName(const QString &fullFileName);

private:
	QLabel *mFpsLabel;
	QLabel *mCameraPosLabel;
	QLabel *mProjectNameLabel;

	//menu
	QMenu *mFileMenu;
	QMenu *mToolMenu;
	QMenu *mViewMenu;
	QMenu *mAboutMenu;

	//file
	QAction *mSeparatorAction;
	QAction *mFileNewAction;
	QAction *mFileOpenAction;
	QAction *mFileAddObject;
	QAction *mFileSaveAction;
	QAction *mExitAction;

	//tool
	QAction *mToolChooseAction;
	QAction *mToolTranslateAction;
	QAction *mToolZoomAction;
	QAction *mToolRotateAction;
	QAction *mToolGridAction;
	QAction *mToolRecoverCamAction;

	//view
	QAction *mViewRenderAction;
	QAction *mViewPropertyAction;
	QAction *mViewTimeLineAction;

	//about
	QAction *mAboutEditAction;

	//toolbar
	QToolBar *mToolBar;
	QComboBox *mTranslateComboBox;

	//��Ⱦ���ڵ�Dock
	RenderWidget *mRenderWidget;

	// �ұ�Tab���ڵ�Dock.
	QDockWidget*	mPropertyTabDockWidget;
	// 
	QTabWidget *mPropertyTabWidget;
	// ��һ�㼶��ģ�ʹ���
	ExModelWidget *mExModelWidget;
	// ��һ�㼶����Ч�������
	ExComponentWidget *mExComponentWidget;

	// ʱ����dock
	TimeLineWidget *mTimeLineWidget;


	// ���ؽ������ļ���
	QString		mImportfilename;
	QString		mCurFileName;

	int			mCurrentTabIndex;
};

#endif
