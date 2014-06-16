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
	//特效格式化对象
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

		/// 加载特效对象格式化对象组
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

		/// 增加特效对象格式化对象
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

		/// 得到特效对象格式化对象
		TYPE0* getFormat( CChar* name )
		{
			std::map<Str,TYPE0*>::iterator iter = mFormats.find(name);
			if ( iter!=mFormats.end() )
			{
				return iter->second;
			}
			return NULL;
		}

		/// 移除特效对象格式化对象
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

		/// 移除所有对象格式化对象
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

		/// 得到特效对象格式化对象列表
		void getFormatList( std::vector<IEffectObjectXmlFormat*>& formatList )
		{
			std::map<Str,TYPE0*>::iterator iter = mFormats.begin();
			for ( ;iter!=mFormats.end(); iter++ )
			{
				formatList.push_back( iter->second );
			}
		}

		/// 设置XMl组元素
		void setGroupElm(XMLElement* elm)
		{
			mGroupElm = elm;
		}

		/// 获取xml组元素
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
	//特效对象序列化
	/******************************************************************************/
	class EffectXmlSerializer : public IEffectXmlSerializer
	{
	public:
		EffectXmlSerializer(EffectComponent* component);
		virtual ~EffectXmlSerializer();
	
		/// 创建特效组件文件
		virtual	Bool					createEffectComponentFormat();
		/// 读取特效组件文件
		virtual Bool					loadEffectComponentFormat(CChar* fileName);
		/// 保存特效组件文件
		virtual Bool					saveEffectFile(CChar* fileName);

		/// 得到类型名
		virtual Str                     getTypeName( SceneObjectTypes type );

		/// 增加特效里对象格式化对象
		virtual IEffectObjectXmlFormat*  addEffectObjectFormat( ISceneObject* object, Bool isAddToXML = true, tinyxml2::XMLElement * elm = NULL);
		/// 得到特效里对象格式化对象
		virtual IEffectObjectXmlFormat*  getEffectObjectFormat( CChar* name, SceneObjectTypes type);
		/// 移除特效里对象格式化对象
		virtual void                    removeEffectObjectFormat( IEffectObjectXmlFormat* format, Bool isDestroyEntity=false);
		/// 移除特效里对象格式化对象
		virtual void                    removeEffectObjectFormat( CChar* name, SceneObjectTypes type, Bool isDestroyEntity=false);

		/// 得到场景对象格式化对象列表
		virtual void                    getEffectObjectXmlFormatList( SceneObjectTypes type, std::vector<IEffectObjectXmlFormat*>& formatList);

		/// 卸载
		virtual void                    unLoad();
		/// 获得当前的场景文件名
		virtual Str						getEffectFileName();

		virtual EffectComponent*		getEffectComponent();

		virtual XMLElement*				getTimeLineXMLEle();
	private:

		/// Component
		EffectComponent*		mComponent;
		/// 场景对象
		Scene*  mScene;

		/// Xml文档对象.
		tinyxml2::XMLDocument*	mEffectXmlDoc;

		/// 新的特效格式下PU格式化对象
		EffectObjectXmlFormatGroup<EffectComponentPUXmlFormat,PUEffect>* mEffectComponentPUFormatGroup;
		/// 新的特效里实体格式下实体格式化对象
		EffectObjectXmlFormatGroup<EffectComponentEntityXmlFormat,Entity>* mEffectComponentEntityFormatGroup;

		/// 新的特效格式下时间线格式化对象
		EffectObjectXmlFormatGroup<EffectComponentTimeLineXmlFormat,EffectComponentTimeLine>* mEffectComponentTimeLineFormatGroup;

		/// 新的子特效里实体格式化对象
		EffectObjectXmlFormatGroup<ModelVisibleEventXmlFormat,ModelVisibleEffectEvent>* mModelVisibleEventFormatGroup;
		/// 新的子特效里实体格式化对象
		EffectObjectXmlFormatGroup<ModelAnimationEventXmlFormat,ModelAnimationEffectEvent>* mModelAnimationEventFormatGroup;
		/// 新的子特效里实体格式化对象
		EffectObjectXmlFormatGroup<ModelBindEventXmlFormat,ModelBindEffectEvent>* mModelBindEventFormatGroup;
		/// 新的子特效里实体格式化对象
		EffectObjectXmlFormatGroup<PUStartEventXmlFormat,PUStartEffectEvent>* mPUStartEventFormatGroup;
		/// 新的子特效里实体格式化对象
		EffectObjectXmlFormatGroup<PUStopEventXmlFormat,PUStopEffectEvent>* mPUStopEventFormatGroup;
		/// 新的子特效里实体格式化对象
		EffectObjectXmlFormatGroup<PUBindEventXmlFormat,PUBindEffectEvent>* mPUBindEventFormatGroup;
		/// 新的子特效里实体格式化对象
		EffectObjectXmlFormatGroup<WeaponLightEventXmlFormat,WeaponLightEvent>* mWeaponLightEventFormatGroup;
		/// 新的子特效里实体格式化对象
		EffectObjectXmlFormatGroup<EffectFadeEventXmlFormat,EffectFadeEvent>* mEffectFadeEventFormatGroup;
		
	};

	/******************************************************************************/
	//新的特效组件里PU格式化对象
	/******************************************************************************/
	class EffectComponentPUXmlFormat : public IEffectObjectXmlFormat
	{
		friend class EffectXmlSerializer;

	public:

		EffectComponentPUXmlFormat(EffectComponent* component, tinyxml2::XMLElement* elm, PUEffect* puEffect);
		virtual ~EffectComponentPUXmlFormat();

		/// 填充场景对象数据到Xml数据中
		virtual void            fill(Bool isAddToXML);
		/// 应用Xml数据到场景对象中
		virtual void            apply(Bool isCheckDirty=false);
		/// 得到场景对象
		virtual ISceneObject*   getSceneObject();
		/// 应用Xml数据到场景实体对象中，如果实体对象为空则创建
		static PUEffect*	    apply(EffectComponent* component, tinyxml2::XMLElement * elm, PUEffect* puEffect=NULL, Bool isCheckDirty=false);

		// 应用索引
		static UInt applyIndex;
		static UInt applyTotal;

	protected:

		/// 实体对象
		PUEffect* mPUEffect;
		/// 场景对象
		Scene* mScene;
		/// component对象
		EffectComponent* mComponent;
	};

	/******************************************************************************/
	//新的特效组件里PU格式化对象
	/******************************************************************************/
	class EffectComponentEntityXmlFormat : public IEffectObjectXmlFormat
	{
		friend class EffectXmlSerializer;

	public:

		EffectComponentEntityXmlFormat(EffectComponent* component, tinyxml2::XMLElement * elm, Entity* entity);
		virtual ~EffectComponentEntityXmlFormat();

		/// 填充场景对象数据到Xml数据中
		virtual void            fill(Bool isAddToXML);
		/// 应用Xml数据到场景对象中
		virtual void            apply(Bool isCheckDirty=false);
		/// 得到场景对象
		virtual ISceneObject*   getSceneObject(){return mEntity;};
		/// 应用Xml数据到场景实体对象中，如果实体对象为空则创建
		static Entity*			apply(EffectComponent* component, tinyxml2::XMLElement * elm, Entity* entity=NULL, Bool isCheckDirty=false);

		// 应用索引
		static UInt applyIndex;
		static UInt applyTotal;

	protected:

		///实体对象
		Entity* mEntity;
		///场景对象
		Scene* mScene;
		/// Component
		EffectComponent* mComponent;
	};

	/******************************************************************************/
	//新的特效组件里时间线格式化对象
	/******************************************************************************/
	class EffectComponentTimeLineXmlFormat : public IEffectObjectXmlFormat
	{
		friend class EffectXmlSerializer;

	public:

		EffectComponentTimeLineXmlFormat(EffectComponent* component, tinyxml2::XMLElement * elm, EffectComponentTimeLine* timeline);
		virtual ~EffectComponentTimeLineXmlFormat();

		/// 填充场景对象数据到Xml数据中
		virtual void            fill(Bool isAddToXML);
		/// 应用Xml数据到场景对象中
		virtual void            apply(Bool isCheckDirty=false);
		/// 得到场景对象
		virtual ISceneObject*   getSceneObject();
		/// 应用Xml数据到场景实体对象中，如果实体对象为空则创建
		static EffectComponentTimeLine*    apply(EffectComponent* component, tinyxml2::XMLElement * elm, EffectComponentTimeLine* timeline=NULL, Bool isCheckDirty=false);

		static	void			applyEvent(EffectComponent* component, tinyxml2::XMLElement * elm);
		// 应用索引
		static UInt applyIndex;
		static UInt applyTotal;

	protected:

		///实体对象
		EffectComponentTimeLine* mEffectComponentTimeLine;
		///场景对象
		Scene* mScene;
		///Component
		EffectComponent* mComponent;
	};

	/******************************************************************************/
	//新的特效组件里模型显示事件格式化对象
	/******************************************************************************/
	class ModelVisibleEventXmlFormat : public IEffectObjectXmlFormat
	{
		friend class EffectXmlSerializer;

	public:

		ModelVisibleEventXmlFormat(EffectComponent* component, tinyxml2::XMLElement * elm, ModelVisibleEffectEvent* visibleEvent);
		virtual ~ModelVisibleEventXmlFormat();

		/// 填充场景对象数据到Xml数据中
		virtual void            fill(Bool isAddToXML);
		/// 应用Xml数据到场景对象中
		virtual void            apply(Bool isCheckDirty=false);
		/// 得到场景对象
		virtual ISceneObject*   getSceneObject();
		/// 应用Xml数据到场景实体对象中，如果实体对象为空则创建
		static ModelVisibleEffectEvent*    apply(EffectComponent* component, tinyxml2::XMLElement * elm, ModelVisibleEffectEvent* event=NULL, Bool isCheckDirty=false);

		// 应用索引
		static UInt applyIndex;
		static UInt applyTotal;

	protected:

		///实体对象
		ModelVisibleEffectEvent* mModelVisibleEvent;
		///场景对象
		Scene* mScene;
		/// Component
		EffectComponent* mComponent;
	};

	/******************************************************************************/
	//新的特效组件里模型播放动画事件格式化对象
	/******************************************************************************/
	class ModelAnimationEventXmlFormat : public IEffectObjectXmlFormat
	{
		friend class EffectXmlSerializer;

	public:

		ModelAnimationEventXmlFormat(EffectComponent* component, tinyxml2::XMLElement * elm, ModelAnimationEffectEvent* aniEvent);
		virtual ~ModelAnimationEventXmlFormat();

		/// 填充场景对象数据到Xml数据中
		virtual void            fill(Bool isAddToXML);
		/// 应用Xml数据到场景对象中
		virtual void            apply(Bool isCheckDirty=false);
		/// 得到场景对象
		virtual ISceneObject*   getSceneObject();
		/// 应用Xml数据到场景实体对象中，如果实体对象为空则创建
		static ModelAnimationEffectEvent*    apply(EffectComponent* component, tinyxml2::XMLElement * elm, ModelAnimationEffectEvent* event=NULL, Bool isCheckDirty=false);

		// 应用索引
		static UInt applyIndex;
		static UInt applyTotal;

	protected:

		///实体对象
		ModelAnimationEffectEvent* mModelAnimationEvent;
		///场景对象
		Scene* mScene;
		///
		EffectComponent* mComponent;
	};

	/******************************************************************************/
	//新的特效组件里模型绑定事件格式化对象
	/******************************************************************************/
	class ModelBindEventXmlFormat : public IEffectObjectXmlFormat
	{
		friend class EffectXmlSerializer;

	public:

		ModelBindEventXmlFormat(EffectComponent* component, tinyxml2::XMLElement * elm, ModelBindEffectEvent* bindEvent);
		virtual ~ModelBindEventXmlFormat();

		/// 填充场景对象数据到Xml数据中
		virtual void            fill(Bool isAddToXML);
		/// 应用Xml数据到场景对象中
		virtual void            apply(Bool isCheckDirty=false);
		/// 得到场景对象
		virtual ISceneObject*   getSceneObject();
		/// 应用Xml数据到场景实体对象中，如果实体对象为空则创建
		static ModelBindEffectEvent*    apply(EffectComponent* component, tinyxml2::XMLElement * elm, ModelBindEffectEvent* event=NULL, Bool isCheckDirty=false);

		// 应用索引
		static UInt applyIndex;
		static UInt applyTotal;

	protected:

		///实体对象
		ModelBindEffectEvent* mModelBindEvent;
		///场景对象
		Scene* mScene;
		///
		EffectComponent* mComponent;
	};

	/******************************************************************************/
	//新的特效组件里特效开始事件格式化对象
	/******************************************************************************/
	class PUStartEventXmlFormat : public IEffectObjectXmlFormat
	{
		friend class EffectXmlSerializer;

	public:

		PUStartEventXmlFormat(EffectComponent* component, tinyxml2::XMLElement * elm, PUStartEffectEvent* startEvent);
		virtual ~PUStartEventXmlFormat();

		/// 填充场景对象数据到Xml数据中
		virtual void            fill(Bool isAddToXML);
		/// 应用Xml数据到场景对象中
		virtual void            apply(Bool isCheckDirty=false);
		/// 得到场景对象
		virtual ISceneObject*   getSceneObject();
		/// 应用Xml数据到场景实体对象中，如果实体对象为空则创建
		static PUStartEffectEvent*    apply(EffectComponent* component, tinyxml2::XMLElement * elm, PUStartEffectEvent* event=NULL, Bool isCheckDirty=false);

		// 应用索引
		static UInt applyIndex;
		static UInt applyTotal;

	protected:

		///实体对象
		PUStartEffectEvent* mPUStartEvent;
		///场景对象
		Scene* mScene;
		///
		EffectComponent* mComponent;
	};

	/******************************************************************************/
	//新的特效组件里特效停止事件格式化对象
	/******************************************************************************/
	class PUStopEventXmlFormat : public IEffectObjectXmlFormat
	{
		friend class EffectXmlSerializer;

	public:

		PUStopEventXmlFormat(EffectComponent* component, tinyxml2::XMLElement * elm, PUStopEffectEvent* stopEvent);
		virtual ~PUStopEventXmlFormat();

		/// 填充场景对象数据到Xml数据中
		virtual void            fill(Bool isAddToXML);
		/// 应用Xml数据到场景对象中
		virtual void            apply(Bool isCheckDirty=false);
		/// 得到场景对象
		virtual ISceneObject*   getSceneObject();
		/// 应用Xml数据到场景实体对象中，如果实体对象为空则创建
		static PUStopEffectEvent*    apply(EffectComponent* component, tinyxml2::XMLElement * elm, PUStopEffectEvent* event=NULL, Bool isCheckDirty=false);

		// 应用索引
		static UInt applyIndex;
		static UInt applyTotal;

	protected:

		///实体对象
		PUStopEffectEvent* mPUStopEvent;
		///场景对象
		Scene* mScene;
		///
		EffectComponent* mComponent;
	};

	/******************************************************************************/
	//新的特效组件里特效绑定事件格式化对象
	/******************************************************************************/
	class PUBindEventXmlFormat : public IEffectObjectXmlFormat
	{
		friend class EffectXmlSerializer;

	public:

		PUBindEventXmlFormat(EffectComponent* component, tinyxml2::XMLElement * elm, PUBindEffectEvent* bindEffect);
		virtual ~PUBindEventXmlFormat();

		/// 填充场景对象数据到Xml数据中
		virtual void            fill(Bool isAddToXML);
		/// 应用Xml数据到场景对象中
		virtual void            apply(Bool isCheckDirty=false);
		/// 得到场景对象
		virtual ISceneObject*   getSceneObject();
		/// 应用Xml数据到场景实体对象中，如果实体对象为空则创建
		static PUBindEffectEvent*    apply(EffectComponent* component, tinyxml2::XMLElement * elm, PUBindEffectEvent* event=NULL, Bool isCheckDirty=false);

		// 应用索引
		static UInt applyIndex;
		static UInt applyTotal;

	protected:

		///实体对象
		PUBindEffectEvent* mPUBindEvent;
		///场景对象
		Scene* mScene;
		///
		EffectComponent* mComponent;
	};

	/******************************************************************************/
	//新的特效组件里刀光事件格式化对象
	/******************************************************************************/
	class WeaponLightEventXmlFormat : public IEffectObjectXmlFormat
	{
		friend class EffectXmlSerializer;

	public:

		WeaponLightEventXmlFormat(EffectComponent* component, tinyxml2::XMLElement * elm, WeaponLightEvent* weaponLightEffect);
		virtual ~WeaponLightEventXmlFormat();

		/// 填充场景对象数据到Xml数据中
		virtual void            fill(Bool isAddToXML);
		/// 应用Xml数据到场景对象中
		virtual void            apply(Bool isCheckDirty=false);
		/// 得到场景对象
		virtual ISceneObject*   getSceneObject();
		/// 应用Xml数据到场景实体对象中，如果实体对象为空则创建
		static WeaponLightEvent*    apply(EffectComponent* component, tinyxml2::XMLElement * elm, WeaponLightEvent* event=NULL, Bool isCheckDirty=false);

		// 应用索引
		static UInt applyIndex;
		static UInt applyTotal;

	protected:

		///实体对象
		WeaponLightEvent* mWeaponLightEvent;
		///场景对象
		Scene* mScene;
		///
		EffectComponent* mComponent;
	};


	/******************************************************************************/
	//新的特效组件里渐变事件格式化对象
	/******************************************************************************/
	class EffectFadeEventXmlFormat : public IEffectObjectXmlFormat
	{
		friend class EffectXmlSerializer;

	public:

		EffectFadeEventXmlFormat(EffectComponent* component, tinyxml2::XMLElement * elm, EffectFadeEvent* effectFade);
		virtual ~EffectFadeEventXmlFormat();

		/// 填充场景对象数据到Xml数据中
		virtual void            fill(Bool isAddToXML);
		/// 应用Xml数据到场景对象中
		virtual void            apply(Bool isCheckDirty=false);
		/// 得到场景对象
		virtual ISceneObject*   getSceneObject();
		/// 应用Xml数据到场景实体对象中，如果实体对象为空则创建
		static EffectFadeEvent*    apply(EffectComponent* component, tinyxml2::XMLElement * elm, EffectFadeEvent* event=NULL, Bool isCheckDirty=false);

		// 应用索引
		static UInt applyIndex;
		static UInt applyTotal;

	protected:

		///实体对象
		EffectFadeEvent* mEffectFadeEvent;
		///场景对象
		Scene* mScene;
		///
		EffectComponent* mComponent;
	};
}

#endif