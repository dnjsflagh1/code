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
	#note: ���η��߿����б�
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
	#note: ���η��߿���ʾ
	-----------------------------------------------------------------------------
	*/
	class TerrainSquareDecorator : public ITerrainSquareDecorator
	{
	public:
		TerrainSquareDecorator(const String& name, Scene* scene);
		virtual ~TerrainSquareDecorator();

		/// ����
		virtual void        rebuild(void);

		/// ˢ��ģ�� 
		virtual void        refresh(void);

		/// ��������ģ�ʹ�ϸ
		virtual void        setBoldSize(Flt size);
		/// �õ�����ģ�ʹ�ϸ
		virtual Flt         getBoldSize(void);

		/// ������ɫ
		virtual void        setColour(Color colour);
		/// �õ���ɫ
		virtual Color       getColour();

		/// ���ÿɼ���
		virtual void        setVisible(Bool visible);
		/// �õ��ɼ���
		virtual Bool        getVisible();

		////////////////////////////////////////////////////////////////

		/// ���ð뾶
		virtual void        setSideLength(Flt lenght) ;
		/// ���������
		virtual void        setCenter(Vec3 pos) ;

	protected:

		/// ��������ζ���
		void                createOgreManualObject();
		/// ���ٶ���ζ���
		void                destroyOgreManualObject();

		/// �������� 
		void                buildMaterial(void);
		/// �õ��������� 
		Str                 getMaterialName(void);

		/// ����Ogre���ֶ�����ģ�Ͷ���
		void                buildMesh(void);
		/// ����Ogre���ֶ�����ģ�Ͷ���
		void                refreshMesh(void);

		//////////////////////////////////////////////////////

	private:

		//  ��������
		Scene*                  mScene;
		/// ����ģ�ʹ�ϸ
		Flt                     mBoldSize;
		/// ��ɫ 
		ColourValue             mColour;
		/// ���ĵ�
		Vec3                    mCenter;
		/// �߳�
		Flt                     mSideLenght;

		//////////////////////////////////////////////////////

		/// Ogre���ֶ�����ģ�Ͷ���
		Ogre::ManualObject*     mOgreManualObject;
		/// �ڵ����
		MGSceneNode*            mSceneNode;
		/// Ogre���ʽӿ� 
		Ogre::MaterialPtr       mOgreMaterialPtr;                   

		////////////////////////////////////////////////////////

		TerrainSquareLineList   mTerrainSquareLineList;
		Int                     mBuildPointCount;

		////////////////////////////////////////////////////////
	};


}

/******************************************************************************/

#endif