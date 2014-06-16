/******************************************************************************/
#include "stdafx.h"
#include "HighLevelDecal.h"
#include "Scene.h"
#include "MGSceneNode.h"
/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	//    HighLevelDecal
	/******************************************************************************/
	//---------------------------------------------------------------------
	HighLevelDecal::HighLevelDecal(Scene* scene, HighLevelDecalSet* set)
		:mHighLevelDecal(set)
		,mScene(scene)
		,mSize(1)
		,mDirty(false)
		,mPos(Vec3(0, 0, 0))
		,mNormal(Vec3(0, 0, 0))
		,mClipLeftPlane(Vec4(0, 0, 0, 0))
		,mClipRightPlane(Vec4(0, 0, 0, 0))
		,mClipFrontPlane(Vec4(0, 0, 0, 0))
		,mClipBackPlane(Vec4(0, 0, 0, 0))
		,mClipTopPlane(Vec4(0, 0, 0, 0))
		,mClipBottomtPlane(Vec4(0, 0, 0, 0))
		,decalVertexCount(0)
		,clipdecalVertexCount(0)
		,decalTriangleCount(0)
		,mVisible(true)
		,vertexArray(NULL)
		,texcoordArray(NULL)
		,triangleArray(NULL)
		,cliptriangleArray(NULL)
		,normalArray(NULL)
	{
		for (Int i = 0; i < 4; i++)
		{
			mBuildVertexPos[i] = Vec3(0,0,0);
		}

	}
	//---------------------------------------------------------------------
	HighLevelDecal::~HighLevelDecal()
	{
		delete []vertexArray;
		delete []texcoordArray;
		delete []triangleArray;
		delete []normalArray;
		delete []cliptriangleArray;
	}
	//---------------------------------------------------------------------
	void HighLevelDecal::setPosition(Vec3& pos)
	{
		mPos = pos;
		mCliptriangleArray.clear();
		mClipVertexArray.clear();
		setChangeDirty();
	}
	//---------------------------------------------------------------------
	Vec3& HighLevelDecal::getPosition()
	{
		return mPos;
	}
	//---------------------------------------------------------------------
	void HighLevelDecal::setSize(int size)
	{
		mSize = size;
		mCliptriangleArray.clear();
		mClipVertexArray.clear();
		calculateMaxVertex(size);
		setChangeDirty();
	}
	//---------------------------------------------------------------------
	int HighLevelDecal::getSize()
	{
		return mSize;
	}
	//---------------------------------------------------------------------
	void HighLevelDecal::setNormal( Vec3& normal )
	{
		mNormal = normal;
	}
	//---------------------------------------------------------------------
	Vec3& HighLevelDecal::getNormal()
	{
		return mNormal;
	}
	//---------------------------------------------------------------------
	void HighLevelDecal::setVisible(Bool visible)
	{
		mVisible = visible;
	}
	//---------------------------------------------------------------------
	Bool HighLevelDecal::getVisible()
	{
		return mVisible;
	}
	//---------------------------------------------------------------------
	IDecalType HighLevelDecal::getType()
	{
		return DT_HIGHLEVEL;
	}
	//---------------------------------------------------------------------
	void HighLevelDecal::setChangeDirty()
	{
		mDirty = true;
	}
	//---------------------------------------------------------------------
	Bool HighLevelDecal::getChangeDirty()
	{
		return mDirty;
	}
	//---------------------------------------------------------------------
	void HighLevelDecal::clearChangeDirty()
	{
		mDirty = false;
	}
	//---------------------------------------------------------------------
	Flt HighLevelDecal::getPlaneHeight(Vec3& pos, Plane& plane, Flt defaultHeight)
	{
		if (plane.normal.y!=0)
		{
			return (-plane.normal.x * pos.x  -plane.normal.z * pos.z  - plane.d) / plane.normal.y;
		}
		return defaultHeight;
	}
	//---------------------------------------------------------------------
	void HighLevelDecal::calculateMaxVertex( int size )
	{
		// 直径
		int diameter = 2*size;
		// 地形网格大小
		int gridsize = (int)mScene->getTerrainManager()->getTerrainChunkBlockGridSize();

		int sqrtVertexCount = diameter/gridsize;

		if ( sqrtVertexCount > 0 )
		{
			sqrtVertexCount += 3;
		}
		else
		{
			sqrtVertexCount = 2;
		}

		maxDecalVertices = sqrtVertexCount*sqrtVertexCount;

		maxTriangleCount = Ogre::Math::Sqr( (Ogre::Math::Sqrt(maxDecalVertices) - 1) ) * 2;
	}
	//---------------------------------------------------------------------
	void HighLevelDecal::buildVertex(Ogre::ManualObject* manualObject)
	{
		buildVertex1(manualObject);
	}
	//---------------------------------------------------------------------
	void HighLevelDecal::buildIndex(Ogre::ManualObject* manualObject,UInt index)
	{
		buildIndex1(manualObject,index);
	}
	//---------------------------------------------------------------------
	void HighLevelDecal::buildVertex1(Ogre::ManualObject* manualObject)
	{

		/*
		0    1
		*----*
		|    | 
		2    3 
		*----*
		*/

		if ( getChangeDirty() )
		{
			clearChangeDirty();
			clipdecalVertexCount = 0;

			Flt cx,cy,cz;
			cx = mPos.x;
			cy = mPos.y;
			cz = mPos.z;

			///////////////////////////////////////////////////////////////

			mBuildVertexPos[0] = Vec3(cx-mSize, cy, cz-mSize);
			mBuildVertexPos[1] = Vec3(cx+mSize, cy, cz-mSize);
			mBuildVertexPos[2] = Vec3(cx-mSize, cy, cz+mSize);
			mBuildVertexPos[3] = Vec3(cx+mSize, cy, cz+mSize);

			///////////////////////////////////////////////////////////////
			if (maxDecalVertices != 0)
			{
				vertexArray = new Vec3[maxDecalVertices];
				texcoordArray = new Vec2[maxDecalVertices];
				triangleArray = new Triangle[maxTriangleCount];
				normalArray = new Vec3[maxDecalVertices];

				cliptriangleArray = new Triangle[maxDecalVertices];
			}

			setNormal(Vec3(0.0f, 1.0f, 0.0f));

			Vec3 mTangent;
			mTangent = Vec3(1.0f, 0.0f, 0.0f);
			calculateClipPlane(mPos, mNormal, mTangent, mSize, mSize, mSize);

			int gridsize = (int)mScene->getTerrainManager()->getTerrainChunkBlockGridSize();
			int XVertexGridCount = (mBuildVertexPos[0].x - mBuildVertexPos[1].x)/gridsize;
			int ZVertexGridCount = (mBuildVertexPos[0].z - mBuildVertexPos[2].z)/gridsize;

			if (XVertexGridCount < 0)
				XVertexGridCount = -1 * XVertexGridCount;

			if (ZVertexGridCount < 0)
				ZVertexGridCount = -1 * ZVertexGridCount;

			if ( XVertexGridCount > 0 && ZVertexGridCount > 0)
			{
				XVertexGridCount = XVertexGridCount /*+ 1 */+ 2;
				ZVertexGridCount = ZVertexGridCount /*+ 1 */+ 2;
			}
			else
			{
				XVertexGridCount = 2;
				ZVertexGridCount = 2;
			}

			for ( int z = 0; z < ZVertexGridCount; z++)
			{
				for(int x = 0; x < XVertexGridCount; x++)
				{
					// 顶点
					if ( x%2 == 0 || z%2 == 0)
					{
						if (x%2 == 0 && z%2 != 0)
						{
							if (z/2 == 0)//1
							{
								vertexArray[z*XVertexGridCount + x] = Vec3( mBuildVertexPos[0].x + gridsize*x/2, mBuildVertexPos[0].y , 
									(gridsize - Quyu(mBuildVertexPos[0].z, gridsize)) + mBuildVertexPos[0].z);
							}
							else if( z/2>0 )//3
							{
								vertexArray[z*XVertexGridCount + x] = Vec3( mBuildVertexPos[0].x + gridsize*x/2, mBuildVertexPos[0].y , 
									vertexArray[(z-2)*XVertexGridCount + x].z + gridsize );
							}

						}
						else if (x%2 != 0 && z%2 == 0)
						{
							if (x/2 == 0)
							{
								vertexArray[z*XVertexGridCount + x] = Vec3( (gridsize - Quyu(mBuildVertexPos[0].x, gridsize)) + mBuildVertexPos[0].x, 
									mBuildVertexPos[0].y , mBuildVertexPos[0].z +gridsize*z/2);
							}
							else if( x/2>0 )
							{
								vertexArray[z*XVertexGridCount + x] = Vec3( vertexArray[z*XVertexGridCount + x - 2].x + gridsize, 
									mBuildVertexPos[0].y , vertexArray[z*XVertexGridCount + x - 2].z );
							}
						}
						else // x%2 == 0 && z%2 == 0  // 2
							vertexArray[z*XVertexGridCount + x] = Vec3( mBuildVertexPos[0].x + gridsize*x/2, mBuildVertexPos[0].y , mBuildVertexPos[0].z +gridsize*z/2);
					}
					else // x%2 != 0 && z%2 != 0
					{
						if ( x/2 == 0)
						{
							if ( z/2 == 0)
							{
								vertexArray[z*XVertexGridCount+ x] = Vec3( (gridsize - Quyu(mBuildVertexPos[0].x, gridsize) ) + mBuildVertexPos[0].x, mBuildVertexPos[0].y , 
									(gridsize - Quyu(mBuildVertexPos[0].z, gridsize) ) + mBuildVertexPos[0].z );
							}
							else if ( z/2 >0 )
							{
								vertexArray[z*XVertexGridCount+ x] = Vec3( (gridsize - Quyu(mBuildVertexPos[0].x, gridsize) ) + mBuildVertexPos[0].x, mBuildVertexPos[0].y , 
									vertexArray[(z-2)*XVertexGridCount + x].z + gridsize );
							}

						}
						else if ( x/2 > 0)
						{
							if ( z/2 == 0)
							{
								vertexArray[z*XVertexGridCount+ x] = Vec3( vertexArray[z*XVertexGridCount + x - 2].x + gridsize, mBuildVertexPos[0].y , 
									(gridsize - Quyu(mBuildVertexPos[0].z, gridsize) ) + mBuildVertexPos[0].z );
							}
							else if ( z/2 > 0)
							{
								vertexArray[z*XVertexGridCount+ x] = Vec3( vertexArray[z*XVertexGridCount + x - 2].x + gridsize, mBuildVertexPos[0].y , 
									vertexArray[(z-2)*XVertexGridCount + x].z + gridsize );
							}
						}
					}

					mScene->getCollisionSystem()->getStickHeight(vertexArray[z*XVertexGridCount+ x], vertexArray[z*XVertexGridCount+ x].y);
					vertexArray[z*XVertexGridCount+ x].y += 0.2;
					// 法线
					normalArray[z*XVertexGridCount+ x] = Vec3(0.0f, 1.0f, 0.0f);

					//texcoordArray[z*XVertexGridCount + x] = Vec2((float)x/((float)XVertexGridCount - 1), (float)z/((float)ZVertexGridCount - 1));
					float texcoodX = (float)( (vertexArray[z*XVertexGridCount + x].x-mBuildVertexPos[0].x)/(mBuildVertexPos[1].x - mBuildVertexPos[0].x) );
					float texcoodY = (float)( (vertexArray[z*XVertexGridCount + x].z-mBuildVertexPos[0].z)/(mBuildVertexPos[2].z - mBuildVertexPos[1].z) );
					if (texcoodX < 0)
						texcoodX = -texcoodX;

					if (texcoodY < 0)
						texcoodY = -texcoodY;
					texcoordArray[z*XVertexGridCount + x] = Vec2(texcoodX, texcoodY);
				}
			}

			decalVertexCount = XVertexGridCount * ZVertexGridCount;
			decalTriangleCount = Ogre::Math::Sqr( (Ogre::Math::Sqrt(decalVertexCount) - 1) ) * 2; 

			// 三角形索引
			if (ZVertexGridCount == 2 && XVertexGridCount == 2)
			{
				triangleArray[0].index[0] = 0;
				triangleArray[0].index[1] = 2;
				triangleArray[0].index[2] = 1;

				triangleArray[1].index[0] = 1;
				triangleArray[1].index[1] = 2;
				triangleArray[1].index[2] = 3;
			}
			else
			{
				for (int z = 0; z < ZVertexGridCount - 1; z++)
				{
					for(int x = 0; x < XVertexGridCount - 1; x++)
					{
						triangleArray[(z*(XVertexGridCount - 1) + x) * 2].index[0] = z*XVertexGridCount + x;
						triangleArray[(z*(XVertexGridCount - 1) + x) * 2].index[1] = (z+1)*ZVertexGridCount + x;
						triangleArray[(z*(XVertexGridCount - 1) + x) * 2].index[2] = z*XVertexGridCount + x + 1;

						triangleArray[(z*(XVertexGridCount - 1) + x) * 2 + 1].index[0] = z*XVertexGridCount + x + 1;
						triangleArray[(z*(XVertexGridCount - 1) + x) * 2 + 1].index[1] = (z+1)*XVertexGridCount + x;
						triangleArray[(z*(XVertexGridCount - 1) + x) * 2 + 1].index[2] = (z+1)*XVertexGridCount + x + 1;
					}
				}

			}

			clipMesh(decalTriangleCount, triangleArray, vertexArray, normalArray);
		}

		Vec3 vertex[9];
		std::multimap<int,const Vec3*>::iterator iter = mClipVertexArray.begin();
		for (; iter != mClipVertexArray.end(); iter++)
		{
			int vertexcount = (*iter).first;
			memcpy(vertex, (*iter).second, vertexcount*sizeof(Vec3));
			for(int i = 0; i < vertexcount; i++)
			{
				manualObject->position(Vector3(vertex[i].x, vertex[i].y, vertex[i].z));
			}
		}

		for (Int i=0;i<maxDecalVertices;i++)
		{
			//Vec3& pos   = vertexArray[i];
			Vec2& uv    = texcoordArray[i];

			// test
			//------------------------------------
			//vertexArraytemp[i] = vertexArray[i];
			texcoodArraytemp[i] = texcoordArray[i];
			//------------------------------------

			//manualObject->position( Vector3(pos.x, pos.y + 0.01, pos.z) );
			manualObject->textureCoord( uv.x, uv.y );
		}
		
	}

	//---------------------------------------------------------------------
	void HighLevelDecal::buildIndex1(Ogre::ManualObject* manualObject,UInt index)
	{
		for (int i = 0; i < maxTriangleCount; i++)
		{
			// test
			// -------------------------------------------------------
			triangleArraytemp[i].index[0] = triangleArray[i].index[0];
			triangleArraytemp[i].index[1] = triangleArray[i].index[1];
			triangleArraytemp[i].index[2] = triangleArray[i].index[2];
			// -------------------------------------------------------

			//manualObject->index(triangleArray[i].index[0]);
			//manualObject->index(triangleArray[i].index[1]);
			//manualObject->index(triangleArray[i].index[2]);

			Triangle triangle;
			for (int i = 0; i < mCliptriangleArray.size(); i++)
			{
				manualObject->index(mCliptriangleArray[i].index[0]);
				manualObject->index(mCliptriangleArray[i].index[1]);
				manualObject->index(mCliptriangleArray[i].index[2]);
			}
		}
	}

	//---------------------------------------------------------------------
	void HighLevelDecal::calculateClipPlane( const Vec3& center, const Vec3& normal, const Vec3& tangent, float width, float height, float depth )
	{
		mPos = center;
		mNormal = normal;

		Vec3 binormal = CrossProduct(normal, tangent);

		// Calculate boundary planes
		float d = DotProduct(center, tangent);
		mClipLeftPlane = Vec4(width * 0.5F - d, tangent.x, tangent.y, tangent.z);
		mClipRightPlane = Vec4(width * 0.5F + d, -tangent.x, -tangent.y, -tangent.z);

		d = DotProduct(center, binormal);
		mClipBottomtPlane = Vec4(height * 0.5F - d, binormal.x, binormal.y, binormal.z);
		mClipTopPlane = Vec4(height * 0.5F + d, -binormal.x, -binormal.y, -binormal.z);

		d = DotProduct(center, normal);
		mClipFrontPlane = Vec4(depth + d, -normal.x, -normal.y, -normal.z);
		mClipBackPlane = Vec4(depth - d, normal.x, normal.y, normal.z);
	}

	void HighLevelDecal::addPolygon( long vertexCount, const Vec3 *vertex, const Vec3 *normal )
	{
		long count = clipdecalVertexCount;
		if (count + vertexCount >= maxTriangleCount*3) return;

		// Add polygon as a triangle fan
		Vec3* vertextemp = new Vec3[vertexCount];
		for (int i = 0; i < vertexCount; i++)
		{
			vertextemp[i] = vertex[i];
		}
		mClipVertexArray.insert(make_pair(vertexCount, vertextemp));
		for (long a = 2; a < vertexCount; a++)
		{
			Triangle triangle;
			triangle.index[0] = (unsigned short) 0;
			triangle.index[1] = (unsigned short) (0 + a);
			triangle.index[2] = (unsigned short) (0 + a - 1);
			mCliptriangleArray.push_back(triangle);
		}

		clipdecalVertexCount = count+vertexCount;
	}

	void HighLevelDecal::clipMesh( long triangleCount, const Triangle *triangle, const Vec3 *vertex, const Vec3 *normal )
	{
		Vec3		newVertex[9];
		Vec3		newNormal[9];

		Vec3		clipVertex[9];
		Vec3		clipNormal[9];

		// Clip one triangle at a time
		for (long a = 0; a < triangleCount; a++)
		{
			long i1 = triangle[a].index[0];
			long i2 = triangle[a].index[1];
			long i3 = triangle[a].index[2];

			const Vec3& v1 = vertex[i1];
			const Vec3& v2 = vertex[i2];
			const Vec3& v3 = vertex[i3];

			Vec3 cross = CrossProduct(v2 - v1, v3 - v1);
			float dotResult = DotProduct(mNormal, cross);
			float crossLength = cross.length();
			if (DotProduct(mNormal, cross) > decalEpsilon * cross.length())
			{
				newVertex[0] = v1;
				newVertex[1] = v2;
				newVertex[2] = v3;

				newNormal[0] = normal[i1];
				newNormal[1] = normal[i2];
				newNormal[2] = normal[i3];

				//long count = clipPolygon(3, newVertex, newNormal, clipVertex, clipNormal);
				//if (count != 0)
				//mClipVertexArray.insert(make_pair(3, newVertex));
				addPolygon(3, newVertex, newNormal);
			}
		}
	}

	long HighLevelDecal::clipPolygon( long vertexCount, const Vec3 *vertex, const Vec3 *normal, Vec3 *newVertex, Vec3 *newNormal ) const
	{
		Vec3		tempVertex[9];
		Vec3		tempNormal[9];

		// Clip against all six planes
		long count = clipPolygonAgainstPlane(mClipLeftPlane, vertexCount, vertex, normal, tempVertex, tempNormal);
		if (count != 0)
		{
			count = clipPolygonAgainstPlane(mClipRightPlane, count, tempVertex, tempNormal, newVertex, newNormal);
			if (count != 0)
			{
				count = clipPolygonAgainstPlane(mClipBottomtPlane, count, newVertex, newNormal, tempVertex, tempNormal);
				if (count != 0)
				{
					count = clipPolygonAgainstPlane(mClipTopPlane, count, tempVertex, tempNormal, newVertex, newNormal);
					if (count != 0)
					{
						count = clipPolygonAgainstPlane(mClipBackPlane, count, newVertex, newNormal, tempVertex, tempNormal);
						if (count != 0)
						{
							count = clipPolygonAgainstPlane(mClipFrontPlane, count, tempVertex, tempNormal, newVertex, newNormal);
						}
					}
				}
			}
		}

		return (count);
	}

	long HighLevelDecal::clipPolygonAgainstPlane( const Vec4& plane, long vertexCount, const Vec3 *vertex, const Vec3 *normal, Vec3 *newVertex, Vec3 *newNormal )
	{
		bool	negative[10];

		// Classify vertices
		long negativeCount = 0;
		for (long a = 0; a < vertexCount; a++)
		{
			bool neg = (DotProduct(plane, vertex[a]) < 0.0F);
			negative[a] = neg;
			negativeCount += neg;
		}

		// Discard this polygon if it's completely culled
		if (negativeCount == vertexCount) return (0);

		long count = 0;
		for (long b = 0; b < vertexCount; b++)
		{
			// c is the index of the previous vertex
			long c = (b != 0) ? b - 1 : vertexCount - 1;

			if (negative[b])
			{
				if (!negative[c])
				{
					// Current vertex is on negative side of plane,
					// but previous vertex is on positive side.
					const Vec3& v1 = vertex[c];
					const Vec3& v2 = vertex[b];
					float t = DotProduct(plane, v1) / (plane.x * (v1.x - v2.x) + plane.y * (v1.y - v2.y) + plane.z * (v1.z - v2.z));
					newVertex[count] = v1 * (1.0F - t) + v2 * t;

					const Vec3& n1 = normal[c];
					const Vec3& n2 = normal[b];
					newNormal[count] = n1 * (1.0F - t) + n2 * t;
					count++;
				}
			}
			else
			{
				if (negative[c])
				{
					// Current vertex is on positive side of plane,
					// but previous vertex is on negative side.
					const Vec3& v1 = vertex[b];
					const Vec3& v2 = vertex[c];
					float t = DotProduct(plane, v1) / (plane.x * (v1.x - v2.x) + plane.y * (v1.y - v2.y) + plane.z * (v1.z - v2.z));
					newVertex[count] = v1 * (1.0F - t) + v2 * t;

					const Vec3& n1 = normal[b];
					const Vec3& n2 = normal[c];
					newNormal[count] = n1 * (1.0F - t) + n2 * t;
					count++;
				}

				// Include current vertex
				newVertex[count] = vertex[b];
				newNormal[count] = normal[b];
				count++;
			}
		}

		// Return number of vertices in clipped polygon
		return (count);
	}
	
	/******************************************************************************/
	//    HighLevelDecalSet
	/******************************************************************************/
	HighLevelDecalSet::HighLevelDecalSet(CChar* name, CChar* texFileName, UInt num, Scene* scene)
		:mOgreDisplaySceneNode(NULL)
		,mOgreManualObject(NULL)
		,mSceneNode(NULL)
		,mScene(scene)
		,mName(name)
		,mTexFileName(texFileName)
		,mDecalNum(num)
	{
		createTerrainDecals();

		buildMaterial();
		createOgreManualObject();
		buildMesh();
	}

	//---------------------------------------------------------------------
	HighLevelDecalSet::~HighLevelDecalSet()
	{
		destroyTerrainDecals();

		destroyOgreManualObject();
	}

	//---------------------------------------------------------------------
	void HighLevelDecalSet::update( Flt delta )
	{
		
	}
	//---------------------------------------------------------------------
	void HighLevelDecalSet::preRendering()
	{
		updateMesh();
	}
	//---------------------------------------------------------------------
	void HighLevelDecalSet::postRendering()
	{

	}
	//---------------------------------------------------------------------
	HighLevelDecal* HighLevelDecalSet::getDecal(UInt index)
	{
		if ( (index >=0) && (index < mDecalNum) )
			return mHighLevelDecals[index];

		return NULL;
	}

	//---------------------------------------------------------------------
	UInt HighLevelDecalSet::getDecalNum()
	{
		return mDecalNum;
	}
	//---------------------------------------------------------------------
	void HighLevelDecalSet::setSize(int size)
	{
		for ( UInt i=0; i<mDecalNum; i++ )
		{
			mHighLevelDecals[i]->setSize(size);
		}
		buildMesh();
	}

	int HighLevelDecalSet::getSize()
	{
		if (mDecalNum)
		{
			return mHighLevelDecals[0]->getSize();
		}
		return 0;
	}
	//---------------------------------------------------------------------
	void HighLevelDecalSet::createTerrainDecals()
	{
		for ( UInt i=0; i<mDecalNum; i++ )
		{
			HighLevelDecal* decal = MG_NEW HighLevelDecal(mScene,this);
			mHighLevelDecals.push_back(decal);
		}
	}

	//---------------------------------------------------------------------
	void HighLevelDecalSet::destroyTerrainDecals()
	{
		for ( UInt i=0; i<mDecalNum; i++ )
		{
			MG_SAFE_DELETE(mHighLevelDecals[i]);
		}
		mHighLevelDecals.clear();
	}

	//---------------------------------------------------------------------
	void HighLevelDecalSet::buildMaterial()
	{
		Str matName = "DecalSet_Material_" + mName;

		/// 得到或创建材质
		mOgreMaterialPtr = Ogre::MaterialManager::getSingleton().getByName(matName);
		if (mOgreMaterialPtr.isNull())
		{
			mOgreMaterialPtr = Ogre::MaterialManager::getSingleton().create(matName, 
				Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
			mOgreMaterialPtr->setReceiveShadows( false );
		}

		/// 得到渲染通道
		Ogre::Pass* pass = mOgreMaterialPtr->getTechnique(0)->getPass(0);
		pass->setLightingEnabled(false);
		pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
		pass->setSceneBlending(Ogre::SBF_SOURCE_ALPHA,Ogre::SBF_ONE_MINUS_SOURCE_ALPHA);
		pass->setCullingMode(Ogre::CULL_NONE);
		pass->setDepthCheckEnabled(true);
		pass->setDepthWriteEnabled(false);
		pass->setDepthBias(0.005);

		/// 得到或创建贴图单元
		Ogre::TextureUnitState* textureUnitState = NULL;
		if ( pass->getNumTextureUnitStates() == 0 )
		{
			textureUnitState = pass->createTextureUnitState( mTexFileName );
			textureUnitState->setTextureAddressingMode( TextureUnitState::TAM_CLAMP );
		}else
		{
			textureUnitState = pass->getTextureUnitState(0);
			textureUnitState->setTextureName( mTexFileName );
			textureUnitState->setTextureAddressingMode(TextureUnitState::TAM_CLAMP);
		}
	}

	//---------------------------------------------------------------------
	void HighLevelDecalSet::createOgreManualObject()
	{
		mOgreManualObject = mScene->getOgreSceneManager()->createManualObject( mName );
		mOgreManualObject->setCastShadows(false);
		//mOgreManualObject->setRenderQueueGroup(Ogre::RENDER_QUEUE_3);
		mOgreManualObject->setRenderQueueGroup(Ogre::RENDER_QUEUE_6);

		//创建实体节点
		mSceneNode = MG_NEW MGSceneNode(mScene->getOgreSceneManager()->getRootSceneNode(),mScene);
		//绑定实体
		mSceneNode->getOgreSceneNode()->attachObject( mOgreManualObject );
	}

	//---------------------------------------------------------------------
	void HighLevelDecalSet::destroyOgreManualObject()
	{
		//销毁实体对象
		if ( mOgreManualObject )
		{
			mScene->getOgreSceneManager()->destroyManualObject(mOgreManualObject);
			mOgreManualObject = NULL;
		}

		//销毁实体节点
		MG_SAFE_DELETE( mSceneNode );
	}

	//---------------------------------------------------------------------
	void HighLevelDecalSet::buildMesh()
	{
		mOgreManualObject->clear();

		mOgreManualObject->setDynamic(true);

		mOgreManualObject->begin(  mOgreMaterialPtr->getName(), Ogre::RenderOperation::OT_TRIANGLE_LIST );

		{
			// vertex
			HighLevelDecal* decal = NULL;
			for (UInt i=0; i < mDecalNum; i++ )
			{
				decal = mHighLevelDecals[i];
				if (decal->getVisible())
				{
					decal->buildVertex(mOgreManualObject);
				}
			}

			// index
			UInt index = 0;
			for ( UInt i=0; i < mDecalNum; i++ )
			{
				decal = mHighLevelDecals[i];
				if (decal->getVisible())
				{
					decal->buildIndex(mOgreManualObject,index);
					index++;
				}
			}
		}

		mOgreManualObject->end();
	}

	//---------------------------------------------------------------------
	void HighLevelDecalSet::updateMesh()
	{
		if ( mOgreManualObject )
		{
			mOgreManualObject->beginUpdate(0);

			// vertex
			HighLevelDecal* decal = NULL;
			for ( UInt i=0; i<mDecalNum; i++ )
			{
				decal = mHighLevelDecals[i];
				if (decal->getVisible())
				{
					decal->buildVertex(mOgreManualObject);
				}
			}

			// index
			UInt index = 0;
			for ( UInt i=0; i < mDecalNum; i++ )
			{
				decal = mHighLevelDecals[i];
				if (decal->getVisible())
				{
					decal->buildIndex(mOgreManualObject,index);
					index++;
				}
			}

			mOgreManualObject->end();
		}
	}


}