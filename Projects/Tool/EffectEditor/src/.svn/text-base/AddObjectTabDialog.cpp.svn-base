#include <QtGui>
#include "Define.h"
#include "DllLoader.h"
#include "GlobalOption.h"
#include "CoreManager.h"
#include "OperationManager.h"

#include "AddObjectTabDialog.h"

using namespace EffectEditor;
AddObjectTabDialog::AddObjectTabDialog(QWidget *parent, Qt::WFlags flags):QDialog(parent, flags)
{	
	mCurrentTab = 0;
	init();
	setWindowTitle("AddObject");
}
AddObjectTabDialog::~AddObjectTabDialog()
{

}

void AddObjectTabDialog::init()
{
	mTabWidget = new QTabWidget;
	mEntityTab = new EntityTab(this);
	mEffectTab = new EffectTab(this);
	mTabWidget->addTab(mEntityTab, tr("AddEntity"));
	mTabWidget->addTab(mEffectTab, tr("AddEffect"));

	mOKBtn = new QPushButton(this);
	mOKBtn->setText("OK");
	mOKBtn->sizeHint();
	mCancleBtn = new QPushButton(this);
	mCancleBtn->setText("Cancel");
	mCancleBtn->sizeHint();

	connect(mOKBtn, SIGNAL(clicked()), this, SLOT(okClicked()));
	connect(mCancleBtn, SIGNAL(clicked()), this, SLOT(cancelClicked()));

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(mTabWidget);

	QHBoxLayout *buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(mOKBtn);
	buttonLayout->addWidget(mCancleBtn);
	mainLayout->addLayout(buttonLayout);
	setLayout(mainLayout);

	connect(mTabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));
}

void AddObjectTabDialog::tabChanged( int index )
{
	mEntityTab->setCurrentItemNameNull();
	mEffectTab->setCurrentItemNameNull();

	mCurrentTab = index;
}

void AddObjectTabDialog::okClicked()
{
	QString objName;
	// EntityTab
	if (mCurrentTab == 0)
	{
		objName = mEntityTab->getCurrentItemName();
		if (!objName.isEmpty())
		{
			ModelDecl modelDecl = mEntityTab->getModelDecl();
			ModelDeclaration* declaration = modelDecl[objName];
			if (declaration)
				OperationManager::getInstance().addEntity(declaration->id);
		}
	}
	else
	{
		objName = mEffectTab->getCurrentItemName();
		if (!objName.isEmpty())
		{
			EffectDecl effectDecl = mEffectTab->getEffectDecl();
			EffectResourceDeclaration* declaration = effectDecl[objName];
			if (declaration)
				OperationManager::getInstance().addEffect(declaration->fileName);
		}
	}

	this->close();
}

void AddObjectTabDialog::cancelClicked()
{
	this->close();
}

void AddObjectTabDialog::initList()
{
	if (mEntityTab)
		mEntityTab->loadEntityList();
	
	if (mEffectTab)
		mEffectTab->loadEffectList();
}
//////////////////////////////////////////////////////////////////////////
EntityTab::EntityTab(QWidget *parent/* = 0*/, Qt::WFlags flag/* = 0*/)
: QWidget(parent)
{
	mEntityTreeWidget = new QTreeWidget(this);
	mEntityTreeWidget->header()->hide();

	connect(mEntityTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem *, int)), 
		this, SLOT(itemChanged(QTreeWidgetItem *, int)));

}

void EntityTab::loadEntityList()
{
	UInt count = CoreManager::getInstance().getEngineMain()->resourceMgr()->getModelDeclarationCount();
	for ( UInt index=0; index<count ; index++ )
	{
		MG::ModelDeclaration* decl = CoreManager::getInstance().getEngineMain()->resourceMgr()->getModelDeclarationByIndex(index);

		QTreeWidgetItem* entity = new QTreeWidgetItem(mEntityTreeWidget);
		std::wstring dest;
		MGStrOp::toString(decl->name.c_str(),dest);
		entity->setText(0, QString::fromUtf16((const ushort *)dest.c_str()));
		mEntityTreeWidget->insertTopLevelItem(index, entity);

		mModelDeclList[QString::fromUtf16((const ushort *)dest.c_str())] = decl;
	}

}

void EntityTab::itemChanged(QTreeWidgetItem *item, int column)
{
	mCurrentSeletedItemName = item->text(0);
}

void EntityTab::setCurrentItemNameNull()
{
	mCurrentSeletedItemName.clear();
}
//////////////////////////////////////////////////////////////////////////
EffectTab::EffectTab(QWidget *parent/* = 0*/, Qt::WFlags flag/* = 0*/)
: QWidget(parent)
{
	mEffectTreeWidget = new QTreeWidget(this);
	mEffectTreeWidget->header()->hide();

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(mEffectTreeWidget);
	mainLayout->addStretch(1);
	setLayout(mainLayout);

	mEffectTreeWidget->setAlternatingRowColors(true);
	mEffectTreeWidget->header()->setMovable(false);

	connect(mEffectTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem *, int)), 
		this, SLOT(itemChanged(QTreeWidgetItem *, int)));

}

void EffectTab::loadEffectList()
{
	UInt count = CoreManager::getInstance().getEngineMain()->resourceMgr()->getEffectResourceDeclarationCount();
	for ( UInt index=0; index<count ; index++ )
	{
		MG::EffectResourceDeclaration* decl = CoreManager::getInstance().getEngineMain()->resourceMgr()->getEffectResourceDeclarationByIndex(index);

		QTreeWidgetItem* effect = new QTreeWidgetItem(mEffectTreeWidget);
		std::wstring dest;
		MGStrOp::toString(decl->name.c_str(),dest);
		effect->setText(0, QString::fromUtf16((const ushort *)dest.c_str()));
		mEffectTreeWidget->insertTopLevelItem(index, effect);

		mEffectDeclList[QString::fromUtf16((const ushort *)dest.c_str())] = decl;
	}

}

void EffectTab::itemChanged(QTreeWidgetItem *item, int column)
{
	mCurrentSeletedItemName = item->text(0);
}

void EffectTab::setCurrentItemNameNull()
{
	mCurrentSeletedItemName.clear();
}