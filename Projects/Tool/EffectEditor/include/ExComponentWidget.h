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
	// ���ʵ�崰��
	EntityWidget* getEntityWidget();
	// ���PU����
	EffectWidget* getEffectWidget();
	// ����¼�����
	EventWidget*  getEventWidget();
	// ������ֵ�ComponentList
	void	addNameToList(std::string name);

	void	clear();
private slots:
	void	changeSeleted(QTreeWidgetItem *item, int column);
	
	void	deleteClicked();
private:
	// ɾ����ť
	QPushButton *mDeleteModelBtn;
	// Component�б�
	QTreeWidget *mComponentTreeWidget;
	// ʵ��
	EntityWidget *mEntityWidget;
	// ��Чdock
	EffectWidget *mEffectWidget;
	// �¼�dock
	EventWidget *mEventWidget;

	QTabWidget *mTabWidget;

	int	mCurrentTab;

	std::list<std::string> mComponentNameList;

	std::string mCurrentComponentName;

	QTreeWidgetItem* mSeletedItem;
};

#endif