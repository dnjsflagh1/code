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
	//�߿����
	/******************************************************************************/
	class EffectGridDecorator : public IEffectGridsDecorator
	{
	public:
		EffectGridDecorator(const String& name, Scene* scene);
		virtual ~EffectGridDecorator();

		// ����
		virtual void        rebuild();
		// ˢ��
		virtual void        refresh();

		/// ���ô�ϸ 
		virtual void        setBoldSize(Flt size);
		/// �õ���ϸ
		virtual Flt         getBoldSize(void);

		/// ������ɫ 
		virtual void        setColour(Color colour);
		/// �õ���ɫ 
		virtual Color       getColour();

		/// ���ÿɼ���
		virtual void        setVisible(Bool visible);
		/// �õ��ɼ���
		virtual Bool        getVisible();

	protected:
		void				build();
		/// ��������ζ���
		void                createOgreManualObject();
		/// ���ٶ���ζ���
		void                destroyOgreManualObject();

		/// ����Ogre���ֶ�����ģ�Ͷ���
		void                buildMesh(void);
		/// ����Ogre���ֶ�����ģ�Ͷ���
		void                refreshMesh(void);
		//////////////////////////////////////////////////////

	private:

		//  ��������
		Scene*                      mScene;
		/// ����ģ�ʹ�ϸ
		Flt                         mBoldSize;

		/// ��ɫ 
		ColourValue                 mColour;

		//////////////////////////////////////////////////////

		/// Ogre���ֶ�����ģ�Ͷ���
		Ogre::ManualObject*         mOgreManualObject;
		/// �ڵ����
		MGSceneNode*                mSceneNode;

		std::vector<Vec3>			mLinePointList;

		int							mLinePointCount;
	};

}

#endif