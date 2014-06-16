/******************************************************************************/
#ifndef _MGENGINEUTILITY_H_
#define _MGENGINEUTILITY_H_
/******************************************************************************/

#include "EnginePreqs.h"

/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //����ͨ�ù��߼�
    /******************************************************************************/
    class MGEngineUtility
    {
    public:

        //����ת��

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
            #note: ����2�߶��ཻ��  

            #note: P0: �߶�1����ʼ��
            D0: �߶�1�ķ���ͳ���
            �߶�1��ʾΪ P0 + s*D0

            P1: �߶�2����ʼ��
            D1: �߶�2�ķ���ͳ���
            �߶�1��ʾΪ P1 + t*D1

            INP: ����ཻ�����ཻ��

            #note: ����ֵΪ0: ���ཻ
            ����ֵΪ1: �ཻ
            ����ֵΪ2: �ص���ƽ��	
        */
        static Int calculateIntersectPoint( const Vector2& P0, const Vector2& D0, const Vector2& P1, const Vector2& D1, Vector2& INP);

        // �ض��߶���������
		static Bool clampLineInRect( Vector2& lineStartPos, Vector2& lineEndPos, Ogre::Rect& rect );

        static Bool clampLineInRect( Vector2& lineStartPos, Vector2& lineEndPos, Ogre::FloatRect& rect );
        // �ضϵ���������
        static Bool isInRect( Vector2& pos, Ogre::Rect& rect );

		static Bool isInRect( Vector2& pos, Ogre::FloatRect& rect );

        /// �ж�2��ʸ���Ƿ��غ�
        static Bool isTwoVectorCoincide( Real cos, Real tolerance = 0.01 );
        /// �ж�2��ʸ���Ƿ�ָ��ͬһ������ 
        static Bool isTwoVectorDirectionEquals( Real cos, Real tolerance = 0.01 );
        /// �ж�2��ʸ���Ƿ�ָ���෴�ķ��� 
        static Bool isTwoVectorDirectionOpposite( Real cos, Real tolerance = 0.01 );
        /// �ж�2��ʸ���Ƿ���һ������ 
        static Bool isTwoVectorDirectionPositive( Real cos, Real tolerance = 0.01 );

        /// �ж�2��ʸ���Ƿ��غ� 
        static Bool isTwoVectorCoincide( const Vector3& vec1, const Vector3& vec2, Real tolerance = 0.01 );
        /// �ж�2��ʸ���Ƿ�ָ��ͬһ������ 
        static Bool isTwoVectorDirectionEquals( const Vector3& vec1, const Vector3& vec2, Real tolerance = 0.01 );
        /// �ж�2��ʸ���Ƿ�ָ���෴�ķ��� 
        static Bool isTwoVectorDirectionOpposite( const Vector3& vec1, const Vector3& vec2, Real tolerance = 0.01 );
        /// �ж�2��ʸ���Ƿ���һ������ 
        static Bool isTwoVectorDirectionPositive( const Vector3& vec1, const Vector3& vec2, Real tolerance = 0.01 );

        /// �ж�2��ʸ���Ƿ��غ� 
        static Bool isTwoVectorCoincide( const Vector2& vec1, const Vector2& vec2, Real tolerance = 0.01 );
        /// �ж�2��ʸ���Ƿ�ָ��ͬһ������ 
        static Bool isTwoVectorDirectionEquals( const Vector2& vec1, const Vector2& vec2, Real tolerance = 0.01 );
        /// �ж�2��ʸ���Ƿ�ָ���෴�ķ��� 
        static Bool isTwoVectorDirectionOpposite( const Vector2& vec1, const Vector2& vec2, Real tolerance = 0.01 );
        /// �ж�2��ʸ���Ƿ�ָ���෴�ķ��� 
        static Bool isTwoVectorDirectionPositive( const Vector2& vec1, const Vector2& vec2, Real tolerance = 0.01 );
		/// �ж�2���߶��Ƿ��ཻ
		static Bool isTwoSegmentsIntersect2D( const Vector2& segment1_start, const Vector2& segment1_end, const Vector2& segment2_start, const Vector2& segment2_end);
		/// �ж�2���߶��Ƿ��ཻ, �������
		static Bool isTwoSegmentsIntersect2D( const Vector2& segment1_start, const Vector2& segment1_end, const Vector2& segment2_start, const Vector2& segment2_end, Vector2& insection_point);
		/// �ж��߶κ�ֱ���Ƿ��ཻ, �������
		static Bool isSegmentLineIntersect2D( const Vector2& segment_start, const Vector2& segment_end, const Vector2& line_start, const Vector2& line_dir, Vector2& insection_point);
		
        /// �õ�2���Ƕȵ����� 
        static Real getCosBetweenTwoVector( Vector3 vec1, Vector3 vec2 );
        /// �õ�2���Ƕȵ����� 
        static Real getCosBetweenTwoVector( Vector2 vec1, Vector2 vec2 );

        /// �õ�ָ������Ĵ���
        static Vector3 getNormaliseVerticalVector( const Vector3& vector, Vector3 referPlaneVector1 = Vector3::UNIT_X, Vector3 referPlaneVector2  = Vector3::UNIT_Z );

        /// �õ�ƽ����
        static Vector3 getNormaliseBisectVector( const Vector3& vec1, const Vector3& vec2, Vector3 referPlaneVector1 = Vector3::UNIT_X, Vector3 referPlaneVector2  = Vector3::UNIT_Z );

        /// �õ�2�������ͶӰ
        static Real getVectorProjection( Vector3 projVec, Vector3 receiveVec );

		static Vector3 rotateVector( Vector3 vec, Radian angle, Vector3 axis = Vector3::UNIT_Y);


    protected:


    };

    

}

/******************************************************************************/

#endif

