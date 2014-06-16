#ifndef __EFFECT_WIDGET_H__
#define __EFFECT_WIDGET_H__

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

class EffectWidget : public QWidget
{
	Q_OBJECT
public:
	EffectWidget(QWidget *parent = 0, Qt::WFlags flags = 0);
	virtual ~EffectWidget();

public:
	void	addNameToList(std::string name);
	void	clear();
	std::list<std::string>& getEffectList();
	void	setEffectList(std::list<std::string> &list);
private:
	void	createWidget();
	void	init();
	void	setProperty();

private slots:
	void	deleteClicked();
	void	changeSeleted(QTreeWidgetItem *item, int column);
	void	vector3ValueChanged(QtProperty *, const QVariant &);

private:
	QTreeWidget *mEffectTreeWidget;
	QPushButton *mDeleteModelBtn;

	QtTreePropertyBrowser *mPropertyBrw;
	Vector3Manager    *mVector3Manager;
	QtVariantPropertyManager *mVarManVec;
	QtVariantEditorFactory *mVariantEditFactory;

	std::list<std::string> mEffectNameList;

	Vec3	mEffectPos;
	Vec3	mEffecScale;

	QTreeWidgetItem* mSeletedItem;
};

#endif