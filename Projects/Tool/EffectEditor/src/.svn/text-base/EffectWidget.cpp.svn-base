#include "EffectWidget.h"
#include <QtGui>
#include "qttreepropertybrowser.h"
#include "qtpropertymanager.h"
#include "ComplexProperties.h"
#include "GlobalOption.h"
#include "CoreManager.h"

using namespace EffectEditor;

EffectWidget::EffectWidget(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent)
	, mEffectTreeWidget(NULL)
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

EffectWidget::~EffectWidget()
{
	MG_SAFE_DELETE(mVariantEditFactory);
	MG_SAFE_DELETE(mVector3Manager);
	MG_SAFE_DELETE(mPropertyBrw);
	MG_SAFE_DELETE(mDeleteModelBtn);
	MG_SAFE_DELETE(mEffectTreeWidget);
}

void EffectWidget::createWidget()
{
	mEffectTreeWidget = new QTreeWidget(this);
	mEffectTreeWidget->header()->hide();

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
	mainLayout->addWidget(mEffectTreeWidget);
	mainLayout->addWidget(mDeleteModelBtn);
	mainLayout->addWidget(mPropertyBrw);

	setLayout(mainLayout);
}

void EffectWidget::init()
{
	mEffectPos = Vec3(0, 0, 0);
	mEffecScale = Vec3(1, 1, 1);

	mEffectTreeWidget->setAlternatingRowColors(true);
	mEffectTreeWidget->header()->setMovable(false);

	connect(mEffectTreeWidget, SIGNAL(itemPressed(QTreeWidgetItem *, int)), this, SLOT(changeSeleted(QTreeWidgetItem *, int)));
	connect(mDeleteModelBtn, SIGNAL(clicked()), this, SLOT(deleteClicked()));
	connect(mVector3Manager, SIGNAL(valueChanged(QtProperty *, const QVariant &)), this, SLOT(vector3ValueChanged(QtProperty *, const QVariant &)));
}

void EffectWidget::changeSeleted(QTreeWidgetItem *item, int column)
{
	mSeletedItem = item;
	IPUEffect* effect =	
		CoreManager::getInstance().getCurEffectComponent()->getPUEffect(mSeletedItem->text(0).toStdString());
	
	if (effect)
	{
		mDeleteModelBtn->setEnabled(true);
		effect->getSceneNode()->getPosition(mEffectPos);
		effect->getSceneNode()->getScale(mEffecScale);
		setProperty();
	}

}

void EffectWidget::addNameToList(std::string name)
{
	QTreeWidgetItem* effect = new QTreeWidgetItem(mEffectTreeWidget);
	effect->setText(0, QString(name.c_str()));

	mEffectNameList.push_back(name);
}

void EffectWidget::clear()
{
	mEffectTreeWidget->clear();
	mPropertyBrw->clear();

	mDeleteModelBtn->setEnabled(false);
}

void EffectWidget::deleteClicked()
{
	if (mSeletedItem)
	{
		int index = mEffectTreeWidget->indexOfTopLevelItem(mSeletedItem);
		mEffectTreeWidget->takeTopLevelItem(index)->removeChild(mSeletedItem);

		Str name = mSeletedItem->text(0).toStdString();
		std::list<std::string>::iterator iter = mEffectNameList.begin();
		for ( ; iter != mEffectNameList.end(); iter++)
		{
			if ( StrCmp((*iter).c_str(), name.c_str()) == 0)
			{
				mEffectNameList.erase(iter);
				break;
			}
		}

		IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
		if (!component)
			return;

		IPUEffect* effect =	component->getPUEffect(name);

		if (effect)
		{
			IEffectXmlSerializer* effectxmlSer = component->getEffectXmlSerializer();
			if (effectxmlSer)
				effectxmlSer->removeEffectObjectFormat(effect->getName().c_str(), effect->getType());

			CoreManager::getInstance().getCurEffectComponent()->destroyPUEffect(effect->getName());

			effect = NULL;

			mSeletedItem = NULL;
			mPropertyBrw->clear();
			mDeleteModelBtn->setEnabled(false);
		}
	}
	
}

void EffectWidget::vector3ValueChanged( QtProperty *pro, const QVariant &var)
{
	if (!mSeletedItem)
		return;

	IPUEffect* effect =	
		CoreManager::getInstance().getCurEffectComponent()->getPUEffect(mSeletedItem->text(0).toStdString());

	if (!effect)
		return;

	QRectF rval = qVariantValue<QRectF>(var);
	Vec3 qval(rval.x(), rval.y(), rval.width());

	QString proname = pro->propertyName();
	if (StrCmp(proname.toStdString().c_str(), "Position") == 0)
	{
		effect->getSceneNode()->setPosition(qval);
	}
	else 
	if (StrCmp(proname.toStdString().c_str(), "Scale") == 0)
	{
		if (qval.x<=0 || qval.y<=0 || qval.z<=0)
			return;

		effect->getSceneNode()->setScale(qval);
	}
}

void EffectWidget::setProperty()
{
	QRectF  vrf;
	QtProperty *prop = mVector3Manager->addProperty(QVariant::RectF, tr("Position"));
	prop->setWhatsThis("0");
	mVector3Manager->setPropertyNames(prop, "X", "Y", "Z");
	vrf = QRectF(mEffectPos.x, mEffectPos.y, mEffectPos.z, 0);
	mVector3Manager->setValue(prop, vrf);
	mPropertyBrw->addProperty(prop);

	prop = mVector3Manager->addProperty(QVariant::RectF, tr("Scale"));
	prop->setWhatsThis("1");
	mVector3Manager->setPropertyNames(prop, "X", "Y", "Z");
	vrf = QRectF(mEffecScale.x, mEffecScale.y, mEffecScale.z, 0);
	mVector3Manager->setValue(prop, vrf);
	mPropertyBrw->addProperty(prop);
}

std::list<std::string>& EffectWidget::getEffectList()
{
	return mEffectNameList;
}

void EffectWidget::setEffectList( std::list<std::string> &list )
{
	mEffectNameList.clear();
	clear();

	std::list<std::string>::iterator iter = list.begin();
	for (; iter != list.end(); iter++)
	{
		mEffectNameList.push_back(*iter);

		QTreeWidgetItem* effect = new QTreeWidgetItem(mEffectTreeWidget);
		effect->setText(0, QString((*iter).c_str()));
	}
}