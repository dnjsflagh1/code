/******************************************************************************/
#ifndef _ISCENEXMLSERIALIZER_H
#define _ISCENEXMLSERIALIZER_H
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //�����������л��ӿ�
    /******************************************************************************/
    class ISceneXmlSerializer
    {
    public:

		/// ���볡��Ŀ¼��subĿ¼�����Ͻӿڣ� �ͻ��˵��øýӿ�
		virtual Bool					loadAllContent( CChar* pathName, CChar* subPathName, Bool isCreateFormats = false ) = 0;

        /// ���볡��Ŀ¼
        virtual Bool                    loadContent( CChar* pathName, Bool isCreateFormats = false ) = 0 ;
        /// ��������Ŀ¼
        virtual Bool                    saveContent( CChar* pathName ) = 0 ;
		/// ���г���					
		virtual Bool					clipContent(CChar* pathName, const RectF &clipRect) = 0;

		///create file
		//@{
		/// ��������Ŀ¼
		virtual Bool                    createSceneContent( TerrainDeclare* decl, Str path, Bool isCreateGameFile = false ) = 0;
		/// ����һ���յĳ���
		virtual Bool					createSceneContent( ) = 0;

		/// ������������
		virtual Bool					createTerrainFormat( TerrainDeclare* decl ) = 0;
		/// �����������
		virtual Bool					loadTerrainFormat(  Str path ) = 0;

		/// �������ļ�
		virtual Bool					createTreeFormat() = 0;
		/// ��ȡ����ʽ�ļ�
		virtual Bool					loadTreeFormat() = 0;

		/// ���������ļ�
		virtual Bool					createSceneFormat() = 0;
		/// ��ȡ�����ļ�
		virtual Bool					loadSceneFormat() = 0;
		///@}


        /// ���볡���ļ�
        virtual Bool                    loadSceneFile( CChar* filename, Bool isCreateFormats = false ) = 0 ;
        /// ���������ļ�
        virtual Bool                    saveSceneFile( CChar* filename ) = 0 ;

        /// ���븽�������ļ�
        virtual Bool                    loadSubSceneFile( CChar* filename, Bool isCreateFormats = false ) = 0 ;
		/// ж�ظ��������ļ�
		virtual void					unloadSubScene() = 0;
		///��ʾ�����ظ�����������
		virtual void					showSubscene(bool show) = 0;
        /// �������������ļ�
        virtual Bool                    saveSubSceneFile( CChar* filename ) = 0 ;

		/// ����ֲ���ļ�
		virtual Bool					loadTreeFile( CChar* filename, Bool isCreateFormats = false ) = 0;
        /// ����ֲ���ļ�
        virtual Bool					saveTreeFile( CChar* filename ) = 0;

        /// �õ�������
        virtual Str                     getTypeName( SceneObjectTypes type ) = 0 ;

        /// ���ӳ��������ʽ������
        virtual ISceneObjectXmlFormat*  addSceneObjectFormat( ISceneObject* object, Bool isSub = false ) = 0 ;
        /// �õ����������ʽ������
        virtual ISceneObjectXmlFormat*  getSceneObjectFormat( CChar* name, SceneObjectTypes type, Bool isSub = false  ) = 0 ;
        /// �Ƴ�ʵ���ʽ������
        virtual void                    removeSceneObjectFormat( ISceneObjectXmlFormat* format, Bool isDestroyEntity=false, Bool isSub = false  ) = 0 ;
        /// �Ƴ�ʵ���ʽ������
        virtual void                    removeSceneObjectFormat( CChar* name, SceneObjectTypes type, Bool isDestroyEntity=false, Bool isSub = false  ) = 0 ;

        /// �õ����������ʽ�������б�
        virtual void                    getSceneObjectXmlFormatList( SceneObjectTypes type, std::vector<ISceneObjectXmlFormat*>& formatList, Bool isSub = false  ) = 0;

		/// ж��
		virtual void                    unLoad() = 0;
		/// ��õ�ǰ�ĳ����ļ���
		virtual Str						getScenePath() = 0;

        /// ���ú��Լ��ص���
        virtual void                    clearIgnoreLoadGroup() = 0;
        virtual void                    addIgnoreLoadGroup( Str group ) = 0;
    };

    /******************************************************************************/
    //������ʽ������ӿ�
    /******************************************************************************/
    class IXmlFormat
    {
    public:
        /// ��䳡���������ݵ�Xml������
        virtual void                    fill() = 0;
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
    //������ʽ������ӿ�
    /******************************************************************************/
    class ISceneObjectXmlFormat : public IXmlFormat
    {
    public://get or set
        /// �õ���������
        virtual ISceneObject*           getSceneObject() = 0;
    };

}

/******************************************************************************/
#endif
