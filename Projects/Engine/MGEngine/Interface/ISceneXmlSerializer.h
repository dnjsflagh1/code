/******************************************************************************/
#ifndef _ISCENEXMLSERIALIZER_H
#define _ISCENEXMLSERIALIZER_H
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //场景对象序列化接口
    /******************************************************************************/
    class ISceneXmlSerializer
    {
    public:

		/// 导入场景目录和sub目录的整合接口， 客户端调用该接口
		virtual Bool					loadAllContent( CChar* pathName, CChar* subPathName, Bool isCreateFormats = false ) = 0;

        /// 导入场景目录
        virtual Bool                    loadContent( CChar* pathName, Bool isCreateFormats = false ) = 0 ;
        /// 导出场景目录
        virtual Bool                    saveContent( CChar* pathName ) = 0 ;
		/// 裁切场景					
		virtual Bool					clipContent(CChar* pathName, const RectF &clipRect) = 0;

		///create file
		//@{
		/// 创建场景目录
		virtual Bool                    createSceneContent( TerrainDeclare* decl, Str path, Bool isCreateGameFile = false ) = 0;
		/// 创建一个空的场景
		virtual Bool					createSceneContent( ) = 0;

		/// 创建地形数据
		virtual Bool					createTerrainFormat( TerrainDeclare* decl ) = 0;
		/// 导入地形数据
		virtual Bool					loadTerrainFormat(  Str path ) = 0;

		/// 创建树文件
		virtual Bool					createTreeFormat() = 0;
		/// 读取数格式文件
		virtual Bool					loadTreeFormat() = 0;

		/// 创建场景文件
		virtual Bool					createSceneFormat() = 0;
		/// 读取场景文件
		virtual Bool					loadSceneFormat() = 0;
		///@}


        /// 导入场景文件
        virtual Bool                    loadSceneFile( CChar* filename, Bool isCreateFormats = false ) = 0 ;
        /// 导出场景文件
        virtual Bool                    saveSceneFile( CChar* filename ) = 0 ;

        /// 导入附属场景文件
        virtual Bool                    loadSubSceneFile( CChar* filename, Bool isCreateFormats = false ) = 0 ;
		/// 卸载附属场景文件
		virtual void					unloadSubScene() = 0;
		///显示或隐藏附属场景内容
		virtual void					showSubscene(bool show) = 0;
        /// 导出附属场景文件
        virtual Bool                    saveSubSceneFile( CChar* filename ) = 0 ;

		/// 导入植被文件
		virtual Bool					loadTreeFile( CChar* filename, Bool isCreateFormats = false ) = 0;
        /// 导出植被文件
        virtual Bool					saveTreeFile( CChar* filename ) = 0;

        /// 得到类型名
        virtual Str                     getTypeName( SceneObjectTypes type ) = 0 ;

        /// 增加场景对象格式化对象
        virtual ISceneObjectXmlFormat*  addSceneObjectFormat( ISceneObject* object, Bool isSub = false ) = 0 ;
        /// 得到场景对象格式化对象
        virtual ISceneObjectXmlFormat*  getSceneObjectFormat( CChar* name, SceneObjectTypes type, Bool isSub = false  ) = 0 ;
        /// 移除实体格式化对象
        virtual void                    removeSceneObjectFormat( ISceneObjectXmlFormat* format, Bool isDestroyEntity=false, Bool isSub = false  ) = 0 ;
        /// 移除实体格式化对象
        virtual void                    removeSceneObjectFormat( CChar* name, SceneObjectTypes type, Bool isDestroyEntity=false, Bool isSub = false  ) = 0 ;

        /// 得到场景对象格式化对象列表
        virtual void                    getSceneObjectXmlFormatList( SceneObjectTypes type, std::vector<ISceneObjectXmlFormat*>& formatList, Bool isSub = false  ) = 0;

		/// 卸载
		virtual void                    unLoad() = 0;
		/// 获得当前的场景文件名
		virtual Str						getScenePath() = 0;

        /// 设置忽略加载的组
        virtual void                    clearIgnoreLoadGroup() = 0;
        virtual void                    addIgnoreLoadGroup( Str group ) = 0;
    };

    /******************************************************************************/
    //场景格式化对象接口
    /******************************************************************************/
    class IXmlFormat
    {
    public:
        /// 填充场景对象数据到Xml数据中
        virtual void                    fill() = 0;
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
    //场景格式化对象接口
    /******************************************************************************/
    class ISceneObjectXmlFormat : public IXmlFormat
    {
    public://get or set
        /// 得到场景对象
        virtual ISceneObject*           getSceneObject() = 0;
    };

}

/******************************************************************************/
#endif
