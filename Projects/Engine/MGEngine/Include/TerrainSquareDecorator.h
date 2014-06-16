/******************************************************************************/
#ifndef _TERRAINSQUAREDECORATOR_H_
#define _TERRAINSQUAREDECORATOR_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IWireframeManager.h"

/******************************************************************************/

namespace MG
{

	/**
	-----------------------------------------------------------------------------
	#note: 地形方线框线列表
	-----------------------------------------------------------------------------
	*/
	class TerrainSquareLineList
	{
	public:
		TerrainSquareLineList();

		void    build( TerrainManager* terrainMgr , Vec3 center, Flt lenght, Flt gap = 1 );
		std::vector<Vec3> mSquareLine;
		Flt  mLastBuildTime;
		Flt  mOffset;
	};


	/**
	-----------------------------------------------------------------------------
	#note: 地形方线框显示
	-----------------------------------------------------------------------------
	*/
	class TerrainSquareDecorator : public ITerrainSquareDecorator
	{
	public:
		TerrainSquareDecorator(const String& name, Scene* scene);
		virtual ~TerrainSquareDecorator();

		/// 构造
		virtual void        rebuild(void);

		/// 刷新模型 
		virtual void        refresh(void);

		/// 设置折线模型粗细
		virtual void        setBoldSize(Flt size);
		/// 得到折线模型粗细
		virtual Flt         getBoldSize(void);

		/// 设置颜色
		virtual void        setColour(Color colour);
		/// 得到颜色
		virtual Color       getColour();

		/// 设置可见度
		virtual void        setVisible(Bool visible);
		/// 得到可见度
		virtual Bool        getVisible();

		////////////////////////////////////////////////////////////////

		/// 设置半径
		virtual void        setSideLength(Flt lenght) ;
		/// 设置坐标点
		virtual void        setCenter(Vec3 pos) ;

	protected:

		/// 创建多边形对象
		void                createOgreManualObject();
		/// 销毁多边形对象
		void                destroyOgreManualObject();

		/// 创建材质 
		void                buildMaterial(void);
		/// 得到材质名字 
		Str                 getMaterialName(void);

		/// 构造Ogre可手动创建模型对象
		void                buildMesh(void);
		/// 构造Ogre可手动创建模型对象
		void                refreshMesh(void);

		//////////////////////////////////////////////////////

	private:

		//  场景对象
		Scene*                  mScene;
		/// 折线模型粗细
		Flt                     mBoldSize;
		/// 颜色 
		ColourValue             mColour;
		/// 中心点
		Vec3                    mCenter;
		/// 边长
		Flt                     mSideLenght;

		//////////////////////////////////////////////////////

		/// Ogre可手动创建模型对象
		Ogre::ManualObject*     mOgreManualObject;
		/// 节点对象
		MGSceneNode*            mSceneNode;
		/// Ogre材质接口 
		Ogre::MaterialPtr       mOgreMaterialPtr;                   

		////////////////////////////////////////////////////////

		TerrainSquareLineList   mTerrainSquareLineList;
		Int                     mBuildPointCount;

		////////////////////////////////////////////////////////
	};


}

/******************************************************************************/

#endif