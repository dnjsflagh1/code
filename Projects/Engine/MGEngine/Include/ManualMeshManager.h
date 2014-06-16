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
    #note:	自定义盒子形状模型数据
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
        #note:    参照顶点数组
        #note:    由一组9个参照顶点组成的一共12个三角面盒子形状模型数据

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

        /** 实际模型顶点数 */
        static const size_t REAL_VERTEX_COUNT = 36;
        /** 实际模型顶点数组 */
        static const size_t realVertexIndexs[REAL_VERTEX_COUNT];

        /** 默认模型顶点UV */
        static const Ogre::Vector2 defaultTextureUV[REAL_VERTEX_COUNT];
        /** 实际模型顶点UV */
        Ogre::Vector2 textureUV[REAL_VERTEX_COUNT];

        /** 实际模型顶点索引UV */
        static const size_t TRIANGLE_INDEX_COUNT = 36;

        /** 颜色 */
        Ogre::ColourValue colour;
        /** 贴图文件 */
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
    #note:	自定义盒子形状模型数据
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
        #note:    参照顶点数组
        #note:    由一组4个参照顶点组成的一共2个三角面的四边形模型

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

        /** 颜色 */
        Ogre::ColourValue colour;
        /** 贴图文件 */
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
    #note:	自定义折叠形状模型数据
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
        #note:    参照顶点数组
        #note:    由一组6个参照顶点组成的一共4个三角面的折叠四边形模型

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

        /** 颜色 */
        Ogre::ColourValue colour;
        /** 贴图文件 */
        String textureName;

        /** 索引类型 */
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
    #note:	三角面
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
    #note:	自定义模型数据管理器
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
        #note: 设置TwistyBoxMeshData参考顶点数据
        #note: TwistyBoxMeshData
           0       1
          /--------/
         / |      /|
        4--------5 |
        |  | 	 | |
        |  2-----|-/3 
        6--------7/

        #

        #remark: 定义 （0,1,2,3）面 到 （4,5,6,7）方向 为 startpos到endpos线段方向

        定义 (2,3)中心点为startpos ， (6,7)中心点为endpos

        #remark: 0,1,4,5面 与 2,3,6,7面的距离定义为高度(Height)

        #remark: 0,2,4,6面 与 1,5,7,3面的距离定义为宽度(Width)
        -----------------------------------------------------------------------------
        */
        void        rebuildTwistyBoxMeshData(TwistyBoxMeshData& data, const Vector3& startpos, const Vector3& endpos, Real height, Real width);

        /** 设置TwistyBoxMeshData参考顶点数据 */
        void        rebuildTwistyBoxMeshData(TwistyBoxMeshData& data, const Vector3& startpos, const Vector3& endpos, 
            const Vector3& startWidthVector, const Vector3& endWidthVector, const Vector3& startheightVector, const Vector3& endheightVector);

        /** 设置TwistyBoxMeshData，UV坐标 */
        void        rebuildTwistyBoxMeshTextureUV(TwistyBoxMeshData& data, Real widthScale, Real heightScale);
        /*
        -----------------------------------------------------------------------------
        #note:   设置QuadrangleMeshData顶点位置
        #note:    
           0       1
          /--------/
         /        /
        2--------3 

        #remark: 0,1线段中心点定义为startpos, 2,3线段中心点定义为endpos
        #remark: 0,1线段方向为startvector, 2,3线段方向为endvector
        -----------------------------------------------------------------------------
        */
        void        rebuildQuadrangleMeshVertexs(QuadrangleMeshData& data, const Vector3& startpos, const Vector3& endpos, 
            const Vector3& startvector, const Vector3& endvector);

        /** 设置QuadrangleMeshData，UV坐标 */
        void        rebuildQuadrangleMeshTextureUV(QuadrangleMeshData& data, Real widthScale);
        /*
        -----------------------------------------------------------------------------
        #note:   设置PuckerMeshData顶点位置
        #note:    

           0       1
          /--------/
         /        /|
        2--------3 |
                 | |
                 | /5 
                 4/

        #remark: 0,1线段中心点定义为startpos, 2,3线段中心点定义为endpos
        #remark: 0,1线段方向为startWidthVector, 2,3线段方向为endWidthVector
        #remark: 5,1线段方向为startheightVector, 4,3线段方向为endheightVector
        -----------------------------------------------------------------------------
        */
        void        rebuildPuckerMeshVertexs(PuckerMeshData& data, const Vector3& startpos, const Vector3& endpos, 
            const Vector3& startWidthVector, const Vector3& endWidthVector, const Vector3& startheightVector, const Vector3& endheightVector);

        /** 设置PuckerMeshData，UV坐标 */
        void        rebuildPuckerMeshTextureUV(PuckerMeshData& data, Real widthScale, Real divScale);


        /*
        -----------------------------------------------------------------------------
        #note:   Ogre模型相关方法
        -----------------------------------------------------------------------------
        */
        /// 得到模型的三角面
        void        getTriangle3DList( MeshPtr mesh, std::vector< Triangle3D >& list );

    };

}

/******************************************************************************/

#endif