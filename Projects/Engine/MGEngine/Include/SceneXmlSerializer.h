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
    //场景地形格式化对象
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

        /// 加载场景对象格式化对象组
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

        /// 增加场景对象格式化对象
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

        /// 得到场景对象格式化对象
        TYPE0* getFormat( CChar* name )
        {
            std::map<Str,TYPE0*>::iterator iter = mFormats.find(name);
            if ( iter!=mFormats.end() )
            {
                return iter->second;
            }
            return NULL;
        }

        /// 移除场景对象格式化对象
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

        /// 得到场景对象格式化对象列表
        void getFormatList( std::vector<ISceneObjectXmlFormat*>& formatList )
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

    private:
        Scene* mScene;
        Str mGroupName;
        std::map<Str,TYPE0*> mFormats;
        XMLElement*	mGroupElm;
    };


	/******************************************************************************/
	//场景对象序列化
	/******************************************************************************/
    class SceneXmlSerializer : public ISceneXmlSerializer
	{
	public:
		SceneXmlSerializer(Scene* scene);
		virtual ~SceneXmlSerializer();

		/// 导入场景目录和sub目录的整合接口， 客户端调用该接口
		virtual Bool					loadAllContent( CChar* pathName, CChar* subPathName, Bool isCreateFormats = false );

        /// 导入场景目录
        virtual Bool                    loadContent( CChar* pathName, Bool isCreateFormats = false )  ;
        /// 导出场景目录
        virtual Bool                    saveContent( CChar* pathName ) ;
		/// 裁切场景					
		virtual Bool					clipContent(CChar* pathName, const RectF &clipRect);

		///create file
		//@{
        /// 创建场景目录
        virtual Bool                    createSceneContent( TerrainDeclare* decl, Str path, Bool isCreateGameFile = false );
		/// 创建一个空的场景
		virtual Bool					createSceneContent( );

		/// 创建地形数据
		virtual Bool					createTerrainFormat( TerrainDeclare* decl );
		/// 导入地形数据
		virtual Bool					loadTerrainFormat( Str path );

		/// 创建树文件
		virtual Bool					createTreeFormat();
		/// 读取数格式文件
		virtual Bool					loadTreeFormat();

		/// 创建场景文件
		virtual Bool					createSceneFormat();
		/// 读取场景文件
		virtual Bool					loadSceneFormat();
		///@}

        ///load or save file
        //@{
		/// 预读场景文件
		virtual Bool					preloadSceneFile( CChar* fileName );
        /// 导入场景文件
        virtual Bool                    loadSceneFile( CChar* filename, Bool isCreateFormats = false );
        /// 导出场景文件
        virtual Bool                    saveSceneFile( CChar* filename ) ;

		/// 预读附属场景文件
		virtual Bool					preloadSubSceneFile( CChar* fileName );
        /// 导入附属场景文件
        virtual Bool                    loadSubSceneFile( CChar* filename, Bool isCreateFormats = false );
		/// 卸载附属场景文件
		virtual void					unloadSubScene();
		///显示或隐藏附属场景内容
		virtual void					showSubscene(bool show);
        /// 导出附属场景文件
        virtual Bool                    saveSubSceneFile( CChar* filename ) ;

        /// 导入地形数据
        virtual Bool                    loadTerrainData( CChar* filename, CChar* dataPath );
        /// 导出地形数据
        virtual Bool                    saveTerrainData( CChar* filename, CChar* dataPath ) ;
		/// 裁切地形数据
		virtual Bool                    clipTerrainData( CChar* filename, CChar* dataPath, RectF clipRect ) ;


		/// 预读场景文件
		virtual Bool					preloadTreeFile( CChar* fileName );
        /// 导入植被文件
        virtual Bool					loadTreeFile( CChar* filename, Bool isCreateFormats = false );
        /// 导出植被文件
        virtual Bool					saveTreeFile( CChar* filename );

		/// 导入轨迹文件, 目前这个文件只能读取不能创建和保存
		virtual Bool					loadTrackFile( CChar* pathName );

        //@}

        /// 卸载
        void                            unLoad();

        virtual void                    clearIgnoreLoadGroup();
        virtual void                    addIgnoreLoadGroup( Str group );
        virtual Bool                    isIgnoreLoadGroup( Str group );

	private:

        std::map<Str,Str>   mIgnoreLoadGroup;

	public:

        /// 得到类型名
        virtual Str                     getTypeName( SceneObjectTypes type ) ;
		
		/// 获得当前的场景文件名
		virtual Str						getScenePath() { return mSceneFilePath; };
        
    public:
        
        //@{ SceneObject

        /// 增加场景对象格式化对象
        virtual ISceneObjectXmlFormat*  addSceneObjectFormat( ISceneObject* object, Bool isSub = false ) ;
        /// 得到场景对象格式化对象
        virtual ISceneObjectXmlFormat*  getSceneObjectFormat( CChar* name, SceneObjectTypes type, Bool isSub = false  ) ;
        /// 移除实体格式化对象
        virtual void                    removeSceneObjectFormat( ISceneObjectXmlFormat* format, Bool isDestroyEntity=false, Bool isSub = false  ) ;
        /// 移除实体格式化对象
        virtual void                    removeSceneObjectFormat( CChar* name, SceneObjectTypes type, Bool isDestroyEntity=false, Bool isSub = false ) ;

        /// 得到场景对象格式化对象列表
        virtual void                    getSceneObjectXmlFormatList( SceneObjectTypes type, std::vector<ISceneObjectXmlFormat*>& formatList, Bool isSub = false  ) ;
   
        //@}
    
	private:
        
        /// 场景路径名
        Str     mSceneFilePath;
        /// 场景对象
        Scene*  mScene;

        //@{
            /////////////////////////////////////////////////////////////////////////////

            /// Xml文档对象.
            tinyxml2::XMLDocument*	mSceneXmlDoc;
            /// Xml文档对象.
            tinyxml2::XMLDocument*	mSubSceneXmlDoc;


            /////////////////////////////////////////////////////////////////////////////

            /// 场景实体格式化对象
            SceneObjectXmlFormatGroup<EntityXmlFormat,Entity>* mEntityFormatGroup;
            /// 场景子实体格式化对象
            SceneObjectXmlFormatGroup<EntityXmlFormat,Entity>* mSubEntityFormatGroup;
			///// 场景特效格式化对象
			//SceneObjectXmlFormatGroup<EffectEntityXmlFormat,EffectEntity>* mEffectEntityFormatGroup;
			/// 场景特子效格式化对象
			//SceneObjectXmlFormatGroup<EffectEntityXmlFormat,EffectEntity>* mSubEffectEntityFormatGroup;
			
			/// CN_MODIFY
			/// 新的特效格式化对象
			SceneObjectXmlFormatGroup<EffectComponentXmlFormat,EffectComponent>* mEffectComponentFormatGroup;
			/// 新的特子效格式化对象
			SceneObjectXmlFormatGroup<EffectComponentXmlFormat,EffectComponent>* mSubEffectComponentFormatGroup;

            /////////////////////////////////////////////////////////////////////////////
            /// 摄像机实体格式化对象
            CameraXmlFormat* mCameraFormat;
            /// 环境实体格式化对象
            EnvironmentXmlFormat * mEnvironmentFormat;

			
        //@}

		//@{
			
			/// 场景实体轨迹动画XML文档对象
			tinyxml2::XMLDocument* mNodeTrackXmlDoc;

			/// 场景实体轨迹动画格式化对象
			NodeTrackXmlFormat*	mNodeTrackXMLFormat;

		//@}


        //@{
            /// SpeedTree Xml文档对象.
            tinyxml2::XMLDocument*	mTreeXmlDoc;
            /// 场景Tree格式化对象
            SceneObjectXmlFormatGroup<TreeXmlFormat,Tree>* mTreeFormatGroup;
			/// 场景Grass格式化对象
			SceneObjectXmlFormatGroup<GrassXmlFormat,Grass>* mGrassFormatGroup;
			/// 植被系统配置格式化对象
			SpeedTreeEnvXmlFormat* mSpeedTreeEnvFormat;
        //@}

        //@{
            /// Terrain文档对象.
            tinyxml2::XMLDocument*	mTerrainXmlDoc;
            TerrainDeclare  mTerrDeclare;
        //@}
       
	};

    //××××××××××××××××××××××××××××××××××××××××××××××××××
    //××××××××××××××××××××××××××××××××××××××××××××××××××

    /******************************************************************************/
    //场景地形格式化对象
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

  
    //××××××××××××××××××××××××××××××××××××××××××××××××××
    //××××××××××××××××××××××××××××××××××××××××××××××××××


    /******************************************************************************/
    //场景摄像机格式化对象
    /******************************************************************************/
    class CameraXmlFormat : public ISceneObjectXmlFormat
    {
        friend class SceneXmlSerializer;

    protected:

        CameraXmlFormat(Scene* scene, XMLElement * elm, Camera* cam);
        virtual ~CameraXmlFormat();

        /// 填充场景摄像机数据到Xml数据中
        virtual void            fill();
        /// 应用Xml数据到场景摄像机中
        virtual void            apply(Bool isCheckDirty=false);
        /// 得到场景摄像机
        virtual ISceneObject*   getSceneObject(){return mCamera;};
        /// 应用Xml数据到场景摄像机对象中，如果摄像机对象为空则创建
        static Camera*          apply(Scene* scene, XMLElement * elm, Camera* cam=NULL, Bool isCheckDirty=false);

    protected:

        ///实体对象
        Camera* mCamera;
        ///场景对象
        Scene* mScene;
    };


    /******************************************************************************/
    //环境格式化对象
    /******************************************************************************/
    class EnvironmentXmlFormat : public ISceneObjectXmlFormat
    {
        friend class SceneXmlSerializer;

    protected:

        EnvironmentXmlFormat(Scene* scene, XMLElement * elm);
        virtual ~EnvironmentXmlFormat();

        /// 场景场景数据到Xml数据中
        virtual void            fill();
        /// 应用Xml数据到场景中
        virtual void            apply(Bool isCheckDirty=false);
        /// 得到场景对象
        virtual ISceneObject*   getSceneObject(){return NULL;};
        /// 应用Xml数据到场景对象中
        static void             apply(Scene* scene, XMLElement * elm, Bool isCheckDirty=false);

    protected:

        ///场景对象
        Scene* mScene;
    };


	/******************************************************************************/
	//场景节点动画格式化对象
	/******************************************************************************/
	class NodeTrackXmlFormat : public ISceneObjectXmlFormat
	{
		friend class SceneXmlSerializer;

	protected:

		/// 应用Xml数据到场景对象中
		static void             applyNodeTrackAnimations(Scene* scene, XMLElement * elm, Bool isCheckDirty=false);

		/// 应用Xml数据到场景节点动画中
		static void				applyNodeTrackAnimation(Scene* scene, XMLElement * elm, Bool isCheckDirty=false);

	protected:

		///场景对象
		Scene*					mScene;
	};

	/******************************************************************************/
	//SpeedTree环境格式化对象
	/******************************************************************************/
	class SpeedTreeEnvXmlFormat : public ISceneObjectXmlFormat
	{
		friend class SceneXmlSerializer;

	protected:

		SpeedTreeEnvXmlFormat(Scene* scene, XMLElement * elm);
		virtual ~SpeedTreeEnvXmlFormat();

		/// 场景场景数据到Xml数据中
		virtual void            fill();
		/// 应用Xml数据到场景中
		virtual void            apply(Bool isCheckDirty=false);

		/// 得到场景对象
		virtual ISceneObject*   getSceneObject(){return NULL;};

		/// 应用Xml数据到场景对象中
		static void             apply(Scene* scene, XMLElement * elm, Bool isCheckDirty=false);

	protected:

		///场景对象
		Scene* mScene;
	};

    /******************************************************************************/
    //场景实体格式化对象
    /******************************************************************************/
    class EntityXmlFormat : public ISceneObjectXmlFormat
    {
        friend class SceneXmlSerializer;

    public:
        
        EntityXmlFormat(Scene* scene, XMLElement * elm, Entity* entity);
        virtual ~EntityXmlFormat();
        
        /// 填充场景对象数据到Xml数据中
        virtual void            fill();
        /// 应用Xml数据到场景对象中
        virtual void            apply(Bool isCheckDirty=false);
		/// 得到场景对象
		virtual ISceneObject*   getSceneObject(){return mEntity;};
		/// 应用Xml数据到场景实体对象中，如果实体对象为空则创建
		static Entity*          apply(Scene* scene, XMLElement * elm, Entity* entity=NULL, Bool isCheckDirty=false);

		// 应用索引
		static UInt applyIndex;
		static UInt applyTotal;

    protected:
        
        ///实体对象
        Entity* mEntity;
        ///场景对象
        Scene* mScene;
    };


    /******************************************************************************/
    //场景Tree格式化对象
    /******************************************************************************/
    class TreeXmlFormat : public ISceneObjectXmlFormat
    {
        friend class SceneXmlSerializer;

    public:

        TreeXmlFormat(Scene* scene, XMLElement * elm, Tree* tree);
        virtual ~TreeXmlFormat();

        /// 填充场景对象数据到Xml数据中
        virtual void            fill();
        /// 应用Xml数据到场景对象中
        virtual void            apply(Bool isCheckDirty=false);
        /// 得到场景对象
        virtual ISceneObject*   getSceneObject();
        /// 应用Xml数据到场景实体对象中，如果实体对象为空则创建
        static Tree*            apply(Scene* scene, XMLElement * elm, Tree* tree=NULL, Bool isCheckDirty=false);

		// 应用索引
		static UInt applyIndex;
		static UInt applyTotal;

    protected:

        ///实体对象
        Tree* mTree;
        ///场景对象
        Scene* mScene;

    };


	/******************************************************************************/
	//场景Grass格式化对象
	/******************************************************************************/
	class GrassXmlFormat : public ISceneObjectXmlFormat
	{
		friend class SceneXmlSerializer;

	public:

		GrassXmlFormat(Scene* scene, XMLElement * elm, Grass* tree);
		virtual ~GrassXmlFormat();

		/// 填充场景对象数据到Xml数据中
		virtual void            fill();
		/// 应用Xml数据到场景对象中
		virtual void            apply(Bool isCheckDirty=false);
		/// 得到场景对象
		virtual ISceneObject*   getSceneObject();
		/// 应用Xml数据到场景实体对象中，如果实体对象为空则创建
		static Grass*            apply(Scene* scene, XMLElement * elm, Grass* tree=NULL, Bool isCheckDirty=false);

		// 应用索引
		static UInt applyIndex;
		static UInt applyTotal;

	protected:

		///实体对象
		Grass* mGrass;
		///场景对象
		Scene* mScene;

	};


	///******************************************************************************/
	////场景特效格式化对象
	///******************************************************************************/
	//class EffectEntityXmlFormat : public ISceneObjectXmlFormat
	//{
	//	friend class SceneXmlSerializer;

	//public:
	//	// CN_MODIFY
	//	EffectEntityXmlFormat(Scene* scene, XMLElement * elm, EffectComponent* tree);
	//	//EffectEntityXmlFormat(Scene* scene, XMLElement * elm, EffectEntity* tree);
	//	virtual ~EffectEntityXmlFormat();

	//	/// 填充场景对象数据到Xml数据中
	//	virtual void            fill();
	//	/// 应用Xml数据到场景对象中
	//	virtual void            apply(Bool isCheckDirty=false);
	//	/// 得到场景对象
	//	virtual ISceneObject*   getSceneObject();
	//	/// 应用Xml数据到场景实体对象中，如果实体对象为空则创建
	//	static EffectComponent*    apply(Scene* scene, XMLElement * elm, EffectComponent* effectEntity=NULL, Bool isCheckDirty=false);

	//	// 应用索引
	//	static UInt applyIndex;
	//	static UInt applyTotal;

	//protected:

	//	///实体对象
	//	// CN_MODIFY
	//	EffectComponent* mEffectEntity;
	//	//EffectEntity* mEffectEntity;
	//	///场景对象
	//	Scene* mScene;
	//};


	/******************************************************************************/
	//新的特效格式化对象 CN_MODIFY
	/******************************************************************************/
	class EffectComponentXmlFormat : public ISceneObjectXmlFormat
	{
		friend class SceneXmlSerializer;

	public:

		EffectComponentXmlFormat(Scene* scene, XMLElement * elm, EffectComponent* effectComponent);
		virtual ~EffectComponentXmlFormat();

		/// 填充场景对象数据到Xml数据中
		virtual void            fill();
		/// 应用Xml数据到场景对象中
		virtual void            apply(Bool isCheckDirty=false);
		/// 得到场景对象
		virtual ISceneObject*   getSceneObject();
		/// 应用Xml数据到场景实体对象中，如果实体对象为空则创建
		static EffectComponent*    apply(Scene* scene, XMLElement * elm, EffectComponent* effectComponent=NULL, Bool isCheckDirty=false);

		// 应用索引
		static UInt applyIndex;
		static UInt applyTotal;

	protected:

		///实体对象
		EffectComponent* mEffectComponent;
		///场景对象
		Scene* mScene;
	};

}

/******************************************************************************/

#endif
