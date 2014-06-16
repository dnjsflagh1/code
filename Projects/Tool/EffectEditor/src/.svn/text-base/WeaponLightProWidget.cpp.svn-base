#include <QtGui>
#include "WeaponLightProWidget.h"
#include "qttreepropertybrowser.h"
#include "qtpropertymanager.h"
#include "qteditorfactory.h"
#include "ComplexProperties.h"
#include "EventWidget.h"
#include "EffectWidget.h"

#include "ExComponentWidget.h"
#include "ExModelWidget.h"
#include "GlobalOption.h"
#include "CoreManager.h"


using namespace EffectEditor;

WeaponLightProWidget::WeaponLightProWidget( QWidget *parent /*= 0*/, Qt::WFlags flags /*= 0*/ )
	: QWidget(parent)
	, mPropertyBrw(NULL)
	, mDoubleManager(NULL)
	, mVector3Manager(NULL)
	, mVarManVec(NULL)
	, mDoubleSpinBoxFactory(NULL)
	, mVariantEditFactory(NULL)
	, mCurrObjectXmlFormat(NULL)
	, mCurrentEntityResID(0)
{
	createWidget();
	init();
}

WeaponLightProWidget::~WeaponLightProWidget()
{
	MG_SAFE_DELETE(mPropertyBrw);
	MG_SAFE_DELETE(mDoubleManager);
	MG_SAFE_DELETE(mVector3Manager);
	MG_SAFE_DELETE(mVariantEditFactory);
	MG_SAFE_DELETE(mCurrObjectXmlFormat);
}

void WeaponLightProWidget::loadElementProps( MG::IEffectObjectXmlFormat* format )
{
	clearElementProps();

	mCurrObjectXmlFormat = format;

	MG::SceneObjectTypes objtype = mCurrObjectXmlFormat->getSceneObject()->getType();
	if (objtype != EOT_WEAPON_LIGHT_EVENT)
		return;

	Weapon_Light_ProSet();
}

void WeaponLightProWidget::clearElementProps()
{
	mCurrObjectXmlFormat = NULL;
	mPropertyBrw->clear();

	mExEntityIndexList.clear();
	mEffectList.clear();
}

void WeaponLightProWidget::createWidget()
{
	mPropertyBrw = new QtTreePropertyBrowser(this);
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(mPropertyBrw);

	setLayout(mainLayout);

	mDoubleManager = new QtDoublePropertyManager(this);
	mEnumManager = new QtEnumPropertyManager(this);

	mVariantEditFactory = new QtVariantEditorFactory(this);
	mDoubleSpinBoxFactory = new QtDoubleSpinBoxFactory(this);
	mComboBoxFactory = new QtEnumEditorFactory(this);

	mVector3Manager = new Vector3Manager(this);
}

void WeaponLightProWidget::init()
{
	mVarManVec = mVector3Manager;

	mPropertyBrw->setFactoryForManager(mDoubleManager, mDoubleSpinBoxFactory);
	mPropertyBrw->setFactoryForManager(mVarManVec, mVariantEditFactory);
	mPropertyBrw->setFactoryForManager(mEnumManager, mComboBoxFactory);
	mPropertyBrw->setAlternatingRowColors(true);

	connect(mDoubleManager, SIGNAL(valueChanged(QtProperty *, double)), this, SLOT(doubleValueChanged(QtProperty *, double)));
	connect(mEnumManager, SIGNAL(valueChanged(QtProperty *, int)), this, SLOT(enumValueChanged(QtProperty *, int)));

	connect(mVector3Manager, SIGNAL(valueChanged(QtProperty *, const QVariant &)), this, SLOT(vector3ValueChanged(QtProperty *, const QVariant &)));
}

void WeaponLightProWidget::Weapon_Light_ProSet()
{
	XMLNode* parentNode       = mCurrObjectXmlFormat->getXmlElm();
	XMLNode* currNode         = parentNode->FirstChild();
	XMLNode* firstSiblingNode = currNode;
	XMLNode* nextNode         = NULL;

	Str puname;
	Str bindExEntityName;
	QRectF  vrf;
	Vec3 pos = Vec3(0,0,0);
	Str8 posx,posy,posz;
	Flt  timepoint = 0.0f;
	U32	 trailLength = 0;
	U32  trailWidth = 0;
	Flt  trailLiveTime = 0;
	while (currNode)
	{
		// 时间点
		XmlHelper::getAttribute(currNode->ToElement(), timepoint, "Timing" );

		// PU名
		XmlHelper::getAttribute(currNode->ToElement(), puname, "PUName" );

		// 外部模型名
		XmlHelper::getAttribute(currNode->ToElement(), bindExEntityName, "BindExEntityName" );

		// 位置
		if (StrCmp(currNode->ToElement()->Value(), "PositionOffset") == 0)
		{
			XmlHelper::getAttribute(currNode->ToElement(), posx, "X" );
			XmlHelper::getAttribute(currNode->ToElement(), posy, "Y" );
			XmlHelper::getAttribute(currNode->ToElement(), posz, "Z" );
		}

		// 丝带的长度
		XmlHelper::getAttribute(currNode->ToElement(), trailLength, "Length" );

		// 丝带的宽度
		XmlHelper::getAttribute(currNode->ToElement(), trailWidth, "Width" );

		// 丝带的生存时间
		XmlHelper::getAttribute(currNode->ToElement(), trailLiveTime, "Time" );


		nextNode    = currNode->NextSibling();
		if (nextNode&&nextNode==firstSiblingNode)
		{
			break;
		}
		currNode = nextNode;
	}

	pos.x = atof(posx.c_str());
	pos.y = atof(posy.c_str());
	pos.z = atof(posz.c_str());

	//////////////////////////////////////////////////////////////////////////
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
	prop = mEnumManager->addProperty(tr("BindExEntity Name"));
	prop->setWhatsThis("2");

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
	////////////////////////////////////////////////////////////////////////////
	prop = mVector3Manager->addProperty(QVariant::RectF, tr("PositionOffset"));
	prop->setWhatsThis("3");
	vrf = QRectF(pos.x, pos.y, pos.z, 0);
	mVector3Manager->setValue(prop, vrf);
	mPropertyBrw->addProperty(prop);

	//////////////////////////////////////////////////////////////////////////
	prop = mDoubleManager->addProperty(tr("TrailLength"));
	prop->setWhatsThis("4");
	mDoubleManager->setValue(prop, trailLength);
	mPropertyBrw->addProperty(prop);

	//////////////////////////////////////////////////////////////////////////
	prop = mDoubleManager->addProperty(tr("TrailWidth"));
	prop->setWhatsThis("5");
	mDoubleManager->setValue(prop, trailWidth);
	mPropertyBrw->addProperty(prop);

	//////////////////////////////////////////////////////////////////////////
	prop = mDoubleManager->addProperty(tr("TrailLiveTime"));
	prop->setWhatsThis("6");
	mDoubleManager->setValue(prop, trailLiveTime);
	mPropertyBrw->addProperty(prop);
}

void WeaponLightProWidget::setSeletedExModelIndex( QtProperty *pro, Str name )
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

void WeaponLightProWidget::setSeletedEffectIndex( QtProperty *pro, Str name )
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

void WeaponLightProWidget::enumValueChanged(QtProperty *pro, int index)
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

	IWeaponLightEvent* weaponLightevent = 
		dynamic_cast<IWeaponLightEvent*>(effectevent);

	QString proname = pro->propertyName();
	// 修改值
	if (StrCmp(proname.toStdString().c_str(), "PU Name") == 0)
	{
		weaponLightevent->setPUName(mEffectList[index].toStdString());
	}
	else 
	if (StrCmp(proname.toStdString().c_str(), "BindExEntity Name") == 0)
	{
		char exEntityindex[100];
		itoa(index, exEntityindex, 10);
		weaponLightevent->setBindExternalEntityName(exEntityindex);
	}

	IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
	if (!component)
		return;

	IEffectXmlSerializer* effectxmlSer = component->getEffectXmlSerializer();
	if (!effectxmlSer)
		return;

	// 填充到xml
	MG::IEffectObjectXmlFormat* format = 
		effectxmlSer->getEffectObjectFormat( weaponLightevent->getName().c_str(), weaponLightevent->getType() );
	if ( format )
	{
		format->fill(true);
	}
}

void WeaponLightProWidget::vector3ValueChanged(QtProperty *pro, const QVariant &var)
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

	IWeaponLightEvent* weaponLightevent = 
		dynamic_cast<IWeaponLightEvent*>(effectevent);

	// 修改值
	QRectF rval = qVariantValue<QRectF>(var);
	Vec3 qval(rval.x(), rval.y(), rval.width());
	QString proname = pro->propertyName();
	if (StrCmp(proname.toStdString().c_str(), "PositionOffset") == 0)
	{
		weaponLightevent->setPosOffset(qval);
	}

	IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
	if (!component)
		return;

	IEffectXmlSerializer* effectxmlSer = component->getEffectXmlSerializer();
	if (!effectxmlSer)
		return;

	// 填充到xml
	MG::IEffectObjectXmlFormat* format = 
		effectxmlSer->getEffectObjectFormat( weaponLightevent->getName().c_str(), weaponLightevent->getType() );
	if ( format )
	{
		format->fill(true);
	}
}

void WeaponLightProWidget::doubleValueChanged( QtProperty *pro, double dvalue)
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

	IWeaponLightEvent* weaponLightevent = 
		dynamic_cast<IWeaponLightEvent*>(effectevent);

	// 修改值
	QString proname = pro->propertyName();
	if (StrCmp(proname.toStdString().c_str(), "Time Point") == 0)
	{
		weaponLightevent->setEventTimePoint(dvalue);
	}
	if (StrCmp(proname.toStdString().c_str(), "TrailLength") == 0)
	{
		weaponLightevent->setTrailLength(dvalue);
	}
	if (StrCmp(proname.toStdString().c_str(), "TrailWidth") == 0)
	{
		weaponLightevent->setTrailWidth(dvalue);
	}
	if (StrCmp(proname.toStdString().c_str(), "TrailLiveTime") == 0)
	{
		weaponLightevent->setTrailLiveTime(dvalue);
	}

	IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
	if (!component)
		return;

	IEffectXmlSerializer* effectxmlSer = component->getEffectXmlSerializer();
	if (!effectxmlSer)
		return;

	// 填充到xml
	MG::IEffectObjectXmlFormat* format = 
		effectxmlSer->getEffectObjectFormat( weaponLightevent->getName().c_str(), weaponLightevent->getType() );
	if ( format )
	{
		format->fill(true);
	}

}