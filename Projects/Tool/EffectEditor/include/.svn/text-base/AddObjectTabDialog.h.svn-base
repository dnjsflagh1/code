#ifndef __ADDOBJECT_TABDIALOG_h__
#define __ADDOBJECT_TABDIALOG_h__
#include <QDialog>

#include "Define.h"
#include "IResourceManager.h"

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QFileInfo;
class QTabWidget;
class QTreeWidget;
class QTreeWidgetItem;
QT_END_NAMESPACE

typedef std::map<QString, MG::ModelDeclaration*> ModelDecl;
typedef std::map<QString, MG::EffectResourceDeclaration*> EffectDecl;

class EntityTab : public QWidget
{
	Q_OBJECT

public:
	EntityTab(QWidget *parent = 0, Qt::WFlags flags = 0);

public:
	void loadEntityList();
	QString getCurrentItemName() { return mCurrentSeletedItemName; }
	void setCurrentItemNameNull();
	ModelDecl& getModelDecl() { return mModelDeclList; }

private slots:
	void	itemChanged(QTreeWidgetItem *item, int column);

private:
	QTreeWidget* mEntityTreeWidget;
	ModelDecl mModelDeclList;
	QString		 mCurrentSeletedItemName;
};

class EffectTab : public QWidget
{
	Q_OBJECT

public:
	EffectTab(QWidget *parent = 0, Qt::WFlags flags = 0);

public:
	void loadEffectList();
	QString getCurrentItemName() { return mCurrentSeletedItemName; }
	void setCurrentItemNameNull();
	EffectDecl& getEffectDecl() {return mEffectDeclList;}

private slots:
	void	itemChanged(QTreeWidgetItem *item, int column);

private:
	QTreeWidget* mEffectTreeWidget;

	EffectDecl  mEffectDeclList;
	QString		mCurrentSeletedItemName;

};

class AddObjectTabDialog :public QDialog
{
	Q_OBJECT
public:
	SINGLETON_INSTANCE(AddObjectTabDialog)
	AddObjectTabDialog(QWidget *parent = 0, Qt::WFlags flag = 0);
	~AddObjectTabDialog(void);

	void init();

	void initList();
private slots:
	void	tabChanged(int index);
	void	okClicked();
	void	cancelClicked();

private:
	QTabWidget *mTabWidget;
	QPushButton *mOKBtn;
	QPushButton *mCancleBtn;

	EntityTab* mEntityTab;
	EffectTab* mEffectTab;

	int	mCurrentTab;
};

#endif