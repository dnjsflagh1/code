/******************************************************************************/
#ifndef _TERRAINGRIDSDECORATOR_H_
#define _TERRAINGRIDSDECORATOR_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IWireframeManager.h"

/******************************************************************************/

namespace MG
{

    
    /**
    -----------------------------------------------------------------------------
    #note: ���������߿����б�
    -----------------------------------------------------------------------------
    */
    class TerrainChunkGridsLineList
    {
    public:
        TerrainChunkGridsLineList();

        void    build( TerrainManager* terrainMgr );
        std::vector<Vec3> mLinePointList;
    };


    /**
    -----------------------------------------------------------------------------
    #note: ���������߼��߿����б�
    -----------------------------------------------------------------------------
    */
    class TerrainLogicGridsLineList
    {
    public:
        TerrainLogicGridsLineList();

        void    build( TerrainManager* terrainMgr );
        std::vector<Vec3> mLinePointList;
    };

    /**
    -----------------------------------------------------------------------------
    #note: ���������߿����б�
    -----------------------------------------------------------------------------
    */
    class TerrainTileGridsLineList
    {
    public:
        TerrainTileGridsLineList();

        void    build( TerrainManager* terrainMgr );
        std::vector<Vec3> mLinePointList;
    };


    /**
    -----------------------------------------------------------------------------
    #note: ���������߿���ʾ
    -----------------------------------------------------------------------------
    */
    class TerrainGridsDecorator : public ITerrainGridsDecorator
    {
    public:
        TerrainGridsDecorator(const String& name, Scene* scene);
        virtual ~TerrainGridsDecorator();

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

        /// ������ɫ
        virtual void        setChunkColour(Color colour);
        /// ������ɫ
        virtual void        setTileColour(Color colour);

        /// ���ÿɼ���
        virtual void        setVisible(Bool visible);
        /// �õ��ɼ���
        virtual Bool        getVisible();


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
        Scene*                      mScene;
        /// ����ģ�ʹ�ϸ
        Flt                         mBoldSize;

        /// ��ɫ 
        ColourValue                 mChunkColour;
        /// ��ɫ 
        ColourValue                 mTileColour;
        /// ��ɫ 
        ColourValue                 mLogicColour;

        //////////////////////////////////////////////////////

        /// Ogre���ֶ�����ģ�Ͷ���
        Ogre::ManualObject*         mOgreManualObject;
        /// �ڵ����
        MGSceneNode*                mSceneNode;
        /// Ogre���ʽӿ� 
        Ogre::MaterialPtr           mOgreMaterialPtr;                   

        ////////////////////////////////////////////////////////

        TerrainChunkGridsLineList   mTerrainChunkGridsLineList;
        Int                         mTerrainChunkGridsLineBuildPointCount;

        ////////////////////////////////////////////////////////

        TerrainTileGridsLineList    mTerrainTileGridsLineList;
        Int                         mTerrainTileGridsLineBuildPointCount;

        ////////////////////////////////////////////////////////

        TerrainLogicGridsLineList   mTerrainLogicGridsLineList;
        Int                         mTerrainLogicGridsLineBuildPointCount;

    };

}

/******************************************************************************/

#endif