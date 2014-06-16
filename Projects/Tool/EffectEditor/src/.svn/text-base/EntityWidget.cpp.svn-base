#include "EntityWidget.h"
#include <QtGui>
#include "qttreepropertybrowser.h"
#include "qtpropertymanager.h"
#include "ComplexProperties.h"
#include "GlobalOption.h"
#include "CoreManager.h"
#include "IEffectXmlSerializer.h"
#include "IEntity.h"
#include "IEffectComponent.h"

using namespace EffectEditor;

EntityWidget::EntityWidget(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent)
	, mEntityTreeWidget(NULL)
	, mDeleteModelBtn(NULL)
	, mPropertyBrw(NULL)
	, mVector3Manager(NULL)
	, mVarManVec(NULL)
	, mVariantEditFactory(NULL)
	, mSeletedItem(NULL)
{
	createWidget();
	init();
}

EntityWidget::~EntityWidget()
{
	MG_SAFE_DELETE(mVariantEditFactory);
	MG_SAFE_DELETE(mVector3Manager);
	MG_SAFE_DELETE(mPropertyBrw);
	MG_SAFE_DELETE(mDeleteModelBtn);
	MG_SAFE_DELETE(mEntityTreeWidget);
}

void EntityWidget::createWidget()
{
	mEntityTreeWidget = new QTreeWidget(this);
	mEntityTreeWidget->header()->hide();

	mDeleteModelBtn = new QPushButton(this);
	mDeleteModelBtn->setText("Delete");
	mDeleteModelBtn->sizeHint();
	mDeleteModelBtn->setEnabled(false);

	mPropertyBrw = new QtTreePropertyBrowser(this);

	mVariantEditFactory = new QtVariantEditorFactory(this);
	mVector3Manager = new Vector3Manager(this);

	mVarManVec = mVector3Manager;
	mPropertyBrw->setFactoryForManager(mVarManVec, mVariantEditFactory);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(mEntityTreeWidget);
	mainLayout->addWidget(mDeleteModelBtn);
	mainLayout->addWidget(mPropertyBrw);

	setLayout(mainLayout);
}

void EntityWidget::init()
{
	mEntityPos = Vec3(0, 0, 0);
	mEntityScale = Vec3(1, 1, 1);

	mEntityTreeWidget->setAlternatingRowColors(true);
	mEntityTreeWidget->header()->setMovable(false);

	connect(mDeleteModelBtn, SIGNAL(clicked()), this, SLOT(deleteClicked()));
	connect(mEntityTreeWidget, SIGNAL(itemPressed(QTreeWidgetItem *, int)), this, SLOT(changeSeleted(QTreeWidgetItem *, int)));
	connect(mVector3Manager, SIGNAL(valueChanged(QtProperty *, const QVariant &)), this, SLOT(vector3ValueChanged(QtProperty *, const QVariant &)));
}

void EntityWidget::changeSeleted(QTreeWidgetItem *item, int column)
{
	mSeletedItem = item;
	IEntity* entity =	
		CoreManager::getInstance().getCurEffectComponent()->getModelEffect(mSeletedItem->text(0).toStdString());

	if (entity )
	{
		mDeleteModelBtn->setEnabled(true);
		entity->getSceneNode()->getPosition(mEntityPos);
		entity->getSceneNode()->getScale(mEntityScale);
		setProperty();
	}
}

void EntityWidget::addNameToList(std::string name)
{
	QTreeWidgetItem* entity = new QTreeWidgetItem(mEntityTreeWidget);
	entity->setText(0, QString(name.c_str()));

	mEntityNameList.push_back(name);
}

void EntityWidget::clear()
{
	mEntityTreeWidget->clear();
	mPropertyBrw->clear();

	mDeleteModelBtn->setEnabled(false);
}

void EntityWidget::deleteClicked()
{
	if (mSeletedItem)
	{
		int index = mEntityTreeWidget->indexOfTopLevelItem(mSeletedItem);
		mEntityTreeWidget->takeTopLevelItem(index)->removeChild(mSeletedItem);

		Str name = mSeletedItem->text(0).toStdString();
		std::list<std::string>::iterator iter = mEntityNameList.begin();
		for ( ; iter != mEntityNameList.end(); iter++)
		{
			if ( StrCmp((*iter).c_str(), name.c_str()) == 0)
			{
				mEntityNameList.erase(iter);
				break;
			}
		}

		IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
		if (!component)
			return;

		IEntity* entity =	
			component->getModelEffect(name);

		if (entity)
		{
			IEffectXmlSerializer* effectxmlSer = component->getEffectXmlSerializer();
			if (effectxmlSer)
				effectxmlSer->removeEffectObjectFormat(entity->getName().c_str(), entity->getType());

			CoreManager::getInstance().getCurEffectComponent()->destroyModelEffect(entity->getName());

			entity = NULL;

			mSeletedItem = NULL;
			mPropertyBrw->clear();
			mDeleteModelBtn->setEnabled(false);
		}
	}
}

void EntityWidget::vector3ValueChanged( QtProperty *pro, const QVariant &var)
{
	if (!mSeletedItem)
		return;

	IEntity* entity =	
		CoreManager::getInstance().getCurEffectComponent()->getModelEffect(mSeletedItem->text(0).toStdString());

	if (!entity)
		return;

	QRectF rval = qVariantValue<QRectF>(var);
	Vec3 qval(rval.x(), rval.y(), rval.width());

	QString proname = pro->propertyName();
	if (StrCmp(proname.toStdString().c_str(), "Position") == 0)
	{
		entity->getSceneNode()->setPosition(qval);
	}
	else 
	if (StrCmp(proname.toStdString().c_str(), "Scale") == 0)
	{
		if (qval.x<=0 || qval.y<=0 || qval.z<=0)
			return;

		entity->getSceneNode()->setScale(qval);
	}
}

void EntityWidget::setProperty()
{
	mPropertyBrw->clear();

	QRectF  vrf;
	QtProperty *prop = mVector3Manager->addProperty(QVariant::RectF, tr("Position"));
	prop->setWhatsThis("0");
	mVector3Manager->setPropertyNames(prop, "X", "Y", "Z");
	vrf = QRectF(mEntityPos.x, mEntityPos.y, mEntityPos.z, 0);
	mVector3Manager->setValue(prop, vrf);
	mPropertyBrw->addProperty(prop);

	prop = mVector3Manager->addProperty(QVariant::RectF, tr("Scale"));
	prop->setWhatsThis("1");
	mVector3Manager->setPropertyNames(prop, "X", "Y", "Z");
	vrf = QRectF(mEntityScale.x, mEntityScale.y, mEntityScale.z, 0);
	mVector3Manager->setValue(prop, vrf);
	mPropertyBrw->addProperty(prop);
}

std::list<std::string>& EntityWidget::getEntityList()
{
	return mEntityNameList;
}

void EntityWidget::setEntityList( std::list<std::string>& list )
{
	mEntityNameList.clear();
	clear();

	std::list<std::string>::iterator iter = list.begin();
	for (; iter != list.end(); iter++)
	{
		mEntityNameList.push_back(*iter);

		QTreeWidgetItem* entity = new QTreeWidgetItem(mEntityTreeWidget);
		entity->setText(0, QString((*iter).c_str()));
	}
}