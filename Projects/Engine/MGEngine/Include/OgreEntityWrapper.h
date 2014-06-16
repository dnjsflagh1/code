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
    //Ogreʵ�����
    /******************************************************************************/
    class OgreEntityWrapper : public IModelObject
    {
        friend class Scene;

    public:
        OgreEntityWrapper(ISceneObject* sceneObject,CChar* entityName, ModelDeclaration* modelDeclaration, Scene* scene);
        OgreEntityWrapper(ISceneObject* sceneObject,CChar* entityName, CChar* groupName, CChar* modelName, Scene* scene);
        virtual ~OgreEntityWrapper();

    public:

        /// ����
        virtual void                    update( Flt delta );

        /// �õ��ռ�ڵ�
        virtual MGSceneNode*            getSceneNode();

        /// Ӧ����Ⱦ����
        virtual void                    applyRenderConfig();


        /////////////////////////////////////////////////////////////////////////////////////


        /// �õ����������λ��
        virtual Vec3                    getBonePosition(CChar* boneName);
        /// �õ�����������λ��
        virtual Vec3                    getBoneWorldPosition(CChar* boneName);
		/// �õ���������Խ�λ��
		virtual Qua						getBoneOrientation(CChar* boneName);
		/// �õ������������λ��
		virtual Qua						getBoneWorldOrientation(CChar* boneName);

		////////////////////////////////////////////////////////////////////////////////////////////

		/// ͨ��һ��ֵ��ȡ��������λ��
		virtual Vec3					getCenterPosition(Flt center = 0.0f, Bool isLocal = true);

		////////////////////////////////////////////////////////////////////////////////////////////


        /// �õ��߶�
        virtual Flt                     getHeight();
        /// �õ����
        virtual Flt                     getWidth();


        /////////////////////////////////////////////////////////////////////////////////////

        /// �õ�ģ��������
        virtual Str                     getModelDeclarationName() { return mModelDeclarationName;};

		/// �õ�ģ��ID
		virtual U32						getModelDeclarationID() { return mModelDeclarationID; };

        /// �õ�OgreEntity
        Ogre::Entity*                   getOgreEntity() { return mOgreEntity; };


        /////////////////////////////////////////////////////////////////////////////////////

		///	��ײ�е�size 
		virtual Vec3					getBoundingBoxSize();

		/// Ѱ·�뾶
		virtual Flt						getPatherRadius();

    public:

        // ������ӰͶ������
        virtual void                    setShadowCastType(ShadowCasterType type);
        // �õ���ӰͶ������
        virtual ShadowCasterType        getShadowCastType();

        // �����Ƿ���ܶ�̬��Ӱ
        virtual void                    setDynamicShadowReceiveEnable(Bool enable);
        // �õ��Ƿ���ܶ�̬��Ӱ
        virtual Bool                    getDynamicShadowReceiveEnable();

        // �����Ƿ���ܾ�̬��Ӱ
        virtual void                    setStaticShadowReceiveEnable(Bool enable);
        // �õ��Ƿ���ܾ�̬��Ӱ
        virtual Bool                    getStaticShadowReceiveEnable();

        /////////////////////////////////////////////////////////////////////////////////////

        // �����Ƿ��ܱ�����
        virtual void                    setReflectEnable(Bool enable);
        // �õ��Ƿ��ܱ�����
        virtual Bool                    getReflectEnable();

        // �����Ƿ��ܱ�����
        virtual void                    setRefractEnable(Bool enable);
        // �õ��Ƿ��ܱ�����
        virtual Bool                    getRefractEnable();

        /////////////////////////////////////////////////////////////////////////////////////

    public:

        // �õ���̬��������
        MaterialDynamicParamsObject&    getMaterialDynamicParamsObject(){ return mMaterialDynamicParams; };

    public:
        
        /////////////////////////////////////////////////////////////////////////////////////

        /// ���ÿɼ���
        virtual void                    applyVisibleFlag();

        /// ���ò���
        virtual void                    applyMaterial();

        /// ���ø���
        virtual void                    setHightLight(Flt shine, Bool useDirty=true);
        /// ���¸���
                void                    updateHightLight();
        /// ��Ӧ����
                void                    applyHightLight(Flt shine);

        /// �����Է���
        virtual void                    setEmissive(Color color, Bool toAccessory = false);

		Color							getEmissive() { return Color(mEmissive.r, mEmissive.g, mEmissive.b, mEmissive.a); }

        /////////////////////////////////////////////////////////////////////////////////////

    public:
        /// ����ģ��
        void                            createOgreEntity(ModelDeclaration* modelDecl,Bool isCreateNode,Bool isBacth);
        /// ����ģ��
        void                            createOgreEntity(Str modelName, Bool isCreateNode,Bool isBacth);
        /// ����ģ��
        void                            destroyOgreEntity();
        /// ����ģ�ͱ�������
        void                            destroyOgreEntityBackupData();

        /////////////////////////////////////////////////////////////////////////////////////

    protected:
        
        //ģ����Ч����
        ModelEffectType                 mModelEffectType;
        // ����
        Str                             mName;
        // ��������
        ISceneObject*                   mSceneObject;
        ///�ڵ����
        MGSceneNode*                    mSceneNode;
        /// Ogreʵ�����
        Ogre::Entity*                   mOgreEntity;

        /// ������������
        Scene*                          mScene;
        /// ģ��������
        Str                             mModelDeclarationName;
		U32								mModelDeclarationID;
		Flt								mPatherRadius;
        // �߹����
        Bool                            mUseHightLightDirty;
        Bool                            mHightLightDirty;

        Flt                             mShiness;
        Ogre::ColourValue               mEmissive;

        // ��������
        MaterialDynamicParamsObject     mMaterialDynamicParams;


        // ��Դ��, ��������Ǹ�OGRE�Ĳ��ʹ������õ�
        Str                             mResourceGroupName;
		// ������, ���������MG�Ĳ��ʹ������õ�
		Str								mMaterialMGGroupName;
        // �Ƿ�������Ⱦ
        Bool                            mIsBatch;


        // ��ӰͶ������
        ShadowCasterType                mShadowCasterType;
        // �Ƿ���ܶ�̬��Ӱ
        Bool                            mDynamicShadowReceiveEnable;
        // �Ƿ���ܾ�̬��Ӱ
        Bool                            mStaticShadowReceiveEnable;
        // �Ƿ��ܹ�������
        Bool                            mReflectEnable;
        // �Ƿ��ܹ�������
        Bool                            mRefractEnable;
        // ���ʸı��־
        Bool                            mMaterialChangeDirty;
    };

}

/******************************************************************************/

#endif
