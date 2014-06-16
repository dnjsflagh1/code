#include <QtGui>
#include "Define.h"
#include "DllLoader.h"
#include "GlobalOption.h"
#include "CoreManager.h"
#include "OperationManager.h"

#include "AddEventDlg.h"

using namespace EffectEditor;
AddEventDlg::AddEventDlg(QWidget *parent, Qt::WFlags flags)
	:QDialog(parent, flags)
	, mEventTiming(0.0f)
{	
	createWidget();
	init();
	setWindowTitle("AddEvent");
}
AddEventDlg::~AddEventDlg()
{

}

void AddEventDlg::createWidget()
{
	mEventTreeWidget = new QTreeWidget(this);
	mEventTreeWidget->header()->hide();

	connect(mEventTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem *, int)), 
		this, SLOT(itemClicked(QTreeWidgetItem *, int)));

	mOKBtn = new QPushButton(this);
	mOKBtn->setText("OK");
	mOKBtn->sizeHint();
	mCancleBtn = new QPushButton(this);
	mCancleBtn->setText("Cancel");
	mCancleBtn->sizeHint();

	connect(mOKBtn, SIGNAL(clicked()), this, SLOT(okClicked()));
	connect(mCancleBtn, SIGNAL(clicked()), this, SLOT(cancelClicked()));

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(mEventTreeWidget);

	QHBoxLayout *buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(mOKBtn);
	buttonLayout->addWidget(mCancleBtn);
	mainLayout->addLayout(buttonLayout);
	setLayout(mainLayout);
}

void AddEventDlg::init()
{
	QTreeWidgetItem* event1 = new QTreeWidgetItem(mEventTreeWidget);
	event1->setText(0, "Model_Visible");

	QTreeWidgetItem* event2 = new QTreeWidgetItem(mEventTreeWidget);
	event2->setText(0, "Model_Animation");

	QTreeWidgetItem* event3 = new QTreeWidgetItem(mEventTreeWidget);
	event3->setText(0, "Model_Bind");

	QTreeWidgetItem* event4 = new QTreeWidgetItem(mEventTreeWidget);
	event4->setText(0, "PU_Start");

	QTreeWidgetItem* event5 = new QTreeWidgetItem(mEventTreeWidget);
	event5->setText(0, "PU_Stop");

	QTreeWidgetItem* event6 = new QTreeWidgetItem(mEventTreeWidget);
	event6->setText(0, "PU_Bind");

	QTreeWidgetItem* event7 = new QTreeWidgetItem(mEventTreeWidget);
	event7->setText(0, "Weapon_Light");

	QTreeWidgetItem* event8 = new QTreeWidgetItem(mEventTreeWidget);
	event8->setText(0, "Effect_Fade");
}

void AddEventDlg::setEventTime( float timing )
{
	mEventTiming = timing;
}

void AddEventDlg::okClicked()
{
	if (!mCurrentEventName.empty())
		OperationManager::getInstance().addEvent(mCurrentEventName, mEventTiming);
	
	this->close();
}

void AddEventDlg::cancelClicked()
{
	this->close();
}

void AddEventDlg::itemClicked( QTreeWidgetItem *item, int com)
{
	mCurrentEventName = item->text(0).toStdString();
}
