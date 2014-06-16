/******************************************************************************/
#ifndef _GAMEMAIN_H_
#define _GAMEMAIN_H_
/******************************************************************************/

#include "ClientPreqs.h"

/******************************************************************************/
namespace MG
{
    
    /******************************************************************************/
    //��Ϸ�������ӿ�
    /******************************************************************************/
    class GameMain
    {
    public:

        SINGLETON_INSTANCE(GameMain)
        GameMain();
        virtual ~GameMain();

        /// ��Ϸ��ʼ��
        Bool        initialize(IMGExternalPackManager* packManager) ;
        /// ������Ϸ
        void        run();
        /// ��Ϸ����ʼ��
        Bool        uninitialize() ;
        /// ����
        Bool        update( Dbl delta );

        /// ֹͣ��Ϸ�������»�ԭ��Ϸ������̬ģ���ڴ�����
        /// ��Ϸ����ص��������
        void        stopAndRestore();

        // ����������
        void        enterLogoScreen();
        // ����������
        void        enterLoginScreen();
        // ������Ϸ����
        void        enterGameScreen();

        /// ������в���������
        void        clearOperatorCtrls() ;
        /// ��ԭ���в���������
        void        revertOperatorCtrls();
        /// ���Ӳ���������
        void        addOperatorCtrls(IOpCtrl* ctrl) ;
        /// �Ƴ�����������
        void        removeOperatorCtrls(IOpCtrl* ctrl) ;

    public:

        // ����ʼ���س���
        void        onStartLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType );
        // ���������س���
        void        onEndLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType );
        /// ��ж�س���
        void        onUnloadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType );

    protected:

        /// ������Ϸ�ļ�
        Bool        loadGameFile(IMGExternalPackManager* packManager);

        /// ���ؽű��ļ�
        Bool        loadGameScript();

    private:

        // ������״̬������
        LinedStateManager   mScreenLinedStateManager;
        IScreen* mActiveScreen;

        /// �������Ƽ���
        std::vector<IOpCtrl*> mOpCtrls;


    };

}

/******************************************************************************/

#endif

