/******************************************************************************/
#ifndef _TERRAINCIRCLEDECORATOR_H_
#define _TERRAINCIRCLEDECORATOR_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IWireframeManager.h"

/******************************************************************************/

namespace MG
{


    /**
    -----------------------------------------------------------------------------
    #note: ����Ȧ�߿����б�
    -----------------------------------------------------------------------------
    */
    class TerrainCircleLineList
    {
    public:
        TerrainCircleLineList();
        
        void    build( TerrainManager* terrainMgr , Vec3 center, Flt radius, Flt gap = 1 );
        std::vector<Vec3> mCircleLine;
        Flt  mBaseRadian;
        Flt  mLastBuildTime;
    };


    /**
    -----------------------------------------------------------------------------
    #note: ����Ȧ�߿���ʾ
    -----------------------------------------------------------------------------
    */
    class TerrainCircleDecorator : public ITerrainCircleDecorator
    {
    public:
        TerrainCircleDecorator(const String& name, Scene* scene);
        virtual ~TerrainCircleDecorator();

        /// ����
        virtual void        rebuild(void);

        /// ˢ��ģ�� 
        virtual void        refresh(void);

        /// ��������ģ�ʹ�ϸ
        virtual void        setBoldSize(Flt size);
        /// �õ�����ģ�ʹ�ϸ
        virtual Flt         getBoldSize(void);

        /// ������ɫ
        virtual void        setColour(Color colour);
        /// �õ���ɫ
        virtual Color       getColour();

        /// ���ÿɼ���
        virtual void        setVisible(Bool visible);
        /// �õ��ɼ���
        virtual Bool        getVisible();

        ////////////////////////////////////////////////////////////////

        /// ���ð뾶
        virtual void        setRadius(Flt radius) ;
        /// ���������
        virtual void        setCenter(Vec3 pos) ;

    protected:

        /// ��������ζ���
        void                createOgreManualObject();
        /// ���ٶ���ζ���
        void                destroyOgreManualObject();

        /// �������� 
        void                buildMaterial(void);
        /// �õ��������� 
        Str                 getMaterialName(void);

        /// ����Ogre���ֶ�����ģ�Ͷ���
        void                buildMesh(void);
        /// ����Ogre���ֶ�����ģ�Ͷ���
        void                refreshMesh(void);

        //////////////////////////////////////////////////////

    private:

        //  ��������
        Scene*                  mScene;
        /// ����ģ�ʹ�ϸ
        Flt                     mBoldSize;
        /// ��ɫ 
        ColourValue             mColour;
        /// ���ĵ�
        Vec3                    mCenter;
        /// �뾶
        Flt                     mRadius;

        //////////////////////////////////////////////////////

        /// Ogre���ֶ�����ģ�Ͷ���
        Ogre::ManualObject*     mOgreManualObject;
        /// �ڵ����
        MGSceneNode*            mSceneNode;
        /// Ogre���ʽӿ� 
        Ogre::MaterialPtr       mOgreMaterialPtr;                   

        ////////////////////////////////////////////////////////

        TerrainCircleLineList   mTerrainCircleLineList;
        Int                     mBuildPointCount;

        ////////////////////////////////////////////////////////
    };

}

/******************************************************************************/

#endif