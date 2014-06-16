/******************************************************************************/
#ifndef _MANUALMESHMANAGER_H_
#define _MANUALMESHMANAGER_H_
/******************************************************************************/

#include "EnginePreqs.h"

/******************************************************************************/

namespace MG
{


    /**
    -----------------------------------------------------------------------------
    #note:	�Զ��������״ģ������
    -----------------------------------------------------------------------------
    */
    struct TwistyBoxMeshData
    {
    public:
        TwistyBoxMeshData(void);
        ~TwistyBoxMeshData(void){};

    public:

        /*
        -----------------------------------------------------------------------------
        #note:    ���ն�������
        #note:    ��һ��9�����ն�����ɵ�һ��12�������������״ģ������

          0       1
          /--------/
         / |      /|
        4--------5 |
        |  | 	 | |
        |  2-----|-/3 
        6--------7/
        -----------------------------------------------------------------------------
        */
        static const size_t REFER_VERTEX_COUNT = 8;
        Ogre::Vector3       referVertexs[REFER_VERTEX_COUNT];

        /** ʵ��ģ�Ͷ����� */
        static const size_t REAL_VERTEX_COUNT = 36;
        /** ʵ��ģ�Ͷ������� */
        static const size_t realVertexIndexs[REAL_VERTEX_COUNT];

        /** Ĭ��ģ�Ͷ���UV */
        static const Ogre::Vector2 defaultTextureUV[REAL_VERTEX_COUNT];
        /** ʵ��ģ�Ͷ���UV */
        Ogre::Vector2 textureUV[REAL_VERTEX_COUNT];

        /** ʵ��ģ�Ͷ�������UV */
        static const size_t TRIANGLE_INDEX_COUNT = 36;

        /** ��ɫ */
        Ogre::ColourValue colour;
        /** ��ͼ�ļ� */
        String textureName;

        inline TwistyBoxMeshData& operator = ( const TwistyBoxMeshData& data )
        {
            colour        = data.colour;
            textureName   = data.textureName;

            for(int i=0; i<REFER_VERTEX_COUNT; i++ )
                referVertexs[i] = data.referVertexs[i];

            for(int j=0; j<REAL_VERTEX_COUNT; j++ )
                textureUV[j] = data.textureUV[j];

            return *this;
        }

        inline bool operator == ( const TwistyBoxMeshData& data ) const { return this == &data; }

    };

    /**
    -----------------------------------------------------------------------------
    #note:	�Զ��������״ģ������
    -----------------------------------------------------------------------------
    */
    struct QuadrangleMeshData
    {
    public:
        QuadrangleMeshData(void);
        ~QuadrangleMeshData(void){};
    public:

        /*
        -----------------------------------------------------------------------------
        #note:    ���ն�������
        #note:    ��һ��4�����ն�����ɵ�һ��2����������ı���ģ��

           0       1
          /--------/
         /        /
        2--------3 
        -----------------------------------------------------------------------------
        */
        static const size_t VERTEX_COUNT = 4;
        Ogre::Vector3 vertexs[VERTEX_COUNT];
        Ogre::Vector2 textureUV[VERTEX_COUNT];
        Ogre::Vector3 normal[VERTEX_COUNT];

        static const size_t TRIANGLE_INDEX_COUNT = 6;
        static const size_t indexs[TRIANGLE_INDEX_COUNT];

        /** ��ɫ */
        Ogre::ColourValue colour;
        /** ��ͼ�ļ� */
        String textureName;

        inline QuadrangleMeshData& operator = ( const QuadrangleMeshData& data )
        {
            colour        = data.colour;
            textureName   = data.textureName;

            for(int i=0; i<VERTEX_COUNT; i++ )
            {
                vertexs[i]   = data.vertexs[i];
                textureUV[i] = data.textureUV[i];
                normal[i]    = data.normal[i];
            }

            return *this;
        }

        inline bool operator == ( const QuadrangleMeshData& data ) const { return this == &data; }
    };

    /**
    -----------------------------------------------------------------------------
    #note:	�Զ����۵���״ģ������
    -----------------------------------------------------------------------------
    */
    struct PuckerMeshData
    {
    public:
        PuckerMeshData(void);
        ~PuckerMeshData(void){};
    public:

        /*
        -----------------------------------------------------------------------------
        #note:    ���ն�������
        #note:    ��һ��6�����ն�����ɵ�һ��4����������۵��ı���ģ��

           0       1
          /--------/
         /        /|
        2--------3 |
                 | |
                 | /5 
                 4/
        -----------------------------------------------------------------------------
        */
        static const size_t VERTEX_COUNT = 6;
        Ogre::Vector3 vertexs[VERTEX_COUNT];
        Ogre::Vector2 textureUV[VERTEX_COUNT];
        Ogre::Vector3 normal[VERTEX_COUNT];

        static const size_t TRIANGLE_INDEX_COUNT = 12;
        static const size_t indexs1[TRIANGLE_INDEX_COUNT];
        static const size_t indexs2[TRIANGLE_INDEX_COUNT];

        static const size_t LEVELPLANE_TRIANGLE_INDEX_COUNT = 6;
        static const size_t lpIndexs1[LEVELPLANE_TRIANGLE_INDEX_COUNT];
        static const size_t lpIndexs2[LEVELPLANE_TRIANGLE_INDEX_COUNT];

        /** ��ɫ */
        Ogre::ColourValue colour;
        /** ��ͼ�ļ� */
        String textureName;

        /** �������� */
        size_t triIndexType;

        inline PuckerMeshData& operator = ( const PuckerMeshData& data )
        {
            colour        = data.colour;
            textureName   = data.textureName;
            triIndexType  = data.triIndexType;

            for(int i=0; i<VERTEX_COUNT; i++ )
            {
                vertexs[i]   = data.vertexs[i];
                textureUV[i] = data.textureUV[i];
                normal[i]    = data.normal[i];
            }

            return *this;
        }
        
        inline bool operator == ( const PuckerMeshData& data ) const { return this == &data; }
    };

    /**
    -----------------------------------------------------------------------------
    #note:	������
    -----------------------------------------------------------------------------
    */
    struct Triangle3D
    {
        Vector3 t0;
        Vector3 t1; 
        Vector3 t2;
        Plane plane;
    };


    /**
    -----------------------------------------------------------------------------
    #note:	�Զ���ģ�����ݹ�����
    -----------------------------------------------------------------------------
    */
    class ManualMeshManager
    {
    public:
        ManualMeshManager(){};
        virtual ~ManualMeshManager(){};	
        SINGLETON_INSTANCE( ManualMeshManager )
    public:

        /*
        -----------------------------------------------------------------------------
        #note: ����TwistyBoxMeshData�ο���������
        #note: TwistyBoxMeshData
           0       1
          /--------/
         / |      /|
        4--------5 |
        |  | 	 | |
        |  2-----|-/3 
        6--------7/

        #

        #remark: ���� ��0,1,2,3���� �� ��4,5,6,7������ Ϊ startpos��endpos�߶η���

        ���� (2,3)���ĵ�Ϊstartpos �� (6,7)���ĵ�Ϊendpos

        #remark: 0,1,4,5�� �� 2,3,6,7��ľ��붨��Ϊ�߶�(Height)

        #remark: 0,2,4,6�� �� 1,5,7,3��ľ��붨��Ϊ���(Width)
        -----------------------------------------------------------------------------
        */
        void        rebuildTwistyBoxMeshData(TwistyBoxMeshData& data, const Vector3& startpos, const Vector3& endpos, Real height, Real width);

        /** ����TwistyBoxMeshData�ο��������� */
        void        rebuildTwistyBoxMeshData(TwistyBoxMeshData& data, const Vector3& startpos, const Vector3& endpos, 
            const Vector3& startWidthVector, const Vector3& endWidthVector, const Vector3& startheightVector, const Vector3& endheightVector);

        /** ����TwistyBoxMeshData��UV���� */
        void        rebuildTwistyBoxMeshTextureUV(TwistyBoxMeshData& data, Real widthScale, Real heightScale);
        /*
        -----------------------------------------------------------------------------
        #note:   ����QuadrangleMeshData����λ��
        #note:    
           0       1
          /--------/
         /        /
        2--------3 

        #remark: 0,1�߶����ĵ㶨��Ϊstartpos, 2,3�߶����ĵ㶨��Ϊendpos
        #remark: 0,1�߶η���Ϊstartvector, 2,3�߶η���Ϊendvector
        -----------------------------------------------------------------------------
        */
        void        rebuildQuadrangleMeshVertexs(QuadrangleMeshData& data, const Vector3& startpos, const Vector3& endpos, 
            const Vector3& startvector, const Vector3& endvector);

        /** ����QuadrangleMeshData��UV���� */
        void        rebuildQuadrangleMeshTextureUV(QuadrangleMeshData& data, Real widthScale);
        /*
        -----------------------------------------------------------------------------
        #note:   ����PuckerMeshData����λ��
        #note:    

           0       1
          /--------/
         /        /|
        2--------3 |
                 | |
                 | /5 
                 4/

        #remark: 0,1�߶����ĵ㶨��Ϊstartpos, 2,3�߶����ĵ㶨��Ϊendpos
        #remark: 0,1�߶η���ΪstartWidthVector, 2,3�߶η���ΪendWidthVector
        #remark: 5,1�߶η���ΪstartheightVector, 4,3�߶η���ΪendheightVector
        -----------------------------------------------------------------------------
        */
        void        rebuildPuckerMeshVertexs(PuckerMeshData& data, const Vector3& startpos, const Vector3& endpos, 
            const Vector3& startWidthVector, const Vector3& endWidthVector, const Vector3& startheightVector, const Vector3& endheightVector);

        /** ����PuckerMeshData��UV���� */
        void        rebuildPuckerMeshTextureUV(PuckerMeshData& data, Real widthScale, Real divScale);


        /*
        -----------------------------------------------------------------------------
        #note:   Ogreģ����ط���
        -----------------------------------------------------------------------------
        */
        /// �õ�ģ�͵�������
        void        getTriangle3DList( MeshPtr mesh, std::vector< Triangle3D >& list );

    };

}

/******************************************************************************/

#endif