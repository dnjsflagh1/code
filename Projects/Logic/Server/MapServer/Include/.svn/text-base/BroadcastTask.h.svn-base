//***********************************************************************************************************
#ifndef _BROADCASTTASK_H_
#define _BROADCASTTASK_H_
//***********************************************************************************************************
#include "MapServerPreqs.h"
#include "Task.h"
//***********************************************************************************************************
namespace MG
{

    ////***********************************************************************************************************
    //// 广播任务
    ////***********************************************************************************************************
    //class BroadcastTask : public ModeTask
    //{	
    //public:
    //    BroadcastTask();
    //    ~BroadcastTask();
    //    SINGLETON_INSTANCE(BroadcastTask);

    //    // 更新
    //    Bool    update();

    //    // 请求广播角色移动
    //    void    requestBroadcastPlayerCharacterMove( PT_PLAYERCHARACTER_C2S_MOVE_POS_DATA* data );

    //protected:
    //    
    //    // 开始广播
    //    void	startBroadcast();

    //protected:

    //    virtual RegionIdType		getRegionId()				= NULL;
    //    virtual	REGION_OBJ_TYPE		getRegionType() const		= NULL;

    //    /******************************************************************************/
    //    // 角色广播包池
    //    /******************************************************************************/
    //    template<typename BP>
    //    class CharacterBroadcastPacketPool
    //    {
    //    public:
    //        
    //        struct BroadcastData
    //        {
    //            RegionIdType        regionID;
    //            REGION_OBJ_TYPE     regionType;

    //            BP                  data;
    //        };

    //        Critical                                            mPoolCs;

    //        typedef std::map<GameObjectIdType, BroadcastData*>  AllPrepareCharacterPacketMap;     

    //        typedef std::pair<GameObjectIdType, BroadcastData*> OneCharacterPacketPair;   
    //        typedef std::vector<OneCharacterPacketPair>         AllProcessCharacterPacketMap;     

    //        AllPrepareCharacterPacketMap                        mAllPrepareCharacterPacketMap;
    //        AllProcessCharacterPacketMap                        mAllProcessCharacterPacketMap;

    //        ObjectPool<BroadcastData>                           mBroadcastDataPool;

    //    public:

    //        // 增加一个准备发送的网络包
    //        inline void addPreparePacket( I32 id, RegionIdType regionID, REGION_OBJ_TYPE regionType, BP* packet )
    //        {
    //            BroadcastData* prepareCharacterPacket = NULL;

    //            mPoolCs.lock();
    //            {
    //               AllPrepareCharacterPacketMap::iterator iter = mAllPrepareCharacterPacketMap.find(id);
    //               if(iter == mAllPrepareCharacterPacketMap.end())
    //               {
    //                   prepareCharacterPacket = MG_POOL_NEW(mBroadcastDataPool, BroadcastData, ());
    //                   mAllPrepareCharacterPacketMap[id] = prepareCharacterPacket;
    //               }else
    //               {
    //                   prepareCharacterPacket = iter->second;
    //               }

    //               // 填充
    //               if ( prepareCharacterPacket )
    //               {
    //                   prepareCharacterPacket->regionID     = regionID;
    //                    prepareCharacterPacket->regionType  = regionType;
    //                   prepareCharacterPacket->data         = *packet;
    //               }
    //            }
    //            mPoolCs.unlock();
    //        }

    //        //-------------------------------------------------------------------------------

    //        // 转移映射表中的数据到列表中
    //        inline void movePrepareMapToProcessList()
    //        {
    //            mPoolCs.lock();
    //            {
    //                DYNAMIC_ASSERT( mAllProcessClientPacketList.size() == 0 );
    //                for(AllPrepareCharacterPacketMap::iterator iter = mAllPrepareCharacterPacketMap.begin(); 
    //                    iter != mAllPrepareCharacterPacketMap.end(); ++iter)
    //                {
    //                    mAllProcessCharacterPacketMap.push_back( 
    //                        OneCharacterPacketPair( iter->first, iter->second ) );
    //                }
    //                mAllPrepareCharacterPacketMap.clear();
    //            }
    //            mPoolCs.unlock();
    //        }

    //        //-------------------------------------------------------------------------------

    //        // 清空处理列表
    //        inline void    clearProcessList()
    //        {
    //            BroadcastData* bpPacket = NULL;

    //            for( UInt i=0; i<mAllProcessCharacterPacketMap.size(); i++ )
    //            {   
    //                bpPacket    = mAllProcessCharacterPacketMap[i].second;

    //                mPoolCs.lock();
    //                {
    //                    MG_POOL_DELETE(mBroadcastDataPool, bpPacket);
    //                }
    //                mPoolCs.unlock();

    //            }

    //            mAllProcessCharacterPacketMap.clear();
    //        }

    //        //-------------------------------------------------------------------------------

    //        // 发送处理列表
    //        inline void    sendProcessPacketList( Byte channel, Byte type )
    //        {
    //            GameObjectIdType id = 0;
    //            BroadcastData* bpPacket = NULL;

    //            for( UInt i=0; i<mAllProcessCharacterPacketMap.size(); i++ )
    //            {   
    //                id          = mAllProcessCharacterPacketMap[i].first;
    //                bpPacket    = mAllProcessCharacterPacketMap[i].second;
    //                
    //                if ( isInRegion( id, bpPacket->regionID, bpPacket->regionType ) )
    //                {
    //                    
    //                    


    //                }
    //            }
    //        }

    //        //-------------------------------------------------------------------------------

    //        // 判断是否还在该区域
    //        virtual void    isInRegion( GameObjectIdType id,  RegionIdType regionID, REGION_OBJ_TYPE regionType )  = 0;
    //    };

    //    ///////////////////////////////////////////////////////////////////////////////////////////
    //
    //private:
    //    




    //};
}

#endif	