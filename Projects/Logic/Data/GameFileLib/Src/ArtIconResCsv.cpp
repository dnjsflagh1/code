//***********************************************************************************************
#include "stdafx.h"
#include "ArtIconResCsv.h"
//***********************************************************************************************
namespace MG
{
    ArtIconResCsv::~ArtIconResCsv()
    {
        clear();
    }
    //-----------------------------------------------------------------------------------
	// MG_CN_MODIFY
    MG::Bool ArtIconResCsv::load( Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/)
    {
        CsvReader csvreader;
		// MG_CN_MODIFY
        if(!csvreader.create(fileName, packManager))
        {
            return false;
        }

        CsvData* csvdata = NULL;
        Int RowCount = csvreader.count();

        for(int i = 0; i < RowCount; ++i)
        {
            csvdata = csvreader.findValue(i);
            if(!csvdata)
            {
                continue;
            }

            ArtIconResCsvInfo* tempInfo = new ArtIconResCsvInfo;
            UInt nCol = 0;

            MGStrOp::toU32(csvdata->mData[nCol++].c_str(),      tempInfo->ArtIconRes_Id     );
			nCol++;
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(),      (U32&)tempInfo->Type        );
            MGStrOp::toString(csvdata->mData[nCol++].c_str(),   tempInfo->ResName	        );
            MGStrOp::toString(csvdata->mData[nCol++].c_str(),   tempInfo->GroupName	        );
            MGStrOp::toString(csvdata->mData[nCol++].c_str(),   tempInfo->ItemName	        );
			MGStrOp::toString(csvdata->mData[nCol++].c_str(),   tempInfo->SmallResName	    );
			MGStrOp::toString(csvdata->mData[nCol++].c_str(),   tempInfo->SmallGroupName	);
			MGStrOp::toString(csvdata->mData[nCol++].c_str(),   tempInfo->SmallItemName	    );

            mArtIconResCsvMap[tempInfo->ArtIconRes_Id] = tempInfo;
        }

        return true;
    }
    //-----------------------------------------------------------------------------------
    const ArtIconResCsvInfo* ArtIconResCsv::getIconArtResInfo( U32 id )
    {
		std::map<U32, ArtIconResCsvInfo*>::iterator it = mArtIconResCsvMap.find(id);
		if (it != mArtIconResCsvMap.end())
		{
			return it->second;
		}
		return NULL;
    }
    //-----------------------------------------------------------------------------------
    MG::Bool ArtIconResCsv::getIconArtResInfo( U32 id, const ArtIconResCsvInfo*& info )
    {
		Bool ret = false;
		std::map<U32, ArtIconResCsvInfo*>::iterator it = mArtIconResCsvMap.find(id);
		if (it != mArtIconResCsvMap.end())
		{
			info = it->second;
			if (info)
			{
				ret = true;
			}
		}
		return ret;
    }
	//-----------------------------------------------------------------------------------
	bool ArtIconResCsv::getIconArtResInfo(IOCN_ART_TYPE type,std::map<U32, ArtIconResCsvInfo*>& mapinfo)
	{
		

        if (mArtIconResCsvMap.empty())
          return false;
		std::map<U32, ArtIconResCsvInfo*>::iterator front = mArtIconResCsvMap.begin();
		std::map<U32, ArtIconResCsvInfo*>::iterator back = mArtIconResCsvMap.end();
		U32 i = 1;
		while (front != back)
		{
			if ((front->second->Type) == type)
			{
				mapinfo[i] = front->second;
				i++;
			}

			front++;
		}
		return true;
	}
	//-----------------------------------------------------------------------------------
    void ArtIconResCsv::clear()
    {
        std::map<U32, ArtIconResCsvInfo*>::iterator front = mArtIconResCsvMap.begin();
        std::map<U32, ArtIconResCsvInfo*>::iterator back = mArtIconResCsvMap.end();
        while (front != back)
        {
            delete front->second;
            ++front;
        }

        mArtIconResCsvMap.clear();
    }
}