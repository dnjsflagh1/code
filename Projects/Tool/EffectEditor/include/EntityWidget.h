#ifndef __ENTITY_WIDGET_H__
#define __ENTITY_WIDGET_H__

#include <QWidget>
#include "Define.h"

class QString;
class QWidget;
class QTreeWidget;
class QTreeWidgetItem;

class QPushButton;
class QtProperty;
class QtTreePropertyBrowser;
class QtVariantPropertyManager;
class Vector3Manager;
class QtVariantEditorFactory;


class EntityWidget : public QWidget
{
	Q_OBJECT
public:
	EntityWidget(QWidget *parent = 0, Qt::WFlags flags = 0);
	virtual ~EntityWidget();

public:
	void	addNameToList(std::string name);
	void	clear();
	std::list<std::string>& getEntityList();
	void	setEntityList(std::list<std::string>& list);
private:
	void	createWidget();
	void	init();
	void	setProperty();

private slots:
	void	vector3ValueChanged(QtProperty *, const QVariant &);
	void	changeSeleted(QTreeWidgetItem *item, int column);
	void	deleteClicked();

private:
	QTreeWidget *mEntityTreeWidget;
	QPushButton *mDeleteModelBtn;

	QtTreePropertyBrowser *mPropertyBrw;
	Vector3Manager    *mVector3Manager;
	QtVariantPropertyManager *mVarManVec;
	QtVariantEditorFactory *mVariantEditFactory;

	Vec3	mEntityPos;
	Vec3	mEntityScale;

	QTreeWidgetItem* mSeletedItem;

	std::list<std::string> mEntityNameList;
};

#endif