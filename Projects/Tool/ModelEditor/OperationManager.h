/******************************************************************************/
#ifndef _OPERATIONMANAGER_H_
#define _OPERATIONMANAGER_H_
/******************************************************************************/



/******************************************************************************/

namespace ModelEditor 
{
    /******************************************************************************/
	class OperationManager
    {
    public:
        SINGLETON_INSTANCE(OperationManager)
        OperationManager();
        ~OperationManager();
        void update( Dbl delta );

    //*********************************************************
    //【摄像机操作】
    public:

        ///还原摄像机
        void revertCamera();
        void updateFreeCameraOp( IInput* input, ITerrainManager* terrain, ICamera* camera, Dbl delta );
        
    //*********************************************************

    private:
       
        Int                 mCurrModelDeclID;
        Flt                 mCameraSpeed;
        Bool                mViewportLock;
        Vec3                mLastMouseTerrainIntersection;

		Flt				    mTimeMouseHold;
		Flt				    mOpInterval;
        Bool			    mIsMouseStateCheck;

        Bool                mRaiseOrLowHeight;
        Bool                mMoveHeight;

        std::vector<Flt>    mCameraHeightSet;
        Flt                 mMaxPitch;
        Flt                 mMinPitch;
    };

}

/******************************************************************************/
#endif

