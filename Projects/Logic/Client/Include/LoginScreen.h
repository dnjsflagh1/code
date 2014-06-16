/******************************************************************************/
#ifndef _LOGINSCREEN_H_
#define _LOGINSCREEN_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "GameSettingManager.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    // ��Ϸ������ع���
    /******************************************************************************/
    class LoginScreen : public IScreen, public IAnimationControllerListener, public ResourceLoadListener, public GameSettingManagerListener
    {
    public:

        SINGLETON_INSTANCE(LoginScreen)
        LoginScreen();
        virtual ~LoginScreen();

        virtual void		update( Flt delta );
        virtual bool		isFinished();
        virtual void		onEnter();
        virtual void		onLeave();

		///////////////////////////////////////////////////////////////

		// ���¼���

	public:
		
		// �����߼������¼�

        virtual void		onStartLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType );
        virtual void		onEndLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType );
        virtual void		onUnloadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType );

		// ��Դ��ȡ��ص��¼�

		virtual void		onInitResourceLoadListener();
		virtual void		onClearResourceLoadListener();

		virtual void		preLoadTerrainChunk( UInt index, UInt total );
		virtual void		postLoadTerrainChunk( UInt index, UInt total );

		virtual void		preloadObject( UInt index, UInt total );
		virtual void		postloadObject( ISceneObject* entity, UInt index, UInt total );

		virtual void		preloadCustomObject( UInt index, UInt total );
		virtual void		postloadCustomObject( ISceneObject* entity, UInt index, UInt total );

		// ��Ϸ������ص��¼�
		virtual void		onApplyDisplayConfig();

	protected:

		Flt					mCustomObjectProgress;
		
	protected:

		// �������¼�

		virtual void		onAnimationStop(CChar* animName);

		//////////////////////////////////////////////////////////////////////////////

	public:


		//������ʵ�����

		// entity index
		enum
		{
			FOCUS_ENTITY_SEIRYU = 0,
			FOCUS_ENTITY_BIAKKO,
			FOCUS_ENTITY_SUSAKU,
			FOCUS_ENTITY_KENBU,
			FOCUS_ENTITY_MAX
		};

		enum
		{
			//create Clan 

			ENTITY_SCENE_CENTER = 0,

			ENTITY_SUSAKU,
			ENTITY_BIAKKO,
			ENTITY_KENBU,
			ENTITY_SEIRYU,

			ENTITY_SUSAKU_FRONT,
			ENTITY_BIAKKO_FRONT,
			ENTITY_KENBU_FRONT,
			ENTITY_SEIRYU_FRONT,

			ENTITY_SUSAKU_BACK,
			ENTITY_BIAKKO_BACK,
			ENTITY_KENBU_BACK,
			ENTITY_SEIRYU_BACK,

			ENTITY_SKYDOM_1,
			ENTITY_SKYDOM_2,
			ENTITY_SKYDOM_3,

			//create\select general 

			ENTITY_CAMERA_1,
			ENTITY_CAMERA_2,
			ENTITY_CAMERA_TARGET_1,
			ENTITY_CAMERA_TARGET_2,

			ENTITY_HALL_PART_1,
			ENTITY_HALL_PART_2,

			ENTITY_CRECHAR_SEAT_POINT,

			ENTITY_CRECHAR_STAND_POINT_1,
			ENTITY_CRECHAR_STAND_POINT_2,
			ENTITY_CRECHAR_STAND_POINT_3,
			ENTITY_CRECHAR_STAND_POINT_4,
			ENTITY_CRECHAR_STAND_POINT_5,
			ENTITY_CRECHAR_STAND_POINT_6,
			ENTITY_CRECHAR_STAND_POINT_7,
			ENTITY_CRECHAR_STAND_POINT_8,

			ENTITY_CRECHAR_STAND_ROW_1,
			ENTITY_CRECHAR_STAND_ROW_2,
			ENTITY_CRECHAR_STAND_ROW_3,
			ENTITY_CRECHAR_STAND_ROW_4,

			ENTITY_SELCHAR_SEAT_POINT,
			ENTITY_SELCHAR_SEAT_POINT_LEFT,
			ENTITY_SELCHAR_SEAT_POINT_RIGHT,

			ENTITY_SELCHAR_STAND_POINT_1,
			ENTITY_SELCHAR_STAND_POINT_2,
			ENTITY_SELCHAR_STAND_POINT_3,
			ENTITY_SELCHAR_STAND_POINT_4,
			ENTITY_SELCHAR_STAND_POINT_5,
			ENTITY_SELCHAR_STAND_POINT_6,
			ENTITY_SELCHAR_STAND_POINT_7,
			ENTITY_SELCHAR_STAND_POINT_8,

			ENTITY_SLOT_MAX,
			
		};

		// ���ʵ��
		IEntity*			getEntity( Int index );
		// ���ʵ��
		IEntity*			getEntity( Str8 name );
		// ���ó���������ɼ�
		void				setAllEntitysVisible( Bool isVisible );

	private:

		//���������б�
		std::vector<Str>	mEntityList;
		
		///////////////////////////////////////////////////////////////

	public:

		//���߼�����

		// ��ȡ�����佫������	
		I32					getTempCharIndex(CCharacterSceneEntity* characterSceneEntity);

		// ��ȡ�����õ��佫
		I32					getSelectCharIndex() { return mSelectedGeneralIndex; }

		// ׼��������Ϸ״̬
		void				prepareJoiningGame();

		// ׼��ѡ��
		void				prepareSelectGeneral(CCharacterSceneEntity* characterSceneEntity);

		// ׼��������ɫ
		void				prepareCreateGeneral();

		// ѡ�н�ɫ
		void				selectGeneral(CCharacterSceneEntity* characterSceneEntity);

		// ͨ�����������ѡ��һ���佫
		void				randomGeneralbyId(U32 randomId);

		// ѡ�н�ɫ�� ��ʱ��ʹ�øú���
		void				selectGeneral2(CCharacterSceneEntity* characterSceneEntity);

	protected:

		//����ģ���ɫ�佫�������б�
		std::map<I32, CPlayerCharacterEntity*>	mTempCharEntityList;

		//ѡ�е�
		I32					mSelectedGeneralIndex;

	public:

		void				clearEnterGameDirty() { mSceneFinishDirty = false;}

		Bool				getEnterGameDirty() { return mSceneFinishDirty; }					

	protected:

		Bool				mSceneFinishDirty;

		///////////////////////////////////////////////////////////////

    public:

		//����������

		// ����ѡ������ĳ���
		Bool				loadCreateClanScene();
		// ����ѡ������ĳ���
		void				destroyCreateClanScene();

		// ����ѡ���佫�ĳ���
		Bool				loadSelectGeneralScene();
		// �����佫ѡ��ĳ���
		void				destroySelectGeneralScene();

		// ���ش����佫�ĳ���
		Bool				loadCreateGeneralScene();
		// ���ٴ����佫�ĳ���
		void				destroyCreateGeneralScene();

	private:

		// ������ʼ��ȡ�ص�
		void				beginLoadScene(CChar* newPath, I32 ctrlType);
		// ������ȡ
		void				loadScene(CChar* mapName, I32 ctrlType);
		// ������ȡ�����ص�
		void				endLoadScene(CChar* newPath, I32 ctrlType);

	private:

		// ���û���״̬
		void				initManualRenderState(I32 ctrlType);

    protected:

        static Str			STATE_NAME;
		

    };

}

/******************************************************************************/

#endif

