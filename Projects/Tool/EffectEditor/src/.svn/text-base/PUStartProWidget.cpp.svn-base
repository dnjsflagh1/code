#include <QtGui>
#include "PUStartProWidget.h"
#include "qttreepropertybrowser.h"
#include "qtpropertymanager.h"
#include "qteditorfactory.h"
#include "ComplexProperties.h"

#include "EventWidget.h"
#include "EntityWidget.h"
#include "EffectWidget.h"

#include "ExComponentWidget.h"
#include "GlobalOption.h"
#include "CoreManager.h"

using namespace EffectEditor;

PUStartProWidget::PUStartProWidget( QWidget *parent /*= 0*/, Qt::WFlags flags /*= 0*/ )
	: QWidget(parent)
	, mPropertyBrw(NULL)
	, mDoubleManager(NULL)
	, mDoubleSpinBoxFactory(NULL)
	, mCurrObjectXmlFormat(NULL)
	, mCurrentEntityResID(0)
{
	createWidget();
	init();
}

PUStartProWidget::~PUStartProWidget()
{
	MG_SAFE_DELETE(mPropertyBrw);
	MG_SAFE_DELETE(mDoubleManager);
	MG_SAFE_DELETE(mDoubleSpinBoxFactory);
	MG_SAFE_DELETE(mCurrObjectXmlFormat);
}

void PUStartProWidget::loadElementProps( MG::IEffectObjectXmlFormat* format )
{
	clearElementProps();

	mCurrObjectXmlFormat = format;

	MG::SceneObjectTypes objtype = mCurrObjectXmlFormat->getSceneObject()->getType();
	if (objtype != EOT_PU_START_EVENT)
		return;

	PU_Start_ProSet();
}

void PUStartProWidget::clearElementProps()
{
	mCurrObjectXmlFormat = NULL;
	mPropertyBrw->clear();

	mEffectList.clear();
}

void PUStartProWidget::createWidget()
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

void PUStartProWidget::init()
{
	mPropertyBrw->setFactoryForManager(mDoubleManager, mDoubleSpinBoxFactory);
	mPropertyBrw->setFactoryForManager(mEnumManager, mComboBoxFactory);
	mPropertyBrw->setAlternatingRowColors(true);

	connect(mDoubleManager, SIGNAL(valueChanged(QtProperty *, double)), this, SLOT(doubleValueChanged(QtProperty *, double)));
	connect(mEnumManager, SIGNAL(valueChanged(QtProperty *, int)), this, SLOT(enumValueChanged(QtProperty *, int)));
}

void PUStartProWidget::PU_Start_ProSet()
{
	XMLNode* parentNode       = mCurrObjectXmlFormat->getXmlElm();
	XMLNode* currNode         = parentNode->FirstChild();
	XMLNode* firstSiblingNode = currNode;
	XMLNode* nextNode         = NULL;

	Str puname;
	Flt  timepoint = 0.0f;
	while (currNode)
	{
		// 时间点
		XmlHelper::getAttribute(currNode->ToElement(), timepoint, "Timing" );

		// PU名
		XmlHelper::getAttribute(currNode->ToElement(), puname, "PUName" );

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
	setSeletedEffectIndex(prop, puname);
	mPropertyBrw->addProperty(prop);
}

void PUStartProWidget::setSeletedEffectIndex( QtProperty *pro, Str name )
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

void PUStartProWidget::enumValueChanged( QtProperty *pro, int index)
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

	IPUStartEffectEvent* pustartevent = 
		dynamic_cast<IPUStartEffectEvent*>(effectevent);

	QString proname = pro->propertyName();
	// 修改值
	if (StrCmp(proname.toStdString().c_str(), "PU Name") == 0)
	{
		pustartevent->setPUName(mEffectList[index].toStdString());
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

void PUStartProWidget::doubleValueChanged( QtProperty *pro, double dvalue)
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