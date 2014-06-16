/******************************************************************************/
#ifndef _OGREENTITYWRAPPER_H_
#define _OGREENTITYWRAPPER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "OgreEntity.h"
#include "IModelObject.h"
#include "MGSceneNode.h"
#include "MaterialManager.h"

/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //Ogre实体对象
    /******************************************************************************/
    class OgreEntityWrapper : public IModelObject
    {
        friend class Scene;

    public:
        OgreEntityWrapper(ISceneObject* sceneObject,CChar* entityName, ModelDeclaration* modelDeclaration, Scene* scene);
        OgreEntityWrapper(ISceneObject* sceneObject,CChar* entityName, CChar* groupName, CChar* modelName, Scene* scene);
        virtual ~OgreEntityWrapper();

    public:

        /// 更新
        virtual void                    update( Flt delta );

        /// 得到空间节点
        virtual MGSceneNode*            getSceneNode();

        /// 应用渲染配置
        virtual void                    applyRenderConfig();


        /////////////////////////////////////////////////////////////////////////////////////


        /// 得到骨骼的相对位置
        virtual Vec3                    getBonePosition(CChar* boneName);
        /// 得到骨骼的世界位置
        virtual Vec3                    getBoneWorldPosition(CChar* boneName);
		/// 得到骨骼的相对角位移
		virtual Qua						getBoneOrientation(CChar* boneName);
		/// 得到骨骼的世界角位移
		virtual Qua						getBoneWorldOrientation(CChar* boneName);

		////////////////////////////////////////////////////////////////////////////////////////////

		/// 通过一个值获取人物中心位置
		virtual Vec3					getCenterPosition(Flt center = 0.0f, Bool isLocal = true);

		////////////////////////////////////////////////////////////////////////////////////////////


        /// 得到高度
        virtual Flt                     getHeight();
        /// 得到宽度
        virtual Flt                     getWidth();


        /////////////////////////////////////////////////////////////////////////////////////

        /// 得到模型描述名
        virtual Str                     getModelDeclarationName() { return mModelDeclarationName;};

		/// 得到模型ID
		virtual U32						getModelDeclarationID() { return mModelDeclarationID; };

        /// 得到OgreEntity
        Ogre::Entity*                   getOgreEntity() { return mOgreEntity; };


        /////////////////////////////////////////////////////////////////////////////////////

		///	碰撞盒的size 
		virtual Vec3					getBoundingBoxSize();

		/// 寻路半径
		virtual Flt						getPatherRadius();

    public:

        // 设置阴影投射类型
        virtual void                    setShadowCastType(ShadowCasterType type);
        // 得到阴影投射类型
        virtual ShadowCasterType        getShadowCastType();

        // 设置是否接受动态阴影
        virtual void                    setDynamicShadowReceiveEnable(Bool enable);
        // 得到是否接受动态阴影
        virtual Bool                    getDynamicShadowReceiveEnable();

        // 设置是否接受静态阴影
        virtual void                    setStaticShadowReceiveEnable(Bool enable);
        // 得到是否接受静态阴影
        virtual Bool                    getStaticShadowReceiveEnable();

        /////////////////////////////////////////////////////////////////////////////////////

        // 设置是否能被反射
        virtual void                    setReflectEnable(Bool enable);
        // 得到是否能被反射
        virtual Bool                    getReflectEnable();

        // 设置是否能被折射
        virtual void                    setRefractEnable(Bool enable);
        // 得到是否能被折射
        virtual Bool                    getRefractEnable();

        /////////////////////////////////////////////////////////////////////////////////////

    public:

        // 得到动态参数对象
        MaterialDynamicParamsObject&    getMaterialDynamicParamsObject(){ return mMaterialDynamicParams; };

    public:
        
        /////////////////////////////////////////////////////////////////////////////////////

        /// 设置可见组
        virtual void                    applyVisibleFlag();

        /// 设置材质
        virtual void                    applyMaterial();

        /// 设置高亮
        virtual void                    setHightLight(Flt shine, Bool useDirty=true);
        /// 更新高亮
                void                    updateHightLight();
        /// 响应高亮
                void                    applyHightLight(Flt shine);

        /// 设置自发光
        virtual void                    setEmissive(Color color, Bool toAccessory = false);

		Color							getEmissive() { return Color(mEmissive.r, mEmissive.g, mEmissive.b, mEmissive.a); }

        /////////////////////////////////////////////////////////////////////////////////////

    public:
        /// 创建模型
        void                            createOgreEntity(ModelDeclaration* modelDecl,Bool isCreateNode,Bool isBacth);
        /// 创建模型
        void                            createOgreEntity(Str modelName, Bool isCreateNode,Bool isBacth);
        /// 销毁模型
        void                            destroyOgreEntity();
        /// 销毁模型备用数据
        void                            destroyOgreEntityBackupData();

        /////////////////////////////////////////////////////////////////////////////////////

    protected:
        
        //模型特效类型
        ModelEffectType                 mModelEffectType;
        // 名字
        Str                             mName;
        // 场景对象
        ISceneObject*                   mSceneObject;
        ///节点对象
        MGSceneNode*                    mSceneNode;
        /// Ogre实体对象
        Ogre::Entity*                   mOgreEntity;

        /// 所属场景对象
        Scene*                          mScene;
        /// 模型描述名
        Str                             mModelDeclarationName;
		U32								mModelDeclarationID;
		Flt								mPatherRadius;
        // 高光参数
        Bool                            mUseHightLightDirty;
        Bool                            mHightLightDirty;

        Flt                             mShiness;
        Ogre::ColourValue               mEmissive;

        // 材质描述
        MaterialDynamicParamsObject     mMaterialDynamicParams;


        // 资源组, 这个组名是给OGRE的材质管理器用的
        Str                             mResourceGroupName;
		// 材质组, 这个组名是MG的材质管理器用的
		Str								mMaterialMGGroupName;
        // 是否批量渲染
        Bool                            mIsBatch;


        // 阴影投射类型
        ShadowCasterType                mShadowCasterType;
        // 是否接受动态阴影
        Bool                            mDynamicShadowReceiveEnable;
        // 是否接受静态阴影
        Bool                            mStaticShadowReceiveEnable;
        // 是否能够被反射
        Bool                            mReflectEnable;
        // 是否能够被折射
        Bool                            mRefractEnable;
        // 材质改变标志
        Bool                            mMaterialChangeDirty;
    };

}

/******************************************************************************/

#endif
