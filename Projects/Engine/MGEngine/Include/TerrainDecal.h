/******************************************************************************/
#ifndef _TERRAINDECAL_H
#define _TERRAINDECAL_H
/******************************************************************************/

#include "EnginePreqs.h"
#include "IDecal.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    /**���ε�����
    */
    /******************************************************************************/
    class TerrainDecal : public IDecal
    {
    public:
        TerrainDecal(Scene* scene, TerrainDecalSet* set);
        virtual ~TerrainDecal();

        /// ����λ��
        virtual void        setPosition(Vec3& pos);
        /// ����λ��
        virtual Vec3&       getPosition();
		/// ���÷���
		virtual void		setNormal(Vec3& normal);
		/// �õ�����
		virtual Vec3&		getNormal();
        /// ���ÿɼ���
        virtual void        setVisible(Bool visible);
        /// ���ÿɼ���
        virtual Bool        getVisible();
		/// �����������
		virtual IDecalType	getType(); 
		/// ���ô�С
				void        setSize(int size);
		/// �õ���С
				int         getSize();
        //���øı��־λ
                void        setChangeDirty();
        //�õ��ı��־λ
                Bool        getChangeDirty();
        //��ոı��־λ
                void        clearChangeDirty();
    
        //����ManualObject
                void        buildVertex(Ogre::ManualObject* manualObject);
                void        buildIndex(Ogre::ManualObject* manualObject,UInt index);

        //�õ�ƽ��߶�
                Flt         getPlaneHeight(Vec3& pos, Plane& plane, Flt defaultHeight);
    private:

                void        buildVertex1(Ogre::ManualObject* manualObject);
                void        buildVertex2(Ogre::ManualObject* manualObject);

                void        buildIndex1(Ogre::ManualObject* manualObject,UInt index);
                void        buildIndex2(Ogre::ManualObject* manualObject,UInt index);

    private:
        
        Scene*              mScene;
        Bool                mDirty;
        TerrainDecalSet*    mTerrainDecalSet;
        Flt                 mSize;
        Flt                 mHalfSize;
        Vec3                mPos;
        Bool                mVisible;

        Vec3                mBuildVertexPos[9];
        Vec2                mBuildVertexUV[9];
    };


    /******************************************************************************/
    /**���ε���������
    */
    /******************************************************************************/
    class TerrainDecalSet : public IDecalSet
    {
    public:
        TerrainDecalSet(CChar* name, CChar* texFileName, UInt num, Scene* scene);
        virtual ~TerrainDecalSet();

        /// �õ������ӿ�
        virtual TerrainDecal*           getDecal(UInt index);
        /// �õ���������
        virtual UInt                    getDecalNum();
		/// ���ô�С
		virtual void					setSize(int size);
		/// ��ȡ��С
		virtual int						getSize();
		/// ����
		virtual void                    update( Flt delta );

		virtual void					preRendering();

		virtual void					postRendering();
    protected:
        
        /// ����ģ��
                void                    createOgreManualObject();
        /// ����ģ��
                void                    destroyOgreManualObject();

        /// ��������
                void                    buildMaterial();
        /// ���������
                void                    buildMesh();

        /// ���¶����
                void                    updateMesh();

    protected:

        /// ������������
                void                    createTerrainDecals();
        /// ������������
                void                    destroyTerrainDecals();

    private:

        Scene*      mScene;

        Str         mName;
        Str         mTexFileName;
        UInt        mDecalNum;

        ///�ڵ����
        MGSceneNode*        mSceneNode;

        /// Ogre���ʽӿ�
        Ogre::MaterialPtr   mOgreMaterialPtr;
        /// Ogre��λ����ʾ�ڵ����
        Ogre::SceneNode*    mOgreDisplaySceneNode;
        /// Ogre���ֶ�����ģ�Ͷ���
        Ogre::ManualObject* mOgreManualObject;

        /// ��������
        std::vector<TerrainDecal*> mTerrainDecals;
    };


}


/******************************************************************************/

#endif