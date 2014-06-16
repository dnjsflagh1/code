/******************************************************************************/
#ifndef _SCENEXMLSERIALIZER_H_
#define _SCENEXMLSERIALIZER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ISceneXmlSerializer.h"

/******************************************************************************/
namespace MG
{

	class TerrainGridXmlFormat;
    class TerrainTextureXmlFormat;
    class TerrainBatchEntityLayerXmlFormat;
    class EntityXmlFormat;
	//class EffectEntityXmlFormat;
	// CN_MODIFY
	class EffectComponentXmlFormat;
	class TreeXmlFormat;
    class CameraXmlFormat;
    class EnvironmentXmlFormat;
	class SpeedTreeEnvXmlFormat;
	class GrassXmlFormat;
	class NodeTrackXmlFormat;
    /******************************************************************************/
    //�������θ�ʽ������
    /******************************************************************************/
    template<typename TYPE0, typename TYPE1>
    class SceneObjectXmlFormatGroup
    {
    public:
        SceneObjectXmlFormatGroup(Scene* scene, Str groupName)
            :mGroupElm(NULL)
            ,mScene(scene)
            ,mGroupName(groupName)
        {
        }
        ~SceneObjectXmlFormatGroup()
        {
            removeAllFormat();
        }

    public:

        /// ���س��������ʽ��������
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
                    TYPE0* format = MG_NEW TYPE0(mScene, currNode->ToElement(), NULL);
                    format->apply();

                    if ( format->getSceneObject() )
                    {
                        Str name = format->getSceneObject()->getName();
                        mFormats[name] = format;
                    }
                }else
                {
                    TYPE0::apply(mScene,currNode->ToElement());
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

        /// ���ӳ��������ʽ������
        TYPE0* addFormat( TYPE1* entity )
        {
            DYNAMIC_ASSERT(mGroupElm!=NULL);
            if ( mGroupElm )
            {
                XMLElement * elm = XmlHelper::addChild(mGroupElm, mGroupName.c_str(), false);
                TYPE0* format = MG_NEW TYPE0(mScene, elm, entity);
                format->fill();
                Str name = entity->getName();
                mFormats[name] = format;
                return format;
            }
            return NULL;
        }

        /// �õ����������ʽ������
        TYPE0* getFormat( CChar* name )
        {
            std::map<Str,TYPE0*>::iterator iter = mFormats.find(name);
            if ( iter!=mFormats.end() )
            {
                return iter->second;
            }
            return NULL;
        }

        /// �Ƴ����������ʽ������
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

        /// �õ����������ʽ�������б�
        void getFormatList( std::vector<ISceneObjectXmlFormat*>& formatList )
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

    private:
        Scene* mScene;
        Str mGroupName;
        std::map<Str,TYPE0*> mFormats;
        XMLElement*	mGroupElm;
    };


	/******************************************************************************/
	//�����������л�
	/******************************************************************************/
    class SceneXmlSerializer : public ISceneXmlSerializer
	{
	public:
		SceneXmlSerializer(Scene* scene);
		virtual ~SceneXmlSerializer();

		/// ���볡��Ŀ¼��subĿ¼�����Ͻӿڣ� �ͻ��˵��øýӿ�
		virtual Bool					loadAllContent( CChar* pathName, CChar* subPathName, Bool isCreateFormats = false );

        /// ���볡��Ŀ¼
        virtual Bool                    loadContent( CChar* pathName, Bool isCreateFormats = false )  ;
        /// ��������Ŀ¼
        virtual Bool                    saveContent( CChar* pathName ) ;
		/// ���г���					
		virtual Bool					clipContent(CChar* pathName, const RectF &clipRect);

		///create file
		//@{
        /// ��������Ŀ¼
        virtual Bool                    createSceneContent( TerrainDeclare* decl, Str path, Bool isCreateGameFile = false );
		/// ����һ���յĳ���
		virtual Bool					createSceneContent( );

		/// ������������
		virtual Bool					createTerrainFormat( TerrainDeclare* decl );
		/// �����������
		virtual Bool					loadTerrainFormat( Str path );

		/// �������ļ�
		virtual Bool					createTreeFormat();
		/// ��ȡ����ʽ�ļ�
		virtual Bool					loadTreeFormat();

		/// ���������ļ�
		virtual Bool					createSceneFormat();
		/// ��ȡ�����ļ�
		virtual Bool					loadSceneFormat();
		///@}

        ///load or save file
        //@{
		/// Ԥ�������ļ�
		virtual Bool					preloadSceneFile( CChar* fileName );
        /// ���볡���ļ�
        virtual Bool                    loadSceneFile( CChar* filename, Bool isCreateFormats = false );
        /// ���������ļ�
        virtual Bool                    saveSceneFile( CChar* filename ) ;

		/// Ԥ�����������ļ�
		virtual Bool					preloadSubSceneFile( CChar* fileName );
        /// ���븽�������ļ�
        virtual Bool                    loadSubSceneFile( CChar* filename, Bool isCreateFormats = false );
		/// ж�ظ��������ļ�
		virtual void					unloadSubScene();
		///��ʾ�����ظ�����������
		virtual void					showSubscene(bool show);
        /// �������������ļ�
        virtual Bool                    saveSubSceneFile( CChar* filename ) ;

        /// �����������
        virtual Bool                    loadTerrainData( CChar* filename, CChar* dataPath );
        /// ������������
        virtual Bool                    saveTerrainData( CChar* filename, CChar* dataPath ) ;
		/// ���е�������
		virtual Bool                    clipTerrainData( CChar* filename, CChar* dataPath, RectF clipRect ) ;


		/// Ԥ�������ļ�
		virtual Bool					preloadTreeFile( CChar* fileName );
        /// ����ֲ���ļ�
        virtual Bool					loadTreeFile( CChar* filename, Bool isCreateFormats = false );
        /// ����ֲ���ļ�
        virtual Bool					saveTreeFile( CChar* filename );

		/// ����켣�ļ�, Ŀǰ����ļ�ֻ�ܶ�ȡ���ܴ����ͱ���
		virtual Bool					loadTrackFile( CChar* pathName );

        //@}

        /// ж��
        void                            unLoad();

        virtual void                    clearIgnoreLoadGroup();
        virtual void                    addIgnoreLoadGroup( Str group );
        virtual Bool                    isIgnoreLoadGroup( Str group );

	private:

        std::map<Str,Str>   mIgnoreLoadGroup;

	public:

        /// �õ�������
        virtual Str                     getTypeName( SceneObjectTypes type ) ;
		
		/// ��õ�ǰ�ĳ����ļ���
		virtual Str						getScenePath() { return mSceneFilePath; };
        
    public:
        
        //@{ SceneObject

        /// ���ӳ��������ʽ������
        virtual ISceneObjectXmlFormat*  addSceneObjectFormat( ISceneObject* object, Bool isSub = false ) ;
        /// �õ����������ʽ������
        virtual ISceneObjectXmlFormat*  getSceneObjectFormat( CChar* name, SceneObjectTypes type, Bool isSub = false  ) ;
        /// �Ƴ�ʵ���ʽ������
        virtual void                    removeSceneObjectFormat( ISceneObjectXmlFormat* format, Bool isDestroyEntity=false, Bool isSub = false  ) ;
        /// �Ƴ�ʵ���ʽ������
        virtual void                    removeSceneObjectFormat( CChar* name, SceneObjectTypes type, Bool isDestroyEntity=false, Bool isSub = false ) ;

        /// �õ����������ʽ�������б�
        virtual void                    getSceneObjectXmlFormatList( SceneObjectTypes type, std::vector<ISceneObjectXmlFormat*>& formatList, Bool isSub = false  ) ;
   
        //@}
    
	private:
        
        /// ����·����
        Str     mSceneFilePath;
        /// ��������
        Scene*  mScene;

        //@{
            /////////////////////////////////////////////////////////////////////////////

            /// Xml�ĵ�����.
            tinyxml2::XMLDocument*	mSceneXmlDoc;
            /// Xml�ĵ�����.
            tinyxml2::XMLDocument*	mSubSceneXmlDoc;


            /////////////////////////////////////////////////////////////////////////////

            /// ����ʵ���ʽ������
            SceneObjectXmlFormatGroup<EntityXmlFormat,Entity>* mEntityFormatGroup;
            /// ������ʵ���ʽ������
            SceneObjectXmlFormatGroup<EntityXmlFormat,Entity>* mSubEntityFormatGroup;
			///// ������Ч��ʽ������
			//SceneObjectXmlFormatGroup<EffectEntityXmlFormat,EffectEntity>* mEffectEntityFormatGroup;
			/// ��������Ч��ʽ������
			//SceneObjectXmlFormatGroup<EffectEntityXmlFormat,EffectEntity>* mSubEffectEntityFormatGroup;
			
			/// CN_MODIFY
			/// �µ���Ч��ʽ������
			SceneObjectXmlFormatGroup<EffectComponentXmlFormat,EffectComponent>* mEffectComponentFormatGroup;
			/// �µ�����Ч��ʽ������
			SceneObjectXmlFormatGroup<EffectComponentXmlFormat,EffectComponent>* mSubEffectComponentFormatGroup;

            /////////////////////////////////////////////////////////////////////////////
            /// �����ʵ���ʽ������
            CameraXmlFormat* mCameraFormat;
            /// ����ʵ���ʽ������
            EnvironmentXmlFormat * mEnvironmentFormat;

			
        //@}

		//@{
			
			/// ����ʵ��켣����XML�ĵ�����
			tinyxml2::XMLDocument* mNodeTrackXmlDoc;

			/// ����ʵ��켣������ʽ������
			NodeTrackXmlFormat*	mNodeTrackXMLFormat;

		//@}


        //@{
            /// SpeedTree Xml�ĵ�����.
            tinyxml2::XMLDocument*	mTreeXmlDoc;
            /// ����Tree��ʽ������
            SceneObjectXmlFormatGroup<TreeXmlFormat,Tree>* mTreeFormatGroup;
			/// ����Grass��ʽ������
			SceneObjectXmlFormatGroup<GrassXmlFormat,Grass>* mGrassFormatGroup;
			/// ֲ��ϵͳ���ø�ʽ������
			SpeedTreeEnvXmlFormat* mSpeedTreeEnvFormat;
        //@}

        //@{
            /// Terrain�ĵ�����.
            tinyxml2::XMLDocument*	mTerrainXmlDoc;
            TerrainDeclare  mTerrDeclare;
        //@}
       
	};

    //����������������������������������������������������������������������������������������������������
    //����������������������������������������������������������������������������������������������������

    /******************************************************************************/
    //�������θ�ʽ������
    /******************************************************************************/
    class TerrainXmlFormat
    {
    public:

        ////////////////////////////////////////////////////////////////////////////////////////

		static void			fillTerrainChunkDeclare(XMLElement * elm, const TerrainDeclare& decl);
        /// LogicData -> Xml
        static void         fillTerrainChunkDeclare(XMLElement * elm, Scene* scene);
        /// Xml -> LogicData
        static void         applyTerrainChunkDeclare(XMLElement * elm, Scene* scene);
        
        ////////////////////////////////////////////////////////////////////////////////////////

        /// LogicData -> Xml
        static void         fillTerrainHeightDeclare(XMLElement * elm, Scene* scene);
        /// Xml -> LogicData
        static void         applyTerrainHeightDeclare(XMLElement * elm, Scene* scene);

        ////////////////////////////////////////////////////////////////////////////////////////

        /// LogicData -> Xml
        static void         fillTerrainRegionDeclare(XMLElement * elm, Scene* scene);
        /// Xml -> LogicData
        static void         applyTerrainRegionDeclare(XMLElement * elm, Scene* scene);

        ////////////////////////////////////////////////////////////////////////////////////////

        /// LogicData -> Xml
        static void         fillTerrainGlobleTextureLayerList(XMLElement * elm, Scene* scene);
        /// Xml -> LogicData
        static void         applyTerrainGlobleTextureList(XMLElement * elm, Scene* scene);

        ////////////////////////////////////////////////////////////////////////////////////////

        /// LogicData -> Xml
        static void         fillTerrainGlobleWaterGroupList(XMLElement * elm, Scene* scene);
        /// Xml -> LogicData
        static void         applyTerrainGlobleWaterGroupList(XMLElement * elm, Scene* scene);

    };

  
    //����������������������������������������������������������������������������������������������������
    //����������������������������������������������������������������������������������������������������


    /******************************************************************************/
    //�����������ʽ������
    /******************************************************************************/
    class CameraXmlFormat : public ISceneObjectXmlFormat
    {
        friend class SceneXmlSerializer;

    protected:

        CameraXmlFormat(Scene* scene, XMLElement * elm, Camera* cam);
        virtual ~CameraXmlFormat();

        /// ��䳡����������ݵ�Xml������
        virtual void            fill();
        /// Ӧ��Xml���ݵ������������
        virtual void            apply(Bool isCheckDirty=false);
        /// �õ����������
        virtual ISceneObject*   getSceneObject(){return mCamera;};
        /// Ӧ��Xml���ݵ���������������У�������������Ϊ���򴴽�
        static Camera*          apply(Scene* scene, XMLElement * elm, Camera* cam=NULL, Bool isCheckDirty=false);

    protected:

        ///ʵ�����
        Camera* mCamera;
        ///��������
        Scene* mScene;
    };


    /******************************************************************************/
    //������ʽ������
    /******************************************************************************/
    class EnvironmentXmlFormat : public ISceneObjectXmlFormat
    {
        friend class SceneXmlSerializer;

    protected:

        EnvironmentXmlFormat(Scene* scene, XMLElement * elm);
        virtual ~EnvironmentXmlFormat();

        /// �����������ݵ�Xml������
        virtual void            fill();
        /// Ӧ��Xml���ݵ�������
        virtual void            apply(Bool isCheckDirty=false);
        /// �õ���������
        virtual ISceneObject*   getSceneObject(){return NULL;};
        /// Ӧ��Xml���ݵ�����������
        static void             apply(Scene* scene, XMLElement * elm, Bool isCheckDirty=false);

    protected:

        ///��������
        Scene* mScene;
    };


	/******************************************************************************/
	//�����ڵ㶯����ʽ������
	/******************************************************************************/
	class NodeTrackXmlFormat : public ISceneObjectXmlFormat
	{
		friend class SceneXmlSerializer;

	protected:

		/// Ӧ��Xml���ݵ�����������
		static void             applyNodeTrackAnimations(Scene* scene, XMLElement * elm, Bool isCheckDirty=false);

		/// Ӧ��Xml���ݵ������ڵ㶯����
		static void				applyNodeTrackAnimation(Scene* scene, XMLElement * elm, Bool isCheckDirty=false);

	protected:

		///��������
		Scene*					mScene;
	};

	/******************************************************************************/
	//SpeedTree������ʽ������
	/******************************************************************************/
	class SpeedTreeEnvXmlFormat : public ISceneObjectXmlFormat
	{
		friend class SceneXmlSerializer;

	protected:

		SpeedTreeEnvXmlFormat(Scene* scene, XMLElement * elm);
		virtual ~SpeedTreeEnvXmlFormat();

		/// �����������ݵ�Xml������
		virtual void            fill();
		/// Ӧ��Xml���ݵ�������
		virtual void            apply(Bool isCheckDirty=false);

		/// �õ���������
		virtual ISceneObject*   getSceneObject(){return NULL;};

		/// Ӧ��Xml���ݵ�����������
		static void             apply(Scene* scene, XMLElement * elm, Bool isCheckDirty=false);

	protected:

		///��������
		Scene* mScene;
	};

    /******************************************************************************/
    //����ʵ���ʽ������
    /******************************************************************************/
    class EntityXmlFormat : public ISceneObjectXmlFormat
    {
        friend class SceneXmlSerializer;

    public:
        
        EntityXmlFormat(Scene* scene, XMLElement * elm, Entity* entity);
        virtual ~EntityXmlFormat();
        
        /// ��䳡���������ݵ�Xml������
        virtual void            fill();
        /// Ӧ��Xml���ݵ�����������
        virtual void            apply(Bool isCheckDirty=false);
		/// �õ���������
		virtual ISceneObject*   getSceneObject(){return mEntity;};
		/// Ӧ��Xml���ݵ�����ʵ������У����ʵ�����Ϊ���򴴽�
		static Entity*          apply(Scene* scene, XMLElement * elm, Entity* entity=NULL, Bool isCheckDirty=false);

		// Ӧ������
		static UInt applyIndex;
		static UInt applyTotal;

    protected:
        
        ///ʵ�����
        Entity* mEntity;
        ///��������
        Scene* mScene;
    };


    /******************************************************************************/
    //����Tree��ʽ������
    /******************************************************************************/
    class TreeXmlFormat : public ISceneObjectXmlFormat
    {
        friend class SceneXmlSerializer;

    public:

        TreeXmlFormat(Scene* scene, XMLElement * elm, Tree* tree);
        virtual ~TreeXmlFormat();

        /// ��䳡���������ݵ�Xml������
        virtual void            fill();
        /// Ӧ��Xml���ݵ�����������
        virtual void            apply(Bool isCheckDirty=false);
        /// �õ���������
        virtual ISceneObject*   getSceneObject();
        /// Ӧ��Xml���ݵ�����ʵ������У����ʵ�����Ϊ���򴴽�
        static Tree*            apply(Scene* scene, XMLElement * elm, Tree* tree=NULL, Bool isCheckDirty=false);

		// Ӧ������
		static UInt applyIndex;
		static UInt applyTotal;

    protected:

        ///ʵ�����
        Tree* mTree;
        ///��������
        Scene* mScene;

    };


	/******************************************************************************/
	//����Grass��ʽ������
	/******************************************************************************/
	class GrassXmlFormat : public ISceneObjectXmlFormat
	{
		friend class SceneXmlSerializer;

	public:

		GrassXmlFormat(Scene* scene, XMLElement * elm, Grass* tree);
		virtual ~GrassXmlFormat();

		/// ��䳡���������ݵ�Xml������
		virtual void            fill();
		/// Ӧ��Xml���ݵ�����������
		virtual void            apply(Bool isCheckDirty=false);
		/// �õ���������
		virtual ISceneObject*   getSceneObject();
		/// Ӧ��Xml���ݵ�����ʵ������У����ʵ�����Ϊ���򴴽�
		static Grass*            apply(Scene* scene, XMLElement * elm, Grass* tree=NULL, Bool isCheckDirty=false);

		// Ӧ������
		static UInt applyIndex;
		static UInt applyTotal;

	protected:

		///ʵ�����
		Grass* mGrass;
		///��������
		Scene* mScene;

	};


	///******************************************************************************/
	////������Ч��ʽ������
	///******************************************************************************/
	//class EffectEntityXmlFormat : public ISceneObjectXmlFormat
	//{
	//	friend class SceneXmlSerializer;

	//public:
	//	// CN_MODIFY
	//	EffectEntityXmlFormat(Scene* scene, XMLElement * elm, EffectComponent* tree);
	//	//EffectEntityXmlFormat(Scene* scene, XMLElement * elm, EffectEntity* tree);
	//	virtual ~EffectEntityXmlFormat();

	//	/// ��䳡���������ݵ�Xml������
	//	virtual void            fill();
	//	/// Ӧ��Xml���ݵ�����������
	//	virtual void            apply(Bool isCheckDirty=false);
	//	/// �õ���������
	//	virtual ISceneObject*   getSceneObject();
	//	/// Ӧ��Xml���ݵ�����ʵ������У����ʵ�����Ϊ���򴴽�
	//	static EffectComponent*    apply(Scene* scene, XMLElement * elm, EffectComponent* effectEntity=NULL, Bool isCheckDirty=false);

	//	// Ӧ������
	//	static UInt applyIndex;
	//	static UInt applyTotal;

	//protected:

	//	///ʵ�����
	//	// CN_MODIFY
	//	EffectComponent* mEffectEntity;
	//	//EffectEntity* mEffectEntity;
	//	///��������
	//	Scene* mScene;
	//};


	/******************************************************************************/
	//�µ���Ч��ʽ������ CN_MODIFY
	/******************************************************************************/
	class EffectComponentXmlFormat : public ISceneObjectXmlFormat
	{
		friend class SceneXmlSerializer;

	public:

		EffectComponentXmlFormat(Scene* scene, XMLElement * elm, EffectComponent* effectComponent);
		virtual ~EffectComponentXmlFormat();

		/// ��䳡���������ݵ�Xml������
		virtual void            fill();
		/// Ӧ��Xml���ݵ�����������
		virtual void            apply(Bool isCheckDirty=false);
		/// �õ���������
		virtual ISceneObject*   getSceneObject();
		/// Ӧ��Xml���ݵ�����ʵ������У����ʵ�����Ϊ���򴴽�
		static EffectComponent*    apply(Scene* scene, XMLElement * elm, EffectComponent* effectComponent=NULL, Bool isCheckDirty=false);

		// Ӧ������
		static UInt applyIndex;
		static UInt applyTotal;

	protected:

		///ʵ�����
		EffectComponent* mEffectComponent;
		///��������
		Scene* mScene;
	};

}

/******************************************************************************/

#endif
