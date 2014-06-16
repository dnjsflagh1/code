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
	/**高精度贴花
	*/
	/******************************************************************************/
	const float decalEpsilon = 0.25F;

	class HighLevelDecal : public IDecal
	{
	public:
		HighLevelDecal(Scene* scene, HighLevelDecalSet* set);
		virtual ~HighLevelDecal();

		/// 设置位置
		virtual void        setPosition(Vec3& pos);
		/// 得到位置
		virtual Vec3&       getPosition();
		/// 设置法线
		virtual void		setNormal(Vec3& normal);
		/// 得到法线
		virtual Vec3&		getNormal();
		/// 设置可见度
		virtual void        setVisible(Bool visible);
		/// 设置可见度
		virtual Bool        getVisible();
		/// 得到类型
		virtual IDecalType	getType(); 
		/// 设置大小
		void				setSize(int size);
		/// 得到大小
		int					getSize();
		//设置改变标志位
		void				setChangeDirty();
		//得到改变标志位
		Bool				getChangeDirty();
		//清空改变标志位
		void				clearChangeDirty();

		//构造ManualObject
		void				buildVertex(Ogre::ManualObject* manualObject);
		void				buildIndex(Ogre::ManualObject* manualObject,UInt index);

		//得到平面高度
		Flt					getPlaneHeight(Vec3& pos, Plane& plane, Flt defaultHeight);
	private:
		void				calculateMaxVertex(int size);
		void				buildVertex1(Ogre::ManualObject* manualObject);

		void				buildIndex1(Ogre::ManualObject* manualObject,UInt index);
		void				buildIndex2(Ogre::ManualObject* manualObject,UInt index);

		//	参数为贴花的中心点,法线,正切,贴花的宽度,高度和深度		
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
		// 做裁剪的六个面.
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
	/**高精度贴花集合
	*/
	/******************************************************************************/
	class HighLevelDecalSet : public IDecalSet
	{
	public:
		HighLevelDecalSet(CChar* name, CChar* texFileName, UInt num, Scene* scene);
		virtual ~HighLevelDecalSet();

		/// 得到贴花接口
		virtual HighLevelDecal*           getDecal(UInt index);
		/// 得到贴花数量
		virtual UInt					  getDecalNum();
		/// 设置大小
		virtual void					  setSize(int size);
		/// 获得大小
		virtual int						  getSize();
		/// 更新贴花
		virtual void					  update( Flt delta );

		virtual void					  preRendering();

		virtual void					  postRendering();
	protected:

		/// 创建模型
		void							  createOgreManualObject();
		/// 销毁模型
		void							  destroyOgreManualObject();

		/// 构建材质
		void							  buildMaterial();
		/// 构建多边形
		void							  buildMesh();

		/// 更新多边形
		void							  updateMesh();

	protected:

		/// 创建贴花对象
		void							  createTerrainDecals();
		/// 销毁贴花对象
		void							  destroyTerrainDecals();

	private:

		Scene*      mScene;

		Str         mName;
		Str         mTexFileName;
		UInt        mDecalNum;

		///节点对象
		MGSceneNode*        mSceneNode;

		/// Ogre材质接口
		Ogre::MaterialPtr   mOgreMaterialPtr;
		/// Ogre的位置显示节点对象
		Ogre::SceneNode*    mOgreDisplaySceneNode;
		/// Ogre可手动创建模型对象
		Ogre::ManualObject* mOgreManualObject;

		/// 贴花对象
		std::vector<HighLevelDecal*> mHighLevelDecals;
	};


}


/******************************************************************************/

#endif