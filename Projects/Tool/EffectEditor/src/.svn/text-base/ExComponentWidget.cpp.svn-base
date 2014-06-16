#include "ExComponentWidget.h"
#include <QtGui>
#include "EntityWidget.h"
#include "EffectWidget.h"
#include "EventWidget.h"
#include "GlobalOption.h"
#include "CoreManager.h"

#include "TimeLineWidget.h"
#include "TimeLineWindow.h"
#include "IEffectComponentTimeLine.h"

using namespace EffectEditor;

ExComponentWidget::ExComponentWidget( QWidget *parent /*= 0*/, Qt::WFlags flags /*= 0*/ )
	: QWidget(parent)
	, mDeleteModelBtn(NULL)
	, mEntityWidget(NULL)
	, mEffectWidget(NULL)
	, mEventWidget(NULL)
	, mComponentTreeWidget(NULL)
	, mSeletedItem(NULL)
{
	createWidget();
	init();
}

ExComponentWidget::~ExComponentWidget()
{
	MG_SAFE_DELETE(mComponentTreeWidget);
	MG_SAFE_DELETE(mEventWidget);
	MG_SAFE_DELETE(mEffectWidget);
	MG_SAFE_DELETE(mEntityWidget);
	MG_SAFE_DELETE(mDeleteModelBtn);
}

void ExComponentWidget::createWidget()
{
	mDeleteModelBtn = new QPushButton(this);
	mDeleteModelBtn->setText("Delete");
	mDeleteModelBtn->sizeHint();
	mDeleteModelBtn->setEnabled(false);

	mEntityWidget = new EntityWidget(this);
	mEffectWidget = new EffectWidget(this);
	mEventWidget = new EventWidget(this);

	mComponentTreeWidget = new QTreeWidget(this);
	mComponentTreeWidget->header()->hide();

	mTabWidget = new QTabWidget;
	mTabWidget->addTab(mEntityWidget, tr("Entity"));
	mTabWidget->addTab(mEffectWidget, tr("Effect"));
	mTabWidget->addTab(mEventWidget,  tr("Event"));

}

void ExComponentWidget::init()
{
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(mComponentTreeWidget);
	mainLayout->addWidget(mDeleteModelBtn);
	mainLayout->addWidget(mTabWidget);

	setLayout(mainLayout);

	connect(mDeleteModelBtn, SIGNAL(clicked()), this, SLOT(deleteClicked()));
	connect(mComponentTreeWidget, SIGNAL(itemPressed(QTreeWidgetItem *, int)), this, SLOT(changeSeleted(QTreeWidgetItem *, int)));
}

EntityWidget* ExComponentWidget::getEntityWidget()
{
	return mEntityWidget;
}

EffectWidget* ExComponentWidget::getEffectWidget()
{
	return mEffectWidget;
}

EventWidget* ExComponentWidget::getEventWidget()
{
	return mEventWidget;
}

void ExComponentWidget::changeSeleted( QTreeWidgetItem *item, int column )
{
	mSeletedItem = item;
	mCurrentComponentName = mSeletedItem->text(0).toStdString();
	CoreManager::getInstance().setCurrentComponent(mCurrentComponentName);
	mDeleteModelBtn->setEnabled(true);

	float periodTime = 
		CoreManager::getInstance().getCurEffectComponent()->getTimeLine()->getPeriodTime();

	Bool loop = 
		CoreManager::getInstance().getCurEffectComponent()->getTimeLine()->getIsLoop();

	WindowSet::main_win->getTimeLineWidget()->getTimeLineWindow()->setMaxTimeNum(periodTime);

	WindowSet::main_win->getTimeLineWidget()->getTimeLineWindow()->setLoopBtnCheck(loop);
}

void ExComponentWidget::addNameToList( std::string name )
{
	QTreeWidgetItem* component = new QTreeWidgetItem(mComponentTreeWidget);
	component->setText(0, QString(name.c_str()));

	mComponentNameList.push_back(name);
}

void ExComponentWidget::clear()
{
	mComponentTreeWidget->clear();
	mEntityWidget->clear();
	mEffectWidget->clear();
	mEventWidget->clear();

	mDeleteModelBtn->setEnabled(false);
}

void ExComponentWidget::deleteClicked()
{
	if (mSeletedItem)
	{
		int index = mComponentTreeWidget->indexOfTopLevelItem(mSeletedItem);
		mComponentTreeWidget->takeTopLevelItem(index)->removeChild(mSeletedItem);

		Str name = mSeletedItem->text(0).toStdString();
		std::list<std::string>::iterator iter = mComponentNameList.begin();
		for ( ; iter != mComponentNameList.end(); iter++)
		{
			if ( StrCmp((*iter).c_str(), name.c_str()) == 0)
			{
				mComponentNameList.erase(iter);
				break;
			}
		}

		CoreManager::getInstance().destoryEffectComponent(name);
		mSeletedItem = NULL;
		mDeleteModelBtn->setEnabled(false);

		CoreManager::getInstance().setCurrentComponent("");
	}
}