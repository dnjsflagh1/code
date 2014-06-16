#include "ExModelWidget.h"
#include <QtGui>
#include "qttreepropertybrowser.h"
#include "qtpropertymanager.h"
#include "ComplexProperties.h"
#include "GlobalOption.h"
#include "CoreManager.h"
#include "IEffectXmlSerializer.h"
#include "IEntity.h"
#include "IEffectComponent.h"
#include "IEntityAccessory.h"

using namespace EffectEditor;

ExModelWidget::ExModelWidget(QWidget *parent/* = 0*/, Qt::WFlags flag/* = 0*/)
	: QWidget(parent)
	, mEntityTreeWidget(NULL)
	, mDeleteModelBtn(NULL)
	, mPlayAnimationBtn(NULL)
	, mStopAnimationBtn(NULL)
	, mBindWeaponBtn(NULL)
	, mPropertyBrw(NULL)
	, mVector3Manager(NULL)
	, mVarManVec(NULL)
	, mVariantEditFactory(NULL)
	, mEnumManager(NULL)
	, mComboBoxFactory(NULL)
	, mSeletedItem(NULL)
{
	createWidget();
	init();
}

ExModelWidget::~ExModelWidget()
{
	MG_SAFE_DELETE(mVariantEditFactory);
	MG_SAFE_DELETE(mVector3Manager);
	MG_SAFE_DELETE(mPropertyBrw);
	MG_SAFE_DELETE(mDeleteModelBtn);
	MG_SAFE_DELETE(mEntityTreeWidget);
}

void ExModelWidget::createWidget()
{
	mEntityTreeWidget = new QTreeWidget(this);
	mEntityTreeWidget->header()->hide();

	mDeleteModelBtn = new QPushButton(this);
	mDeleteModelBtn->setText("Delete");
	mDeleteModelBtn->sizeHint();
	mDeleteModelBtn->setEnabled(false);

	mPlayAnimationBtn = new QPushButton(this);
	mPlayAnimationBtn->setText("Play Animation");
	mPlayAnimationBtn->sizeHint();

	mStopAnimationBtn = new QPushButton(this);
	mStopAnimationBtn->setText("Stop Animation");
	mStopAnimationBtn->sizeHint();

	mBindWeaponBtn = new QPushButton(this);
	mBindWeaponBtn->setText("Bind Weapon");
	mBindWeaponBtn->sizeHint();

	mPropertyBrw = new QtTreePropertyBrowser(this);
	mVector3Manager = new Vector3Manager(this);
	mEnumManager = new QtEnumPropertyManager(this);

	mVariantEditFactory = new QtVariantEditorFactory(this);
	mComboBoxFactory = new QtEnumEditorFactory(this);

	mVarManVec = mVector3Manager;
	mPropertyBrw->setFactoryForManager(mVarManVec, mVariantEditFactory);
	mPropertyBrw->setFactoryForManager(mEnumManager, mComboBoxFactory);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(mEntityTreeWidget);
	mainLayout->addWidget(mDeleteModelBtn);
	mainLayout->addWidget(mPropertyBrw);

	QHBoxLayout *subLayout = new QHBoxLayout;
	subLayout->addWidget(mPlayAnimationBtn);
	subLayout->addWidget(mStopAnimationBtn);
	subLayout->addWidget(mBindWeaponBtn);

	mainLayout->addLayout(subLayout);
	setLayout(mainLayout);
}

void ExModelWidget::init()
{
	mExEntityPos = Vec3(0, 0, 0);
	mExEntityScale = Vec3(1, 1, 1);

	connect(mEntityTreeWidget, SIGNAL(itemPressed(QTreeWidgetItem *, int)), this, SLOT(changeSeleted(QTreeWidgetItem *, int)));
	connect(mDeleteModelBtn, SIGNAL(clicked()), this, SLOT(deleteClicked()));
	connect(mVector3Manager, SIGNAL(valueChanged(QtProperty *, const QVariant &)), this, SLOT(vector3ValueChanged(QtProperty *, const QVariant &)));

	connect(mPlayAnimationBtn, SIGNAL(clicked()), this, SLOT(playAnimationClicked()));
	connect(mStopAnimationBtn, SIGNAL(clicked()), this, SLOT(stopAnimationClicked()));
	connect(mBindWeaponBtn, SIGNAL(clicked()), this, SLOT(bindWeaponClicked()));
	connect(mEnumManager, SIGNAL(valueChanged(QtProperty *, int)), this, SLOT(enumValueChanged(QtProperty *, int)));
}

void ExModelWidget::addNameToList(std::string name)
{
	QTreeWidgetItem* entity = new QTreeWidgetItem(mEntityTreeWidget);
	entity->setText(0, QString(name.c_str()));

	mEntityNameList.push_back(name);
}

void ExModelWidget::clear()
{
	mEntityTreeWidget->clear();
	mPropertyBrw->clear();

	mDeleteModelBtn->setEnabled(false);
}

void ExModelWidget::changeSeleted(QTreeWidgetItem *item, int column)
{
	mSeletedItem = item;
	IEntity* entity =	
		CoreManager::getInstance().getCurEffectComponent()->getSlotModelEffect(mSeletedItem->text(0).toStdString());

	if (entity)
	{
		mDeleteModelBtn->setEnabled(true);
		entity->getSceneNode()->getPosition(mExEntityPos);
		entity->getSceneNode()->getScale(mExEntityScale);
		setProperty(entity->getModelObject()->getModelDeclarationID());
	}
}

void ExModelWidget::playAnimationClicked()
{
	if (!mSeletedItem)
		return;

	IEntity* entity =	
		CoreManager::getInstance().getCurEffectComponent()->getSlotModelEffect(mSeletedItem->text(0).toStdString());

	if (entity)
	{
		IAnimationController* animationController =
			entity->getAnimationController();
		if (animationController)
		{
			animationController->play(mSelectedAnimationName.c_str());
			animationController->setLoop(mSelectedAnimationName.c_str(), true);
		}
	}
}

void ExModelWidget::stopAnimationClicked()
{
	if (!mSeletedItem)
		return;

	IEntity* entity =	
		CoreManager::getInstance().getCurEffectComponent()->getSlotModelEffect(mSeletedItem->text(0).toStdString());

	if (entity && !mSelectedAnimationName.empty())
	{
		// 设置模型动画名(是否循环), 可以由外部调用stop来停止循环
		IAnimationController* animationController =
			entity->getAnimationController();
		if (animationController)
			animationController->stop(mSelectedAnimationName.c_str());
	}
}

void ExModelWidget::bindWeaponClicked()
{
	if (mEntityNameList.size()<2)
		return;

	IEntity* roleEntity = NULL;
	IEntity* weaponEntity = NULL;

	Str entityname;

	std::list<std::string>::iterator iter = mEntityNameList.begin();
	int index = 0;
	for (; iter != mEntityNameList.end(); iter++)
	{
		if (index == 0)
		{
			roleEntity = CoreManager::getInstance().getScene()->getEntityfromSlot(index);
		}
		else if (index == 1)
		{
			weaponEntity = CoreManager::getInstance().getScene()->getEntityfromSlot(index);
			break;
		}
		index++;
	}

	if (roleEntity && weaponEntity)
	{
		IEntityAccessory entityAccessory;
		entityAccessory.isDepositLifeTime = false;
		entityAccessory.isSyncAnimation = false;
		entityAccessory.relativePosition = Vec3(0,0,0);
		entityAccessory.relativeQuaternion = Qua(1,0,0,0);
		entityAccessory.bindBoneName = "Bip01 L Hand";
		entityAccessory.sceneObject = weaponEntity;

		CoreManager::getInstance().getScene()->createEntityDynamicAccessorys(
			roleEntity, weaponEntity->getName().c_str(), weaponEntity->getModelObject()->getModelDeclarationID(),
			SOT_ENTITY, &entityAccessory);

	}
}

void ExModelWidget::deleteClicked()
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

		IEntity* entity = component->getSlotModelEffect(name);

		if (entity)
		{
			IEffectXmlSerializer* effectxmlSer = component->getEffectXmlSerializer();
			if (effectxmlSer)
				effectxmlSer->removeEffectObjectFormat(entity->getName().c_str(), entity->getType());

			CoreManager::getInstance().getScene()->destroySlotEntity(entity->getName().c_str());

			entity = NULL;

			mSeletedItem = NULL;
			mPropertyBrw->clear();
			mDeleteModelBtn->setEnabled(false);
		}
	}

}

void ExModelWidget::vector3ValueChanged( QtProperty *pro, const QVariant & var)
{
	if (!mSeletedItem)
		return;

	IEntity* entity =	
		CoreManager::getInstance().getCurEffectComponent()->getSlotModelEffect(mSeletedItem->text(0).toStdString());

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

void ExModelWidget::enumValueChanged( QtProperty *pro, int index)
{
	QString proname = pro->propertyName();

	if (StrCmp(proname.toStdString().c_str(), "Animation Name") == 0)
		mSelectedAnimationName = mAnimationList[index].toStdString().c_str();

}

void ExModelWidget::setProperty(unsigned int entityResID)
{
	mAnimationList.clear();

	QRectF  vrf;
	QtProperty *prop = mVector3Manager->addProperty(QVariant::RectF, tr("Position"));
	prop->setWhatsThis("0");
	mVector3Manager->setPropertyNames(prop, "X", "Y", "Z");
	vrf = QRectF(0, 0, 0, 0);
	mVector3Manager->setValue(prop, vrf);
	mPropertyBrw->addProperty(prop);

	prop = mVector3Manager->addProperty(QVariant::RectF, tr("Scale"));
	prop->setWhatsThis("1");
	mVector3Manager->setPropertyNames(prop, "X", "Y", "Z");
	vrf = QRectF(1, 1, 1, 0);
	mVector3Manager->setValue(prop, vrf);
	mPropertyBrw->addProperty(prop);

	prop = mEnumManager->addProperty(tr("Animation Name"));
	mAnimationList.push_back("");

	std::vector<std::string> actionList;
	CoreManager::getInstance().getEngineMain()->resourceMgr()->getActionList(entityResID, actionList);

	//std::vector<std::string> boneList;
	//CoreManager::getInstance().getEngineMain()->resourceMgr()->getBoneList(entityResID, boneList);

	std::vector<std::string>::iterator iter = actionList.begin();
	for ( ; iter != actionList.end(); iter++)
	{
		mAnimationList.push_back(QString((*iter).c_str()));
	}

	mEnumManager->setEnumNames(prop, mAnimationList);
	mEnumManager->setValue(prop, -1);
	mPropertyBrw->addProperty(prop);
}

std::list<std::string>& ExModelWidget::getExModelNameList()
{
	return mEntityNameList;
}

unsigned int ExModelWidget::getExModelNameListSize()
{
	return mEntityNameList.size();
}
