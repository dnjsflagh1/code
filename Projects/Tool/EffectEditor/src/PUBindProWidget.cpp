#include <QtGui>
#include "PUBindProWidget.h"
#include "qttreepropertybrowser.h"
#include "qtpropertymanager.h"
#include "qteditorfactory.h"
#include "ComplexProperties.h"
#include "EventWidget.h"
#include "EntityWidget.h"
#include "EffectWidget.h"

#include "ExComponentWidget.h"
#include "ExModelWidget.h"
#include "GlobalOption.h"
#include "CoreManager.h"

using namespace EffectEditor;

PUBindProWidget::PUBindProWidget( QWidget *parent /*= 0*/, Qt::WFlags flags /*= 0*/ )
: QWidget(parent)
, mPropertyBrw(NULL)
, mDoubleManager(NULL)
, mStringManager(NULL)
, mBoolManager(NULL)
, mQuaternionManager(NULL)
, mVector3Manager(NULL)
, mVarManQua(NULL)
, mVarManVec(NULL)
, mLineEditFactory(NULL)
, mCheckBoxFactory(NULL)
, mDoubleSpinBoxFactory(NULL)
, mVariantEditFactory(NULL)
, mCurrObjectXmlFormat(NULL)
, mCurrentEntityResID(0)
{
	createWidget();
	init();
}

PUBindProWidget::~PUBindProWidget()
{
	MG_SAFE_DELETE(mPropertyBrw);
	MG_SAFE_DELETE(mDoubleManager);
	MG_SAFE_DELETE(mStringManager);
	MG_SAFE_DELETE(mBoolManager);
	MG_SAFE_DELETE(mVector3Manager);
	MG_SAFE_DELETE(mQuaternionManager);
	MG_SAFE_DELETE(mLineEditFactory);
	MG_SAFE_DELETE(mCheckBoxFactory);
	MG_SAFE_DELETE(mVariantEditFactory);
	MG_SAFE_DELETE(mCurrObjectXmlFormat);
}

void PUBindProWidget::loadElementProps( MG::IEffectObjectXmlFormat* format )
{
	clearElementProps();

	mCurrObjectXmlFormat = format;

	MG::SceneObjectTypes objtype = mCurrObjectXmlFormat->getSceneObject()->getType();
	if (objtype != EOT_PU_BIND_EVENT)
		return;

	PU_Bind_ProSet();
}

void PUBindProWidget::clearElementProps()
{
	mCurrObjectXmlFormat = NULL;
	mPropertyBrw->clear();

	mEntityList.clear();
	mExEntityIndexList.clear();
	mEffectList.clear();
}

void PUBindProWidget::createWidget()
{
	mPropertyBrw = new QtTreePropertyBrowser(this);
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(mPropertyBrw);

	setLayout(mainLayout);

	mDoubleManager = new QtDoublePropertyManager(this);
	mStringManager = new QtStringPropertyManager(this);
	mBoolManager = new QtBoolPropertyManager(this);
	mEnumManager = new QtEnumPropertyManager(this);

	mLineEditFactory = new QtLineEditFactory(this);
	mCheckBoxFactory = new QtCheckBoxFactory(this);
	mVariantEditFactory = new QtVariantEditorFactory(this);
	mDoubleSpinBoxFactory = new QtDoubleSpinBoxFactory(this);
	mComboBoxFactory = new QtEnumEditorFactory(this);

	mQuaternionManager = new QuaternionManager(this);
	mVector3Manager = new Vector3Manager(this);
}

void PUBindProWidget::init()
{
	mVarManQua = mQuaternionManager;
	mVarManVec = mVector3Manager;

	mPropertyBrw->setFactoryForManager(mBoolManager, mCheckBoxFactory);
	mPropertyBrw->setFactoryForManager(mStringManager, mLineEditFactory);
	mPropertyBrw->setFactoryForManager(mDoubleManager, mDoubleSpinBoxFactory);
	mPropertyBrw->setFactoryForManager(mVarManQua, mVariantEditFactory);
	mPropertyBrw->setFactoryForManager(mVarManVec, mVariantEditFactory);
	mPropertyBrw->setFactoryForManager(mEnumManager, mComboBoxFactory);
	mPropertyBrw->setAlternatingRowColors(true);
	//mPropertyBrw->setIndentation(10);

	connect(mDoubleManager, SIGNAL(valueChanged(QtProperty *, double)), this, SLOT(doubleValueChanged(QtProperty *, double)));
	connect(mStringManager, SIGNAL(valueChanged(QtProperty *, const QString &)), this, SLOT(stringValueChanged(QtProperty *, const QString &)));
	connect(mBoolManager, SIGNAL(valueChanged(QtProperty *, bool)), this, SLOT(boolValueChanged(QtProperty *, bool)));
	connect(mEnumManager, SIGNAL(valueChanged(QtProperty *, int)), this, SLOT(enumValueChanged(QtProperty *, int)));

	connect(mQuaternionManager, SIGNAL(valueChanged(QtProperty *, const QVariant &)), this, SLOT(quaternionValueChanged(QtProperty *, const QVariant &)));
	connect(mVector3Manager, SIGNAL(valueChanged(QtProperty *, const QVariant &)), this, SLOT(vector3ValueChanged(QtProperty *, const QVariant &)));
}

void PUBindProWidget::PU_Bind_ProSet()
{
	XMLNode* parentNode       = mCurrObjectXmlFormat->getXmlElm();
	XMLNode* currNode         = parentNode->FirstChild();
	XMLNode* firstSiblingNode = currNode;
	XMLNode* nextNode         = NULL;

	Str puname;
	Str bindExEntityName;
	Str bindModelName;
	Str bindPUName;
	Str bindBoneName;
	QRectF  vrf;
	Vec3 pos = Vec3(0,0,0);
	Str8 posx,posy,posz;
	Vec4 orientation = Vec4(1,0,0,0);
	Str8 quaw,quax,quay,quaz;
	Bool bindRootComponent = false;
	Int isBindRootComponent = 0;
	Flt  timepoint = 0.0f;
	while (currNode)
	{
		// 时间点
		XmlHelper::getAttribute(currNode->ToElement(), timepoint, "Timing" );

		// 模型名
		XmlHelper::getAttribute(currNode->ToElement(), puname, "PUName" );

		// isBindRootComponent
		XmlHelper::getAttribute(currNode->ToElement(), isBindRootComponent, "Value" );

		// 外部模型名
		XmlHelper::getAttribute(currNode->ToElement(), bindExEntityName, "BindExEntityName" );

		// 内部模型名
		XmlHelper::getAttribute(currNode->ToElement(), bindModelName, "BindModelName" );

		// PU名
		XmlHelper::getAttribute(currNode->ToElement(), bindPUName, "BindPUName" );

		// 骨骼名
		XmlHelper::getAttribute(currNode->ToElement(), bindBoneName, "BindBoneName" );

		// 位置
		if (StrCmp(currNode->ToElement()->Value(), "PositionOffset") == 0)
		{
			XmlHelper::getAttribute(currNode->ToElement(), posx, "X" );
			XmlHelper::getAttribute(currNode->ToElement(), posy, "Y" );
			XmlHelper::getAttribute(currNode->ToElement(), posz, "Z" );
		}

		// 朝向
		if (StrCmp(currNode->ToElement()->Value(), "OrientationOffset") == 0)
		{
			XmlHelper::getAttribute(currNode->ToElement(), quaw, "W" );
			XmlHelper::getAttribute(currNode->ToElement(), quax, "X" );
			XmlHelper::getAttribute(currNode->ToElement(), quay, "Y" );
			XmlHelper::getAttribute(currNode->ToElement(), quaz, "Z" );
		}

		nextNode    = currNode->NextSibling();
		if (nextNode&&nextNode==firstSiblingNode)
		{
			break;
		}
		currNode = nextNode;
	}

	bindRootComponent = (isBindRootComponent!=0);

	pos.x = atof(posx.c_str());
	pos.y = atof(posy.c_str());
	pos.z = atof(posz.c_str());

	orientation.w = atof(quaw.c_str());
	orientation.x = atof(quax.c_str());
	orientation.y = atof(quay.c_str());
	orientation.z = atof(quaz.c_str());

	QtProperty *prop = mDoubleManager->addProperty(tr("Time Point"));
	prop->setWhatsThis("0");
	mDoubleManager->setValue(prop, timepoint);
	mPropertyBrw->addProperty(prop);

	//////////////////////////////////////////////////////////////////////////
	prop = mEnumManager->addProperty(tr("PU Name"));
	prop->setWhatsThis("1");

	std::list<std::string> effectlist =
		WindowSet::main_win->getExComponentWidget()->getEffectWidget()->getEffectList();
	mEffectList.push_back("");
	std::list<std::string>::iterator iter = effectlist.begin();
	for ( ; iter != effectlist.end(); iter++)
	{
		mEffectList.push_back(QString((*iter).c_str()));
	}
	mEnumManager->setEnumNames(prop, mEffectList);
	setSeletedEffectIndex(prop, puname);
	mPropertyBrw->addProperty(prop);

	//////////////////////////////////////////////////////////////////////////
	prop = mBoolManager->addProperty(tr("isBindRootComponent"));
	prop->setWhatsThis("2");
	mBoolManager->setValue(prop, bindRootComponent);
	mPropertyBrw->addProperty(prop);

	//////////////////////////////////////////////////////////////////////////
	prop = mEnumManager->addProperty(tr("BindExEntity Name"));
	prop->setWhatsThis("3");

	unsigned int exModelListSize =
		WindowSet::main_win->getExModelWidget()->getExModelNameListSize();

	mExEntityIndexList.push_back("");
	for (int i = 0; i < exModelListSize; i++)
	{
		char s[100];
		itoa(i+1, s, 10);
		mExEntityIndexList.push_back(QString(s));
	}
	mEnumManager->setEnumNames(prop, mExEntityIndexList);
	setSeletedExModelIndex(prop, bindExEntityName);
	mPropertyBrw->addProperty(prop);

	//////////////////////////////////////////////////////////////////////////
	prop = mEnumManager->addProperty(tr("BindModel Name"));
	prop->setWhatsThis("4");

	std::list<std::string> entitylist =
		WindowSet::main_win->getExComponentWidget()->getEntityWidget()->getEntityList();
	mEntityList.push_back("");
	std::list<std::string>::iterator bindlistiter = entitylist.begin();
	for ( ; bindlistiter != entitylist.end(); bindlistiter++)
	{
		mEntityList.push_back(QString((*bindlistiter).c_str()));
	}
	mEnumManager->setEnumNames(prop, mEntityList);
	setSeletedModelIndex(prop, bindModelName);
	mPropertyBrw->addProperty(prop);

	//////////////////////////////////////////////////////////////////////////
	prop = mEnumManager->addProperty(tr("BindPU Name"));
	prop->setWhatsThis("5");

	mEnumManager->setEnumNames(prop, mEffectList);
	setSeletedEffectIndex(prop, bindPUName);
	mPropertyBrw->addProperty(prop);

	//////////////////////////////////////////////////////////////////////////
	prop = mStringManager->addProperty(tr("BindBone Name"));
	prop->setWhatsThis("6");
	mStringManager->setValue(prop, bindBoneName.c_str());
	mPropertyBrw->addProperty(prop);

	//////////////////////////////////////////////////////////////////////////
	prop = mVector3Manager->addProperty(QVariant::RectF, tr("PositionOffset"));
	prop->setWhatsThis("7");
	mVector3Manager->setPropertyNames(prop, "X", "Y", "Z");
	vrf = QRectF(pos.x, pos.y, pos.z, 0);
	mVector3Manager->setValue(prop, vrf);
	mPropertyBrw->addProperty(prop);

	//////////////////////////////////////////////////////////////////////////
	prop = mQuaternionManager->addProperty(QVariant::RectF, tr("OrientationOffset"));
	prop->setWhatsThis("8");
	vrf = QRectF(orientation.x, orientation.y, orientation.z, orientation.w);
	mQuaternionManager->setValue(prop, vrf);
	mPropertyBrw->addProperty(prop);
}

void PUBindProWidget::setSeletedModelIndex( QtProperty *pro, Str name )
{
	QStringList::Iterator iter = mEntityList.begin();
	int i = 0;
	for (; iter != mEntityList.end(); iter++)
	{
		Str modelName = (*iter).toStdString();
		if (StrCmp(modelName.c_str(), name.c_str()) == 0)
		{
			mEnumManager->setValue(pro, i);
			break;
		}	
		i++;
	}
	mEnumManager->setValue(pro, -1);
}

void PUBindProWidget::setSeletedExModelIndex( QtProperty *pro, Str name )
{
	QStringList::Iterator iter = mExEntityIndexList.begin();
	int i = 0;
	for (; iter != mExEntityIndexList.end(); iter++)
	{
		Str exModelName = (*iter).toStdString();
		if (StrCmp(exModelName.c_str(), name.c_str()) == 0)
		{
			mEnumManager->setValue(pro, i);
			break;
		}	
		i++;
	}
	mEnumManager->setValue(pro, -1);
}

void PUBindProWidget::setSeletedEffectIndex( QtProperty *pro, Str name )
{
	QStringList::Iterator iter = mEffectList.begin();
	int i = 0;
	for (; iter != mEffectList.end(); iter++)
	{
		Str effectName = (*iter).toStdString();
		if (StrCmp(effectName.c_str(), name.c_str()) == 0)
		{
			mEnumManager->setValue(pro, i);
			break;
		}	
		i++;
	}
	mEnumManager->setValue(pro, -1);
}

void PUBindProWidget::stringValueChanged( QtProperty *pro, const QString & proValue )
{
	QTreeWidgetItem* seletedItem = 
		WindowSet::main_win->getExComponentWidget()->getEventWidget()->getCurrentItem();

	if (!seletedItem)
		return;

	Str name = seletedItem->text(0).toStdString();

	IEffectEvent* effectevent =	
		CoreManager::getInstance().getCurEffectComponent()->getEffectEvent(name);

	if (!effectevent)
		return;

	IPUBindEffectEvent* puBindevent =
		dynamic_cast<IPUBindEffectEvent*>(effectevent);

	QString proname = pro->propertyName();
	if (StrCmp(proname.toStdString().c_str(), "BindBone Name") == 0)
	{
		puBindevent->setBindBoneName(proValue.toStdString());
	}

	IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
	if (!component)
		return;

	IEffectXmlSerializer* effectxmlSer = component->getEffectXmlSerializer();
	if (!effectxmlSer)
		return;

	// 填充到xml
	MG::IEffectObjectXmlFormat* format = 
		effectxmlSer->getEffectObjectFormat( puBindevent->getName().c_str(), puBindevent->getType() );
	if ( format )
	{
		format->fill(true);
	}

}

void PUBindProWidget::boolValueChanged( QtProperty *pro, bool b )
{
	QTreeWidgetItem* seletedItem = 
		WindowSet::main_win->getExComponentWidget()->getEventWidget()->getCurrentItem();

	if (!seletedItem)
		return;

	Str name = seletedItem->text(0).toStdString();

	IEffectEvent* effectevent =	
		CoreManager::getInstance().getCurEffectComponent()->getEffectEvent(name);

	if (!effectevent)
		return;

	IPUBindEffectEvent* puBindevent =
		dynamic_cast<IPUBindEffectEvent*>(effectevent);

	QString proname = pro->propertyName();
	// 修改值

	if (StrCmp(proname.toStdString().c_str(), "isBindRootComponent") == 0)
	{
		puBindevent->setIsBindRootComponent(b);
	}

	IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
	if (!component)
		return;

	IEffectXmlSerializer* effectxmlSer = component->getEffectXmlSerializer();
	if (!effectxmlSer)
		return;

	// 填充到xml
	MG::IEffectObjectXmlFormat* format = 
		effectxmlSer->getEffectObjectFormat( puBindevent->getName().c_str(), puBindevent->getType() );
	if ( format )
	{
		format->fill(true);
	}
}

void PUBindProWidget::enumValueChanged(QtProperty *pro, int index)
{
	QTreeWidgetItem* seletedItem = 
		WindowSet::main_win->getExComponentWidget()->getEventWidget()->getCurrentItem();

	if (!seletedItem)
		return;

	Str name = seletedItem->text(0).toStdString();

	IEffectEvent* effectevent =	
		CoreManager::getInstance().getCurEffectComponent()->getEffectEvent(name);

	if (!effectevent)
		return;

	IPUBindEffectEvent* puBindevent =
		dynamic_cast<IPUBindEffectEvent*>(effectevent);

	QString proname = pro->propertyName();
	// 修改值
	if (StrCmp(proname.toStdString().c_str(), "PU Name") == 0)
	{
		puBindevent->setPUName(mEffectList[index].toStdString());
	}
	else 
	if (StrCmp(proname.toStdString().c_str(), "BindExEntity Name") == 0)
	{
		char exEntityindex[100];
		itoa(index, exEntityindex, 10);
		puBindevent->setBindExternalEntityName(exEntityindex);
	}
	else 
	if (StrCmp(proname.toStdString().c_str(), "BindModel Name") == 0)
	{
		puBindevent->setBindModelName(mEntityList[index].toStdString());
	}
	else
	if (StrCmp(proname.toStdString().c_str(), "BindPU Name") == 0)
	{
		puBindevent->setBindPUName(mEffectList[index].toStdString());
	}

	IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
	if (!component)
		return;

	IEffectXmlSerializer* effectxmlSer = component->getEffectXmlSerializer();
	if (!effectxmlSer)
		return;

	// 填充到xml
	MG::IEffectObjectXmlFormat* format = 
		effectxmlSer->getEffectObjectFormat( puBindevent->getName().c_str(), puBindevent->getType() );
	if ( format )
	{
		format->fill(true);
	}
}

void PUBindProWidget::quaternionValueChanged( QtProperty *pro, const QVariant &var)
{
	QTreeWidgetItem* seletedItem = 
		WindowSet::main_win->getExComponentWidget()->getEventWidget()->getCurrentItem();

	if (!seletedItem)
		return;

	Str name = seletedItem->text(0).toStdString();

	IEffectEvent* effectevent =	
		CoreManager::getInstance().getCurEffectComponent()->getEffectEvent(name);

	if (!effectevent)
		return;

	IPUBindEffectEvent* puBindevent =
		dynamic_cast<IPUBindEffectEvent*>(effectevent);

	// 修改值
	QRectF rval = qVariantValue<QRectF>(var);
	Vec4 qval(rval.height(), rval.x(), rval.y(), rval.width());
	QString proname = pro->propertyName();
	if (StrCmp(proname.toStdString().c_str(), "OrientationOffset") == 0)
	{
		puBindevent->setOriOffset(qval);
	}

	IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
	if (!component)
		return;

	IEffectXmlSerializer* effectxmlSer = component->getEffectXmlSerializer();
	if (!effectxmlSer)
		return;

	// 填充到xml
	MG::IEffectObjectXmlFormat* format = 
		effectxmlSer->getEffectObjectFormat( puBindevent->getName().c_str(), puBindevent->getType() );
	if ( format )
	{
		format->fill(true);
	}
}

void PUBindProWidget::vector3ValueChanged( QtProperty *pro, const QVariant &var)
{
	QTreeWidgetItem* seletedItem = 
		WindowSet::main_win->getExComponentWidget()->getEventWidget()->getCurrentItem();

	if (!seletedItem)
		return;

	Str name = seletedItem->text(0).toStdString();

	IEffectEvent* effectevent =	
		CoreManager::getInstance().getCurEffectComponent()->getEffectEvent(name);

	if (!effectevent)
		return;

	IPUBindEffectEvent* puBindevent =
		dynamic_cast<IPUBindEffectEvent*>(effectevent);

	// 修改值
	QRectF rval = qVariantValue<QRectF>(var);
	Vec3 qval(rval.x(), rval.y(), rval.width());
	QString proname = pro->propertyName();
	if (StrCmp(proname.toStdString().c_str(), "PositionOffset") == 0)
	{
		puBindevent->setPosOffset(qval);
	}

	IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
	if (!component)
		return;

	IEffectXmlSerializer* effectxmlSer = component->getEffectXmlSerializer();
	if (!effectxmlSer)
		return;

	// 填充到xml
	MG::IEffectObjectXmlFormat* format = 
		effectxmlSer->getEffectObjectFormat( puBindevent->getName().c_str(), puBindevent->getType() );
	if ( format )
	{
		format->fill(true);
	}
}

void PUBindProWidget::doubleValueChanged( QtProperty *pro, double dvalue)
{
	QTreeWidgetItem* seletedItem = 
		WindowSet::main_win->getExComponentWidget()->getEventWidget()->getCurrentItem();

	if (!seletedItem)
		return;

	Str name = seletedItem->text(0).toStdString();

	IEffectEvent* effectevent =	
		CoreManager::getInstance().getCurEffectComponent()->getEffectEvent(name);

	if (!effectevent)
		return;

	// 修改值
	QString proname = pro->propertyName();
	if (StrCmp(proname.toStdString().c_str(), "Time Point") == 0)
	{
		effectevent->setEventTimePoint(dvalue);
	}

	IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
	if (!component)
		return;

	IEffectXmlSerializer* effectxmlSer = component->getEffectXmlSerializer();
	if (!effectxmlSer)
		return;

	// 填充到xml
	MG::IEffectObjectXmlFormat* format = 
		effectxmlSer->getEffectObjectFormat( effectevent->getName().c_str(), effectevent->getType() );
	if ( format )
	{
		format->fill(true);
	}
}