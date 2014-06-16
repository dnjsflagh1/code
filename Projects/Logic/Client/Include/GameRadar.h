#ifndef _GAME_RADAR_H
#define _GAME_RADAR_H
/******************************************************************************/
#include "ClientPreqs.h"
#include "IEngineMain.h"
#include "GameMiniMapManager.h"
#include "IImage.h"
/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//��ϷС��ͼ
	/******************************************************************************/

	class GameRadar : public GameMiniMap
	{
	public:

		////////////////////////////////////////////////////////////////////

		explicit GameRadar( Str name );
		~GameRadar();

		////////////////////////////////////////////////////////////////////

		//��ʼ��
		Bool					init();

		//����ʼ��
		void					unInit();

		//��ȡĳ�ŵ�ͼ
		Bool					loadMap( Str name, Str path, Vec2 visibleWorldSize, Vec2 worldCenter );

		//ж��ĳ�ŵ�ͼ
		void					unloadMap();

		//����
		void					update(Flt delta);

		////////////////////////////////////////////////////////////////////

	public:

		//������ʾ���С�״��UI�ؼ�
		void					setContainerWidget(IImage* image);
		//�ͷ�UI�ؼ��ϵ�С�״�
		void					releaseContainerWidget(IImage* image);

		//��ͼƬλ�õ�����λ��
		Vec2					convertImagePositionToWorldPosition(VecI2 imagePos);
		//�ӿؼ��ϵ����λ�õ�ͼƬλ��
		VecI2					convertContainerPositionToImagePosition(VecI2 containerPos);
		//������λ�õ�ͼƬλ��
		VecI2					convertWorldPositionToImagePosition(Vec3 worldPos);

	protected:

		////////////////////////////////////////////////////////////////////
		//���ƺ���
		////////////////////////////////////////////////////////////////////

		//����ͼ����
		void					drawBackGround();
		//�������н�ɫ
		void					drawAllUnit();
		//�������еĽ�ɫ�� �ڷ�ս��״̬��;
		void					drawPeaceUnit(IdType mainID);
		//�������еĽ�ɫ�� ��ս��״̬��;
		void					drawBattleUnit(IdType mainID, FORCE mainForce);
		//�����Ļ��ƽ�ɫ
		void					drawUnit(Vec3 pos, const Str& iconName, const Str& iconGroup);
		////////////////////////////////////////////////////////////////////

	protected:
		
		//////////////////////////////////////////////////////////////////////
		//�ؼ�
		//////////////////////////////////////////////////////////////////////
		VecI2					mContainerSize;

		//////////////////////////////////////////////////////////////////////
		//��Դ
		//////////////////////////////////////////////////////////////////////

		//��ͼͼƬ��Դ
		Str						mWorldMapName;

		Str						mWorldMapGroup;
		
		//����Լ���ͼ��
		Str						mSelfCharIcon;
		//ͬ�����
		Str						mCompanyCharIcon;
		//�������
		Str						mRivalCharIcon;
		//��������
		Str						mCompanyArmyIcon;
		//�Է�����
		Str						mRivalArmyIcon;
		//������������
		Str						mCompanyBuildIcon;
		//�Է���������
		Str						mRivalBuildIcon;
		//��ͨ����
		Str						mPeaceBuildIcon;
		//NPC
		Str						mNpcIcon;

		//////////////////////////////////////////////////////////////////////
		//��ʱ
		//////////////////////////////////////////////////////////////////////

		//���¼��
		Flt						mUpdateInterval;
		//���¼�ʱ
		Flt						mTimeElapse;
	
	};
}

/******************************************************************************/
#endif