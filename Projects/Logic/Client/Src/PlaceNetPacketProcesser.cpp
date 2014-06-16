#include "stdafx.h"
#include "PlaceNetPacket.h"
#include "PlaceNetPacketProcesser.h"
//#include "CWorldManager.h"
#include "UISelectPlace.h"
#include "ClientNetApplyManager.h"
#include "CSceneManager.h"
namespace MG
{
	//--------------------------------------------------------------------------
	PlaceNetPacketProcesser::PlaceNetPacketProcesser()
	{

	}
	//--------------------------------------------------------------------------
	PlaceNetPacketProcesser::~PlaceNetPacketProcesser()
	{

	}
	//--------------------------------------------------------------------------
	void MG::PlaceNetPacketProcesser::onRecvPlaceInfoFromMapServer( I32 id, PT_PLACE_M2C_CLICED_INFO_DATA* data )
	{
#if 0
		//FUNDETECTION(__MG_FUNC__);
		PlaceObjectInfo* placeObj = CWorldManager_OldVersion::getInstance().getPlaceObjInfo(data->placeId);
		if (placeObj)
		{
			UISelectPlace::getInstance().setTitle(placeObj->name.c_str());
			UISelectPlace::getInstance().setDesc(placeObj->description.c_str());
			UISelectPlace::getInstance().setCurrPlaceObj(data->placeId);
			UISelectPlace::getInstance().openGui();
		}
#endif
	}

	//--------------------------------------------------------------------------
	Bool PlaceNetPacketProcesser::processFrontServerPacket( I32 id,NetEventRecv* packet )
	{
		if ( packet->getChannel() == GNPC_PLACE )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_PLACE_M2C_CLICED_INFO:
				onRecvPlaceInfoFromMapServer( id, (PT_PLACE_M2C_CLICED_INFO_DATA*)data->data );
				break;
			}
			return true;
		}
		return false;
	}
	//--------------------------------------------------------------------------
	void PlaceNetPacketProcesser::sendPlaceClickToMapServer( IdType placeId, NetVec2 placePos, NetVec2 placeDir)
	{
        // ���һ�����͡�����ˡ�����
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_PLACE;
            packet->type    = PT_PLACE_C2F_CLICED_INFO;

            // ת���߼���
            PT_PLACE_C2F_CLICED_INFO_DATA* sendData = (PT_PLACE_C2F_CLICED_INFO_DATA*)(packet->data);
            if ( sendData )
            {
                // ����߼���
                sendData->placeId = placeId;
                sendData->placePos = placePos.getData();
                sendData->placeDir = placeDir.getData();

                // ��������
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_PLACE_C2F_CLICED_INFO_DATA_INFO::dataSize );
            }
        }
	
    }

}
