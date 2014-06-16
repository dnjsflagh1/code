#ifndef __EXCOMPONENT_WIDGET_H__
#define __EXCOMPONENT_WIDGET_H__

#include <qdockwidget.h>

class EntityWidget;
class EffectWidget;
class EventWidget;
class QTabWidget;
class QTreeWidget;
class QTreeWidgetItem;
class QPushButton;

class ExComponentWidget : public QWidget
{
	Q_OBJECT
public:
	ExComponentWidget(QWidget *parent = 0, Qt::WFlags flags = 0);
	virtual ~ExComponentWidget();

private:
	void	createWidget();
	void	init();

public:
	// 获得实体窗口
	EntityWidget* getEntityWidget();
	// 获得PU窗口
	EffectWidget* getEffectWidget();
	// 获得事件窗口
	EventWidget*  getEventWidget();
	// 添加名字到ComponentList
	void	addNameToList(std::string name);

	void	clear();
private slots:
	void	changeSeleted(QTreeWidgetItem *item, int column);
	
	void	deleteClicked();
private:
	// 删除按钮
	QPushButton *mDeleteModelBtn;
	// Component列表
	QTreeWidget *mComponentTreeWidget;
	// 实体
	EntityWidget *mEntityWidget;
	// 特效dock
	EffectWidget *mEffectWidget;
	// 事件dock
	EventWidget *mEventWidget;

	QTabWidget *mTabWidget;

	int	mCurrentTab;

	std::list<std::string> mComponentNameList;

	std::string mCurrentComponentName;

	QTreeWidgetItem* mSeletedItem;
};

#endif