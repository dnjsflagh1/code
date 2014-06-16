/******************************************************************************/
#ifndef _EFFECTGRIDSDECORATOR_H_
#define _EFFECTGRIDSDECORATOR_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "EnginePreqs.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//线框对象
	/******************************************************************************/
	class EffectGridDecorator : public IEffectGridsDecorator
	{
	public:
		EffectGridDecorator(const String& name, Scene* scene);
		virtual ~EffectGridDecorator();

		// 构造
		virtual void        rebuild();
		// 刷新
		virtual void        refresh();

		/// 设置粗细 
		virtual void        setBoldSize(Flt size);
		/// 得到粗细
		virtual Flt         getBoldSize(void);

		/// 设置颜色 
		virtual void        setColour(Color colour);
		/// 得到颜色 
		virtual Color       getColour();

		/// 设置可见度
		virtual void        setVisible(Bool visible);
		/// 得到可见度
		virtual Bool        getVisible();

	protected:
		void				build();
		/// 创建多边形对象
		void                createOgreManualObject();
		/// 销毁多边形对象
		void                destroyOgreManualObject();

		/// 构造Ogre可手动创建模型对象
		void                buildMesh(void);
		/// 构造Ogre可手动创建模型对象
		void                refreshMesh(void);
		//////////////////////////////////////////////////////

	private:

		//  场景对象
		Scene*                      mScene;
		/// 折线模型粗细
		Flt                         mBoldSize;

		/// 颜色 
		ColourValue                 mColour;

		//////////////////////////////////////////////////////

		/// Ogre可手动创建模型对象
		Ogre::ManualObject*         mOgreManualObject;
		/// 节点对象
		MGSceneNode*                mSceneNode;

		std::vector<Vec3>			mLinePointList;

		int							mLinePointCount;
	};

}

#endif