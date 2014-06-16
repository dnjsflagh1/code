//***********************************************************************************************************
#ifndef _THREADTASK_H_
#define _THREADTASK_H_
//***********************************************************************************************************
#include "FrontServerPreqs.h"
//***********************************************************************************************************
namespace MG
{
    //***********************************************************************************************************
    // 线程任务类型
    //***********************************************************************************************************
    enum ThreadTaskType
    {
        TTT_PREPAREJOINGAME = 0,
        TTT_CREATECLAN,
        TTT_DELETECLAN,
        TTT_CREATEGENERAL,
        TTT_JOINGAMETASK,
        
        TTT_NORMAL_SERVER,
        TTT_NETTRANSPOND_SEND_SERVER,
        TTT_NETTRANSPOND_SAVE_SERVER,
    };

	//***********************************************************************************************************
	// LoginServer检测后 准备进入游戏任务
	//***********************************************************************************************************
    class PrepareJoinGameTask : public ModeTask
    {	
    public:
		PrepareJoinGameTask(NetEventRecv* netEvent,U32 key = 0);
        ~PrepareJoinGameTask();
		virtual	void	process();
		virtual	void	free();
		NetEventRecv	*mNetEvent;
    };

	//***********************************************************************************************************
	// 创建家族任务
	//***********************************************************************************************************
	class CreateClanTask : public ModeTask
	{	
	public:
		CreateClanTask(NetEventRecv* netEvent,I32 netId,U32 key = 0);
		~CreateClanTask();
		virtual	void	process();
		virtual	void	free();
		NetEventRecv	*mNetEvent;
		I32				mClientNetId;
	};

	//***********************************************************************************************************
	// 删除家族任务
	//***********************************************************************************************************
	class DeleteClanTask : public ModeTask
	{	
	public:
		DeleteClanTask(I32 clientNetId,NetEventRecv* netEvent,U32 key = 0);
		~DeleteClanTask();
		virtual	void	process();
		virtual	void	free();
		NetEventRecv	*mNetEvent;
		I32				mClientNetId;
	};

	//***********************************************************************************************************
	// 创建武将任务
	//***********************************************************************************************************
	class CreateGeneralTask : public ModeTask
	{	
	public:
		CreateGeneralTask(NetEventRecv* netEvent,I32 clientNetId,U32 key = 0);
		~CreateGeneralTask();
		virtual	void	process();
		virtual	void	free();
		NetEventRecv	*mNetEvent;
		I32				mClientNetId;
	};

	//***********************************************************************************************************
	// 进入游戏任务
	//***********************************************************************************************************
	class JoinGameTask : public ModeTask
	{	
	public:
		JoinGameTask(NetEventRecv* netEvent,I32 clientNetId, U32 key = 0);
		~JoinGameTask();
		virtual	void	process();
		virtual	void	free();
		NetEventRecv	*mNetEvent;
		I32				mClientNetId;
	};


	//***********************************************************************************************************
	// 服务器日常消息处理任务
	//***********************************************************************************************************
	class ServerNormalTask : public ModeTask
	{	
	public:
		ServerNormalTask(NetEventRecv* netEvent,I32 serverNetId, U32 key = 0);
		~ServerNormalTask();
		virtual	void	process();
		virtual	void	free();
		NetEventRecv	*mNetEvent;
		I32				mServerNetId;
	};

    //***********************************************************************************************************
    // 服务器发送转发消息处理任务
    //***********************************************************************************************************
    class ServerNetTranspondSendTask : public ModeTask
    {	
    public:
        ServerNetTranspondSendTask(NetEventRecv* netEvent,I32 serverNetId, U32 key = 0);
        ~ServerNetTranspondSendTask();
        virtual	void	process();
        virtual	void	free();
        NetEventRecv	*mNetEvent;
        I32				mServerNetId;
    };


    //***********************************************************************************************************
    // 服务器保存转发消息处理任务
    //***********************************************************************************************************
    class ServerNetTranspondSaveTask : public ModeTask
    {	
    public:
        ServerNetTranspondSaveTask(NetEventRecv* netEvent,I32 serverNetId, U32 key = 0);
        ~ServerNetTranspondSaveTask();
        virtual	void	process();
        virtual	void	free();
        NetEventRecv	*mNetEvent;
        I32				mServerNetId;
    };

}
//***********************************************************************************************************
#endif
//***********************************************************************************************************