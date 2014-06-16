/******************************************************************************/
#include "stdafx.h"
#include "TerrainHeightOperation.h"
#include "Scene.h"
#include "TerrainChunk.h"
#include "BrushSystem.h"
#include "TerrainTiles.h"
#include "TerrainHeightOperationManager.h"
#include "BrushStyle.h"
#include "BrushShape.h"
#include "EditorSystem.h"

#include "TerrainGroundSurface.h"
#include "TerrainWaterSurface.h"
/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //TerrainHeightOperation
    /******************************************************************************/
    TerrainHeightOperation::TerrainHeightOperation(TerrainSurfaceType type)
        :mTerrainSurfaceType(type)
    {

    }

    //-----------------------------------------------------------------------
    TerrainHeightOperation::~TerrainHeightOperation()
    {

    }

	//-----------------------------------------------------------------------
	void TerrainHeightOperation::execute( TerrainChunk* chunk, Ogre::Rect& worldRect )
	{
        TerrainSurface* surface = NULL;
        if ( mTerrainSurfaceType == TST_GROUND )
        {
            surface = chunk->getTerrainGroundSurface();
        }else
        if ( mTerrainSurfaceType == TST_WATER )
        {
            surface = chunk->getTerrainWaterSurface();
        }

        //////////////////////////////////////////////////////////////////////

        if ( surface )
        {
            /* // ��������

            -z
            |
            |
            w0---------w1
            |          |
            | [brush]  |
            |          |
            w2---------w3----+x
            */

            // ��������Rect
            Vector3 w0 = Vector3( worldRect.left,  0, worldRect.top );
            Vector3 w1 = Vector3( worldRect.right, 0, worldRect.top );
            Vector3 w2 = Vector3( worldRect.left,  0, worldRect.bottom );
            Vector3 w3 = Vector3( worldRect.right, 0, worldRect.bottom );


            /* // ��������
            +y
            |
            |
            p0---------p1
            |          |
            | [brush]  |
            |          |
            p2---------p3----+x
            */
            // ��������Rect
            Vector3 p0,p1,p2,p3; 
            surface->convertWorldPositionToVertexPoint(w0, &p0);
            surface->convertWorldPositionToVertexPoint(w1, &p1);
            surface->convertWorldPositionToVertexPoint(w2, &p2);
            surface->convertWorldPositionToVertexPoint(w3, &p3);


            // ������Χ�е����ж���
            for (uint16 y = p2.y; y <= p0.y; y ++)
            {
                for (uint16 x = p2.x; x <= p3.x; x ++)
                {
                    // Ӱ��߶Ȳ���
                    influenceHeight( chunk, surface, x, y, 0 );

                    // ͬ��ˮλ��
                    if ( mTerrainSurfaceType == TST_GROUND )
                    {
                        chunk->getTerrainWaterSurface()->dirtyRect( x, y );
                    }
                }
            }
        }
	}

	//-----------------------------------------------------------------------
	void TerrainHeightOperation::rollback()
	{

	}

    /******************************************************************************/
    //TerrainRaiseHeightOperation
    /******************************************************************************/
    TerrainRaiseHeightOperation::TerrainRaiseHeightOperation(TerrainSurfaceType type)
        :TerrainHeightOperation(type)
    {

    }

    //-----------------------------------------------------------------------
    TerrainRaiseHeightOperation::~TerrainRaiseHeightOperation()
    {

    }

	//-----------------------------------------------------------------------
	void TerrainRaiseHeightOperation::influenceHeight( TerrainChunk* chunk, TerrainSurface* surface, Int x, Int y, Flt intensity )
	{
		if ( surface )
		{
			// �õ���������
			Vector3 worldPos;
			surface->convertVertexPointToWorldPosition(x,y,0,&worldPos);
			Vec2 world2DPos = Vec2(worldPos.x,worldPos.z);

            Vec2 magin;
			// �ж��Ƿ��ڱ�ˢ��Χ��
			if ( BrushSystem::getInstance().getActiveShape()->isValidPos( world2DPos, magin ) )
			{
				// �õ���ˢ��Ӱ��ϵ��
				Flt intensity = BrushSystem::getInstance().getActiveStyle()->getIntensity( world2DPos );

				// �õ�����
				Flt amplitude = 0.0;
				if ( mTerrainSurfaceType == TST_GROUND )
				{
					amplitude = TerrainRaiseHeightOperationManager::getInstance().getAmplitude();
				}
				else if ( mTerrainSurfaceType == TST_WATER )
				{
					amplitude = TerrainRaiseHeightOperationManager::getInstance().getWaterAmplitude();
				}

				// �õ����α仯��
				Flt height_delta = amplitude * intensity;

				// �õ������߸߶�
				Flt height = surface->getHeightAtPoint(x,y);
				height += height_delta;

				// ���ø߶�
				surface->setHeightAtPoint(x,y,height);
			}
		}	
	}

    /******************************************************************************/
    //TerrainLowerHeightOperation
    /******************************************************************************/
    TerrainLowerHeightOperation::TerrainLowerHeightOperation(TerrainSurfaceType type)
        :TerrainHeightOperation(type)
    {

    }

    //-----------------------------------------------------------------------
    TerrainLowerHeightOperation::~TerrainLowerHeightOperation()
    {

    }

	//-----------------------------------------------------------------------
	void TerrainLowerHeightOperation::influenceHeight( TerrainChunk* chunk, TerrainSurface* surface, Int x, Int y, Flt intensity )
	{
		if ( surface )
		{
			// �õ���������
			Vector3 worldPos;
			surface->convertVertexPointToWorldPosition(x,y,0,&worldPos);
			Vec2 world2DPos = Vec2(worldPos.x,worldPos.z);

            Vec2 magin;
			// �ж��Ƿ��ڱ�ˢ��Χ��
			if ( BrushSystem::getInstance().getActiveShape()->isValidPos( world2DPos, magin ) )
			{
				// �õ���ˢ��Ӱ��ϵ��
				Flt intensity = BrushSystem::getInstance().getActiveStyle()->getIntensity( world2DPos );

				// �õ�����
				Flt amplitude = 0.0;
				if ( mTerrainSurfaceType == TST_GROUND )
				{
					amplitude = TerrainLowerHeightOperationManager::getInstance().getAmplitude();
				}
				else if ( mTerrainSurfaceType == TST_WATER )
				{
					amplitude = TerrainLowerHeightOperationManager::getInstance().getWaterAmplitude();
				}

				// �õ����α仯��
				Flt height_delta = amplitude * intensity;

				// �õ������߸߶�
				Flt height = surface->getHeightAtPoint(x,y);
				height -= height_delta;

				// ���ø߶�
				surface->setHeightAtPoint(x,y,height);
			}
		}	
	}

    /******************************************************************************/
    //TerrainUniformHeightOperation
    /******************************************************************************/
    TerrainUniformHeightOperation::TerrainUniformHeightOperation(TerrainSurfaceType type)
        :TerrainHeightOperation(type)
    {
		
    }

    //-----------------------------------------------------------------------
    TerrainUniformHeightOperation::~TerrainUniformHeightOperation()
    {

    }

	//-----------------------------------------------------------------------
	void TerrainUniformHeightOperation::execute()
	{
		if ( getScene() )
		{
			TerrainManager* terrain = getScene()->getTerrainManager();
			if ( terrain )
			{
				Vec3 center = BrushSystem::getInstance().getStartPos();
				TerrainChunk* terrainChunk = terrain->getTerrainChunkByWorldPos(Vec2(center.x, center.z));
				if ( mTerrainSurfaceType == TST_GROUND && 
					terrainChunk && terrainChunk->getTerrainGroundSurface() )
				{
					TerrainGroundSurface* surface = terrainChunk->getTerrainGroundSurface();
					TerrainUniformHeightOperationManager::getInstance().setGroundHeight(surface->getHeightAtWorldPosition(center.x, center.z));
				}

				Ogre::Rect rect = BrushSystem::getInstance().getActiveRect();
				UInt chunkCount = terrain->getTerrainChunkCount();

				for (UInt i=0;i<chunkCount; i++)
				{
					TerrainChunk* chunk = terrain->getTerrainChunkByIndex(i);

					if ( chunk )
					{
						Ogre::Rect chunkRect = rect.intersect( chunk->getBoundingRect() );

						if ( chunkRect.isNull() == false )
						{
							TerrainHeightOperation::execute( chunk, chunkRect );
						}
					}
				}
			}
		}
	}

    //-----------------------------------------------------------------------
	void TerrainUniformHeightOperation::influenceHeight( TerrainChunk* chunk, TerrainSurface* surface, Int x, Int y, Flt intensity )
	{
        Vec3 brushPos = BrushSystem::getInstance().getStartPos();

		if ( surface )
		{
			// �õ���������
			Vector3 worldPos;
			surface->convertVertexPointToWorldPosition(x,y,0,&worldPos);
			Vec2 world2DPos = Vec2(worldPos.x,worldPos.z);

            Vec2 magin;
			// �ж��Ƿ��ڱ�ˢ��Χ��
			if ( BrushSystem::getInstance().getActiveShape()->isValidPos( world2DPos, magin ) )
			{ 
				Flt uniformHeight = 0;

				if ( mTerrainSurfaceType == TST_GROUND )
				{
					uniformHeight = TerrainUniformHeightOperationManager::getInstance().getGroundHeight();
				}
				else if ( mTerrainSurfaceType == TST_WATER )
				{
					uniformHeight = TerrainUniformHeightOperationManager::getInstance().getWaterHeight();
				}
				
				//������ƽ�߶�
				surface->setHeightAtPoint(x, y, uniformHeight);
			}
		}	
	}
    /******************************************************************************/
    //TerrainNoiseHeightOperation
    /******************************************************************************/
    TerrainNoiseHeightOperation::TerrainNoiseHeightOperation(TerrainSurfaceType type)
        :TerrainHeightOperation(type)
    {

    }

    //-----------------------------------------------------------------------
    TerrainNoiseHeightOperation::~TerrainNoiseHeightOperation()
    {

    }

	//-----------------------------------------------------------------------
	void TerrainNoiseHeightOperation::influenceHeight( TerrainChunk* chunk, TerrainSurface* surface, Int x, Int y, Flt intensity )
	{
        Vector3 worldPos;
        surface->convertVertexPointToWorldPosition(x, y, &worldPos);
        Vec3 brushPos   = BrushSystem::getInstance().getStartPos();
        Flt brushSize  = BrushSystem::getInstance().getSize();

        ////////////////////////////////////////////////////////////////////////////////////////

        Vector3 vec_dist;
		Flt noise_value = 0.0f;
        vec_dist.x = worldPos.x - brushPos.x;
        vec_dist.y = 0;
        vec_dist.z = worldPos.z - brushPos.z;

        if ( x % 35 == 0 || y % 35 == 0 || fabs(vec_dist.length() - brushSize) < 1.0f )
        {
            noise_value = 0.0f;
        }	
        else
        {
            Flt result = MGMath::MG_PerlinNoise_2D( (Flt)(x) / 35.0f, (Flt)(y) / 35.0f, 0.7f, 6);
            noise_value = -0.5f + 1.5f * ( result + 0.5f );
        }	

        ///////////////////////////////////////////////////////////////////////////////////////////

		Vec2 world2DPos = Vec2(worldPos.x,worldPos.z);

        Vec2 magin;
		// �ж��Ƿ��ڱ�ˢ��Χ��
		if ( BrushSystem::getInstance().getActiveShape()->isValidPos( world2DPos, magin ) )
		{
			// �õ�����
			Flt amplitude = TerrainNoiseHeightOperationManager::getInstance().getAmplitude();

			// �õ����α仯��
			Flt height_delta = amplitude * noise_value;

			// �õ������߸߶�
			Flt height = surface->getHeightAtPoint(x,y);
			height += height_delta;

			// ���ø߶�
			surface->setHeightAtPoint(x,y,height);
		}
	}
	//-----------------------------------------------------------------------
	Flt TerrainNoiseHeightOperation::coherentNoise(Vec2 vertex_frac, Flt left_top, Flt left_buttom, Flt right_top, Flt right_buttom)
	{
		Flt final_result_top = MG_LERP(left_top, right_top, MGMath::Fade( vertex_frac.x ));
		Flt final_result_buttom = MG_LERP(left_buttom, right_buttom, MGMath::Fade( vertex_frac.x ));
		Flt final_result = MG_LERP(final_result_buttom, final_result_top, MGMath::Fade( vertex_frac.y));

		return final_result;
	}
	//-----------------------------------------------------------------------
	Flt TerrainNoiseHeightOperation::perlinNoise(int octaves, Vec2 vertex_frac, Flt left_top, Flt left_buttom, Flt right_top, Flt right_buttom)
	{
		Flt total = 0.0f;
		Flt persistence = 4.0f;

		for ( int i = 0; i < octaves; i++ )
		{
			Vec2 _vertex_frac;
			_vertex_frac.x = vertex_frac.x * ( Ogre::Math::Pow(2, i) );
			_vertex_frac.y = vertex_frac.y * ( Ogre::Math::Pow(2, i) );

			total += ( coherentNoise(_vertex_frac, left_top, right_buttom, right_top, right_buttom) / Ogre::Math::Pow(persistence, i) );
		}

		total = max(-1.0f, total);
		total = min(total, 1.0f);

		return total;
	}
    
    /******************************************************************************/
    //TerrainSmoothHeightOperation
    /******************************************************************************/
    TerrainSmoothHeightOperation::TerrainSmoothHeightOperation(TerrainSurfaceType type)
        :TerrainHeightOperation(type)
    {

    }
    //-----------------------------------------------------------------------
    TerrainSmoothHeightOperation::~TerrainSmoothHeightOperation()
    {

    }
	//-----------------------------------------------------------------------
	void TerrainSmoothHeightOperation::influenceHeight( TerrainChunk* chunk, TerrainSurface* surface, Int x, Int y, Flt intensity )
	{
		//�õ���������
		Vector3 worldPos;
		surface->convertVertexPointToWorldPosition(x, y, 0, &worldPos);
		Vec2 world2DPos = Vec2(worldPos.x,worldPos.z);

        Vec2 magin;
		//�ж��Ƿ��ڱ�ˢ��Χ֮��
		if ( BrushSystem::getInstance().getActiveShape()->isValidPos(world2DPos,magin) )
		{
			/* // ��������
			+y
			|
			|
			p0----p1-----p2
			|            |
			p7    p9     p3
			|            |
			p6----p5-----p4--+x
			*/
			//Vector3 p0,p1,p2,p3,p4,p5,p6,p7;
			//p9��������Ҫ�����ĵ�

			Flt amplitude = TerrainSmoothHeightOperationManager::getInstance().getAmplitude();
			Flt total_height = surface->getHeightAtPoint(x, y)/* TerrainSmoothHeightOperationManager::getInstance().getAmplitude()*/;
			Flt total_point = 1;
			int vertexSideNum = surface->getVertexSideNum();

			//����p9��Χ�����е㣬���ϸ߶�ֵ
			for ( int point_index_y = y - 1; point_index_y <= y + 1; point_index_y++ )
			{
				for ( int point_index_x = x - 1; point_index_x <= x + 1; point_index_x++ )
				{
					//����������ĵ���p9, ��Ҫ����;
					if ( point_index_x == x && point_index_y == y )
						continue;

					if ( point_index_x >= 0 && 
						point_index_x < vertexSideNum
						&& point_index_y >= 0 && 
						point_index_y < vertexSideNum )
					{
						total_height += surface->getHeightAtPoint(point_index_x, point_index_y);
						total_point ++;
					}
				}
			}

			//Ŀ��߶�
			Flt original_height = surface->getHeightAtPoint(x, y);
			Flt average_height = total_height / total_point;

			//��Ŀ��߶��ƽ�
			Flt delta = average_height - original_height;
			delta *= amplitude;

			surface->setHeightAtPoint(x, y , original_height + delta);
		}
		
	}
	
}


