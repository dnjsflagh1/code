#include "stdafx.h"
#include "BuildTemplateInfo.h"

namespace MG
{
	BuildTemplateInfos::BuildTemplateInfos()
	{

	}
    //-----------------------------------------------------------------------------------------------
	BuildTemplateInfos::~BuildTemplateInfos()
	{
		BuildTemplateInfo* buildInfo = NULL;
		for(BuildInfoIt it = mBuildInfoList.begin(); it != mBuildInfoList.end(); ++it)
		{
			buildInfo = it->second;
			if(buildInfo)
			{
				delete buildInfo;
				buildInfo = NULL;
			}
		}
	}
    //-----------------------------------------------------------------------------------------------
	Bool BuildTemplateInfos::loadFile(CChar16* fileName)
	{
		CsvReader csvreader;

		if(!csvreader.create(fileName))
		{
			return false;
		}

		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();
        BuildTemplateInfo* buildinfo = NULL;
		for(int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}
            Int nCol = 0;
			buildinfo = new BuildTemplateInfo;
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), buildinfo->id);
			buildinfo->name = csvdata->mData[nCol++];
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), buildinfo->lvl);
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), buildinfo->characterTempId);
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), buildinfo->artIconResId);
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), buildinfo->artMeshResId);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), buildinfo->artMapResId);			
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), buildinfo->audioResId);

			mBuildInfoList[buildinfo->id] = buildinfo;
		}

		return true;
	}
    //-----------------------------------------------------------------------------------------------
    const BuildTemplateInfo* BuildTemplateInfos::getBuildTemplateInfo( U32 buildTempID )
    {
        return mBuildInfoList[buildTempID];
    }
    //-----------------------------------------------------------------------------------------------
    MG::Bool BuildTemplateInfos::getBuildTemplateInfo( U32 buildTempID, const BuildTemplateInfo*& info )
    {
        BuildTemplateInfo* pInfo = mBuildInfoList[buildTempID];
        if ( pInfo )
        {
            info = pInfo;
            return true;
        }

        return false;
    }

}