//***********************************************************************************************************
#ifndef _JUMP_REGION_TASK_H_
#define _JUMP_REGION_TASK_H_
//***********************************************************************************************************
#include "MapServerPreqs.h"
#include "Task.h"
//***********************************************************************************************************
namespace MG
{

    //***********************************************************************************************************
    // 线程任务类型
    //***********************************************************************************************************
    enum ThreadTaskType
    {
        TTT_JUMPREGION = 0,
    
    };



	//***********************************************************************************************************
	// LoginServer检测后 准备进入游戏任务
	//***********************************************************************************************************
    class JumpRegionTask : public ModeTask
    {	
    public:
		JumpRegionTask(NetEventRecv* netEvent, I32 netId, U32 key);
        ~JumpRegionTask();
		virtual	void	process();
		virtual	void	free();

		I32			getNetId() const;

	private:
		void	processPlayerPackage(I32 id, GameNetPacketData* data);
		void	processPlayerCharacterPackage(I32 id, GameNetPacketData* data);
		void	processItemPackage(I32 id, GameNetPacketData* data);

	public:

		NetEventRecv	*mNetEvent;
		I32				mNetId;
    };
}

#endif	//_JUMP_REGION_TASK_H_