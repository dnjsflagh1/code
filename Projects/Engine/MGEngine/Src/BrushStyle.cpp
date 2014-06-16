\/******************************************************************************/
#include "stdafx.h"
#include "BrushStyle.h"
#include "BrushSystem.h"
#include "IBrushShape.h"
/******************************************************************************/

namespace MG
{


    /******************************************************************************/
    //BrushAirStyle
    /******************************************************************************/
    BrushAirStyle::BrushAirStyle()
		:mAtten(100.0f)
    {
		
    }

    //-----------------------------------------------------------------------
    BrushAirStyle::~BrushAirStyle()
    {

    }
	//-----------------------------------------------------------------------
	Flt BrushAirStyle::getAttenuation()
	{
		return mAtten;
	}
	//-----------------------------------------------------------------------
	void BrushAirStyle::setAttenuation(Flt atten)
	{
		mAtten = atten;
	}
    //-----------------------------------------------------------------------
    Bool BrushAirStyle::isValidPos( Vec2 pos )
    {
        return false;
    }

    //-----------------------------------------------------------------------
    Flt BrushAirStyle::getIntensity( Vec2 pos )
    {
		IBrushShape* brushShape = BrushSystem::getInstance().getActiveShape();
		if ( !brushShape )
			return 0.0f;

		Flt brushSize   =  brushShape->getValidRange(pos);
		if ( brushSize == 0.0f )
			return 0.0f;

		Vec3 brushPos = BrushSystem::getInstance().getStartPos();

		Vector2 brush2DPos = Vector2( brushPos.x, brushPos.z );
		Vector2 judgePos = Vector2( pos.x, pos.y );

		Flt radius      = ( brush2DPos - judgePos ).length();
        
        if ( radius > brushSize )
        {
            radius = brushSize;
        }

		Flt affect_factor = 1.0f - ( radius / brushSize );

		affect_factor = max(0.0f, affect_factor);
		affect_factor = min(1.0f, affect_factor);

		Flt result = 0.0f;

		if ( mAtten < 20.0f )
		{
			Flt fBase = 1.0f - ( mAtten - 1 ) * 0.02f;  //最大影响半径

			if ( fBase <= 0.0f )
				fBase = 0.0f;

			Flt fRadius = 1.0f - affect_factor;  // 当前半径;

			if ( fRadius >= fBase )
			{
				Flt rate = ( fRadius - fBase ) / ( 1.0 - fBase );
				//rate *= 0.75f;
				result = (1.0 - pow((cos( (1.0f - rate) * MG_PI) + 1.0f) * 0.5f, 2.0f));
				//result = 1 - ( 3 * rate * rate - 2 * rate * rate * rate ); 
			}
			else
			{
				result = 1.0f;
			}
		}
		else if ( mAtten < 50.0f )
		{
			result = (1.0 - pow((cos( (affect_factor) * MG_PI) + 1.0f) * 0.5f, (50.0f - mAtten) * 0.2f + 1.0f));
		}
		else
		{
			result = ( pow((cos( (1.0f - affect_factor) * MG_PI) + 1.0f) * 0.5f, ((mAtten - 50.0f)) * 0.025f + 1.0f));
		}

		return result;
    }

    /******************************************************************************/
    //BrushPaintStyle
    /******************************************************************************/
    BrushPaintStyle::BrushPaintStyle()
    {

    }

    //-----------------------------------------------------------------------
    BrushPaintStyle::~BrushPaintStyle()
    {

    }

    //-----------------------------------------------------------------------
    Bool BrushPaintStyle::isValidPos( Vec2 pos )
    {

        return false;
    }

    //-----------------------------------------------------------------------
    Flt BrushPaintStyle::getIntensity( Vec2 pos )
    {
		return 1.0f;
    }
    /******************************************************************************/
    //BrushNoiseStyle
    /******************************************************************************/
	Flt	BrushNoiseStyle::FILTER_TEX_MAX_SIZE = 512;
	//-----------------------------------------------------------------------
    BrushNoiseStyle::BrushNoiseStyle()
		:m_fVariable(0.0f)
		,m_nFilterTexHeight(0)
		,m_nFilterTexWidth(0)
		,m_pFilterTexData(NULL)
	{
    }

    //-----------------------------------------------------------------------
    BrushNoiseStyle::~BrushNoiseStyle()
    {
		delete []m_pFilterTexData;
    }

    //-----------------------------------------------------------------------
    Bool BrushNoiseStyle::isValidPos( Vec2 pos )
    {
        return false;
    }

    //-----------------------------------------------------------------------
    Flt BrushNoiseStyle::getIntensity( Vec2 pos )
    {
		if ( m_pFilterTexData == NULL )
		{
			drawFilterTexture();
		}

		//获取笔刷中心世界坐标 
		Vec3 brushPos = BrushSystem::getInstance().getStartPos();

		//获取当前输入坐标 
		Vector2 judgePos = Vector2( pos.x, pos.y );

		//获取当前输入坐标， 在过滤图中的纹理位置
		/*	(0.0,1.0)---------(1.0,1.0)
				|				  |
				|				  |
				|			 	  |
				|				  |	
				|				  |
			(0.0,0.0)---------(1.0,0.0)	
		*/
		Vector2 brushLD = Vector2( brushPos.x - BrushSystem::getInstance().getSize(), brushPos.z + BrushSystem::getInstance().getSize() );
		Vector2 brushRU = Vector2( brushPos.x + BrushSystem::getInstance().getSize(), brushPos.z - BrushSystem::getInstance().getSize() );

		Vector2 texCoord = Vector2( (float)(judgePos.x - brushLD.x) / (float)(brushRU.x - brushLD.x), 
									(float)(judgePos.y - brushLD.y) / (float)(brushRU.y - brushLD.y) );

		//通过纹理位置获得我的噪度
		U32 filterTexPosX = texCoord.x * m_nFilterTexWidth;
		U32 filterTexPosY = texCoord.y * m_nFilterTexHeight;

		if ( filterTexPosX < 0 || 
			filterTexPosX > m_nFilterTexWidth || 
			filterTexPosY < 0 || 
			filterTexPosY > m_nFilterTexHeight )
			return 0.0f;

		return (Flt)m_pFilterTexData[filterTexPosY * m_nFilterTexWidth + filterTexPosX] / 255.0f;
    }
	//-----------------------------------------------------------------------
	Flt BrushNoiseStyle::getResolution()
	{
		return m_nFilterTexHeight * m_nFilterTexWidth;
	}
	//-----------------------------------------------------------------------
	void BrushNoiseStyle::setResolution(U32 size)
	{
		MGMin ( size, FILTER_TEX_MAX_SIZE );
		MGMax ( 0, size );

		m_nFilterTexWidth = size;
		m_nFilterTexHeight = size;

		drawFilterTexture();
	}
	//-----------------------------------------------------------------------
	Flt  BrushNoiseStyle::getVariable()
	{
		return m_fVariable;
	}
	//-----------------------------------------------------------------------
	void BrushNoiseStyle::setVariable(Flt variable)
	{
		m_fVariable = variable;

		min ( m_fVariable, 1.0f );
		max ( 0.0f, m_fVariable );
		
		drawFilterTexture();
	}
	//-----------------------------------------------------------------------
	void BrushNoiseStyle::drawFilterTexture()
	{
		if ( !m_pFilterTexData )
		{
			m_pFilterTexData = new U8[ FILTER_TEX_MAX_SIZE * FILTER_TEX_MAX_SIZE ];
		}

		//clear Texture;
		ZeroMemory( m_pFilterTexData, sizeof(U8) * FILTER_TEX_MAX_SIZE * FILTER_TEX_MAX_SIZE );

		m_nFilterTexHeight = FILTER_TEX_MAX_SIZE;
		m_nFilterTexWidth = FILTER_TEX_MAX_SIZE;

		//calculate every element
		for ( U32 y = 0; y < m_nFilterTexHeight; y++ )
		{
			for ( U32 x = 0; x < m_nFilterTexWidth; x++ )
			{
				U8 int_result = 0;

				/*if ( x % 35 == 0 || y % 35 == 0 )
				{
					m_pFilterTexData[ y * m_nFilterTexWidth + x ] = int_result;
				}
				else*/
				{
					Flt result = MGMath::MG_PerlinNoise_2D( (Flt)x / 35.0f, (Flt)y / 35.0f, 0.7f, 6);

					U8 int_result = (result + 0.5f) * 255;

					int_result = MGMax( 0, int_result );
					int_result = MGMin( int_result, 255 );

					m_pFilterTexData[ y * m_nFilterTexWidth + x ] = int_result;
				}
			}
		}
	}
	//-----------------------------------------------------------------------
	void BrushNoiseStyle::resizeFilterTexture()
	{
		//if ( !m_pFilterTexData )
		//{
		//	m_pFilterTexData = new U8[ FILTER_TEX_MAX_WIDTH * FILTER_TEX_MAX_HEIGHT ];
		//}

		////clear Texture;
		//ZeroMemory( m_pFilterTexData, sizeof(U8) * FILTER_TEX_MAX_WIDTH * FILTER_TEX_MAX_HEIGHT );

		////

	}
    /******************************************************************************/
    //BrushFractalStyle
    /******************************************************************************/
    BrushFractalStyle::BrushFractalStyle()
    {

    }

    //-----------------------------------------------------------------------
    BrushFractalStyle::~BrushFractalStyle()
    {

    }

    //-----------------------------------------------------------------------
    Bool BrushFractalStyle::isValidPos( Vec2 pos )
    {

        return false;
    }

    //-----------------------------------------------------------------------
    Flt BrushFractalStyle::getIntensity( Vec2 pos )
    {

        return 1;
    }


}