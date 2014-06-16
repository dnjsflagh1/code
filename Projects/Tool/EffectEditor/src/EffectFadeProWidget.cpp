#include <QtGui>
#include "EffectFadeProWidget.h"
#include "qttreepropertybrowser.h"
#include "qtpropertymanager.h"
#include "qteditorfactory.h"
#include "ComplexProperties.h"

#include "EventWidget.h"
#include "EffectWidget.h"

#include "ExComponentWidget.h"
#include "GlobalOption.h"
#include "CoreManager.h"

using namespace EffectEditor;

EffectFadeProWidget::EffectFadeProWidget( QWidget *parent /*= 0*/, Qt::WFlags flags /*= 0*/ )
	: QWidget(parent)
	, mPropertyBrw(NULL)
	, mDoubleManager(NULL)
	, mDoubleSpinBoxFactory(NULL)
	, mCurrObjectXmlFormat(NULL)
{
	createWidget();
	init();
}

EffectFadeProWidget::~EffectFadeProWidget()
{
	MG_SAFE_DELETE(mPropertyBrw);
	MG_SAFE_DELETE(mDoubleManager);
	MG_SAFE_DELETE(mDoubleSpinBoxFactory);
	MG_SAFE_DELETE(mCurrObjectXmlFormat);
}

void EffectFadeProWidget::loadElementProps( MG::IEffectObjectXmlFormat* format )
{
	clearElementProps();

	mCurrObjectXmlFormat = format;

	MG::SceneObjectTypes objtype = mCurrObjectXmlFormat->getSceneObject()->getType();
	if (objtype != EOT_EFFECT_FADE_EVENT)
		return;

	Effect_Fade_ProSet();
}

void EffectFadeProWidget::clearElementProps()
{
	mCurrObjectXmlFormat = NULL;
	mPropertyBrw->clear();

	mEffectList.clear();
}

void EffectFadeProWidget::createWidget()
{
	mPropertyBrw = new QtTreePropertyBrowser(this);
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(mPropertyBrw);

	setLayout(mainLayout);

	mDoubleManager = new QtDoublePropertyManager(this);
	mEnumManager = new QtEnumPropertyManager(this);

	mDoubleSpinBoxFactory = new QtDoubleSpinBoxFactory(this);
	mComboBoxFactory = new QtEnumEditorFactory(this);
}

void EffectFadeProWidget::init()
{
	mPropertyBrw->setFactoryForManager(mDoubleManager, mDoubleSpinBoxFactory);
	mPropertyBrw->setFactoryForManager(mEnumManager, mComboBoxFactory);
	mPropertyBrw->setAlternatingRowColors(true);

	connect(mDoubleManager, SIGNAL(valueChanged(QtProperty *, double)), this, SLOT(doubleValueChanged(QtProperty *, double)));
	connect(mEnumManager, SIGNAL(valueChanged(QtProperty *, int)), this, SLOT(enumValueChanged(QtProperty *, int)));
}

void EffectFadeProWidget::Effect_Fade_ProSet()
{
	// 设置
	XMLNode* parentNode       = mCurrObjectXmlFormat->getXmlElm();
	XMLNode* currNode         = parentNode->FirstChild();
	XMLNode* firstSiblingNode = currNode;
	XMLNode* nextNode         = NULL;

	Str8 modelname, fadetype;
	Flt  timepoint = 0.0f;
	Flt  fadeTimepoint = 0.0f;
	Flt  durtimepoint = 0.0f;
	Flt  fadevalue = 0.0f;
	while (currNode)
	{
		// 时间点
		XmlHelper::getAttribute(currNode->ToElement(), timepoint, "Timing" );

		// PU名
		XmlHelper::getAttribute(currNode->ToElement(), modelname, "PUName" );

		// 渐变时间点
		XmlHelper::getAttribute(currNode->ToElement(), fadeTimepoint, "FadeTiming" );

		// 持续时间
		XmlHelper::getAttribute(currNode->ToElement(), durtimepoint, "DurTiming" );

		// 渐变类型
		XmlHelper::getAttribute(currNode->ToElement(), fadetype, "Type" );

		// 渐变值
		XmlHelper::getAttribute(currNode->ToElement(), fadevalue, "Value" );

		nextNode    = currNode->NextSibling();
		if (nextNode&&nextNode==firstSiblingNode)
		{
			break;
		}
		currNode = nextNode;
	}

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
	setSeletedEffectIndex(prop, modelname);
	mPropertyBrw->addProperty(prop);

	//////////////////////////////////////////////////////////////////////////
	prop = mDoubleManager->addProperty(tr("FadeTime"));
	prop->setWhatsThis("2");
	mDoubleManager->setValue(prop, fadeTimepoint);
	mPropertyBrw->addProperty(prop);

	//////////////////////////////////////////////////////////////////////////
	prop = mDoubleManager->addProperty(tr("DurationTime"));
	prop->setWhatsThis("3");
	mDoubleManager->setValue(prop, durtimepoint);
	mPropertyBrw->addProperty(prop);

	//////////////////////////////////////////////////////////////////////////
	prop = mEnumManager->addProperty(tr("FadeType"));
	prop->setWhatsThis("4");
	QStringList fadetypeList;
	fadetypeList.push_back("Scale");
	fadetypeList.push_back("Velocity");
	mEnumManager->setEnumNames(prop, fadetypeList);
	mPropertyBrw->addProperty(prop);

	//////////////////////////////////////////////////////////////////////////
	prop = mDoubleManager->addProperty(tr("FadeValue"));
	prop->setWhatsThis("5");
	mDoubleManager->setValue(prop, fadevalue);
	mPropertyBrw->addProperty(prop);
}

void EffectFadeProWidget::setSeletedEffectIndex( QtProperty *pro, Str name )
{
	QStringList::Iterator iter = mEffectList.begin();
	int i = 0;
	for (; iter != mEffectList.end(); iter++)
	{
		Str puName = (*iter).toStdString();
		if (StrCmp(puName.c_str(), name.c_str()) == 0)
		{
			mEnumManager->setValue(pro, i);
			break;
		}	
		i++;
	}
	mEnumManager->setValue(pro, -1);
}

void EffectFadeProWidget::enumValueChanged( QtProperty *pro, int index)
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

	IEffectFadeEvent* effectfadeevent =
		dynamic_cast<IEffectFadeEvent*>(effectevent);

	QString proname = pro->propertyName();
	// 修改值
	if (StrCmp(proname.toStdString().c_str(), "PU Name") == 0)
	{
		Str puname = mEffectList[index].toStdString();
		effectfadeevent->setPUName(puname);
	}
	else
	if (StrCmp(proname.toStdString().c_str(), "FadeType") == 0)
	{
		if (index == 0)
		{
			effectfadeevent->setFadeType(EFT_SCALE);
		}
		else
		if (index == 1)
		{
			effectfadeevent->setFadeType(EFT_VELOCITY);
		}
		else
			effectfadeevent->setFadeType(EFT_NULL);
	}

	IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
	if (!component)
		return;

	IEffectXmlSerializer* effectxmlSer = component->getEffectXmlSerializer();
	if (!effectxmlSer)
		return;

	// 填充到xml
	MG::IEffectObjectXmlFormat* format = 
		effectxmlSer->getEffectObjectFormat( effectfadeevent->getName().c_str(), effectfadeevent->getType() );
	if ( format )
	{
		format->fill(true);
	}
}

void EffectFadeProWidget::doubleValueChanged( QtProperty *pro, double dvalue)
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

	IEffectFadeEvent* effectfadeevent =
		dynamic_cast<IEffectFadeEvent*>(effectevent);

	// 修改值
	QString proname = pro->propertyName();
	if (StrCmp(proname.toStdString().c_str(), "Time Point") == 0)
	{
		effectfadeevent->setEventTimePoint(dvalue);
	}
	else
	if (StrCmp(proname.toStdString().c_str(), "FadeTime") == 0)
	{
		effectfadeevent->setFadeTimePoint(dvalue);
	}
	else
	if (StrCmp(proname.toStdString().c_str(), "DurationTime") == 0)
	{
		effectfadeevent->setDurationTime(dvalue);
	}
	else
	if (StrCmp(proname.toStdString().c_str(), "FadeValue") == 0)
	{
		effectfadeevent->setFadeValue(dvalue);
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