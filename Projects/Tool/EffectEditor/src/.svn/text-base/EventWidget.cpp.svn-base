#include <QtGui>

#include "EventWidget.h"
#include "GlobalOption.h"

#include "ModelVisibleProWidget.h"
#include "ModelAniProWidget.h"
#include "ModelBindProWidget.h"
#include "PUStartProWidget.h"
#include "PUStopProWidget.h"
#include "PUBindProWidget.h"
#include "WeaponLightProWidget.h"
#include "EffectFadeProWidget.h"

#include "CoreManager.h"

using namespace EffectEditor;

EventWidget::EventWidget(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent)
	, mDeleteModelBtn(NULL)
	, mEventTreeWidget(NULL)
	, mSeletedItem(NULL)
	, mModelVisibleProWidget(NULL)
	, mModelAniProWidget(NULL)
	, mModelBindProWidget(NULL)
	, mPUStartProWidget(NULL)
	, mPUStopProWidget(NULL)
	, mPUBindProWidget(NULL)
	, mWeaponLightProWidget(NULL)
	, mEffectFadeProWidget(NULL)
{
	createWidget();
	init();
}

EventWidget::~EventWidget()
{
	MG_SAFE_DELETE(mDeleteModelBtn);
	MG_SAFE_DELETE(mEventTreeWidget);

	MG_SAFE_DELETE(mModelVisibleProWidget);
	MG_SAFE_DELETE(mModelAniProWidget);
	MG_SAFE_DELETE(mModelBindProWidget);
	MG_SAFE_DELETE(mPUStartProWidget);
	MG_SAFE_DELETE(mPUStopProWidget);
	MG_SAFE_DELETE(mPUBindProWidget);
	MG_SAFE_DELETE(mWeaponLightProWidget);
	MG_SAFE_DELETE(mEffectFadeProWidget);
}

void EventWidget::createWidget()
{
	mEventTreeWidget = new QTreeWidget(this);
	mEventTreeWidget->header()->hide();

	mDeleteModelBtn = new QPushButton(this);
	mDeleteModelBtn->setText("Delete");
	mDeleteModelBtn->sizeHint();
	mDeleteModelBtn->setEnabled(false);

	//////////////////////////////////////////////////////////////////////////
	mModelVisibleProWidget	= new ModelVisibleProWidget(this);
	mModelAniProWidget		= new ModelAniProWidget(this);
	mModelBindProWidget		= new ModelBindProWidget(this);
	mPUStartProWidget		= new PUStartProWidget(this);
	mPUStopProWidget		= new PUStopProWidget(this);
	mPUBindProWidget		= new PUBindProWidget(this);
	mWeaponLightProWidget	= new WeaponLightProWidget(this);
	mEffectFadeProWidget	= new EffectFadeProWidget(this);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(mEventTreeWidget);
	mainLayout->addWidget(mDeleteModelBtn);

	mainLayout->addWidget(mModelVisibleProWidget);
	mainLayout->addWidget(mModelAniProWidget);
	mainLayout->addWidget(mModelBindProWidget);
	mainLayout->addWidget(mPUStartProWidget);
	mainLayout->addWidget(mPUStopProWidget);
	mainLayout->addWidget(mPUBindProWidget);
	mainLayout->addWidget(mWeaponLightProWidget);
	mainLayout->addWidget(mEffectFadeProWidget);

	setLayout(mainLayout);

	mModelVisibleProWidget->setVisible(false);
	mModelAniProWidget->setVisible(false);
	mModelBindProWidget->setVisible(false);
	mPUStartProWidget->setVisible(false);
	mPUStopProWidget->setVisible(false);
	mPUBindProWidget->setVisible(false);
	mWeaponLightProWidget->setVisible(false);
	mEffectFadeProWidget->setVisible(false);
}

void EventWidget::init()
{
	mEventTreeWidget->setAlternatingRowColors(true);
	mEventTreeWidget->header()->setMovable(false);

	connect(mDeleteModelBtn, SIGNAL(clicked()), this, SLOT(deleteClicked()));
	connect(mEventTreeWidget, SIGNAL(itemPressed(QTreeWidgetItem *, int)), this, SLOT(changeSeleted(QTreeWidgetItem *, int)));
}

void EventWidget::deleteClicked()
{
	if (mSeletedItem)
	{
		int index = mEventTreeWidget->indexOfTopLevelItem(mSeletedItem);
		mEventTreeWidget->takeTopLevelItem(index)->removeChild(mSeletedItem);

		IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
		if (!component)
			return;

		IEffectEvent* effectevent =	
			component->getEffectEvent(mSeletedItem->text(0).toStdString());

		if (effectevent)
		{
			IEffectXmlSerializer* effectxmlSer = component->getEffectXmlSerializer();
			if (effectxmlSer)
				effectxmlSer->removeEffectObjectFormat(effectevent->getName().c_str(), effectevent->getType());

			CoreManager::getInstance().getCurEffectComponent()->destroyEffectEvent(effectevent->getName());

			effectevent = NULL;

			mSeletedItem = NULL;
			mDeleteModelBtn->setEnabled(false);
		}
	}
}

void EventWidget::changeSeleted(QTreeWidgetItem *item, int column)
{
	mSeletedItem = item;
	Str name = mSeletedItem->text(0).toStdString();
	Str typeName = mEventNameList[name];

	IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
	if (!component)
		return;

	IEffectXmlSerializer* effectxmlSer = component->getEffectXmlSerializer();
	if (!effectxmlSer)
		return;

	MG::IEffectObjectXmlFormat* format = 
		effectxmlSer->getEffectObjectFormat( name.c_str(), getEventType(typeName) );
	if ( format )
	{
		mDeleteModelBtn->setEnabled(true);

		mModelVisibleProWidget->setVisible(false);
		mModelAniProWidget->setVisible(false);
		mModelBindProWidget->setVisible(false);
		mPUStartProWidget->setVisible(false);
		mPUStopProWidget->setVisible(false);
		mPUBindProWidget->setVisible(false);
		mWeaponLightProWidget->setVisible(false);
		mEffectFadeProWidget->setVisible(false);

		MG::SceneObjectTypes objtype = format->getSceneObject()->getType();

		switch (objtype)
		{
		case SOT_ENTITY:
			break;
		case EOT_PU:
			break;
		case EOT_TIMELINE:
			break;
		case EOT_MODEL_VISIBLE_EVENT:
			{
				mModelVisibleProWidget->loadElementProps(format);
				mModelVisibleProWidget->setVisible(true);
				break;
			}
		case EOT_MODEL_ANIMATION_EVENT:
			{
				mModelAniProWidget->loadElementProps(format);
				mModelAniProWidget->setVisible(true);
				break;
			}
		case EOT_MODEL_BIND_EVENT:
			{
				mModelBindProWidget->loadElementProps(format);
				mModelBindProWidget->setVisible(true);
				break;
			}
		case EOT_PU_START_EVENT:
			{
				mPUStartProWidget->loadElementProps(format);
				mPUStartProWidget->setVisible(true);
				break;
			}
		case EOT_PU_STOP_EVENT:
			{
				mPUStopProWidget->loadElementProps(format);
				mPUStopProWidget->setVisible(true);
				break;
			}
		case EOT_PU_BIND_EVENT:
			{
				mPUBindProWidget->loadElementProps(format);
				mPUBindProWidget->setVisible(true);
				break;
			}
		case EOT_WEAPON_LIGHT_EVENT:
			{
				mWeaponLightProWidget->loadElementProps(format);
				mWeaponLightProWidget->setVisible(true);
				break;
			}
		case EOT_EFFECT_FADE_EVENT:
			{
				mEffectFadeProWidget->loadElementProps(format);
				mEffectFadeProWidget->setVisible(true);
				break;
			}
		}
	}
}

void EventWidget::addNameToList(const std::string& name, const std::string& typeName)
{
	QTreeWidgetItem* event = new QTreeWidgetItem(mEventTreeWidget);
	event->setText(0, QString(name.c_str()));

	mEventNameList[name] = typeName;
}

QTreeWidgetItem* EventWidget::getCurrentItem()
{
	return mSeletedItem;
}

MG::SceneObjectTypes EventWidget::getEventType(const std::string& eventName )
{
	if (strcmp(eventName.c_str(), "Model_Visible") == 0)
		return EOT_MODEL_VISIBLE_EVENT;
	else
	if (strcmp(eventName.c_str(), "Model_Animation") == 0)
		return EOT_MODEL_ANIMATION_EVENT;
	else
	if (strcmp(eventName.c_str(), "Model_Bind") == 0)
		return EOT_MODEL_BIND_EVENT;
	else
	if (strcmp(eventName.c_str(), "PU_Start") == 0)
		return EOT_PU_START_EVENT;
	else
	if (strcmp(eventName.c_str(), "PU_Stop") == 0)
		return EOT_PU_STOP_EVENT;
	else
	if (strcmp(eventName.c_str(), "PU_Bind") == 0)
		return EOT_PU_BIND_EVENT;
	else
	if (strcmp(eventName.c_str(), "Weapon_Light") == 0)
		return EOT_WEAPON_LIGHT_EVENT;
	else
	if (strcmp(eventName.c_str(), "Effect_Fade") == 0)
		return EOT_EFFECT_FADE_EVENT;

	return SOT_NULL;
}

void EventWidget::clear()
{
	mEventTreeWidget->clear();

	mDeleteModelBtn->setEnabled(false);
}

void EventWidget::setEventMap( std::map<std::string, std::string> eventmap )
{
	mEventNameList.clear();
	clear();
	
	std::map<std::string, std::string>::iterator iter = eventmap.begin();
	for (; iter != eventmap.end(); iter++)
	{
		mEventNameList[iter->first] = iter->second;

		QTreeWidgetItem* event = new QTreeWidgetItem(mEventTreeWidget);
		event->setText(0, QString(iter->first.c_str()));
	}

}