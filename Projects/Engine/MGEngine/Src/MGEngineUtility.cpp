/******************************************************************************/
#include "stdafx.h"
#include "MGEngineUtility.h"
#include "MGCapabilities.h"
#include "ISceneNode.h"
/******************************************************************************/

namespace MG
{
    //-----------------------------------------------------------------------
    void MGEngineUtility::toVec2( const Vec3& src, Vector3& des)
    {
        des.x = src.x;
        des.y = src.y;
        des.z = src.z;
    }

    //-----------------------------------------------------------------------
    void MGEngineUtility::toVec3( const Vec3& src, Vector3& des)
    {
        des.x = src.x;
        des.y = src.y;
        des.z = src.z;
    }

    //-----------------------------------------------------------------------
    Vector2 MGEngineUtility::toVec2( const Vec3& src )
    {
        return Vector2(src.x,src.y);
    }

    //-----------------------------------------------------------------------
    Vector3 MGEngineUtility::toVec3( const Vec3& src )
    {
        return Vector3(src.x,src.y,src.z);
    }

    //-----------------------------------------------------------------------
    void MGEngineUtility::toVec2( const Vector3& src, Vec3& des)
    {
        des.x = src.x;
        des.y = src.y;
    }

    //-----------------------------------------------------------------------
    void MGEngineUtility::toVec3( const Vector3& src, Vec3& des)
    {
        des.x = src.x;
        des.y = src.y;
		des.z = src.z;
    }

    //-----------------------------------------------------------------------
    Vec2 MGEngineUtility::toVec2( const Vector3& src )
    {
        return Vec2(src.x,src.y);
    }

    //-----------------------------------------------------------------------
    Vec3 MGEngineUtility::toVec3( const Vector3& src )
    {
        return Vec3(src.x,src.y,src.z);
    }

    //-----------------------------------------------------------------------
    Qua MGEngineUtility::toQua( const Quaternion& src )
    {
        return Qua(src.w,src.x,src.y,src.z);
    }

    //-----------------------------------------------------------------------
    Vector3 MGEngineUtility::getPosition( ISceneNode* node )
    {
        Vector3 result;
        Vec3 pos;
        node->getPosition( pos );
        MGEngineUtility::toVec3( pos, result );
        return result;
    }

    //-----------------------------------------------------------------------
    Vector3 MGEngineUtility::getDirection( ISceneNode* node )
    {
        Vector3 result;
        Vec3 pos;
        node->getDirection( pos );
        MGEngineUtility::toVec3( pos, result );
        return result;
    }

    //-----------------------------------------------------------------------
    Int MGEngineUtility::getMipMapNum( Int texSize, Int minSize )
    {
		if ( minSize >= texSize )
			return 0;

        Int minMipmap = Ogre::Math::Log2( minSize );
        Int mipmap = Ogre::Math::Log2( texSize ) - minMipmap;
        if ( mipmap < 1)
            mipmap = 1;
        return mipmap;
    }

    //-----------------------------------------------------------------------
    Int MGEngineUtility::calculateIntersectPoint( const Vector2& P0, const Vector2& D0, const Vector2& P1, const Vector2& D1, Vector2& INP)
    {
        Vector2 E = P1 - P0;

        float kross = D0.x * D1.y - D0.y * D1.x;

        //notice: 如果有线段长度非常小的情况，则要修改下面判断算法
        if ( abs( kross ) > 0.001 )
        {
            float s = (E.x * D1.y - E.y * D1.x) / kross;
            if ( (s<0) || (s>1) )
                return 0;

            float t = (E.x * D0.y - E.y * D0.x) / kross;
            if ( (t<0) || (t>1) )
                return 0;

            INP = P0 + s*D0;
            return 1;
        }

        //notice: 如果需要区分平行于重合则在下面加代码
        return 2;
    }

	//-----------------------------------------------------------------------
	Bool MGEngineUtility::clampLineInRect( Vector2& lineStartPos, Vector2& lineEndPos, Ogre::Rect& rect )
	{
		/* // 顶点坐标
		+y
		|
		|
		v0----0----v1
		|          |
		3  [Rect]  1
		|          |
		v2----2----v3----+x
		*/


		Vector2 v0 = Vector2( rect.left, rect.top );
		Vector2 v1 = Vector2( rect.right, rect.top );
		Vector2 v2 = Vector2( rect.left, rect.bottom );
		Vector2 v3 = Vector2( rect.right, rect.bottom );

		//////////////////////////////////////////////////////////////

		Bool    lineStartPosValid = false;
		Bool    lineEndPosValid = false;

		UInt intersectPoint = 0;

		lineStartPosValid = isInRect( lineStartPos, rect );
		lineEndPosValid = isInRect( lineEndPos, rect );

		if ( !lineStartPosValid )
			intersectPoint++;

		if ( !lineEndPosValid )
			intersectPoint++;

		//////////////////////////////////////////////////////////////

		if ( intersectPoint > 0 )
		{
			Vector2 INP[2];
			UInt index = 0;

			//////////////////////////////////////////////////////////////


			// 0 
			if (intersectPoint > 0)
			{
				if ( calculateIntersectPoint(lineStartPos,lineEndPos-lineStartPos,v0,v1-v0,INP[index]) )
				{
					intersectPoint--;
					index++;
				}
			}

			// 1 
			if (intersectPoint > 0)
			{
				if ( calculateIntersectPoint(lineStartPos,lineEndPos-lineStartPos,v3,v1-v3,INP[index]) )
				{
					intersectPoint--;
					index++;
				}
			}

			// 2 
			if (intersectPoint > 0)
			{
				if ( calculateIntersectPoint(lineStartPos,lineEndPos-lineStartPos,v3,v2-v3,INP[index]) )
				{
					intersectPoint--;
					index++;
				}
			}

			// 2 
			if (intersectPoint > 0)
			{
				if ( calculateIntersectPoint(lineStartPos,lineEndPos-lineStartPos,v2,v0-v2,INP[index]) )
				{
					intersectPoint--;
					index++;
				}
			}

			//////////////////////////////////////////////////////////////


			Vector2 lineStartNewPos = lineStartPos;
			Vector2 lineEndNewPos   = lineEndPos;

			if ( index == 0 )
			{
				return false;
			}else
				if ( index == 1 )
				{
					if ( !lineStartPosValid )
					{
						lineStartNewPos = INP[0];
					}else
					{
						lineEndNewPos = INP[0];
					}
				}else
					if ( index == 2 )
					{
						lineStartNewPos = INP[0];
						lineEndNewPos = INP[1];
					}

					//////////////////////////////////////////////////////////////

					Bool xBig = lineStartPos.x > lineEndPos.x;
					Bool yBig = lineStartPos.y > lineEndPos.y;


					Bool xNewBig = lineStartNewPos.x > lineEndNewPos.x;
					Bool yNewBig = lineStartNewPos.y > lineEndNewPos.y;


					if ( (xBig != xNewBig) || (yBig != yNewBig) )
					{
						lineStartPos    = lineEndNewPos;
						lineEndPos      = lineStartNewPos;
					}else
					{
						lineStartPos    = lineStartNewPos;
						lineEndPos      = lineEndNewPos;
					}
		}

		return true;
	}


    //-----------------------------------------------------------------------
    Bool MGEngineUtility::clampLineInRect( Vector2& lineStartPos, Vector2& lineEndPos, Ogre::FloatRect& rect )
    {

        /* // 顶点坐标
        +y
        |
        |
        v0----0----v1
        |          |
        3  [Rect]  1
        |          |
        v2----2----v3----+x
        */


        Vector2 v0 = Vector2( rect.left, rect.top );
        Vector2 v1 = Vector2( rect.right, rect.top );
        Vector2 v2 = Vector2( rect.left, rect.bottom );
        Vector2 v3 = Vector2( rect.right, rect.bottom );

        //////////////////////////////////////////////////////////////

        Bool    lineStartPosValid = false;
        Bool    lineEndPosValid = false;

        UInt intersectPoint = 0;

        lineStartPosValid = isInRect( lineStartPos, rect );
        lineEndPosValid = isInRect( lineEndPos, rect );

        if ( !lineStartPosValid )
            intersectPoint++;

        if ( !lineEndPosValid )
            intersectPoint++;
       
        //////////////////////////////////////////////////////////////

        if ( intersectPoint > 0 )
        {
            Vector2 INP[2];
            UInt index = 0;

            //////////////////////////////////////////////////////////////


            // 0 
            if (intersectPoint > 0)
            {
                if ( calculateIntersectPoint(lineStartPos,lineEndPos-lineStartPos,v0,v1-v0,INP[index]) )
                {
                    intersectPoint--;
                    index++;
                }
            }

            // 1 
            if (intersectPoint > 0)
            {
                if ( calculateIntersectPoint(lineStartPos,lineEndPos-lineStartPos,v3,v1-v3,INP[index]) )
                {
                    intersectPoint--;
                    index++;
                }
            }

            // 2 
            if (intersectPoint > 0)
            {
                if ( calculateIntersectPoint(lineStartPos,lineEndPos-lineStartPos,v3,v2-v3,INP[index]) )
                {
                    intersectPoint--;
                    index++;
                }
            }

            // 2 
            if (intersectPoint > 0)
            {
                if ( calculateIntersectPoint(lineStartPos,lineEndPos-lineStartPos,v2,v0-v2,INP[index]) )
                {
                    intersectPoint--;
                    index++;
                }
            }

            //////////////////////////////////////////////////////////////


            Vector2 lineStartNewPos = lineStartPos;
            Vector2 lineEndNewPos   = lineEndPos;

            if ( index == 0 )
            {
                return false;
            }else
            if ( index == 1 )
            {
                if ( !lineStartPosValid )
                {
                    lineStartNewPos = INP[0];
                }else
                {
                    lineEndNewPos = INP[0];
                }
            }else
            if ( index == 2 )
            {
                lineStartNewPos = INP[0];
                lineEndNewPos = INP[1];
            }

            //////////////////////////////////////////////////////////////

            Bool xBig = lineStartPos.x > lineEndPos.x;
            Bool yBig = lineStartPos.y > lineEndPos.y;


            Bool xNewBig = lineStartNewPos.x > lineEndNewPos.x;
            Bool yNewBig = lineStartNewPos.y > lineEndNewPos.y;


            if ( (xBig != xNewBig) || (yBig != yNewBig) )
            {
                lineStartPos    = lineEndNewPos;
                lineEndPos      = lineStartNewPos;
            }else
            {
                lineStartPos    = lineStartNewPos;
                lineEndPos      = lineEndNewPos;
            }
        }

        return true;
    }

	 //-----------------------------------------------------------------------
	Bool MGEngineUtility::isInRect( Vector2& pos, Ogre::FloatRect& rect )
	{
		if ( pos.x < rect.left )
		{
			return false;
		}
		if ( pos.x > rect.right )
		{
			return false;
		}
		if ( pos.y < rect.top )
		{
			return false;
		}
		if ( pos.y > rect.bottom )
		{
			return false;
		}

		return true;
	}

    //-----------------------------------------------------------------------
    Bool MGEngineUtility::isInRect( Vector2& pos, Ogre::Rect& rect )
    {
        if ( pos.x < rect.left )
        {
            return false;
        }
        if ( pos.x > rect.right )
        {
            return false;
        }
        if ( pos.y < rect.top )
        {
            return false;
        }
        if ( pos.y > rect.bottom )
        {
            return false;
        }

        return true;
    }

    //-----------------------------------------------------------------------
    Bool MGEngineUtility::isTwoVectorCoincide( Real cos, Real tolerance )
    {
        Real tcos;
        tcos = abs( 1 - cos );
        if ( tcos < tolerance )
            return true;

        tcos = abs( 1 + cos );
        if ( tcos < tolerance )
            return true;

        return false;
    }

    //-----------------------------------------------------------------------
    Bool MGEngineUtility::isTwoVectorDirectionEquals( Real cos, Real tolerance )
    {
        cos = abs( 1 - cos );
        if ( cos < tolerance )
            return true;
        else
            return false;
    }

    //-----------------------------------------------------------------------
    Bool MGEngineUtility::isTwoVectorDirectionOpposite( Real cos, Real tolerance )
    {
        cos = abs( 1 + cos );
        if ( cos < tolerance )
            return true;
        else
            return false;
    }

    //-----------------------------------------------------------------------
    Bool MGEngineUtility::isTwoVectorDirectionPositive( Real cos, Real tolerance )
    {
        if ( cos > tolerance )
            return true;
        else
            return false;
    }

    //-----------------------------------------------------------------------
    Bool MGEngineUtility::isTwoVectorCoincide( const Vector3& vec1, const Vector3& vec2, Real tolerance )
    {
        Real cos = getCosBetweenTwoVector( vec1, vec2 );
        return isTwoVectorCoincide( cos, tolerance );
    }

    //-----------------------------------------------------------------------
    Bool MGEngineUtility::isTwoVectorDirectionEquals( const Vector3& vec1, const Vector3& vec2, Real tolerance )
    {
        Real cos = getCosBetweenTwoVector( vec1, vec2 );
        return isTwoVectorDirectionEquals( cos, tolerance );
    }

    //-----------------------------------------------------------------------
    Bool MGEngineUtility::isTwoVectorDirectionOpposite( const Vector3& vec1, const Vector3& vec2, Real tolerance )
    {
        Real cos = getCosBetweenTwoVector( vec1, vec2 );
        return isTwoVectorDirectionOpposite( cos, tolerance );
    }

    //-----------------------------------------------------------------------
    Bool MGEngineUtility::isTwoVectorDirectionPositive( const Vector3& vec1, const Vector3& vec2, Real tolerance )
    {
        Real cos = getCosBetweenTwoVector( vec1, vec2 );
        return isTwoVectorDirectionPositive( cos, tolerance );
    }

    //-----------------------------------------------------------------------
    Bool MGEngineUtility::isTwoVectorCoincide( const Vector2& vec1, const Vector2& vec2, Real tolerance )
    {
        Real cos = getCosBetweenTwoVector( vec1, vec2 );
        return isTwoVectorCoincide( cos, tolerance );
    }

    //-----------------------------------------------------------------------
    Bool MGEngineUtility::isTwoVectorDirectionEquals( const Vector2& vec1, const Vector2& vec2, Real tolerance )
    {
        Real cos = getCosBetweenTwoVector( vec1, vec2 );
        return isTwoVectorDirectionEquals( cos, tolerance );
    }

    //-----------------------------------------------------------------------
    Bool MGEngineUtility::isTwoVectorDirectionOpposite( const Vector2& vec1, const Vector2& vec2, Real tolerance )
    {
        Real cos = getCosBetweenTwoVector( vec1, vec2 );
        return isTwoVectorDirectionOpposite( cos, tolerance );
    }

    //-----------------------------------------------------------------------
    Bool MGEngineUtility::isTwoVectorDirectionPositive( const Vector2& vec1, const Vector2& vec2, Real tolerance )
    {
        Real cos = getCosBetweenTwoVector( vec1, vec2 );
        return isTwoVectorDirectionPositive( cos, tolerance );
    }

    //-----------------------------------------------------------------------
    Real MGEngineUtility::getCosBetweenTwoVector( Vector3 vec1, Vector3 vec2 )
    {
        vec1.normalise();
        vec2.normalise();

        return vec1.dotProduct( vec2 );
    }

    //-----------------------------------------------------------------------
    Real MGEngineUtility::getCosBetweenTwoVector( Vector2 vec1, Vector2 vec2 )
    {
        vec1.normalise();
        vec2.normalise();

        return vec1.dotProduct( vec2 );
    }

    //-----------------------------------------------------------------------
    Vector3 MGEngineUtility::getNormaliseVerticalVector( const Vector3& vector, Vector3 referPlaneVector1, Vector3 referPlaneVector2 )
    {
        Vector3 result;

        if ( isTwoVectorCoincide( referPlaneVector1, referPlaneVector2) )
        {
            return vector;
        }

        Vector3 rpv = referPlaneVector1;
        if ( isTwoVectorCoincide( vector, referPlaneVector1) )
            rpv = referPlaneVector2;

        result = rpv.crossProduct( vector );
        result = result.crossProduct( vector );

        result.normalise();

        return result;
    }

    //-----------------------------------------------------------------------
    Vector3 MGEngineUtility::getNormaliseBisectVector( const Vector3& vec1, const Vector3& vec2, Vector3 referPlaneVector1, Vector3 referPlaneVector2 )
    {
        Vector3 result ;

        if ( isTwoVectorDirectionOpposite( vec1, vec2 ) )
        {
            result = getNormaliseVerticalVector( vec1, referPlaneVector1, referPlaneVector2 );
        }else
        {
            result = vec1 + vec2;
            result.normalise();
        }

        return result;
    }

    //-----------------------------------------------------------------------
    Real MGEngineUtility::getVectorProjection( Vector3 projVec, Vector3 receiveVec )
    {
        Real n;

        projVec.normalise();

        n = receiveVec.dotProduct( projVec );

        return n;
    }

	//-----------------------------------------------------------------------
	Vector3 MGEngineUtility::rotateVector( Vector3 vec, Radian angle, Vector3 axis )
	{
		//Radian rotateAngle = Radian(angle);
		//Vec3 vector = Vec3(vec.x, vec.y, vec.z);
		//Vector3 axisVector =  Vec3(axis.x, axis.y, axis.z);
		Quaternion q;
		q.FromAngleAxis(angle,axis);
		vec = q * vec;

		return vec;
	}

	//-----------------------------------------------------------------------
	Bool MGEngineUtility::isTwoSegmentsIntersect2D( const Vector2& segment1_start, const Vector2& segment1_end, const Vector2& segment2_start, const Vector2& segment2_end )
	{
		// if line1 stand across line2
		bool intersect = false;

		if ( ( segment1_start - segment2_start ).crossProduct( segment2_end - segment2_start ) * 
			 ( segment2_end - segment2_start ).crossProduct( segment1_end - segment2_start ) > 0 )
			intersect = true;

		if ( intersect )
		{
			// if line2 stand across line1
			if ( ( segment2_start - segment1_start ).crossProduct( segment1_end - segment1_start ) * 
				( segment1_end - segment1_start ).crossProduct( segment2_end - segment1_start ) > 0 )
			{
				intersect = true;
			}
			else
			{
				intersect = false;
			}
		}

		return  intersect;		
	}

	//-----------------------------------------------------------------------
	Bool MGEngineUtility::isTwoSegmentsIntersect2D( const Vector2& segment1_start, const Vector2& segment1_end, const Vector2& segment2_start, const Vector2& segment2_end, Vector2& insection_point )
	{
		// 公式取自<<计算机图形学几何工具算法详解>> P173

		// segments line1_start + s * dir_segament1 for s in [0,1], line2_start + t * dir_segment2 for t in [0,1]
		Vector2 dir_segament1 = segment1_end - segment1_start;
		Vector2 dir_segament2 = segment2_end - segment2_start;
		/*Vector2 norm_segament1 = ( line1_end - line1_start ).normalise();
		Vector2 norm_segament2 = ( line2_end - line2_start ).normalise();*/

		Vector2 delta = segment2_start - segment1_start;

		Flt kross = dir_segament1.crossProduct( dir_segament2 );
		
		Flt sqrlen1 = ( segment1_end - segment1_start ).length();
		sqrlen1 *= sqrlen1;

		Flt sqrlen2 = ( segment2_end - segment2_start ).length();
		sqrlen2 *= sqrlen2;

		Flt sqrKross = kross * kross;
		Flt sqrEpsilon = 0.0001f;

		if ( sqrKross > sqrEpsilon * sqrlen1 * sqrlen2 )
		{
			// lines of the segments are not parallel
			Flt s = delta.crossProduct(dir_segament2) / kross;
			if ( s < 0 || s > 1 )
				// intersection of lines is not a point on segment2
				return false;

			Flt t = delta.crossProduct(dir_segament1) / kross;
			if ( t < 0 || t > 1 )
				// intersection of lines is not a point on  segment1;
				return false;

			insection_point = segment1_start + s * dir_segament1;
			return true;
		}

		return false;

		//后面还有平行的时候线段重合的判断， 一会儿加上
	}

	//-----------------------------------------------------------------------
	Bool MGEngineUtility::isSegmentLineIntersect2D( const Vector2& segment_start, const Vector2& segment_end, const Vector2& line_start, const Vector2& line_dir, Vector2& insection_point)
	{
		// segments line1_start + s * dir_segament1 for s in [0,1], line2_start + t * dir_segment2 for t in [0,1]
		Vector2 dir_segament1 = segment_end - segment_start;
		Vector2 line_dir_norm = line_dir.normalisedCopy();
		Vector2 delta = line_start - segment_start;

		Flt kross = dir_segament1.crossProduct( line_dir );
		
		Flt sqrlen1 = ( segment_end - segment_start ).length();
		sqrlen1 *= sqrlen1;
		// normal line 
		Flt sqrlen2 = 1.0f;

		Flt sqrKross = kross * kross;
		Flt sqrEpsilon = 0.0001f;

		if ( sqrKross > sqrEpsilon * sqrlen1 * sqrlen2 )
		{
			Flt s = delta.crossProduct(line_dir_norm) / kross;
			if ( s < 0 || s > 1 )
				// intersection of lines is not a point on segment2
				return false;

			insection_point = segment_start + s * dir_segament1;
			return true;
		}

		return false;
	}

}