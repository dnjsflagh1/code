/******************************************************************************/
#ifndef _EFFECTXMLSERIALIZER_H_
#define _EFFECTXMLSERIALIZER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IEffectXmlSerializer.h"
#include "EffectComponent.h"

/******************************************************************************/

namespace MG
{
	class PUEffect;
	class Entity;
	class EffectComponent;
	class EffectComponentTimeLine;
	class ModelVisibleEffectEvent;
	class ModelAnimationEffectEvent;
	class ModelBindEffectEvent;
	class PUStartEffectEvent;
	class PUStopEffectEvent;
	class PUBindEffectEvent;
	class WeaponLightEvent;
	class EffectFadeEvent;

	class EffectComponentPUXmlFormat;
	class EffectComponentEntityXmlFormat;
	class EffectComponentTimeLineXmlFormat;
	class ModelVisibleEventXmlFormat;
	class ModelAnimationEventXmlFormat;
	class ModelBindEventXmlFormat;
	class PUStartEventXmlFormat;
	class PUStopEventXmlFormat;
	class PUBindEventXmlFormat;
	class WeaponLightEventXmlFormat;
	class EffectFadeEventXmlFormat;

	/******************************************************************************/
	//��Ч��ʽ������
	/******************************************************************************/
	template<typename TYPE0, typename TYPE1>
	class EffectObjectXmlFormatGroup
	{
	public:
		EffectObjectXmlFormatGroup(EffectComponent* component, Str groupName)
			:mGroupElm(NULL)
			,mComponent(component)
			,mGroupName(groupName)
		{
		}
		~EffectObjectXmlFormatGroup()
		{
			removeAllFormat();
		}

	public:

		/// ������Ч�����ʽ��������
		void loadGroup( XMLElement * groupElm, Bool isCreateFormats = false )
		{
			setGroupElm( groupElm );

			XMLNode* parentNode       = groupElm;
			XMLNode* currNode         = parentNode->FirstChild();
			XMLNode* firstSiblingNode = currNode;
			XMLNode* nextNode         = NULL;

			Int i = 0;

			while( currNode )
			{
				if ( isCreateFormats )
				{
					TYPE0* format = MG_NEW TYPE0(mComponent, currNode->ToElement(), NULL);
					format->apply();

					if ( format->getSceneObject() )
					{
						Str name = format->getSceneObject()->getName();
						mFormats[name] = format;
					}
				}else
				{
					TYPE0::apply(mComponent,currNode->ToElement());
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

		/// ������Ч�����ʽ������
		TYPE0* addFormat( TYPE1* entity, Bool isAddToXML, XMLElement *xml)
		{
			DYNAMIC_ASSERT(mGroupElm!=NULL);
			if ( mGroupElm )
			{
				XMLElement * elm = NULL;
				if (!isAddToXML && xml)
					elm = xml;
				else
					elm = XmlHelper::addChild(mGroupElm, mGroupName.c_str(), false);

				TYPE0* format = MG_NEW TYPE0(mComponent, elm, entity);
				format->fill(isAddToXML);
				Str name = entity->getName();
				mFormats[name] = format;
				return format;
			}
			return NULL;
		}

		/// �õ���Ч�����ʽ������
		TYPE0* getFormat( CChar* name )
		{
			std::map<Str,TYPE0*>::iterator iter = mFormats.find(name);
			if ( iter!=mFormats.end() )
			{
				return iter->second;
			}
			return NULL;
		}

		/// �Ƴ���Ч�����ʽ������
		void removeFormat( CChar* name )
		{
			std::map<Str,TYPE0*>::iterator iter = mFormats.find(name);
			if ( iter!=mFormats.end() )
			{
				mGroupElm->DeleteChild(iter->second->getXmlElm());
				MG_DELETE( iter->second );
				mFormats.erase( iter );
			}
		}

		/// �Ƴ����ж����ʽ������
		void removeAllFormat()
		{
			std::map<Str,TYPE0*>::iterator iter = mFormats.begin();
			for ( ;iter!=mFormats.end(); iter++ )
			{
				MG_DELETE( iter->second );
			}
			mFormats.clear();

			if (mGroupElm)
			{
				mGroupElm->DeleteChildren();
				mGroupElm = NULL;
			}
		}

		/// �õ���Ч�����ʽ�������б�
		void getFormatList( std::vector<IEffectObjectXmlFormat*>& formatList )
		{
			std::map<Str,TYPE0*>::iterator iter = mFormats.begin();
			for ( ;iter!=mFormats.end(); iter++ )
			{
				formatList.push_back( iter->second );
			}
		}

		/// ����XMl��Ԫ��
		void setGroupElm(XMLElement* elm)
		{
			mGroupElm = elm;
		}

		/// ��ȡxml��Ԫ��
		XMLElement* getGroupElm()
		{
			return mGroupElm;
		}

	private:
		EffectComponent* mComponent;
		Str mGroupName;
		std::map<Str,TYPE0*> mFormats;
		XMLElement*	mGroupElm;
	};

	/******************************************************************************/
	//��Ч�������л�
	/******************************************************************************/
	class EffectXmlSerializer : public IEffectXmlSerializer
	{
	public:
		EffectXmlSerializer(EffectComponent* component);
		virtual ~EffectXmlSerializer();
	
		/// ������Ч����ļ�
		virtual	Bool					createEffectComponentFormat();
		/// ��ȡ��Ч����ļ�
		virtual Bool					loadEffectComponentFormat(CChar* fileName);
		/// ������Ч����ļ�
		virtual Bool					saveEffectFile(CChar* fileName);

		/// �õ�������
		virtual Str                     getTypeName( SceneObjectTypes type );

		/// ������Ч������ʽ������
		virtual IEffectObjectXmlFormat*  addEffectObjectFormat( ISceneObject* object, Bool isAddToXML = true, tinyxml2::XMLElement * elm = NULL);
		/// �õ���Ч������ʽ������
		virtual IEffectObjectXmlFormat*  getEffectObjectFormat( CChar* name, SceneObjectTypes type);
		/// �Ƴ���Ч������ʽ������
		virtual void                    removeEffectObjectFormat( IEffectObjectXmlFormat* format, Bool isDestroyEntity=false);
		/// �Ƴ���Ч������ʽ������
		virtual void                    removeEffectObjectFormat( CChar* name, SceneObjectTypes type, Bool isDestroyEntity=false);

		/// �õ����������ʽ�������б�
		virtual void                    getEffectObjectXmlFormatList( SceneObjectTypes type, std::vector<IEffectObjectXmlFormat*>& formatList);

		/// ж��
		virtual void                    unLoad();
		/// ��õ�ǰ�ĳ����ļ���
		virtual Str						getEffectFileName();

		virtual EffectComponent*		getEffectComponent();

		virtual XMLElement*				getTimeLineXMLEle();
	private:

		/// Component
		EffectComponent*		mComponent;
		/// ��������
		Scene*  mScene;

		/// Xml�ĵ�����.
		tinyxml2::XMLDocument*	mEffectXmlDoc;

		/// �µ���Ч��ʽ��PU��ʽ������
		EffectObjectXmlFormatGroup<EffectComponentPUXmlFormat,PUEffect>* mEffectComponentPUFormatGroup;
		/// �µ���Ч��ʵ���ʽ��ʵ���ʽ������
		EffectObjectXmlFormatGroup<EffectComponentEntityXmlFormat,Entity>* mEffectComponentEntityFormatGroup;

		/// �µ���Ч��ʽ��ʱ���߸�ʽ������
		EffectObjectXmlFormatGroup<EffectComponentTimeLineXmlFormat,EffectComponentTimeLine>* mEffectComponentTimeLineFormatGroup;

		/// �µ�����Ч��ʵ���ʽ������
		EffectObjectXmlFormatGroup<ModelVisibleEventXmlFormat,ModelVisibleEffectEvent>* mModelVisibleEventFormatGroup;
		/// �µ�����Ч��ʵ���ʽ������
		EffectObjectXmlFormatGroup<ModelAnimationEventXmlFormat,ModelAnimationEffectEvent>* mModelAnimationEventFormatGroup;
		/// �µ�����Ч��ʵ���ʽ������
		EffectObjectXmlFormatGroup<ModelBindEventXmlFormat,ModelBindEffectEvent>* mModelBindEventFormatGroup;
		/// �µ�����Ч��ʵ���ʽ������
		EffectObjectXmlFormatGroup<PUStartEventXmlFormat,PUStartEffectEvent>* mPUStartEventFormatGroup;
		/// �µ�����Ч��ʵ���ʽ������
		EffectObjectXmlFormatGroup<PUStopEventXmlFormat,PUStopEffectEvent>* mPUStopEventFormatGroup;
		/// �µ�����Ч��ʵ���ʽ������
		EffectObjectXmlFormatGroup<PUBindEventXmlFormat,PUBindEffectEvent>* mPUBindEventFormatGroup;
		/// �µ�����Ч��ʵ���ʽ������
		EffectObjectXmlFormatGroup<WeaponLightEventXmlFormat,WeaponLightEvent>* mWeaponLightEventFormatGroup;
		/// �µ�����Ч��ʵ���ʽ������
		EffectObjectXmlFormatGroup<EffectFadeEventXmlFormat,EffectFadeEvent>* mEffectFadeEventFormatGroup;
		
	};

	/******************************************************************************/
	//�µ���Ч�����PU��ʽ������
	/******************************************************************************/
	class EffectComponentPUXmlFormat : public IEffectObjectXmlFormat
	{
		friend class EffectXmlSerializer;

	public:

		EffectComponentPUXmlFormat(EffectComponent* component, tinyxml2::XMLElement* elm, PUEffect* puEffect);
		virtual ~EffectComponentPUXmlFormat();

		/// ��䳡���������ݵ�Xml������
		virtual void            fill(Bool isAddToXML);
		/// Ӧ��Xml���ݵ�����������
		virtual void            apply(Bool isCheckDirty=false);
		/// �õ���������
		virtual ISceneObject*   getSceneObject();
		/// Ӧ��Xml���ݵ�����ʵ������У����ʵ�����Ϊ���򴴽�
		static PUEffect*	    apply(EffectComponent* component, tinyxml2::XMLElement * elm, PUEffect* puEffect=NULL, Bool isCheckDirty=false);

		// Ӧ������
		static UInt applyIndex;
		static UInt applyTotal;

	protected:

		/// ʵ�����
		PUEffect* mPUEffect;
		/// ��������
		Scene* mScene;
		/// component����
		EffectComponent* mComponent;
	};

	/******************************************************************************/
	//�µ���Ч�����PU��ʽ������
	/******************************************************************************/
	class EffectComponentEntityXmlFormat : public IEffectObjectXmlFormat
	{
		friend class EffectXmlSerializer;

	public:

		EffectComponentEntityXmlFormat(EffectComponent* component, tinyxml2::XMLElement * elm, Entity* entity);
		virtual ~EffectComponentEntityXmlFormat();

		/// ��䳡���������ݵ�Xml������
		virtual void            fill(Bool isAddToXML);
		/// Ӧ��Xml���ݵ�����������
		virtual void            apply(Bool isCheckDirty=false);
		/// �õ���������
		virtual ISceneObject*   getSceneObject(){return mEntity;};
		/// Ӧ��Xml���ݵ�����ʵ������У����ʵ�����Ϊ���򴴽�
		static Entity*			apply(EffectComponent* component, tinyxml2::XMLElement * elm, Entity* entity=NULL, Bool isCheckDirty=false);

		// Ӧ������
		static UInt applyIndex;
		static UInt applyTotal;

	protected:

		///ʵ�����
		Entity* mEntity;
		///��������
		Scene* mScene;
		/// Component
		EffectComponent* mComponent;
	};

	/******************************************************************************/
	//�µ���Ч�����ʱ���߸�ʽ������
	/******************************************************************************/
	class EffectComponentTimeLineXmlFormat : public IEffectObjectXmlFormat
	{
		friend class EffectXmlSerializer;

	public:

		EffectComponentTimeLineXmlFormat(EffectComponent* component, tinyxml2::XMLElement * elm, EffectComponentTimeLine* timeline);
		virtual ~EffectComponentTimeLineXmlFormat();

		/// ��䳡���������ݵ�Xml������
		virtual void            fill(Bool isAddToXML);
		/// Ӧ��Xml���ݵ�����������
		virtual void            apply(Bool isCheckDirty=false);
		/// �õ���������
		virtual ISceneObject*   getSceneObject();
		/// Ӧ��Xml���ݵ�����ʵ������У����ʵ�����Ϊ���򴴽�
		static EffectComponentTimeLine*    apply(EffectComponent* component, tinyxml2::XMLElement * elm, EffectComponentTimeLine* timeline=NULL, Bool isCheckDirty=false);

		static	void			applyEvent(EffectComponent* component, tinyxml2::XMLElement * elm);
		// Ӧ������
		static UInt applyIndex;
		static UInt applyTotal;

	protected:

		///ʵ�����
		EffectComponentTimeLine* mEffectComponentTimeLine;
		///��������
		Scene* mScene;
		///Component
		EffectComponent* mComponent;
	};

	/******************************************************************************/
	//�µ���Ч�����ģ����ʾ�¼���ʽ������
	/******************************************************************************/
	class ModelVisibleEventXmlFormat : public IEffectObjectXmlFormat
	{
		friend class EffectXmlSerializer;

	public:

		ModelVisibleEventXmlFormat(EffectComponent* component, tinyxml2::XMLElement * elm, ModelVisibleEffectEvent* visibleEvent);
		virtual ~ModelVisibleEventXmlFormat();

		/// ��䳡���������ݵ�Xml������
		virtual void            fill(Bool isAddToXML);
		/// Ӧ��Xml���ݵ�����������
		virtual void            apply(Bool isCheckDirty=false);
		/// �õ���������
		virtual ISceneObject*   getSceneObject();
		/// Ӧ��Xml���ݵ�����ʵ������У����ʵ�����Ϊ���򴴽�
		static ModelVisibleEffectEvent*    apply(EffectComponent* component, tinyxml2::XMLElement * elm, ModelVisibleEffectEvent* event=NULL, Bool isCheckDirty=false);

		// Ӧ������
		static UInt applyIndex;
		static UInt applyTotal;

	protected:

		///ʵ�����
		ModelVisibleEffectEvent* mModelVisibleEvent;
		///��������
		Scene* mScene;
		/// Component
		EffectComponent* mComponent;
	};

	/******************************************************************************/
	//�µ���Ч�����ģ�Ͳ��Ŷ����¼���ʽ������
	/******************************************************************************/
	class ModelAnimationEventXmlFormat : public IEffectObjectXmlFormat
	{
		friend class EffectXmlSerializer;

	public:

		ModelAnimationEventXmlFormat(EffectComponent* component, tinyxml2::XMLElement * elm, ModelAnimationEffectEvent* aniEvent);
		virtual ~ModelAnimationEventXmlFormat();

		/// ��䳡���������ݵ�Xml������
		virtual void            fill(Bool isAddToXML);
		/// Ӧ��Xml���ݵ�����������
		virtual void            apply(Bool isCheckDirty=false);
		/// �õ���������
		virtual ISceneObject*   getSceneObject();
		/// Ӧ��Xml���ݵ�����ʵ������У����ʵ�����Ϊ���򴴽�
		static ModelAnimationEffectEvent*    apply(EffectComponent* component, tinyxml2::XMLElement * elm, ModelAnimationEffectEvent* event=NULL, Bool isCheckDirty=false);

		// Ӧ������
		static UInt applyIndex;
		static UInt applyTotal;

	protected:

		///ʵ�����
		ModelAnimationEffectEvent* mModelAnimationEvent;
		///��������
		Scene* mScene;
		///
		EffectComponent* mComponent;
	};

	/******************************************************************************/
	//�µ���Ч�����ģ�Ͱ��¼���ʽ������
	/******************************************************************************/
	class ModelBindEventXmlFormat : public IEffectObjectXmlFormat
	{
		friend class EffectXmlSerializer;

	public:

		ModelBindEventXmlFormat(EffectComponent* component, tinyxml2::XMLElement * elm, ModelBindEffectEvent* bindEvent);
		virtual ~ModelBindEventXmlFormat();

		/// ��䳡���������ݵ�Xml������
		virtual void            fill(Bool isAddToXML);
		/// Ӧ��Xml���ݵ�����������
		virtual void            apply(Bool isCheckDirty=false);
		/// �õ���������
		virtual ISceneObject*   getSceneObject();
		/// Ӧ��Xml���ݵ�����ʵ������У����ʵ�����Ϊ���򴴽�
		static ModelBindEffectEvent*    apply(EffectComponent* component, tinyxml2::XMLElement * elm, ModelBindEffectEvent* event=NULL, Bool isCheckDirty=false);

		// Ӧ������
		static UInt applyIndex;
		static UInt applyTotal;

	protected:

		///ʵ�����
		ModelBindEffectEvent* mModelBindEvent;
		///��������
		Scene* mScene;
		///
		EffectComponent* mComponent;
	};

	/******************************************************************************/
	//�µ���Ч�������Ч��ʼ�¼���ʽ������
	/******************************************************************************/
	class PUStartEventXmlFormat : public IEffectObjectXmlFormat
	{
		friend class EffectXmlSerializer;

	public:

		PUStartEventXmlFormat(EffectComponent* component, tinyxml2::XMLElement * elm, PUStartEffectEvent* startEvent);
		virtual ~PUStartEventXmlFormat();

		/// ��䳡���������ݵ�Xml������
		virtual void            fill(Bool isAddToXML);
		/// Ӧ��Xml���ݵ�����������
		virtual void            apply(Bool isCheckDirty=false);
		/// �õ���������
		virtual ISceneObject*   getSceneObject();
		/// Ӧ��Xml���ݵ�����ʵ������У����ʵ�����Ϊ���򴴽�
		static PUStartEffectEvent*    apply(EffectComponent* component, tinyxml2::XMLElement * elm, PUStartEffectEvent* event=NULL, Bool isCheckDirty=false);

		// Ӧ������
		static UInt applyIndex;
		static UInt applyTotal;

	protected:

		///ʵ�����
		PUStartEffectEvent* mPUStartEvent;
		///��������
		Scene* mScene;
		///
		EffectComponent* mComponent;
	};

	/******************************************************************************/
	//�µ���Ч�������Чֹͣ�¼���ʽ������
	/******************************************************************************/
	class PUStopEventXmlFormat : public IEffectObjectXmlFormat
	{
		friend class EffectXmlSerializer;

	public:

		PUStopEventXmlFormat(EffectComponent* component, tinyxml2::XMLElement * elm, PUStopEffectEvent* stopEvent);
		virtual ~PUStopEventXmlFormat();

		/// ��䳡���������ݵ�Xml������
		virtual void            fill(Bool isAddToXML);
		/// Ӧ��Xml���ݵ�����������
		virtual void            apply(Bool isCheckDirty=false);
		/// �õ���������
		virtual ISceneObject*   getSceneObject();
		/// Ӧ��Xml���ݵ�����ʵ������У����ʵ�����Ϊ���򴴽�
		static PUStopEffectEvent*    apply(EffectComponent* component, tinyxml2::XMLElement * elm, PUStopEffectEvent* event=NULL, Bool isCheckDirty=false);

		// Ӧ������
		static UInt applyIndex;
		static UInt applyTotal;

	protected:

		///ʵ�����
		PUStopEffectEvent* mPUStopEvent;
		///��������
		Scene* mScene;
		///
		EffectComponent* mComponent;
	};

	/******************************************************************************/
	//�µ���Ч�������Ч���¼���ʽ������
	/******************************************************************************/
	class PUBindEventXmlFormat : public IEffectObjectXmlFormat
	{
		friend class EffectXmlSerializer;

	public:

		PUBindEventXmlFormat(EffectComponent* component, tinyxml2::XMLElement * elm, PUBindEffectEvent* bindEffect);
		virtual ~PUBindEventXmlFormat();

		/// ��䳡���������ݵ�Xml������
		virtual void            fill(Bool isAddToXML);
		/// Ӧ��Xml���ݵ�����������
		virtual void            apply(Bool isCheckDirty=false);
		/// �õ���������
		virtual ISceneObject*   getSceneObject();
		/// Ӧ��Xml���ݵ�����ʵ������У����ʵ�����Ϊ���򴴽�
		static PUBindEffectEvent*    apply(EffectComponent* component, tinyxml2::XMLElement * elm, PUBindEffectEvent* event=NULL, Bool isCheckDirty=false);

		// Ӧ������
		static UInt applyIndex;
		static UInt applyTotal;

	protected:

		///ʵ�����
		PUBindEffectEvent* mPUBindEvent;
		///��������
		Scene* mScene;
		///
		EffectComponent* mComponent;
	};

	/******************************************************************************/
	//�µ���Ч����ﵶ���¼���ʽ������
	/******************************************************************************/
	class WeaponLightEventXmlFormat : public IEffectObjectXmlFormat
	{
		friend class EffectXmlSerializer;

	public:

		WeaponLightEventXmlFormat(EffectComponent* component, tinyxml2::XMLElement * elm, WeaponLightEvent* weaponLightEffect);
		virtual ~WeaponLightEventXmlFormat();

		/// ��䳡���������ݵ�Xml������
		virtual void            fill(Bool isAddToXML);
		/// Ӧ��Xml���ݵ�����������
		virtual void            apply(Bool isCheckDirty=false);
		/// �õ���������
		virtual ISceneObject*   getSceneObject();
		/// Ӧ��Xml���ݵ�����ʵ������У����ʵ�����Ϊ���򴴽�
		static WeaponLightEvent*    apply(EffectComponent* component, tinyxml2::XMLElement * elm, WeaponLightEvent* event=NULL, Bool isCheckDirty=false);

		// Ӧ������
		static UInt applyIndex;
		static UInt applyTotal;

	protected:

		///ʵ�����
		WeaponLightEvent* mWeaponLightEvent;
		///��������
		Scene* mScene;
		///
		EffectComponent* mComponent;
	};


	/******************************************************************************/
	//�µ���Ч����･���¼���ʽ������
	/******************************************************************************/
	class EffectFadeEventXmlFormat : public IEffectObjectXmlFormat
	{
		friend class EffectXmlSerializer;

	public:

		EffectFadeEventXmlFormat(EffectComponent* component, tinyxml2::XMLElement * elm, EffectFadeEvent* effectFade);
		virtual ~EffectFadeEventXmlFormat();

		/// ��䳡���������ݵ�Xml������
		virtual void            fill(Bool isAddToXML);
		/// Ӧ��Xml���ݵ�����������
		virtual void            apply(Bool isCheckDirty=false);
		/// �õ���������
		virtual ISceneObject*   getSceneObject();
		/// Ӧ��Xml���ݵ�����ʵ������У����ʵ�����Ϊ���򴴽�
		static EffectFadeEvent*    apply(EffectComponent* component, tinyxml2::XMLElement * elm, EffectFadeEvent* event=NULL, Bool isCheckDirty=false);

		// Ӧ������
		static UInt applyIndex;
		static UInt applyTotal;

	protected:

		///ʵ�����
		EffectFadeEvent* mEffectFadeEvent;
		///��������
		Scene* mScene;
		///
		EffectComponent* mComponent;
	};
}

#endif