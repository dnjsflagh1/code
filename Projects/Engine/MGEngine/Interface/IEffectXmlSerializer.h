/******************************************************************************/
#ifndef _IEFFECTXMLSERIALIZER_H
#define _IEFFECTXMLSERIALIZER_H
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"

/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	//��Ч��ʽ������ӿ�
	/******************************************************************************/
	class IEffectXmlFormat
	{
	public:
		/// ��䳡���������ݵ�Xml������
		virtual void                    fill(Bool isAddToXML) = 0;
		/// Ӧ��Xml���ݵ�����������
		virtual void                    apply(Bool isCheckDirty=false) = 0;
		/// �õ�Xml���ݶ���
		virtual void                    setXmlElm(XMLElement* elm){ mXmlElm = elm; };
		/// �õ�Xml���ݶ���
		virtual XMLElement*				getXmlElm() {return mXmlElm;};
	protected:
		XMLElement* mXmlElm;
	};

	/******************************************************************************/
	//��Ч��ʽ������ӿ�
	/******************************************************************************/
	class IEffectObjectXmlFormat : public IEffectXmlFormat
	{
	public://get or set
		/// �õ���������
		virtual ISceneObject*           getSceneObject() = 0;
	};

	/******************************************************************************/
	//��Ч�������л��ӿ�
	/******************************************************************************/
	class IEffectXmlSerializer
	{
	public:
		/// ������Ч����ļ�
		virtual	Bool					createEffectComponentFormat() = 0;
		/// ��ȡ��Ч����ļ�
		virtual Bool					loadEffectComponentFormat(CChar* fileName) = 0;
		/// ������Ч����ļ�
		virtual Bool					saveEffectFile(CChar* fileName) = 0;

		/// �õ�������
		virtual Str                     getTypeName( SceneObjectTypes type ) = 0 ;

		/// ������Ч������ʽ������
		virtual IEffectObjectXmlFormat*  addEffectObjectFormat( ISceneObject* object, Bool isAddToXML = true, tinyxml2::XMLElement * elm = NULL) = 0 ;
		/// �õ���Ч������ʽ������
		virtual IEffectObjectXmlFormat*  getEffectObjectFormat( CChar* name, SceneObjectTypes type) = 0 ;
		/// �Ƴ���Ч������ʽ������
		virtual void                    removeEffectObjectFormat( IEffectObjectXmlFormat* format, Bool isDestroyEntity=false) = 0 ;
		/// �Ƴ���Ч������ʽ������
		virtual void                    removeEffectObjectFormat( CChar* name, SceneObjectTypes type, Bool isDestroyEntity=false) = 0 ;

		/// �õ����������ʽ�������б�
		virtual void                    getEffectObjectXmlFormatList( SceneObjectTypes type, std::vector<IEffectObjectXmlFormat*>& formatList) = 0;

		/// ж��
		virtual void                    unLoad() = 0;
		/// ��õ�ǰ�ĳ����ļ���
		virtual Str						getEffectFileName() = 0;

		virtual IEffectComponent*		getEffectComponent() = 0;

		virtual XMLElement*				getTimeLineXMLEle() = 0;
	};

}

/******************************************************************************/
#endif
