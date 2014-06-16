/******************************************************************************/
#ifndef _COREMANAGER_H_
#define _COREMANAGER_H_
/******************************************************************************/

namespace GameMapEditor {


    /******************************************************************************/
    class CoreManager
    {
    public:
        SINGLETON_INSTANCE(CoreManager)
        CoreManager();
        ~CoreManager();

        /** ��Ϸ��ʼ��. */
        Bool            initialize() ;
        /** ������Ϸ. */
        void            run();
        /** ��Ϸ����ʼ�� */
        Bool            uninitialize() ;

        /** ֹͣ��Ϸ. */
        void            stop();

        /** �õ���������. */
        IScene*         getScene();
        /** �õ���Ϸ����ӿ�. */
        IEngineMain*    getEngineMain();

        /** ���ó���. */
        void            initScene();

    public:

        /** �����ⲿ�� */
        Bool            loadLib();
        /** ж���ⲿ��. */
        Bool            unLoadLib();
        /** ��������. */
        Bool            loadEngine();
        /** ж������. */
        Bool            unLoadEngine();
        /** ������Ϸ����. */
        Bool            loadGameFile();
        /** ж����Ϸ���� */
        Bool            unLoadGameFile();
        /** ���ش���. */
        Bool            loadForm();
        /** ж�ش���. */
        Bool            unLoadForm();
        /** ��Ϸ����. */
        Bool            update( Dbl delta );

    private:
       
        /// ��Ϸ����ӿ�ָ��
        IEngineMain* mEngineMain;
        /// ��Ϸ����DLL������
        DllLoader mEngineDllLoader;

        /// ��Ϸ������
        IScene* mMainScene;

        /// ��Ϸ����ֹͣ��־λ
        Bool mStopUpdateDirty;
        /// �ϴθ���֡ʱ��
        Dbl mLastUpdateTicks;
        /// ��ǰ����֡ʱ��
        Dbl mCurrUpdateTicks;
        /// ��ǰ����֡ʱ���
        Dbl mUpdateDelta;
    };

}

/******************************************************************************/
#endif

