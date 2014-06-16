/******************************************************************************/
#ifndef _EFFECTCOMPONENTBINDER_H_
#define _EFFECTCOMPONENTBINDER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ISceneNode.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	// 特效组件绑定器,绑定节点
	/******************************************************************************/
	class EffectComponentBinderSceneNode
	{
	public:

		EffectComponentBinderSceneNode(IEffectComponent* component, ISceneNode* binder = NULL, ISceneNode* beBindeder = NULL,
			IEntity* parentEntity = NULL, Vec3 offsetpos = Vec3(0, 0, 0), Qua offsetqua = Qua(1, 0, 0, 0) );
		virtual ~EffectComponentBinderSceneNode();

	public:
		void	setParentEntity(IEntity* parentEntity);
		void	setBinder(ISceneNode* binder);
		void	setBeBinder(ISceneNode* beBinder);
		void	setOffsetpos(Vec3& offsetpos);
		void	setOffsetQua(Qua& offsetqua);
		void	update();

	private:
		IEffectComponent*	mParentComponent;
		IEntity*			mParentEntity;
		ISceneNode*			mBinder;
		ISceneNode*			mBeBindeder;
		Vec3				mOffsetpos;
		Qua					mOffsetqua;
	};

	/******************************************************************************/
	// 特效组件绑定器,绑定骨骼位置
	/******************************************************************************/
	class EffectComponentBinderBonePos
	{
	public:

		EffectComponentBinderBonePos(IEffectComponent* component, ISceneNode* binder = NULL, IEntity* beBinder = NULL, IEntity* parentEntity = NULL, Str boneName = "");
		virtual ~EffectComponentBinderBonePos();

	public:
		void	setParentEntity(IEntity* parentEntity);

		void	setBinder(ISceneNode* binder);
		void	setbeBinder(IEntity* beBinder);
		void	setBoneName(Str& boneName);
		void	update();

	private:
		IEffectComponent*	mParentComponent;
		IEntity*			mParentEntity;
		ISceneNode*			mBinder;
		IEntity*			mBeBinder;
		Str					mBoneName;
		Bool				bIsBindRootComponent;
	};
}

#endif