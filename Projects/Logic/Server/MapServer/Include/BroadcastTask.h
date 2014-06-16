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
    //// �㲥����
    ////***********************************************************************************************************
    //class BroadcastTask : public ModeTask
    //{	
    //public:
    //    BroadcastTask();
    //    ~BroadcastTask();
    //    SINGLETON_INSTANCE(BroadcastTask);

    //    // ����
    //    Bool    update();

    //    // ����㲥��ɫ�ƶ�
    //    void    requestBroadcastPlayerCharacterMove( PT_PLAYERCHARACTER_C2S_MOVE_POS_DATA* data );

    //protected:
    //    
    //    // ��ʼ�㲥
    //    void	startBroadcast();

    //protected:

    //    virtual RegionIdType		getRegionId()				= NULL;
    //    virtual	REGION_OBJ_TYPE		getRegionType() const		= NULL;

    //    /******************************************************************************/
    //    // ��ɫ�㲥����
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

    //        // ����һ��׼�����͵������
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

    //               // ���
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

    //        // ת��ӳ����е����ݵ��б���
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

    //        // ��մ����б�
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

    //        // ���ʹ����б�
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

    //        // �ж��Ƿ��ڸ�����
    //        virtual void    isInRegion( GameObjectIdType id,  RegionIdType regionID, REGION_OBJ_TYPE regionType )  = 0;
    //    };

    //    ///////////////////////////////////////////////////////////////////////////////////////////
    //
    //private:
    //    




    //};
}

#endif	