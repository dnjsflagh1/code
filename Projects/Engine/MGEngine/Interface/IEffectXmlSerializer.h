/******************************************************************************/
#ifndef _IEFFECTXMLSERIALIZER_H
#define _IEFFECTXMLSERIALIZER_H
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"

/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	//特效格式化对象接口
	/******************************************************************************/
	class IEffectXmlFormat
	{
	public:
		/// 填充场景对象数据到Xml数据中
		virtual void                    fill(Bool isAddToXML) = 0;
		/// 应用Xml数据到场景对象中
		virtual void                    apply(Bool isCheckDirty=false) = 0;
		/// 得到Xml数据对象
		virtual void                    setXmlElm(XMLElement* elm){ mXmlElm = elm; };
		/// 得到Xml数据对象
		virtual XMLElement*				getXmlElm() {return mXmlElm;};
	protected:
		XMLElement* mXmlElm;
	};

	/******************************************************************************/
	//特效格式化对象接口
	/******************************************************************************/
	class IEffectObjectXmlFormat : public IEffectXmlFormat
	{
	public://get or set
		/// 得到场景对象
		virtual ISceneObject*           getSceneObject() = 0;
	};

	/******************************************************************************/
	//特效对象序列化接口
	/******************************************************************************/
	class IEffectXmlSerializer
	{
	public:
		/// 创建特效组件文件
		virtual	Bool					createEffectComponentFormat() = 0;
		/// 读取特效组件文件
		virtual Bool					loadEffectComponentFormat(CChar* fileName) = 0;
		/// 保存特效组件文件
		virtual Bool					saveEffectFile(CChar* fileName) = 0;

		/// 得到类型名
		virtual Str                     getTypeName( SceneObjectTypes type ) = 0 ;

		/// 增加特效里对象格式化对象
		virtual IEffectObjectXmlFormat*  addEffectObjectFormat( ISceneObject* object, Bool isAddToXML = true, tinyxml2::XMLElement * elm = NULL) = 0 ;
		/// 得到特效里对象格式化对象
		virtual IEffectObjectXmlFormat*  getEffectObjectFormat( CChar* name, SceneObjectTypes type) = 0 ;
		/// 移除特效里对象格式化对象
		virtual void                    removeEffectObjectFormat( IEffectObjectXmlFormat* format, Bool isDestroyEntity=false) = 0 ;
		/// 移除特效里对象格式化对象
		virtual void                    removeEffectObjectFormat( CChar* name, SceneObjectTypes type, Bool isDestroyEntity=false) = 0 ;

		/// 得到场景对象格式化对象列表
		virtual void                    getEffectObjectXmlFormatList( SceneObjectTypes type, std::vector<IEffectObjectXmlFormat*>& formatList) = 0;

		/// 卸载
		virtual void                    unLoad() = 0;
		/// 获得当前的场景文件名
		virtual Str						getEffectFileName() = 0;

		virtual IEffectComponent*		getEffectComponent() = 0;

		virtual XMLElement*				getTimeLineXMLEle() = 0;
	};

}

/******************************************************************************/
#endif
