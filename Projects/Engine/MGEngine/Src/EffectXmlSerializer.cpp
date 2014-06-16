/******************************************************************************/
#include "stdafx.h"
#include "EngineMain.h"
#include "Scene.h"
#include "EffectComponent.h"
#include "EffectXmlSerializer.h"
#include "tinyxml2.h"

#include "PUEffect.h"
#include "Entity.h"
#include "EffectComponentTimeLine.h"
#include "ModelEffectEvent.h"
#include "PUEffectEvent.h"
#include "WeaponLightEvent.h"
#include "EffectFadeEvent.h"
/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	/** 场景文件节点标签 */
	//@{ 
#define EFFECT_TAG "Effect"
#define PU_TAG "PUGroup"
#define ENTITY_TAG "ModelGroup"
#define TIMELINE_TAG "TimeLine"
#define TIMEPOINT_TAG "Timing"
#define EVENT_TAG "Event"

	//@}
	/** 特效文件版本号 */
	//@{ 
	//版本 2012.11.2
#define EFFECT_FILE_VERSION_1 "EFFECT_FILE_VERSION_1"
	//@}

	/** 特效当前文件版本 */
#define EFFECT_FILE_VERSION_NOW EFFECT_FILE_VERSION_1

	/******************************************************************************/
	//EffectXmlSerializer
	/******************************************************************************/
	EffectXmlSerializer::EffectXmlSerializer(EffectComponent* component)
		: mComponent(component)
		, mEffectXmlDoc(NULL)
	{
		if (mComponent)
			mScene = mComponent->getScene();

		mEffectXmlDoc				= MG_NEW tinyxml2::XMLDocument;

		mEffectComponentPUFormatGroup			= MG_NEW EffectObjectXmlFormatGroup<EffectComponentPUXmlFormat,PUEffect>(mComponent,"PU");

		mEffectComponentEntityFormatGroup		= MG_NEW EffectObjectXmlFormatGroup<EffectComponentEntityXmlFormat,Entity>(mComponent,"Model");

		mEffectComponentTimeLineFormatGroup		= MG_NEW EffectObjectXmlFormatGroup<EffectComponentTimeLineXmlFormat,EffectComponentTimeLine>(mComponent,"TimeLine");

		mModelVisibleEventFormatGroup			= MG_NEW EffectObjectXmlFormatGroup<ModelVisibleEventXmlFormat,ModelVisibleEffectEvent>(mComponent,"Event");
		mModelAnimationEventFormatGroup			= MG_NEW EffectObjectXmlFormatGroup<ModelAnimationEventXmlFormat,ModelAnimationEffectEvent>(mComponent,"Event");
		mModelBindEventFormatGroup				= MG_NEW EffectObjectXmlFormatGroup<ModelBindEventXmlFormat,ModelBindEffectEvent>(mComponent,"Event");

		mPUStartEventFormatGroup				= MG_NEW EffectObjectXmlFormatGroup<PUStartEventXmlFormat,PUStartEffectEvent>(mComponent,"Event");
		mPUStopEventFormatGroup					= MG_NEW EffectObjectXmlFormatGroup<PUStopEventXmlFormat,PUStopEffectEvent>(mComponent,"Event");
		mPUBindEventFormatGroup					= MG_NEW EffectObjectXmlFormatGroup<PUBindEventXmlFormat,PUBindEffectEvent>(mComponent,"Event");

		mWeaponLightEventFormatGroup			= MG_NEW EffectObjectXmlFormatGroup<WeaponLightEventXmlFormat,WeaponLightEvent>(mComponent,"Event");
		mEffectFadeEventFormatGroup				= MG_NEW EffectObjectXmlFormatGroup<EffectFadeEventXmlFormat,EffectFadeEvent>(mComponent,"Event");
	}
	//-----------------------------------------------------------------------
	EffectXmlSerializer::~EffectXmlSerializer()
	{
		 unLoad();

		 MG_SAFE_DELETE( mEffectFadeEventFormatGroup );
		 MG_SAFE_DELETE( mWeaponLightEventFormatGroup );
		 MG_SAFE_DELETE( mPUBindEventFormatGroup );
		 MG_SAFE_DELETE( mPUStopEventFormatGroup );
		 MG_SAFE_DELETE( mPUStartEventFormatGroup );
		 MG_SAFE_DELETE( mModelBindEventFormatGroup );
		 MG_SAFE_DELETE( mModelAnimationEventFormatGroup );
		 MG_SAFE_DELETE( mModelVisibleEventFormatGroup );
		 MG_SAFE_DELETE( mEffectComponentTimeLineFormatGroup );
		 MG_SAFE_DELETE( mEffectComponentEntityFormatGroup );
		 MG_SAFE_DELETE( mEffectComponentPUFormatGroup );
	}
	//-----------------------------------------------------------------------
	void EffectXmlSerializer::unLoad()
	{
		mEffectFadeEventFormatGroup->removeAllFormat();
		mWeaponLightEventFormatGroup->removeAllFormat();
		mPUBindEventFormatGroup->removeAllFormat();
		mPUStopEventFormatGroup->removeAllFormat();
		mPUStartEventFormatGroup->removeAllFormat();
		mModelBindEventFormatGroup->removeAllFormat();
		mModelAnimationEventFormatGroup->removeAllFormat();
		mModelVisibleEventFormatGroup->removeAllFormat();
		mEffectComponentTimeLineFormatGroup->removeAllFormat();
		mEffectComponentEntityFormatGroup->removeAllFormat();
		mEffectComponentPUFormatGroup->removeAllFormat();

		MG_SAFE_DELETE( mEffectXmlDoc );
	}
	//-----------------------------------------------------------------------
	Bool EffectXmlSerializer::createEffectComponentFormat()
	{
		//---------------------------------------------------------------------------

		// 销毁原有特效的格式化存储文件
		mEffectFadeEventFormatGroup->removeAllFormat();
		mWeaponLightEventFormatGroup->removeAllFormat();
		mEffectComponentPUFormatGroup->removeAllFormat();
		mEffectComponentEntityFormatGroup->removeAllFormat();

		mEffectComponentTimeLineFormatGroup->removeAllFormat();

		mEffectXmlDoc->DeleteChildren();

		//---------------------------------------------------------------------------

		/*
		创建新的Effect文件格式化存储
		*/

		XMLElement* rootElm = XmlHelper::addChild(mEffectXmlDoc, EFFECT_TAG);
		if ( rootElm )
		{
			Str8 version = EFFECT_FILE_VERSION_NOW;
			XmlHelper::setAttribute(rootElm, version, "Version");

			//PUGroup
			XMLElement* puElm = XmlHelper::addChild(rootElm, PU_TAG);
			if ( puElm )
			{
				mEffectComponentPUFormatGroup->setGroupElm( puElm );
			}

			//EnityGroup
			XMLElement* entityElm =  XmlHelper::addChild(rootElm, ENTITY_TAG);
			if ( entityElm )
			{
				mEffectComponentEntityFormatGroup->setGroupElm( entityElm );
			}

			//TimeLine
			XMLElement* timeLineElm = XmlHelper::addChild(rootElm, TIMELINE_TAG);
			if (timeLineElm)
			{
				Flt periodTime = 10.0f;
				XmlHelper::setAttribute(timeLineElm, periodTime, "Period");

				Int loop = 0;
				XmlHelper::setAttribute(timeLineElm, loop, "Loop");

				mEffectComponentTimeLineFormatGroup->setGroupElm(timeLineElm);

				mModelVisibleEventFormatGroup->setGroupElm(timeLineElm);
				mModelAnimationEventFormatGroup->setGroupElm(timeLineElm);
				mModelBindEventFormatGroup->setGroupElm(timeLineElm);
				mPUStartEventFormatGroup->setGroupElm(timeLineElm);
				mPUStopEventFormatGroup->setGroupElm(timeLineElm);
				mPUBindEventFormatGroup->setGroupElm(timeLineElm);
				mWeaponLightEventFormatGroup->setGroupElm(timeLineElm);
				mEffectFadeEventFormatGroup->setGroupElm(timeLineElm);
			}

		}

		return true;
	}
	//-----------------------------------------------------------------------
	Bool EffectXmlSerializer::loadEffectComponentFormat(CChar* fileName)
	{
		if (mEffectXmlDoc->LoadFile(fileName) != XML_NO_ERROR)
		{
			// MG_CN_MODIFY
			IMGExternalPackManager *packManager = EngineMain::getInstance().getPackManager();
			if (packManager)
			{				
				char* buf = NULL;
				int size = 0;
				packManager->extractPackFile(fileName, buf, size);
				if (mEffectXmlDoc->LoadFile(buf) != XML_NO_ERROR)
				{
					MG_MESSAGE("effect file Serialization error");
					DYNAMIC_ASSERT(false);
					return false;
				}
			}
			else
			{
				MG_MESSAGE("effect file Serialization error");
				DYNAMIC_ASSERT(false);
				return false;
			}
		}

		Str8 version; 
		XMLElement* rootElm = mEffectXmlDoc->RootElement();
		if (rootElm)
		{
			version = XML_GET_ATTRIBUTE(rootElm,"Version");

			//create component
			{
				XMLNode* parentNode       = rootElm;
				XMLNode* currNode         = parentNode->FirstChild();
				XMLNode* firstSiblingNode = currNode;
				XMLNode* nextNode         = NULL;

				XMLElement* PUElm = XmlHelper::getChild(parentNode, PU_TAG);
				if (PUElm)
					mEffectComponentPUFormatGroup->setGroupElm( PUElm );
				else
					XmlHelper::addChild(parentNode, PU_TAG);
				
				XMLElement* ModelElm = XmlHelper::getChild(parentNode, ENTITY_TAG);
				if (ModelElm)
					mEffectComponentEntityFormatGroup->setGroupElm( ModelElm );
				else
					XmlHelper::addChild(parentNode, ENTITY_TAG);
				
				XMLElement* timeLineElm = XmlHelper::getChild(parentNode, TIMELINE_TAG);
				if (timeLineElm)
				{
					mEffectComponentTimeLineFormatGroup->setGroupElm(timeLineElm);

					mModelVisibleEventFormatGroup->setGroupElm(timeLineElm);
					mModelAnimationEventFormatGroup->setGroupElm(timeLineElm);
					mModelBindEventFormatGroup->setGroupElm(timeLineElm);
					mPUStartEventFormatGroup->setGroupElm(timeLineElm);
					mPUStopEventFormatGroup->setGroupElm(timeLineElm);
					mPUBindEventFormatGroup->setGroupElm(timeLineElm);
					mWeaponLightEventFormatGroup->setGroupElm(timeLineElm);
					mEffectFadeEventFormatGroup->setGroupElm(timeLineElm);
				}
				else
					XmlHelper::addChild(parentNode, TIMELINE_TAG);

				while( currNode )
				{
					//TODO:
					std::string formatType = XML_GET_VALUE(currNode);

					if (formatType == PU_TAG)
					{
						mEffectComponentPUFormatGroup->loadGroup(currNode->ToElement());
					}
					else if (formatType == ENTITY_TAG)
					{
						mEffectComponentEntityFormatGroup->loadGroup(currNode->ToElement());
					}
					else if (formatType == TIMELINE_TAG)
					{
						mEffectComponentTimeLineFormatGroup->loadGroup(currNode->ToElement());
					}

					//@ parallel 
					nextNode    = currNode->NextSibling();
					if (nextNode&&nextNode==firstSiblingNode)
					{
						break;
					}
					currNode = nextNode;
				}
			}
		}


		return true;
	}
	//-----------------------------------------------------------------------
	Bool EffectXmlSerializer::saveEffectFile( CChar* fileName )
	{
		if (mEffectXmlDoc->SaveFile(fileName) == XML_NO_ERROR)
			return true;
		else
			return false;
	}
	//-----------------------------------------------------------------------
	Str EffectXmlSerializer::getTypeName( SceneObjectTypes type )
	{
		switch(type)
		{
		case EOT_PU:
			return "PU";
		case SOT_ENTITY:
			return "Entity";
		case EOT_TIMELINE:
			return "TimeLine";
		case EOT_MODEL_VISIBLE_EVENT:
			return "Model_Visible";
		case EOT_MODEL_ANIMATION_EVENT:
			return "Model_Animation";
		case EOT_MODEL_BIND_EVENT:
			return "Model_Bind";
		case EOT_PU_START_EVENT:
			return "PU_Start";
		case EOT_PU_STOP_EVENT:
			return "PU_Stop";
		case EOT_PU_BIND_EVENT:
			return "PU_Bind";
		}

		return "NULL_TYPE";
	}
	//-----------------------------------------------------------------------
	IEffectObjectXmlFormat* EffectXmlSerializer::addEffectObjectFormat(ISceneObject* object, Bool isAddToXML, tinyxml2::XMLElement * elm)
	{
		if ( object->getType() == EOT_PU )
			return mEffectComponentPUFormatGroup->addFormat( dynamic_cast<MG::PUEffect*>(object), isAddToXML, elm);
		else if ( object->getType() == SOT_ENTITY )
			return mEffectComponentEntityFormatGroup->addFormat( dynamic_cast<MG::Entity*>(object), isAddToXML, elm);
		else if ( object->getType() == EOT_TIMELINE )
			return mEffectComponentTimeLineFormatGroup->addFormat( dynamic_cast<MG::EffectComponentTimeLine*>(object), isAddToXML, elm);
		else if ( object->getType() == EOT_MODEL_VISIBLE_EVENT )
			return mModelVisibleEventFormatGroup->addFormat(dynamic_cast<MG::ModelVisibleEffectEvent*>(object), isAddToXML, elm);
		else if ( object->getType() == EOT_MODEL_ANIMATION_EVENT )
			return mModelAnimationEventFormatGroup->addFormat(dynamic_cast<MG::ModelAnimationEffectEvent*>(object), isAddToXML, elm);
		else if ( object->getType() == EOT_MODEL_BIND_EVENT )
			return mModelBindEventFormatGroup->addFormat(dynamic_cast<MG::ModelBindEffectEvent*>(object), isAddToXML, elm);
		else if ( object->getType() == EOT_PU_START_EVENT )
			return mPUStartEventFormatGroup->addFormat(dynamic_cast<MG::PUStartEffectEvent*>(object), isAddToXML, elm);
		else if ( object->getType() == EOT_PU_STOP_EVENT )
			return mPUStopEventFormatGroup->addFormat(dynamic_cast<MG::PUStopEffectEvent*>(object), isAddToXML, elm);
		else if ( object->getType() == EOT_PU_BIND_EVENT )
			return mPUBindEventFormatGroup->addFormat(dynamic_cast<MG::PUBindEffectEvent*>(object), isAddToXML, elm);
		else if ( object->getType() == EOT_WEAPON_LIGHT_EVENT)
			return mWeaponLightEventFormatGroup->addFormat(dynamic_cast<MG::WeaponLightEvent*>(object), isAddToXML, elm);
		else if ( object->getType() == EOT_EFFECT_FADE_EVENT)
			return mEffectFadeEventFormatGroup->addFormat(dynamic_cast<MG::EffectFadeEvent*>(object), isAddToXML, elm);

		return NULL;
	}
	//-----------------------------------------------------------------------
	IEffectObjectXmlFormat* EffectXmlSerializer::getEffectObjectFormat( CChar* name, SceneObjectTypes type)
	{
		if ( type == EOT_PU )
			return mEffectComponentPUFormatGroup->getFormat( name );
		else if ( type == SOT_ENTITY )
			return mEffectComponentEntityFormatGroup->getFormat( name );
		else if ( type == EOT_TIMELINE)
			return mEffectComponentTimeLineFormatGroup->getFormat( name );
		else if ( type == EOT_MODEL_VISIBLE_EVENT )
			return mModelVisibleEventFormatGroup->getFormat(name);
		else if ( type == EOT_MODEL_ANIMATION_EVENT)
			return mModelAnimationEventFormatGroup->getFormat( name );
		else if ( type == EOT_MODEL_BIND_EVENT)
			return mModelBindEventFormatGroup->getFormat( name );
		else if ( type == EOT_PU_START_EVENT)
			return mPUStartEventFormatGroup->getFormat( name );
		else if ( type == EOT_PU_STOP_EVENT)
			return mPUStopEventFormatGroup->getFormat( name );
		else if ( type == EOT_PU_BIND_EVENT)
			return mPUBindEventFormatGroup->getFormat( name );
		else if ( type == EOT_WEAPON_LIGHT_EVENT)
			return mWeaponLightEventFormatGroup->getFormat( name );
		else if ( type == EOT_EFFECT_FADE_EVENT)
			return mEffectFadeEventFormatGroup->getFormat(name);

		return NULL;
	}
	//-----------------------------------------------------------------------
	void EffectXmlSerializer::removeEffectObjectFormat( IEffectObjectXmlFormat* format, Bool isDestroyEntity)
	{
		removeEffectObjectFormat( format->getSceneObject()->getName().c_str(), format->getSceneObject()->getType(), isDestroyEntity);
	}
	//-----------------------------------------------------------------------
	void EffectXmlSerializer::removeEffectObjectFormat( CChar* name, SceneObjectTypes type, Bool isDestroyEntity)
	{
		switch ( type )
		{
		case EOT_PU:
			mEffectComponentPUFormatGroup->removeFormat( name );
			break;
		case SOT_ENTITY:
			mEffectComponentEntityFormatGroup->removeFormat( name );
			break;
		case EOT_TIMELINE:
			mEffectComponentTimeLineFormatGroup->removeFormat( name );
			break;
		case EOT_MODEL_VISIBLE_EVENT:
			mModelVisibleEventFormatGroup->removeFormat(name);
			break;
		case EOT_MODEL_ANIMATION_EVENT:
			mModelAnimationEventFormatGroup->removeFormat(name);
			break;
		case EOT_MODEL_BIND_EVENT:
			mModelBindEventFormatGroup->removeFormat(name);
			break;
		case EOT_PU_START_EVENT:
			mPUStartEventFormatGroup->removeFormat(name);
			break;
		case EOT_PU_STOP_EVENT:
			mPUStopEventFormatGroup->removeFormat(name);
			break;
		case EOT_PU_BIND_EVENT:
			mPUBindEventFormatGroup->removeFormat(name);
			break;
		case EOT_WEAPON_LIGHT_EVENT:
			mWeaponLightEventFormatGroup->removeFormat(name);
			break;
		case EOT_EFFECT_FADE_EVENT:
			mEffectFadeEventFormatGroup->removeFormat(name);
			break;
		}
		if ( isDestroyEntity )
		{
			mScene->destroySceneObject( name, type );
		}
	}
	//-----------------------------------------------------------------------
	void EffectXmlSerializer::getEffectObjectXmlFormatList( SceneObjectTypes type, std::vector<IEffectObjectXmlFormat*>& formatList)
	{
		if ( type == EOT_PU )
			mEffectComponentPUFormatGroup->getFormatList( formatList );
		else 
		if ( type == SOT_ENTITY )
			mEffectComponentEntityFormatGroup->getFormatList( formatList );
		else
		if (type == EOT_TIMELINE )
			mEffectComponentTimeLineFormatGroup->getFormatList( formatList );
		else 
		if ( type == EOT_MODEL_VISIBLE_EVENT )
			mModelVisibleEventFormatGroup->getFormatList( formatList );
		else 
		if ( type == EOT_MODEL_ANIMATION_EVENT)
			mModelAnimationEventFormatGroup->getFormatList(formatList);
		else
		if ( type == EOT_MODEL_BIND_EVENT )
			mModelBindEventFormatGroup->getFormatList( formatList );
		else 
		if ( type == EOT_PU_START_EVENT)
			mPUStartEventFormatGroup->getFormatList(formatList);
		else
		if ( type == EOT_PU_STOP_EVENT )
			mPUStopEventFormatGroup->getFormatList( formatList );
		else 
		if ( type == EOT_PU_BIND_EVENT)
			mPUBindEventFormatGroup->getFormatList(formatList);
		else
		if ( type == EOT_WEAPON_LIGHT_EVENT)
			mWeaponLightEventFormatGroup->getFormatList(formatList);
		else
		if ( type == EOT_EFFECT_FADE_EVENT)
			mEffectFadeEventFormatGroup->getFormatList(formatList);
	}
	//-----------------------------------------------------------------------
	Str EffectXmlSerializer::getEffectFileName()
	{
		return "";
	}
	//-----------------------------------------------------------------------
	EffectComponent* EffectXmlSerializer::getEffectComponent()
	{
		return mComponent;
	}
	//-----------------------------------------------------------------------
	XMLElement* EffectXmlSerializer::getTimeLineXMLEle()
	{
		return mEffectComponentTimeLineFormatGroup->getGroupElm();
	}
	/******************************************************************************/
	//EffectComponentPUXmlFormat
	/******************************************************************************/
	EffectComponentPUXmlFormat::EffectComponentPUXmlFormat(EffectComponent* component, tinyxml2::XMLElement * elm, PUEffect* puEffect )
		: mComponent(component)
		, mPUEffect(puEffect)
	{
		if (mComponent)
			mScene = mComponent->getScene();

		mXmlElm = elm;
	}
	//-----------------------------------------------------------------------
	EffectComponentPUXmlFormat::~EffectComponentPUXmlFormat()
	{

	}
	//-----------------------------------------------------------------------
	void EffectComponentPUXmlFormat::fill(Bool isAddToXML)
	{
		if (mPUEffect&&mXmlElm&&isAddToXML)
		{
			// 组
			Str8 groupName = mPUEffect->getGroup();
			XmlHelper::setAttribute( mXmlElm, groupName, "Group" );

			//名字
			if (!mComponent)
				return;

			Str8 name = mComponent->getEffectName(mPUEffect);
			XmlHelper::setAttribute( mXmlElm, name, "Name" );

			//PU模版名
			Str8 effectTemplateName = mPUEffect->getEffectTemplateName();
			XmlHelper::setAttribute( mXmlElm, effectTemplateName, "PUTemplate" );

		}
	}
	//-----------------------------------------------------------------------
	void EffectComponentPUXmlFormat::apply( Bool isCheckDirty/*=false*/ )
	{
		if (mXmlElm)
		{
			mPUEffect = EffectComponentPUXmlFormat::apply(mComponent, mXmlElm, mPUEffect, isCheckDirty);
		}
	}
	//-----------------------------------------------------------------------
	PUEffect* EffectComponentPUXmlFormat::apply(EffectComponent* component, tinyxml2::XMLElement * elm, PUEffect* puEffect, Bool isCheckDirty )
	{
		if (!component)
			return NULL;

		// 名字
		Str8 name;
		XmlHelper::getAttribute( elm, name, "Name" );

		//PU模版名字
		Str8 effectTemplateName;
		XmlHelper::getAttribute( elm, effectTemplateName, "PUTemplate" );

		if ( puEffect == NULL )
		{
			puEffect = component->createPUEffect( effectTemplateName.c_str(), name.c_str());
			puEffect->getSceneNode()->setVisible(false);
			name = component->getEffectName(puEffect);
			XmlHelper::setAttribute( elm, name, "Name" );
		}

		if ( puEffect )
		{
			// 设置基本参数
			puEffect->getSceneNode()->setPosition(Vec3(0, 0, 0));
			puEffect->getSceneNode()->setOrientation(Qua(1, 0, 0, 0));
		}

		return puEffect;
	}

	ISceneObject* EffectComponentPUXmlFormat::getSceneObject()
	{
		return mPUEffect;
	}
	/******************************************************************************/
	//EffectComponentEntityXmlFormat
	/******************************************************************************/
	EffectComponentEntityXmlFormat::EffectComponentEntityXmlFormat(EffectComponent* component, tinyxml2::XMLElement * elm, Entity* entity )
		:mComponent(component)
		,mEntity(entity)
	{
		if (mComponent)
			mScene = mComponent->getScene();

		mXmlElm = elm;
	}
	//-----------------------------------------------------------------------
	EffectComponentEntityXmlFormat::~EffectComponentEntityXmlFormat()
	{

	}
	//-----------------------------------------------------------------------
	void EffectComponentEntityXmlFormat::fill(Bool isAddToXML)
	{
		if (mEntity&&mXmlElm&&isAddToXML)
		{
			// 组
			Str8 groupName = mEntity->getGroup();
			XmlHelper::setAttribute( mXmlElm, groupName, "Group" );

			//名字
			if (!mComponent)
				return;

			Str8 name = mComponent->getModelName(mEntity);
			XmlHelper::setAttribute( mXmlElm, name, "Name" );

			// 模型编号
			U32 modelDeclID = mEntity->getModelObject()->getModelDeclarationID();
			XmlHelper::setAttribute( mXmlElm, modelDeclID, "ModelDeclID" );

		}
	}
	//-----------------------------------------------------------------------
	void EffectComponentEntityXmlFormat::apply( Bool isCheckDirty/*=false*/ )
	{
		if (mXmlElm)
		{
			mEntity = EffectComponentEntityXmlFormat::apply(mComponent, mXmlElm, mEntity);
		}
	}
	//-----------------------------------------------------------------------
	Entity* EffectComponentEntityXmlFormat::apply(EffectComponent* component, tinyxml2::XMLElement * elm, Entity* entity/*=NULL*/, Bool isCheckDirty/*=false*/ )
	{
		if (!component)
			return NULL;

		// 名字
		Str8 name;
		XmlHelper::getAttribute( elm, name, "Name" );

		// 模型编号
		U32 modelDeclID = 0;
		XmlHelper::getAttribute( elm, modelDeclID, "ModelDeclID" );

		if ( entity == NULL )
		{
			entity = component->createModelEffect( modelDeclID, name.c_str());
			entity->getSceneNode()->setVisible(false);
			name = component->getModelName(entity);
			XmlHelper::setAttribute( elm, name, "Name" );
		}

		if ( entity )
		{
			// 设置基本参数
			entity->getSceneNode()->setPosition(Vec3(0, 0, 0));
			entity->getSceneNode()->setOrientation(Qua(1, 0, 0, 0));
		}

		return entity;
	}

	///******************************************************************************/
	////EffectComponentTimeLineXmlFormat
	///******************************************************************************/
	EffectComponentTimeLineXmlFormat::EffectComponentTimeLineXmlFormat(EffectComponent* component, tinyxml2::XMLElement * elm, EffectComponentTimeLine* timeline )
		:mComponent(component)
		,mEffectComponentTimeLine(timeline)
	{
		if (mComponent)
			mScene = mComponent->getScene();

		mXmlElm = elm;
	}
	//-----------------------------------------------------------------------
	EffectComponentTimeLineXmlFormat::~EffectComponentTimeLineXmlFormat()
	{

	}
	//-----------------------------------------------------------------------
	void EffectComponentTimeLineXmlFormat::fill(Bool isAddToXML)
	{
		if (mEffectComponentTimeLine&&mXmlElm&&isAddToXML)
		{
			Flt periodTime = mEffectComponentTimeLine->getPeriodTime();
			XmlHelper::setAttribute( mXmlElm, periodTime, "Period" );

			Bool loop = mEffectComponentTimeLine->getIsLoop();
			XmlHelper::setAttribute( mXmlElm, loop, "Loop" );
		}
	}
	//-----------------------------------------------------------------------
	void EffectComponentTimeLineXmlFormat::apply( Bool isCheckDirty/*=false*/ )
	{
		if (mXmlElm)
		{
			mEffectComponentTimeLine = EffectComponentTimeLineXmlFormat::apply(mComponent, mXmlElm, mEffectComponentTimeLine, isCheckDirty);
		}
	}
	//-----------------------------------------------------------------------
	EffectComponentTimeLine* EffectComponentTimeLineXmlFormat::apply(EffectComponent* component, tinyxml2::XMLElement * elm, EffectComponentTimeLine* timeline, Bool isCheckDirty/*=false*/ )
	{
		if (!component)
			return NULL;

		if (!timeline)
			timeline = component->getTimeLine();

		if (!timeline)
			return NULL;

		Flt periodTime;
		if (XmlHelper::getAttribute( elm->Parent()->ToElement(), periodTime, "Period" ))
			timeline->setPeriodTime(periodTime);

		Flt loop;
		if ( XmlHelper::getAttribute( elm->Parent()->ToElement(), loop, "Loop" ) )
			timeline->setIsLoop(loop);

		applyEvent(component, elm);

		return timeline;
	}

	ISceneObject* EffectComponentTimeLineXmlFormat::getSceneObject()
	{
		return mEffectComponentTimeLine;
	}

	void EffectComponentTimeLineXmlFormat::applyEvent(EffectComponent* component, tinyxml2::XMLElement * elm )
	{
		if (!component)
			return;

		IEffectEvent *effectEvent = NULL;

		Str8 eventName;
		XmlHelper::getAttribute( elm, eventName, "EventName" );

		if(!eventName.empty() && !effectEvent)
			effectEvent = component->createEffectEvent(eventName, 0);

		if (!effectEvent)
			return;

		if (effectEvent)
			component->getEffectXmlSerializer()->addEffectObjectFormat(effectEvent, false, elm);

		XMLNode* parent = elm;
		XMLNode* currNode = elm->FirstChild();
		XMLNode* firstSiblingNode = currNode;
		XMLNode* nextNode = NULL;

		//获取特效以及各种资源的总数
		while ( currNode )
		{
			Flt timepoint = 0.0f;
			if (XmlHelper::getAttribute( currNode->ToElement(), timepoint, "Timing" ))
				effectEvent->setEventTimePoint(timepoint);

			//Str8 modelName;
			//if( XmlHelper::getAttribute( currNode->ToElement(), modelName, "ModelName" ) ) 
			//	effectEvent->setModelName(modelName);

			//Str8 aniName;
			//if( XmlHelper::getAttribute( currNode->ToElement(), aniName, "AniName" ) ) 
			//	effectEvent->setAnimationName(aniName);

			//Str8 puName;
			//if( XmlHelper::getAttribute( currNode->ToElement(), puName, "PUName" ) ) 
			//	effectEvent->setPUName(puName);

			//Int visible = 0;
			//if (StrCmp(currNode->ToElement()->Value(), "Visible") == 0)
			//{
			//	if( XmlHelper::getAttribute( currNode->ToElement(), visible, "Value" ) ) 
			//		effectEvent->setVisible((visible!=0));
			//}

			//Int loopplay = 0;
			//if (StrCmp(currNode->ToElement()->Value(), "LoopPlay") == 0)
			//{
			//	if( XmlHelper::getAttribute( currNode->ToElement(), loopplay, "Value" ) ) 
			//		effectEvent->setIsLoop((loopplay!=0));
			//}

			//Int isBindRootComponent = 0;
			//if (StrCmp(currNode->ToElement()->Value(), "isBindRootComponent") == 0)
			//{
			//	if( XmlHelper::getAttribute( currNode->ToElement(), isBindRootComponent, "Value" ) ) 
			//		effectEvent->setIsBindRootComponent((isBindRootComponent!=0));
			//}

			//Str8 bindExEntityName;
			//if( XmlHelper::getAttribute( currNode->ToElement(), bindExEntityName, "BindExEntityName" ) ) 
			//	effectEvent->setBindExternalEntityName(bindExEntityName);

			//Str8 bindModelName;
			//if( XmlHelper::getAttribute( currNode->ToElement(), bindModelName, "BindModelName" ) ) 
			//	effectEvent->setBindModelName(bindModelName);

			//Str8 bindPUName;
			//if( XmlHelper::getAttribute( currNode->ToElement(), bindPUName, "BindPUName" ) ) 
			//	effectEvent->setBindPUName(bindPUName);

			//Str8 bindBoneName;
			//if( XmlHelper::getAttribute( currNode->ToElement(), bindBoneName, "BindBoneName" ) ) 
			//	effectEvent->setBindBoneName(bindBoneName);

			//// 位置
			//Vec3 pos = Vec3(0,0,0);
			//Vec3XmlFormat::load(currNode->ToElement(), "PositionOffset", pos);
			//effectEvent->setPosOffset(pos);

			//// 朝向
			//Vec4 orientation = Vec4(1,0,0,0);
			//Vec4XmlFormat::load(currNode->ToElement(), "OrientationOffset", orientation);
			//effectEvent->setOriOffset(orientation);

			//@ parallel 
			nextNode = currNode->NextSibling();

			if ( nextNode && nextNode == firstSiblingNode )
			{
				break;
			}

			currNode = nextNode;
		}


	}
	/******************************************************************************/
	//ModelVisibleEventXmlFormat
	/******************************************************************************/
	ModelVisibleEventXmlFormat::ModelVisibleEventXmlFormat(EffectComponent* component, tinyxml2::XMLElement * elm, ModelVisibleEffectEvent* visibleEvent )
		:mComponent(component)
		,mModelVisibleEvent(visibleEvent)
	{
		if (mComponent)
			mScene = mComponent->getScene();

		mXmlElm = elm;
	}
	//-----------------------------------------------------------------------
	ModelVisibleEventXmlFormat::~ModelVisibleEventXmlFormat()
	{

	}
	//-----------------------------------------------------------------------
	void ModelVisibleEventXmlFormat::fill(Bool isAddToXML)
	{
		if (mModelVisibleEvent&&mXmlElm)
		{
			if (isAddToXML)
				XmlHelper::setAttribute( mXmlElm, "Model_Visible", "EventName" );

			// Time Point
			{
				XMLElement* elm = NULL;
				Flt timepoint = 0;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "Point" );
					timepoint = mModelVisibleEvent->getEventTimePoint();
					XmlHelper::setAttribute( elm, timepoint, "Timing" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "Point" );
					XmlHelper::getAttribute(elm, timepoint, "Timing");
					mModelVisibleEvent->setEventTimePoint(timepoint);
				}
			}

			// Model Name
			{
				XMLElement* elm = NULL;
				Str modelName;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "Model" );
					modelName = mModelVisibleEvent->getModelName();
					XmlHelper::setAttribute( elm, modelName, "ModelName" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "Model" );
					XmlHelper::getAttribute(elm, modelName, "ModelName");
					mModelVisibleEvent->setModelName(modelName);
				}

			}

			// Visible
			{
				XMLElement* elm = NULL;
				Bool visible = false;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "Visible" );
					visible = mModelVisibleEvent->getVisible();
					XmlHelper::setAttribute( elm, visible, "Value" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "Visible" );
					Str visibleStr = "0";
					XmlHelper::getAttribute(elm, visibleStr, "Value");
					mModelVisibleEvent->setVisible(visibleStr == "1" ? true : false);
				}
			}

		}
	}
	//-----------------------------------------------------------------------
	void ModelVisibleEventXmlFormat::apply( Bool isCheckDirty/*=false*/ )
	{
		if (mXmlElm)
			mModelVisibleEvent = ModelVisibleEventXmlFormat::apply(mComponent, mXmlElm, mModelVisibleEvent, isCheckDirty);

	}
	//-----------------------------------------------------------------------
	ModelVisibleEffectEvent* ModelVisibleEventXmlFormat::apply(EffectComponent* component, tinyxml2::XMLElement * elm, ModelVisibleEffectEvent* event/*=NULL*/, Bool isCheckDirty/*=false*/ )
	{
		if ( (component == NULL) || (event == NULL) )
			return NULL;	

		// Time Point
		XMLElement* timepointAttrs = XmlHelper::getChild(elm, "Timing");
		Flt timepoint = 0;
		if ( XmlHelper::getAttribute( timepointAttrs, timepoint, "Point" ) )
		{
			event->setEventTimePoint(timepoint);
		}

		// Model Name
		XMLElement* nameAttrs = XmlHelper::getChild(elm, "Model");
		Str modelname;
		if ( XmlHelper::getAttribute( nameAttrs, modelname, "ModelName" ) )
		{
			event->setModelName(modelname);
		}

		// Visible
		XMLElement* visbleAttrs = XmlHelper::getChild(elm, "Visible");
		Int visible = 1;
		if ( XmlHelper::getAttribute( visbleAttrs, visible, "Value" ) )
		{
			event->setVisible(visible!=0);
		}

		return event;
	}

	ISceneObject* ModelVisibleEventXmlFormat::getSceneObject()
	{
		return mModelVisibleEvent;
	}
	/******************************************************************************/
	//ModelAnimationEventXmlFormat
	/******************************************************************************/
	ModelAnimationEventXmlFormat::ModelAnimationEventXmlFormat(EffectComponent* component, tinyxml2::XMLElement * elm, ModelAnimationEffectEvent* aniEvent )
		:mComponent(component)
		,mModelAnimationEvent(aniEvent)
	{
		if (mComponent)
			mScene = mComponent->getScene();

		mXmlElm = elm;
	}
	//-----------------------------------------------------------------------
	ModelAnimationEventXmlFormat::~ModelAnimationEventXmlFormat()
	{

	}
	//-----------------------------------------------------------------------
	void ModelAnimationEventXmlFormat::fill(Bool isAddToXML)
	{
		if (mModelAnimationEvent&&mXmlElm)
		{
			if (isAddToXML)
				XmlHelper::setAttribute( mXmlElm, "Model_Animation", "EventName" );

			// Time Point
			{
				XMLElement* elm = NULL;
				Flt timepoint = 0;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "Point" );
					timepoint = mModelAnimationEvent->getEventTimePoint();
					XmlHelper::setAttribute( elm, timepoint, "Timing" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "Point" );
					XmlHelper::getAttribute(elm, timepoint, "Timing");
					mModelAnimationEvent->setEventTimePoint(timepoint);
				}

			}

			// Model Name
			{
				XMLElement* elm = NULL;
				Str modelName;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "Model" );
					modelName = mModelAnimationEvent->getModelName();
					XmlHelper::setAttribute( elm, modelName, "ModelName" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "Model" );
					XmlHelper::getAttribute(elm, modelName, "Timing");
					mModelAnimationEvent->setModelName(modelName);
				}
			}

			// Animation Name
			{
				XMLElement* elm = NULL;
				Str aniName;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "Animation" );
					aniName = mModelAnimationEvent->getAnimationName();
					XmlHelper::setAttribute( elm, aniName, "AniName" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "Animation" );
					XmlHelper::getAttribute(elm, aniName, "AniName");
					mModelAnimationEvent->setAnimationName(aniName);
				}

			}

			// Loop
			{
				XMLElement* elm = NULL;
				Bool loop = false;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "LoopPlay" );
					loop = mModelAnimationEvent->getLoop();
					XmlHelper::setAttribute( elm, loop, "Value" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "LoopPlay" );
					Str loopStr = "0";
					XmlHelper::getAttribute(elm, loopStr, "Value");
					mModelAnimationEvent->setIsLoop(loopStr == "1" ? true : false);
				}
			}

		}
	}
	//-----------------------------------------------------------------------
	void ModelAnimationEventXmlFormat::apply( Bool isCheckDirty/*=false*/ )
	{
		if (mXmlElm)
			mModelAnimationEvent = ModelAnimationEventXmlFormat::apply(mComponent, mXmlElm, mModelAnimationEvent, isCheckDirty);
	}
	//-----------------------------------------------------------------------
	ModelAnimationEffectEvent* ModelAnimationEventXmlFormat::apply(EffectComponent* component, tinyxml2::XMLElement * elm, ModelAnimationEffectEvent* event/*=NULL*/, Bool isCheckDirty/*=false*/ )
	{
		if ( (component == NULL) || (event == NULL) )
			return NULL;	

		// Time Point
		XMLElement* timepointAttrs = XmlHelper::getChild(elm, "Timing");
		Flt timepoint;
		if ( XmlHelper::getAttribute( timepointAttrs, timepoint, "Point" ) )
		{
			event->setEventTimePoint(timepoint);
		}

		// Model Name
		XMLElement* nameAttrs = XmlHelper::getChild(elm, "Model");
		Str modelname;
		if ( XmlHelper::getAttribute( nameAttrs, modelname, "ModelName" ) )
		{
			event->setModelName(modelname);
		}

		// Animation Name
		XMLElement* aninameAttrs = XmlHelper::getChild(elm, "Animation");
		Str aniname;
		if ( XmlHelper::getAttribute(aninameAttrs, aniname, "AniName" ) )
		{
			event->setAnimationName(aniname);
		}

		// Loop
		XMLElement* loopAttrs = XmlHelper::getChild(elm, "LoopPlay");
		Int loop = 1;
		if ( XmlHelper::getAttribute( loopAttrs, loop, "Value" ) )
		{
			event->setIsLoop(loop);
		}

		return event;
	}

	ISceneObject* ModelAnimationEventXmlFormat::getSceneObject()
	{
		return mModelAnimationEvent;
	}
	/******************************************************************************/
	//ModelBindEventXmlFormat
	/******************************************************************************/
	ModelBindEventXmlFormat::ModelBindEventXmlFormat(EffectComponent* component, tinyxml2::XMLElement * elm, ModelBindEffectEvent* bindEvent )
		:mComponent(component)
		,mModelBindEvent(bindEvent)
	{
		if (mComponent)
			mScene = mComponent->getScene();

		mXmlElm = elm;
	}
	//-----------------------------------------------------------------------
	ModelBindEventXmlFormat::~ModelBindEventXmlFormat()
	{

	}
	//-----------------------------------------------------------------------
	void ModelBindEventXmlFormat::fill(Bool isAddToXML)
	{
		if (mModelBindEvent&&mXmlElm)
		{
			if (isAddToXML)
				XmlHelper::setAttribute( mXmlElm, "Model_Bind", "EventName" );

			// Time Point
			{
				XMLElement* elm = NULL;
				Flt timepoint = false;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "Point" );
					timepoint = mModelBindEvent->getEventTimePoint();
					XmlHelper::setAttribute( elm, timepoint, "Timing" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "Point" );
					XmlHelper::getAttribute(elm, timepoint, "Timing");
					mModelBindEvent->setEventTimePoint(timepoint);
				}
			}

			// Model Name
			{
				XMLElement* elm = NULL;
				Str modelName;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "Model" );
					modelName = mModelBindEvent->getModelName();
					XmlHelper::setAttribute( elm, modelName, "ModelName" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "Model" );
					XmlHelper::getAttribute(elm, modelName, "ModelName");
					mModelBindEvent->setModelName(modelName);
				}

			}

			// isBindRootComponent
			{
				XMLElement* elm = NULL;
				Bool isBind = false;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "isBindRootComponent" );
					isBind = mModelBindEvent->getIsBindRootComponent();
					XmlHelper::setAttribute( elm, isBind, "Value" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "isBindRootComponent" );
					Str isBindStr = "0";
					XmlHelper::getAttribute(elm, isBindStr, "Value");
					mModelBindEvent->setIsBindRootComponent(isBindStr == "1" ? true : false);
				}

			}

			// BindExternalEntity
			{
				XMLElement* elm = NULL;
				Str exEntity;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "BindExternalEntity" );
					exEntity = mModelBindEvent->getBindExternalEntityName();
					XmlHelper::setAttribute( elm, exEntity, "BindExEntityName" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "BindExternalEntity" );
					XmlHelper::getAttribute(elm, exEntity, "BindExEntityName");
					mModelBindEvent->setBindExternalEntityName(exEntity);
				}

			}

			// BindModel
			{
				XMLElement* elm = NULL;
				Str bindModel;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "BindModel" );
					bindModel = mModelBindEvent->getBindModelName();
					XmlHelper::setAttribute( elm, bindModel, "BindModelName" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "BindModel" );
					XmlHelper::getAttribute(elm, bindModel, "BindModelName");
					mModelBindEvent->setBindModelName(bindModel);
				}
			}

			// BindPU
			{
				XMLElement* elm = NULL;
				Str bindPUName;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "BindPU" );
					bindPUName = mModelBindEvent->getBindPUName();
					XmlHelper::setAttribute( elm, bindPUName, "BindPUName" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "BindPU" );
					XmlHelper::getAttribute(elm, bindPUName, "BindPUName");
					mModelBindEvent->setBindPUName(bindPUName);
				}

			}

			// BindBone
			{
				XMLElement* elm = NULL;
				Str bindBoneName;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "BindBone" );
					bindBoneName = mModelBindEvent->getBindBoneName();
					XmlHelper::setAttribute( elm, bindBoneName, "BindBoneName" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "BindBone" );
					XmlHelper::getAttribute(elm, bindBoneName, "BindBoneName");
					mModelBindEvent->setBindBoneName(bindBoneName);
				}

			}

			// 位置
			Vec3 pos;
			if (isAddToXML)
			{
				pos = mModelBindEvent->getPosOffset();
				Vec3XmlFormat::save(mXmlElm, "PositionOffset", pos);
			}
			else
			{
				Vec3XmlFormat::load(mXmlElm, "PositionOffset", pos);
				mModelBindEvent->setPosOffset(pos);
			}


			// 朝向
			Vec4 orientation;
			if (isAddToXML)
			{
				orientation = mModelBindEvent->getOriOffset();
				Vec4XmlFormat::save(mXmlElm, "OrientationOffset", Vec4(orientation.w, orientation.x,orientation.y,orientation.z) );
			}
			else
			{
				Vec4XmlFormat::load(mXmlElm, "OrientationOffset", orientation);
				mModelBindEvent->setOriOffset(orientation);
			}
		}
	}
	//-----------------------------------------------------------------------
	void ModelBindEventXmlFormat::apply( Bool isCheckDirty/*=false*/ )
	{
		if (mXmlElm)
			mModelBindEvent = ModelBindEventXmlFormat::apply(mComponent, mXmlElm, mModelBindEvent, isCheckDirty);
	}
	//-----------------------------------------------------------------------
	ModelBindEffectEvent* ModelBindEventXmlFormat::apply(EffectComponent* component, tinyxml2::XMLElement * elm, ModelBindEffectEvent* event/*=NULL*/, Bool isCheckDirty/*=false*/ )
	{
		// Time Point
		XMLElement* timepointAttrs = XmlHelper::getChild(elm, "Timing");
		Flt timepoint;
		if ( XmlHelper::getAttribute( timepointAttrs, timepoint, "Point" ) )
		{
			event->setEventTimePoint(timepoint);
		}

		// Model Name
		XMLElement* nameAttrs = XmlHelper::getChild(elm, "Model");
		Str modelname;
		if ( XmlHelper::getAttribute( nameAttrs, modelname, "ModelName" ) )
		{
			event->setModelName(modelname);
		}

		// isBindRootComponent
		XMLElement* bindrootAttrs = XmlHelper::getChild(elm, "isBindRootComponent");
		Int isBindRootComponent = 1;
		if ( XmlHelper::getAttribute( bindrootAttrs, isBindRootComponent, "Value" ) )
		{
			event->setIsBindRootComponent(isBindRootComponent!=0);
		}

		// BindExternalEntity
		XMLElement* bindExternalEntityAttrs = XmlHelper::getChild(elm, "BindExternalEntity");
		Str bindExEntityName;
		if ( XmlHelper::getAttribute( bindExternalEntityAttrs, bindExEntityName, "BindExEntityName" ) )
		{
			event->setBindExternalEntityName(bindExEntityName);
		}

		// BindModel
		XMLElement* bindModelAttrs = XmlHelper::getChild(elm, "BindModel");
		Str bindModelName;
		if ( XmlHelper::getAttribute( bindModelAttrs, bindModelName, "BindModelName" ) )
		{
			event->setBindModelName(bindModelName);
		}

		// BindPU
		XMLElement* bindPUAttrs = XmlHelper::getChild(elm, "BindPU");
		Str bindPUName;
		if ( XmlHelper::getAttribute( bindPUAttrs, bindPUName, "BindPUName" ) )
		{
			event->setBindPUName(bindPUName);
		}

		// BindBone
		XMLElement* bindBoneAttrs = XmlHelper::getChild(elm, "BindBone");
		Str bindBoneName;
		if ( XmlHelper::getAttribute( bindBoneAttrs, bindBoneName, "BindBoneName" ) )
		{
			event->setBindBoneName(bindBoneName);
		}

		// 位置
		Vec3 pos = Vec3(0,0,0);
		Vec3XmlFormat::load(elm, "PositionOffset", pos);
		event->setPosOffset(pos);

		// 朝向
		Vec4 orientation = Vec4(1,0,0,0);
		Vec4XmlFormat::load(elm, "OrientationOffset", orientation);
		event->setOriOffset(orientation);

		return event;
	}

	ISceneObject* ModelBindEventXmlFormat::getSceneObject()
	{
		return mModelBindEvent;
	}
	/******************************************************************************/
	//PUStartEventXmlFormat
	/******************************************************************************/
	PUStartEventXmlFormat::PUStartEventXmlFormat(EffectComponent* component, tinyxml2::XMLElement * elm,  PUStartEffectEvent* startEvent )
		:mComponent(component)
		,mPUStartEvent(startEvent)
	{
		mXmlElm = elm;
	}
	//-----------------------------------------------------------------------
	PUStartEventXmlFormat::~PUStartEventXmlFormat()
	{

	}
	//-----------------------------------------------------------------------
	void PUStartEventXmlFormat::fill(Bool isAddToXML)
	{
		if (mPUStartEvent&&mXmlElm)
		{
			if (isAddToXML)
				XmlHelper::setAttribute( mXmlElm, "PU_Start", "EventName" );

			// Time Point
			{
				XMLElement* elm = NULL;
				Flt timepoint = 0;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "Point" );
					Flt timepoint = mPUStartEvent->getEventTimePoint();
					XmlHelper::setAttribute( elm, timepoint, "Timing" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "Point" );
					XmlHelper::getAttribute(elm, timepoint, "Timing");
					mPUStartEvent->setEventTimePoint(timepoint);
				}

			}

			// PU Name
			{
				XMLElement* elm = NULL;
				Str puName;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "PU" );
					puName = mPUStartEvent->getPUName();
					XmlHelper::setAttribute( elm, puName, "PUName" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "PU" );
					XmlHelper::getAttribute(elm, puName, "PUName");
					mPUStartEvent->setPUName(puName);
				}
			}

		}
	}
	//-----------------------------------------------------------------------
	void PUStartEventXmlFormat::apply( Bool isCheckDirty/*=false*/ )
	{
		if (mXmlElm)
			mPUStartEvent = PUStartEventXmlFormat::apply(mComponent, mXmlElm, mPUStartEvent, isCheckDirty);
	}
	//-----------------------------------------------------------------------
	PUStartEffectEvent* PUStartEventXmlFormat::apply(EffectComponent* component, tinyxml2::XMLElement * elm, PUStartEffectEvent* event/*=NULL*/, Bool isCheckDirty/*=false*/ )
	{
		if ( (component == NULL) || (event == NULL) )
			return NULL;	

		// Time Point
		XMLElement* timepointAttrs = XmlHelper::getChild(elm, "Timing");
		Flt timepoint;
		if ( XmlHelper::getAttribute( timepointAttrs, timepoint, "Point" ) )
		{
			event->setEventTimePoint(timepoint);
		}

		// PU Name
		XMLElement* nameAttrs = XmlHelper::getChild(elm, "PU");
		Str puname;
		if ( XmlHelper::getAttribute( nameAttrs, puname, "PUName" ) )
		{
			event->setPUName(puname);
		}

		return event;
	}

	ISceneObject* PUStartEventXmlFormat::getSceneObject()
	{
		return mPUStartEvent;
	}
	/******************************************************************************/
	//PUStopEventXmlFormat
	/******************************************************************************/
	PUStopEventXmlFormat::PUStopEventXmlFormat(EffectComponent* component, tinyxml2::XMLElement * elm,  PUStopEffectEvent* stopEvent )
		:mComponent(component)
		,mPUStopEvent(stopEvent)
	{
		if (mComponent)
			mScene = mComponent->getScene();

		mXmlElm = elm;
	}
	//-----------------------------------------------------------------------
	PUStopEventXmlFormat::~PUStopEventXmlFormat()
	{

	}
	//-----------------------------------------------------------------------
	void PUStopEventXmlFormat::fill(Bool isAddToXML)
	{
		if (mPUStopEvent&&mXmlElm)
		{
			if (isAddToXML)
				XmlHelper::setAttribute( mXmlElm, "PU_Stop", "EventName" );

			// Time Point
			{
				XMLElement* elm = NULL;
				Flt timepoint = 0;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "Point" );
					Flt timepoint = mPUStopEvent->getEventTimePoint();
					XmlHelper::setAttribute( elm, timepoint, "Timing" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "Point" );
					XmlHelper::getAttribute(elm, timepoint, "Timing");
					mPUStopEvent->setEventTimePoint(timepoint);
				}

			}

			// PU Name
			{
				XMLElement* elm = NULL;
				Str puName;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "PU" );
					puName = mPUStopEvent->getPUName();
					XmlHelper::setAttribute( elm, puName, "PUName" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "PU" );
					XmlHelper::getAttribute(elm, puName, "PUName");
					mPUStopEvent->setPUName(puName);
				}

			}

		}
	}
	//-----------------------------------------------------------------------
	void PUStopEventXmlFormat::apply( Bool isCheckDirty/*=false*/ )
	{
		if (mXmlElm)
			mPUStopEvent = PUStopEventXmlFormat::apply(mComponent, mXmlElm, mPUStopEvent, isCheckDirty);
	}
	//-----------------------------------------------------------------------
	PUStopEffectEvent* PUStopEventXmlFormat::apply(EffectComponent* component, tinyxml2::XMLElement * elm, PUStopEffectEvent* event/*=NULL*/, Bool isCheckDirty/*=false*/ )
	{
		if ( (component == NULL) || (event == NULL) )
			return NULL;	

		// Time Point
		XMLElement* timepointAttrs = XmlHelper::getChild(elm, "Timing");
		Flt timepoint;
		if ( XmlHelper::getAttribute( timepointAttrs, timepoint, "Point" ) )
		{
			event->setEventTimePoint(timepoint);
		}

		// PU Name
		XMLElement* nameAttrs = XmlHelper::getChild(elm, "PU");
		Str puname;
		if ( XmlHelper::getAttribute( nameAttrs, puname, "PUName" ) )
		{
			event->setPUName(puname);
		}

		return event;
	}

	ISceneObject* PUStopEventXmlFormat::getSceneObject()
	{
		return mPUStopEvent;
	}
	/******************************************************************************/
	//PUBindEventXmlFormat
	/******************************************************************************/
	PUBindEventXmlFormat::PUBindEventXmlFormat(EffectComponent* component, tinyxml2::XMLElement * elm, PUBindEffectEvent* bindEffect )
		:mComponent(component)
		,mPUBindEvent(bindEffect)
	{
		if (mComponent)
			mScene = mComponent->getScene();

		mXmlElm = elm;
	}
	//-----------------------------------------------------------------------
	PUBindEventXmlFormat::~PUBindEventXmlFormat()
	{

	}
	//-----------------------------------------------------------------------
	void PUBindEventXmlFormat::fill(Bool isAddToXML)
	{
		if (mPUBindEvent&&mXmlElm)
		{
			if (isAddToXML)
				XmlHelper::setAttribute( mXmlElm, "PU_Bind", "EventName" );

			// Time Point
			{
				XMLElement* elm = NULL;
				Flt timepoint = 0;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "Point" );
					timepoint = mPUBindEvent->getEventTimePoint();
					XmlHelper::setAttribute( elm, timepoint, "Timing" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "Point" );
					XmlHelper::getAttribute(elm, timepoint, "Timing");
					mPUBindEvent->setEventTimePoint(timepoint);
				}

			}

			// PU Name
			{
				XMLElement* elm = NULL;
				Str puName;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "PU" );
					puName = mPUBindEvent->getPUName();
					XmlHelper::setAttribute( elm, puName, "PUName" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "PU" );
					XmlHelper::getAttribute(elm, puName, "PUName");
					mPUBindEvent->setPUName(puName);
				}

			}

			// isBindRootComponent
			{
				XMLElement* elm = NULL;
				Bool isBind = false;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "isBindRootComponent" );
					isBind = mPUBindEvent->getIsBindRootComponent();
					XmlHelper::setAttribute( elm, isBind, "Value" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "isBindRootComponent" );
					Str isBindStr = "0";
					XmlHelper::getAttribute(elm, isBindStr, "Value");
					mPUBindEvent->setIsBindRootComponent(isBindStr == "1" ? true : false);
				}
	
			}

			// BindExternalEntity
			{
				XMLElement* elm = NULL;
				Str exEntity;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "BindExternalEntity" );
					exEntity = mPUBindEvent->getBindExternalEntityName();
					XmlHelper::setAttribute( elm, exEntity, "BindExEntityName" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "BindExternalEntity" );
					XmlHelper::getAttribute(elm, exEntity, "BindExEntityName");
					mPUBindEvent->setBindExternalEntityName(exEntity);
				}

			}

			// BindModel
			{
				XMLElement* elm = NULL;
				Str bindModel;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "BindModel" );
					bindModel = mPUBindEvent->getBindModelName();
					XmlHelper::setAttribute( elm, bindModel, "BindModelName" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "BindModel" );
					XmlHelper::getAttribute(elm, bindModel, "BindModelName");
					mPUBindEvent->setBindModelName(bindModel);
				}

			}

			// BindPU
			{
				XMLElement* elm = NULL;
				Str bindPUName;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "BindPU" );
					Str bindPUName = mPUBindEvent->getBindPUName();
					XmlHelper::setAttribute( elm, bindPUName, "BindPUName" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "BindPU" );
					XmlHelper::getAttribute(elm, bindPUName, "BindPUName");
					mPUBindEvent->setBindPUName(bindPUName);
				}

			}

			// BindBone
			{
				XMLElement* elm = NULL;
				Str bindBoneName;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "BindBone" );
					bindBoneName = mPUBindEvent->getBindBoneName();
					XmlHelper::setAttribute( elm, bindBoneName, "BindBoneName" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "BindBone" );
					XmlHelper::getAttribute(elm, bindBoneName, "BindBoneName");
					mPUBindEvent->setBindBoneName(bindBoneName);
				}

			}

			// 位置
			Vec3 pos;
			if (isAddToXML)
			{
				pos = mPUBindEvent->getPosOffset();
				Vec3XmlFormat::save(mXmlElm, "PositionOffset", pos);
			}
			else
			{
				Vec3XmlFormat::load(mXmlElm, "PositionOffset", pos);
				mPUBindEvent->setPosOffset(pos);
			}

			// 朝向
			Vec4 orientation;
			if (isAddToXML)
			{
				orientation = mPUBindEvent->getOriOffset();
				Vec4XmlFormat::save(mXmlElm, "OrientationOffset", Vec4(orientation.w, orientation.x,orientation.y,orientation.z) );
			}
			else
			{
				Vec4XmlFormat::load(mXmlElm, "OrientationOffset", orientation);
				mPUBindEvent->setOriOffset(orientation);
			}
		}
	}
	//-----------------------------------------------------------------------
	void PUBindEventXmlFormat::apply( Bool isCheckDirty/*=false*/ )
	{
		if (mXmlElm)
			mPUBindEvent = PUBindEventXmlFormat::apply(mComponent, mXmlElm, mPUBindEvent, isCheckDirty);
	}
	//-----------------------------------------------------------------------
	PUBindEffectEvent* PUBindEventXmlFormat::apply(EffectComponent* component, tinyxml2::XMLElement * elm, PUBindEffectEvent* event/*=NULL*/, Bool isCheckDirty/*=false*/ )
	{
		// Time Point
		XMLElement* timepointAttrs = XmlHelper::getChild(elm, "Timing");
		Flt timepoint;
		if ( XmlHelper::getAttribute( timepointAttrs, timepoint, "Point" ) )
		{
			event->setEventTimePoint(timepoint);
		}

		// PU Name
		XMLElement* nameAttrs = XmlHelper::getChild(elm, "PU");
		Str puname;
		if ( XmlHelper::getAttribute( nameAttrs, puname, "PUName" ) )
		{
			event->setPUName(puname);
		}

		// isBindRootComponent
		XMLElement* bindrootAttrs = XmlHelper::getChild(elm, "isBindRootComponent");
		Int isBindRootComponent = 1;
		if ( XmlHelper::getAttribute( bindrootAttrs, isBindRootComponent, "Value" ) )
		{
			event->setIsBindRootComponent(isBindRootComponent!=0);
		}

		// BindExternalEntity
		XMLElement* bindExternalEntityAttrs = XmlHelper::getChild(elm, "BindExternalEntity");
		Str bindExEntityName;
		if ( XmlHelper::getAttribute( bindExternalEntityAttrs, bindExEntityName, "BindExEntityName" ) )
		{
			event->setBindExternalEntityName(bindExEntityName);
		}

		// BindModel
		XMLElement* bindModelAttrs = XmlHelper::getChild(elm, "BindModel");
		Str bindModelName;
		if ( XmlHelper::getAttribute( bindModelAttrs, bindModelName, "BindModelName" ) )
		{
			event->setBindModelName(bindModelName);
		}

		// BindPU
		XMLElement* bindPUAttrs = XmlHelper::getChild(elm, "BindPU");
		Str bindPUName;
		if ( XmlHelper::getAttribute( bindPUAttrs, bindPUName, "BindPUName" ) )
		{
			event->setBindPUName(bindPUName);
		}

		// BindBone
		XMLElement* bindBoneAttrs = XmlHelper::getChild(elm, "BindBone");
		Str bindBoneName;
		if ( XmlHelper::getAttribute( bindBoneAttrs, bindBoneName, "BindBoneName" ) )
		{
			event->setBindBoneName(bindBoneName);
		}

		// 位置
		Vec3 pos = Vec3(0,0,0);
		Vec3XmlFormat::load(elm, "PositionOffset", pos);
		event->setPosOffset(pos);

		// 朝向
		Vec4 orientation = Vec4(1,0,0,0);
		Vec4XmlFormat::load(elm, "OrientationOffset", orientation);
		event->setOriOffset(orientation);

		return event;
	}

	ISceneObject* PUBindEventXmlFormat::getSceneObject()
	{
		return mPUBindEvent;
	}

	/******************************************************************************/
	//WeaponLightEventXmlFormat
	/******************************************************************************/
	WeaponLightEventXmlFormat::WeaponLightEventXmlFormat( EffectComponent* component, tinyxml2::XMLElement * elm, WeaponLightEvent* weaponLightEffect )
		:mComponent(component)
		,mWeaponLightEvent(weaponLightEffect)
	{
		if (mComponent)
			mScene = mComponent->getScene();

		mXmlElm = elm;
	}

	WeaponLightEventXmlFormat::~WeaponLightEventXmlFormat()
	{

	}

	void WeaponLightEventXmlFormat::fill( Bool isAddToXML )
	{
		if (mWeaponLightEvent&&mXmlElm)
		{
			if (isAddToXML)
				XmlHelper::setAttribute( mXmlElm, "Weapon_Light", "EventName" );

			// Time Point
			{
				XMLElement* elm = NULL;
				Flt timepoint = 0;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "Point" );
					timepoint = mWeaponLightEvent->getEventTimePoint();
					XmlHelper::setAttribute( elm, timepoint, "Timing" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "Point" );
					XmlHelper::getAttribute(elm, timepoint, "Timing");
					mWeaponLightEvent->setEventTimePoint(timepoint);
				}

			}

			// PU Name
			{
				XMLElement* elm = NULL;
				Str puName;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "PU" );
					puName = mWeaponLightEvent->getPUName();
					XmlHelper::setAttribute( elm, puName, "PUName" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "PU" );
					XmlHelper::getAttribute(elm, puName, "PUName");
					mWeaponLightEvent->setPUName(puName);
				}

			}

			// BindExternalEntity
			{
				XMLElement* elm = NULL;
				Str exEntity;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "BindExternalEntity" );
					exEntity = mWeaponLightEvent->getBindExternalEntityName();
					XmlHelper::setAttribute( elm, exEntity, "BindExEntityName" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "BindExternalEntity" );
					XmlHelper::getAttribute(elm, exEntity, "BindExEntityName");
					mWeaponLightEvent->setBindExternalEntityName(exEntity);
				}

			}

			// 位置
			Vec3 pos;
			if (isAddToXML)
			{
				pos = mWeaponLightEvent->getPosOffset();
				Vec3XmlFormat::save(mXmlElm, "PositionOffset", pos);
			}
			else
			{
				Vec3XmlFormat::load(mXmlElm, "PositionOffset", pos);
				mWeaponLightEvent->setPosOffset(pos);
			}

			// TrailLength
			{
				XMLElement* elm = NULL;
				U32 trailLength = 0;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "TrailLength" );
					trailLength = mWeaponLightEvent->getTrailLength();
					XmlHelper::setAttribute( elm, trailLength, "Length" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "TrailLength" );
					XmlHelper::getAttribute(elm, trailLength, "Length");
					mWeaponLightEvent->setTrailLength(trailLength);
				}

			}

			// TrailWitdh
			{
				XMLElement* elm = NULL;
				U32 trailWidth = 0;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "TrailWidth" );
					trailWidth = mWeaponLightEvent->getTrailWidth();
					XmlHelper::setAttribute( elm, trailWidth, "Width" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "TrailWidth" );
					XmlHelper::getAttribute(elm, trailWidth, "Width");
					mWeaponLightEvent->setTrailWidth(trailWidth);
				}

			}

			// TrailLiveTime
			{
				XMLElement* elm = NULL;
				Flt trailLiveTime = 0;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "TrailLiveTime" );
					trailLiveTime = mWeaponLightEvent->getTrailLiveTime();
					XmlHelper::setAttribute( elm, trailLiveTime, "Time" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "TrailLiveTime" );
					XmlHelper::getAttribute(elm, trailLiveTime, "Time");
					mWeaponLightEvent->setTrailLiveTime(trailLiveTime);
				}

			}

		}
	}

	void WeaponLightEventXmlFormat::apply( Bool isCheckDirty/*=false*/ )
	{
		if (mXmlElm)
			mWeaponLightEvent = WeaponLightEventXmlFormat::apply(mComponent, mXmlElm, mWeaponLightEvent, isCheckDirty);
	}

	WeaponLightEvent* WeaponLightEventXmlFormat::apply( EffectComponent* component, tinyxml2::XMLElement * elm, WeaponLightEvent* event/*=NULL*/, Bool isCheckDirty/*=false*/ )
	{
		// Time Point
		XMLElement* timepointAttrs = XmlHelper::getChild(elm, "Timing");
		Flt timepoint;
		if ( XmlHelper::getAttribute( timepointAttrs, timepoint, "Point" ) )
		{
			event->setEventTimePoint(timepoint);
		}

		// PU Name
		XMLElement* nameAttrs = XmlHelper::getChild(elm, "PU");
		Str puname;
		if ( XmlHelper::getAttribute( nameAttrs, puname, "PUName" ) )
		{
			event->setPUName(puname);
		}

		// BindExternalEntity
		XMLElement* bindExternalEntityAttrs = XmlHelper::getChild(elm, "BindExternalEntity");
		Str bindExEntityName;
		if ( XmlHelper::getAttribute( bindExternalEntityAttrs, bindExEntityName, "BindExEntityName" ) )
		{
			event->setBindExternalEntityName(bindExEntityName);
		}

		// 位置
		Vec3 pos = Vec3(0,0,0);
		Vec3XmlFormat::load(elm, "PositionOffset", pos);
		event->setPosOffset(pos);

		// TrailLength
		XMLElement* traillengthAttrs = XmlHelper::getChild(elm, "TrailLength");
		U32 traillength;
		if ( XmlHelper::getAttribute( traillengthAttrs, traillength, "Length" ) )
		{
			event->setTrailLength(traillength);
		}

		// TrailWidth
		XMLElement* trailwidthAttrs = XmlHelper::getChild(elm, "TrailWidth");
		U32 trailwidth;
		if ( XmlHelper::getAttribute( trailwidthAttrs, trailwidth, "Width" ) )
		{
			event->setTrailWidth(trailwidth);
		}

		// TrailLiveTime
		XMLElement* traillivetimeAttrs = XmlHelper::getChild(elm, "TrailLiveTime");
		Flt traillivetime;
		if ( XmlHelper::getAttribute( traillivetimeAttrs, traillivetime, "Time" ) )
		{
			event->setTrailLiveTime(traillivetime);
		}

		return event;
	}

	ISceneObject* WeaponLightEventXmlFormat::getSceneObject()
	{
		return mWeaponLightEvent;
	}


	/******************************************************************************/
	//EffectFadeEventXmlFormat
	/******************************************************************************/
	EffectFadeEventXmlFormat::EffectFadeEventXmlFormat( EffectComponent* component, tinyxml2::XMLElement * elm, EffectFadeEvent* effectFade )
		:mComponent(component)
		,mEffectFadeEvent(effectFade)
	{
		if (mComponent)
			mScene = mComponent->getScene();

		mXmlElm = elm;
	}

	EffectFadeEventXmlFormat::~EffectFadeEventXmlFormat()
	{

	}

	void EffectFadeEventXmlFormat::fill( Bool isAddToXML )
	{
		if (mEffectFadeEvent&&mXmlElm)
		{
			if (isAddToXML)
				XmlHelper::setAttribute( mXmlElm, "Effect_Fade", "EventName" );

			// Time Point
			{
				XMLElement* elm = NULL;
				Flt timepoint = 0;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "Point" );
					timepoint = mEffectFadeEvent->getEventTimePoint();
					XmlHelper::setAttribute( elm, timepoint, "Timing" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "Point" );
					XmlHelper::getAttribute(elm, timepoint, "Timing");
					mEffectFadeEvent->setEventTimePoint(timepoint);
				}
			}

			// PU Name
			{
				XMLElement* elm = NULL;
				Str puName;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "PU" );
					puName = mEffectFadeEvent->getPUName();
					XmlHelper::setAttribute( elm, puName, "PUName" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "PU" );
					XmlHelper::getAttribute(elm, puName, "PUName");
					mEffectFadeEvent->setPUName(puName);
				}

			}

			// FadeTimePoint
			{
				XMLElement* elm = NULL;
				Flt fadeTimePoint = 0;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "FadePoint" );
					fadeTimePoint = mEffectFadeEvent->getFadeTimePoint();
					XmlHelper::setAttribute( elm, fadeTimePoint, "Timing" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "FadePoint" );
					XmlHelper::getAttribute(elm, fadeTimePoint, "Timing");
					mEffectFadeEvent->setFadeTimePoint(fadeTimePoint);
				}

			}

			// Duration
			{
				XMLElement* elm = NULL;
				U32 duration = 0;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "Duration" );
					duration = mEffectFadeEvent->getDurationTime();
					XmlHelper::setAttribute( elm, duration, "Timing" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "Duration" );
					XmlHelper::getAttribute(elm, duration, "Timing");
					mEffectFadeEvent->setDurationTime(duration);
				}
			}

			// FadeType
			{
				XMLElement* elm = NULL;
				Str fadeType;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "FadeType" );
					fadeType = mEffectFadeEvent->getFadeTypeStr();
					XmlHelper::setAttribute( elm, fadeType, "TypeName" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "FadeType" );
					XmlHelper::getAttribute(elm, fadeType, "TypeName");
					mEffectFadeEvent->setFadeType(mEffectFadeEvent->getFadeTypeFromStr(fadeType));
				}

			}

			// FadeValue
			{
				XMLElement* elm = NULL;
				Flt fadeValue = 0;
				if (isAddToXML)
				{
					elm = XmlHelper::addChild( mXmlElm, "FadeValue" );
					fadeValue = mEffectFadeEvent->getFadeValue();
					XmlHelper::setAttribute( elm, fadeValue, "Value" ); 
				}
				else
				{
					elm = XmlHelper::getChild( mXmlElm, "FadeValue" );
					XmlHelper::getAttribute(elm, fadeValue, "Value");
					mEffectFadeEvent->setFadeValue(fadeValue);
				}
			}

		}
	}

	void EffectFadeEventXmlFormat::apply( Bool isCheckDirty/*=false*/ )
	{
		if (mXmlElm)
			mEffectFadeEvent = EffectFadeEventXmlFormat::apply(mComponent, mXmlElm, mEffectFadeEvent, isCheckDirty);
	}

	EffectFadeEvent* EffectFadeEventXmlFormat::apply( EffectComponent* component, tinyxml2::XMLElement * elm, EffectFadeEvent* event/*=NULL*/, Bool isCheckDirty/*=false*/ )
	{
		// Time Point
		XMLElement* timepointAttrs = XmlHelper::getChild(elm, "Timing");
		Flt timepoint;
		if ( XmlHelper::getAttribute( timepointAttrs, timepoint, "Point" ) )
		{
			event->setEventTimePoint(timepoint);
		}

		// PU Name
		XMLElement* nameAttrs = XmlHelper::getChild(elm, "PU");
		Str puname;
		if ( XmlHelper::getAttribute( nameAttrs, puname, "PUName" ) )
		{
			event->setPUName(puname);
		}

		// FadePoint
		XMLElement* fadePointAttrs = XmlHelper::getChild(elm, "FadePoint");
		Flt fadePoint;
		if ( XmlHelper::getAttribute( fadePointAttrs, fadePoint, "Timing" ) )
		{
			event->setFadeTimePoint(fadePoint);
		}

		// Duration
		XMLElement* durationAttrs = XmlHelper::getChild(elm, "Duration");
		U32 duration;
		if ( XmlHelper::getAttribute( durationAttrs, duration, "Timing" ) )
		{
			event->setDurationTime(duration);
		}

		// FadeType
		XMLElement* fadeTypeAttrs = XmlHelper::getChild(elm, "FadeType");
		Str typeName;
		if ( XmlHelper::getAttribute( fadeTypeAttrs, typeName, "TypeName" ) )
		{
			event->setFadeType(event->getFadeTypeFromStr(typeName));
		}

		// FadeValue
		XMLElement* fadeValueAttrs = XmlHelper::getChild(elm, "FadeValue");
		Flt fadeValue;
		if ( XmlHelper::getAttribute( fadeValueAttrs, fadeValue, "Value" ) )
		{
			event->setFadeValue(fadeValue);
		}

		return event;
	}

	ISceneObject* EffectFadeEventXmlFormat::getSceneObject()
	{
		return mEffectFadeEvent;
	}
}