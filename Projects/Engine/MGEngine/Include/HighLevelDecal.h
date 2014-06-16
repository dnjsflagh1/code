/******************************************************************************/
#ifndef _HIGHLEVELDECAL_H
#define _HIGHLEVELDECAL_H
/******************************************************************************/

#include "EnginePreqs.h"
#include "IDecal.h"

/******************************************************************************/
namespace MG
{
	struct ColorRGBA
	{
		float		red;
		float		green;
		float		blue;
		float		alpha;

		ColorRGBA() {}

		ColorRGBA(float r, float g, float b, float a)
		{
			red = r;
			green = g;
			blue = b;
			alpha = a;
		}
	};

	struct Triangle
	{
		unsigned short	index[3];
	};
	inline float DotProduct(const Vec3& p, const Vec3& q)
	{
		return (p.x * q.x + p.y * q.y + p.z * q.z);
	}
	inline float DotProduct(const Vec4& p, const Vec3& q)
	{
		return (p.x * q.x + p.y * q.y + p.z * q.z + p.w);
	}
	inline Vec3 CrossProduct(const Vec3& p, const Vec3& q)
	{
		return Vec3(p.y*q.z-q.y*p.z, p.z*q.x-q.z*p.x, p.x*q.y-p.y*q.x);
	}
	inline float Quyu(float fvalue, float fSzie) // float %
	{
		int cout = fvalue/fSzie;

		if (cout < 0)
		{
			return -1*(fvalue - cout*fSzie);
		}
		else
			return (fvalue - cout*fSzie);
	}
	/******************************************************************************/
	/**�߾�������
	*/
	/******************************************************************************/
	const float decalEpsilon = 0.25F;

	class HighLevelDecal : public IDecal
	{
	public:
		HighLevelDecal(Scene* scene, HighLevelDecalSet* set);
		virtual ~HighLevelDecal();

		/// ����λ��
		virtual void        setPosition(Vec3& pos);
		/// �õ�λ��
		virtual Vec3&       getPosition();
		/// ���÷���
		virtual void		setNormal(Vec3& normal);
		/// �õ�����
		virtual Vec3&		getNormal();
		/// ���ÿɼ���
		virtual void        setVisible(Bool visible);
		/// ���ÿɼ���
		virtual Bool        getVisible();
		/// �õ�����
		virtual IDecalType	getType(); 
		/// ���ô�С
		void				setSize(int size);
		/// �õ���С
		int					getSize();
		//���øı��־λ
		void				setChangeDirty();
		//�õ��ı��־λ
		Bool				getChangeDirty();
		//��ոı��־λ
		void				clearChangeDirty();

		//����ManualObject
		void				buildVertex(Ogre::ManualObject* manualObject);
		void				buildIndex(Ogre::ManualObject* manualObject,UInt index);

		//�õ�ƽ��߶�
		Flt					getPlaneHeight(Vec3& pos, Plane& plane, Flt defaultHeight);
	private:
		void				calculateMaxVertex(int size);
		void				buildVertex1(Ogre::ManualObject* manualObject);

		void				buildIndex1(Ogre::ManualObject* manualObject,UInt index);
		void				buildIndex2(Ogre::ManualObject* manualObject,UInt index);

		//	����Ϊ���������ĵ�,����,����,�����Ŀ��,�߶Ⱥ����		
		void				calculateClipPlane(const Vec3& center, const Vec3& normal, const Vec3& tangent, float width = 1.0f, float height = 0.1f, float depth = 1.0f);
		void				addPolygon(long vertexCount, const Vec3 *vertex, const Vec3 *normal);
		void				clipMesh(long triangleCount, const Triangle *triangle, const Vec3 *vertex, const Vec3 *normal);
		long				clipPolygon(long vertexCount, const Vec3 *vertex, const Vec3 *normal, Vec3 *newVertex, Vec3 *newNormal) const;
		static long			clipPolygonAgainstPlane(const Vec4& plane, long vertexCount, const Vec3 *vertex, const Vec3 *normal, Vec3 *newVertex, Vec3 *newNormal);

	private:

		Scene*              mScene;
		Bool                mDirty;
		HighLevelDecalSet*  mHighLevelDecal;
		int                 mSize;
		Vec3                mPos;
		Vec3				mNormal;
		Bool                mVisible;
		// ���ü���������.
		Vec4				mClipLeftPlane;
		Vec4				mClipRightPlane;
		Vec4				mClipFrontPlane;
		Vec4				mClipBackPlane;
		Vec4				mClipTopPlane;
		Vec4				mClipBottomtPlane;

		long				maxDecalVertices;
		long				maxTriangleCount;
		long				decalVertexCount;
		long				decalTriangleCount;

		Vec3*				vertexArray;
		Vec2*				texcoordArray;
		Triangle*			triangleArray;
		Vec3*				normalArray;

		Vec3                mBuildVertexPos[4];

		Vec3				vertexArraytemp[256];
		Vec2				texcoodArraytemp[256];
		Triangle			triangleArraytemp[256];

		long				clipdecalVertexCount;
		long				clipdecalTriangleCount;
		Triangle*			cliptriangleArray;

		std::multimap<int,const Vec3*> mClipVertexArray;
		std::vector<Triangle> mCliptriangleArray;
	};


	/******************************************************************************/
	/**�߾�����������
	*/
	/******************************************************************************/
	class HighLevelDecalSet : public IDecalSet
	{
	public:
		HighLevelDecalSet(CChar* name, CChar* texFileName, UInt num, Scene* scene);
		virtual ~HighLevelDecalSet();

		/// �õ������ӿ�
		virtual HighLevelDecal*           getDecal(UInt index);
		/// �õ���������
		virtual UInt					  getDecalNum();
		/// ���ô�С
		virtual void					  setSize(int size);
		/// ��ô�С
		virtual int						  getSize();
		/// ��������
		virtual void					  update( Flt delta );

		virtual void					  preRendering();

		virtual void					  postRendering();
	protected:

		/// ����ģ��
		void							  createOgreManualObject();
		/// ����ģ��
		void							  destroyOgreManualObject();

		/// ��������
		void							  buildMaterial();
		/// ���������
		void							  buildMesh();

		/// ���¶����
		void							  updateMesh();

	protected:

		/// ������������
		void							  createTerrainDecals();
		/// ������������
		void							  destroyTerrainDecals();

	private:

		Scene*      mScene;

		Str         mName;
		Str         mTexFileName;
		UInt        mDecalNum;

		///�ڵ����
		MGSceneNode*        mSceneNode;

		/// Ogre���ʽӿ�
		Ogre::MaterialPtr   mOgreMaterialPtr;
		/// Ogre��λ����ʾ�ڵ����
		Ogre::SceneNode*    mOgreDisplaySceneNode;
		/// Ogre���ֶ�����ģ�Ͷ���
		Ogre::ManualObject* mOgreManualObject;

		/// ��������
		std::vector<HighLevelDecal*> mHighLevelDecals;
	};


}


/******************************************************************************/

#endif