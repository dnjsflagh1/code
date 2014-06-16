/******************************************************************************/
#ifndef _POLYLINEWIREFRAMEDECORATOR_H_
#define _POLYLINEWIREFRAMEDECORATOR_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ManualMeshManager.h"
#include "IWireframeManager.h"
#include "Polyline.h"

/******************************************************************************/

namespace MG
{


    /**
    -----------------------------------------------------------------------------
    #note:	������������ģ����Ϣ
    ÿ�������е��߶κͿ��Ƶ���TwistyBoxMeshData�������
    -----------------------------------------------------------------------------
    */
    class PolylineWireframeDecorator : public PolylineListener, public IPolylineWireframeDecorator
    {
    public:
        PolylineWireframeDecorator(const String& name, Scene* scene);
        virtual ~PolylineWireframeDecorator();

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

        /// �õ���װ�ε�Polyline
        virtual Polyline*   getPolyline(void);

    protected:

        /// ��������ζ���
        void                createOgreManualObject();
        /// ���ٶ���ζ���
        void                destroyOgreManualObject();

        /// �������� 
        String              createOrRetrieveOgreMaterial(void);

        /// ����ģ������
        void                buildMeshData(void);

        /// ����Ogre���ֶ�����ģ�Ͷ���
        void                buildOgreManualObject(void);
        
        /// ����Ogre���ֶ�����ģ�Ͷ���
        void                refreshOgreManualObject(void);

        /// �����Ƿ������߶��󱣳ָĶ���ͬ��
        void                setSyncEnable(bool enable);

    private:

        /// ���mesh���ݵ�Ogre���ֶ�����ģ�Ͷ�����
        void                fillMeshDataInOgreManualObject(void);

    private:

        //  ��������
        Scene*      mScene;
        //  ���߶���
        Polyline*   mPolyline;
        //  �Ƿ񱣳ָĶ�ͬ��
        Bool        mSyncEnable;
        /// ����ģ�ʹ�ϸ
        Flt         mBoldSize;
        /// ��ɫ 
        ColourValue mColour;

        //////////////////////////////////////////////////////

        /// Ogre���ֶ�����ģ�Ͷ���
        Ogre::ManualObject* mOgreManualObject;
        /// �ڵ����
        MGSceneNode* mSceneNode;
        /// Ogre���ʽӿ� 
        Ogre::MaterialPtr   mOgreMaterialPtr;

        ////////////////////////////////////////////////////////

        /// �������ģ�͵�TwistyBoxMeshData�����б�
        typedef std::list<TwistyBoxMeshData> TwistyBoxMeshDataList;
        TwistyBoxMeshDataList mTwistyBoxMeshDatas;
    };

}

/******************************************************************************/

#endif