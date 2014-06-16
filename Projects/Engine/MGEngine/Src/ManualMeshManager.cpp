/******************************************************************************/
#include "stdafx.h"
#include "Scene.h"
#include "MGSceneNode.h"
#include "EngineMain.h"
#include "ManualMeshManager.h"
#include "MGEngineUtility.h"
/******************************************************************************/

namespace MG
{
    /*
    -----------------------------------------------------------------------------
    Class TwistyBoxMeshData
    -----------------------------------------------------------------------------
    */
    //   0       1
    //  /--------/
    // / |      /|
    //4--------5 |
    //|  | 	 | |
    //|  2-----|-/3 
    //6--------7/

    const Vector2 TwistyBoxMeshData::defaultTextureUV[TwistyBoxMeshData::REAL_VERTEX_COUNT] = {
        Vector2(0,0.75),Vector2(0.25,0.75),Vector2(0,1),   // 0,1,2,
        Vector2(0.25,0.75),Vector2(0.25,1),Vector2(0,1),   // 1,3,2,
        Vector2(0.25,0.75),Vector2(0,1),Vector2(0,0.75),   // 5,6,4,
        Vector2(0.25,0.75),Vector2(0.25,1),Vector2(0,1),   // 5,7,6,

        Vector2(0,0.25),Vector2(0,0.5),Vector2(1,0.5),	   //1,3,7,
        Vector2(0,0.25),Vector2(1,0.5),Vector2(1,0.25),    //1,7,5,
        Vector2(1,0.25),Vector2(0,0.25),Vector2(1,0.5),	   //4,0,6,
        Vector2(0,0.25),Vector2(0,0.5),Vector2(1,0.5),	   //0,2,6,

        Vector2(1,0.25),Vector2(0,0.25),Vector2(0,0),	   //4,0,1,
        Vector2(1,0.25),Vector2(0,0),Vector2(1,0),		   //4,1,5,
        Vector2(0,0.25),Vector2(0,0),Vector2(1,0.25),		//2,3,6,	
        Vector2(0,0),Vector2(1,0),Vector2(1,0.25),		    //3,7,6						
    };

    //-----------------------------------------------------------------------
    const size_t TwistyBoxMeshData::realVertexIndexs[TwistyBoxMeshData::REAL_VERTEX_COUNT] = {
        0,1,2,
        1,3,2,
        5,6,4,
        5,7,6,

        1,3,7,
        1,7,5,
        4,0,6,
        0,2,6,

        4,0,1,
        4,1,5,
        2,3,6,
        3,7,6
    };
    //-----------------------------------------------------------------------
    TwistyBoxMeshData::TwistyBoxMeshData()
    {
        colour = ColourValue::Green;
        textureName = "";

        for(int i=0; i<REFER_VERTEX_COUNT; i++ )
            referVertexs[i] = Vector3(0,0,0);

        for(int i=0; i<REAL_VERTEX_COUNT; i++ )
            textureUV[i] = defaultTextureUV[i];
    }

    /*
    -----------------------------------------------------------------------------
    #note:	QuadrangleMeshData
    -----------------------------------------------------------------------------
    */

    //-----------------------------------------------------------------------
    const size_t QuadrangleMeshData::indexs[QuadrangleMeshData::TRIANGLE_INDEX_COUNT]= {
        0,2,1,
        1,2,3,
    };

    //-----------------------------------------------------------------------
    QuadrangleMeshData::QuadrangleMeshData()
    {
        colour        = ColourValue::Blue;
        textureName   = "";

        for(int i=0; i<QuadrangleMeshData::VERTEX_COUNT; i++ )
        {
            vertexs[i]   = Vector3(0,0,0);
            normal[i]    = Vector3(0,1,0);
        }

        textureUV[0] = Vector2(0,0);
        textureUV[1] = Vector2(1,0);
        textureUV[2] = Vector2(0,1);
        textureUV[3] = Vector2(1,1);
    }

    /*
    -----------------------------------------------------------------------------
    #note:	PuckerMeshData
    -----------------------------------------------------------------------------
    */

    //-----------------------------------------------------------------------
    const size_t PuckerMeshData::indexs1[PuckerMeshData::TRIANGLE_INDEX_COUNT]= {
        1,2,0,
        1,3,2,
        1,4,3,
        1,5,4,
    };

    //-----------------------------------------------------------------------
    const size_t PuckerMeshData::indexs2[PuckerMeshData::TRIANGLE_INDEX_COUNT]= {
        1,0,2,
        1,2,3,
        1,3,4,
        1,4,5,
    };

    //-----------------------------------------------------------------------
    const size_t PuckerMeshData::lpIndexs1[PuckerMeshData::LEVELPLANE_TRIANGLE_INDEX_COUNT]= {
        1,2,0,
        1,3,2,
    };

    //-----------------------------------------------------------------------
    const size_t PuckerMeshData::lpIndexs2[PuckerMeshData::LEVELPLANE_TRIANGLE_INDEX_COUNT]= {
        1,0,2,
        1,2,3,
    };

    //-----------------------------------------------------------------------
    PuckerMeshData::PuckerMeshData()
    {
        colour        = ColourValue::Blue;
        textureName   = "";
        triIndexType  = 1;

        for(int i=0; i<PuckerMeshData::VERTEX_COUNT; i++ )
        {
            vertexs[i]   = Vector3(0,0,0);
            normal[i]    = Vector3(0,1,0);
        }

        textureUV[0] = Vector2(0,0);
        textureUV[1] = Vector2(0.5,0);

        textureUV[2] = Vector2(0,1);
        textureUV[3] = Vector2(0.5,1);

        textureUV[4] = Vector2(1,1);
        textureUV[5] = Vector2(1,0);
    }

    /*
    -----------------------------------------------------------------------------
    Class ManualMeshManager
    -----------------------------------------------------------------------------
    */
    //-----------------------------------------------------------------------
    void ManualMeshManager::rebuildTwistyBoxMeshData(TwistyBoxMeshData& data, 
        const Vector3& startpos, const Vector3& endpos, Real height, Real width)
    {
        Vector3 line = startpos - endpos;
        line.normalise();

        Vector3 verticalline = Vector3::UNIT_X;
        Real angleResult = abs(line.absDotProduct(Vector3::UNIT_Y) - 1);
        if (angleResult > 0.01)
            verticalline = line.crossProduct(Vector3::UNIT_Y);
        verticalline.normalise();

        Vector3 horizontalline = line.crossProduct(verticalline);
        horizontalline.normalise();

        data.referVertexs[0] = startpos;
        data.referVertexs[1] = startpos;
        data.referVertexs[2] = startpos;
        data.referVertexs[3] = startpos;
        data.referVertexs[4] = endpos;
        data.referVertexs[5] = endpos;
        data.referVertexs[6] = endpos;
        data.referVertexs[7] = endpos;

        Vector3 widthVector = verticalline * height / 2.0f;
        data.referVertexs[1] += widthVector;
        data.referVertexs[3] += widthVector;
        data.referVertexs[5] += widthVector;
        data.referVertexs[7] += widthVector;
        data.referVertexs[0] -= widthVector;
        data.referVertexs[2] -= widthVector;
        data.referVertexs[4] -= widthVector;
        data.referVertexs[6] -= widthVector;

        Vector3 heightVector = horizontalline * width / 2.0f;
        data.referVertexs[0] += heightVector;
        data.referVertexs[1] += heightVector;
        data.referVertexs[4] += heightVector;
        data.referVertexs[5] += heightVector;
        data.referVertexs[2] -= heightVector;
        data.referVertexs[3] -= heightVector;
        data.referVertexs[6] -= heightVector;
        data.referVertexs[7] -= heightVector;

    }

    //-----------------------------------------------------------------------
    void ManualMeshManager::rebuildTwistyBoxMeshData(TwistyBoxMeshData& data, const Vector3& startpos, const Vector3& endpos, 
        const Vector3& startWidthVector, const Vector3& endWidthVector, const Vector3& startheightVector, const Vector3& endheightVector)
    {

        data.referVertexs[0] = startpos + startWidthVector;
        data.referVertexs[1] = startpos - startWidthVector;
        data.referVertexs[2] = startpos + startWidthVector;
        data.referVertexs[3] = startpos - startWidthVector;

        data.referVertexs[4] = endpos + endWidthVector;
        data.referVertexs[5] = endpos - endWidthVector;
        data.referVertexs[6] = endpos + endWidthVector;
        data.referVertexs[7] = endpos - endWidthVector;

        data.referVertexs[0] += startheightVector;
        data.referVertexs[1] += startheightVector;
        data.referVertexs[4] += endheightVector;
        data.referVertexs[5] += endheightVector;
    }

    //-----------------------------------------------------------------------
    void ManualMeshManager::rebuildTwistyBoxMeshTextureUV(TwistyBoxMeshData& data, Real widthScale, Real heightScale)
    {
        Real length1 = data.referVertexs[0].distance(data.referVertexs[4]);
        Real length2 = data.referVertexs[1].distance(data.referVertexs[5]);

        Real perScale = 64 / widthScale;

        Real UVScale1 = perScale * length1 / 256.0;
        Real UVScale2 = perScale * length2 / 256.0;

        //UVScale = 2;
        // 4 6     UVScale1 
        // 5 7     UVScale2
        data.textureUV[14].x = UVScale2;
        data.textureUV[16].x = UVScale2;
        data.textureUV[17].x = UVScale2;

        data.textureUV[18].x = UVScale1;
        data.textureUV[20].x = UVScale1;
        data.textureUV[23].x = UVScale1;

        data.textureUV[24].x = UVScale1;
        data.textureUV[27].x = UVScale1;
        data.textureUV[29].x = UVScale2;

        data.textureUV[32].x = UVScale1;
        data.textureUV[34].x = UVScale2;
        data.textureUV[35].x = UVScale1;

        //0,1,2,  -- 0 1 2
        //1,3,2,  -- 3 4 5
        //5,6,4,  -- 6 7 8
        //5,7,6,  -- 9 10 11

        //1,3,7,  -- 12 13 14
        //1,7,5,  -- 15 16 17
        //4,0,6,  -- 18 19 20
        //0,2,6,  -- 21 22 23

        //4,0,1,  -- 24 25 26
        //4,1,5,  -- 27 28 29
        //2,3,6,  -- 30 31 32
        //3,7,6   -- 33 34 35
    }

    //-----------------------------------------------------------------------
    void ManualMeshManager::rebuildQuadrangleMeshVertexs(QuadrangleMeshData& data, const Vector3& startpos, const Vector3& endpos, 
        const Vector3& startvector, const Vector3& endvector)
    {
        data.vertexs[0] = startpos + startvector;
        data.vertexs[1] = startpos - startvector;
        data.vertexs[2] = endpos + endvector;
        data.vertexs[3] = endpos - endvector;
    }

    //-----------------------------------------------------------------------
    void ManualMeshManager::rebuildQuadrangleMeshTextureUV(QuadrangleMeshData& data,  Real widthScale)
    {
        Real distance01 = data.vertexs[0].distance(data.vertexs[2]);
        Real distance13 = data.vertexs[1].distance(data.vertexs[3]);

        Vector3 line01 = data.vertexs[0] - data.vertexs[1];
        Vector3 line02 = data.vertexs[0] - data.vertexs[2];
        line02.normalise();	

        Real startDelta = line01.dotProduct( line02 );
        startDelta = startDelta / widthScale;

        data.textureUV[0] = Vector2(0,0);
        data.textureUV[1] = Vector2(1,startDelta);

        data.textureUV[2] = data.textureUV[0];
        data.textureUV[3] = data.textureUV[1];

        data.textureUV[2].y += distance01 / widthScale;
        data.textureUV[3].y += distance13 / widthScale;
    }

    //-----------------------------------------------------------------------
    void ManualMeshManager::rebuildPuckerMeshVertexs(PuckerMeshData& data, const Vector3& startpos, const Vector3& endpos, 
        const Vector3& startWidthVector, const Vector3& endWidthVector, const Vector3& startheightVector, const Vector3& endheightVector)
    {
        data.vertexs[1] = startpos;
        data.vertexs[5] = startpos;
        data.vertexs[0] = startpos - startWidthVector;

        data.vertexs[3] = endpos;
        data.vertexs[4] = endpos;
        data.vertexs[2] = endpos - endWidthVector;

        data.vertexs[0] += startheightVector;
        data.vertexs[1] += startheightVector;

        data.vertexs[2] += endheightVector;
        data.vertexs[3] += endheightVector;
    }

    //-----------------------------------------------------------------------
    void ManualMeshManager::rebuildPuckerMeshTextureUV(PuckerMeshData& data, Real widthScale, Real divScale)
    {
        Real distance01 = data.vertexs[0].distance(data.vertexs[2]);
        Real distance13 = data.vertexs[1].distance(data.vertexs[3]);

        Vector3 line01 = data.vertexs[0] - data.vertexs[1];
        Vector3 line02 = data.vertexs[0] - data.vertexs[2];
        line02.normalise();	

        Real startDelta = line01.dotProduct( line02 );
        startDelta = startDelta / widthScale;

        data.textureUV[0] = Vector2(0,0);
        data.textureUV[1] = Vector2(divScale,startDelta);
        data.textureUV[2] = Vector2(0,0);
        data.textureUV[3] = Vector2(divScale,startDelta);

        data.textureUV[4] = Vector2(1,startDelta);
        data.textureUV[5] = Vector2(1,startDelta);

        data.textureUV[2].y += distance01 / widthScale;
        data.textureUV[3].y += distance13 / widthScale;
        data.textureUV[4].y += distance13 / widthScale;
    }

    //-----------------------------------------------------------------------
    void ManualMeshManager::getTriangle3DList( MeshPtr mesh, std::vector< Triangle3D >& list )
    {
        list.clear();

        if ( mesh.isNull() )
            return;

        ///////////////////////////////////////////////////////////

        //不考虑使用共享顶点缓存
        //得到顶点和索引数目
        size_t vertex_count = 0;
        size_t index_count  = 0;
        for (unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i)
        {
            Ogre::SubMesh* submesh = mesh->getSubMesh( i );
            vertex_count += submesh->vertexData->vertexCount;
            index_count  += submesh->indexData->indexCount;
        }

        std::vector<Ogre::Vector3> posList;
        posList.resize( vertex_count + 1 );
        std::vector<unsigned long> indexList;
        indexList.resize( index_count + 1 );

        ///////////////////////////////////////////////////////////


        //填充顶点索引容器
        size_t current_offset  = 0;
        size_t shared_offset   = 0;
        size_t next_offset     = 0;
        size_t index_offset    = 0;

        for ( unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i)
        {
            //顶点
            Ogre::SubMesh* submesh = mesh->getSubMesh(i);
            Ogre::VertexData* vertex_data = submesh->vertexData;

            const Ogre::VertexElement* posElem =
                vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);

            Ogre::HardwareVertexBufferSharedPtr vbuf =
                vertex_data->vertexBufferBinding->getBuffer(posElem->getSource());

            unsigned char* vertex =
                static_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
            {
                float* pReal;

                for( size_t j = 0; j < vertex_data->vertexCount; ++j, vertex += vbuf->getVertexSize())
                {
                    posElem->baseVertexPointerToElement(vertex, &pReal);

                    Ogre::Vector3 pt(pReal[0], pReal[1], pReal[2]);

                    posList[current_offset + j] = pt;
                }
            }
            vbuf->unlock();

            next_offset += vertex_data->vertexCount;

            //索引
            Ogre::IndexData* index_data = submesh->indexData;
            size_t numTris = index_data->indexCount / 3;
            Ogre::HardwareIndexBufferSharedPtr ibuf = index_data->indexBuffer;

            bool use32bitindexes = (ibuf->getType() == Ogre::HardwareIndexBuffer::IT_32BIT);

            unsigned long*  pLong = static_cast<unsigned long*>(ibuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
            {

                unsigned short* pShort = reinterpret_cast<unsigned short*>(pLong);

                size_t offset = current_offset;

                if ( use32bitindexes )
                {
                    for ( size_t k = 0; k < numTris*3; ++k)
                    {
                        indexList[index_offset++] = pLong[k] + static_cast<unsigned long>(offset);
                    }
                }
                else
                {
                    for ( size_t k = 0; k < numTris*3; ++k)
                    {
                        indexList[index_offset++] = static_cast<unsigned long>(pShort[k]) +
                            static_cast<unsigned long>(offset);
                    }
                }
            }

            ibuf->unlock();

            current_offset = next_offset;
        }

        ///////////////////////////////////////////////////////////

        Triangle3D tri;

        //填充
        for (size_t i = 0; i < index_count; i += 3)
        {
            tri.t0 = posList[ indexList[i] ];
            tri.t1 = posList[ indexList[i+1] ];
            tri.t2 = posList[ indexList[i+2] ];
            tri.plane = Plane( tri.t0, tri.t1, tri.t2 );

            list.push_back( tri );
        }
    }

   
}