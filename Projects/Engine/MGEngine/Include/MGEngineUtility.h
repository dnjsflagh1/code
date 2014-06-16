/******************************************************************************/
#ifndef _MGENGINEUTILITY_H_
#define _MGENGINEUTILITY_H_
/******************************************************************************/

#include "EnginePreqs.h"

/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //引擎通用工具集
    /******************************************************************************/
    class MGEngineUtility
    {
    public:

        //类型转换

        static void         toVec2( const Vec3& src, Vector3& des );
        static void         toVec3( const Vec3& src, Vector3& des );
        static Vector2      toVec2( const Vec3& src );
        static Vector3      toVec3( const Vec3& src );

        static void         toVec2( const Vector3& src, Vec3& des );
        static void         toVec3( const Vector3& src, Vec3& des );
        static Vec2         toVec2( const Vector3& src );
        static Vec3         toVec3( const Vector3& src );

        static Qua          toQua( const Quaternion& src );

        static Vector3      getPosition( ISceneNode* node );
        static Vector3      getDirection( ISceneNode* node );


        ///////////////////////////////////////////////////////////////////////////////////////////////

        static Int          getMipMapNum( Int texSize, Int minSize = 32 );
        
        ///////////////////////////////////////////////////////////////////////////////////////////////


        /** 
            #note: 计算2线段相交点  

            #note: P0: 线段1的起始点
            D0: 线段1的方向和长度
            线段1表示为 P0 + s*D0

            P1: 线段2的起始点
            D1: 线段2的方向和长度
            线段1表示为 P1 + t*D1

            INP: 如果相交返回相交点

            #note: 返回值为0: 不相交
            返回值为1: 相交
            返回值为2: 重叠或平行	
        */
        static Int calculateIntersectPoint( const Vector2& P0, const Vector2& D0, const Vector2& P1, const Vector2& D1, Vector2& INP);

        // 截断线段在区域内
		static Bool clampLineInRect( Vector2& lineStartPos, Vector2& lineEndPos, Ogre::Rect& rect );

        static Bool clampLineInRect( Vector2& lineStartPos, Vector2& lineEndPos, Ogre::FloatRect& rect );
        // 截断点在区域内
        static Bool isInRect( Vector2& pos, Ogre::Rect& rect );

		static Bool isInRect( Vector2& pos, Ogre::FloatRect& rect );

        /// 判断2个矢量是否重合
        static Bool isTwoVectorCoincide( Real cos, Real tolerance = 0.01 );
        /// 判断2个矢量是否指向同一个方向 
        static Bool isTwoVectorDirectionEquals( Real cos, Real tolerance = 0.01 );
        /// 判断2个矢量是否指向相反的方向 
        static Bool isTwoVectorDirectionOpposite( Real cos, Real tolerance = 0.01 );
        /// 判断2个矢量是否在一个半轴 
        static Bool isTwoVectorDirectionPositive( Real cos, Real tolerance = 0.01 );

        /// 判断2个矢量是否重合 
        static Bool isTwoVectorCoincide( const Vector3& vec1, const Vector3& vec2, Real tolerance = 0.01 );
        /// 判断2个矢量是否指向同一个方向 
        static Bool isTwoVectorDirectionEquals( const Vector3& vec1, const Vector3& vec2, Real tolerance = 0.01 );
        /// 判断2个矢量是否指向相反的方向 
        static Bool isTwoVectorDirectionOpposite( const Vector3& vec1, const Vector3& vec2, Real tolerance = 0.01 );
        /// 判断2个矢量是否在一个半轴 
        static Bool isTwoVectorDirectionPositive( const Vector3& vec1, const Vector3& vec2, Real tolerance = 0.01 );

        /// 判断2个矢量是否重合 
        static Bool isTwoVectorCoincide( const Vector2& vec1, const Vector2& vec2, Real tolerance = 0.01 );
        /// 判断2个矢量是否指向同一个方向 
        static Bool isTwoVectorDirectionEquals( const Vector2& vec1, const Vector2& vec2, Real tolerance = 0.01 );
        /// 判断2个矢量是否指向相反的方向 
        static Bool isTwoVectorDirectionOpposite( const Vector2& vec1, const Vector2& vec2, Real tolerance = 0.01 );
        /// 判断2个矢量是否指向相反的方向 
        static Bool isTwoVectorDirectionPositive( const Vector2& vec1, const Vector2& vec2, Real tolerance = 0.01 );
		/// 判断2条线段是否相交
		static Bool isTwoSegmentsIntersect2D( const Vector2& segment1_start, const Vector2& segment1_end, const Vector2& segment2_start, const Vector2& segment2_end);
		/// 判断2条线段是否相交, 求出交点
		static Bool isTwoSegmentsIntersect2D( const Vector2& segment1_start, const Vector2& segment1_end, const Vector2& segment2_start, const Vector2& segment2_end, Vector2& insection_point);
		/// 判断线段和直线是否相交, 求出交点
		static Bool isSegmentLineIntersect2D( const Vector2& segment_start, const Vector2& segment_end, const Vector2& line_start, const Vector2& line_dir, Vector2& insection_point);
		
        /// 得到2个角度的余弦 
        static Real getCosBetweenTwoVector( Vector3 vec1, Vector3 vec2 );
        /// 得到2个角度的余弦 
        static Real getCosBetweenTwoVector( Vector2 vec1, Vector2 vec2 );

        /// 得到指定方向的垂线
        static Vector3 getNormaliseVerticalVector( const Vector3& vector, Vector3 referPlaneVector1 = Vector3::UNIT_X, Vector3 referPlaneVector2  = Vector3::UNIT_Z );

        /// 得到平分线
        static Vector3 getNormaliseBisectVector( const Vector3& vec1, const Vector3& vec2, Vector3 referPlaneVector1 = Vector3::UNIT_X, Vector3 referPlaneVector2  = Vector3::UNIT_Z );

        /// 得到2个方向的投影
        static Real getVectorProjection( Vector3 projVec, Vector3 receiveVec );

		static Vector3 rotateVector( Vector3 vec, Radian angle, Vector3 axis = Vector3::UNIT_Y);


    protected:


    };

    

}

/******************************************************************************/

#endif

