#include <QtGui>
#include "ModelAniProWidget.h"
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

ModelAniProWidget::ModelAniProWidget( QWidget *parent /*= 0*/, Qt::WFlags flags /*= 0*/ )
: QWidget(parent)
, mPropertyBrw(NULL)
, mStringManager(NULL)
, mDoubleManager(NULL)
, mBoolManager(NULL)
, mLineEditFactory(NULL)
, mCheckBoxFactory(NULL)
, mDoubleSpinBoxFactory(NULL)
, mCurrObjectXmlFormat(NULL)
, mCurrentEntityResID(0)
{
	createWidget();
	init();
}

ModelAniProWidget::~ModelAniProWidget()
{
	MG_SAFE_DELETE(mPropertyBrw);
	MG_SAFE_DELETE(mStringManager);
	MG_SAFE_DELETE(mDoubleManager);
	MG_SAFE_DELETE(mBoolManager);
	MG_SAFE_DELETE(mLineEditFactory);
	MG_SAFE_DELETE(mCheckBoxFactory);
	MG_SAFE_DELETE(mCurrObjectXmlFormat);
}

void ModelAniProWidget::loadElementProps( MG::IEffectObjectXmlFormat* format )
{
	clearElementProps();

	mCurrObjectXmlFormat = format;

	MG::SceneObjectTypes objtype = mCurrObjectXmlFormat->getSceneObject()->getType();
	if (objtype != EOT_MODEL_ANIMATION_EVENT)
		return;

	Model_Animation_ProSet();
}

void ModelAniProWidget::clearElementProps()
{
	mCurrObjectXmlFormat = NULL;
	mPropertyBrw->clear();

	mEntityList.clear();
	mAnimationList.clear();
}

void ModelAniProWidget::createWidget()
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
	mDoubleSpinBoxFactory = new QtDoubleSpinBoxFactory(this);
	mComboBoxFactory = new QtEnumEditorFactory(this);
}

void ModelAniProWidget::init()
{
	mPropertyBrw->setFactoryForManager(mBoolManager, mCheckBoxFactory);
	mPropertyBrw->setFactoryForManager(mStringManager, mLineEditFactory);
	mPropertyBrw->setFactoryForManager(mDoubleManager, mDoubleSpinBoxFactory);
	mPropertyBrw->setFactoryForManager(mEnumManager, mComboBoxFactory);
	mPropertyBrw->setAlternatingRowColors(true);

	connect(mDoubleManager, SIGNAL(valueChanged(QtProperty *, double)), this, SLOT(doubleValueChanged(QtProperty *, double)));
	connect(mBoolManager, SIGNAL(valueChanged(QtProperty *, bool)), this, SLOT(boolValueChanged(QtProperty *, bool)));
	connect(mEnumManager, SIGNAL(valueChanged(QtProperty *, int)), this, SLOT(enumValueChanged(QtProperty *, int)));
	connect(mStringManager, SIGNAL(valueChanged(QtProperty *, const QString &)), this, SLOT(stringValueChanged(QtProperty *, const QString &)));
}

void ModelAniProWidget::Model_Animation_ProSet()
{
	XMLNode* parentNode       = mCurrObjectXmlFormat->getXmlElm();
	XMLNode* currNode         = parentNode->FirstChild();
	XMLNode* firstSiblingNode = currNode;
	XMLNode* nextNode         = NULL;

	Str8 modelname;
	Str8 animationName;
	BOOL bloop = FALSE;
	Flt  timepoint = 0.0f;
	while (currNode)
	{
		// 时间点
		XmlHelper::getAttribute(currNode->ToElement(), timepoint, "Timing" );

		// 模型名
		XmlHelper::getAttribute(currNode->ToElement(), modelname, "ModelName" );

		// 动画名
		XmlHelper::getAttribute(currNode->ToElement(), animationName, "AniName" );

		// 是否可见
		Int loop = 1;
		XmlHelper::getAttribute(currNode->ToElement(), loop, "Value" );
		bloop = (loop!=0);

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

	//////////////////////////////////////////////////////////////////////////
	prop = mStringManager->addProperty(tr("Animation Name"));
	prop->setWhatsThis("2");
	mStringManager->setValue(prop, animationName.c_str());
	mPropertyBrw->addProperty(prop);

	//////////////////////////////////////////////////////////////////////////
	prop = mBoolManager->addProperty(tr("Loop"));
	prop->setWhatsThis("3");
	mBoolManager->setValue(prop, bloop);
	mPropertyBrw->addProperty(prop);
}

void ModelAniProWidget::setSeletedModelIndex( QtProperty *pro, Str name )
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

void ModelAniProWidget::boolValueChanged( QtProperty *pro, bool b )
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

	IModelAnimationEffectEvent* modelAnievent =
		dynamic_cast<IModelAnimationEffectEvent*>(effectevent);

	QString proname = pro->propertyName();
	// 修改值
	if (StrCmp(proname.toStdString().c_str(), "Loop") == 0)
	{
		modelAnievent->setIsLoop(b);
	}

	IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
	if (!component)
		return;

	IEffectXmlSerializer* effectxmlSer = component->getEffectXmlSerializer();
	if (!effectxmlSer)
		return;

	// 填充到xml
	MG::IEffectObjectXmlFormat* format = 
		effectxmlSer->getEffectObjectFormat( modelAnievent->getName().c_str(), modelAnievent->getType() );
	if ( format )
	{
		format->fill(true);
	}
}

void ModelAniProWidget::enumValueChanged( QtProperty *pro, int index)
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

	IModelAnimationEffectEvent* modelAnievent =
		dynamic_cast<IModelAnimationEffectEvent*>(effectevent);

	QString proname = pro->propertyName();
	// 修改值
	if (StrCmp(proname.toStdString().c_str(), "Model Name") == 0)
	{
		mAnimationList.clear();

		Str modelname = mEntityList[index].toStdString();
		modelAnievent->setModelName(modelname);
		IEntity* entity = NULL;
		if (!modelname.empty())
		{
			entity = CoreManager::getInstance().getScene()->getEntity(index-1);
		}
		if (entity)
		{
			mCurrentEntityResID = 
				entity->getModelObject()->getModelDeclarationID();
		}
	}
	else 
	if (StrCmp(proname.toStdString().c_str(), "Animation Name") == 0)
	{
		modelAnievent->setAnimationName(mAnimationList[index].toStdString().c_str());
	}

	IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
	if (!component)
		return;

	IEffectXmlSerializer* effectxmlSer = component->getEffectXmlSerializer();
	if (!effectxmlSer)
		return;

	// 填充到xml
	MG::IEffectObjectXmlFormat* format = 
		effectxmlSer->getEffectObjectFormat( modelAnievent->getName().c_str(), modelAnievent->getType() );
	if ( format )
	{
		format->fill(true);
	}
}

void ModelAniProWidget::doubleValueChanged( QtProperty *pro, double dvalue)
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

void ModelAniProWidget::stringValueChanged( QtProperty *pro, const QString & proValue )
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

	IModelAnimationEffectEvent* modelAnievent =
		dynamic_cast<IModelAnimationEffectEvent*>(effectevent);

	QString proname = pro->propertyName();
	if (StrCmp(proname.toStdString().c_str(), "Animation Name") == 0)
	{
		modelAnievent->setAnimationName(proValue.toStdString());
	}

	IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
	if (!component)
		return;

	IEffectXmlSerializer* effectxmlSer = component->getEffectXmlSerializer();
	if (!effectxmlSer)
		return;

	// 填充到xml
	MG::IEffectObjectXmlFormat* format = 
		effectxmlSer->getEffectObjectFormat( modelAnievent->getName().c_str(), modelAnievent->getType() );
	if ( format )
	{
		format->fill(true);
	}
}