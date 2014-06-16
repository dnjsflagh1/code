/******************************************************************************/
#include "stdafx.h"
#include "BrushShape.h"
#include "BrushSystem.h"
#include "MGEngineUtility.h"
/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //BrushCircleShape
    /******************************************************************************/
    BrushCircleShape::BrushCircleShape()
    {
        
    }

    //-----------------------------------------------------------------------
    BrushCircleShape::~BrushCircleShape()
    {
        
    }

    //-----------------------------------------------------------------------
    Bool BrushCircleShape::isValidPos( Vec2 pos, Vec2& margin )
    {
        Vec3 brushPos = BrushSystem::getInstance().getStartPos();

        Vector2 brush2DPos = Vector2( brushPos.x, brushPos.z );
        Vector2 judgePos = Vector2( pos.x, pos.y );

        Flt radius      = ( brush2DPos - judgePos ).length();
        Flt brushSize   =  BrushSystem::getInstance().getSize();
        
        Vector2 ogreVec2 = (judgePos - brush2DPos).normalisedCopy();
        ogreVec2 = ogreVec2 * abs(radius-brushSize);
        margin  = Vec2(ogreVec2.x,ogreVec2.y);

        if ( radius <= brushSize )
        {
            return true;
        }

        return false;
    }

	 //-----------------------------------------------------------------------
	Flt BrushCircleShape::getValidRange( Vec2 pos )
	{
		return BrushSystem::getInstance().getSize();
	}

    /******************************************************************************/
    //BrushRectShape
    /******************************************************************************/
    BrushRectShape::BrushRectShape()
    {

    }

    //-----------------------------------------------------------------------
    BrushRectShape::~BrushRectShape()
    {

    }

    //-----------------------------------------------------------------------
    Bool BrushRectShape::isValidPos( Vec2 pos, Vec2& margin )
    {
		Vec3 brushPos = BrushSystem::getInstance().getStartPos();

		Vector2 brush2DPos = Vector2( brushPos.x, brushPos.z );
		Vector2 judgePos = Vector2( pos.x, pos.y );
		Vector2 judge_dir = (judgePos - brush2DPos).normalisedCopy();

		Flt radius      = ( brush2DPos - judgePos ).length();
		Flt brushSize   =  BrushSystem::getInstance().getSize();
		Flt brushValidRange = getValidRange(pos);

		Vector2 ogreVec2 = judge_dir * abs(radius-brushValidRange);
		margin = Vec2(ogreVec2.x,ogreVec2.y);

		if ( brushValidRange != 0.0f &&
			radius <= brushValidRange )
		{
			return true;
		}

		return false;
    }

	//-----------------------------------------------------------------------
	Flt BrushRectShape::getValidRange( Vec2 pos )
	{
		Vec3 brushPos = BrushSystem::getInstance().getStartPos();

		Vector2 brush2DPos = Vector2( brushPos.x, brushPos.z );
		Vector2 judgePos = Vector2( pos.x, pos.y );
		Vector2 judge_dir = (judgePos - brush2DPos).normalisedCopy();

		Flt radius      = ( brush2DPos - judgePos ).length();
		Flt brushSize   =  BrushSystem::getInstance().getSize();

		Vector2 rect_lu = brush2DPos + Vector2( -brushSize, -brushSize );
		Vector2 rect_ru = brush2DPos + Vector2( brushSize, -brushSize );
		Vector2 rect_ld = brush2DPos + Vector2( -brushSize, brushSize );
		Vector2 rect_rd = brush2DPos + Vector2( brushSize, brushSize);

		Vector2 pt_insect;

		if ( MGEngineUtility::isSegmentLineIntersect2D( rect_ru, rect_lu, brush2DPos, judge_dir, pt_insect ) )
			return (pt_insect - brush2DPos).length();
		if ( MGEngineUtility::isSegmentLineIntersect2D( rect_rd, rect_ru, brush2DPos, judge_dir, pt_insect ) )
			return (pt_insect - brush2DPos).length();
		if ( MGEngineUtility::isSegmentLineIntersect2D( rect_ld, rect_rd, brush2DPos, judge_dir, pt_insect ) )
			return (pt_insect - brush2DPos).length();
		if ( MGEngineUtility::isSegmentLineIntersect2D( rect_lu, rect_ld, brush2DPos, judge_dir, pt_insect ) )
			return (pt_insect - brush2DPos).length();

		return 0.0f;
	}

    /******************************************************************************/
    //BrushRhombusShape
    /******************************************************************************/
    BrushRhombusShape::BrushRhombusShape()
    {

    }

    //-----------------------------------------------------------------------
    BrushRhombusShape::~BrushRhombusShape()
    {

    }

    //-----------------------------------------------------------------------
    Bool BrushRhombusShape::isValidPos( Vec2 pos, Vec2& margin )
    {
		Vec3 brushPos = BrushSystem::getInstance().getStartPos();

		Vector2 brush2DPos = Vector2( brushPos.x, brushPos.z );
		Vector2 judgePos = Vector2( pos.x, pos.y );
		Vector2 judge_dir = (judgePos - brush2DPos).normalisedCopy();

		Flt radius      = ( brush2DPos - judgePos ).length();
		Flt brushSize   =  BrushSystem::getInstance().getSize();
		Flt brushValidRange = getValidRange(pos);

		Vector2 ogreVec2 = judge_dir * abs(radius-brushValidRange);
		margin = Vec2(ogreVec2.x,ogreVec2.y);
		
		if ( brushValidRange != 0.0f &&
			radius <= brushValidRange )
		{
			return true;
		}

		return false;
    }

	//-----------------------------------------------------------------------
	Flt BrushRhombusShape::getValidRange( Vec2 pos )
	{
		Vec3 brushPos = BrushSystem::getInstance().getStartPos();

		Vector2 brush2DPos = Vector2( brushPos.x, brushPos.z );
		Vector2 judgePos = Vector2( pos.x, pos.y );
		Vector2 judge_dir = (judgePos - brush2DPos).normalisedCopy();

		Flt radius      = ( brush2DPos - judgePos ).length();
		Flt brushSize   =  BrushSystem::getInstance().getSize();

		Vector2 shape_up = brush2DPos + Vector2( 0.0f, -brushSize );
		Vector2 shape_left = brush2DPos + Vector2( -brushSize, 0.0f );
		Vector2 shape_down = brush2DPos + Vector2( 0.0f, brushSize );
		Vector2 shape_right = brush2DPos + Vector2( brushSize, 0.0f);

		Vector2 pt_insect;

		if ( MGEngineUtility::isSegmentLineIntersect2D( shape_left, shape_up, brush2DPos, judge_dir, pt_insect ) )
			return (pt_insect - brush2DPos).length();
		if ( MGEngineUtility::isSegmentLineIntersect2D( shape_up, shape_right, brush2DPos, judge_dir, pt_insect ) )
			return (pt_insect - brush2DPos).length();
		if ( MGEngineUtility::isSegmentLineIntersect2D( shape_right, shape_down, brush2DPos, judge_dir, pt_insect ) )
			return (pt_insect - brush2DPos).length();
		if ( MGEngineUtility::isSegmentLineIntersect2D( shape_down, shape_left, brush2DPos, judge_dir, pt_insect ) )
			return (pt_insect - brush2DPos).length();

		return 0.0f;
	}

}


