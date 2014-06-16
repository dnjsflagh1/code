#include <QtGui>
#include "ModelVisibleProWidget.h"
#include "qttreepropertybrowser.h"
#include "qtpropertymanager.h"
#include "qteditorfactory.h"
#include "ComplexProperties.h"

#include "EventWidget.h"
#include "EntityWidget.h"

#include "ExComponentWidget.h"
#include "GlobalOption.h"
#include "CoreManager.h"

using namespace EffectEditor;

ModelVisibleProWidget::ModelVisibleProWidget( QWidget *parent /*= 0*/, Qt::WFlags flags /*= 0*/ )
	: QWidget(parent)
	, mPropertyBrw(NULL)
	, mDoubleManager(NULL)
	, mBoolManager(NULL)
	, mCheckBoxFactory(NULL)
	, mDoubleSpinBoxFactory(NULL)
	, mCurrObjectXmlFormat(NULL)
	, mCurrentEntityResID(0)
{
	createWidget();
	init();
}

ModelVisibleProWidget::~ModelVisibleProWidget()
{
	MG_SAFE_DELETE(mPropertyBrw);
	MG_SAFE_DELETE(mDoubleManager);
	MG_SAFE_DELETE(mBoolManager);
	MG_SAFE_DELETE(mCheckBoxFactory);
	MG_SAFE_DELETE(mDoubleSpinBoxFactory);
	MG_SAFE_DELETE(mCurrObjectXmlFormat);
}

void ModelVisibleProWidget::loadElementProps( MG::IEffectObjectXmlFormat* format )
{
	clearElementProps();

	mCurrObjectXmlFormat = format;

	MG::SceneObjectTypes objtype = mCurrObjectXmlFormat->getSceneObject()->getType();
	if (objtype != EOT_MODEL_VISIBLE_EVENT)
		return;

	Model_Visible_ProSet();
}

void ModelVisibleProWidget::clearElementProps()
{
	mCurrObjectXmlFormat = NULL;
	mPropertyBrw->clear();

	mEntityList.clear();
}

void ModelVisibleProWidget::createWidget()
{
	mPropertyBrw = new QtTreePropertyBrowser(this);
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(mPropertyBrw);

	setLayout(mainLayout);

	mDoubleManager = new QtDoublePropertyManager(this);
	mBoolManager = new QtBoolPropertyManager(this);
	mEnumManager = new QtEnumPropertyManager(this);

	mCheckBoxFactory = new QtCheckBoxFactory(this);
	mDoubleSpinBoxFactory = new QtDoubleSpinBoxFactory(this);
	mComboBoxFactory = new QtEnumEditorFactory(this);
}

void ModelVisibleProWidget::init()
{
	mPropertyBrw->setFactoryForManager(mBoolManager, mCheckBoxFactory);
	mPropertyBrw->setFactoryForManager(mDoubleManager, mDoubleSpinBoxFactory);
	mPropertyBrw->setFactoryForManager(mEnumManager, mComboBoxFactory);
	mPropertyBrw->setAlternatingRowColors(true);

	connect(mDoubleManager, SIGNAL(valueChanged(QtProperty *, double)), this, SLOT(doubleValueChanged(QtProperty *, double)));
	connect(mBoolManager, SIGNAL(valueChanged(QtProperty *, bool)), this, SLOT(boolValueChanged(QtProperty *, bool)));
	connect(mEnumManager, SIGNAL(valueChanged(QtProperty *, int)), this, SLOT(enumValueChanged(QtProperty *, int)));
}

void ModelVisibleProWidget::Model_Visible_ProSet()
{
	// 设置
	XMLNode* parentNode       = mCurrObjectXmlFormat->getXmlElm();
	XMLNode* currNode         = parentNode->FirstChild();
	XMLNode* firstSiblingNode = currNode;
	XMLNode* nextNode         = NULL;

	Str8 modelname;
	BOOL bvisible = FALSE;
	Flt  timepoint = 0.0f;
	while (currNode)
	{
		// 时间点
		XmlHelper::getAttribute(currNode->ToElement(), timepoint, "Timing" );

		// 模型名
		XmlHelper::getAttribute(currNode->ToElement(), modelname, "ModelName" );

		// 是否可见
		Int visible = 1;
		XmlHelper::getAttribute(currNode->ToElement(), visible, "Value" );
		bvisible = (visible!=0);

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


	prop = mEnumManager->addProperty(tr("Model Name"));
	prop->setWhatsThis("1");

	std::list<std::string> entitylist =
		WindowSet::main_win->getExComponentWidget()->getEntityWidget()->getEntityList();
	mEntityList.push_back("");
	std::list<std::string>::iterator iter = entitylist.begin();
	for ( ; iter != entitylist.end(); iter++)
	{
		mEntityList.push_back(QString((*iter).c_str()));
	}
	mEnumManager->setEnumNames(prop, mEntityList);
	setSeletedModelIndex(prop, modelname);
	mPropertyBrw->addProperty(prop);

	prop = mBoolManager->addProperty(tr("Visible"));
	prop->setWhatsThis("2");
	mBoolManager->setValue(prop, bvisible);
	mPropertyBrw->addProperty(prop);
}

void ModelVisibleProWidget::setSeletedModelIndex( QtProperty *pro, Str name )
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

void ModelVisibleProWidget::boolValueChanged( QtProperty *pro, bool b )
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

	IModelVisibleEffectEvent* modelvisiblevent = 
		dynamic_cast<IModelVisibleEffectEvent*>(effectevent);

	QString proname = pro->propertyName();
	// 修改值
	if (StrCmp(proname.toStdString().c_str(), "Visible") == 0)
	{
		modelvisiblevent->setVisible(b);
	}

	IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
	if (!component)
		return;

	IEffectXmlSerializer* effectxmlSer = component->getEffectXmlSerializer();
	if (!effectxmlSer)
		return;

	// 填充到xml
	MG::IEffectObjectXmlFormat* format = 
		effectxmlSer->getEffectObjectFormat( modelvisiblevent->getName().c_str(), modelvisiblevent->getType() );
	if ( format )
	{
		format->fill(true);
	}
}

void ModelVisibleProWidget::enumValueChanged( QtProperty *pro, int index)
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

	IModelVisibleEffectEvent* modelvisiblevent =
		dynamic_cast<IModelVisibleEffectEvent*>(effectevent);

	QString proname = pro->propertyName();
	// 修改值
	if (StrCmp(proname.toStdString().c_str(), "Model Name") == 0)
	{
		Str modelname = mEntityList[index].toStdString();
		modelvisiblevent->setModelName(modelname);
		IEntity* entity = CoreManager::getInstance().getScene()->getEntity(modelname.c_str());
		if (entity)
		{
			mCurrentEntityResID = 
				entity->getModelObject()->getModelDeclarationID();
		}
	}

	IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
	if (!component)
		return;

	IEffectXmlSerializer* effectxmlSer = component->getEffectXmlSerializer();
	if (!effectxmlSer)
		return;

	// 填充到xml
	MG::IEffectObjectXmlFormat* format = 
		effectxmlSer->getEffectObjectFormat( modelvisiblevent->getName().c_str(), modelvisiblevent->getType() );
	if ( format )
	{
		format->fill(true);
	}
}

void ModelVisibleProWidget::doubleValueChanged( QtProperty *pro, double dvalue)
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