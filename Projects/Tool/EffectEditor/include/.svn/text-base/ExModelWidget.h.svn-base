#ifndef __EXMODEL_WIDGET_H__
#define __EXMODEL_WIDGET_H__

#include <qdockwidget.h>
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
class QtEnumPropertyManager;
class QtVariantEditorFactory;
class QtEnumEditorFactory;

class ExModelWidget : public QWidget
{
	Q_OBJECT
public:
	ExModelWidget(QWidget *parent = 0, Qt::WFlags flags = 0);
	virtual ~ExModelWidget();

public:
	void	addNameToList(std::string name);
	void	clear();
	std::list<std::string>& getExModelNameList();
	unsigned int getExModelNameListSize();
private:
	void	createWidget();
	void	init();
	void	setProperty(unsigned int entityResID);

private slots:
	void	deleteClicked();
	void	playAnimationClicked();
	void	stopAnimationClicked();
	void	bindWeaponClicked();
	void	changeSeleted(QTreeWidgetItem *item, int column);
	void	vector3ValueChanged(QtProperty *, const QVariant &);
	void	enumValueChanged(QtProperty *, int);
private:
	QTreeWidget *mEntityTreeWidget;
	QPushButton *mDeleteModelBtn;
	QPushButton *mPlayAnimationBtn;
	QPushButton *mStopAnimationBtn;
	QPushButton *mBindWeaponBtn;
	
	QtTreePropertyBrowser *mPropertyBrw;
	Vector3Manager    *mVector3Manager;
	QtVariantPropertyManager *mVarManVec;
	QtEnumPropertyManager* mEnumManager;

	QtVariantEditorFactory *mVariantEditFactory;
	QtEnumEditorFactory *mComboBoxFactory;

	Vec3	mExEntityPos;
	Vec3	mExEntityScale;

	QTreeWidgetItem* mSeletedItem;

	std::list<std::string> mEntityNameList;
	
	/// 动作名列表
	QStringList mAnimationList;

	std::string mSelectedAnimationName;
};

#endif